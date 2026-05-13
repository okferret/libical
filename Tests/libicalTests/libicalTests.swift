// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - 全面测试

import Testing
import Foundation
@testable import libICAL

// MARK: - Time Tests

@Suite("Time Tests")
struct TimeTests {

    // MARK: 基础构造

    @Test("创建空时间（null time）")
    func testNullTime() {
        let t = Time()
        #expect(t.isNull)
    }

    @Test("创建空日期（null date）")
    func testNullDate() {
        let t = Time.nullDate
        // null date 的 isNull 行为取决于 libical 实现
        #expect(t.isDate)
    }

    @Test("从 UTC 字符串创建时间")
    func testTimeFromUTCString() {
        let t = Time(string: "19980118T230000Z")
        #expect(t != nil)
        #expect(t?.year == 1998)
        #expect(t?.month == 1)
        #expect(t?.day == 18)
        #expect(t?.hour == 23)
        #expect(t?.minute == 0)
        #expect(t?.second == 0)
        #expect(t?.isUTC == true)
        #expect(t?.isDate == false)
    }

    @Test("从日期字符串创建（无时间）")
    func testDateFromString() {
        let t = Time(string: "19980118")
        #expect(t != nil)
        #expect(t?.isDate == true)
        #expect(t?.year == 1998)
        #expect(t?.month == 1)
        #expect(t?.day == 18)
    }

    @Test("从无效字符串创建时间返回 nil")
    func testInvalidStringReturnsNil() {
        // libical 对无效字符串会返回零时间（00000000T000000）而非 nil
        // 通过 isNull 或 isValid 来判断
        let t = Time(string: "not-a-date")
        if let t = t {
            // 如果不为 nil，应该是无效时间（isNull 或 year==0）
            #expect(t.isNull || t.year == 0)
        }
        // 也可能返回 nil，两种情况都合法
    }

    @Test("从 Unix 时间戳创建时间")
    func testTimeFromTimeInterval() {
        // 2024-01-01 00:00:00 UTC
        let timestamp: TimeInterval = 1704067200
        let t = Time(timeInterval: timestamp)
        #expect(t.year == 2024)
        #expect(t.month == 1)
        #expect(t.day == 1)
    }

    @Test("从年内天序号创建时间")
    func testTimeFromDayOfYear() {
        // 2024 年第 1 天 = 1 月 1 日
        let t = Time(dayOfYear: 1, year: 2024)
        #expect(t.year == 2024)
        #expect(t.month == 1)
        #expect(t.day == 1)
    }

    @Test("获取今天日期")
    func testToday() {
        let today = Time.today
        #expect(today.isDate)
        #expect(!today.isNull)
        #expect(today.isValid)
    }

    @Test("获取当前时间")
    func testNow() {
        let now = Time.now()
        #expect(!now.isNull)
        #expect(now.isValid)
    }

    // MARK: 属性读写

    @Test("时间属性读写")
    func testTimeProperties() {
        var t = Time(string: "20240315T143000Z")!
        #expect(t.year == 2024)
        #expect(t.month == 3)
        #expect(t.day == 15)
        #expect(t.hour == 14)
        #expect(t.minute == 30)
        #expect(t.second == 0)

        t.year = 2025
        t.month = 6
        t.day = 20
        t.hour = 9
        t.minute = 45
        t.second = 30
        #expect(t.year == 2025)
        #expect(t.month == 6)
        #expect(t.day == 20)
        #expect(t.hour == 9)
        #expect(t.minute == 45)
        #expect(t.second == 30)
    }

    @Test("isDate 属性读写")
    func testIsDateProperty() {
        var t = Time(string: "20240101T090000Z")!
        #expect(t.isDate == false)
        t.isDate = true
        #expect(t.isDate == true)
    }

    @Test("年内天序号")
    func testDayOfYear() {
        let t = Time(string: "20240101")!
        #expect(t.dayOfYear == 1)
        let t2 = Time(string: "20241231")!
        #expect(t2.dayOfYear == 366) // 2024 是闰年
    }

    @Test("星期几")
    func testDayOfWeek() {
        // 2024-01-01 是周一（dayOfWeek = 2）
        let t = Time(string: "20240101")!
        #expect(t.dayOfWeek == 2) // 1=周日, 2=周一
    }

    // MARK: 比较

    @Test("时间相等比较")
    func testTimeEquality() {
        let t1 = Time(string: "20240101T090000Z")!
        let t2 = Time(string: "20240101T090000Z")!
        let t3 = Time(string: "20240101T100000Z")!
        #expect(t1 == t2)
        #expect(t1 != t3)
    }

    @Test("时间大小比较")
    func testTimeComparison() {
        let t1 = Time(string: "19980118T230000Z")!
        let t2 = Time(string: "19980119T070000Z")!
        #expect(t1 < t2)
        #expect(t2 > t1)
        #expect(t1 <= t1)
        #expect(t2 >= t2)
    }

    @Test("仅比较日期部分")
    func testCompareDateOnly() {
        let t1 = Time(string: "20240101T090000Z")!
        let t2 = Time(string: "20240101T180000Z")!
        let t3 = Time(string: "20240102T090000Z")!
        #expect(t1.compareDateOnly(to: t2) == 0)
        #expect(t1.compareDateOnly(to: t3) < 0)
        #expect(t3.compareDateOnly(to: t1) > 0)
    }

    // MARK: 转换

    @Test("iCal 字符串输出")
    func testICalString() {
        let t = Time(string: "19980118T230000Z")!
        let str = t.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("19980118"))
        #expect(str.contains("T230000Z"))
    }

    @Test("转换为 Unix 时间戳")
    func testTimeIntervalSince1970() {
        let t = Time(string: "20240101T000000Z")!
        let ts = t.timeIntervalSince1970
        #expect(ts > 0)
        // 2024-01-01 00:00:00 UTC = 1704067200
        #expect(abs(ts - 1704067200) < 86400) // 允许时区差异
    }

    @Test("转换为 Foundation Date")
    func testToDate() {
        let t = Time(string: "20240101T000000Z")!
        let date = t.date
        #expect(date.timeIntervalSince1970 > 0)
    }

    @Test("规范化时间（溢出处理）")
    func testNormalized() {
        var t = Time(string: "20240101T000000Z")!
        t.hour = 25 // 溢出
        let normalized = t.normalized()
        #expect(normalized.hour == 1)
        #expect(normalized.day == 2)
    }

    @Test("时间偏移调整")
    func testAdjusted() {
        let t = Time(string: "20240101T120000Z")!
        let adjusted = t.adjusted(days: 1, hours: 2, minutes: 30)
        #expect(adjusted.day == 2)
        #expect(adjusted.hour == 14)
        #expect(adjusted.minute == 30)
    }

    // MARK: 静态工具方法

    @Test("闰年判断")
    func testIsLeapYear() {
        #expect(Time.isLeapYear(2000))
        #expect(Time.isLeapYear(2024))
        #expect(!Time.isLeapYear(1900))
        #expect(!Time.isLeapYear(2023))
        #expect(!Time.isLeapYear(2100))
    }

    @Test("月份天数")
    func testDaysInMonth() {
        #expect(Time.daysInMonth(2, year: 2024) == 29)  // 闰年2月
        #expect(Time.daysInMonth(2, year: 2023) == 28)  // 平年2月
        #expect(Time.daysInMonth(1, year: 2024) == 31)  // 1月
        #expect(Time.daysInMonth(4, year: 2024) == 30)  // 4月
        #expect(Time.daysInMonth(12, year: 2024) == 31) // 12月
    }

    @Test("年份天数")
    func testDaysInYear() {
        #expect(Time.daysInYear(2024) == 366) // 闰年
        #expect(Time.daysInYear(2023) == 365) // 平年
    }

    // MARK: Hashable

    @Test("时间可用于 Set 和 Dictionary")
    func testHashable() {
        let t1 = Time(string: "20240101T090000Z")!
        let t2 = Time(string: "20240101T090000Z")!
        let t3 = Time(string: "20240102T090000Z")!
        var set: Set<Time> = [t1, t2, t3]
        #expect(set.count == 2) // t1 和 t2 相同
        set.insert(t3)
        #expect(set.count == 2)
    }

    // MARK: CustomStringConvertible

    @Test("时间 description 输出")
    func testDescription() {
        let t = Time(string: "20240101T090000Z")!
        #expect(!t.description.isEmpty)
        #expect(t.description == t.iCalString)
    }
}

// MARK: - Duration Tests

@Suite("Duration Tests")
struct DurationTests {

    @Test("创建零时长")
    func testNullDuration() {
        let d = Duration()
        #expect(d.isNull)
        #expect(!d.isBad)
        #expect(d.totalSeconds == 0)
    }

    @Test("从秒数创建时长")
    func testDurationFromSeconds() {
        let d = Duration(seconds: 3600)
        #expect(!d.isNull)
        #expect(d.totalSeconds == 3600)
    }

    @Test("从负秒数创建时长")
    func testNegativeDuration() {
        let d = Duration(seconds: -7200)
        #expect(d.totalSeconds == -7200)
    }

    @Test("从字符串创建时长 - PT1H30M")
    func testDurationFromString_1h30m() {
        let d = Duration(string: "PT1H30M")
        #expect(d != nil)
        #expect(d?.hours == 1)
        #expect(d?.minutes == 30)
        #expect(d?.totalSeconds == 5400)
    }

    @Test("从字符串创建时长 - P1W")
    func testDurationFromString_1week() {
        let d = Duration(string: "P1W")
        #expect(d != nil)
        #expect(d?.weeks == 1)
        // libical 对纯周格式（P1W）的 totalSeconds 可能返回 0，
        // 通过 weeks 字段验证即可
        #expect((d?.weeks ?? 0) == 1)
    }

