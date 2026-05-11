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
        .library(
            name: "libical",
            targets: ["libical"]
        ),
    ],
    targets: [
        // libical XCFramework（由 build_libical_xcframework.sh 构建生成）
        .binaryTarget(
            name: "libical",
            path: "./output/libical.xcframework"
        ),
        .testTarget(
            name: "libicalTests",
            dependencies: ["libical"]
        ),
    ]
)
