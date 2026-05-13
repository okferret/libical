// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Component

import libical

// MARK: - Component

/// iCalendar 组件，对应 C 的 `icalcomponent *`
///
/// 组件是 iCalendar 数据的基本容器，可包含属性和子组件。
/// 常见组件类型：
/// - `VCALENDAR`：日历容器，包含所有其他组件
/// - `VEVENT`：日历事件
/// - `VTODO`：待办事项
/// - `VJOURNAL`：日记
/// - `VALARM`：闹钟（嵌套在 VEVENT/VTODO 中）
/// - `VTIMEZONE`：时区定义
///
/// 通过 `borrowing` 初始化的实例不拥有底层指针（不负责释放），
/// 通过 `owning` 初始化的实例拥有底层指针（deinit 时释放）。
public final class Component: @unchecked Sendable {

    // MARK: Internal storage

    /// 底层 C 组件指针
    internal let cPointer: OpaquePointer
    /// 是否拥有底层指针的所有权（决定 deinit 时是否释放）
    private var owned: Bool

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

    /// 将所有权转移给 libical（例如添加到父组件或 merge 后），
    /// 防止 deinit 时 double-free。
    internal func transferOwnership() {
        owned = false
    }

    /// 从 libical 收回所有权（例如从父组件移除后），
    /// 使 deinit 时正确释放内存。
    internal func reclaimOwnership() {
        owned = true
    }

    /// 创建指定类型的空组件
    /// - Parameter kind: 组件类型
    public init(kind: ComponentKind) {
        self.cPointer = icalcomponent_new(kind.cValue)
        self.owned = true
    }

    /// 从 iCalendar 格式字符串创建组件
    /// - Parameter string: iCalendar 格式字符串（如完整的 VCALENDAR 文本）
    /// - Returns: 解析成功返回组件，失败返回 nil
    public init?(string: String) {
        guard let ptr = icalcomponent_new_from_string(string) else { return nil }
        self.cPointer = ptr
        self.owned = true
    }

    deinit {
        // 仅在拥有所有权时释放底层指针（递归释放所有子组件和属性）
        if owned {
            icalcomponent_free(cPointer)
        }
    }

    // MARK: Cloning

    /// 深度克隆当前组件（包含所有属性和子组件）
    /// - Returns: 新的组件副本，内存分配失败返回 nil
    public func clone() -> Component? {
        guard let ptr = icalcomponent_clone(cPointer) else { return nil }
        return Component(owning: ptr)
    }

    // MARK: Kind & validity

    /// 组件类型
    public var kind: ComponentKind {
        ComponentKind(cValue: icalcomponent_isa(cPointer))
    }

    /// 是否为有效的 iCalendar 组件
    public var isValid: Bool {
        icalcomponent_is_valid(cPointer)
    }

    /// 组件名称字符串（如 `"VCALENDAR"`、`"VEVENT"`）
    public var componentName: String? {
        guard let ptr = icalcomponent_get_component_name(cPointer) else { return nil }
        return String(cString: ptr)
    }

    // MARK: X-NAME / IANA name

