// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Property

import libical

// MARK: - Property

/// iCalendar 属性，对应 C 的 `icalproperty *`
///
/// 属性是 iCalendar 组件的基本数据单元，例如：
/// - `SUMMARY:会议`（摘要属性）
/// - `DTSTART:20240101T120000Z`（开始时间属性）
/// - `ATTENDEE;CN=张三:mailto:zhangsan@example.com`（参与者属性，含参数）
///
/// 通过 `borrowing` 初始化的实例不拥有底层指针（不负责释放），
/// 通过 `owning` 初始化的实例拥有底层指针（deinit 时释放）。
public final class Property: @unchecked Sendable {

    // MARK: Internal storage

    /// 底层 C 属性指针
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

    /// 将所有权转移给 libical（例如添加到组件后），防止 deinit 时 double-free。
    internal func transferOwnership() {
        owned = false
    }

    /// 从 libical 收回所有权（例如从组件移除后），使 deinit 时正确释放内存。
    internal func reclaimOwnership() {
        owned = true
    }

    /// 创建指定类型的空属性
    /// - Parameter kind: 属性类型
    public init(kind: PropertyKind) {
        self.cPointer = icalproperty_new(kind.cValue)
        self.owned = true
    }

    /// 从 iCalendar 格式字符串创建属性（如 `"SUMMARY:会议"`）
    /// - Parameter string: iCalendar 格式的属性字符串
    /// - Returns: 解析成功返回属性对象，失败返回 nil
    public init?(string: String) {
        guard let ptr = icalproperty_new_from_string(string) else { return nil }
        self.cPointer = ptr
        self.owned = true
    }

    deinit {
        // 仅在拥有所有权时释放底层指针
        if owned {
            icalproperty_free(cPointer)
        }
    }

    // MARK: Cloning

    /// 克隆当前属性，返回独立副本（包含所有参数）
    /// - Returns: 新的属性副本，内存分配失败返回 nil
    public func clone() -> Property? {
        guard let ptr = icalproperty_clone(cPointer) else { return nil }
        return Property(owning: ptr)
    }

    // MARK: Kind

    /// 属性类型
    public var kind: PropertyKind {
        PropertyKind(cValue: icalproperty_isa(cPointer))
    }

    /// 属性名称字符串（如 `"SUMMARY"`、`"X-CUSTOM-PROP"`）
    public var name: String? {
        guard let ptr = icalproperty_get_property_name(cPointer) else { return nil }
        return String(cString: ptr)
    }

    // MARK: Value

