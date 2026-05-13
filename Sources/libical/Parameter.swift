// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Parameter

import libical

// MARK: - Parameter

/// iCalendar 属性参数，对应 C 的 `icalparameter *`
///
/// 参数附加在属性上，提供属性值的额外元数据，例如：
/// - `TZID=America/New_York`（时区参数）
/// - `CN=张三`（通用名称参数）
/// - `PARTSTAT=ACCEPTED`（参与状态参数）
///
/// 通过 `borrowing` 初始化的实例不拥有底层指针（不负责释放），
/// 通过 `owning` 初始化的实例拥有底层指针（deinit 时释放）。
public final class Parameter: @unchecked Sendable {

    // MARK: Internal storage

    /// 底层 C 参数指针
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

    /// 将所有权转移给 libical（例如添加到属性后），防止 deinit 时 double-free。
    internal func transferOwnership() {
        owned = false
    }

    /// 从 libical 收回所有权（例如从属性移除后），使 deinit 时正确释放内存。
    internal func reclaimOwnership() {
        owned = true
    }

    /// 创建指定类型的空参数
    /// - Parameter kind: 参数类型
    public init(kind: ParameterKind) {
        self.cPointer = icalparameter_new(kind.cValue)
        self.owned = true
    }

    /// 从 iCalendar 格式字符串创建参数（如 `"TZID=America/New_York"`）
    /// - Parameter string: iCalendar 格式的参数字符串
    /// - Returns: 解析成功返回参数对象，失败返回 nil
    public init?(string: String) {
        guard let ptr = icalparameter_new_from_string(string) else { return nil }
        self.cPointer = ptr
        self.owned = true
    }

    /// 从参数类型和值字符串创建参数
    /// - Parameters:
    ///   - kind: 参数类型
    ///   - value: 参数值字符串
    /// - Returns: 创建成功返回参数对象，失败返回 nil
    public init?(kind: ParameterKind, value: String) {
        guard let ptr = icalparameter_new_from_value_string(kind.cValue, value) else { return nil }
        self.cPointer = ptr
        self.owned = true
    }

    deinit {
        // 仅在拥有所有权时释放底层指针
        if owned {
            icalparameter_free(cPointer)
        }
    }

    // MARK: Cloning

    /// 克隆当前参数，返回独立副本
    /// - Returns: 新的参数副本，内存分配失败返回 nil
    public func clone() -> Parameter? {
        guard let ptr = icalparameter_clone(cPointer) else { return nil }
        return Parameter(owning: ptr)
    }

    // MARK: Properties

    /// 参数类型
    public var kind: ParameterKind {
        ParameterKind(cValue: icalparameter_isa(cPointer))
    }