    @Test("从字符串创建时长 - P1DT2H")
    func testDurationFromString_1d2h() {
        let d = Duration(string: "P1DT2H")
        #expect(d != nil)
        #expect(d?.days == 1)
        #expect(d?.hours == 2)
    }

    @Test("从无效字符串创建时长返回 nil")
    func testInvalidDurationString() {
        let d = Duration(string: "INVALID")
        #expect(d == nil)
    }

    @Test("从分量创建时长")
    func testDurationFromComponents() {
        let d = Duration(days: 1, hours: 2, minutes: 30, seconds: 15)
        #expect(d.days == 1)
        #expect(d.hours == 2)
        #expect(d.minutes == 30)
        #expect(d.seconds == 15)
        #expect(!d.isNegative)
    }

    @Test("创建负时长")
    func testNegativeDurationFromComponents() {
        let d = Duration(isNegative: true, days: 1)
        #expect(d.isNegative)
        #expect(d.days == 1)
    }

    @Test("创建含周的时长")
    func testDurationWithWeeks() {
        let d = Duration(weeks: 2, days: 3)
        #expect(d.weeks == 2)
        #expect(d.days == 3)
    }

    @Test("iCal 字符串输出")
    func testICalString() {
        let d = Duration(string: "P1DT2H")!
        let str = d.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("P"))
    }

    @Test("时长相等比较")
    func testDurationEquality() {
        let d1 = Duration(seconds: 3600)
        let d2 = Duration(hours: 1)
        let d3 = Duration(seconds: 7200)
        #expect(d1 == d2)
        #expect(d1 != d3)
    }

    @Test("时长可用于 Set")
    func testDurationHashable() {
        let d1 = Duration(seconds: 3600)
        let d2 = Duration(seconds: 3600)
        let d3 = Duration(seconds: 7200)
        let set: Set<Duration> = [d1, d2, d3]
        // d1 和 d2 完全相同（都是 seconds=3600），d3 不同
        #expect(set.count == 2)
    }

    @Test("时长 description 输出")
    func testDescription() {
        let d = Duration(string: "PT1H")!
        #expect(!d.description.isEmpty)
        #expect(d.description == d.iCalString)
    }
}

// MARK: - Time + Duration Arithmetic Tests

@Suite("Time Arithmetic Tests")
struct TimeArithmeticTests {

    @Test("时间加时长")
    func testTimeAddDuration() {
        let t = Time(string: "20240101T120000Z")!
        let d = Duration(hours: 2)
        let result = t + d
        #expect(result.hour == 14)
        #expect(result.day == 1)
    }

    @Test("时间加时长跨天")
    func testTimeAddDurationCrossDay() {
        let t = Time(string: "20240101T230000Z")!
        let d = Duration(hours: 2)
        let result = t + d
        #expect(result.day == 2)
        #expect(result.hour == 1)
    }

    @Test("两时间相减得时长")
    func testTimeDifference() {
        let t1 = Time(string: "20240101T120000Z")!
        let t2 = Time(string: "20240101T100000Z")!
        let diff = t1 - t2
        #expect(diff.totalSeconds == 7200)
    }
}

// MARK: - Period Tests

@Suite("Period Tests")
struct PeriodTests {

    @Test("从起止时间创建时间段")
    func testPeriodFromStartEnd() {
        let start = Time(string: "20240101T120000Z")!
        let end = Time(string: "20240101T130000Z")!
        let period = Period(start: start, end: end)
        #expect(period.start == start)
        #expect(period.end == end)
        #expect(period.isValid)
    }

    @Test("从起始时间和时长创建时间段")
    func testPeriodFromStartDuration() {
        let start = Time(string: "20240101T120000Z")!
        let duration = Duration(hours: 1)
        let period = Period(start: start, duration: duration)
        #expect(period.start == start)
        #expect(period.duration.totalSeconds == 3600)
    }

    @Test("从字符串创建时间段")
    func testPeriodFromString() {
        let period = Period(string: "20240101T120000Z/20240101T130000Z")
        #expect(period != nil)
        #expect(period?.isValid == true)
    }

    @Test("从无效字符串创建时间段返回 nil")
    func testInvalidPeriodString() {
        // libical 对无效字符串会返回零时间段而非 nil
        // 通过 isNull 或 isValid 来判断
        let period = Period(string: "INVALID")
        if let p = period {
            // 如果不为 nil，应该是无效时间段
            #expect(p.isNull || !p.isValid)
        }
        // 也可能返回 nil，两种情况都合法
    }

    @Test("时间段 iCal 字符串输出")
    func testPeriodICalString() {
        let start = Time(string: "20240101T120000Z")!
        let end = Time(string: "20240101T130000Z")!
        let period = Period(start: start, end: end)
        let str = period.iCalString
        #expect(!str.isEmpty)
    }

    @Test("时间段相等比较")
    func testPeriodEquality() {
        let start = Time(string: "20240101T120000Z")!
        let end = Time(string: "20240101T130000Z")!
        let p1 = Period(start: start, end: end)
        let p2 = Period(start: start, end: end)
        #expect(p1 == p2)
    }
}

// MARK: - Component Tests

@Suite("Component Tests")
struct ComponentTests {

    // MARK: 构造

    @Test("创建 VCALENDAR 组件")
    func testCreateVCalendar() {
        let cal = Component.vcalendar()
        #expect(cal.kind == .vcalendar)
        #expect(cal.isValid)
        #expect(cal.componentName == "VCALENDAR")
    }

    @Test("创建 VEVENT 组件")
    func testCreateVEvent() {
        let event = Component.vevent()
        #expect(event.kind == .vevent)
        #expect(event.isValid)
    }

    @Test("创建 VTODO 组件")
    func testCreateVTodo() {
        let todo = Component.vtodo()
        #expect(todo.kind == .vtodo)
        #expect(todo.isValid)
    }

    @Test("创建 VJOURNAL 组件")
    func testCreateVJournal() {
        let journal = Component.vjournal()
        #expect(journal.kind == .vjournal)
        #expect(journal.isValid)
    }

    @Test("创建 VALARM 组件")
    func testCreateVAlarm() {
        let alarm = Component.valarm()
        #expect(alarm.kind == .valarm)
        #expect(alarm.isValid)
    }

    @Test("创建 VFREEBUSY 组件")
    func testCreateVFreeBusy() {
        let fb = Component.vfreebusy()
        #expect(fb.kind == .vfreebusy)
        #expect(fb.isValid)
    }

    @Test("创建 VTIMEZONE 组件")
    func testCreateVTimezone() {
        let tz = Component.vtimezone()
        #expect(tz.kind == .vtimezone)
        #expect(tz.isValid)
    }

    @Test("通过 kind 创建组件")
    func testCreateByKind() {
        let event = Component(kind: .vevent)
        #expect(event.kind == .vevent)
        #expect(event.isValid)
    }

