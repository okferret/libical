// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Time, Duration, Period

@preconcurrency import libical
import Foundation

// MARK: - Time

/// iCalendar 日期/时间类型，对应 C 的 `icaltimetype`
///
/// 可表示纯日期（`isDate == true`）或日期时间，支持时区关联。
/// 实现了 `Equatable`、`Comparable`、`Hashable` 协议，可直接用于集合和排序。
public struct Time: Equatable, Comparable, Hashable, Sendable, CustomStringConvertible {

    // MARK: Internal storage

    /// 底层 C 时间结构体
    internal var cValue: icaltimetype

    // MARK: Initializers

    /// 从底层 C 结构体创建
    public init(cValue: icaltimetype) {
        self.cValue = cValue
    }

    /// 创建空时间（null time，`isNull == true`）
    public init() {
        self.cValue = icaltime_null_time()
    }

    /// 创建空日期（null date，仅日期部分为空）
    public static var nullDate: Time {
        Time(cValue: icaltime_null_date())
    }

    /// 从 RFC5545 格式字符串创建（如 `"20240101T120000Z"`）
    /// - Parameter string: iCalendar 格式的日期时间字符串
    /// - Returns: 解析成功返回时间对象，无效字符串返回 nil
    public init?(string: String) {
        let t = icaltime_from_string(string)
        guard icaltime_is_valid_time(t) else { return nil }
        self.cValue = t
    }

    /// 从 Unix 时间戳创建
    /// - Parameters:
    ///   - timeInterval: Unix 时间戳（自 1970-01-01 00:00:00 UTC 的秒数）
    ///   - isDate: 是否仅表示日期（忽略时间部分），默认 false
    ///   - timezone: 关联的时区，nil 表示浮动时间
    public init(timeInterval: TimeInterval, isDate: Bool = false, timezone: Timezone? = nil) {
        let t = icaltime_from_timet_with_zone(
            time_t(timeInterval),
            isDate,
            timezone?.cPointer
        )
        self.cValue = t
    }

    /// 从年份中的第几天创建（1 月 1 日为第 1 天）
    /// - Parameters:
    ///   - dayOfYear: 年内天序号（1-366）
    ///   - year: 年份
    public init(dayOfYear: Int, year: Int) {
        self.cValue = icaltime_from_day_of_year(Int32(dayOfYear), Int32(year))
    }

    /// 获取当前时间（可指定时区）
    /// - Parameter timezone: 目标时区，nil 表示使用系统本地时区
    /// - Returns: 当前时间
    public static func now(in timezone: Timezone? = nil) -> Time {
        Time(cValue: icaltime_current_time_with_zone(timezone?.cPointer))
    }

    /// 获取今天的日期（仅日期，无时间部分）
    public static var today: Time {
        Time(cValue: icaltime_today())
    }

    // MARK: Properties

    /// 年份
    public var year: Int {
        get { Int(cValue.year) }
        set { cValue.year = Int32(newValue) }
    }

    /// 月份（1-12）
    public var month: Int {
        get { Int(cValue.month) }
        set { cValue.month = Int32(newValue) }
    }

    /// 日（1-31）
    public var day: Int {
        get { Int(cValue.day) }
        set { cValue.day = Int32(newValue) }
    }

    /// 小时（0-23）
    public var hour: Int {
        get { Int(cValue.hour) }
        set { cValue.hour = Int32(newValue) }
    }

    /// 分钟（0-59）
    public var minute: Int {
        get { Int(cValue.minute) }
        set { cValue.minute = Int32(newValue) }
    }

    /// 秒（0-60，60 用于闰秒）
    public var second: Int {
        get { Int(cValue.second) }
        set { cValue.second = Int32(newValue) }
    }

    /// 是否为纯日期（不含时间部分）
    public var isDate: Bool {
        get { cValue.is_date != 0 }
        set { cValue.is_date = newValue ? 1 : 0 }
    }

