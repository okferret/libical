#!/bin/bash

set -e

# 增强日志输出函数（带颜色）
function log {
    local level=$1
    local message=$2
    local timestamp=$(date +"%Y-%m-%d %H:%M:%S")
    case $level in
        INFO)  echo -e "\033[32m[${timestamp}] [${level}] ${message}\033[0m" ;;
        ERROR) echo -e "\033[31m[${timestamp}] [${level}] ${message}\033[0m" ;;
        *)     echo "[${timestamp}] [${level}] ${message}" ;;
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
declare -a REQUIRED_CMDS=(cmake xcodebuild lipo)
for cmd in "${REQUIRED_CMDS[@]}"; do
    if ! command -v $cmd &> /dev/null; then
        handle_error "Missing required command: $cmd"
    fi
done

# 定义路径（使用 readlink -f 替代 realpath 增强兼容性）
function get_realpath {
    if readlink -f "$1" &> /dev/null; then
        readlink -f "$1"
    else
        # 处理不支持 -f 选项的情况
        local path=$(cd "$(dirname "$1")" && pwd -P)/$(basename "$1")
        echo "$path"
    fi
}

# 获取包含 libical 的实际目录
LIBICAL_DIR=$(find "$(get_realpath .)" -type d -name "libical-*" | head -n 1)
if [ -z "$LIBICAL_DIR" ]; then
    handle_error "未找到以 libical- 开头的目录。"
fi

LIBICAL_SRC_DIR=$(get_realpath "$LIBICAL_DIR")
BUILD_DIR="${LIBICAL_SRC_DIR}/../build"
OUTPUT_DIR="${LIBICAL_SRC_DIR}/../output"
FRAMEWORK_NAME="libical"
XCFRAMEWORK_PATH="${OUTPUT_DIR}/${FRAMEWORK_NAME}.xcframework"
BUILD_TYPE="Release"
DEPLOYMENT_TARGET_MACOS="10.15"
DEPLOYMENT_TARGET_IOS="13.0"

# 清理历史构建
log "INFO" "Cleaning previous builds..."
if [[ -d "${BUILD_DIR}" ]]; then
    rm -rf "${BUILD_DIR}"
fi
if [[ -d "${OUTPUT_DIR}" ]]; then
    rm -rf "${OUTPUT_DIR}"
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

# Framework构建函数
function create_framework {
    local framework_dir=$1
    local lib_path=$2
    local headers_dir=$3
    
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
    local umbrella_header="${framework_dir}/Headers/${FRAMEWORK_NAME}.h"
    cat > "${umbrella_header}" <<EOF
#import <Foundation/Foundation.h>

FOUNDATION_EXPORT double ${FRAMEWORK_NAME}VersionNumber;
FOUNDATION_EXPORT const unsigned char ${FRAMEWORK_NAME}VersionString[];

#import "${FRAMEWORK_NAME}/ical.h"
EOF

    # 生成模块映射
    cat > "${framework_dir}/Modules/module.modulemap" <<EOF
module ${FRAMEWORK_NAME} {
    umbrella header "Headers/${FRAMEWORK_NAME}.h"
    export *
    link "${FRAMEWORK_NAME}"
}
EOF
}

# 构建单个架构
function build_arch {
    local arch=$1
    local platform=$2
    local sdk=$3
    local deployment_target=$4

    log "INFO" "Building for ${arch} (${platform})..."
    
    local build_dir="${BUILD_DIR}/${platform}_${arch}"
    create_dir "${build_dir}"
    
    cd "${build_dir}" || handle_error "Failed to enter build directory"

    # 获取SDK路径
    local sdk_path
    sdk_path=$(xcrun --sdk "${sdk}" --show-sdk-path) || handle_error "Failed to get ${sdk} SDK path"

    # CMake配置
    local cmake_args=(
        -G "Unix Makefiles"
        -DCMAKE_BUILD_TYPE="${BUILD_TYPE}"
        -DCMAKE_OSX_SYSROOT="${sdk_path}"
        -DCMAKE_OSX_ARCHITECTURES="${arch}"
        -DCMAKE_OSX_DEPLOYMENT_TARGET="${deployment_target}"
        -DCMAKE_INSTALL_PREFIX="${OUTPUT_DIR}/${platform}_${arch}"
        -DICAL_GLIB=OFF
        -DBUILD_SHARED_LIBS=OFF
    )

    log "INFO" "Configuring CMake for ${arch}"
    cmake "${LIBICAL_SRC_DIR}" "${cmake_args[@]}" || handle_error "CMake configuration failed"

    log "INFO" "Building for ${arch} (using $(sysctl -n hw.ncpu) threads)"
    make -j$(sysctl -n hw.ncpu) || handle_error "Build failed for ${arch}"

    log "INFO" "Installing artifacts for ${arch}"
    make install || handle_error "Install failed for ${arch}"

    # 验证头文件
    local header_file="${OUTPUT_DIR}/${platform}_${arch}/include/${FRAMEWORK_NAME}/ical.h"
    if [[ ! -f "${header_file}" ]]; then
        handle_error "Header file missing after install: ${header_file}"
    fi

    # 创建framework
    local framework_dir="${OUTPUT_DIR}/${platform}.${arch}/${FRAMEWORK_NAME}.framework"
    create_framework \
        "${framework_dir}" \
        "${OUTPUT_DIR}/${platform}_${arch}/lib/${FRAMEWORK_NAME}.a" \
        "${OUTPUT_DIR}/${platform}_${arch}/include/${FRAMEWORK_NAME}"
}

