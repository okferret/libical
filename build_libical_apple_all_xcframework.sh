#!/usr/bin/env bash
set -euo pipefail

# ===== 可调最低系统版本（按需改）=====
MIN_IOS="13.0"
MIN_TVOS="13.0"
MIN_WATCHOS="6.0"
MIN_MACOS="10.15"
MIN_CATALYST_IOS="14.0"

# ===== 架构配置（按需改）=====
SIM_ARCHS="arm64;x86_64"
MAC_ARCHS="arm64;x86_64"

ROOT="$(pwd)/libical-apple-build"
SRC_DIR="$ROOT/libical"
OUT_DIR="$ROOT/output"
BUILD_DIR="$ROOT/build"
XC_OUT="$ROOT/libical.xcframework"

# ===== CPU 核心数（并发时每个任务独占全部核心，由 OS 调度）=====
CPU_COUNT=$(sysctl -n hw.ncpu)

rm -rf "$ROOT"
mkdir -p "$ROOT" "$OUT_DIR" "$BUILD_DIR"

# ===== 获取最新版本并克隆源码 =====
echo "== Fetching latest release tag =="

LATEST_TAG=$(curl -fsSL https://api.github.com/repos/libical/libical/releases/latest \
  | python3 -c "import sys,json; print(json.load(sys.stdin)['tag_name'])")
echo "Latest libical version: $LATEST_TAG"

echo "== Cloning libical source =="
git clone --depth 1 --branch "$LATEST_TAG" https://github.com/libical/libical.git "$SRC_DIR"
echo "== Source cloned =="

# ===== 不依赖外部库的静态 CMake 参数（平台无关）=====
# libical 核心库仅依赖系统 C 库，无需第三方压缩库
COMMON_CMAKE_ARGS=(
  -DCMAKE_BUILD_TYPE=Release
  -DBUILD_SHARED_LIBS=OFF

  # ===== 只构建静态库 =====
  -DLIBICAL_STATIC=true

  # ===== 禁用不需要的组件 =====
  -DLIBICAL_BUILD_TESTING=false        # 不构建测试套件
  -DLIBICAL_BUILD_EXAMPLES=false       # 不构建示例程序
  -DLIBICAL_BUILD_DOCS=false           # 不构建 API 文档
  -DLIBICAL_BUILD_VZIC=false           # 不构建 vzic 工具

  # ===== 禁用语言绑定（Apple 平台不需要）=====
  -DLIBICAL_CXX_BINDINGS=false         # 不构建 C++ 绑定
  -DLIBICAL_JAVA_BINDINGS=false        # 不构建 Java 绑定
  -DLIBICAL_GLIB=false                 # 不构建 GLib/GObject 接口
  -DLIBICAL_GLIB_VAPI=false            # 不构建 Vala vapi 文件
  -DLIBICAL_GOBJECT_INTROSPECTION=false # 不构建 GObject 内省文件

  # ===== 时区数据 =====
  # 使用内置时区数据，避免依赖系统 /usr/share/zoneinfo
  # 对于 iOS/tvOS/watchOS 等无法访问系统时区数据库的平台，必须启用
  -DLIBICAL_ENABLE_BUILTIN_TZDATA=true

  # ===== 开发者模式（关闭）=====
  -DLIBICAL_DEVMODE=false
)