    /// 是否处于夏令时
    public var isDaylight: Bool {
        get { cValue.is_daylight != 0 }
        set { cValue.is_daylight = newValue ? 1 : 0 }
    }

    /// 是否为空时间（null time）
    public var isNull: Bool {
        icaltime_is_null_time(cValue)
    }

    /// 是否为有效时间
    public var isValid: Bool {
        icaltime_is_valid_time(cValue)
    }

    /// 是否为 UTC 时间
    public var isUTC: Bool {
        icaltime_is_utc(cValue)
    }

    /// 关联的时区标识符（TZID），浮动时间返回 nil
    public var timezoneID: String? {
        guard let ptr = icaltime_get_tzid(cValue) else { return nil }
        return String(cString: ptr)
    }

    /// 在当年中的天序号（1 月 1 日为 1）
    public var dayOfYear: Int {
        Int(icaltime_day_of_year(cValue))
    }

    /// 星期几（1=周日，2=周一，...，7=周六）
    public var dayOfWeek: Int {
        Int(icaltime_day_of_week(cValue))
    }

    /// 获取当前日期所在周的起始日在年内的天序号
    /// - Parameter firstDayOfWeek: 每周第一天（1=周日，2=周一，...）
    /// - Returns: 本周起始日的年内天序号
    public func startDayOfYearWeek(firstDayOfWeek: Int) -> Int {
        Int(icaltime_start_doy_week(cValue, Int32(firstDayOfWeek)))
    }

    /// 关联的时区对象（借用，不拥有所有权）
    public var timezone: Timezone? {
        guard let ptr = icaltime_get_timezone(cValue) else { return nil }
        return Timezone(borrowing: ptr)
    }

    // MARK: Conversion

    /// 转换为 Unix 时间戳（自 1970-01-01 00:00:00 UTC 的秒数）
    public var timeIntervalSince1970: TimeInterval {
        TimeInterval(icaltime_as_timet(cValue))
    }

    /// 在指定时区下转换为 Unix 时间戳
    /// - Parameter timezone: 目标时区，nil 表示使用关联时区
    /// - Returns: Unix 时间戳
    public func timeIntervalSince1970(in timezone: Timezone?) -> TimeInterval {
        TimeInterval(icaltime_as_timet_with_zone(cValue, timezone?.cPointer))
    }

    /// 转换为 Foundation `Date` 对象
    public var date: Date {
        Date(timeIntervalSince1970: timeIntervalSince1970)
    }

