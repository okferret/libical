// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Recurrence

import libical

// MARK: - Recurrence

/// iCalendar 重复规则，对应 C 的 `icalrecurrencetype *`（引用计数管理）
///
/// 封装 RFC5545 中的 RRULE 属性值，描述事件的重复模式。
/// 例如：`"FREQ=WEEKLY;BYDAY=MO,WE,FR"` 表示每周一、三、五重复。
///
/// 底层使用引用计数（`icalrecurrencetype_ref` / `icalrecurrencetype_unref`）管理内存。
public final class Recurrence: @unchecked Sendable, CustomStringConvertible {

    // MARK: Internal storage

    /// 底层 C 重复规则指针
    internal var cPointer: UnsafeMutablePointer<icalrecurrencetype>

    // MARK: Initializers

    /// 从底层 C 指针创建（增加引用计数，共享所有权）
    internal init(retaining pointer: UnsafeMutablePointer<icalrecurrencetype>) {
        self.cPointer = pointer
        icalrecurrencetype_ref(pointer)
    }

    /// 从底层 C 指针创建（接管所有权，不增加引用计数）
    internal init(owning pointer: UnsafeMutablePointer<icalrecurrencetype>) {
        self.cPointer = pointer
    }

    /// 创建新的空重复规则
    /// - Returns: 成功返回新重复规则，内存分配失败返回 nil
    public init?() {
        guard let ptr = icalrecurrencetype_new() else { return nil }
        self.cPointer = ptr
    }

    /// 从 RFC5545 格式字符串创建重复规则
    /// - Parameter string: RRULE 值字符串，例如 `"FREQ=WEEKLY;BYDAY=MO,WE,FR"`
    /// - Returns: 解析成功返回重复规则，失败返回 nil
    public init?(string: String) {
        guard let ptr = icalrecurrencetype_new_from_string(string) else { return nil }
        self.cPointer = ptr
    }

    deinit {
        // 减少引用计数，引用计数归零时自动释放内存
        icalrecurrencetype_unref(cPointer)
    }

    // MARK: Cloning

    /// 克隆当前重复规则，返回独立副本
    /// - Returns: 新的重复规则副本，内存分配失败返回 nil
    public func clone() -> Recurrence? {
        guard let ptr = icalrecurrencetype_clone(cPointer) else { return nil }
        return Recurrence(owning: ptr)
    }

    // MARK: Properties

    /// 重复频率（如每天、每周、每月等）
    public var frequency: RecurrenceFrequency {
        get { RecurrenceFrequency(cValue: cPointer.pointee.freq) }
        set { cPointer.pointee.freq = newValue.cValue }
    }

    /// 重复结束时间（与 `count` 互斥，优先使用 `until`）
    /// 设置后重复在此时间之后停止
    public var until: Time {
        get { Time(cValue: cPointer.pointee.until) }
        set { cPointer.pointee.until = newValue.cValue }
    }

    /// 重复总次数（与 `until` 互斥，0 表示无限重复）
    public var count: Int {
        get { Int(cPointer.pointee.count) }
        set { cPointer.pointee.count = Int32(newValue) }
    }

    /// 重复间隔（默认为 1，如 `FREQ=WEEKLY;INTERVAL=2` 表示每两周）
    public var interval: Int {
        get { Int(cPointer.pointee.interval) }
        set { cPointer.pointee.interval = Int16(newValue) }
    }

    /// 每周的起始日（用于 WEEKLY 和 MONTHLY 频率的计算）
    public var weekStart: Weekday {
        get { Weekday(cValue: cPointer.pointee.week_start) }
        set { cPointer.pointee.week_start = newValue.cValue }
    }

    /// RSCALE 日历系统名称（用于非公历的重复规则，如 `"CHINESE"`）
    public var rscale: String? {
        guard let ptr = cPointer.pointee.rscale else { return nil }
        return String(cString: ptr)
    }

