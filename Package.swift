// swift-tools-version: 6.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "libical",
    platforms: [
        .iOS(.v13),
        .macOS(.v10_15),
        .tvOS(.v13),
        .watchOS(.v6),
    ],
    products: [
        // libICAL Swift 封装层（对外唯一暴露的产品）
        .library(
            name: "libICAL",
            targets: ["libICAL"]
        ),
    ],
    targets: [
        // libical XCFramework（由 build_libical_apple_all_xcframework.sh 构建生成）
        .binaryTarget(
            name: "libical",
            path: "./libical-apple-build/libical.xcframework"
        ),
        // libICAL Swift 封装层
        .target(
            name: "libICAL",
            dependencies: ["libical"],
            path: "Sources/libICAL",
            swiftSettings: [
                .swiftLanguageMode(.v5)
            ]
        ),
        .testTarget(
            name: "libicalTests",
            dependencies: ["libICAL"],
            path: "Tests/libicalTests"
        ),
    ]
)