    /// 转换为 iCalendar 格式字符串（如 `"20240101T120000Z"`）
    /// 使用 `_r` 版本返回独立分配的缓冲区，线程安全，需要手动释放
    public var iCalString: String {
        guard let ptr = icaltime_as_ical_string_r(cValue) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 规范化时间（处理溢出的时间字段，如 25 小时 → 次日 1 小时）
    /// - Returns: 规范化后的新时间对象
    public func normalized() -> Time {
        Time(cValue: icaltime_normalize(cValue))
    }

    /// 将时间转换到指定时区
    /// - Parameter timezone: 目标时区
    /// - Returns: 转换后的新时间对象
    public func converted(to timezone: Timezone) -> Time {
        Time(cValue: icaltime_convert_to_zone(cValue, timezone.cPointer))
    }

    /// 设置时间关联的时区（不转换时间值，仅更改时区标记）
    /// - Parameter timezone: 要关联的时区
    /// - Returns: 更新时区后的新时间对象
    public func settingTimezone(_ timezone: Timezone) -> Time {
        var copy = cValue
        return Time(cValue: icaltime_set_timezone(&copy, timezone.cPointer))
    }

    /// 对时间进行偏移调整
    /// - Parameters:
    ///   - days: 偏移天数（可为负数）
    ///   - hours: 偏移小时数（可为负数）
    ///   - minutes: 偏移分钟数（可为负数）
    ///   - seconds: 偏移秒数（可为负数）
    /// - Returns: 调整后的新时间对象
    public func adjusted(days: Int = 0, hours: Int = 0, minutes: Int = 0, seconds: Int = 0) -> Time {
        var copy = cValue
        icaltime_adjust(&copy, Int32(days), Int32(hours), Int32(minutes), Int32(seconds))
        return Time(cValue: copy)
    }

    // MARK: Static helpers

    /// 获取指定年月的天数
    /// - Parameters:
    ///   - month: 月份（1-12）
    ///   - year: 年份（用于判断闰年）
    /// - Returns: 该月的天数
    public static func daysInMonth(_ month: Int, year: Int) -> Int {
        Int(icaltime_days_in_month(Int32(month), Int32(year)))
    }

    /// 判断指定年份是否为闰年
    /// - Parameter year: 年份
    /// - Returns: 是闰年返回 true
    public static func isLeapYear(_ year: Int) -> Bool {
        icaltime_is_leap_year(Int32(year))
    }

    /// 获取指定年份的总天数（平年 365，闰年 366）
    /// - Parameter year: 年份
    /// - Returns: 该年的总天数
    public static func daysInYear(_ year: Int) -> Int {
        Int(icaltime_days_in_year(Int32(year)))
    }

    // MARK: Equatable & Comparable

    /// 比较两个时间是否相等（考虑时区）
    public static func == (lhs: Time, rhs: Time) -> Bool {
        icaltime_compare(lhs.cValue, rhs.cValue) == 0
    }

    /// 比较两个时间的先后顺序（考虑时区）
    public static func < (lhs: Time, rhs: Time) -> Bool {
        icaltime_compare(lhs.cValue, rhs.cValue) < 0
    }

    /// 仅比较日期部分（忽略时间和时区）
    /// - Parameter other: 另一个时间
    /// - Returns: 负数表示早于，0 表示相同，正数表示晚于
    public func compareDateOnly(to other: Time) -> Int {
        Int(icaltime_compare_date_only(cValue, other.cValue))
    }

    /// 仅比较日期部分（在指定时区下比较）
    /// - Parameters:
    ///   - other: 另一个时间
    ///   - timezone: 用于比较的时区
    /// - Returns: 负数表示早于，0 表示相同，正数表示晚于
    public func compareDateOnly(to other: Time, in timezone: Timezone) -> Int {
        Int(icaltime_compare_date_only_tz(cValue, other.cValue, timezone.cPointer))
    }

    // MARK: Hashable

    /// 基于年月日时分秒和是否为日期计算哈希值
    public func hash(into hasher: inout Hasher) {
        hasher.combine(year)
        hasher.combine(month)
        hasher.combine(day)
        hasher.combine(hour)
        hasher.combine(minute)
        hasher.combine(second)
        hasher.combine(isDate)
    }

    // MARK: CustomStringConvertible

    /// 返回 iCalendar 格式字符串表示
    public var description: String { iCalString }
}

// MARK: - Duration

/// iCalendar 时间段类型，对应 C 的 `icaldurationtype`
///
/// 表示一段时间长度，可包含周、天、时、分、秒，支持负值。
/// 例如：`P1W`（1 周）、`PT2H30M`（2 小时 30 分钟）、`-P1D`（负 1 天）
public struct Duration: Equatable, Hashable, Sendable, CustomStringConvertible {

    // MARK: Internal storage

    /// 底层 C 时间段结构体
    internal var cValue: icaldurationtype

    // MARK: Initializers

    /// 从底层 C 结构体创建
    public init(cValue: icaldurationtype) {
        self.cValue = cValue
    }

    /// 创建空时间段（零时长）
    public init() {
        self.cValue = icaldurationtype_null_duration()
    }

    /// 从总秒数创建时间段
    /// - Parameter seconds: 总秒数（正数或负数）
    public init(seconds: Int) {
        self.cValue = icaldurationtype_from_seconds(Int32(seconds))
    }