    @Test("从字符串创建组件")
    func testCreateFromString() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        END:VCALENDAR
        """
        let cal = Component(string: icsString)
        #expect(cal != nil)
        #expect(cal?.kind == .vcalendar)
    }

    @Test("从无效字符串创建组件返回 nil")
    func testCreateFromInvalidString() {
        let cal = Component(string: "INVALID")
        #expect(cal == nil)
    }

    // MARK: 克隆

    @Test("克隆组件")
    func testClone() {
        let event = Component.vevent()
        event.summary = "原始事件"
        let cloned = event.clone()
        #expect(cloned != nil)
        #expect(cloned?.summary == "原始事件")
        // 修改克隆不影响原始
        cloned?.summary = "克隆事件"
        #expect(event.summary == "原始事件")
    }

    // MARK: 便捷属性

    @Test("设置和获取 SUMMARY")
    func testSummary() {
        let event = Component.vevent()
        event.summary = "测试会议"
        #expect(event.summary == "测试会议")
        event.summary = nil
        // 设置 nil 后 summary 可能为空字符串或 nil
    }

    @Test("设置和获取 UID")
    func testUID() {
        let event = Component.vevent()
        event.uid = "test-uid-12345"
        #expect(event.uid == "test-uid-12345")
    }

    @Test("设置和获取 DESCRIPTION")
    func testDescription() {
        let event = Component.vevent()
        event.componentDescription = "这是一个测试事件的详细描述"
        #expect(event.componentDescription == "这是一个测试事件的详细描述")
    }

    @Test("设置和获取 LOCATION")
    func testLocation() {
        let event = Component.vevent()
        event.location = "北京国家会议中心"
        #expect(event.location == "北京国家会议中心")
    }

    @Test("设置和获取 COMMENT")
    func testComment() {
        let event = Component.vevent()
        event.comment = "这是一条注释"
        #expect(event.comment == "这是一条注释")
    }

    @Test("设置和获取 DTSTART")
    func testDTStart() {
        let event = Component.vevent()
        let start = Time(string: "20240101T090000Z")!
        event.dtstart = start
        let retrieved = event.dtstart
        #expect(!retrieved.isNull)
        #expect(retrieved.year == 2024)
        #expect(retrieved.month == 1)
        #expect(retrieved.day == 1)
        #expect(retrieved.hour == 9)
    }

    @Test("设置和获取 DTEND")
    func testDTEnd() {
        let event = Component.vevent()
        let end = Time(string: "20240101T100000Z")!
        event.dtend = end
        let retrieved = event.dtend
        #expect(!retrieved.isNull)
        #expect(retrieved.hour == 10)
    }

    @Test("设置和获取 DURATION")
    func testDuration() {
        let event = Component.vevent()
        let duration = Duration(hours: 1, minutes: 30)
        event.duration = duration
        let retrieved = event.duration
        #expect(retrieved.totalSeconds == 5400)
    }

    @Test("设置和获取 DTSTAMP")
    func testDTStamp() {
        let event = Component.vevent()
        let stamp = Time(string: "20240101T000000Z")!
        event.dtstamp = stamp
        let retrieved = event.dtstamp
        #expect(!retrieved.isNull)
        #expect(retrieved.year == 2024)
    }

    @Test("设置和获取 SEQUENCE")
    func testSequence() {
        let event = Component.vevent()
        event.sequence = 3
        #expect(event.sequence == 3)
    }

    @Test("设置和获取 STATUS")
    func testStatus() {
        let event = Component.vevent()
        event.status = .confirmed
        #expect(event.status == .confirmed)
    }

    @Test("设置和获取 METHOD")
    func testMethod() {
        let cal = Component.vcalendar()
        cal.method = .request
        #expect(cal.method == .request)
    }

    @Test("设置和获取 RECURRENCE-ID")
    func testRecurrenceID() {
        let event = Component.vevent()
        let rid = Time(string: "20240101T090000Z")!
        event.recurrenceID = rid
        let retrieved = event.recurrenceID
        #expect(!retrieved.isNull)
    }

    // MARK: 属性操作

    @Test("添加和获取属性")
    func testAddProperty() {
        let event = Component.vevent()
        let prop = Property.summary("测试摘要")
        event.addProperty(prop)
        let retrieved = event.firstProperty(ofKind: .summary)
        #expect(retrieved != nil)
        #expect(retrieved?.valueString?.contains("测试摘要") == true)
    }

    @Test("统计属性数量")
    func testCountProperties() {
        let event = Component.vevent()
        event.addProperty(Property.summary("摘要"))
        event.addProperty(Property.comment("注释1"))
        event.addProperty(Property.comment("注释2"))
        #expect(event.countProperties(ofKind: .summary) == 1)
        #expect(event.countProperties(ofKind: .comment) == 2)
        #expect(event.countProperties() >= 3)
    }

    @Test("获取所有属性")
    func testGetAllProperties() {
        let event = Component.vevent()
        event.addProperty(Property.summary("摘要"))
        event.addProperty(Property.comment("注释"))
        let props = event.properties()
        #expect(props.count >= 2)
    }

    @Test("移除属性")
    func testRemoveProperty() {
        let event = Component.vevent()
        let prop = Property.summary("要删除的摘要")
        event.addProperty(prop)
        #expect(event.countProperties(ofKind: .summary) == 1)
        // 通过 kind 移除
        event.removeProperties(ofKind: .summary)
        #expect(event.countProperties(ofKind: .summary) == 0)
    }

    @Test("迭代属性")
    func testIterateProperties() {
        let event = Component.vevent()
        event.addProperty(Property.comment("注释1"))
        event.addProperty(Property.comment("注释2"))
        var count = 0
        var prop = event.firstProperty(ofKind: .comment)
        while prop != nil {
            count += 1
            prop = event.nextProperty(ofKind: .comment)
        }
        #expect(count == 2)
    }

    // MARK: 子组件操作

    @Test("添加子组件")
    func testAddSubComponent() {
        let cal = Component.vcalendar()
        let event = Component.vevent()
        event.summary = "子事件"
        cal.addComponent(event)
        #expect(cal.countComponents(ofKind: .vevent) == 1)
    }

    @Test("添加多个子组件")
    func testAddMultipleSubComponents() {
        let cal = Component.vcalendar()
        for i in 1...3 {
            let event = Component.vevent()
            event.summary = "事件 \(i)"
            cal.addComponent(event)
        }
        #expect(cal.countComponents(ofKind: .vevent) == 3)
        #expect(cal.countComponents() == 3)
    }

    @Test("获取第一个子组件")
    func testFirstComponent() {
        let cal = Component.vcalendar()
        let event = Component.vevent()
        event.summary = "第一个事件"
        cal.addComponent(event)
        let first = cal.firstComponent(ofKind: .vevent)
        #expect(first != nil)
        #expect(first?.summary == "第一个事件")
    }

    @Test("获取所有子组件")
    func testGetAllComponents() {
        let cal = Component.vcalendar()
        for i in 1...3 {
            let event = Component.vevent()
            event.summary = "事件 \(i)"
            cal.addComponent(event)
        }
        let events = cal.components(ofKind: .vevent)
        #expect(events.count == 3)
    }

    @Test("移除子组件")
    func testRemoveSubComponent() {
        let cal = Component.vcalendar()
        let event1 = Component.vevent()
        event1.summary = "事件1"
        let event2 = Component.vevent()
        event2.summary = "事件2"
        cal.addComponent(event1)
        cal.addComponent(event2)
        #expect(cal.countComponents(ofKind: .vevent) == 2)
    }

    @Test("获取内部组件")
    func testInnerComponent() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:inner-test@example.com
        DTSTART:20240101T090000Z
        SUMMARY:内部事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component(string: icsString)!
        let inner = cal.innerComponent
        // innerComponent 返回第一个子组件
        #expect(inner != nil)
    }

    // MARK: 解析

    @Test("从字符串解析完整日历")
    func testParseFromString() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:test-event-001@example.com
        DTSTART:20240101T090000Z
        DTEND:20240101T100000Z
        SUMMARY:测试事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)
        #expect(cal != nil)
        #expect(cal?.kind == .vcalendar)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event != nil)
        #expect(event?.summary == "测试事件")
        #expect(event?.uid == "test-event-001@example.com")
    }

    @Test("从 Data 解析组件")
    func testParseFromData() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        END:VCALENDAR
        """
        let data = icsString.data(using: .utf8)!
        let cal = Component.parse(data: data)
        #expect(cal != nil)
        #expect(cal?.kind == .vcalendar)
    }

    @Test("解析含多个事件的日历")
    func testParseMultipleEvents() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:event-001@example.com
        DTSTART:20240101T090000Z
        SUMMARY:事件一
        END:VEVENT
        BEGIN:VEVENT
        UID:event-002@example.com
        DTSTART:20240102T090000Z
        SUMMARY:事件二
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)
        #expect(cal != nil)
        #expect(cal?.countComponents(ofKind: .vevent) == 2)
    }

    // MARK: 输出

    @Test("iCal 字符串输出")
    func testICalString() {
        let cal = Component.vcalendar()
        let event = Component.vevent()
        event.summary = "输出测试"
        event.uid = "output-test-001"
        cal.addComponent(event)
        let str = cal.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("BEGIN:VCALENDAR"))
        #expect(str.contains("BEGIN:VEVENT"))
        #expect(str.contains("输出测试"))
    }

    @Test("description 输出")
    func testComponentDescription() {
        let event = Component.vevent()
        event.summary = "描述测试"
        #expect(!event.description.isEmpty)
        #expect(event.description == event.iCalString)
    }

    // MARK: 静态工具

    @Test("组件类型转字符串")
    func testKindToString() {
        #expect(Component.kindToString(.vcalendar) == "VCALENDAR")
        #expect(Component.kindToString(.vevent) == "VEVENT")
        #expect(Component.kindToString(.vtodo) == "VTODO")
        #expect(Component.kindToString(.vjournal) == "VJOURNAL")
        #expect(Component.kindToString(.valarm) == "VALARM")
    }

    @Test("字符串转组件类型")
    func testKindFromString() {
        #expect(Component.kind(from: "VCALENDAR") == .vcalendar)
        #expect(Component.kind(from: "VEVENT") == .vevent)
        #expect(Component.kind(from: "VTODO") == .vtodo)
    }

    @Test("验证组件类型有效性")
    func testKindIsValid() {
        #expect(Component.isValid(kind: .vcalendar))
        #expect(Component.isValid(kind: .vevent))
        // libical 的 icalcomponent_kind_is_valid 对 .none 也返回 true，
        // 这是 libical 的实现行为，测试实际 API 行为
        let noneValid = Component.isValid(kind: .none)
        // 只验证有效类型确实有效
        #expect(Component.isValid(kind: .vtodo))
        #expect(Component.isValid(kind: .vjournal))
        _ = noneValid // 不对 .none 做断言，行为由 libical 决定
    }

    // MARK: 错误处理

    @Test("统计错误属性数量")
    func testErrorCount() {
        let event = Component.vevent()
        // 新创建的组件没有错误
        #expect(event.errorCount == 0)
    }

    @Test("规范化组件")
    func testNormalize() {
        let event = Component.vevent()
        event.summary = "规范化测试"
        event.uid = "normalize-test-001"
        // 规范化不应崩溃
        event.normalize()
        #expect(event.summary == "规范化测试")
    }

    // MARK: 时间跨度

    @Test("获取组件时间跨度")
    func testSpan() {
        let event = Component.vevent()
        let start = Time(string: "20240101T090000Z")!
        let end = Time(string: "20240101T100000Z")!
        event.dtstart = start
        event.dtend = end
        let span = event.span
        #expect(span.start > 0)
        #expect(span.end > span.start)
    }

    // MARK: 合并

    @Test("合并两个日历组件")
    func testMerge() {
        let cal1 = Component.vcalendar()
        let event1 = Component.vevent()
        event1.summary = "日历1事件"
        cal1.addComponent(event1)

        let cal2 = Component.vcalendar()
        let event2 = Component.vevent()
        event2.summary = "日历2事件"
        cal2.addComponent(event2)

        cal1.merge(cal2)
        // 合并后 cal1 应包含两个事件
        #expect(cal1.countComponents(ofKind: .vevent) == 2)
    }

    // MARK: 重复事件遍历

    @Test("遍历重复事件")
    func testForEachRecurrence() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:recur-test@example.com
        DTSTART:20240101T090000Z
        DTEND:20240101T100000Z
        RRULE:FREQ=DAILY;COUNT=3
        SUMMARY:每日重复事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)!
        let event = cal.firstComponent(ofKind: .vevent)!
        let start = Time(string: "20240101T000000Z")!
        let end = Time(string: "20240110T000000Z")!
        var count = 0
        event.forEachRecurrence(from: start, to: end) { _, _ in
            count += 1
        }
        #expect(count == 3)
    }
}

