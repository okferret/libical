#!/bin/bash

set -e

# 增强日志输出函数（带颜色）— 始终写到 stderr，避免污染函数返回值
function log {
    local level=$1
    local message=$2
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    case $level in
        INFO)  echo -e "\033[32m[${timestamp}] [${level}] ${message}\033[0m" >&2 ;;
        WARN)  echo -e "\033[33m[${timestamp}] [${level}] ${message}\033[0m" >&2 ;;
        ERROR) echo -e "\033[31m[${timestamp}] [${level}] ${message}\033[0m" >&2 ;;
        *)     echo "[${timestamp}] [${level}] ${message}" >&2 ;;
    esac
}
# 错误处理函数（增强版）
function handle_error {
    local message=$1
    local line_number=$(caller 0 | awk '{print $1}')
    log "ERROR" "Line ${line_number}: ${message}"
    log "ERROR" "Working directory: $(pwd)"
    log "ERROR" "Failed command: ${BASH_COMMAND}"
    log "ERROR" "Environment variables:"
    env | grep -E "BUILD_DIR|OUTPUT_DIR|LIBICAL_SRC_DIR"
    exit 1
}

trap 'handle_error "Script failed unexpectedly"' ERR

# 检查运行环境
if [[ "$(uname)" != "Darwin" ]]; then
    handle_error "This script requires macOS to run"
fi

# 检查依赖工具
declare -a REQUIRED_CMDS=(cmake xcodebuild lipo xcrun git)
for cmd in "${REQUIRED_CMDS[@]}"; do
    if ! command -v $cmd &> /dev/null; then
        handle_error "Missing required command: $cmd"
    fi
done

# ── 路径辅助函数 ──────────────────────────────────────────────────────────────
function get_realpath {
    if readlink -f "$1" &> /dev/null; then
        readlink -f "$1"
    else
        # macOS 默认 BSD readlink 不支持 -f，手动拼接
        local path=$(cd "$(dirname "$1")" && pwd -P)/$(basename "$1")
        echo "$path"
    fi
}

# ── 源码目录 & 构建目录 ───────────────────────────────────────────────────────
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
LIBICAL_REPO="https://github.com/libical/libical.git"
LIBICAL_SRC_DIR="${SCRIPT_DIR}/libical_src"
BUILD_DIR="${SCRIPT_DIR}/build"
OUTPUT_DIR="${SCRIPT_DIR}/output"

# ── 自动克隆 / 更新 libical 源码 ─────────────────────────────────────────────
if [[ -d "${LIBICAL_SRC_DIR}/.git" ]]; then
    log "INFO" "libical source already exists, pulling latest changes..."
    git -C "${LIBICAL_SRC_DIR}" fetch --tags --prune || handle_error "git fetch failed"
    # 切换到最新 tag（稳定版本）
    LATEST_TAG=$(git -C "${LIBICAL_SRC_DIR}" tag --sort=-v:refname | grep -E '^v?[0-9]+\.[0-9]+' | head -n 1)
    if [[ -n "${LATEST_TAG}" ]]; then
        log "INFO" "Checking out latest tag: ${LATEST_TAG}"
        git -C "${LIBICAL_SRC_DIR}" checkout "${LATEST_TAG}" || handle_error "git checkout ${LATEST_TAG} failed"
    else
        log "WARN" "No release tag found, staying on current branch"
    fi
else
    log "INFO" "Cloning libical from ${LIBICAL_REPO}..."
    git clone --depth 1 "${LIBICAL_REPO}" "${LIBICAL_SRC_DIR}" || handle_error "git clone failed"
    # 获取所有 tags（shallow clone 默认不含 tags）
    git -C "${LIBICAL_SRC_DIR}" fetch --tags --unshallow 2>/dev/null || \
    git -C "${LIBICAL_SRC_DIR}" fetch --tags || true
    LATEST_TAG=$(git -C "${LIBICAL_SRC_DIR}" tag --sort=-v:refname | grep -E '^v?[0-9]+\.[0-9]+' | head -n 1)
    if [[ -n "${LATEST_TAG}" ]]; then
        log "INFO" "Checking out latest tag: ${LATEST_TAG}"
        git -C "${LIBICAL_SRC_DIR}" checkout "${LATEST_TAG}" || handle_error "git checkout ${LATEST_TAG} failed"
    fi
fi

log "INFO" "libical source directory: ${LIBICAL_SRC_DIR}"
FRAMEWORK_NAME="libical"
XCFRAMEWORK_PATH="${OUTPUT_DIR}/${FRAMEWORK_NAME}.xcframework"
BUILD_TYPE="Release"