    /// X 扩展参数名称（仅对 `kind == .x` 的参数有效）
    public var xname: String? {
        get {
            guard let ptr = icalparameter_get_xname(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalparameter_set_xname(cPointer, newValue)
        }
    }

    /// X 扩展参数值（仅对 `kind == .x` 的参数有效）
    public var xvalue: String? {
        get {
            guard let ptr = icalparameter_get_xvalue(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalparameter_set_xvalue(cPointer, newValue)
        }
    }

    /// IANA 注册参数名称（仅对 `kind == .iana` 的参数有效）
    public var ianaName: String? {
        get {
            guard let ptr = icalparameter_get_iana_name(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalparameter_set_iana_name(cPointer, newValue)
        }
    }

    /// IANA 注册参数值（仅对 `kind == .iana` 的参数有效）
    public var ianaValue: String? {
        get {
            guard let ptr = icalparameter_get_iana_value(cPointer) else { return nil }
            return String(cString: ptr)
        }
        set {
            icalparameter_set_iana_value(cPointer, newValue)
        }
    }

    /// 是否为多值参数（参数值包含多个以逗号分隔的值）
    public var isMultivalued: Bool {
        icalparameter_is_multivalued(cPointer)
    }

    // MARK: Conversion

    /// 将参数转换为 iCalendar 格式字符串（如 `"TZID=America/New_York"`）
    public var iCalString: String {
        guard let ptr = icalparameter_as_ical_string_r(cPointer) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    // MARK: Comparison

    /// 判断两个参数是否具有相同的参数名（类型相同）
    /// - Parameter other: 另一个参数
    /// - Returns: 参数名相同返回 true
    public func hasSameName(as other: Parameter) -> Bool {
        icalparameter_has_same_name(cPointer, other.cPointer)
    }

    // MARK: Static helpers

    /// 将参数类型转换为字符串名称（如 `.tzid` → `"TZID"`）
    /// - Parameter kind: 参数类型
    /// - Returns: 参数名称字符串，无效类型返回 nil
    public static func kindToString(_ kind: ParameterKind) -> String? {
        guard let ptr = icalparameter_kind_to_string(kind.cValue) else { return nil }
        return String(cString: ptr)
    }

    /// 从字符串名称解析参数类型（如 `"TZID"` → `.tzid`）
    /// - Parameter string: 参数名称字符串
    /// - Returns: 对应的参数类型
    public static func kind(from string: String) -> ParameterKind {
        ParameterKind(cValue: icalparameter_string_to_kind(string))
    }

    /// 判断参数类型是否有效
    /// - Parameter kind: 参数类型
    /// - Returns: 有效返回 true
    public static func isValid(kind: ParameterKind) -> Bool {
        icalparameter_kind_is_valid(kind.cValue)
    }

    /// 获取参数类型对应的值类型（以及是否多值）
    /// - Parameters:
    ///   - paramKind: 参数类型
    ///   - isMultivalued: 输出参数，是否为多值参数
    /// - Returns: 对应的 C 值类型
    public static func valueKind(for paramKind: ParameterKind, isMultivalued: inout Bool) -> icalvalue_kind {
        var mv: Int32 = 0
        let vk = icalparameter_kind_value_kind(paramKind.cValue, &mv)
        isMultivalued = mv != 0
        return vk
    }

    /// 解码参数值（对 URL 编码的参数值进行解码）
    /// - Parameter value: 待解码的参数值字符串
    /// - Returns: 解码后的字符串
    public static func decodeValue(_ value: String) -> String {
        var copy = value
        return copy.withUTF8 { ptr in
            // 需要可变缓冲区，复制到 C 字符串
            let len = ptr.count + 1
            let buf = UnsafeMutablePointer<CChar>.allocate(capacity: len)
            defer { buf.deallocate() }
            ptr.baseAddress?.withMemoryRebound(to: CChar.self, capacity: len) { src in
                buf.initialize(from: src, count: len)
            }
            icalparameter_decode_value(buf)
            return String(cString: buf)
        }
    }
}

// MARK: - Parameter + CustomStringConvertible

extension Parameter: CustomStringConvertible {
    /// 返回参数的 iCalendar 格式字符串表示
    public var description: String { iCalString }
}

// MARK: - Convenience constructors for common parameters

/// 常用参数的便捷构造方法
extension Parameter {

    /// 创建 TZID 参数（时区标识）
    /// - Parameter value: 时区标识符，如 "America/New_York"
    public static func tzid(_ value: String) -> Parameter? {
        Parameter(kind: .tzid, value: value)
    }

    /// 创建 LANGUAGE 参数（语言标签）
    /// - Parameter value: BCP 47 语言标签，如 "zh-CN"
    public static func language(_ value: String) -> Parameter? {
        Parameter(kind: .language, value: value)
    }

    /// 创建 CN 参数（通用名称）
    /// - Parameter value: 显示名称，如 "张三"
    public static func cn(_ value: String) -> Parameter? {
        Parameter(kind: .cn, value: value)
    }

    /// 创建 EMAIL 参数（邮件地址）
    /// - Parameter value: 邮件地址字符串
    public static func email(_ value: String) -> Parameter? {
        Parameter(kind: .email, value: value)
    }

    /// 创建 ROLE 参数（参与者角色）
    /// - Parameter role: 角色枚举值
    public static func role(_ role: Role) -> Parameter? {
        Parameter(kind: .role, value: role.iCalString)
    }

    /// 创建 PARTSTAT 参数（参与状态）
    /// - Parameter partstat: 参与状态枚举值
    public static func partstat(_ partstat: PartStat) -> Parameter? {
        Parameter(kind: .partstat, value: partstat.iCalString)
    }

    /// 创建 CUTYPE 参数（日历用户类型）
    /// - Parameter cutype: 用户类型枚举值
    public static func cutype(_ cutype: CUType) -> Parameter? {
        Parameter(kind: .cutype, value: cutype.iCalString)
    }

    /// 创建 FBTYPE 参数（空闲/忙碌类型）
    /// - Parameter fbtype: 空闲/忙碌类型枚举值
    public static func fbtype(_ fbtype: FBType) -> Parameter? {
        Parameter(kind: .fbtype, value: fbtype.iCalString)
    }

    /// 创建 RSVP 参数（是否需要回复）
    /// - Parameter value: true 表示需要回复，false 表示不需要
    public static func rsvp(_ value: Bool) -> Parameter? {
        Parameter(kind: .rsvp, value: value ? "TRUE" : "FALSE")
    }

    /// 创建 ENCODING 参数（编码方式）
    /// - Parameter encoding: 编码类型枚举值
    public static func encoding(_ encoding: Encoding) -> Parameter? {
        Parameter(kind: .encoding, value: encoding.iCalString)
    }
}

// MARK: - Role iCalString helper

extension Role {
    /// 将角色枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:              return "X-NAME"
        case .chair:          return "CHAIR"
        case .reqParticipant: return "REQ-PARTICIPANT"
        case .optParticipant: return "OPT-PARTICIPANT"
        case .nonParticipant: return "NON-PARTICIPANT"
        case .none:           return "NONE"
        }
    }
}

// MARK: - PartStat iCalString helper

extension PartStat {
    /// 将参与状态枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:           return "X"
        case .needsAction: return "NEEDS-ACTION"
        case .accepted:    return "ACCEPTED"
        case .declined:    return "DECLINED"
        case .tentative:   return "TENTATIVE"
        case .delegated:   return "DELEGATED"
        case .completed:   return "COMPLETED"
        case .inProcess:   return "IN-PROCESS"
        case .failed:      return "FAILED"
        case .none:        return "NONE"
        }
    }
}

// MARK: - CUType iCalString helper

extension CUType {
    /// 将日历用户类型枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:          return "X"
        case .individual: return "INDIVIDUAL"
        case .group:      return "GROUP"
        case .resource:   return "RESOURCE"
        case .room:       return "ROOM"
        case .unknown:    return "UNKNOWN"
        case .none:       return "NONE"
        }
    }
}

// MARK: - FBType iCalString helper

extension FBType {
    /// 将空闲/忙碌类型枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:               return "X"
        case .free:            return "FREE"
        case .busy:            return "BUSY"
        case .busyUnavailable: return "BUSY-UNAVAILABLE"
        case .busyTentative:   return "BUSY-TENTATIVE"
        case .none:            return "NONE"
        }
    }
}

// MARK: - Encoding iCalString helper

extension Encoding {
    /// 将编码类型枚举转换为 iCalendar 格式字符串
    fileprivate var iCalString: String {
        switch self {
        case .x:      return "X"
        case .base64: return "BASE64"
        case .bit8:   return "8BIT"
        case .none:   return "NONE"
        }
    }
}