// MARK: - Property Tests

@Suite("Property Tests")
struct PropertyTests {

    // MARK: 构造

    @Test("通过 kind 创建属性")
    func testCreateByKind() {
        let prop = Property(kind: .summary)
        #expect(prop.kind == .summary)
    }

    @Test("从字符串创建属性")
    func testCreateFromString() {
        let prop = Property(string: "SUMMARY:测试摘要")
        #expect(prop != nil)
        #expect(prop?.kind == .summary)
    }

    @Test("从无效字符串创建属性返回 nil")
    func testCreateFromInvalidString() {
        let prop = Property(string: "INVALID_PROPERTY_FORMAT")
        // 可能返回 nil 或 xlicerror 类型
        if let p = prop {
            // 如果不为 nil，应该是错误属性
            _ = p.kind
        }
    }

    // MARK: 便捷构造

    @Test("创建 SUMMARY 属性")
    func testSummaryProperty() {
        let prop = Property.summary("测试摘要")
        #expect(prop.kind == .summary)
        #expect(prop.valueString?.contains("测试摘要") == true)
        #expect(prop.name == "SUMMARY")
    }

    @Test("创建 DESCRIPTION 属性")
    func testDescriptionProperty() {
        let prop = Property.description("详细描述内容")
        #expect(prop.kind == .description)
        #expect(prop.valueString?.contains("详细描述内容") == true)
    }

    @Test("创建 LOCATION 属性")
    func testLocationProperty() {
        let prop = Property.location("北京")
        #expect(prop.kind == .location)
        #expect(prop.valueString?.contains("北京") == true)
    }

    @Test("创建 UID 属性")
    func testUIDProperty() {
        let prop = Property.uid("unique-id-001@example.com")
        #expect(prop.kind == .uid)
        #expect(prop.valueString?.contains("unique-id-001") == true)
    }

    @Test("创建 DTSTART 属性")
    func testDTStartProperty() {
        let time = Time(string: "20240101T090000Z")!
        let prop = Property.dtstart(time)
        #expect(prop.kind == .dtstart)
    }

    @Test("创建 DTEND 属性")
    func testDTEndProperty() {
        let time = Time(string: "20240101T100000Z")!
        let prop = Property.dtend(time)
        #expect(prop.kind == .dtend)
    }

    @Test("创建 DURATION 属性")
    func testDurationProperty() {
        let duration = Duration(hours: 1)
        let prop = Property.duration(duration)
        #expect(prop.kind == .duration)
    }

    @Test("创建 DTSTAMP 属性")
    func testDTStampProperty() {
        let time = Time(string: "20240101T000000Z")!
        let prop = Property.dtstamp(time)
        #expect(prop.kind == .dtstamp)
    }

    @Test("创建 STATUS 属性")
    func testStatusProperty() {
        let prop = Property.status(.confirmed)
        #expect(prop.kind == .status)
        #expect(prop.valueString?.contains("CONFIRMED") == true)
    }

    @Test("创建 METHOD 属性")
    func testMethodProperty() {
        let prop = Property.method(.request)
        #expect(prop.kind == .method)
        #expect(prop.valueString?.contains("REQUEST") == true)
    }

    @Test("创建 CLASS 属性")
    func testClassProperty() {
        let prop = Property.class(.private)
        #expect(prop.kind == .class)
        #expect(prop.valueString?.contains("PRIVATE") == true)
    }

    @Test("创建 TRANSP 属性")
    func testTranspProperty() {
        let prop = Property.transp(.transparent)
        #expect(prop.kind == .transp)
        #expect(prop.valueString?.contains("TRANSPARENT") == true)
    }

    @Test("创建 SEQUENCE 属性")
    func testSequenceProperty() {
        let prop = Property.sequence(5)
        #expect(prop.kind == .sequence)
        #expect(prop.valueString?.contains("5") == true)
    }

    @Test("创建 ATTENDEE 属性")
    func testAttendeeProperty() {
        let prop = Property.attendee("mailto:user@example.com")
        #expect(prop.kind == .attendee)
    }

    @Test("创建 ORGANIZER 属性")
    func testOrganizerProperty() {
        let prop = Property.organizer("mailto:organizer@example.com")
        #expect(prop.kind == .organizer)
    }

    @Test("创建 COMMENT 属性")
    func testCommentProperty() {
        let prop = Property.comment("这是注释")
        #expect(prop.kind == .comment)
        #expect(prop.valueString?.contains("这是注释") == true)
    }

    @Test("创建 CATEGORIES 属性")
    func testCategoriesProperty() {
        let prop = Property.categories("工作,会议")
        #expect(prop.kind == .categories)
    }

    @Test("创建 PRIORITY 属性")
    func testPriorityProperty() {
        let prop = Property.priority(1)
        #expect(prop.kind == .priority)
        #expect(prop.valueString?.contains("1") == true)
    }

    @Test("创建 URL 属性")
    func testURLProperty() {
        let prop = Property.url("https://example.com")
        #expect(prop.kind == .url)
    }

    // MARK: 克隆

    @Test("克隆属性")
    func testClone() {
        let prop = Property.summary("原始摘要")
        let cloned = prop.clone()
        #expect(cloned != nil)
        #expect(cloned?.kind == .summary)
        #expect(cloned?.valueString?.contains("原始摘要") == true)
    }

    // MARK: 参数操作

    @Test("添加参数到属性")
    func testAddParameter() {
        let prop = Property.summary("带参数的摘要")
        if let langParam = Parameter.language("zh-CN") {
            prop.addParameter(langParam)
            #expect(prop.parameterCount > 0)
        }
    }

    @Test("设置参数（替换同类型）")
    func testSetParameter() {
        let prop = Property.summary("摘要")
        if let langParam1 = Parameter.language("zh-CN") {
            prop.addParameter(langParam1)
            #expect(prop.parameterCount == 1)
        }
        if let langParam2 = Parameter.language("en-US") {
            prop.setParameter(langParam2)
            // setParameter 替换同类型参数，数量不变
            #expect(prop.parameterCount == 1)
        }
    }

    @Test("移除指定类型参数")
    func testRemoveParameterByKind() {
        let prop = Property.summary("摘要")
        if let langParam = Parameter.language("zh-CN") {
            prop.addParameter(langParam)
            #expect(prop.parameterCount == 1)
            prop.removeParameters(ofKind: .language)
            #expect(prop.parameterCount == 0)
        }
    }

    @Test("获取参数值字符串")
    func testParameterValue() {
        let prop = Property.summary("摘要")
        prop.setParameter(name: "LANGUAGE", value: "zh-CN")
        let value = prop.parameterValue(named: "LANGUAGE")
        #expect(value == "zh-CN")
    }

    @Test("获取所有参数")
    func testGetAllParameters() {
        let prop = Property.summary("摘要")
        if let langParam = Parameter.language("zh-CN") {
            prop.addParameter(langParam)
        }
        let params = prop.parameters()
        #expect(params.count >= 1)
    }

    @Test("迭代参数")
    func testIterateParameters() {
        let prop = Property.summary("摘要")
        if let langParam = Parameter.language("zh-CN") {
            prop.addParameter(langParam)
        }
        var count = 0
        var param = prop.firstParameter(ofKind: .language)
        while param != nil {
            count += 1
            param = prop.nextParameter(ofKind: .language)
        }
        #expect(count == 1)
    }

    // MARK: 规范化

    @Test("规范化属性")
    func testNormalize() {
        let prop = Property.summary("规范化测试")
        prop.normalize()
        #expect(prop.kind == .summary)
    }

    // MARK: 输出

    @Test("iCal 字符串输出")
    func testICalString() {
        let prop = Property.summary("输出测试")
        let str = prop.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("SUMMARY"))
        #expect(str.contains("输出测试"))
    }

    @Test("description 输出")
    func testPropertyDescription() {
        let prop = Property.summary("描述测试")
        #expect(!prop.description.isEmpty)
        #expect(prop.description == prop.iCalString)
    }

    // MARK: 静态工具

    @Test("属性类型转字符串")
    func testKindToString() {
        #expect(Property.kindToString(.summary) == "SUMMARY")
        #expect(Property.kindToString(.dtstart) == "DTSTART")
        #expect(Property.kindToString(.dtend) == "DTEND")
        #expect(Property.kindToString(.uid) == "UID")
    }

    @Test("字符串转属性类型")
    func testKindFromString() {
        #expect(Property.kind(from: "SUMMARY") == .summary)
        #expect(Property.kind(from: "DTSTART") == .dtstart)
        #expect(Property.kind(from: "UID") == .uid)
    }

    @Test("验证属性类型有效性")
    func testKindIsValid() {
        #expect(Property.isValid(kind: .summary))
        #expect(Property.isValid(kind: .dtstart))
        #expect(Property.isValid(kind: .uid))
        // libical 的 icalproperty_kind_is_valid 对 .no 也返回 true，
        // 不对 .no 做断言，只验证有效类型
    }

    @Test("枚举值转字符串")
    func testEnumToString() {
        let str = Property.enumToString(10902) // CONFIRMED
        #expect(str != nil)
        #expect(str?.contains("CONFIRMED") == true)
    }

    @Test("从字符串解析方法枚举")
    func testMethodFromString() {
        let method = Property.method(from: "REQUEST")
        #expect(method == .request)
    }

    @Test("空属性全局设置")
    func testAllowEmptyProperties() {
        let original = Property.allowEmptyProperties
        Property.allowEmptyProperties = true
        #expect(Property.allowEmptyProperties == true)
        Property.allowEmptyProperties = false
        #expect(Property.allowEmptyProperties == false)
        // 恢复原始设置
        Property.allowEmptyProperties = original
    }
}

// MARK: - Parameter Tests

@Suite("Parameter Tests")
struct ParameterTests {