# ── Deployment Targets ──────────────────────────────────────────────────────
DEPLOYMENT_TARGET_MACOS="10.15"
DEPLOYMENT_TARGET_IOS="13.0"
DEPLOYMENT_TARGET_TVOS="13.0"
DEPLOYMENT_TARGET_WATCHOS="6.0"
# ────────────────────────────────────────────────────────────────────────────

# 清理历史构建
# 清理历史构建
log "INFO" "Cleaning previous builds..."
# 使用 || true 避免目录被占用时 rm 失败触发 set -e
if [[ -d "${BUILD_DIR}" ]]; then
    rm -rf "${BUILD_DIR}" || { log "WARN" "rm failed, retrying after 2s..."; sleep 2; rm -rf "${BUILD_DIR}"; }
fi
if [[ -d "${OUTPUT_DIR}" ]]; then
    rm -rf "${OUTPUT_DIR}" || { log "WARN" "rm failed, retrying after 2s..."; sleep 2; rm -rf "${OUTPUT_DIR}"; }
fi
mkdir -p "${BUILD_DIR}" "${OUTPUT_DIR}"
# 目录创建函数
function create_dir {
    local dir=$1
    mkdir -p "${dir}" || handle_error "Failed to create directory: ${dir}"
    log "INFO" "Created directory: ${dir}"
}

# 安全文件复制函数
function safe_copy {
    local src=$1
    local dest=$2

    if [[ ! -e "${src}" ]]; then
        handle_error "Copy source not found: ${src}"
    fi

    log "INFO" "Copying: ${src} -> ${dest}"
    if [[ -d "${src}" ]]; then
        cp -R "${src}/"* "${dest}" || handle_error "Failed to copy directory"
    else
        cp "${src}" "${dest}" || handle_error "Failed to copy file"
    fi
}

# ── Framework 构建函数 ────────────────────────────────────────────────────────
# 参数：
#   $1  framework_dir   目标 .framework 路径
#   $2  lib_path        静态库 .a 路径
#   $3  headers_dir     头文件目录
#   $4  platform        平台标识（见 case 分支）
function create_framework {
    local framework_dir=$1
    local lib_path=$2
    local headers_dir=$3
    local platform=$4

    create_dir "${framework_dir}/Headers"
    create_dir "${framework_dir}/Modules"

    # 复制静态库
    if [[ ! -f "${lib_path}" ]]; then
        handle_error "Static library not found: ${lib_path}"
    fi
    safe_copy "${lib_path}" "${framework_dir}/${FRAMEWORK_NAME}"

    # 复制头文件
    if [[ ! -d "${headers_dir}" ]]; then
        handle_error "Headers directory not found: ${headers_dir}"
    fi
    safe_copy "${headers_dir}" "${framework_dir}/Headers"

    # 生成伞头文件
    # 注意：framework 内头文件已平铺在 Headers/ 下，直接 include 即可
    local umbrella_header="${framework_dir}/Headers/${FRAMEWORK_NAME}.h"
    cat > "${umbrella_header}" <<'UMBRELLA_EOF'
#ifndef LIBICAL_UMBRELLA_H
#define LIBICAL_UMBRELLA_H

#include "ical.h"
#include "icalss.h"
#include "icalvcal.h"
#include "vcard.h"

#endif /* LIBICAL_UMBRELLA_H */
UMBRELLA_EOF

    # 生成模块映射
    # umbrella header 路径相对于 framework bundle 根目录
    cat > "${framework_dir}/Modules/module.modulemap" <<EOF
framework module ${FRAMEWORK_NAME} {
    umbrella header "${FRAMEWORK_NAME}.h"
    export *
    module * { export * }
}
EOF

    # 生成 Info.plist（根据平台类型设置参数）
    log "INFO" "Generating Info.plist for ${platform}"
    local PLATFORM_NAME
    local MIN_OS_VERSION

    case "$platform" in
        iphoneos)
            PLATFORM_NAME="iPhoneOS"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_IOS}"
            ;;
        iphonesimulator)
            PLATFORM_NAME="iPhoneSimulator"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_IOS}"
            ;;
        macos)
            PLATFORM_NAME="MacOSX"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_MACOS}"
            ;;
        appletvos)
            PLATFORM_NAME="AppleTVOS"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_TVOS}"
            ;;
        appletvsimulator)
            PLATFORM_NAME="AppleTVSimulator"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_TVOS}"
            ;;
        watchos)
            PLATFORM_NAME="WatchOS"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_WATCHOS}"
            ;;
        watchsimulator)
            PLATFORM_NAME="WatchSimulator"
            MIN_OS_VERSION="${DEPLOYMENT_TARGET_WATCHOS}"
            ;;
        *) handle_error "Unsupported platform: $platform" ;;
    esac

    cat > "${framework_dir}/Info.plist" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
    <key>CFBundleDevelopmentRegion</key>
    <string>en</string>
    <key>CFBundleExecutable</key>
    <string>${FRAMEWORK_NAME}</string>
    <key>CFBundleIdentifier</key>
    <string>org.libical.${FRAMEWORK_NAME}</string>
    <key>CFBundleInfoDictionaryVersion</key>
    <string>6.0</string>
    <key>CFBundleName</key>
    <string>${FRAMEWORK_NAME}</string>
    <key>CFBundlePackageType</key>
    <string>FMWK</string>
    <key>CFBundleShortVersionString</key>
    <string>1.0.0</string>
    <key>CFBundleVersion</key>
    <string>1</string>
    <key>CFBundleSupportedPlatforms</key>
    <array>
        <string>${PLATFORM_NAME}</string>
    </array>
    <key>MinimumOSVersion</key>
    <string>${MIN_OS_VERSION}</string>