    /// X 扩展组件名称（仅对 `kind == .x` 的组件有效）
    public var xName: String? {
        get {
            guard let ptr = icalcomponent_get_x_name(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_x_name(cPointer, newValue)
        }
    }

    /// IANA 注册组件名称（仅对 `kind == .iana` 的组件有效）
    public var ianaName: String? {
        get {
            guard let ptr = icalcomponent_get_iana_name(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_iana_name(cPointer, newValue)
        }
    }

    // MARK: Properties

    /// 将属性添加到组件。
    /// ⚠️ libical 会接管该属性的所有权，调用后请勿再对 `property` 调用 free 相关操作。
    /// 传入的 `property` 必须是 owned（非 borrowing）的对象，添加后其 Swift 包装对象
    /// 的 `owned` 标志会被清除，以防止 deinit 时 double-free。
    public func addProperty(_ property: Property) {
        icalcomponent_add_property(cPointer, property.cPointer)
        // 组件接管了属性的所有权，清除 Swift 包装的 owned 标志
        property.transferOwnership()
    }

    /// 从组件中移除指定属性（属性所有权归还给调用方）
    /// - Parameter property: 要移除的属性对象
    public func removeProperty(_ property: Property) {
        icalcomponent_remove_property(cPointer, property.cPointer)
        // 属性从组件中移除后，所有权归还给 Swift 包装对象
        property.reclaimOwnership()
    }

    /// 移除组件中所有指定类型的属性
    /// - Parameter kind: 要移除的属性类型
    public func removeProperties(ofKind kind: PropertyKind) {
        icalcomponent_remove_property_by_kind(cPointer, kind.cValue)
    }

    /// 统计组件中指定类型的属性数量
    /// - Parameter kind: 属性类型，`.any` 表示统计所有属性（默认）
    /// - Returns: 属性数量
    public func countProperties(ofKind kind: PropertyKind = .any) -> Int {
        Int(icalcomponent_count_properties(cPointer, kind.cValue))
    }

    /// 获取第一个指定类型的属性（用于迭代）
    /// - Parameter kind: 属性类型，`.any` 表示任意类型（默认）
    /// - Returns: 找到的属性（借用），未找到返回 nil
    public func firstProperty(ofKind kind: PropertyKind = .any) -> Property? {
        guard let ptr = icalcomponent_get_first_property(cPointer, kind.cValue) else { return nil }
        return Property(borrowing: ptr)
    }

    /// 获取下一个指定类型的属性（配合 `firstProperty` 使用迭代）
    /// - Parameter kind: 属性类型，`.any` 表示任意类型（默认）
    /// - Returns: 下一个属性（借用），无更多属性返回 nil
    public func nextProperty(ofKind kind: PropertyKind = .any) -> Property? {
        guard let ptr = icalcomponent_get_next_property(cPointer, kind.cValue) else { return nil }
        return Property(borrowing: ptr)
    }

    /// 获取指定类型的所有属性数组
    /// - Parameter kind: 属性类型，`.any` 表示获取所有属性（默认）
    /// - Returns: 属性数组（借用，不拥有所有权）
    public func properties(ofKind kind: PropertyKind = .any) -> [Property] {
        var result: [Property] = []
        var ptr = icalcomponent_get_first_property(cPointer, kind.cValue)
        while let p = ptr {
            result.append(Property(borrowing: p))
            ptr = icalcomponent_get_next_property(cPointer, kind.cValue)
        }
        return result
    }

    // MARK: Sub-components

    /// 将子组件添加到当前组件。
    /// ⚠️ libical 会接管子组件的所有权，调用后 `child` 的 Swift 包装对象
    /// 的 `owned` 标志会被清除，以防止 deinit 时 double-free。
    public func addComponent(_ child: Component) {
        icalcomponent_add_component(cPointer, child.cPointer)
        // 父组件接管了子组件的所有权，清除 Swift 包装的 owned 标志
        child.transferOwnership()
    }

    /// 从当前组件中移除指定子组件（子组件所有权归还给调用方）
    /// - Parameter child: 要移除的子组件
    public func removeComponent(_ child: Component) {
        icalcomponent_remove_component(cPointer, child.cPointer)
        // 子组件从父组件中移除后，所有权归还给 Swift 包装对象
        child.reclaimOwnership()
    }

    /// 统计指定类型的子组件数量
    /// - Parameter kind: 组件类型，`.any` 表示统计所有子组件（默认）
    /// - Returns: 子组件数量
    public func countComponents(ofKind kind: ComponentKind = .any) -> Int {
        Int(icalcomponent_count_components(cPointer, kind.cValue))
    }

    /// 获取第一个指定类型的子组件（用于迭代）
    /// - Parameter kind: 组件类型，`.any` 表示任意类型（默认）
    /// - Returns: 找到的子组件（借用），未找到返回 nil
    public func firstComponent(ofKind kind: ComponentKind = .any) -> Component? {
        guard let ptr = icalcomponent_get_first_component(cPointer, kind.cValue) else { return nil }
        return Component(borrowing: ptr)
    }

    /// 获取下一个指定类型的子组件（配合 `firstComponent` 使用迭代）
    /// - Parameter kind: 组件类型，`.any` 表示任意类型（默认）
    /// - Returns: 下一个子组件（借用），无更多子组件返回 nil
    public func nextComponent(ofKind kind: ComponentKind = .any) -> Component? {
        guard let ptr = icalcomponent_get_next_component(cPointer, kind.cValue) else { return nil }
        return Component(borrowing: ptr)
    }

    /// 获取指定类型的所有子组件数组
    /// - Parameter kind: 组件类型，`.any` 表示获取所有子组件（默认）
    /// - Returns: 子组件数组（借用，不拥有所有权）
    public func components(ofKind kind: ComponentKind = .any) -> [Component] {
        var result: [Component] = []
        var ptr = icalcomponent_get_first_component(cPointer, kind.cValue)
        while let p = ptr {
            result.append(Component(borrowing: p))
            ptr = icalcomponent_get_next_component(cPointer, kind.cValue)
        }
        return result
    }

    /// 获取内部嵌套组件（如 VCALENDAR 内的第一个实际组件）
    public var innerComponent: Component? {
        guard let ptr = icalcomponent_get_inner(cPointer) else { return nil }
        return Component(borrowing: ptr)
    }

    /// 获取第一个"真实"子组件（跳过 VTIMEZONE 等辅助组件）
    public var firstRealComponent: Component? {
        guard let ptr = icalcomponent_get_first_real_component(cPointer) else { return nil }
        return Component(borrowing: ptr)
    }

    /// 父组件（借用，不拥有所有权）
    /// 设置时不转移所有权，仅更新父组件引用
    public var parent: Component? {
        get {
            guard let ptr = icalcomponent_get_parent(cPointer) else { return nil }
            return Component(borrowing: ptr)
        }
        set {
            icalcomponent_set_parent(cPointer, newValue?.cPointer)
        }
    }

    // MARK: Span

    /// 获取组件的时间跨度（基于 DTSTART 和 DTEND/DURATION 计算）
    public var span: TimeSpan {
        TimeSpan(cValue: icalcomponent_get_span(cPointer))
    }

    // MARK: Timezone iteration

    /// 遍历组件中所有 TZID 参数，对每个参数调用回调
    /// - Parameter callback: 对每个 TZID 参数调用的闭包（参数为借用，不拥有所有权）
    public func forEachTZID(callback: @escaping (Parameter) -> Void) {
        typealias CallbackBox = (Parameter) -> Void
        var box: CallbackBox = callback
        withUnsafeMutablePointer(to: &box) { boxPtr in
            icalcomponent_foreach_tzid(
                cPointer,
                { param, data in
                    guard let param = param, let data = data else { return }
                    let swiftParam = Parameter(borrowing: param)
                    let cb = data.assumingMemoryBound(to: CallbackBox.self).pointee
                    cb(swiftParam)
                },
                boxPtr
            )
        }
    }

    // MARK: Merge

    /// 合并另一个组件到当前组件（将 `other` 的子组件和属性移入当前组件）。
    /// ⚠️ `icalcomponent_merge_component` 会消耗（free）`other` 的底层指针，
    /// 因此调用后必须清除 `other` 的 owned 标志，防止 deinit 时 double-free。
    /// - Parameter other: 要合并的组件（合并后不可再使用）
    public func merge(_ other: Component) {
        icalcomponent_merge_component(cPointer, other.cPointer)
        // merge 后 other 的底层指针已被 libical 释放，清除 owned 标志
        other.transferOwnership()
    }

    // MARK: Convenience properties

    /// 事件开始时间（DTSTART 属性）
    public var dtstart: Time {
        get { Time(cValue: icalcomponent_get_dtstart(cPointer)) }
        set { icalcomponent_set_dtstart(cPointer, newValue.cValue) }
    }

    /// 事件结束时间（DTEND 属性，VEVENT 使用）
    public var dtend: Time {
        get { Time(cValue: icalcomponent_get_dtend(cPointer)) }
        set { icalcomponent_set_dtend(cPointer, newValue.cValue) }
    }

    /// 待办截止时间（DUE 属性，VTODO 使用）
    public var due: Time {
        get { Time(cValue: icalcomponent_get_due(cPointer)) }
        set { icalcomponent_set_due(cPointer, newValue.cValue) }
    }

    /// 持续时长（DURATION 属性）
    public var duration: Duration {
        get { Duration(cValue: icalcomponent_get_duration(cPointer)) }
        set { icalcomponent_set_duration(cPointer, newValue.cValue) }
    }

    /// 时间戳（DTSTAMP 属性，记录组件创建或最后修改时间）
    public var dtstamp: Time {
        get { Time(cValue: icalcomponent_get_dtstamp(cPointer)) }
        set { icalcomponent_set_dtstamp(cPointer, newValue.cValue) }
    }

    /// 摘要/标题（SUMMARY 属性）
    public var summary: String? {
        get {
            guard let ptr = icalcomponent_get_summary(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_summary(cPointer, newValue ?? "")
        }
    }

    /// 详细描述（DESCRIPTION 属性）
    /// 注意：属性名使用 `componentDescription` 以避免与 Swift 的 `description` 冲突
    public var componentDescription: String? {
        get {
            guard let ptr = icalcomponent_get_description(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_description(cPointer, newValue ?? "")
        }
    }

    /// 地点（LOCATION 属性）
    public var location: String? {
        get {
            guard let ptr = icalcomponent_get_location(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_location(cPointer, newValue ?? "")
        }
    }

    /// 唯一标识符（UID 属性，全局唯一）
    public var uid: String? {
        get {
            guard let ptr = icalcomponent_get_uid(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_uid(cPointer, newValue ?? "")
        }
    }

    /// 注释（COMMENT 属性）
    public var comment: String? {
        get {
            guard let ptr = icalcomponent_get_comment(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_comment(cPointer, newValue ?? "")
        }
    }

    /// 关联日历标识（RELCALID 属性）
    public var relcalid: String? {
        get {
            guard let ptr = icalcomponent_get_relcalid(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalcomponent_set_relcalid(cPointer, newValue ?? "")
        }
    }

    /// 重复标识（RECURRENCE-ID 属性，用于标识重复事件的特定实例）
    public var recurrenceID: Time {
        get { Time(cValue: icalcomponent_get_recurrenceid(cPointer)) }
        set { icalcomponent_set_recurrenceid(cPointer, newValue.cValue) }
    }

    /// 序列号（SEQUENCE 属性，每次修改事件时递增）
    public var sequence: Int {
        get { Int(icalcomponent_get_sequence(cPointer)) }
        set { icalcomponent_set_sequence(cPointer, Int32(newValue)) }
    }

    /// 日历方法（METHOD 属性，用于 iTIP 调度）
    public var method: PropertyMethod {
        get { PropertyMethod(cValue: icalcomponent_get_method(cPointer)) }
        set { icalcomponent_set_method(cPointer, newValue.cValue) }
    }

    /// 状态（STATUS 属性）
    public var status: PropertyStatus {
        get { PropertyStatus(cValue: icalcomponent_get_status(cPointer)) }
        set { icalcomponent_set_status(cPointer, newValue.cValue) }
    }

    // MARK: Timezone

    /// 根据 TZID 获取组件中定义的时区
    /// - Parameter tzid: 时区标识符
    /// - Returns: 找到的时区（借用），未找到返回 nil
    public func timezone(forTZID tzid: String) -> Timezone? {
        guard let ptr = icalcomponent_get_timezone(cPointer, tzid) else { return nil }
        return Timezone(borrowing: ptr)
    }

    // MARK: Error handling

    /// 组件中的错误属性数量（XLICERROR 属性）
    public var errorCount: Int {
        Int(icalcomponent_count_errors(cPointer))
    }

    /// 移除组件中所有错误属性（XLICERROR）
    public func stripErrors() {
        icalcomponent_strip_errors(cPointer)
    }

    /// 将错误属性转换为标准属性（尝试修复解析错误）
    public func convertErrors() {
        icalcomponent_convert_errors(cPointer)
    }

    /// 检查组件是否符合 RFC5545 限制规则
    /// - Returns: 符合规则返回 true，存在违规返回 false
    public func checkRestrictions() -> Bool {
        icalcomponent_check_restrictions(cPointer)
    }

    // MARK: Normalization

    /// 规范化组件（排序属性、规范化值格式、添加必要属性等）
    public func normalize() {
        icalcomponent_normalize(cPointer)
    }

    // MARK: Recurrence

    /// 遍历组件在指定时间范围内的所有重复实例
    /// - Parameters:
    ///   - start: 时间范围起始
    ///   - end: 时间范围结束
    ///   - callback: 对每个重复实例调用的闭包，参数为组件（借用）和时间跨度
    public func forEachRecurrence(
        from start: Time,
        to end: Time,
        callback: @escaping (Component, TimeSpan) -> Void
    ) {
        typealias CallbackBox = (Component, TimeSpan) -> Void
        var box: CallbackBox = callback
        withUnsafeMutablePointer(to: &box) { boxPtr in
            icalcomponent_foreach_recurrence(
                cPointer,
                start.cValue,
                end.cValue,
                { comp, span, data in
                    guard let comp = comp, let span = span, let data = data else { return }
                    let swiftComp = Component(borrowing: comp)
                    let swiftSpan = TimeSpan(cValue: span.pointee)
                    let cb = data.assumingMemoryBound(to: CallbackBox.self).pointee
                    cb(swiftComp, swiftSpan)
                },
                boxPtr
            )
        }
    }

    // MARK: Conversion

    /// 将组件转换为 iCalendar 格式字符串（完整的文本表示）
    public var iCalString: String {
        guard let ptr = icalcomponent_as_ical_string_r(cPointer) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    // MARK: Static helpers

    /// 将组件类型转换为字符串名称（如 `.vevent` → `"VEVENT"`）
    /// - Parameter kind: 组件类型
    /// - Returns: 组件名称字符串，无效类型返回 nil
    public static func kindToString(_ kind: ComponentKind) -> String? {
        guard let ptr = icalcomponent_kind_to_string(kind.cValue) else { return nil }
        return String(cString: ptr)
    }

    /// 从字符串名称解析组件类型（如 `"VEVENT"` → `.vevent`）
    /// - Parameter string: 组件名称字符串
    /// - Returns: 对应的组件类型
    public static func kind(from string: String) -> ComponentKind {
        ComponentKind(cValue: icalcomponent_string_to_kind(string))
    }

    /// 判断组件类型是否有效
    /// - Parameter kind: 组件类型
    /// - Returns: 有效返回 true
    public static func isValid(kind: ComponentKind) -> Bool {
        icalcomponent_kind_is_valid(kind.cValue)
    }
}

// MARK: - Component + CustomStringConvertible

extension Component: CustomStringConvertible {
    /// 返回组件的 iCalendar 格式字符串表示
    public var description: String { iCalString }
}

// MARK: - Convenience constructors

/// 常用组件类型的便捷构造方法
extension Component {

    /// 创建 VCALENDAR 组件（日历容器）
    public static func vcalendar() -> Component {
        Component(owning: icalcomponent_new_vcalendar())
    }

    /// 创建 VEVENT 组件（日历事件）
    public static func vevent() -> Component {
        Component(owning: icalcomponent_new_vevent())
    }

    /// 创建 VTODO 组件（待办事项）
    public static func vtodo() -> Component {
        Component(owning: icalcomponent_new_vtodo())
    }

    /// 创建 VJOURNAL 组件（日记）
    public static func vjournal() -> Component {
        Component(owning: icalcomponent_new_vjournal())
    }

    /// 创建 VALARM 组件（闹钟提醒）
    public static func valarm() -> Component {
        Component(owning: icalcomponent_new_valarm())
    }

    /// 创建 VFREEBUSY 组件（空闲/忙碌信息）
    public static func vfreebusy() -> Component {
        Component(owning: icalcomponent_new_vfreebusy())
    }

    /// 创建 VTIMEZONE 组件（时区定义）
    public static func vtimezone() -> Component {
        Component(owning: icalcomponent_new_vtimezone())
    }

    /// 创建 STANDARD 组件（VTIMEZONE 的标准时间子组件）
    public static func xstandard() -> Component {
        Component(owning: icalcomponent_new_xstandard())
    }

    /// 创建 DAYLIGHT 组件（VTIMEZONE 的夏令时子组件）
    public static func xdaylight() -> Component {
        Component(owning: icalcomponent_new_xdaylight())
    }

    /// 创建 VAGENDA 组件（议程）
    public static func vagenda() -> Component {
        Component(owning: icalcomponent_new_vagenda())
    }

    /// 创建 VQUERY 组件（查询）
    public static func vquery() -> Component {
        Component(owning: icalcomponent_new_vquery())
    }

    /// 创建 VREPLY 组件（回复）
    public static func vreply() -> Component {
        Component(owning: icalcomponent_new_vreply())
    }

    /// 创建 VAVAILABILITY 组件（可用性信息）
    public static func vavailability() -> Component {
        Component(owning: icalcomponent_new_vavailability())
    }

    /// 创建 AVAILABLE 组件（VAVAILABILITY 的可用时间子组件）
    public static func xavailable() -> Component {
        Component(owning: icalcomponent_new_xavailable())
    }

    /// 创建 VPOLL 组件（投票）
    public static func vpoll() -> Component {
        Component(owning: icalcomponent_new_vpoll())
    }

    /// 创建 VVOTER 组件（投票者）
    public static func vvoter() -> Component {
        Component(owning: icalcomponent_new_vvoter())
    }

    /// 创建 VOTE 组件（投票记录）
    public static func xvote() -> Component {
        Component(owning: icalcomponent_new_xvote())
    }

    /// 创建 VPATCH 组件（补丁）
    public static func vpatch() -> Component {
        Component(owning: icalcomponent_new_vpatch())
    }

    /// 创建 PATCH 组件（补丁内容）
    public static func xpatch() -> Component {
        Component(owning: icalcomponent_new_xpatch())
    }

    /// 创建 PARTICIPANT 组件（参与者）
    public static func participant() -> Component {
        Component(owning: icalcomponent_new_participant())
    }

    /// 创建 VLOCATION 组件（位置）
    public static func vlocation() -> Component {
        Component(owning: icalcomponent_new_vlocation())
    }

    /// 创建 VRESOURCE 组件（资源）
    public static func vresource() -> Component {
        Component(owning: icalcomponent_new_vresource())
    }

    /// 创建 X 扩展组件（自定义扩展组件）
    /// - Parameter name: 扩展组件名称（应以 `"X-"` 开头）
    /// - Returns: 创建成功返回组件，失败返回 nil
    public static func x(name: String) -> Component? {
        guard let ptr = icalcomponent_new_x(name) else { return nil }
        return Component(owning: ptr)
    }

    /// 创建 IANA 注册组件
    /// - Parameter name: IANA 注册的组件名称
    /// - Returns: 创建成功返回组件，失败返回 nil
    public static func iana(name: String) -> Component? {
        guard let ptr = icalcomponent_new_iana(name) else { return nil }
        return Component(owning: ptr)
    }
}

// MARK: - TimeSpan

/// 时间跨度，对应 C 的 `icaltime_span`
///
/// 表示一个以 Unix 时间戳（秒）为单位的时间区间，
/// 用于 `icalcomponent_get_span` 和 `forEachRecurrence` 回调。
public struct TimeSpan: Equatable, Sendable {
    /// 起始时间（Unix 时间戳，秒）
    public let start: Int
    /// 结束时间（Unix 时间戳，秒）
    public let end: Int
    /// 是否为忙碌时间段（用于空闲/忙碌查询）
    public let isBusy: Bool

    /// 从底层 C 结构体创建
    internal init(cValue: icaltime_span) {
        self.start = Int(cValue.start)
        self.end = Int(cValue.end)
        self.isBusy = cValue.is_busy != 0
    }
}
