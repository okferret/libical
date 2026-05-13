// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Parser

import Foundation
import libical

// MARK: - ParserState

/// 解析器状态，对应 C 的 `icalparser_state`
public enum ParserState: UInt32, Sendable {
    case error      = 0  // ICALPARSER_ERROR
    case success    = 1  // ICALPARSER_SUCCESS
    case beginComp  = 2  // ICALPARSER_BEGIN_COMP
    case endComp    = 3  // ICALPARSER_END_COMP
    case inProgress = 4  // ICALPARSER_IN_PROGRESS

    internal init(cValue: icalparser_state) {
        self = ParserState(rawValue: cValue.rawValue) ?? .error
    }
}

// MARK: - ParserCtrl

/// 控制字符处理方式，对应 C 的 `icalparser_ctrl`
public enum ParserCtrl: UInt32, Sendable {
    case keep  = 0  // ICALPARSER_CTRL_KEEP
    case omit  = 1  // ICALPARSER_CTRL_OMIT
    case error = 2  // ICALPARSER_CTRL_ERROR

    internal init(cValue: icalparser_ctrl) {
        self = ParserCtrl(rawValue: cValue.rawValue) ?? .keep
    }

    internal var cValue: icalparser_ctrl {
        icalparser_ctrl(rawValue: self.rawValue)
    }
}

// MARK: - Parser

/// iCalendar 解析器，对应 C 的 `icalparser *`
public final class Parser: @unchecked Sendable {

    // MARK: Internal storage

    private let cPointer: OpaquePointer

    // MARK: Initializers

    public init() {
        self.cPointer = icalparser_new()
    }

    deinit {
        icalparser_free(cPointer)
    }

    // MARK: State

    public var state: ParserState {
        ParserState(cValue: icalparser_get_state(cPointer))
    }

    // MARK: Line-by-line parsing

    /// 添加一行数据进行解析
    public func addLine(_ line: String) -> Component? {
        // 使用 withCString 确保 C 字符串在闭包期间有效，
        // icalparser_add_line 需要可变指针，通过 strdup 创建副本
        return line.withCString { cStr in
            // icalparser_add_line 内部会修改传入的字符串（折叠换行等），
            // 因此需要传入可写副本，避免修改 Swift 字符串的只读缓冲区
            guard let mutableCStr = strdup(cStr) else { return nil }
            defer { free(mutableCStr) }
            guard let compPtr = icalparser_add_line(cPointer, mutableCStr) else { return nil }
            return Component(owning: compPtr)
        }
    }
    /// 清理解析器并返回已解析的内容
    public func clean() -> Component? {
        guard let ptr = icalparser_clean(cPointer) else { return nil }
        return Component(owning: ptr)
    }

    // MARK: Static parsing

    /// 直接解析 RFC5545 格式字符串
    public static func parse(string: String) -> Component? {
        guard let ptr = icalparser_parse_string(string) else { return nil }
        return Component(owning: ptr)
    }

    // MARK: Global settings

    public static var ctrl: ParserCtrl {
        get { ParserCtrl(cValue: icalparser_get_ctrl()) }
        set { icalparser_set_ctrl(newValue.cValue) }
    }
}

// MARK: - Convenience parsing extensions

extension Component {

    /// 从 RFC5545 格式字符串解析组件
    public static func parse(_ string: String) -> Component? {
        Parser.parse(string: string)
    }

    /// 从 Data 解析组件
    public static func parse(data: Data) -> Component? {
        guard let string = String(data: data, encoding: .utf8) else { return nil }
        return Parser.parse(string: string)
    }
}