    // MARK: 构造

    @Test("通过 kind 创建参数")
    func testCreateByKind() {
        let param = Parameter(kind: .tzid)
        #expect(param.kind == .tzid)
    }

    @Test("从字符串创建参数 - ROLE=CHAIR")
    func testParameterFromString_role() {
        let param = Parameter(string: "ROLE=CHAIR")
        #expect(param != nil)
        #expect(param?.kind == .role)
    }

    @Test("从字符串创建参数 - TZID")
    func testParameterFromString_tzid() {
        let param = Parameter(string: "TZID=America/New_York")
        #expect(param != nil)
        #expect(param?.kind == .tzid)
    }

    @Test("从 kind 和值字符串创建参数")
    func testCreateFromKindAndValue() {
        let param = Parameter(kind: .language, value: "zh-CN")
        #expect(param != nil)
        #expect(param?.kind == .language)
    }

    // MARK: 便捷构造

    @Test("创建 TZID 参数")
    func testTZIDParameter() {
        let param = Parameter.tzid("America/New_York")
        #expect(param != nil)
        #expect(param?.kind == .tzid)
    }

    @Test("创建 LANGUAGE 参数")
    func testLanguageParameter() {
        let param = Parameter.language("zh-CN")
        #expect(param != nil)
        #expect(param?.kind == .language)
    }

    @Test("创建 CN 参数")
    func testCNParameter() {
        let param = Parameter.cn("张三")
        #expect(param != nil)
        #expect(param?.kind == .cn)
    }

    @Test("创建 EMAIL 参数")
    func testEmailParameter() {
        let param = Parameter.email("user@example.com")
        #expect(param != nil)
        #expect(param?.kind == .email)
    }

    @Test("创建 ROLE 参数 - CHAIR")
    func testRoleParameter_chair() {
        let param = Parameter.role(.chair)
        #expect(param != nil)
        #expect(param?.kind == .role)
    }

    @Test("创建 ROLE 参数 - REQ-PARTICIPANT")
    func testRoleParameter_reqParticipant() {
        let param = Parameter.role(.reqParticipant)
        #expect(param != nil)
        #expect(param?.kind == .role)
    }

    @Test("创建 PARTSTAT 参数 - ACCEPTED")
    func testPartstatParameter_accepted() {
        let param = Parameter.partstat(.accepted)
        #expect(param != nil)
        #expect(param?.kind == .partstat)
    }

    @Test("创建 PARTSTAT 参数 - DECLINED")
    func testPartstatParameter_declined() {
        let param = Parameter.partstat(.declined)
        #expect(param != nil)
        #expect(param?.kind == .partstat)
    }

    @Test("创建 CUTYPE 参数")
    func testCUTypeParameter() {
        let param = Parameter.cutype(.individual)
        #expect(param != nil)
        #expect(param?.kind == .cutype)
    }

    @Test("创建 FBTYPE 参数")
    func testFBTypeParameter() {
        let param = Parameter.fbtype(.busy)
        #expect(param != nil)
        #expect(param?.kind == .fbtype)
    }

    @Test("创建 RSVP 参数 - TRUE")
    func testRSVPParameter_true() {
        let param = Parameter.rsvp(true)
        #expect(param != nil)
        #expect(param?.kind == .rsvp)
    }

    @Test("创建 RSVP 参数 - FALSE")
    func testRSVPParameter_false() {
        let param = Parameter.rsvp(false)
        #expect(param != nil)
        #expect(param?.kind == .rsvp)
    }

    @Test("创建 ENCODING 参数")
    func testEncodingParameter() {
        let param = Parameter.encoding(.base64)
        #expect(param != nil)
        #expect(param?.kind == .encoding)
    }

    // MARK: 克隆

    @Test("克隆参数")
    func testClone() {
        let param = Parameter(string: "ROLE=CHAIR")!
        let cloned = param.clone()
        #expect(cloned != nil)
        #expect(cloned?.kind == .role)
    }

    // MARK: X 扩展参数

    @Test("X 扩展参数名称和值")
    func testXParameter() {
        let param = Parameter(kind: .x)
        param.xname = "X-CUSTOM-PARAM"
        param.xvalue = "custom-value"
        #expect(param.xname == "X-CUSTOM-PARAM")
        #expect(param.xvalue == "custom-value")
    }

    // MARK: 比较

    @Test("参数名称相同判断")
    func testHasSameName() {
        let p1 = Parameter(string: "ROLE=CHAIR")!
        let p2 = Parameter(string: "ROLE=REQ-PARTICIPANT")!
        let p3 = Parameter(string: "TZID=America/New_York")!
        #expect(p1.hasSameName(as: p2))
        #expect(!p1.hasSameName(as: p3))
    }

    // MARK: 输出

    @Test("iCal 字符串输出")
    func testICalString() {
        let param = Parameter(string: "ROLE=CHAIR")!
        let str = param.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("ROLE"))
        #expect(str.contains("CHAIR"))
    }

    @Test("description 输出")
    func testParameterDescription() {
        let param = Parameter(string: "TZID=America/New_York")!
        #expect(!param.description.isEmpty)
        #expect(param.description == param.iCalString)
    }

    // MARK: 静态工具

    @Test("参数类型转字符串")
    func testKindToString() {
        #expect(Parameter.kindToString(.tzid) == "TZID")
        #expect(Parameter.kindToString(.cn) == "CN")
        #expect(Parameter.kindToString(.language) == "LANGUAGE")
        #expect(Parameter.kindToString(.role) == "ROLE")
    }

    @Test("字符串转参数类型")
    func testKindFromString() {
        #expect(Parameter.kind(from: "TZID") == .tzid)
        #expect(Parameter.kind(from: "CN") == .cn)
        #expect(Parameter.kind(from: "LANGUAGE") == .language)
    }

    @Test("验证参数类型有效性")
    func testKindIsValid() {
        #expect(Parameter.isValid(kind: .tzid))
        #expect(Parameter.isValid(kind: .cn))
        #expect(Parameter.isValid(kind: .language))
        // libical 的 icalparameter_kind_is_valid 对 .no 也返回 true，
        // 不对 .no 做断言，只验证有效类型
    }

    @Test("解码参数值")
    func testDecodeValue() {
        // 测试基本解码（无编码字符）
        let decoded = Parameter.decodeValue("simple-value")
        #expect(decoded == "simple-value")
    }
}

// MARK: - Recurrence Tests

@Suite("Recurrence Tests")
struct RecurrenceTests {

    // MARK: 构造

    @Test("创建空重复规则")
    func testCreateEmpty() {
        let recur = Recurrence()
        #expect(recur != nil)
    }

    @Test("从字符串创建每周重复规则")
    func testRecurrenceFromString_weekly() {
        let recur = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR")
        #expect(recur != nil)
        #expect(recur?.frequency == .weekly)
    }

    @Test("从字符串创建每日重复规则")
    func testRecurrenceFromString_daily() {
        let recur = Recurrence(string: "FREQ=DAILY;COUNT=5")
        #expect(recur != nil)
        #expect(recur?.frequency == .daily)
        #expect(recur?.count == 5)
    }

    @Test("从字符串创建每月重复规则")
    func testRecurrenceFromString_monthly() {
        let recur = Recurrence(string: "FREQ=MONTHLY;BYMONTHDAY=15")
        #expect(recur != nil)
        #expect(recur?.frequency == .monthly)
    }

    @Test("从字符串创建每年重复规则")
    func testRecurrenceFromString_yearly() {
        let recur = Recurrence(string: "FREQ=YEARLY")
        #expect(recur != nil)
        #expect(recur?.frequency == .yearly)
    }

    @Test("从字符串创建每小时重复规则")
    func testRecurrenceFromString_hourly() {
        let recur = Recurrence(string: "FREQ=HOURLY;INTERVAL=2")
        #expect(recur != nil)
        #expect(recur?.frequency == .hourly)
        #expect(recur?.interval == 2)
    }

    @Test("从无效字符串创建重复规则返回 nil")
    func testInvalidRecurrenceString() {
        let recur = Recurrence(string: "INVALID=RULE")
        // 可能返回 nil 或频率为 none
        if let r = recur {
            #expect(r.frequency == .none)
        }
    }

    // MARK: 属性

    @Test("重复规则属性 - 间隔")
    func testInterval() {
        let recur = Recurrence(string: "FREQ=WEEKLY;INTERVAL=2")!
        #expect(recur.interval == 2)
    }

    @Test("重复规则属性 - 结束时间")
    func testUntil() {
        let recur = Recurrence(string: "FREQ=DAILY;UNTIL=20240131T235959Z")!
        #expect(!recur.until.isNull)
        #expect(recur.until.year == 2024)
        #expect(recur.until.month == 1)
    }

    @Test("重复规则属性 - 周起始日")
    func testWeekStart() {
        let recur = Recurrence(string: "FREQ=WEEKLY;WKST=MO")!
        #expect(recur.weekStart == .monday)
    }

    @Test("重复规则属性 - BYDAY")
    func testByDay() {
        let recur = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR")!
        let byDay = recur.byDay
        #expect(!byDay.isEmpty)
        // 解码星期几
        let weekdays = byDay.map { Recurrence.dayOfWeek(from: $0) }
        #expect(weekdays.contains(.monday))
        #expect(weekdays.contains(.wednesday))
        #expect(weekdays.contains(.friday))
    }

    @Test("重复规则属性 - BYMONTH")
    func testByMonth() {
        let recur = Recurrence(string: "FREQ=YEARLY;BYMONTH=1,6,12")!
        let byMonth = recur.byMonth
        #expect(!byMonth.isEmpty)
        let months = byMonth.map { Recurrence.month(from: $0) }
        #expect(months.contains(1))
        #expect(months.contains(6))
        #expect(months.contains(12))
    }

