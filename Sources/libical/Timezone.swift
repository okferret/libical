// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Timezone

import libical

// MARK: - Timezone

/// iCalendar 时区类型，对应 C 的 `icaltimezone *`
///
/// 封装 libical 的时区操作，支持内置时区查询、时间转换和 UTC 偏移计算。
/// 通过 `borrowing` 初始化的实例不拥有底层指针（不负责释放），
/// 通过 `owning` 初始化的实例拥有底层指针（deinit 时释放）。
public final class Timezone: @unchecked Sendable {

    // MARK: Internal storage

    /// 底层 C 时区指针
    internal let cPointer: OpaquePointer
    /// 是否拥有底层指针的所有权（决定 deinit 时是否释放）
    private let owned: Bool

    // MARK: Initializers

    /// 借用外部指针创建（不拥有所有权，不负责释放）
    internal init(borrowing pointer: OpaquePointer) {
        self.cPointer = pointer
        self.owned = false
    }

    /// 接管指针所有权创建（deinit 时负责释放）
    internal init(owning pointer: OpaquePointer) {
        self.cPointer = pointer
        self.owned = true
    }

    /// 创建新的空时区对象
    /// - Returns: 成功返回新时区，内存分配失败返回 nil
    public init?() {
        guard let ptr = icaltimezone_new() else { return nil }
        self.cPointer = ptr
        self.owned = true
    }

    deinit {
        // 仅在拥有所有权时释放底层指针
        if owned {
            icaltimezone_free(cPointer, 1)
        }
    }

    // MARK: Built-in timezones

    /// UTC 时区（协调世界时）
    public static var utc: Timezone? {
        guard let ptr = icaltimezone_get_utc_timezone() else { return nil }
        return Timezone(borrowing: ptr)
    }

    /// 根据位置名称获取内置时区（如 "America/New_York"）
    /// - Parameter location: IANA 时区位置字符串
    /// - Returns: 对应的内置时区，未找到返回 nil
    public static func builtin(location: String) -> Timezone? {
        guard let ptr = icaltimezone_get_builtin_timezone(location) else { return nil }
        return Timezone(borrowing: ptr)
    }

    /// 根据 TZID 获取内置时区
    /// - Parameter tzid: 时区标识符字符串
    /// - Returns: 对应的内置时区，未找到返回 nil
    public static func builtin(tzid: String) -> Timezone? {
        guard let ptr = icaltimezone_get_builtin_timezone_from_tzid(tzid) else { return nil }
        return Timezone(borrowing: ptr)
    }

    /// 根据 UTC 偏移和时区名称获取内置时区
    /// - Parameters:
    ///   - utcOffset: UTC 偏移秒数
    ///   - tzname: 时区名称（如 "EST"）
    /// - Returns: 对应的内置时区，未找到返回 nil
    public static func builtin(utcOffset: Int, tzname: String) -> Timezone? {
        guard let ptr = icaltimezone_get_builtin_timezone_from_offset(Int32(utcOffset), tzname) else { return nil }
        return Timezone(borrowing: ptr)
    }

    /// 克隆当前时区，返回独立副本
    /// - Returns: 新的时区副本，内存分配失败返回 nil
    public func clone() -> Timezone? {
        guard let ptr = icaltimezone_copy(cPointer) else { return nil }
        return Timezone(owning: ptr)
    }

    // MARK: Properties

    /// 时区标识符（TZID），如 "America/New_York"
    public var tzid: String? {
        guard let ptr = icaltimezone_get_tzid(cPointer) else { return nil }
        return String(cString: ptr)
    }

    /// 时区位置名称，如 "America/New_York"
    public var location: String? {
        guard let ptr = icaltimezone_get_location(cPointer) else { return nil }
        return String(cString: ptr)
    }

    /// 时区名称字符串（可能包含标准时和夏令时名称，以 "/" 分隔）
    public var tznames: String? {
        guard let ptr = icaltimezone_get_tznames(cPointer) else { return nil }
        return String(cString: ptr)
    }

    /// 时区显示名称（优先使用 location，其次 tznames）
    public var displayName: String? {
        guard let ptr = icaltimezone_get_display_name(cPointer) else { return nil }
        return String(cString: ptr)
    }

    /// 时区所在地的纬度（度）
    public var latitude: Double {
        icaltimezone_get_latitude(cPointer)
    }

    /// 时区所在地的经度（度）
    public var longitude: Double {
        icaltimezone_get_longitude(cPointer)
    }

    // MARK: Component access

    /// 获取时区的 VTIMEZONE 组件（借用，不拥有所有权）
    public var component: Component? {
        guard let ptr = icaltimezone_get_component(cPointer) else { return nil }
        return Component(borrowing: ptr)
    }

    /// 设置时区的 VTIMEZONE 组件
    /// - Parameter component: 包含时区定义的 VTIMEZONE 组件
    /// - Returns: 设置成功返回 true，失败返回 false
    @discardableResult
    public func setComponent(_ component: Component) -> Bool {
        icaltimezone_set_component(cPointer, component.cPointer)
    }

    // MARK: Time conversion

    /// 将时间从一个时区转换到另一个时区（原地修改传入的 Time）
    /// - Parameters:
    ///   - time: 要转换的时间（inout，转换后原地更新）
    ///   - fromZone: 源时区
    ///   - toZone: 目标时区
    public static func convertTime(_ time: inout Time, from fromZone: Timezone, to toZone: Timezone) {
        icaltimezone_convert_time(&time.cValue, fromZone.cPointer, toZone.cPointer)
    }

    // MARK: UTC offset

