# libical XCFramework

将 [libical](https://github.com/libical/libical) 自动构建为支持多平台的 Apple XCFramework 静态库。

---

## 特性

- 自动从 GitHub 克隆 / 更新 libical 源码，并切换到最新稳定 tag
- 支持以下全部 Apple 平台：

| 平台 | 架构 | Deployment Target |
|------|------|-------------------|
| iOS Device | arm64 | 13.0 |
| iOS Simulator | x86_64 + arm64 | 13.0 |
| macOS | x86_64 + arm64 | 10.15 |
| tvOS Device | arm64 | 13.0 |
| tvOS Simulator | x86_64 + arm64 | 13.0 |
| watchOS Device | arm64 + arm64_32 | 6.0 |
| watchOS Simulator | x86_64 + arm64 | 6.0 |

- 构建产物为**静态库** XCFramework，无需额外依赖
- 构建完成后自动清理中间产物，仅保留 `output/libical.xcframework`

---

## 依赖

运行脚本前请确保以下工具已安装：

| 工具 | 说明 |
|------|------|
| `cmake` | 构建系统，推荐通过 [Homebrew](https://brew.sh) 安装：`brew install cmake` |
| `git` | 用于克隆 / 更新 libical 源码 |
| `xcodebuild` | Xcode 命令行工具，随 Xcode 安装 |
| `lipo` | 多架构库合并工具，随 Xcode 安装 |
| `xcrun` | SDK 路径查询工具，随 Xcode 安装 |
| `perl` | libical 构建系统依赖，macOS 自带 |

安装 Xcode 命令行工具：

```bash
xcode-select --install
```

安装 cmake（如未安装）：

```bash
brew install cmake
```

---

## 使用方法

### 构建 XCFramework

```bash
chmod +x build_libical_xcframework.sh
./build_libical_xcframework.sh
```

构建完成后，产物位于：

```
output/libical.xcframework
```

### 重新构建

脚本每次运行都会：
1. 拉取 libical 最新 tag 并切换
2. 清空上次的 `build/` 和 `output/` 目录
3. 重新编译所有平台
4. 生成新的 XCFramework

直接再次运行脚本即可：

```bash
./build_libical_xcframework.sh
```

---

## 目录结构

```
.
├── build_libical_xcframework.sh   # 构建脚本
├── libical_src/                   # 自动克隆的 libical 源码（gitignore）
├── build/                         # 构建中间产物（gitignore，构建后自动删除）
├── output/
│   └── libical.xcframework        # 最终产物
├── Sources/                       # Swift Package 源码目录
├── Tests/                         # Swift Package 测试目录
└── Package.swift                  # Swift Package 描述文件
```

---

## 集成到项目

### Swift Package Manager

在 `Package.swift` 中添加本地 XCFramework 依赖：

```swift
.binaryTarget(
    name: "libical",
    path: "output/libical.xcframework"
)
```

### Xcode 手动集成

1. 将 `output/libical.xcframework` 拖入 Xcode 项目
2. 在 **Target → General → Frameworks, Libraries, and Embedded Content** 中确认已添加
3. 将 **Embed** 设置为 **Do Not Embed**（静态库无需嵌入）

### 头文件引用

```c
#include <libical/ical.h>
```

---

## 构建参数说明

脚本中的关键 CMake 参数：

| 参数 | 值 | 说明 |
|------|----|------|
| `BUILD_SHARED_LIBS` | `OFF` | 禁用动态库 |
| `LIBICAL_STATIC` | `True` | 启用静态库构建 |
| `LIBICAL_GLIB` | `False` | 禁用 GLib 绑定（需要 pkg-config） |
| `LIBICAL_JAVA_BINDINGS` | `False` | 禁用 Java 绑定（需要 JDK） |
| `LIBICAL_CXX_BINDINGS` | `False` | 禁用 C++ 绑定 |
| `LIBICAL_GOBJECT_INTROSPECTION` | `False` | 禁用 GObject 内省 |
| `LIBICAL_BUILD_VZIC` | `False` | 禁用 vzic 工具构建 |
| `LIBICAL_BUILD_DOCS` | `False` | 禁用文档生成 |
| `LIBICAL_BUILD_TESTING` | `False` | 禁用测试构建 |
| `LIBICAL_BUILD_EXAMPLES` | `False` | 禁用示例构建 |

如需修改 Deployment Target，编辑脚本中的以下变量：

```bash
DEPLOYMENT_TARGET_MACOS="10.15"
DEPLOYMENT_TARGET_IOS="13.0"
DEPLOYMENT_TARGET_TVOS="13.0"
DEPLOYMENT_TARGET_WATCHOS="6.0"
```

---

## 许可证

本仓库的构建脚本遵循 [MIT License](LICENSE)。

libical 本身遵循 **LGPL 2.1 / MPL 2.0** 双重许可证，详见 [libical 官方仓库](https://github.com/libical/libical)。