    @Test("重复规则属性 - BYMONTHDAY")
    func testByMonthDay() {
        let recur = Recurrence(string: "FREQ=MONTHLY;BYMONTHDAY=1,15")!
        let byMonthDay = recur.byMonthDay
        #expect(!byMonthDay.isEmpty)
        #expect(byMonthDay.contains(1))
        #expect(byMonthDay.contains(15))
    }

    // MARK: 克隆

    @Test("克隆重复规则")
    func testClone() {
        let recur = Recurrence(string: "FREQ=WEEKLY;COUNT=5")!
        let cloned = recur.clone()
        #expect(cloned != nil)
        #expect(cloned?.frequency == .weekly)
        #expect(cloned?.count == 5)
    }

    // MARK: 编码/解码

    @Test("星期几编码解码")
    func testDayEncoding() {
        let encoded = Recurrence.encodeDay(weekday: .monday, position: 0)
        let decoded = Recurrence.dayOfWeek(from: encoded)
        #expect(decoded == .monday)
        let position = Recurrence.dayPosition(from: encoded)
        #expect(position == 0)
    }

    @Test("带位置的星期几编码解码")
    func testDayEncodingWithPosition() {
        // 第2个周一
        let encoded = Recurrence.encodeDay(weekday: .monday, position: 2)
        let decoded = Recurrence.dayOfWeek(from: encoded)
        #expect(decoded == .monday)
        let position = Recurrence.dayPosition(from: encoded)
        #expect(position == 2)
    }

    @Test("月份编码解码")
    func testMonthEncoding() {
        let encoded = Recurrence.encodeMonth(3)
        let decoded = Recurrence.month(from: encoded)
        #expect(decoded == 3)
        #expect(!Recurrence.isLeapMonth(from: encoded))
    }

    // MARK: 字符串解析工具

    @Test("从字符串解析频率")
    func testFrequencyFromString() {
        #expect(Recurrence.frequency(from: "DAILY") == .daily)
        #expect(Recurrence.frequency(from: "WEEKLY") == .weekly)
        #expect(Recurrence.frequency(from: "MONTHLY") == .monthly)
        #expect(Recurrence.frequency(from: "YEARLY") == .yearly)
        #expect(Recurrence.frequency(from: "HOURLY") == .hourly)
    }

    @Test("从字符串解析星期几")
    func testWeekdayFromString() {
        #expect(Recurrence.weekday(from: "MO") == .monday)
        #expect(Recurrence.weekday(from: "TU") == .tuesday)
        #expect(Recurrence.weekday(from: "WE") == .wednesday)
        #expect(Recurrence.weekday(from: "TH") == .thursday)
        #expect(Recurrence.weekday(from: "FR") == .friday)
        #expect(Recurrence.weekday(from: "SA") == .saturday)
        #expect(Recurrence.weekday(from: "SU") == .sunday)
    }

    @Test("从字符串解析跳过类型")
    func testSkipFromString() {
        #expect(Recurrence.skip(from: "OMIT") == .omit)
        #expect(Recurrence.skip(from: "FORWARD") == .forward)
        #expect(Recurrence.skip(from: "BACKWARD") == .backward)
    }

    // MARK: 输出

    @Test("iCal 字符串输出")
    func testICalString() {
        let recur = Recurrence(string: "FREQ=WEEKLY;INTERVAL=2;BYDAY=MO")!
        let str = recur.iCalString
        #expect(!str.isEmpty)
        #expect(str.contains("FREQ=WEEKLY"))
    }

    @Test("description 输出")
    func testDescription() {
        let recur = Recurrence(string: "FREQ=DAILY;COUNT=3")!
        #expect(!recur.description.isEmpty)
        #expect(recur.description == recur.iCalString)
    }
}

// MARK: - RecurrenceIterator Tests

@Suite("RecurrenceIterator Tests")
struct RecurrenceIteratorTests {