</dict>
</plist>
EOF
}

# ── 构建单个架构 ──────────────────────────────────────────────────────────────
# 参数：
#   $1  arch              目标架构（arm64 / x86_64 / arm64_32）
#   $2  platform          平台标识（iphoneos / iphonesimulator / macos /
#                          appletvos / appletvsimulator / watchos / watchsimulator）
#   $3  sdk               xcrun SDK 名称（iphoneos / iphonesimulator / macosx /
#                          appletvos / appletvsimulator / watchos / watchsimulator）
#   $4  deployment_target 最低部署版本
function build_arch {
    local arch=$1
    local platform=$2
    local sdk=$3
    local deployment_target=$4

    log "INFO" "Building for ${arch} (${platform})..."

    local build_dir="${BUILD_DIR}/${platform}_${arch}"
    create_dir "${build_dir}"

    cd "${build_dir}" || handle_error "Failed to enter build directory"

    # 获取 SDK 路径
    local sdk_path
    sdk_path=$(xcrun --sdk "${sdk}" --show-sdk-path) || handle_error "Failed to get ${sdk} SDK path"

    # CMake 配置
    local cmake_args=(
        -G "Unix Makefiles"
        -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
        -DCMAKE_OSX_SYSROOT="${sdk_path}"
        -DCMAKE_OSX_ARCHITECTURES="${arch}"
        -DCMAKE_OSX_DEPLOYMENT_TARGET="${deployment_target}"
        -DCMAKE_INSTALL_PREFIX="${OUTPUT_DIR}/${platform}_${arch}"
        -DBUILD_SHARED_LIBS=OFF
        -DLIBICAL_STATIC=True
        -DLIBICAL_JAVA_BINDINGS=False
        -DLIBICAL_GOBJECT_INTROSPECTION=False
        -DLIBICAL_GLIB=False
        -DLIBICAL_BUILD_VZIC=False
        -DLIBICAL_BUILD_DOCS=False
        -DLIBICAL_CXX_BINDINGS=False
        -DLIBICAL_BUILD_TESTING=False
        -DLIBICAL_BUILD_EXAMPLES=False
    )
    log "INFO" "Configuring CMake for ${arch} / ${platform}"
    cmake "${LIBICAL_SRC_DIR}" "${cmake_args[@]}" || handle_error "CMake configuration failed for ${arch}/${platform}"

    log "INFO" "Building for ${arch} / ${platform} (using $(sysctl -n hw.ncpu) threads)"
    make -j$(sysctl -n hw.ncpu) || handle_error "Build failed for ${arch}/${platform}"

    log "INFO" "Installing artifacts for ${arch} / ${platform}"
    make install || handle_error "Install failed for ${arch}/${platform}"

    # 验证头文件
    local header_file="${OUTPUT_DIR}/${platform}_${arch}/include/${FRAMEWORK_NAME}/ical.h"
    if [[ ! -f "${header_file}" ]]; then
        handle_error "Header file missing after install: ${header_file}"
    fi

    # 创建 framework
    local framework_dir="${OUTPUT_DIR}/${platform}.${arch}/${FRAMEWORK_NAME}.framework"
    create_framework \
        "${framework_dir}" \
        "${OUTPUT_DIR}/${platform}_${arch}/lib/${FRAMEWORK_NAME}.a" \
        "${OUTPUT_DIR}/${platform}_${arch}/include/${FRAMEWORK_NAME}" \
        "${platform}"
}