    /// 跳过类型（用于 RSCALE 扩展，处理不存在的日期）
    public var skip: RecurrenceSkip {
        get { RecurrenceSkip(cValue: cPointer.pointee.skip) }
        set { cPointer.pointee.skip = newValue.cValue }
    }

    // MARK: BY* arrays

    /// BYSECOND 列表（秒，范围 0-60）
    public var bySecond: [Int] { byArray(index: Int(ICAL_BY_SECOND.rawValue)) }

    /// BYMINUTE 列表（分钟，范围 0-59）
    public var byMinute: [Int] { byArray(index: Int(ICAL_BY_MINUTE.rawValue)) }

    /// BYHOUR 列表（小时，范围 0-23）
    public var byHour: [Int] { byArray(index: Int(ICAL_BY_HOUR.rawValue)) }

    /// BYDAY 列表（编码的星期几+位置，使用 `dayOfWeek(from:)` 和 `dayPosition(from:)` 解码）
    public var byDay: [Int] { byArray(index: Int(ICAL_BY_DAY.rawValue)) }

    /// BYMONTHDAY 列表（月内天序号，范围 1-31，负数表示从月末倒数）
    public var byMonthDay: [Int] { byArray(index: Int(ICAL_BY_MONTH_DAY.rawValue)) }

    /// BYYEARDAY 列表（年内天序号，范围 1-366，负数表示从年末倒数）
    public var byYearDay: [Int] { byArray(index: Int(ICAL_BY_YEAR_DAY.rawValue)) }

    /// BYWEEKNO 列表（年内周序号，范围 1-53，负数表示从年末倒数）
    public var byWeekNo: [Int] { byArray(index: Int(ICAL_BY_WEEK_NO.rawValue)) }

    /// BYMONTH 列表（编码的月份，使用 `month(from:)` 和 `isLeapMonth(from:)` 解码）
    public var byMonth: [Int] { byArray(index: Int(ICAL_BY_MONTH.rawValue)) }

    /// BYSETPOS 列表（在 BY* 规则生成的集合中选取特定位置的实例）
    public var bySetPos: [Int] { byArray(index: Int(ICAL_BY_SET_POS.rawValue)) }

    // MARK: Day encoding/decoding

    /// 从编码的 BYDAY 值中提取星期几
    /// - Parameter encodedDay: BYDAY 数组中的编码值
    /// - Returns: 对应的星期几枚举
    public static func dayOfWeek(from encodedDay: Int) -> Weekday {
        Weekday(cValue: icalrecurrencetype_day_day_of_week(Int16(encodedDay)))
    }

    /// 从编码的 BYDAY 值中提取位置（如第几个星期几）
    /// - Parameter encodedDay: BYDAY 数组中的编码值
    /// - Returns: 位置值（0 表示所有，正数表示第 n 个，负数表示倒数第 n 个）
    public static func dayPosition(from encodedDay: Int) -> Int {
        Int(icalrecurrencetype_day_position(Int16(encodedDay)))
    }

    /// 将星期几和位置编码为 BYDAY 值
    /// - Parameters:
    ///   - weekday: 星期几枚举
    ///   - position: 位置（0 表示所有，正数表示第 n 个，负数表示倒数第 n 个）
    /// - Returns: 编码后的 BYDAY 值
    public static func encodeDay(weekday: Weekday, position: Int) -> Int {
        Int(icalrecurrencetype_encode_day(weekday.cValue, Int32(position)))
    }

    // MARK: Month encoding/decoding

    /// 从编码的 BYMONTH 值中提取月份数字（1-12）
    /// - Parameter encodedMonth: BYMONTH 数组中的编码值
    /// - Returns: 月份数字
    public static func month(from encodedMonth: Int) -> Int {
        Int(icalrecurrencetype_month_month(Int16(encodedMonth)))
    }