# ===== 通用构建函数 =====
# 参数：NAME SYSNAME SDK ARCHS DEPLOY [EXTRA_CMAKE_ARGS...]
build_one() {
  local NAME="$1"
  local SYSNAME="$2"
  local SDK="$3"
  local ARCHS="$4"
  local DEPLOY="$5"
  shift 5
  local EXTRA_ARGS=("$@")

  local BDIR="$BUILD_DIR/$NAME"
  local IDIR="$OUT_DIR/$NAME"
  rm -rf "$BDIR" "$IDIR"
  mkdir -p "$BDIR" "$IDIR"

  echo "== Configure $NAME (arch: $ARCHS) =="

  local CMAKE_CMD=(
    cmake -S "$SRC_DIR" -B "$BDIR"
    -G "Unix Makefiles"
    -DCMAKE_SYSTEM_NAME="$SYSNAME"
    -DCMAKE_OSX_SYSROOT="$SDK"
    -DCMAKE_OSX_ARCHITECTURES="$ARCHS"
    -DCMAKE_OSX_DEPLOYMENT_TARGET="$DEPLOY"
    -DCMAKE_INSTALL_PREFIX="$IDIR"
    "${COMMON_CMAKE_ARGS[@]}"
  )

  if [ ${#EXTRA_ARGS[@]} -gt 0 ]; then
    CMAKE_CMD+=("${EXTRA_ARGS[@]}")
  fi

  "${CMAKE_CMD[@]}"

  echo "== Build $NAME =="
  cmake --build "$BDIR" --config Release -- -j"$CPU_COUNT"

  echo "== Install $NAME =="
  cmake --install "$BDIR"

  echo "== Done: $NAME =="
}

# ===== 为 Catalyst 单独编译单个架构 =====
build_catalyst_arch() {
  local ARCH="$1"
  local NAME="catalyst-$ARCH"
  local IDIR="$OUT_DIR/$NAME"

  echo "== Build Catalyst for $ARCH =="

  local BDIR="$BUILD_DIR/$NAME"
  rm -rf "$BDIR" "$IDIR"
  mkdir -p "$BDIR" "$IDIR"

  # 清除可能冲突的环境变量
  unset MACOSX_DEPLOYMENT_TARGET
  unset SDKROOT

  cmake -S "$SRC_DIR" -B "$BDIR" \
    -G "Unix Makefiles" \
    -DCMAKE_SYSTEM_NAME="Darwin" \
    -DCMAKE_OSX_SYSROOT="macosx" \
    -DCMAKE_OSX_ARCHITECTURES="$ARCH" \
    -DCMAKE_INSTALL_PREFIX="$IDIR" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET="" \
    -DCMAKE_C_FLAGS="-target ${ARCH}-apple-ios${MIN_CATALYST_IOS}-macabi" \
    -DCMAKE_CXX_FLAGS="-target ${ARCH}-apple-ios${MIN_CATALYST_IOS}-macabi" \
    -DCMAKE_EXE_LINKER_FLAGS="-target ${ARCH}-apple-ios${MIN_CATALYST_IOS}-macabi" \
    -DCMAKE_SHARED_LINKER_FLAGS="-target ${ARCH}-apple-ios${MIN_CATALYST_IOS}-macabi" \
    -DCMAKE_MODULE_LINKER_FLAGS="-target ${ARCH}-apple-ios${MIN_CATALYST_IOS}-macabi" \
    "${COMMON_CMAKE_ARGS[@]}"

  cmake --build "$BDIR" --config Release -- -j"$CPU_COUNT"
  cmake --install "$BDIR"

  echo "== Done: $NAME =="
}

# ===== 并发编译所有平台 =====
echo "== Starting parallel builds (CPU cores: $CPU_COUNT) =="

# iOS device
build_one "ios-device" "iOS" "iphoneos" "arm64" "$MIN_IOS" &
PIDS=($!)

# iOS simulator
build_one "ios-sim" "iOS" "iphonesimulator" "$SIM_ARCHS" "$MIN_IOS" &
PIDS+=($!)

# tvOS device
build_one "tvos-device" "tvOS" "appletvos" "arm64" "$MIN_TVOS" \
  -DHAVE_FORK=OFF \
  -DHAVE_VFORK=OFF \
  -DHAVE_POSIX_SPAWN=OFF \
  -DHAVE_POSIX_SPAWNP=OFF &
PIDS+=($!)

# tvOS simulator
build_one "tvos-sim" "tvOS" "appletvsimulator" "$SIM_ARCHS" "$MIN_TVOS" \
  -DHAVE_FORK=OFF \
  -DHAVE_VFORK=OFF \
  -DHAVE_POSIX_SPAWN=OFF \
  -DHAVE_POSIX_SPAWNP=OFF &
PIDS+=($!)

# watchOS simulator
build_one "watchos-sim" "watchOS" "watchsimulator" "$SIM_ARCHS" "$MIN_WATCHOS" \
  -DHAVE_FORK=OFF \
  -DHAVE_VFORK=OFF \
  -DHAVE_POSIX_SPAWN=OFF \
  -DHAVE_POSIX_SPAWNP=OFF &
PIDS+=($!)

# macOS
build_one "macos" "Darwin" "macosx" "$MAC_ARCHS" "$MIN_MACOS" &
PIDS+=($!)

# watchOS 真机（arm64_32 优先，失败则回退 arm64，串行处理避免回退逻辑竞争）
(
  build_one "watchos-device" "watchOS" "watchos" "arm64_32" "$MIN_WATCHOS" \
    -DHAVE_FORK=OFF \
    -DHAVE_VFORK=OFF \
    -DHAVE_POSIX_SPAWN=OFF \
    -DHAVE_POSIX_SPAWNP=OFF || {
    echo "Warning: arm64_32 build failed, trying arm64..."
    build_one "watchos-device" "watchOS" "watchos" "arm64" "$MIN_WATCHOS" \
      -DHAVE_FORK=OFF \
      -DHAVE_VFORK=OFF \
      -DHAVE_POSIX_SPAWN=OFF \
      -DHAVE_POSIX_SPAWNP=OFF
  }
) &
PIDS+=($!)

# 等待所有并发任务完成
echo "== Waiting for all parallel builds to complete =="
FAILED=0
for PID in "${PIDS[@]}"; do
  if ! wait "$PID"; then
    echo "❌ A parallel build task (PID=$PID) failed"
    FAILED=1
  fi
done
[ "$FAILED" -eq 1 ] && { echo "❌ One or more builds failed. Aborting."; exit 1; }
echo "== All parallel builds completed =="

# ===== Mac Catalyst（串行，因需 unset 环境变量）=====
echo "== Mac Catalyst =="
echo "Info: Using MIN_CATALYST_IOS=${MIN_CATALYST_IOS} for Catalyst target"

# 检测当前 Xcode 主版本，若 >= 26 则跳过 x86_64 Catalyst（Apple Silicon Mac 不需要）
XCODE_MAJOR=$(xcodebuild -version 2>/dev/null | awk '/^Xcode/{print int($2)}')
echo "Detected Xcode major version: ${XCODE_MAJOR}"

SKIP_CATALYST_X86=false
if [ "${XCODE_MAJOR}" -ge 26 ] 2>/dev/null; then
  echo "Xcode >= 26 detected: skipping x86_64 Catalyst (not needed on Apple Silicon)"
  SKIP_CATALYST_X86=true
fi

if [ "$SKIP_CATALYST_X86" = false ]; then
  build_catalyst_arch "x86_64" || {
    echo "Catalyst x86_64 build failed, skipping Catalyst support"
    rm -rf "$OUT_DIR/catalyst-x86_64" "$OUT_DIR/catalyst-arm64" "$OUT_DIR/catalyst"
    touch "$OUT_DIR/.catalyst_unavailable"
  }
fi

if [ ! -f "$OUT_DIR/.catalyst_unavailable" ]; then
  build_catalyst_arch "arm64" || {
    echo "Catalyst arm64 build failed, skipping Catalyst support"
    rm -rf "$OUT_DIR/catalyst-x86_64" "$OUT_DIR/catalyst-arm64" "$OUT_DIR/catalyst"
    touch "$OUT_DIR/.catalyst_unavailable"
  }
fi

# 合并 Catalyst 的 fat 库（如果可用）
if [ ! -f "$OUT_DIR/.catalyst_unavailable" ]; then
  HAS_X86_CATALYST=false
  HAS_ARM64_CATALYST=false
  [ -f "$OUT_DIR/catalyst-x86_64/lib/libical.a" ] && HAS_X86_CATALYST=true
  [ -f "$OUT_DIR/catalyst-arm64/lib/libical.a" ] && HAS_ARM64_CATALYST=true

  if [ "$HAS_X86_CATALYST" = true ] && [ "$HAS_ARM64_CATALYST" = true ]; then
    echo "== Merging Catalyst architectures (arm64 + x86_64) =="
    mkdir -p "$OUT_DIR/catalyst/lib"
    lipo -create \
      "$OUT_DIR/catalyst-x86_64/lib/libical.a" \
      "$OUT_DIR/catalyst-arm64/lib/libical.a" \
      -output "$OUT_DIR/catalyst/lib/libical.a"
    # 同时合并 libicalss.a（时区数据库静态库，如果存在）
    if [ -f "$OUT_DIR/catalyst-x86_64/lib/libicalss.a" ] && [ -f "$OUT_DIR/catalyst-arm64/lib/libicalss.a" ]; then
      lipo -create \
        "$OUT_DIR/catalyst-x86_64/lib/libicalss.a" \
        "$OUT_DIR/catalyst-arm64/lib/libicalss.a" \
        -output "$OUT_DIR/catalyst/lib/libicalss.a"
    fi
    if [ -f "$OUT_DIR/catalyst-x86_64/lib/libicalvcal.a" ] && [ -f "$OUT_DIR/catalyst-arm64/lib/libicalvcal.a" ]; then
      lipo -create \
        "$OUT_DIR/catalyst-x86_64/lib/libicalvcal.a" \
        "$OUT_DIR/catalyst-arm64/lib/libicalvcal.a" \
        -output "$OUT_DIR/catalyst/lib/libicalvcal.a"
    fi
    cp -r "$OUT_DIR/catalyst-arm64/include" "$OUT_DIR/catalyst/"
    echo "Catalyst fat library (arm64 + x86_64) created"
  elif [ "$HAS_ARM64_CATALYST" = true ]; then
    echo "== Using Catalyst arm64-only library =="
    mkdir -p "$OUT_DIR/catalyst/lib"
    cp "$OUT_DIR/catalyst-arm64/lib/libical.a" "$OUT_DIR/catalyst/lib/libical.a"
    [ -f "$OUT_DIR/catalyst-arm64/lib/libicalss.a" ]    && cp "$OUT_DIR/catalyst-arm64/lib/libicalss.a"    "$OUT_DIR/catalyst/lib/libicalss.a"
    [ -f "$OUT_DIR/catalyst-arm64/lib/libicalvcal.a" ]  && cp "$OUT_DIR/catalyst-arm64/lib/libicalvcal.a"  "$OUT_DIR/catalyst/lib/libicalvcal.a"
    cp -r "$OUT_DIR/catalyst-arm64/include" "$OUT_DIR/catalyst/"
    echo "Catalyst arm64-only library created"
  else
    echo "Catalyst support disabled or build failed"
    touch "$OUT_DIR/.catalyst_unavailable"
  fi
else
  echo "Catalyst support disabled or build failed"
fi

# ===== 将各平台的多个静态库合并为单一 libical.a =====
# libical 会生成 libical.a / libicalss.a / libicalvcal.a 三个静态库
# 为方便 XCFramework 使用，将它们合并为一个 libical_merged.a
echo "== Merging libical static libraries per platform =="

merge_platform_libs() {
  local PLATFORM_DIR="$1"
  local LIB_DIR="$PLATFORM_DIR/lib"

  local LIBS_TO_MERGE=()
  [ -f "$LIB_DIR/libical.a" ]      && LIBS_TO_MERGE+=("$LIB_DIR/libical.a")
  [ -f "$LIB_DIR/libicalss.a" ]    && LIBS_TO_MERGE+=("$LIB_DIR/libicalss.a")
  [ -f "$LIB_DIR/libicalvcal.a" ]  && LIBS_TO_MERGE+=("$LIB_DIR/libicalvcal.a")

  if [ ${#LIBS_TO_MERGE[@]} -gt 1 ]; then
    local MERGED_TMP="$LIB_DIR/libical_merged.a"
    libtool -static -o "$MERGED_TMP" "${LIBS_TO_MERGE[@]}"
    # 用合并后的库替换 libical.a（XCFramework 只引用 libical.a）
    mv "$MERGED_TMP" "$LIB_DIR/libical.a"
    echo "  ✓ Merged $(basename $PLATFORM_DIR): libical.a + libicalss.a + libicalvcal.a -> libical.a"
  elif [ ${#LIBS_TO_MERGE[@]} -eq 1 ]; then
    echo "  ✓ $(basename $PLATFORM_DIR): only libical.a found, no merge needed"
  else
    echo "  ⚠ $(basename $PLATFORM_DIR): no libical.a found, skipping"
  fi
}

for PLATFORM_DIR in \
  "$OUT_DIR/ios-device" \
  "$OUT_DIR/ios-sim" \
  "$OUT_DIR/tvos-device" \
  "$OUT_DIR/tvos-sim" \
  "$OUT_DIR/watchos-device" \
  "$OUT_DIR/watchos-sim" \
  "$OUT_DIR/macos" \
  "$OUT_DIR/catalyst"; do
  [ -d "$PLATFORM_DIR" ] && merge_platform_libs "$PLATFORM_DIR"
done

# 验证所有生成的库
echo "== Verifying all libraries =="
find "$OUT_DIR" -name "libical.a" -type f | while read -r lib; do
  echo "  $(basename $(dirname $(dirname $lib)))/$(basename $lib):"
  lipo -info "$lib" 2>/dev/null | sed 's/^/    /' || echo "    Not a fat library or invalid"
done

# ===== 为每个平台的 Headers 目录生成 module.modulemap（Swift 导入所需）=====
echo "== Generating module.modulemap for Swift support =="

# libical 主要头文件：ical.h 是聚合头文件，包含所有公共 API
MODULEMAP_CONTENT='module libical {
    header "libical/ical.h"

    export *
}'

for PLATFORM_DIR in \
  "$OUT_DIR/ios-device" \
  "$OUT_DIR/ios-sim" \
  "$OUT_DIR/tvos-device" \
  "$OUT_DIR/tvos-sim" \
  "$OUT_DIR/watchos-device" \
  "$OUT_DIR/watchos-sim" \
  "$OUT_DIR/macos" \
  "$OUT_DIR/catalyst"; do
  if [ -d "$PLATFORM_DIR/include" ]; then
    echo "$MODULEMAP_CONTENT" > "$PLATFORM_DIR/include/module.modulemap"
    echo "  ✓ Written: $PLATFORM_DIR/include/module.modulemap"
  fi
done

# ===== 创建 XCFramework =====
echo "== Creating XCFramework =="
rm -rf "$XC_OUT"

XC_ARGS=()

[ -f "$OUT_DIR/ios-device/lib/libical.a" ]     && XC_ARGS+=(-library "$OUT_DIR/ios-device/lib/libical.a"     -headers "$OUT_DIR/ios-device/include")
[ -f "$OUT_DIR/ios-sim/lib/libical.a" ]         && XC_ARGS+=(-library "$OUT_DIR/ios-sim/lib/libical.a"         -headers "$OUT_DIR/ios-sim/include")
[ -f "$OUT_DIR/tvos-device/lib/libical.a" ]     && XC_ARGS+=(-library "$OUT_DIR/tvos-device/lib/libical.a"     -headers "$OUT_DIR/tvos-device/include")
[ -f "$OUT_DIR/tvos-sim/lib/libical.a" ]        && XC_ARGS+=(-library "$OUT_DIR/tvos-sim/lib/libical.a"        -headers "$OUT_DIR/tvos-sim/include")
[ -f "$OUT_DIR/watchos-device/lib/libical.a" ]  && XC_ARGS+=(-library "$OUT_DIR/watchos-device/lib/libical.a"  -headers "$OUT_DIR/watchos-device/include")
[ -f "$OUT_DIR/watchos-sim/lib/libical.a" ]     && XC_ARGS+=(-library "$OUT_DIR/watchos-sim/lib/libical.a"     -headers "$OUT_DIR/watchos-sim/include")
[ -f "$OUT_DIR/macos/lib/libical.a" ]           && XC_ARGS+=(-library "$OUT_DIR/macos/lib/libical.a"           -headers "$OUT_DIR/macos/include")
[ -f "$OUT_DIR/catalyst/lib/libical.a" ]        && XC_ARGS+=(-library "$OUT_DIR/catalyst/lib/libical.a"        -headers "$OUT_DIR/catalyst/include")

if [ ${#XC_ARGS[@]} -gt 0 ]; then
  xcodebuild -create-xcframework \
    "${XC_ARGS[@]}" \
    -output "$XC_OUT"

  echo "✅ XCFramework created: $XC_OUT"

  echo "== XCFramework Info =="
  echo "Framework slices:"
  plutil -p "$XC_OUT/Info.plist" | grep -A 5 "AvailableLibraries"

  echo -e "\nIndividual library architectures:"
  find "$XC_OUT" -name "libical.a" -exec lipo -info {} \;

  echo -e "\nModule map files (Swift support):"
  find "$XC_OUT" -name "module.modulemap" | while read -r f; do
    echo "  ✓ $f"
  done
else
  echo "Error: No libraries found to create XCFramework"
  exit 1
fi

# ===== 清理中间文件，只保留最终的 XCFramework =====
echo ""
echo "== Cleaning up intermediate files =="

rm -rf "$SRC_DIR"   && echo "  ✓ Removed libical source directory"
rm -rf "$BUILD_DIR" && echo "  ✓ Removed build directory"
rm -rf "$OUT_DIR"   && echo "  ✓ Removed output directory"
rmdir "$ROOT" 2>/dev/null || true

echo ""
echo "✅ Cleanup complete! Only XCFramework remains:"
echo "   $XC_OUT"
echo ""
echo "📦 Final output size:"
du -sh "$XC_OUT" 2>/dev/null || echo "  (unable to determine size)"

# 可选：将 XCFramework 移动到当前目录
# mv "$XC_OUT" ./libical.xcframework
# echo "   Moved to: $(pwd)/libical.xcframework"