    /// 从 RFC5545 格式字符串创建（如 `"P1W2DT3H4M5S"`）
    /// - Parameter string: iCalendar 格式的时间段字符串
    /// - Returns: 解析成功返回时间段，无效字符串返回 nil
    public init?(string: String) {
        let d = icaldurationtype_from_string(string)
        guard !icaldurationtype_is_bad_duration(d) else { return nil }
        self.cValue = d
    }

    /// 从各时间分量创建时间段
    /// - Parameters:
    ///   - isNegative: 是否为负时间段，默认 false
    ///   - weeks: 周数，默认 0
    ///   - days: 天数，默认 0
    ///   - hours: 小时数，默认 0
    ///   - minutes: 分钟数，默认 0
    ///   - seconds: 秒数，默认 0
    public init(isNegative: Bool = false, weeks: Int = 0, days: Int = 0,
                hours: Int = 0, minutes: Int = 0, seconds: Int = 0) {
        var d = icaldurationtype_null_duration()
        d.is_neg = isNegative ? 1 : 0
        d.weeks = UInt32(weeks)
        d.days = UInt32(days)
        d.hours = UInt32(hours)
        d.minutes = UInt32(minutes)
        d.seconds = UInt32(seconds)
        self.cValue = d
    }

    // MARK: Properties

    /// 是否为负时间段
    public var isNegative: Bool {
        get { cValue.is_neg != 0 }
        set { cValue.is_neg = newValue ? 1 : 0 }
    }

    /// 周数部分
    public var weeks: Int {
        get { Int(cValue.weeks) }
        set { cValue.weeks = UInt32(newValue) }
    }

    /// 天数部分
    public var days: Int {
        get { Int(cValue.days) }
        set { cValue.days = UInt32(newValue) }
    }

    /// 小时部分
    public var hours: Int {
        get { Int(cValue.hours) }
        set { cValue.hours = UInt32(newValue) }
    }

    /// 分钟部分
    public var minutes: Int {
        get { Int(cValue.minutes) }
        set { cValue.minutes = UInt32(newValue) }
    }

    /// 秒数部分
    public var seconds: Int {
        get { Int(cValue.seconds) }
        set { cValue.seconds = UInt32(newValue) }
    }

    /// 是否为空时间段（零时长）
    public var isNull: Bool {
        icaldurationtype_is_null_duration(cValue)
    }

    /// 是否为无效时间段（解析失败时产生）
    public var isBad: Bool {
        icaldurationtype_is_bad_duration(cValue)
    }

    /// 转换为总秒数（不考虑夏令时，1 周 = 7 天 = 604800 秒）
    public var totalSeconds: Int {
        Int(icaldurationtype_as_seconds(cValue))
    }

    /// 转换为 UTC 总秒数（考虑夏令时调整）
    public var totalUTCSeconds: Int {
        Int(icaldurationtype_as_utc_seconds(cValue))
    }

    /// 规范化时间段（将各分量调整为标准范围）
    /// - Returns: 规范化后的新时间段对象
    public func normalized() -> Duration {
        Duration(cValue: icaldurationtype_normalize(cValue))
    }

    /// 转换为 iCalendar 格式字符串（如 `"P1W2DT3H4M5S"`）
    public var iCalString: String {
        guard let ptr = icaldurationtype_as_ical_string_r(cValue) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    // MARK: Equatable & Hashable

    /// 通过总秒数和正负号比较两个时间段是否相等
    public static func == (lhs: Duration, rhs: Duration) -> Bool {
        lhs.totalSeconds == rhs.totalSeconds && lhs.isNegative == rhs.isNegative
    }

    /// 基于各时间分量计算哈希值
    public func hash(into hasher: inout Hasher) {
        hasher.combine(isNegative)
        hasher.combine(weeks)
        hasher.combine(days)
        hasher.combine(hours)
        hasher.combine(minutes)
        hasher.combine(seconds)
    }

    /// 返回 iCalendar 格式字符串表示
    public var description: String { iCalString }
}

// MARK: - Time + Duration arithmetic

extension Time {
    /// 时间加上时间段，返回新的时间（`time + duration`）
    public static func + (lhs: Time, rhs: Duration) -> Time {
        Time(cValue: icalduration_extend(lhs.cValue, rhs.cValue))
    }