    /// 判断编码的 BYMONTH 值是否表示闰月（用于农历等日历系统）
    /// - Parameter encodedMonth: BYMONTH 数组中的编码值
    /// - Returns: 是闰月返回 true
    public static func isLeapMonth(from encodedMonth: Int) -> Bool {
        icalrecurrencetype_month_is_leap(Int16(encodedMonth))
    }

    /// 将月份数字和是否闰月编码为 BYMONTH 值
    /// - Parameters:
    ///   - month: 月份数字（1-12）
    ///   - isLeap: 是否为闰月，默认 false
    /// - Returns: 编码后的 BYMONTH 值
    public static func encodeMonth(_ month: Int, isLeap: Bool = false) -> Int {
        Int(icalrecurrencetype_encode_month(Int32(month), isLeap))
    }

    // MARK: Conversion

    /// 将重复规则转换为 iCalendar 格式字符串（如 `"FREQ=WEEKLY;BYDAY=MO,WE,FR"`）
    public var iCalString: String {
        guard let ptr = icalrecurrencetype_as_string_r(cPointer) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 返回 iCalendar 格式字符串表示
    public var description: String { iCalString }

    // MARK: Static string conversion helpers

    /// 从字符串解析重复频率枚举（如 `"WEEKLY"` → `.weekly`）
    /// - Parameter string: 频率字符串
    /// - Returns: 对应的频率枚举值
    public static func frequency(from string: String) -> RecurrenceFrequency {
        RecurrenceFrequency(cValue: icalrecur_string_to_freq(string))
    }

    /// 从字符串解析跳过类型枚举（如 `"OMIT"` → `.omit`）
    /// - Parameter string: 跳过类型字符串
    /// - Returns: 对应的跳过类型枚举值
    public static func skip(from string: String) -> RecurrenceSkip {
        RecurrenceSkip(cValue: icalrecur_string_to_skip(string))
    }

    /// 从字符串解析星期几枚举（如 `"MO"` → `.monday`）
    /// - Parameter string: 星期几字符串（两字母缩写）
    /// - Returns: 对应的星期几枚举值
    public static func weekday(from string: String) -> Weekday {
        Weekday(cValue: icalrecur_string_to_weekday(string))
    }

    /// 获取 libical 支持的 RSCALE 日历系统列表
    /// - Returns: 支持的日历系统名称数组（如 `["GREGORIAN", "CHINESE", ...]`）
    public static var rscaleSupportedCalendars: [String] {
        guard let array = icalrecurrencetype_rscale_supported_calendars() else { return [] }
        let count = Int(array.pointee.num_elements)
        var result: [String] = []
        result.reserveCapacity(count)
        for i in 0..<count {
            if let ptr = icalarray_element_at(array, i) {
                // 数组中存储的是 char* 指针
                let strPtrPtr = ptr.assumingMemoryBound(to: UnsafePointer<CChar>.self)
                result.append(String(cString: strPtrPtr.pointee))
            }
        }
        return result
    }

    // MARK: Private helpers

    /// 读取 by[index] 数组中的有效值
    /// - Parameter index: BY* 数组的索引（对应 `ICAL_BY_*` 常量）
    /// - Returns: 该 BY* 规则中的所有有效值数组
    private func byArray(index: Int) -> [Int] {
        let numParts = Int(ICAL_BY_NUM_PARTS.rawValue)
        guard index >= 0 && index < numParts else { return [] }
        // 使用 withUnsafeBytes 访问 by 数组（固定大小的 tuple）
        return withUnsafeBytes(of: cPointer.pointee.by) { rawBuffer in
            let stride = MemoryLayout<icalrecurrence_by_data>.stride
            let offset = index * stride
            guard offset + stride <= rawBuffer.count else { return [] }
            let byEntry = rawBuffer.load(
                fromByteOffset: offset,
                as: icalrecurrence_by_data.self
            )
            guard let dataPtr = byEntry.data, byEntry.size > 0 else { return [] }
            var result: [Int] = []
            result.reserveCapacity(Int(byEntry.size))
            for i in 0..<Int(byEntry.size) {
                result.append(Int(dataPtr[i]))
            }
            return result
        }
    }
}

// MARK: - RecurrenceIterator

/// 重复规则迭代器，对应 C 的 `icalrecur_iterator *`
///
/// 根据重复规则和起始时间，逐一生成每次重复的时间点。
/// 支持正向（`next()`）和反向（`previous()`）迭代。
///
/// 示例：
/// ```swift
/// if let rule = Recurrence(string: "FREQ=WEEKLY;COUNT=3"),
///    let iter = RecurrenceIterator(rule: rule, start: startTime) {
///     for time in iter {
///         print(time)
///     }
/// }
/// ```
public final class RecurrenceIterator: @unchecked Sendable {