# 主构建流程
log "INFO" "Starting build process..."

# 构建 iOS 架构
build_arch "arm64" "iphoneos" "iphoneos" "${DEPLOYMENT_TARGET_IOS}"
build_arch "x86_64" "iphonesimulator" "iphonesimulator" "${DEPLOYMENT_TARGET_IOS}"
build_arch "arm64" "iphonesimulator" "iphonesimulator" "${DEPLOYMENT_TARGET_IOS}"

# 构建 macOS 架构
build_arch "x86_64" "macos" "macosx" "${DEPLOYMENT_TARGET_MACOS}"
build_arch "arm64" "macos" "macosx" "${DEPLOYMENT_TARGET_MACOS}"

# 合并模拟器库
log "INFO" "Merging simulator libraries..."
SIMULATOR_LIBS=(
    "${OUTPUT_DIR}/iphonesimulator_x86_64/lib/${FRAMEWORK_NAME}.a"
    "${OUTPUT_DIR}/iphonesimulator_arm64/lib/${FRAMEWORK_NAME}.a"
)
MERGED_SIMULATOR_DIR="${OUTPUT_DIR}/simulator_merged"
create_dir "${MERGED_SIMULATOR_DIR}/lib"

lipo -create "${SIMULATOR_LIBS[@]}" -output "${MERGED_SIMULATOR_DIR}/lib/${FRAMEWORK_NAME}.a" || {
    handle_error "Failed to merge simulator libraries"
}

# 复制头文件（使用 arm64 的头文件）
SIMULATOR_HEADER_SRC="${OUTPUT_DIR}/iphonesimulator_arm64/include/${FRAMEWORK_NAME}"
MERGED_HEADER_DIR="${MERGED_SIMULATOR_DIR}/include/${FRAMEWORK_NAME}"
create_dir "${MERGED_HEADER_DIR}"
safe_copy "${SIMULATOR_HEADER_SRC}" "${MERGED_HEADER_DIR}"

# 创建合并后的framework
SIMULATOR_FRAMEWORK_DIR="${OUTPUT_DIR}/iphonesimulator.merged/${FRAMEWORK_NAME}.framework"
create_framework \
    "${SIMULATOR_FRAMEWORK_DIR}" \
    "${MERGED_SIMULATOR_DIR}/lib/${FRAMEWORK_NAME}.a" \
    "${MERGED_HEADER_DIR}"

# 合并 macOS 库
log "INFO" "Merging macOS libraries..."
MACOS_LIBS=(
    "${OUTPUT_DIR}/macos_x86_64/lib/${FRAMEWORK_NAME}.a"
    "${OUTPUT_DIR}/macos_arm64/lib/${FRAMEWORK_NAME}.a"
)
MERGED_MACOS_DIR="${OUTPUT_DIR}/macos_merged"
create_dir "${MERGED_MACOS_DIR}/lib"

lipo -create "${MACOS_LIBS[@]}" -output "${MERGED_MACOS_DIR}/lib/${FRAMEWORK_NAME}.a" || {
    handle_error "Failed to merge macOS libraries"
}

# 复制 macOS 头文件（使用 arm64 的头文件）
MACOS_HEADER_SRC="${OUTPUT_DIR}/macos_arm64/include/${FRAMEWORK_NAME}"
MERGED_MACOS_HEADER_DIR="${MERGED_MACOS_DIR}/include/${FRAMEWORK_NAME}"
create_dir "${MERGED_MACOS_HEADER_DIR}"
safe_copy "${MACOS_HEADER_SRC}" "${MERGED_MACOS_HEADER_DIR}"

# 创建合并后的 macOS framework
MACOS_FRAMEWORK_DIR="${OUTPUT_DIR}/macos.merged/${FRAMEWORK_NAME}.framework"
create_framework \
    "${MACOS_FRAMEWORK_DIR}" \
    "${MERGED_MACOS_DIR}/lib/${FRAMEWORK_NAME}.a" \
    "${MERGED_MACOS_HEADER_DIR}"

# 创建 XCFramework
log "INFO" "Creating XCFramework..."
xcodebuild -create-xcframework \
    -framework "${OUTPUT_DIR}/iphoneos.arm64/${FRAMEWORK_NAME}.framework" \
    -framework "${SIMULATOR_FRAMEWORK_DIR}" \
    -framework "${MACOS_FRAMEWORK_DIR}" \
    -output "${XCFRAMEWORK_PATH}" || handle_error "Failed to create XCFramework"

# 验证最终产物
if [[ ! -d "${XCFRAMEWORK_PATH}" ]]; then
    handle_error "XCFramework not generated at expected path: ${XCFRAMEWORK_PATH}"
fi

log "INFO" "Build successful! XCFramework location:"
echo -e "\033[34m${XCFRAMEWORK_PATH}\033[0m"

# 打开输出目录
open "${OUTPUT_DIR}"