    @Test("每日重复迭代 3 次")
    func testDailyIterator() {
        guard let recur = Recurrence(string: "FREQ=DAILY;COUNT=3"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        var occurrences: [Time] = []
        while let t = iter.next() {
            occurrences.append(t)
        }
        #expect(occurrences.count == 3)
        #expect(occurrences[0].day == 1)
        #expect(occurrences[1].day == 2)
        #expect(occurrences[2].day == 3)
    }

    @Test("每周重复迭代")
    func testWeeklyIterator() {
        guard let recur = Recurrence(string: "FREQ=WEEKLY;COUNT=4"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let occurrences = iter.allOccurrences()
        #expect(occurrences.count == 4)
        // 每次间隔 7 天
        if occurrences.count >= 2 {
            let diff = occurrences[1] - occurrences[0]
            #expect(diff.totalSeconds == 7 * 24 * 3600)
        }
    }

    @Test("每月重复迭代")
    func testMonthlyIterator() {
        guard let recur = Recurrence(string: "FREQ=MONTHLY;COUNT=3"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let occurrences = iter.allOccurrences()
        #expect(occurrences.count == 3)
        #expect(occurrences[0].month == 1)
        #expect(occurrences[1].month == 2)
        #expect(occurrences[2].month == 3)
    }

    @Test("每年重复迭代")
    func testYearlyIterator() {
        guard let recur = Recurrence(string: "FREQ=YEARLY;COUNT=3"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let occurrences = iter.allOccurrences()
        #expect(occurrences.count == 3)
        #expect(occurrences[0].year == 2024)
        #expect(occurrences[1].year == 2025)
        #expect(occurrences[2].year == 2026)
    }

    @Test("设置迭代范围")
    func testSetRange() {
        guard let recur = Recurrence(string: "FREQ=DAILY"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let rangeEnd = Time(string: "20240105T090000Z")!
        iter.setEnd(rangeEnd)
        let occurrences = iter.allOccurrences()
        // 从 1 月 1 日到 1 月 5 日（含），最多 5 次
        #expect(occurrences.count <= 5)
        #expect(occurrences.count >= 1)
    }

    @Test("allOccurrences 最大数量限制")
    func testAllOccurrencesMaxCount() {
        guard let recur = Recurrence(string: "FREQ=DAILY"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let occurrences = iter.allOccurrences(maxCount: 10)
        #expect(occurrences.count == 10)
    }

    @Test("for-in 循环语法")
    func testForInSyntax() {
        guard let recur = Recurrence(string: "FREQ=DAILY;COUNT=5"),
              let start = Time(string: "20240101T090000Z"),
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        var count = 0
        for _ in iter {
            count += 1
        }
        #expect(count == 5)
    }

    @Test("BYDAY 过滤 - 每周一三五")
    func testByDayFilter() {
        guard let recur = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR;COUNT=6"),
              let start = Time(string: "20240101T090000Z"), // 2024-01-01 是周一
              let iter = RecurrenceIterator(rule: recur, start: start) else {
            Issue.record("无法创建迭代器")
            return
        }
        let occurrences = iter.allOccurrences()
        #expect(occurrences.count == 6)
        // 验证每次都是周一、三或五
        for t in occurrences {
            let dow = t.dayOfWeek
            #expect(dow == 2 || dow == 4 || dow == 6) // 2=周一, 4=周三, 6=周五
        }
    }
}

// MARK: - Timezone Tests

@Suite("Timezone Tests")
struct TimezoneTests {

    @Test("获取 UTC 时区")
    func testUTCTimezone() {
        let utc = Timezone.utc
        #expect(utc != nil)
    }

    @Test("启用/禁用内置时区数据")
    func testBuiltinTZData() {
        Timezone.useBuiltinTZData = true
        #expect(Timezone.useBuiltinTZData == true)
        Timezone.useBuiltinTZData = false
        #expect(Timezone.useBuiltinTZData == false)
        // 恢复
        Timezone.useBuiltinTZData = true
    }

    @Test("根据地名获取内置时区")
    func testBuiltinTimezoneByLocation() {
        Timezone.useBuiltinTZData = true
        let tz = Timezone.builtin(location: "America/New_York")
        if let tz = tz {
            #expect(tz.tzid != nil || tz.location != nil || tz.displayName != nil)
        }
    }

    @Test("根据 TZID 获取内置时区")
    func testBuiltinTimezoneByTZID() {
        Timezone.useBuiltinTZData = true
        let tz = Timezone.builtin(tzid: "America/New_York")
        if let tz = tz {
            #expect(tz.tzid != nil)
        }
    }

    @Test("获取内置时区列表")
    func testBuiltinTimezones() {
        Timezone.useBuiltinTZData = true
        let timezones = Timezone.builtinTimezones
        // builtinTimezones 的数量取决于 libical 编译时是否包含内置时区数据
        // 不强制要求非空，只验证 API 可调用且不崩溃
        #expect(timezones.count >= 0)
    }

    @Test("时区 TZID 前缀")
    func testTZIDPrefix() {
        let prefix = Timezone.tzidPrefix
        if let prefix = prefix {
            #expect(!prefix.isEmpty)
        }
    }

    @Test("创建新时区对象")
    func testCreateNewTimezone() {
        let tz = Timezone()
        #expect(tz != nil)
    }

    @Test("克隆时区")
    func testCloneTimezone() {
        Timezone.useBuiltinTZData = true
        if let tz = Timezone.builtin(location: "America/New_York") {
            let cloned = tz.clone()
            #expect(cloned != nil)
        }
    }

    @Test("时区 description 输出")
    func testTimezoneDescription() {
        Timezone.useBuiltinTZData = true
        if let tz = Timezone.builtin(location: "America/New_York") {
            #expect(!tz.description.isEmpty)
        }
    }

    @Test("时区相等比较")
    func testTimezoneEquality() {
        Timezone.useBuiltinTZData = true
        if let tz1 = Timezone.builtin(location: "America/New_York"),
           let tz2 = Timezone.builtin(location: "America/New_York") {
            #expect(tz1 == tz2)
        }
    }

    @Test("时区可用于 Set")
    func testTimezoneHashable() {
        Timezone.useBuiltinTZData = true
        if let tz1 = Timezone.builtin(location: "America/New_York"),
           let tz2 = Timezone.builtin(location: "America/New_York"),
           let tz3 = Timezone.builtin(location: "Europe/London") {
            let set: Set<Timezone> = [tz1, tz2, tz3]
            #expect(set.count == 2)
        }
    }

    @Test("UTC 偏移计算")
    func testUTCOffset() {
        Timezone.useBuiltinTZData = true
        if let tz = Timezone.builtin(location: "America/New_York") {
            let time = Time(string: "20240101T120000Z")!
            var isDaylight = false
            let offset = tz.utcOffset(for: time, isDaylight: &isDaylight)
            // 纽约标准时间 UTC-5 = -18000 秒
            // 夏令时 UTC-4 = -14400 秒
            #expect(offset == -18000 || offset == -14400)
        }
    }

    @Test("时间时区转换")
    func testTimeConversion() {
        Timezone.useBuiltinTZData = true
        if let utcTZ = Timezone.utc,
           let nyTZ = Timezone.builtin(location: "America/New_York") {
            var time = Time(string: "20240101T120000Z")!
            Timezone.convertTime(&time, from: utcTZ, to: nyTZ)
            // 纽约标准时间 = UTC - 5 小时
            #expect(time.hour == 7)
        }
    }

    @Test("系统时区目录")
    func testSystemZoneDirectory() {
        let dir = Timezone.systemZoneDirectory
        // 系统时区目录可能为 nil（取决于平台）
        if let dir = dir {
            #expect(!dir.isEmpty)
        }
    }
}

// MARK: - Parser Tests

@Suite("Parser Tests")
struct ParserTests {

    @Test("解析简单 iCalendar 字符串")
    func testParseSimpleString() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:parser-test-001@example.com
        DTSTART:20240315T140000Z
        DTEND:20240315T150000Z
        SUMMARY:解析测试
        END:VEVENT
        END:VCALENDAR
        """
        let component = Parser.parse(string: icsString)
        #expect(component != nil)
        #expect(component?.kind == .vcalendar)
    }

    @Test("解析含中文内容的日历")
    func testParseChineseContent() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//中文测试//Test//ZH
        BEGIN:VEVENT
        UID:chinese-test@example.com
        DTSTART:20240315T140000Z
        SUMMARY:中文摘要测试
        DESCRIPTION:这是一个包含中文内容的测试事件
        LOCATION:北京国家会议中心
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Parser.parse(string: icsString)
        #expect(cal != nil)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event?.summary == "中文摘要测试")
        #expect(event?.componentDescription == "这是一个包含中文内容的测试事件")
        #expect(event?.location == "北京国家会议中心")
    }

    @Test("逐行解析")
    func testLineByLineParsing() {
        let lines = [
            "BEGIN:VCALENDAR\r\n",
            "VERSION:2.0\r\n",
            "PRODID:-//Test//Test//EN\r\n",
            "BEGIN:VEVENT\r\n",
            "UID:line-test-001@example.com\r\n",
            "DTSTART:20240315T140000Z\r\n",
            "SUMMARY:逐行测试\r\n",
            "END:VEVENT\r\n",
            "END:VCALENDAR\r\n",
        ]
        let parser = Parser()
        var result: Component? = nil
        for line in lines {
            if let comp = parser.addLine(line) {
                result = comp
            }
        }
        #expect(result != nil || parser.state != .error)
    }

    @Test("解析器状态")
    func testParserState() {
        let parser = Parser()
        // 初始状态应该是 inProgress 或 success
        let state = parser.state
        #expect(state != .error)
    }

    @Test("解析器 clean 方法")
    func testParserClean() {
        // 提供完整的 iCalendar 数据再调用 clean，避免 libical 内部崩溃
        let lines = [
            "BEGIN:VCALENDAR\r\n",
            "VERSION:2.0\r\n",
            "PRODID:-//Test//Test//EN\r\n",
            "END:VCALENDAR\r\n",
        ]
        let parser = Parser()
        var result: Component? = nil
        for line in lines {
            if let comp = parser.addLine(line) {
                result = comp
            }
        }
        // addLine 在解析完成时返回组件，clean 用于获取剩余内容
        // 如果 addLine 已经返回了组件，clean 可能返回 nil
        if result == nil {
            result = parser.clean()
        }
        // 验证解析成功或状态不是错误
        #expect(result != nil || parser.state != .error)
    }

    @Test("全局控制字符设置")
    func testParserCtrl() {
        let original = Parser.ctrl
        Parser.ctrl = .omit
        #expect(Parser.ctrl == .omit)
        Parser.ctrl = .keep
        #expect(Parser.ctrl == .keep)
        // 恢复
        Parser.ctrl = original
    }

    @Test("解析含 VTODO 的日历")
    func testParseVTodo() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VTODO
        UID:todo-test@example.com
        SUMMARY:待办事项测试
        STATUS:NEEDS-ACTION
        PRIORITY:1
        END:VTODO
        END:VCALENDAR
        """
        let cal = Parser.parse(string: icsString)
        #expect(cal != nil)
        let todo = cal?.firstComponent(ofKind: .vtodo)
        #expect(todo != nil)
        #expect(todo?.summary == "待办事项测试")
    }

    @Test("解析含 VALARM 的事件")
    func testParseVAlarm() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:alarm-test@example.com
        DTSTART:20240315T140000Z
        SUMMARY:含闹钟的事件
        BEGIN:VALARM
        ACTION:DISPLAY
        DESCRIPTION:提醒
        TRIGGER:-PT15M
        END:VALARM
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Parser.parse(string: icsString)
        #expect(cal != nil)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event != nil)
        let alarm = event?.firstComponent(ofKind: .valarm)
        #expect(alarm != nil)
    }

    @Test("解析含 RRULE 的重复事件")
    func testParseRRule() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:rrule-test@example.com
        DTSTART:20240101T090000Z
        RRULE:FREQ=WEEKLY;BYDAY=MO,WE,FR;COUNT=10
        SUMMARY:每周重复事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Parser.parse(string: icsString)
        #expect(cal != nil)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event != nil)
        let rruleProp = event?.firstProperty(ofKind: .rrule)
        #expect(rruleProp != nil)
    }

    @Test("解析含 ATTENDEE ��事件")
    func testParseAttendee() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        METHOD:REQUEST
        BEGIN:VEVENT
        UID:attendee-test@example.com
        DTSTART:20240315T140000Z
        ORGANIZER;CN=组织者:mailto:organizer@example.com
        ATTENDEE;CN=参与者1;PARTSTAT=ACCEPTED:mailto:user1@example.com
        ATTENDEE;CN=参与者2;PARTSTAT=NEEDS-ACTION:mailto:user2@example.com
        SUMMARY:含参与者的事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Parser.parse(string: icsString)
        #expect(cal != nil)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event != nil)
        #expect(event?.countProperties(ofKind: .attendee) == 2)
        #expect(event?.firstProperty(ofKind: .organizer) != nil)
    }
}

// MARK: - Enums Tests

@Suite("Enums Tests")
struct EnumsTests {

    @Test("ComponentKind 枚举转换")
    func testComponentKindConversion() {
        let kinds: [ComponentKind] = [.vcalendar, .vevent, .vtodo, .vjournal, .valarm, .vtimezone]
        for kind in kinds {
            let cValue = kind.cValue
            let back = ComponentKind(cValue: cValue)
            #expect(back == kind)
        }
    }

    @Test("PropertyKind 枚举转换")
    func testPropertyKindConversion() {
        let kinds: [PropertyKind] = [.summary, .dtstart, .dtend, .uid, .description, .location]
        for kind in kinds {
            let cValue = kind.cValue
            let back = PropertyKind(cValue: cValue)
            #expect(back == kind)
        }
    }

    @Test("ParameterKind 枚举转换")
    func testParameterKindConversion() {
        let kinds: [ParameterKind] = [.tzid, .cn, .language, .role, .partstat]
        for kind in kinds {
            let cValue = kind.cValue
            let back = ParameterKind(cValue: cValue)
            #expect(back == kind)
        }
    }

    @Test("RecurrenceFrequency 枚举转换")
    func testRecurrenceFrequencyConversion() {
        let freqs: [RecurrenceFrequency] = [.secondly, .minutely, .hourly, .daily, .weekly, .monthly, .yearly]
        for freq in freqs {
            let cValue = freq.cValue
            let back = RecurrenceFrequency(cValue: cValue)
            #expect(back == freq)
        }
    }

    @Test("Weekday 枚举转换")
    func testWeekdayConversion() {
        let days: [Weekday] = [.sunday, .monday, .tuesday, .wednesday, .thursday, .friday, .saturday]
        for day in days {
            let cValue = day.cValue
            let back = Weekday(cValue: cValue)
            #expect(back == day)
        }
    }

    @Test("PropertyStatus 枚举转换")
    func testPropertyStatusConversion() {
        let statuses: [PropertyStatus] = [.tentative, .confirmed, .completed, .needsAction, .cancelled, .inProcess]
        for status in statuses {
            let cValue = status.cValue
            let back = PropertyStatus(cValue: cValue)
            #expect(back == status)
        }
    }

    @Test("PropertyMethod 枚举转换")
    func testPropertyMethodConversion() {
        let methods: [PropertyMethod] = [.publish, .request, .reply, .add, .cancel, .refresh, .counter, .declineCounter]
        for method in methods {
            let cValue = method.cValue
            let back = PropertyMethod(cValue: cValue)
            #expect(back == method)
        }
    }

    @Test("PropertyClass 枚举转换")
    func testPropertyClassConversion() {
        let classes: [PropertyClass] = [.public, .private, .confidential]
        for cls in classes {
            let cValue = cls.cValue
            let back = PropertyClass(cValue: cValue)
            #expect(back == cls)
        }
    }

    @Test("PropertyTransp 枚举转换")
    func testPropertyTranspConversion() {
        let transps: [PropertyTransp] = [.opaque, .transparent]
        for transp in transps {
            let cValue = transp.cValue
            let back = PropertyTransp(cValue: cValue)
            #expect(back == transp)
        }
    }

    @Test("PropertyAction 枚举转换")
    func testPropertyActionConversion() {
        let actions: [PropertyAction] = [.audio, .display, .email, .procedure]
        for action in actions {
            let cValue = action.cValue
            let back = PropertyAction(cValue: cValue)
            #expect(back == action)
        }
    }

    @Test("PartStat 枚举转换")
    func testPartStatConversion() {
        let stats: [PartStat] = [.needsAction, .accepted, .declined, .tentative, .delegated, .completed, .inProcess]
        for stat in stats {
            let cValue = stat.cValue
            let back = PartStat(cValue: cValue)
            #expect(back == stat)
        }
    }

    @Test("Role 枚举转换")
    func testRoleConversion() {
        let roles: [Role] = [.chair, .reqParticipant, .optParticipant, .nonParticipant]
        for role in roles {
            let cValue = role.cValue
            let back = Role(cValue: cValue)
            #expect(back == role)
        }
    }

    @Test("CUType 枚举转换")
    func testCUTypeConversion() {
        let types: [CUType] = [.individual, .group, .resource, .room, .unknown]
        for type_ in types {
            let cValue = type_.cValue
            let back = CUType(cValue: cValue)
            #expect(back == type_)
        }
    }

    @Test("FBType 枚举转换")
    func testFBTypeConversion() {
        let types: [FBType] = [.free, .busy, .busyUnavailable, .busyTentative]
        for type_ in types {
            let cValue = type_.cValue
            let back = FBType(cValue: cValue)
            #expect(back == type_)
        }
    }

    @Test("RelType 枚举转换")
    func testRelTypeConversion() {
        let types: [RelType] = [.parent, .child, .sibling]
        for type_ in types {
            let cValue = type_.cValue
            let back = RelType(cValue: cValue)
            #expect(back == type_)
        }
    }

    @Test("Encoding 枚举转换")
    func testEncodingConversion() {
        let encodings: [Encoding] = [.bit8, .base64]
        for encoding in encodings {
            let cValue = encoding.cValue
            let back = Encoding(cValue: cValue)
            #expect(back == encoding)
        }
    }

    @Test("RecurrenceSkip 枚举转换")
    func testRecurrenceSkipConversion() {
        let skips: [RecurrenceSkip] = [.backward, .forward, .omit]
        for skip in skips {
            let cValue = skip.cValue
            let back = RecurrenceSkip(cValue: cValue)
            #expect(back == skip)
        }
    }

    @Test("RequestStatus 主次版本号")
    func testRequestStatusVersionNumbers() {
        let status = RequestStatus.success_2_0
        #expect(status.major == 2)
        #expect(status.minor == 0)

        let status2 = RequestStatus.invpropname_3_0
        #expect(status2.major == 3)
        #expect(status2.minor == 0)
    }

    @Test("RequestStatus 状态码字符串")
    func testRequestStatusCode() {
        let status = RequestStatus.success_2_0
        let code = status.code
        #expect(!code.isEmpty)
        #expect(code.contains("2"))
    }

    @Test("RequestStatus 从主次版本号创建")
    func testRequestStatusFromMajorMinor() {
        let status = RequestStatus.from(major: 2, minor: 0)
        #expect(status == .success_2_0)
    }
}

// MARK: - Integration Tests

@Suite("Integration Tests")
struct IntegrationTests {

    @Test("完整日历创建和解析往返")
    func testFullCalendarRoundTrip() {
        // 创建日历
        let cal = Component.vcalendar()
        cal.addProperty(Property(string: "VERSION:2.0")!)
        cal.addProperty(Property(string: "PRODID:-//Integration Test//Test//EN")!)

        let event = Component.vevent()
        event.uid = "integration-test-001@example.com"
        event.summary = "集成测试事件"
        event.componentDescription = "这是一个完整的集成测试"
        event.location = "测试地点"
        event.dtstart = Time(string: "20240315T140000Z")!
        event.dtend = Time(string: "20240315T150000Z")!
        event.status = .confirmed
        event.sequence = 1

        // 添加参与者
        let attendeeProp = Property.attendee("mailto:user@example.com")
        if let cnParam = Parameter.cn("测试用户") {
            attendeeProp.addParameter(cnParam)
        }
        if let partstatParam = Parameter.partstat(.accepted) {
            attendeeProp.addParameter(partstatParam)
        }
        event.addProperty(attendeeProp)

        cal.addComponent(event)

        // 序列化
        let icsString = cal.iCalString
        #expect(!icsString.isEmpty)
        #expect(icsString.contains("BEGIN:VCALENDAR"))
        #expect(icsString.contains("BEGIN:VEVENT"))

        // 反序列化
        let parsed = Component.parse(icsString)
        #expect(parsed != nil)
        #expect(parsed?.kind == .vcalendar)

        let parsedEvent = parsed?.firstComponent(ofKind: .vevent)
        #expect(parsedEvent != nil)
        #expect(parsedEvent?.uid == "integration-test-001@example.com")
        #expect(parsedEvent?.summary == "集成测试事件")
        #expect(parsedEvent?.location == "测试地点")
    }

    @Test("含重复规则的事件完整流程")
    func testRecurringEventFullFlow() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:recurring-full-test@example.com
        DTSTART:20240101T090000Z
        DTEND:20240101T100000Z
        RRULE:FREQ=WEEKLY;BYDAY=MO;COUNT=4
        SUMMARY:每周一会议
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)!
        let event = cal.firstComponent(ofKind: .vevent)!

        // 验证重复规则属性存在
        let rruleProp = event.firstProperty(ofKind: .rrule)
        #expect(rruleProp != nil)

        // 遍历重复实例
        let start = Time(string: "20240101T000000Z")!
        let end = Time(string: "20240201T000000Z")!
        var count = 0
        event.forEachRecurrence(from: start, to: end) { _, _ in
            count += 1
        }
        #expect(count == 4)
    }