    /// 计算两个时间之差（`lhs - rhs`），返回正向 Duration
    public static func - (lhs: Time, rhs: Time) -> Duration {
        Duration(cValue: icalduration_from_times(lhs.cValue, rhs.cValue))
    }
}

// MARK: - Period

/// iCalendar 时间段，对应 C 的 `icalperiodtype`
///
/// 表示一个时间区间，可通过起止时间或起始时间+持续时长来定义。
/// 例如：`"20240101T120000Z/20240101T130000Z"`（起止时间）
///       `"20240101T120000Z/PT1H"`（起始时间 + 1 小时）
public struct Period: Equatable, Hashable, Sendable, CustomStringConvertible {

    // MARK: Internal storage

    /// 底层 C 时间段结构体
    internal var cValue: icalperiodtype

    // MARK: Initializers

    /// 从底层 C 结构体创建
    public init(cValue: icalperiodtype) {
        self.cValue = cValue
    }

    /// 从起始时间和结束时间创建时间段
    /// - Parameters:
    ///   - start: 起始时间
    ///   - end: 结束时间
    public init(start: Time, end: Time) {
        var p = icalperiodtype_null_period()
        p.start = start.cValue
        p.end = end.cValue
        self.cValue = p
    }

    /// 从起始时间和持续时长创建时间段
    /// - Parameters:
    ///   - start: 起始时间
    ///   - duration: 持续时长
    public init(start: Time, duration: Duration) {
        var p = icalperiodtype_null_period()
        p.start = start.cValue
        p.duration = duration.cValue
        self.cValue = p
    }

    /// 从 RFC5545 格式字符串创建（如 `"20240101T120000Z/PT1H"`）
    /// - Parameter string: iCalendar 格式的时间段字符串
    /// - Returns: 解析成功返回时间段，无效字符串返回 nil
    public init?(string: String) {
        let p = icalperiodtype_from_string(string)
        guard icalperiodtype_is_valid_period(p) else { return nil }
        self.cValue = p
    }

    // MARK: Properties

    /// 起始时间
    public var start: Time {
        get { Time(cValue: cValue.start) }
        set { cValue.start = newValue.cValue }
    }

    /// 结束时间（通过起止时间定义时有效）
    public var end: Time {
        get { Time(cValue: cValue.end) }
        set { cValue.end = newValue.cValue }
    }

    /// 持续时长（通过起始时间+时长定义时有效）
    public var duration: Duration {
        get { Duration(cValue: cValue.duration) }
        set { cValue.duration = newValue.cValue }
    }

    /// 是否为空时间段（null period）
    public var isNull: Bool {
        icalperiodtype_is_null_period(cValue)
    }

    /// 是否为有效时间段
    public var isValid: Bool {
        icalperiodtype_is_valid_period(cValue)
    }

    /// 转换为 iCalendar 格式字符串
    /// 使用 `_r` 版本返回独立分配的缓冲区，线程安全，需要手动释放
    public var iCalString: String {
        guard let ptr = icalperiodtype_as_ical_string_r(cValue) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    // MARK: Equatable & Hashable

    /// 通过起始时间和结束时间比较两个时间段是否相等
    public static func == (lhs: Period, rhs: Period) -> Bool {
        lhs.start == rhs.start && lhs.end == rhs.end
    }

    /// 基于起始时间和结束时间计算哈希值
    public func hash(into hasher: inout Hasher) {
        hasher.combine(start)
        hasher.combine(end)
    }

    /// 返回 iCalendar 格式字符串表示
    public var description: String { iCalString }
}