    /// 属性值的字符串表示
    /// 使用 `_r` 版本返回独立分配的缓冲区，线程安全，需要手动释放
    public var valueString: String? {
        guard let ptr = icalproperty_get_value_as_string_r(cPointer) else { return nil }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 从字符串设置属性值
    /// - Parameters:
    ///   - string: 属性值字符串
    ///   - type: 值类型名称（如 `"TEXT"`、`"DATE-TIME"`），默认 `"NO"` 表示自动推断
    public func setValue(string: String, type: String = "NO") {
        icalproperty_set_value_from_string(cPointer, string, type)
    }

    // MARK: X-NAME / IANA name

    /// X 扩展属性名称（仅对 `kind == .x` 的属性有效，如 `"X-APPLE-TRAVEL-DURATION"`）
    public var xName: String? {
        get {
            guard let ptr = icalproperty_get_x_name(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalproperty_set_x_name(cPointer, newValue)
        }
    }

    /// IANA 注册属性名称（仅对 `kind == .x` 且为 IANA 属性时有效）
    public var ianaName: String? {
        get {
            guard let ptr = icalproperty_get_iana_name(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalproperty_set_iana_name(cPointer, newValue)
        }
    }

    // MARK: Parameters

    /// 属性包含的参数数量
    public var parameterCount: Int {
        Int(icalproperty_count_parameters(cPointer))
    }

    /// 将参数添加到属性。
    /// ⚠️ libical 会接管该参数的所有权，调用后 `parameter` 的 Swift 包装对象
    /// 的 `owned` 标志会被清除，以防止 deinit 时 double-free。
    public func addParameter(_ parameter: Parameter) {
        icalproperty_add_parameter(cPointer, parameter.cPointer)
        parameter.transferOwnership()
    }

    /// 设置参数（替换同类型的已有参数）。
    /// ⚠️ libical 会接管该参数的所有权，调用后 `parameter` 的 Swift 包装对象
    /// 的 `owned` 标志会被清除，以防止 deinit 时 double-free。
    public func setParameter(_ parameter: Parameter) {
        icalproperty_set_parameter(cPointer, parameter.cPointer)
        parameter.transferOwnership()
    }

    /// 移除指定类型的所有参数
    /// - Parameter kind: 要移除的参数类型
    public func removeParameters(ofKind kind: ParameterKind) {
        icalproperty_remove_parameter_by_kind(cPointer, kind.cValue)
    }

    /// 移除指定名称的所有参数
    /// - Parameter name: 参数名称字符串（如 `"TZID"`）
    public func removeParameters(named name: String) {
        icalproperty_remove_parameter_by_name(cPointer, name)
    }

    /// 移除指定的参数对象
    /// - Parameter parameter: 要移除的参数对象
    public func removeParameter(_ parameter: Parameter) {
        icalproperty_remove_parameter_by_ref(cPointer, parameter.cPointer)
    }

    /// 获取第一个指定类型的参数（用于迭代）
    /// - Parameter kind: 参数类型，`.any` 表示任意类型
    /// - Returns: 找到的参数（借用），未找到返回 nil
    public func firstParameter(ofKind kind: ParameterKind) -> Parameter? {
        guard let ptr = icalproperty_get_first_parameter(cPointer, kind.cValue) else { return nil }
        return Parameter(borrowing: ptr)
    }

    /// 获取下一个指定类型的参数（配合 `firstParameter` 使用迭代）
    /// - Parameter kind: 参数类型，`.any` 表示任意类型
    /// - Returns: 下一个参数（借用），无更多参数返回 nil
    public func nextParameter(ofKind kind: ParameterKind) -> Parameter? {
        guard let ptr = icalproperty_get_next_parameter(cPointer, kind.cValue) else { return nil }
        return Parameter(borrowing: ptr)
    }

    /// 获取指定类型的所有参数数组
    /// - Parameter kind: 参数类型，`.any` 表示获取所有参数（默认）
    /// - Returns: 参数数组（借用，不拥有所有权）
    public func parameters(ofKind kind: ParameterKind = .any) -> [Parameter] {
        var result: [Parameter] = []
        var ptr = icalproperty_get_first_parameter(cPointer, kind.cValue)
        while let p = ptr {
            result.append(Parameter(borrowing: p))
            ptr = icalproperty_get_next_parameter(cPointer, kind.cValue)
        }
        return result
    }

    /// 获取指定名称的参数值字符串
    /// - Parameter name: 参数名称（如 `"TZID"`）
    /// - Returns: 参数值字符串，未找到返回 nil
    public func parameterValue(named name: String) -> String? {
        guard let ptr = icalproperty_get_parameter_as_string(cPointer, name) else { return nil }
        return String(cString: ptr)
    }

    /// 通过名称和值字符串设置参数
    /// - Parameters:
    ///   - name: 参数名称（如 `"TZID"`）
    ///   - value: 参数值字符串（如 `"America/New_York"`）
    public func setParameter(name: String, value: String) {
        icalproperty_set_parameter_from_string(cPointer, name, value)
    }

    // MARK: Normalization

    /// 规范化属性（排序参数、规范化值格式等）
    public func normalize() {
        icalproperty_normalize(cPointer)
    }

    // MARK: Conversion

    /// 将属性转换为 iCalendar 格式字符串（包含参数和值）
    public var iCalString: String {
        guard let ptr = icalproperty_as_ical_string_r(cPointer) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    // MARK: Static helpers

    /// 将属性类型转换为字符串名称（如 `.summary` → `"SUMMARY"`）
    /// - Parameter kind: 属性类型
    /// - Returns: 属性名称字符串，无效类型返回 nil
    public static func kindToString(_ kind: PropertyKind) -> String? {
        guard let ptr = icalproperty_kind_to_string(kind.cValue) else { return nil }
        return String(cString: ptr)
    }

    /// 从字符串名称解析属性类型（如 `"SUMMARY"` → `.summary`）
    /// - Parameter string: 属性名称字符串
    /// - Returns: 对应的属性类型
    public static func kind(from string: String) -> PropertyKind {
        PropertyKind(cValue: icalproperty_string_to_kind(string))
    }

    /// 判断属性类型是否有效
    /// - Parameter kind: 属性类型
    /// - Returns: 有效返回 true
    public static func isValid(kind: PropertyKind) -> Bool {
        icalproperty_kind_is_valid(kind.cValue)
    }

    /// 获取属性类型对应的默认值类型
    /// - Parameter propertyKind: 属性类型
    /// - Returns: 对应的 C 值类型
    public static func valueKind(for propertyKind: PropertyKind) -> icalvalue_kind {
        icalproperty_kind_to_value_kind(propertyKind.cValue)
    }

    /// 根据值类型获取对应的属性类型
    /// - Parameter valueKind: C 值类型
    /// - Returns: 对应的属性类型
    public static func propertyKind(for valueKind: icalvalue_kind) -> PropertyKind {
        PropertyKind(cValue: icalproperty_value_kind_to_kind(valueKind))
    }

    /// 将枚举整数值转换为对应的字符串（如状态、方法等枚举值）
    /// - Parameter e: 枚举整数值
    /// - Returns: 对应的字符串，无效值返回 nil
    public static func enumToString(_ e: Int) -> String? {
        guard let ptr = icalproperty_enum_to_string_r(Int32(e)) else { return nil }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 根据属性类型和字符串获取对应的枚举整数值
    /// - Parameters:
    ///   - kind: 属性类型
    ///   - string: 枚举值字符串（如 `"CONFIRMED"`）
    /// - Returns: 对应的枚举整数值
    public static func enumValue(for kind: PropertyKind, string: String) -> Int {
        Int(icalproperty_kind_and_string_to_enum(Int32(kind.cValue.rawValue), string))
    }

    /// 判断枚举整数值是否属于指定属性类型
    /// - Parameters:
    ///   - kind: 属性类型
    ///   - e: 枚举整数值
    /// - Returns: 属于该属性类型返回 true
    public static func enumBelongs(to kind: PropertyKind, enum e: Int) -> Bool {
        icalproperty_enum_belongs_to_property(kind.cValue, Int32(e))
    }

    /// 从字符串解析状态枚举值
    /// - Parameter string: 状态字符串（如 `"CONFIRMED"`）
    /// - Returns: 对应的 C 状态枚举值
    public static func status(from string: String) -> icalproperty_status {
        icalproperty_string_to_status(string)
    }

    /// 从字符串解析动作枚举值
    /// - Parameter string: 动作字符串（如 `"AUDIO"`）
    /// - Returns: 对应的 C 动作枚举值
    public static func action(from string: String) -> icalproperty_action {
        icalproperty_string_to_action(string)
    }

    /// 从字符串解析透明度枚举值
    /// - Parameter string: 透明度字符串（如 `"OPAQUE"`）
    /// - Returns: 对应的 C 透明度枚举值
    public static func transp(from string: String) -> icalproperty_transp {
        icalproperty_string_to_transp(string)
    }

    /// 从字符串解析访问分类枚举值
    /// - Parameter string: 分类字符串（如 `"PUBLIC"`）
    /// - Returns: 对应的 C 分类枚举值
    public static func `class`(from string: String) -> icalproperty_class {
        icalproperty_string_to_class(string)
    }

    /// 从字符串解析日历方法枚举值
    /// - Parameter string: 方法字符串（如 `"REQUEST"`）
    /// - Returns: 对应的方法枚举值
    public static func method(from string: String) -> PropertyMethod {
        PropertyMethod(cValue: icalproperty_string_to_method(string))
    }

    /// 从字符串解析参与者类型枚举值
    /// - Parameter string: 参与者类型字符串
    /// - Returns: 对应的 C 参与者类型枚举值
    public static func participantType(from string: String) -> icalproperty_participanttype {
        icalproperty_string_to_participanttype(string)
    }

    /// 从字符串解析资源类型枚举值
    /// - Parameter string: 资源类型字符串
    /// - Returns: 对应的 C 资源类型枚举值
    public static func resourceType(from string: String) -> icalproperty_resourcetype {
        icalproperty_string_to_resourcetype(string)
    }

    /// 是否允许空值属性（全局设置）
    /// 设置为 true 时，值为空的属性不会被过滤
    public static var allowEmptyProperties: Bool {
        get { icalproperty_get_allow_empty_properties() }
        set { icalproperty_set_allow_empty_properties(newValue) }
    }
}

// MARK: - Property + CustomStringConvertible

extension Property: CustomStringConvertible {
    /// 返回属性的 iCalendar 格式字符串表示
    public var description: String { iCalString }
}

// MARK: - Convenience constructors

/// 常用属性的便捷构造方法
extension Property {

    /// 创建 SUMMARY 属性（摘要/标题）
    /// - Parameter value: 摘要文本
    public static func summary(_ value: String) -> Property {
        let p = Property(kind: .summary)
        p.setValue(string: value)
        return p
    }

    /// 创建 DESCRIPTION 属性（详细描述）
    /// - Parameter value: 描述文本
    public static func description(_ value: String) -> Property {
        let p = Property(kind: .description)
        p.setValue(string: value)
        return p
    }

    /// 创建 LOCATION 属性（地点）
    /// - Parameter value: 地点文本
    public static func location(_ value: String) -> Property {
        let p = Property(kind: .location)
        p.setValue(string: value)
        return p
    }

    /// 创建 UID 属性（唯一标识符）
    /// - Parameter value: UID 字符串（建议使用 UUID 格式）
    public static func uid(_ value: String) -> Property {
        let p = Property(kind: .uid)
        p.setValue(string: value)
        return p
    }

    /// 创建 DTSTART 属性（开始时间）
    /// - Parameter time: 开始时间
    public static func dtstart(_ time: Time) -> Property {
        let p = Property(kind: .dtstart)
        p.setValue(string: time.iCalString)
        return p
    }

    /// 创建 DTEND 属性（结束时间）
    /// - Parameter time: 结束时间
    public static func dtend(_ time: Time) -> Property {
        let p = Property(kind: .dtend)
        p.setValue(string: time.iCalString)
        return p
    }

    /// 创建 DURATION 属性（持续时长）
    /// - Parameter duration: 持续时长
    public static func duration(_ duration: Duration) -> Property {
        let p = Property(kind: .duration)
        p.setValue(string: duration.iCalString)
        return p
    }

    /// 创建 DTSTAMP 属性（时间戳，记录创建/修改时间）
    /// - Parameter time: 时间戳时间（通常为 UTC）
    public static func dtstamp(_ time: Time) -> Property {
        let p = Property(kind: .dtstamp)
        p.setValue(string: time.iCalString)
        return p
    }

    /// 创建 STATUS 属性（状态）
    /// - Parameter status: 状态枚举值
    public static func status(_ status: PropertyStatus) -> Property {
        let p = Property(kind: .status)
        p.setValue(string: status.iCalString)
        return p
    }

    /// 创建 METHOD 属性（日历方法）
    /// - Parameter method: 方法枚举值
    public static func method(_ method: PropertyMethod) -> Property {
        let p = Property(kind: .method)
        p.setValue(string: method.iCalString)
        return p
    }

    /// 创建 CLASS 属性（访问分类）
    /// - Parameter cls: 访问分类枚举值
    public static func `class`(_ cls: PropertyClass) -> Property {
        let p = Property(kind: .class)
        p.setValue(string: cls.iCalString)
        return p
    }

    /// 创建 TRANSP 属性（时间透明度）
    /// - Parameter transp: 透明度枚举值
    public static func transp(_ transp: PropertyTransp) -> Property {
        let p = Property(kind: .transp)
        p.setValue(string: transp.iCalString)
        return p
    }

    /// 创建 SEQUENCE 属性（序列号，每次修改递增）
    /// - Parameter value: 序列号（非负整数）
    public static func sequence(_ value: Int) -> Property {
        let p = Property(kind: .sequence)
        p.setValue(string: "\(value)")
        return p
    }

    /// 创建 ATTENDEE 属性（参与者）
    /// - Parameter calAddress: 参与者的日历地址（如 `"mailto:user@example.com"`）
    public static func attendee(_ calAddress: String) -> Property {
        let p = Property(kind: .attendee)
        p.setValue(string: calAddress)
        return p
    }

    /// 创建 ORGANIZER 属性（组织者）
    /// - Parameter calAddress: 组织者的日历地址（如 `"mailto:organizer@example.com"`）
    public static func organizer(_ calAddress: String) -> Property {
        let p = Property(kind: .organizer)
        p.setValue(string: calAddress)
        return p
    }

    /// 创建 COMMENT 属性（注释）
    /// - Parameter value: 注释文本
    public static func comment(_ value: String) -> Property {
        let p = Property(kind: .comment)
        p.setValue(string: value)
        return p
    }

    /// 创建 CATEGORIES 属性（分类标签）
    /// - Parameter value: 分类字符串（多个分类以逗号分隔）
    public static func categories(_ value: String) -> Property {
        let p = Property(kind: .categories)
        p.setValue(string: value)
        return p
    }

    /// 创建 PRIORITY 属性（优先级）
    /// - Parameter value: 优先级（0=未定义，1=最高，9=最低）
    public static func priority(_ value: Int) -> Property {
        let p = Property(kind: .priority)
        p.setValue(string: "\(value)")
        return p
    }

    /// 创建 URL 属性（相关 URL）
    /// - Parameter value: URL 字符串
    public static func url(_ value: String) -> Property {
        let p = Property(kind: .url)
        p.setValue(string: value)
        return p
    }
}

// MARK: - PropertyStatus iCalString helper

extension PropertyStatus {
    /// 将状态枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:           return "X"
        case .tentative:   return "TENTATIVE"
        case .confirmed:   return "CONFIRMED"
        case .completed:   return "COMPLETED"
        case .needsAction: return "NEEDS-ACTION"
        case .cancelled:   return "CANCELLED"
        case .inProcess:   return "IN-PROCESS"
        case .draft:       return "DRAFT"
        case .final:       return "FINAL"
        case .none:        return "NONE"
        }
    }
}

// MARK: - PropertyMethod iCalString helper

extension PropertyMethod {
    /// 将方法枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:              return "X"
        case .publish:        return "PUBLISH"
        case .request:        return "REQUEST"
        case .reply:          return "REPLY"
        case .add:            return "ADD"
        case .cancel:         return "CANCEL"
        case .refresh:        return "REFRESH"
        case .counter:        return "COUNTER"
        case .declineCounter: return "DECLINECOUNTER"
        case .none:           return "NONE"
        }
    }
}

// MARK: - PropertyClass iCalString helper

extension PropertyClass {
    /// 将访问分类枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:            return "X"
        case .public:       return "PUBLIC"
        case .private:      return "PRIVATE"
        case .confidential: return "CONFIDENTIAL"
        case .none:         return "NONE"
        }
    }
}

// MARK: - PropertyTransp iCalString helper

extension PropertyTransp {
    /// 将透明度枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:           return "X"
        case .opaque:      return "OPAQUE"
        case .transparent: return "TRANSPARENT"
        case .none:        return "NONE"
        }
    }
}