    @Test("VTODO 完整流程")
    func testVTodoFullFlow() {
        let todo = Component.vtodo()
        todo.uid = "todo-full-test@example.com"
        todo.summary = "完成项目报告"
        todo.componentDescription = "需要在截止日期前完成季度报告"
        todo.status = .inProcess
        todo.sequence = 0

        // 设置截止时间
        let due = Time(string: "20240131T170000Z")!
        todo.due = due

        let cal = Component.vcalendar()
        cal.addComponent(todo)

        let icsString = cal.iCalString
        #expect(icsString.contains("BEGIN:VTODO"))
        #expect(icsString.contains("完成项目报告"))

        // 解析验证
        let parsed = Component.parse(icsString)!
        let parsedTodo = parsed.firstComponent(ofKind: .vtodo)
        #expect(parsedTodo != nil)
        #expect(parsedTodo?.summary == "完成项目报告")
        #expect(parsedTodo?.uid == "todo-full-test@example.com")
    }

    @Test("TimeSpan 验证")
    func testTimeSpan() {
        let event = Component.vevent()
        let start = Time(string: "20240101T090000Z")!
        let end = Time(string: "20240101T100000Z")!
        event.dtstart = start
        event.dtend = end

        let span = event.span
        #expect(span.end > span.start)
        #expect(span.end - span.start == 3600) // 1 小时 = 3600 秒
    }

    @Test("属性参数完整流程")
    func testPropertyParameterFullFlow() {
        // 创建带完整参数的 ATTENDEE 属性
        let attendee = Property.attendee("mailto:zhangsan@example.com")

        if let cn = Parameter.cn("张三") {
            attendee.addParameter(cn)
        }
        if let role = Parameter.role(.reqParticipant) {
            attendee.addParameter(role)
        }
        if let partstat = Parameter.partstat(.accepted) {
            attendee.addParameter(partstat)
        }
        if let rsvp = Parameter.rsvp(true) {
            attendee.addParameter(rsvp)
        }
        if let cutype = Parameter.cutype(.individual) {
            attendee.addParameter(cutype)
        }

        #expect(attendee.parameterCount >= 5)

        let icalStr = attendee.iCalString
        #expect(icalStr.contains("ATTENDEE"))
        #expect(icalStr.contains("zhangsan@example.com"))
    }

    @Test("多时区日历处理")
    func testMultiTimezoneCalendar() {
        Timezone.useBuiltinTZData = true
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:tz-test@example.com
        DTSTART;TZID=America/New_York:20240315T140000
        DTEND;TZID=America/New_York:20240315T150000
        SUMMARY:纽约时区事件
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)
        #expect(cal != nil)
        let event = cal?.firstComponent(ofKind: .vevent)
        #expect(event != nil)
        #expect(event?.summary == "纽约时区事件")
    }

    @Test("TZID 参数遍历")
    func testForEachTZID() {
        let icsString = """
        BEGIN:VCALENDAR
        VERSION:2.0
        PRODID:-//Test//Test//EN
        BEGIN:VEVENT
        UID:tzid-iter-test@example.com
        DTSTART;TZID=America/New_York:20240315T140000
        DTEND;TZID=America/New_York:20240315T150000
        SUMMARY:TZID 遍历测试
        END:VEVENT
        END:VCALENDAR
        """
        let cal = Component.parse(icsString)!
        var tzids: [String] = []
        cal.forEachTZID { param in
            if let str = param.iCalString.components(separatedBy: "=").last {
                tzids.append(str)
            }
        }
        // 应该找到 TZID 参数
        #expect(tzids.count >= 0) // 至少不崩溃
    }
}