    /// 获取指定本地时间对应的 UTC 偏移（秒）
    /// - Parameters:
    ///   - time: 本地时间
    ///   - isDaylight: 输出参数，是否为夏令时
    /// - Returns: UTC 偏移秒数（正数表示东区）
    public func utcOffset(for time: Time, isDaylight: inout Bool) -> Int {
        var daylight: Int32 = 0
        var t = time.cValue
        let offset = icaltimezone_get_utc_offset(cPointer, &t, &daylight)
        isDaylight = daylight != 0
        return Int(offset)
    }

    /// 获取指定 UTC 时间对应的 UTC 偏移（秒）
    /// - Parameters:
    ///   - time: UTC 时间
    ///   - isDaylight: 输出参数，是否为夏令时
    /// - Returns: UTC 偏移秒数（正数表示东区）
    public func utcOffset(forUTC time: Time, isDaylight: inout Bool) -> Int {
        var daylight: Int32 = 0
        var t = time.cValue
        let offset = icaltimezone_get_utc_offset_of_utc_time(cPointer, &t, &daylight)
        isDaylight = daylight != 0
        return Int(offset)
    }

    // MARK: VTIMEZONE utilities

    /// 从 VTIMEZONE 组件获取位置字符串
    /// - Parameter component: VTIMEZONE 组件
    /// - Returns: 位置字符串，未找到返回 nil
    public static func location(fromVTimezone component: Component) -> String? {
        guard let ptr = icaltimezone_get_location_from_vtimezone(component.cPointer) else { return nil }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 从 VTIMEZONE 组件获取时区名称字符串
    /// - Parameter component: VTIMEZONE 组件
    /// - Returns: 时区名称字符串，未找到返回 nil
    public static func tznames(fromVTimezone component: Component) -> String? {
        guard let ptr = icaltimezone_get_tznames_from_vtimezone(component.cPointer) else { return nil }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 展开 VTIMEZONE 组件到指定年份（预计算时区转换规则）
    /// - Parameters:
    ///   - component: VTIMEZONE 组件
    ///   - endYear: 展开到的目标年份
    public static func expandVTimezone(_ component: Component, endYear: Int) {
        icaltimezone_expand_vtimezone(component.cPointer, Int32(endYear), nil)
    }

    /// 截断 VTIMEZONE 组件到指定时间范围（减小数据量）
    /// - Parameters:
    ///   - vtz: VTIMEZONE 组件
    ///   - start: 起始时间
    ///   - end: 结束时间
    ///   - ms: 是否保留毫秒精度
    public static func truncateVTimezone(_ vtz: Component, start: Time, end: Time, ms: Bool = false) {
        icaltimezone_truncate_vtimezone(vtz.cPointer, start.cValue, end.cValue, ms)
    }

    // MARK: Global settings

    /// 是否使用 libical 内置时区数据（而非系统时区数据库）
    public static var useBuiltinTZData: Bool {
        get { icaltimezone_get_builtin_tzdata() }
        set { icaltimezone_set_builtin_tzdata(newValue) }
    }

    /// 系统时区数据库目录路径（只读）
    public static var systemZoneDirectory: String? {
        guard let ptr = icaltimezone_get_system_zone_directory() else { return nil }
        return String(cString: ptr)
    }

    /// 设置系统时区数据库目录路径
    /// - Parameter path: 时区数据库目录的文件系统路径
    public static func setSystemZoneDirectory(_ path: String) {
        icaltimezone_set_system_zone_directory(path)
    }

    /// 时区数据目录路径（可读写）
    /// 设置为 nil 时释放当前目录设置
    public static var zoneDirectory: String? {
        get {
            guard let ptr = icaltimezone_get_zone_directory() else { return nil }
            return String(cString: ptr)
        }
        set {
            if let path = newValue {
                icaltimezone_set_zone_directory(path)
            } else {
                icaltimezone_free_zone_directory()
            }
        }
    }

    /// TZID 前缀字符串（用于区分本地时区和全局时区）
    /// 设置为 nil 时不做任何操作
    public static var tzidPrefix: String? {
        get {
            guard let ptr = icaltimezone_tzid_prefix() else { return nil }
            return String(cString: ptr)
        }
        set {
            if let prefix = newValue {
                icaltimezone_set_tzid_prefix(prefix)
            }
        }
    }

    /// 释放所有内置时区缓存（释放内存）
    public static func freeBuiltinTimezones() {
        icaltimezone_free_builtin_timezones()
    }

    /// 获取所有内置时区列表
    /// - Returns: 内置时区数组（借用，不拥有所有权）
    public static var builtinTimezones: [Timezone] {
        guard let array = icaltimezone_get_builtin_timezones() else { return [] }
        let count = Int(array.pointee.num_elements)
        var result: [Timezone] = []
        result.reserveCapacity(count)
        for i in 0..<count {
            if let ptr = icalarray_element_at(array, i) {
                // icalarray 中每个元素是 icaltimezone 结构体（非指针），
                // 通过 OpaquePointer 直接包装原始指针
                result.append(Timezone(borrowing: OpaquePointer(ptr)))
            }
        }
        return result
    }
}

// MARK: - Timezone + CustomStringConvertible

extension Timezone: CustomStringConvertible {
    /// 返回时区的可读描述（优先显示名称 > TZID > 位置 > 未知）
    public var description: String {
        displayName ?? tzid ?? location ?? "<unknown timezone>"
    }
}

// MARK: - Timezone + Equatable

extension Timezone: Equatable {
    /// 通过 TZID 比较两个时区是否相同
    public static func == (lhs: Timezone, rhs: Timezone) -> Bool {
        lhs.tzid == rhs.tzid
    }
}

// MARK: - Timezone + Hashable

extension Timezone: Hashable {
    /// 基于 TZID 计算哈希值
    public func hash(into hasher: inout Hasher) {
        hasher.combine(tzid)
    }
}