    // MARK: Internal storage

    /// 底层 C 迭代器指针
    private var cPointer: OpaquePointer

    // MARK: Initializers

    /// 创建重复规则迭代器
    /// - Parameters:
    ///   - rule: 重复规则
    ///   - start: 重复的起始时间（第一次发生的时间）
    /// - Returns: 创建成功返回迭代器，失败返回 nil
    public init?(rule: Recurrence, start: Time) {
        guard let ptr = icalrecur_iterator_new(rule.cPointer, start.cValue) else { return nil }
        self.cPointer = ptr
    }

    deinit {
        icalrecur_iterator_free(cPointer)
    }

    // MARK: Configuration

    /// 设置迭代起始时间（跳过此时间之前的重复实例）
    /// - Parameter start: 新的起始时间
    /// - Returns: 设置成功返回 true
    @discardableResult
    public func setStart(_ start: Time) -> Bool {
        icalrecur_iterator_set_start(cPointer, start.cValue)
    }

    /// 设置迭代结束时间（超过此时间后停止迭代）
    /// - Parameter end: 结束时间
    /// - Returns: 设置成功返回 true
    @discardableResult
    public func setEnd(_ end: Time) -> Bool {
        icalrecur_iterator_set_end(cPointer, end.cValue)
    }

    /// 同时设置迭代的起始和结束时间范围
    /// - Parameters:
    ///   - from: 起始时间
    ///   - to: 结束时间
    /// - Returns: 设置成功返回 true
    @discardableResult
    public func setRange(from: Time, to: Time) -> Bool {
        icalrecur_iterator_set_range(cPointer, from.cValue, to.cValue)
    }

    // MARK: Iteration

    /// 获取下一个重复时间点
    /// - Returns: 下一个时间点，迭代结束返回 nil
    public func next() -> Time? {
        let t = icalrecur_iterator_next(cPointer)
        guard !icaltime_is_null_time(t) else { return nil }
        return Time(cValue: t)
    }

    /// 获取上一个重复时间点（反向迭代）
    /// - Returns: 上一个时间点，迭代结束返回 nil
    public func previous() -> Time? {
        let t = icalrecur_iterator_prev(cPointer)
        guard !icaltime_is_null_time(t) else { return nil }
        return Time(cValue: t)
    }

    /// 获取所有重复时间点数组
    /// - Parameter maxCount: 最大返回数量，防止无限重复规则导致无限循环，默认 1000
    /// - Returns: 所有重复时间点数组
    public func allOccurrences(maxCount: Int = 1000) -> [Time] {
        var result: [Time] = []
        result.reserveCapacity(Swift.min(maxCount, 64))
        var count = 0
        while count < maxCount {
            guard let t = next() else { break }
            result.append(t)
            count += 1
        }
        return result
    }
}

// MARK: - RecurrenceIterator + Sequence

/// 使 `RecurrenceIterator` 支持 `for-in` 循环语法
extension RecurrenceIterator: Sequence, IteratorProtocol {
    public typealias Element = Time

    /// 返回自身作为迭代器（满足 `Sequence` 协议）
    public func makeIterator() -> RecurrenceIterator { self }
}