# ── 合并多架构静态库并生成 framework ─────────────────────────────────────────
# 参数：
#   $1  merged_tag   合并产物的目录标签（如 simulator_merged）
#   $2  platform     平台标识（传给 create_framework）
#   $3+ lib_paths    需要合并的 .a 文件路径列表（至少一个）
#
# 约定：头文件取第一个 lib_path 对应的 install 目录
function merge_and_create_framework {
    local merged_tag=$1
    local platform=$2
    shift 2
    local lib_paths=("$@")

    log "INFO" "Merging libraries for ${platform} -> ${merged_tag}..."

    local merged_dir="${OUTPUT_DIR}/${merged_tag}"
    create_dir "${merged_dir}/lib"

    lipo -create "${lib_paths[@]}" -output "${merged_dir}/lib/${FRAMEWORK_NAME}.a" || \
        handle_error "Failed to merge libraries for ${platform}"

    # 从第一个库路径推导头文件目录
    # lib_paths[0] 形如 .../output/<platform>_<arch>/lib/libical.a
    local first_lib="${lib_paths[0]}"
    local install_prefix
    install_prefix=$(dirname "$(dirname "${first_lib}")")   # 去掉 /lib/libical.a
    local header_src="${install_prefix}/include/${FRAMEWORK_NAME}"

    local merged_header_dir="${merged_dir}/include/${FRAMEWORK_NAME}"
    create_dir "${merged_header_dir}"
    safe_copy "${header_src}" "${merged_header_dir}"

    local framework_dir="${OUTPUT_DIR}/${merged_tag}/${FRAMEWORK_NAME}.framework"
    create_framework \
        "${framework_dir}" \
        "${merged_dir}/lib/${FRAMEWORK_NAME}.a" \
        "${merged_header_dir}" \
        "${platform}"

    # 将 framework 路径输出给调用方
    echo "${framework_dir}"
}

# ════════════════════════════════════════════════════════════════════════════
# 主构建流程
# ════════════════════════════════════════════════════════════════════════════
log "INFO" "Starting build process..."

# ── iOS ──────────────────────────────────────────────────────────────────────
log "INFO" "=== iOS ==="
build_arch "arm64"  "iphoneos"        "iphoneos"        "${DEPLOYMENT_TARGET_IOS}"
build_arch "x86_64" "iphonesimulator" "iphonesimulator" "${DEPLOYMENT_TARGET_IOS}"
build_arch "arm64"  "iphonesimulator" "iphonesimulator" "${DEPLOYMENT_TARGET_IOS}"

# ── macOS ─────────────────────────────────────────────────────────────────────
log "INFO" "=== macOS ==="
build_arch "x86_64" "macos" "macosx" "${DEPLOYMENT_TARGET_MACOS}"
build_arch "arm64"  "macos" "macosx" "${DEPLOYMENT_TARGET_MACOS}"

# ── tvOS ──────────────────────────────────────────────────────────────────────
log "INFO" "=== tvOS ==="
build_arch "arm64"  "appletvos"        "appletvos"        "${DEPLOYMENT_TARGET_TVOS}"
build_arch "x86_64" "appletvsimulator" "appletvsimulator" "${DEPLOYMENT_TARGET_TVOS}"
build_arch "arm64"  "appletvsimulator" "appletvsimulator" "${DEPLOYMENT_TARGET_TVOS}"

# ── watchOS ───────────────────────────────────────────────────────────────────
log "INFO" "=== watchOS ==="
build_arch "arm64"    "watchos"        "watchos"        "${DEPLOYMENT_TARGET_WATCHOS}"
build_arch "arm64_32" "watchos"        "watchos"        "${DEPLOYMENT_TARGET_WATCHOS}"
build_arch "x86_64"   "watchsimulator" "watchsimulator" "${DEPLOYMENT_TARGET_WATCHOS}"
build_arch "arm64"    "watchsimulator" "watchsimulator" "${DEPLOYMENT_TARGET_WATCHOS}"

# ════════════════════════════════════════════════════════════════════════════
# 合并多架构库
# ════════════════════════════════════════════════════════════════════════════

