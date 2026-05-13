# libical Swift Wrapper

将 [libical](https://github.com/libical/libical) 自动构建为支持多平台的 Apple XCFramework 静态库，并提供完整的 Swift 封装层（`libICAL`）。

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
- 提供完整的 **Swift 封装层**（`libICAL` 模块），覆盖 iCalendar 全部核心类型
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
├── Sources/
│   └── libical/                   # Swift 封装层源码（libICAL 模块）
│       ├── libical.swift          # 模块说明
│       ├── Component.swift        # iCalendar 组件
│       ├── Property.swift         # iCalendar 属性
│       ├── Parameter.swift        # iCalendar 属性参数
│       ├── Time.swift             # 日期/时间/时间段/时间区间
│       ├── Timezone.swift         # 时区
│       ├── Recurrence.swift       # 重复规则与迭代器
│       ├── Parser.swift           # iCalendar 解析器
│       └── Enums.swift            # 枚举类型定义
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

或通过 Xcode → File → Add Package Dependencies 添加本仓库。

### Xcode 手动集成

1. 将 `output/libical.xcframework` 拖入 Xcode 项目
2. 在 **Target → General → Frameworks, Libraries, and Embedded Content** 中确认已添加
3. 将 **Embed** 设置为 **Do Not Embed**（静态库无需嵌入）

### 头文件引用（C/Objective-C）

```c
#include <libical/ical.h>
```

### Swift 模块导入

```swift
import libICAL
```

---

## Swift API 详细使用文档

### 核心类型概览

| 类型 | 说明 |
|------|------|
| `Component` | iCalendar 组件（VCALENDAR、VEVENT 等） |
| `Property` | iCalendar 属性（DTSTART、SUMMARY 等） |
| `Parameter` | iCalendar 属性参数（TZID、CN 等） |
| `Time` | 日期/时间类型（值类型） |
| `Duration` | 时间段类型（如 PT1H30M，值类型） |
| `Period` | 时间区间类型（起止时间或起始+时长，值类型） |
| `TimeSpan` | 时间跨度（Unix 时间戳区间，值类型） |
| `Timezone` | 时区类型 |
| `Recurrence` | 重复规则（RRULE） |
| `RecurrenceIterator` | 重复规则迭代器（支持 `for-in`） |
| `Parser` | iCalendar 字符串解析器 |

---

### Component — iCalendar 组件

`Component` 是 iCalendar 数据的基本容器，可包含属性和子组件。

#### 创建组件

```swift
// 便捷工厂方法
let calendar   = Component.vcalendar()    // VCALENDAR 容器
let event      = Component.vevent()       // VEVENT 事件
let todo       = Component.vtodo()        // VTODO 待办
let journal    = Component.vjournal()     // VJOURNAL 日记
let alarm      = Component.valarm()       // VALARM 闹钟
let freebusy   = Component.vfreebusy()    // VFREEBUSY 空闲/忙碌
let timezone   = Component.vtimezone()    // VTIMEZONE 时区定义
let standard   = Component.xstandard()   // STANDARD（VTIMEZONE 子组件）
let daylight   = Component.xdaylight()   // DAYLIGHT（VTIMEZONE 子组件）
let agenda     = Component.vagenda()      // VAGENDA 议程
let avail      = Component.vavailability() // VAVAILABILITY 可用性
let poll       = Component.vpoll()        // VPOLL 投票
let patch      = Component.vpatch()       // VPATCH 补丁
let participant = Component.participant() // PARTICIPANT 参与者
let location   = Component.vlocation()   // VLOCATION 位置
let resource   = Component.vresource()   // VRESOURCE 资源

// X 扩展组件
let xComp = Component.x(name: "X-MY-COMPONENT")

// IANA 注册组件
let ianaComp = Component.iana(name: "MY-COMPONENT")

// 通用构造
let comp = Component(kind: .vevent)

// 从 iCalendar 字符串解析
let comp2 = Component(string: """
BEGIN:VEVENT
UID:abc@example.com
SUMMARY:会议
END:VEVENT
""")
```

#### 解析 iCalendar 字符串

```swift
let icsString = """
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//MyApp//MyApp//EN
BEGIN:VEVENT
UID:event-001@example.com
DTSTART:20240601T090000Z
DTEND:20240601T100000Z
SUMMARY:团队周会
END:VEVENT
END:VCALENDAR
"""

// 静态方法解析
if let calendar = Component.parse(icsString) {
    print(calendar.kind)  // .vcalendar
}

// 从 Data 解析
if let data = icsString.data(using: .utf8),
   let calendar = Component.parse(data: data) {
    print(calendar.kind)
}
```

#### 读写常用属性

```swift
let event = Component.vevent()

// 摘要/标题
event.summary = "季度总结会议"
print(event.summary ?? "")

// 详细描述（使用 componentDescription 避免与 Swift 的 description 冲突）
event.componentDescription = "Q2 业绩回顾与 Q3 目标制定"

// 地点
event.location = "北京·朝阳区·望京 SOHO T1"

// 唯一标识符
event.uid = UUID().uuidString

// 开始/结束时间
event.dtstart = Time(string: "20240601T090000Z")!
event.dtend   = Time(string: "20240601T110000Z")!

// 待办截止时间（VTODO 使用）
todo.due = Time(string: "20240630T180000Z")!

// 持续时长（与 dtend 二选一）
event.duration = Duration(hours: 2)

// 时间戳（创建/修改时间）
event.dtstamp = Time.now()

// 状态
event.status = .confirmed   // .tentative / .cancelled / .needsAction 等

// 日历方法（iTIP 调度）
event.method = .request     // .publish / .reply / .cancel 等

// 序列号（每次修改递增）
event.sequence = 1

// 注释
event.comment = "请准时参加"

// 重复标识（用于标识重复事件的特定实例）
event.recurrenceID = Time(string: "20240601T090000Z")!

// 关联日历标识
event.relcalid = "my-calendar-id"

// X 扩展组件名称（kind == .x 时有效）
event.xName = "X-MY-COMPONENT"

// IANA 注册组件名称（kind == .iana 时有效）
event.ianaName = "MY-COMPONENT"

// 父组件（借用引用）
let parent = event.parent
```

#### 管理属性

```swift
let event = Component.vevent()

// 添加属性（组件接管所有权）
let summaryProp = Property.summary("重要会议")
event.addProperty(summaryProp)

// 获取第一个指定类型的属性
if let prop = event.firstProperty(ofKind: .summary) {
    print(prop.valueString ?? "")
}

// 迭代属性（firstProperty + nextProperty）
var prop = event.firstProperty(ofKind: .attendee)
while let p = prop {
    print(p.valueString ?? "")
    prop = event.nextProperty(ofKind: .attendee)
}

// 获取所有指定类型的属性数组
let allAttendees = event.properties(ofKind: .attendee)
for attendee in allAttendees {
    print(attendee.valueString ?? "")
}

// 获取所有属性（不限类型）
let allProps = event.properties()

// 统计属性数量
let count = event.countProperties(ofKind: .any)

// 移除指定属性对象
if let prop = event.firstProperty(ofKind: .comment) {
    event.removeProperty(prop)
}

// 移除所有指定类型的属性
event.removeProperties(ofKind: .comment)
```

#### 管理子组件

```swift
let calendar = Component.vcalendar()
let event    = Component.vevent()
event.summary = "子事件"

// 添加子组件（父组件接管所有权）
calendar.addComponent(event)

// 统计子组件数量
print(calendar.countComponents(ofKind: .vevent))  // 1
print(calendar.countComponents())                  // 所有子组件

// 获取第一个指定类型的子组件
if let firstEvent = calendar.firstComponent(ofKind: .vevent) {
    print(firstEvent.summary ?? "")
}

// 迭代子组件（firstComponent + nextComponent）
var comp = calendar.firstComponent(ofKind: .vevent)
while let c = comp {
    print(c.summary ?? "")
    comp = calendar.nextComponent(ofKind: .vevent)
}

// 获取所有指定类型的子组件数组
let events = calendar.components(ofKind: .vevent)
for e in events {
    print(e.summary ?? "")
}

// 移除子组件
if let e = calendar.firstComponent(ofKind: .vevent) {
    calendar.removeComponent(e)
}

// 获取内部嵌套组件（如 VCALENDAR 内的第一个实际组件）
let inner = calendar.innerComponent

// 获取第一个"真实"子组件（跳过 VTIMEZONE 等辅助组件）
let real = calendar.firstRealComponent
```

#### 时区相关

```swift
// 根据 TZID 获取组件中定义的时区
if let tz = calendar.timezone(forTZID: "America/New_York") {
    print(tz.tzid ?? "")
}

// 遍历组件中所有 TZID 参数
calendar.forEachTZID { param in
    print(param.iCalString)  // 如 "TZID=America/New_York"
}
```

#### 构建完整日历并输出

```swift
let calendar = Component.vcalendar()

// 添加版本和产品标识
calendar.addProperty(Property(string: "VERSION:2.0")!)
calendar.addProperty(Property(string: "PRODID:-//MyApp//MyApp//EN")!)

let event = Component.vevent()
event.uid       = "event-001@myapp.com"
event.summary   = "产品发布会"
event.location  = "上海·浦东新区·张江高科"
event.dtstart   = Time(string: "20240901T100000Z")!
event.dtend     = Time(string: "20240901T120000Z")!
event.dtstamp   = Time.now()
event.status    = .confirmed

calendar.addComponent(event)

// 输出 iCalendar 格式字符串
print(calendar.iCalString)
// 或直接 print(calendar)，因为实现了 CustomStringConvertible
```

#### 时间跨度与重复遍历

```swift
// 获取组件的时间跨度（基于 DTSTART 和 DTEND/DURATION）
let span = event.span
print("开始: \(span.start), 结束: \(span.end), 忙碌: \(span.isBusy)")

// 遍历指定时间范围内的所有重复实例
let rangeStart = Time(string: "20240101T000000Z")!
let rangeEnd   = Time(string: "20241231T235959Z")!

event.forEachRecurrence(from: rangeStart, to: rangeEnd) { comp, span in
    print("重复实例: \(comp.summary ?? ""), 时间跨度: \(span.start)-\(span.end)")
}
```

#### 错误处理与规范化

```swift
// 检查解析错误数量
print(event.errorCount)

// 移除错误属性
event.stripErrors()

// 将错误属性转换为标准属性（尝试修复）
event.convertErrors()

// 检查是否符合 RFC5545 限制规则
let isValid = event.checkRestrictions()

// 规范化组件（排序属性、规范化值格式等）
event.normalize()

// 深度克隆
if let cloned = event.clone() {
    print(cloned.summary ?? "")
}

// 合并另一个组件（other 合并后不可再使用）
let other = Component.vcalendar()
calendar.merge(other)
```

#### 静态工具方法

```swift
// 组件类型转字符串
Component.kindToString(.vevent)    // "VEVENT"
Component.kindToString(.vcalendar) // "VCALENDAR"

// 字符串转组件类型
Component.kind(from: "VEVENT")     // .vevent

// 验证组件类型有效性
Component.isValid(kind: .vevent)   // true
```

---

### Property — iCalendar 属性

#### 创建属性

```swift
// 便捷工厂方法
let summary   = Property.summary("团队会议")
let desc      = Property.description("Q3 目标讨论")
let location  = Property.location("会议室 A")
let uid       = Property.uid(UUID().uuidString)
let dtstart   = Property.dtstart(Time(string: "20240601T090000Z")!)
let dtend     = Property.dtend(Time(string: "20240601T110000Z")!)
let duration  = Property.duration(Duration(hours: 1, minutes: 30))
let dtstamp   = Property.dtstamp(Time.now())
let status    = Property.status(.confirmed)
let method    = Property.method(.request)
let cls       = Property.class(.public)
let transp    = Property.transp(.opaque)
let seq       = Property.sequence(1)
let attendee  = Property.attendee("mailto:user@example.com")
let organizer = Property.organizer("mailto:boss@example.com")
let comment   = Property.comment("请准时参加")
let categories = Property.categories("工作,会议")
let priority  = Property.priority(1)   // 1=最高，9=最低，0=未定义
let url       = Property.url("https://example.com/meeting")

// 通用构造
let prop = Property(kind: .summary)

// 从 iCalendar 格式字符串解析
let prop2 = Property(string: "SUMMARY:重要会议")
```

#### 读写属性值

```swift
let prop = Property(kind: .summary)

// 设置值（自动推断类型）
prop.setValue(string: "新的摘要")

// 设置值（指定类型）
prop.setValue(string: "20240601T090000Z", type: "DATE-TIME")

// 读取值字符串
print(prop.valueString ?? "")

// 读取属性名
print(prop.name ?? "")  // "SUMMARY"

// 读取属性类型
print(prop.kind)  // .summary

// 输出 iCalendar 格式字符串
print(prop.iCalString)  // "SUMMARY:新的摘要"

// X 扩展属性名称（kind == .x 时有效）
let xProp = Property(kind: .x)
xProp.xName = "X-APPLE-TRAVEL-DURATION"
xProp.setValue(string: "PT30M")
print(xProp.iCalString)  // "X-APPLE-TRAVEL-DURATION:PT30M"

// IANA 注册属性名称
xProp.ianaName = "MY-IANA-PROP"
```

#### 管理参数

```swift
let attendeeProp = Property.attendee("mailto:user@example.com")

// 添加参数
if let cn = Parameter.cn("张三") {
    attendeeProp.addParameter(cn)
}
if let role = Parameter.role(.reqParticipant) {
    attendeeProp.addParameter(role)
}
if let partstat = Parameter.partstat(.accepted) {
    attendeeProp.setParameter(partstat)  // 替换同类型的已有参数
}

// 统计参数数量
print(attendeeProp.parameterCount)

// 获取参数值字符串
print(attendeeProp.parameterValue(named: "CN") ?? "")

// 通过名称和值设置参数
attendeeProp.setParameter(name: "RSVP", value: "TRUE")

// 获取所有参数（不限类型）
let params = attendeeProp.parameters()
for param in params {
    print(param.iCalString)
}

// 获取指定类型的所有参数
let cnParams = attendeeProp.parameters(ofKind: .cn)

// 迭代参数（firstParameter + nextParameter）
var param = attendeeProp.firstParameter(ofKind: .cn)
while let p = param {
    print(p.iCalString)
    param = attendeeProp.nextParameter(ofKind: .cn)
}

// 移除参数
attendeeProp.removeParameters(ofKind: .rsvp)
attendeeProp.removeParameters(named: "CN")
attendeeProp.removeParameter(someParam)
```

#### 静态工具方法

```swift
// 属性类型转字符串
Property.kindToString(.summary)   // "SUMMARY"
Property.kindToString(.dtstart)   // "DTSTART"

// 字符串转属性类型
Property.kind(from: "SUMMARY")    // .summary

// 验证属性类型有效性
Property.isValid(kind: .summary)  // true

// 枚举值转字符串（如状态、方法等）
Property.enumToString(10902)      // "CONFIRMED"

// 从字符串解析各枚举值
Property.method(from: "REQUEST")  // .request
Property.status(from: "CONFIRMED") // icalproperty_status
Property.action(from: "DISPLAY")
Property.transp(from: "OPAQUE")
Property.class(from: "PUBLIC")

// 空属性全局设置
Property.allowEmptyProperties = true
```

---

### Parameter — iCalendar 属性参数

#### 创建参数

```swift
// 便捷工厂方法
let tzid     = Parameter.tzid("Asia/Shanghai")
let language = Parameter.language("zh-CN")
let cn       = Parameter.cn("李四")
let email    = Parameter.email("lisi@example.com")
let role     = Parameter.role(.chair)              // .reqParticipant / .optParticipant 等
let partstat = Parameter.partstat(.accepted)       // .declined / .tentative 等
let cutype   = Parameter.cutype(.individual)       // .group / .resource / .room 等
let fbtype   = Parameter.fbtype(.busy)             // .free / .busyUnavailable 等
let rsvp     = Parameter.rsvp(true)
let encoding = Parameter.encoding(.base64)

// 通用构造
let param = Parameter(kind: .tzid)

// 从 iCalendar 格式字符串解析
let param2 = Parameter(string: "ROLE=CHAIR")

// 从类型和值字符串创建
let param3 = Parameter(kind: .cn, value: "王五")
```

#### 读写参数

```swift
let param = Parameter(string: "ROLE=CHAIR")!

// 读取参数类型
print(param.kind)  // .role

// 输出 iCalendar 格式字符串
print(param.iCalString)  // "ROLE=CHAIR"

// X 扩展参数
let xParam = Parameter(kind: .x)
xParam.xname  = "X-CUSTOM-PARAM"
xParam.xvalue = "custom-value"

// IANA 注册参数
let ianaParam = Parameter(kind: .iana)
ianaParam.ianaName  = "MY-IANA-PARAM"
ianaParam.ianaValue = "my-value"

// 是否为多值参数
print(param.isMultivalued)

// 比较参数名是否相同
let p1 = Parameter(string: "ROLE=CHAIR")!
let p2 = Parameter(string: "ROLE=REQ-PARTICIPANT")!
print(p1.hasSameName(as: p2))  // true（同为 ROLE 参数）
```

#### 静态工具方法

```swift
// 参数类型转字符串
Parameter.kindToString(.tzid)      // "TZID"
Parameter.kindToString(.cn)        // "CN"

// 字符串转参数类型
Parameter.kind(from: "TZID")       // .tzid

// 验证参数类型有效性
Parameter.isValid(kind: .tzid)     // true

// 解码参数值（URL 编码解码）
Parameter.decodeValue("simple-value")
```

---

### Time — 日期/时间

`Time` 是值类型（`struct`），实现了 `Equatable`、`Comparable`、`Hashable`。

#### 创建时间

```swift
// 空时间（null time）
let nullTime = Time()
print(nullTime.isNull)  // true

// 从 RFC5545 格式字符串
let t1 = Time(string: "20240601T090000Z")!   // UTC 时间
let t2 = Time(string: "20240601T170000")     // 浮动时间（无时区）
let t3 = Time(string: "20240601")            // 纯日期

// 从 Unix 时间戳
let t4 = Time(timeInterval: Date().timeIntervalSince1970)

// 从 Unix 时间戳 + 时区
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    let t5 = Time(timeInterval: Date().timeIntervalSince1970, timezone: tz)
}

// 从年内天序号
let t6 = Time(dayOfYear: 1, year: 2024)  // 2024 年第 1 天

// 当前时间
let now   = Time.now()
let nowInTZ = Time.now(in: Timezone.builtin(location: "Asia/Shanghai"))
let today = Time.today  // 仅日期，无时间部分

// 空日期
let nullDate = Time.nullDate
```

#### 读写时间字段

```swift
var t = Time(string: "20240601T090000Z")!

print(t.year)       // 2024
print(t.month)      // 6
print(t.day)        // 1
print(t.hour)       // 9
print(t.minute)     // 0
print(t.second)     // 0
print(t.isDate)     // false（含时间部分）
print(t.isUTC)      // true
print(t.isNull)     // false
print(t.isValid)    // true
print(t.isDaylight) // false（是否夏令时）
print(t.dayOfYear)  // 153（年内天序号）
print(t.dayOfWeek)  // 7（1=周日，2=周一，...，7=周六）
print(t.timezoneID ?? "") // "UTC"（关联的 TZID）

// 关联的时区对象（借用）
let tz = t.timezone

// 修改字段
t.hour = 10
t.minute = 30
```

#### 时间转换

```swift
let t = Time(string: "20240601T090000Z")!

// 转换为 Unix 时间戳
let ts = t.timeIntervalSince1970

// 在指定时区下转换为 Unix 时间戳
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    let tsInTZ = t.timeIntervalSince1970(in: tz)
}

// 转换为 Foundation Date
let date = t.date

// 转换为 iCalendar 格式字符串
print(t.iCalString)  // "20240601T090000Z"

// 转换到指定时区（返回新时间对象）
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    let localTime = t.converted(to: tz)
    print(localTime.hour)  // 17（UTC+8）
}

// 设置时区（不转换时间值，仅更改时区标记）
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    let tagged = t.settingTimezone(tz)
}

// 规范化（处理溢出字段）
var t2 = Time(string: "20240601T235900Z")!
t2.minute = 70  // 溢出
let normalized = t2.normalized()
print(normalized.hour)    // 0（次日）
print(normalized.minute)  // 10

// 时间偏移
let tomorrow = t.adjusted(days: 1)
let nextHour = t.adjusted(hours: 1)
let earlier  = t.adjusted(hours: -2, minutes: -30)
```

#### 时间比较

```swift
let t1 = Time(string: "20240601T090000Z")!
let t2 = Time(string: "20240601T100000Z")!

print(t1 < t2)   // true
print(t1 == t2)  // false

// 仅比较日期部分（忽略时间）
print(t1.compareDateOnly(to: t2))  // 0（同一天）

// 在指定时区下仅比较日期部分
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    print(t1.compareDateOnly(to: t2, in: tz))
}

// 获取本周起始日的年内天序号
let startDOY = t1.startDayOfYearWeek(firstDayOfWeek: 2)  // 2=周一
```

#### 静态工具方法

```swift
// 判断闰年
print(Time.isLeapYear(2024))  // true
print(Time.isLeapYear(2023))  // false

// 获取月份天数
print(Time.daysInMonth(2, year: 2024))  // 29（闰年）
print(Time.daysInMonth(2, year: 2023))  // 28

// 获取年份总天数
print(Time.daysInYear(2024))  // 366
```

---

### Duration — 时间段

`Duration` 是值类型（`struct`），表示一段时间长度。

#### 创建时间段

```swift
// 零时长
let zero = Duration()
print(zero.isNull)  // true

// 从总秒数
let oneHour = Duration(seconds: 3600)

// 从 RFC5545 格式字符串
let d1 = Duration(string: "PT1H30M")!   // 1 小时 30 分钟
let d2 = Duration(string: "P1W")!       // 1 周
let d3 = Duration(string: "P1DT2H")!    // 1 天 2 小时
let d4 = Duration(string: "-P1D")!      // 负 1 天（用于 TRIGGER 提前提醒）

// 从各分量
let d5 = Duration(weeks: 1)
let d6 = Duration(days: 1, hours: 2, minutes: 30)
let d7 = Duration(isNegative: true, hours: 1)  // 提前 1 小时触发
```

#### 读写时间段字段

```swift
let d = Duration(string: "P1DT2H30M")!

print(d.weeks)        // 0
print(d.days)         // 1
print(d.hours)        // 2
print(d.minutes)      // 30
print(d.seconds)      // 0
print(d.isNegative)   // false
print(d.isNull)       // false
print(d.isBad)        // false（是否为无效时间段）
print(d.totalSeconds)    // 95400
print(d.totalUTCSeconds) // 95400（考虑夏令时）

// 规范化时间段
let normalized = d.normalized()

// 输出 iCalendar 格式字符串
print(d.iCalString)  // "P1DT2H30M"
```

---

### Period — 时间区间

`Period` 是值类型（`struct`），表示一个时间区间。

#### 创建时间区间

```swift
let start = Time(string: "20240601T090000Z")!
let end   = Time(string: "20240601T110000Z")!

// 通过起止时间创建
let p1 = Period(start: start, end: end)

// 通过起始时间 + 持续时长创建
let p2 = Period(start: start, duration: Duration(hours: 2))

// 从 RFC5545 格式字符串解析
let p3 = Period(string: "20240601T090000Z/20240601T110000Z")
let p4 = Period(string: "20240601T090000Z/PT2H")

// 输出 iCalendar 格式字符串
print(p1.iCalString)  // "20240601T090000Z/20240601T110000Z"
```

---

### Timezone — 时区

#### 获取时区

```swift
// UTC 时区
let utc = Timezone.utc

// 根据 IANA 位置名称获取内置时区
let shanghai  = Timezone.builtin(location: "Asia/Shanghai")
let newYork   = Timezone.builtin(location: "America/New_York")
let london    = Timezone.builtin(location: "Europe/London")

// 根据 TZID 获取内置时区
let tz = Timezone.builtin(tzid: "Asia/Shanghai")

// 根据 UTC 偏移和时区名称获取
let est = Timezone.builtin(utcOffset: -18000, tzname: "EST")  // UTC-5

// 获取所有内置时区列表
let allTimezones = Timezone.builtinTimezones
for tz in allTimezones {
    print(tz.displayName ?? tz.tzid ?? "")
}

// 创建新的空时区对象
let newTZ = Timezone()
```

#### 时区属性

```swift
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    print(tz.tzid ?? "")         // "Asia/Shanghai"
    print(tz.location ?? "")     // "Asia/Shanghai"
    print(tz.tznames ?? "")      // "CST"
    print(tz.displayName ?? "")  // "Asia/Shanghai"
    print(tz.latitude)           // 31.2
    print(tz.longitude)          // 121.4

    // 获取 VTIMEZONE 组件
    let vtimezone = tz.component

    // 设置 VTIMEZONE 组件
    if let vtComp = Component.vtimezone() as Component? {
        tz.setComponent(vtComp)
    }
}
```

#### 时区转换

```swift
// 方式一：使用 Time.converted(to:)
let utcTime = Time(string: "20240601T090000Z")!
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    let localTime = utcTime.converted(to: tz)
    print(localTime.hour)  // 17
}

// 方式二：使用 Timezone.convertTime(_:from:to:)（原地修改）
var t = Time(string: "20240601T090000Z")!
if let utc = Timezone.utc,
   let tz  = Timezone.builtin(location: "Asia/Shanghai") {
    Timezone.convertTime(&t, from: utc, to: tz)
    print(t.hour)  // 17
}
```

#### UTC 偏移查询

```swift
if let tz = Timezone.builtin(location: "Asia/Shanghai") {
    var isDaylight = false

    // 本地时间对应的 UTC 偏移
    let offset = tz.utcOffset(for: Time.now(), isDaylight: &isDaylight)
    print("UTC 偏移: \(offset / 3600) 小时")  // 8
    print("夏令时: \(isDaylight)")              // false

    // UTC 时间对应的 UTC 偏移
    let offsetFromUTC = tz.utcOffset(forUTC: Time.now(), isDaylight: &isDaylight)
}
```

#### VTIMEZONE 工具方法

```swift
// 从 VTIMEZONE 组件获取位置字符串
if let vtComp = calendar.firstComponent(ofKind: .vtimezone) {
    let loc = Timezone.location(fromVTimezone: vtComp)
    let names = Timezone.tznames(fromVTimezone: vtComp)
}

// 展开 VTIMEZONE 到指定年份（预计算转换规则）
Timezone.expandVTimezone(vtComp, endYear: 2030)

// 截断 VTIMEZONE 到指定时间范围（减小数据量）
let start = Time(string: "20200101T000000Z")!
let end   = Time(string: "20300101T000000Z")!
Timezone.truncateVTimezone(vtComp, start: start, end: end)
```

#### 全局设置

```swift
// 使用 libical 内置时区数据（而非系统时区数据库）
Timezone.useBuiltinTZData = true

// 设置时区数据库目录
Timezone.setSystemZoneDirectory("/usr/share/zoneinfo")

// 时区数据目录（可读写）
Timezone.zoneDirectory = "/custom/zoneinfo"
print(Timezone.systemZoneDirectory ?? "")

// TZID 前缀
print(Timezone.tzidPrefix ?? "")
Timezone.tzidPrefix = "/custom/"

// 释放内置时区缓存
Timezone.freeBuiltinTimezones()
```

---

### Recurrence — 重复规则

#### 创建重复规则

```swift
// 从 RFC5545 格式字符串
let daily   = Recurrence(string: "FREQ=DAILY")
let weekly  = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR")
let monthly = Recurrence(string: "FREQ=MONTHLY;BYMONTHDAY=1")
let yearly  = Recurrence(string: "FREQ=YEARLY;BYMONTH=1;BYMONTHDAY=1")

// 带结束条件
let limited1 = Recurrence(string: "FREQ=DAILY;COUNT=10")         // 重复 10 次
let limited2 = Recurrence(string: "FREQ=WEEKLY;UNTIL=20241231T235959Z")  // 到指定日期

// 带间隔
let biweekly = Recurrence(string: "FREQ=WEEKLY;INTERVAL=2;BYDAY=MO")  // 每两周一次

// 创建空规则并手动设置
if let recur = Recurrence() {
    recur.frequency = .weekly
    recur.interval  = 2
    recur.count     = 5
    recur.weekStart = .monday
    print(recur.iCalString)  // "FREQ=WEEKLY;INTERVAL=2;COUNT=5;WKST=MO"
}
```

#### 读取重复规则属性

```swift
let recur = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR;COUNT=10")!

print(recur.frequency)  // .weekly
print(recur.count)      // 10
print(recur.interval)   // 1
print(recur.weekStart)  // .sunday（默认）
print(recur.until.isNull) // true（未设置结束时间）
print(recur.rscale ?? "") // RSCALE 日历系统名称
print(recur.skip)         // .omit（跳过类型）

// BY* 规则数组
print(recur.byDay)       // 编码的星期几值
print(recur.byMonthDay)  // 月内天序号
print(recur.byMonth)     // 月份
print(recur.byHour)      // 小时
print(recur.byMinute)    // 分钟
print(recur.bySecond)    // 秒
print(recur.byWeekNo)    // 年内周序号
print(recur.byYearDay)   // 年内天序号
print(recur.bySetPos)    // 集合位置

// 解码 BYDAY 值
for encodedDay in recur.byDay {
    let weekday  = Recurrence.dayOfWeek(from: encodedDay)
    let position = Recurrence.dayPosition(from: encodedDay)
    print("星期: \(weekday), 位置: \(position)")
}

// 解码 BYMONTH 值
for encodedMonth in recur.byMonth {
    let month   = Recurrence.month(from: encodedMonth)
    let isLeap  = Recurrence.isLeapMonth(from: encodedMonth)
    print("月份: \(month), 闰月: \(isLeap)")
}

// 输出 iCalendar 格式字符串
print(recur.iCalString)  // "FREQ=WEEKLY;COUNT=10;BYDAY=MO,WE,FR"
```

#### 编码/解码工具

```swift
// 星期几编码解码
let encoded = Recurrence.encodeDay(weekday: .monday, position: 2)  // 第2个周一
let weekday  = Recurrence.dayOfWeek(from: encoded)   // .monday
let position = Recurrence.dayPosition(from: encoded) // 2

// 月份编码解码
let encodedMonth = Recurrence.encodeMonth(3)          // 3月
let month        = Recurrence.month(from: encodedMonth) // 3
let isLeap       = Recurrence.isLeapMonth(from: encodedMonth) // false

// 从字符串解析枚举
Recurrence.frequency(from: "WEEKLY")  // .weekly
Recurrence.weekday(from: "MO")        // .monday
Recurrence.skip(from: "OMIT")         // .omit

// 获取支持的 RSCALE 日历系统列表
let calendars = Recurrence.rscaleSupportedCalendars
```

#### 使用迭代器遍历重复时间点

```swift
let recur = Recurrence(string: "FREQ=DAILY;COUNT=5")!
let start = Time(string: "20240601T090000Z")!

// 方式一：手动迭代
if let iter = RecurrenceIterator(rule: recur, start: start) {
    while let t = iter.next() {
        print(t.iCalString)
    }
}

// 方式二：for-in 循环（实现了 Sequence 协议）
if let iter = RecurrenceIterator(rule: recur, start: start) {
    for t in iter {
        print(t.iCalString)
    }
}

// 方式三：获取所有时间点数组
if let iter = RecurrenceIterator(rule: recur, start: start) {
    let all = iter.allOccurrences()  // 默认最多 1000 个
    print(all.count)  // 5
}

// 设置迭代结束时间
if let iter = RecurrenceIterator(rule: recur, start: start) {
    let rangeEnd = Time(string: "20240610T235959Z")!
    iter.setEnd(rangeEnd)
    let filtered = iter.allOccurrences()
}

// 同时设置起始和结束时间范围
if let iter = RecurrenceIterator(rule: recur, start: start) {
    let rangeStart = Time(string: "20240603T000000Z")!
    let rangeEnd   = Time(string: "20240610T235959Z")!
    iter.setRange(from: rangeStart, to: rangeEnd)
}

// 反向迭代
if let iter = RecurrenceIterator(rule: recur, start: start) {
    while let t = iter.previous() {
        print(t.iCalString)
    }
}
```

---

### Parser — iCalendar 解析器

#### 静态解析（推荐）

```swift
// 直接解析完整的 iCalendar 字符串
let icsString = """
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//MyApp//MyApp//EN
BEGIN:VEVENT
UID:event-001@example.com
DTSTART:20240601T090000Z
DTEND:20240601T110000Z
SUMMARY:团队会议
END:VEVENT
END:VCALENDAR
"""

if let calendar = Parser.parse(string: icsString) {
    print(calendar.kind)  // .vcalendar
    if let event = calendar.firstComponent(ofKind: .vevent) {
        print(event.summary ?? "")  // "团队会议"
    }
}

// 等价的便捷方法
let calendar2 = Component.parse(icsString)

// 从 Data 解析
if let data = icsString.data(using: .utf8) {
    let calendar3 = Component.parse(data: data)
}
```

#### 逐行解析（流式处理）

```swift
let parser = Parser()

let lines = [
    "BEGIN:VCALENDAR\r\n",
    "VERSION:2.0\r\n",
    "PRODID:-//Test//Test//EN\r\n",
    "BEGIN:VEVENT\r\n",
    "UID:line-test-001@example.com\r\n",
    "DTSTART:20240315T140000Z\r\n",
    "SUMMARY:逐行解析测试\r\n",
    "END:VEVENT\r\n",
    "END:VCALENDAR\r\n",
]

var result: Component? = nil
for line in lines {
    if let comp = parser.addLine(line) {
        result = comp
    }
}

// 检查解析状态
print(parser.state)  // .success / .error / .inProgress / .beginComp / .endComp

// 清理并获取已解析内容
if result == nil {
    result = parser.clean()
}
```

#### 全局控制字符处理

```swift
// 设置控制字符处理方式
Parser.ctrl = .omit   // 忽略控制字符（默认）
Parser.ctrl = .keep   // 保留控制字符
Parser.ctrl = .error  // 遇到控制字符报错
```

---

### 完整示例

#### 示例一：创建会议邀请

```swift
import libICAL

// 创建日历容器
let calendar = Component.vcalendar()
calendar.addProperty(Property(string: "VERSION:2.0")!)
calendar.addProperty(Property(string: "PRODID:-//MyApp//MyApp//EN")!)
calendar.method = .request  // 会议邀请

// 创建事件
let event = Component.vevent()
event.uid       = "meeting-2024-001@myapp.com"
event.summary   = "Q3 产品规划会议"
event.componentDescription = "讨论 Q3 产品路线图和资源分配"
event.location  = "北京·朝阳区·望京 SOHO T1-2001"
event.dtstart   = Time(string: "20240701T100000Z")!
event.dtend     = Time(string: "20240701T120000Z")!
event.dtstamp   = Time.now()
event.status    = .confirmed
event.sequence  = 0

// 添加组织者
let organizer = Property.organizer("mailto:pm@myapp.com")
if let cn = Parameter.cn("产品经理") {
    organizer.addParameter(cn)
}
event.addProperty(organizer)

// 添加参与者
let attendee1 = Property.attendee("mailto:dev@myapp.com")
if let cn       = Parameter.cn("开发负责人"),
   let role     = Parameter.role(.reqParticipant),
   let partstat = Parameter.partstat(.needsAction),
   let rsvp     = Parameter.rsvp(true) {
    attendee1.addParameter(cn)
    attendee1.addParameter(role)
    attendee1.addParameter(partstat)
    attendee1.addParameter(rsvp)
}
event.addProperty(attendee1)

// 添加闹钟提醒（提前 15 分钟）
let alarm = Component.valarm()
alarm.addProperty(Property(string: "ACTION:DISPLAY")!)
alarm.addProperty(Property(string: "DESCRIPTION:会议提醒")!)
alarm.addProperty(Property(string: "TRIGGER:-PT15M")!)
event.addComponent(alarm)

// 组装并输出
calendar.addComponent(event)
print(calendar.iCalString)
```

#### 示例二：解析并读取日历文件

```swift
import libICAL

let icsContent = """
BEGIN:VCALENDAR
VERSION:2.0
PRODID:-//Google Inc//Google Calendar 70.9054//EN
BEGIN:VEVENT
DTSTART:20240601T090000Z
DTEND:20240601T100000Z
RRULE:FREQ=WEEKLY;BYDAY=MO,WE,FR
SUMMARY:晨会
UID:standup@google.com
STATUS:CONFIRMED
END:VEVENT
END:VCALENDAR
"""

guard let calendar = Component.parse(icsContent) else {
    print("解析失败")
    exit(1)
}

// 遍历所有事件
for event in calendar.components(ofKind: .vevent) {
    print("标题: \(event.summary ?? "无")")
    print("开始: \(event.dtstart.iCalString)")
    print("结束: \(event.dtend.iCalString)")
    print("状态: \(event.status)")
    print("UID: \(event.uid ?? "无")")

    // 读取重复规则
    if let rruleProp = event.firstProperty(ofKind: .rrule),
       let rruleStr  = rruleProp.valueString,
       let recur     = Recurrence(string: rruleStr) {
        print("重复频率: \(recur.frequency)")

        // 展开未来 30 天内的重复实例
        let now = Time.now()
        let future = now.adjusted(days: 30)
        event.forEachRecurrence(from: now, to: future) { comp, span in
            let startDate = Date(timeIntervalSince1970: TimeInterval(span.start))
            print("  重复实例: \(startDate)")
        }
    }
    print("---")
}
```

#### 示例三：创建待办事项

```swift
import libICAL

let calendar = Component.vcalendar()
calendar.addProperty(Property(string: "VERSION:2.0")!)
calendar.addProperty(Property(string: "PRODID:-//MyApp//MyApp//EN")!)

let todo = Component.vtodo()
todo.uid       = "todo-001@myapp.com"
todo.summary   = "完成 Q3 技术方案文档"
todo.componentDescription = "包含架构设计、接口定义和性能指标"
todo.due       = Time(string: "20240630T180000Z")!
todo.dtstamp   = Time.now()
todo.status    = .needsAction
todo.addProperty(Property.priority(1))  // 最高优先级
todo.addProperty(Property.categories("工作,文档"))

calendar.addComponent(todo)
print(calendar.iCalString)
```

#### 示例四：重复规则迭代

```swift
import libICAL

// 每周一、三、五的晨会，共 10 次
guard let recur = Recurrence(string: "FREQ=WEEKLY;BYDAY=MO,WE,FR;COUNT=10"),
      let start = Time(string: "20240601T090000Z"),
      let iter  = RecurrenceIterator(rule: recur, start: start) else {
    print("创建失败")
    exit(1)
}

print("晨会时间表：")
for (index, time) in iter.enumerated() {
    let date = Date(timeIntervalSince1970: time.timeIntervalSince1970)
    print("第 \(index + 1) 次: \(date)")
}
```

#### 示例五：时区转换

```swift
import libICAL

Timezone.useBuiltinTZData = true

let utcTime = Time(string: "20240601T090000Z")!

if let shanghai = Timezone.builtin(location: "Asia/Shanghai"),
   let newYork  = Timezone.builtin(location: "America/New_York") {

    // UTC → 上海
    let shanghaiTime = utcTime.converted(to: shanghai)
    print("上海时间: \(shanghaiTime.hour):\(shanghaiTime.minute)")  // 17:00

    // UTC → 纽约
    let nyTime = utcTime.converted(to: newYork)
    print("纽约时间: \(nyTime.hour):\(nyTime.minute)")  // 5:00

    // 查询 UTC 偏移
    var isDaylight = false
    let offset = shanghai.utcOffset(for: utcTime, isDaylight: &isDaylight)
    print("上海 UTC 偏移: \(offset / 3600) 小时")  // 8
}
```

---

## 测试

项目包含完整的单元测试，覆盖所有核心类型和功能：

```bash
swift test
```

| 测试套件 | 内容 |
|---|---|
| `Time Tests` | 时间创建、属性读写、比较、转换、规范化、静态工具方法 |
| `Duration Tests` | 时长创建（秒/字符串/分量）、比较、iCal 输出 |
| `Time Arithmetic Tests` | 时间加时长、跨天、两时间相减 |
| `Period Tests` | 时间段创建、字符串解析、相等比较 |
| `Component Tests` | 组件创建/克隆/解析、属性操作、子组件操作、合并、重复事件遍历 |
| `Property Tests` | 各类属性创建、参数操作、规范化、iCal 输出 |
| `Parameter Tests` | 参数创建/克隆、X 扩展参数、比较、静态工具 |
| `Recurrence Tests` | 重复规则解析（日/周/月/年/时）、属性读取、编码解码 |
| `RecurrenceIterator Tests` | 迭代器（日/周/月/年）、范围限制、BYDAY 过滤 |
| `Timezone Tests` | UTC 时区、内置时区、UTC 偏移、时区转换 |
| `Parser Tests` | 字符串解析、中文内容、逐行解析、VTODO/VALARM/RRULE/ATTENDEE |
| `Enums Tests` | 所有枚举类型的 C 值双向转换 |
| `Integration Tests` | 完整日历往返（创建→序列化→解析）、重复事件、VTODO、多时区、属性参数 |

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