# ── iOS Simulator ─────────────────────────────────────────────────────────────
log "INFO" "Merging iOS Simulator libraries..."
IOS_SIM_FW=$(merge_and_create_framework \
    "iphonesimulator_merged" \
    "iphonesimulator" \
    "${OUTPUT_DIR}/iphonesimulator_x86_64/lib/${FRAMEWORK_NAME}.a" \
    "${OUTPUT_DIR}/iphonesimulator_arm64/lib/${FRAMEWORK_NAME}.a")

# ── macOS ─────────────────────────────────────────────────────────────────────
log "INFO" "Merging macOS libraries..."
MACOS_FW=$(merge_and_create_framework \
    "macos_merged" \
    "macos" \
    "${OUTPUT_DIR}/macos_x86_64/lib/${FRAMEWORK_NAME}.a" \
    "${OUTPUT_DIR}/macos_arm64/lib/${FRAMEWORK_NAME}.a")

# ── tvOS Simulator ────────────────────────────────────────────────────────────
log "INFO" "Merging tvOS Simulator libraries..."
TVOS_SIM_FW=$(merge_and_create_framework \
    "appletvsimulator_merged" \
    "appletvsimulator" \
    "${OUTPUT_DIR}/appletvsimulator_x86_64/lib/${FRAMEWORK_NAME}.a" \
    "${OUTPUT_DIR}/appletvsimulator_arm64/lib/${FRAMEWORK_NAME}.a")

# ── watchOS Device（arm64 + arm64_32）────────────────────────────────────────
log "INFO" "Merging watchOS device libraries..."
WATCHOS_FW=$(merge_and_create_framework \
    "watchos_merged" \
    "watchos" \
    "${OUTPUT_DIR}/watchos_arm64/lib/${FRAMEWORK_NAME}.a" \
    "${OUTPUT_DIR}/watchos_arm64_32/lib/${FRAMEWORK_NAME}.a")

# ── watchOS Simulator ─────────────────────────────────────────────────────────
log "INFO" "Merging watchOS Simulator libraries..."
WATCHOS_SIM_FW=$(merge_and_create_framework \
    "watchsimulator_merged" \
    "watchsimulator" \
    "${OUTPUT_DIR}/watchsimulator_x86_64/lib/${FRAMEWORK_NAME}.a" \
    "${OUTPUT_DIR}/watchsimulator_arm64/lib/${FRAMEWORK_NAME}.a")

# ── iOS Device framework 路径（单架构，无需合并）─────────────────────────────
IOS_FW="${OUTPUT_DIR}/iphoneos.arm64/${FRAMEWORK_NAME}.framework"

# ── tvOS Device framework 路径（单架构，无需合并）────────────────────────────
TVOS_FW="${OUTPUT_DIR}/appletvos.arm64/${FRAMEWORK_NAME}.framework"

# ════════════════════════════════════════════════════════════════════════════
# 创建 XCFramework
# ════════════════════════════════════════════════════════════════════════════
log "INFO" "Creating XCFramework..."
xcodebuild -create-xcframework \
    -framework "${IOS_FW}" \
    -framework "${IOS_SIM_FW}" \
    -framework "${MACOS_FW}" \
    -framework "${TVOS_FW}" \
    -framework "${TVOS_SIM_FW}" \
    -framework "${WATCHOS_FW}" \
    -framework "${WATCHOS_SIM_FW}" \
    -output "${XCFRAMEWORK_PATH}" || handle_error "Failed to create XCFramework"

# 验证最终产物
if [[ ! -d "${XCFRAMEWORK_PATH}" ]]; then
    handle_error "XCFramework not generated at expected path: ${XCFRAMEWORK_PATH}"
fi

log "INFO" "Build successful! XCFramework location:"
echo -e "\033[34m${XCFRAMEWORK_PATH}\033[0m"

# 打开输出目录
open "${OUTPUT_DIR}"

# 清理临时文件
log "INFO" "Cleaning up temporary files..."
if [[ -d "${BUILD_DIR}" ]]; then
    rm -rf "${BUILD_DIR}"
    log "INFO" "Removed build directory: ${BUILD_DIR}"
fi

# 清理除 libical.xcframework 之外的其他文件
find "${OUTPUT_DIR}" -mindepth 1 -maxdepth 1 ! -name "${FRAMEWORK_NAME}.xcframework" -exec rm -rf {} +
log "INFO" "Cleaned up output directory, only ${FRAMEWORK_NAME}.xcframework remains."

log "INFO" "Cleanup complete!"
