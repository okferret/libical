// SPDX-License-Identifier: LGPL-2.1-only OR MPL-2.0
// libICAL Swift Wrapper - Enums

import libical

// MARK: - ComponentKind

/// iCalendar 组件类型，对应 C 的 `icalcomponent_kind`
public enum ComponentKind: Int32, CaseIterable, Sendable {
    case none           = 0  // 无效组件
    case any            = 1  // 任意组件（用于查询）
    case xroot          = 2  // 根组件
    case xattach        = 3  // 附件组件
    case vevent         = 4  // 日历事件组件
    case vtodo          = 5  // 待办事项组件
    case vjournal       = 6  // 日记组件
    case vcalendar      = 7  // 日历容器组件
    case vagenda        = 8  // 议程组件
    case vfreebusy      = 9  // 空闲/忙碌组件
    case valarm         = 10 // 闹钟组件
    case vtimezone      = 15 // 时区组件
    case xstandard      = 16 // 标准时间组件（VTIMEZONE 子组件）
    case xdaylight      = 17 // 夏令时组件（VTIMEZONE 子组件）
    case x              = 18 // 自定义扩展组件
    case vavailability  = 26 // 可用性组件
    case vpoll          = 28 // 投票组件
    case vpatch         = 31 // 补丁组件
    case participant    = 33 // 参与者组件
    case vlocation      = 34 // 位置组件
    case vresource      = 35 // 资源组件
    case iana           = 36 // IANA 注册组件

    /// 转换为 C 枚举值
    public var cValue: icalcomponent_kind {
        icalcomponent_kind(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalcomponent_kind) {
        self = ComponentKind(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyKind

/// iCalendar 属性类型，对应 C 的 `icalproperty_kind`
public enum PropertyKind: Int32, CaseIterable, Sendable {
    case any            = 0   // 任意属性（用于查询）
    case acknowledged   = 1   // 确认时间属性
    case action         = 2   // 闹钟动作属性
    case attach         = 4   // 附件属性
    case attendee       = 5   // 参与者属性
    case calscale       = 8   // 日历标度属性
    case categories     = 12  // 分类属性
    case `class`        = 13  // 访问分类属性
    case color          = 118 // 颜色属性
    case comment        = 15  // 注释属性
    case completed      = 16  // 完成时间属性
    case conference     = 120 // 会议属性
    case contact        = 18  // 联系人属性
    case created        = 19  // 创建时间属性
    case description    = 29  // 描述属性
    case dtend          = 30  // 结束时间属性
    case dtstamp        = 31  // 时间戳属性
    case dtstart        = 32  // 开始时间属性
    case due            = 33  // 截止时间属性（VTODO）
    case duration       = 34  // 持续时间属性
    case exdate         = 35  // 排除日期属性
    case freebusy       = 38  // 空闲/忙碌属性
    case geo            = 39  // 地理位置属性
    case image          = 119 // 图片属性
    case lastModified   = 42  // 最后修改时间属性
    case link           = 134 // 链接属性
    case location       = 43  // 位置属性
    case method         = 48  // 日历方法属性
    case name           = 115 // 名称属性
    case organizer      = 52  // 组织者属性
    case percentComplete = 54 // 完成百分比属性
    case priority       = 56  // 优先级属性
    case prodid         = 57  // 产品标识属性
    case rdate          = 62  // 重复日期属性
    case recurrenceId   = 66  // 重复标识属性
    case relatedTo      = 67  // 关联属性
    case `repeat`       = 69  // 重复次数属性（VALARM）
    case requestStatus  = 70  // 请求状态属性
    case resources      = 71  // 资源属性
    case rrule          = 73  // 重复规则属性
    case sequence       = 75  // 序列号属性
    case source         = 117 // 来源属性
    case status         = 76  // 状态属性
    case summary        = 78  // 摘要属性
    case transp         = 80  // 时间透明度属性
    case trigger        = 81  // 触发器属性（VALARM）
    case tzid           = 82  // 时区标识属性
    case tzname         = 83  // 时区名称属性
    case tzoffsetfrom   = 84  // 时区偏移来源属性
    case tzoffsetto     = 85  // 时区偏移目标属性
    case tzurl          = 86  // 时区 URL 属性
    case uid            = 87  // 唯一标识属性
    case url            = 88  // URL 属性
    case version        = 89  // 版本属性
    case x              = 90  // 自定义扩展属性
    case xlicerror      = 93  // libical 错误属性
    case no             = 100 // 无效属性

    /// 转换为 C 枚举值
    public var cValue: icalproperty_kind {
        icalproperty_kind(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_kind) {
        self = PropertyKind(rawValue: Int32(cValue.rawValue)) ?? .no
    }
}

// MARK: - ParameterKind

/// iCalendar 参数类型，对应 C 的 `icalparameter_kind`
public enum ParameterKind: Int32, CaseIterable, Sendable {
    case any            = 0  // 任意参数（用于查询）
    case actionparam    = 1  // 动作参数
    case altrep         = 2  // 替代表示参数
    case charset        = 3  // 字符集参数
    case cn             = 4  // 通用名称参数
    case cutype         = 5  // 日历用户类型参数
    case delegatedFrom  = 6  // 委托来源参数
    case delegatedTo    = 7  // 委托目标参数
    case dir            = 8  // 目录参数
    case display        = 46 // 显示参数
    case email          = 50 // 邮件参数
    case encoding       = 10 // 编码参数
    case fbtype         = 11 // 空闲/忙碌类型参数
    case feature        = 48 // 特性参数
    case filename       = 42 // 文件名参数
    case fmttype        = 12 // 格式类型参数
    case iana           = 33 // IANA 注册参数
    case language       = 14 // 语言参数
    case member         = 18 // 成员参数
    case partstat       = 20 // 参与状态参数
    case range          = 21 // 范围参数
    case related        = 22 // 关联参数
    case reltype        = 23 // 关联类型参数
    case role           = 24 // 角色参数
    case rsvp           = 25 // 回复请求参数
    case scheduleAgent  = 34 // 调度代理参数
    case sentby         = 26 // 发送者参数
    case tzid           = 27 // 时区标识参数
    case value          = 28 // 值类型参数
    case x              = 29 // 自定义扩展参数
    case no             = 32 // 无效参数

    /// 转换为 C 枚举值
    public var cValue: icalparameter_kind {
        icalparameter_kind(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_kind) {
        self = ParameterKind(rawValue: Int32(cValue.rawValue)) ?? .no
    }
}

// MARK: - RecurrenceFrequency

/// 重复规则频率，对应 C 的 `icalrecurrencetype_frequency`
public enum RecurrenceFrequency: Int32, CaseIterable, Sendable {
    case secondly = 0 // 按秒重复
    case minutely = 1 // 按分钟重复
    case hourly   = 2 // 按小时重复
    case daily    = 3 // 按天重复
    case weekly   = 4 // 按周重复
    case monthly  = 5 // 按月重复
    case yearly   = 6 // 按年重复
    case none     = 7 // 无重复

    /// 转换为 C 枚举值
    public var cValue: icalrecurrencetype_frequency {
        icalrecurrencetype_frequency(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalrecurrencetype_frequency) {
        self = RecurrenceFrequency(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - Weekday

/// 星期几，对应 C 的 `icalrecurrencetype_weekday`
public enum Weekday: Int32, CaseIterable, Sendable {
    case none      = 0 // 未指定
    case sunday    = 1 // 星期日
    case monday    = 2 // 星期一
    case tuesday   = 3 // 星期二
    case wednesday = 4 // 星期三
    case thursday  = 5 // 星期四
    case friday    = 6 // 星期五
    case saturday  = 7 // 星期六

    /// 转换为 C 枚举值
    public var cValue: icalrecurrencetype_weekday {
        icalrecurrencetype_weekday(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalrecurrencetype_weekday) {
        self = Weekday(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyStatus

/// 属性状态值，对应 C 的 `icalproperty_status`
public enum PropertyStatus: Int32, CaseIterable, Sendable {
    case x            = 10900 // 自定义扩展状态
    case tentative    = 10901 // 暂定（VEVENT）
    case confirmed    = 10902 // 已确认（VEVENT）
    case completed    = 10903 // 已完成（VTODO）
    case needsAction  = 10904 // 需要处理（VTODO/VJOURNAL）
    case cancelled    = 10905 // 已取消
    case inProcess    = 10906 // 进行中（VTODO）
    case draft        = 10907 // 草稿（VJOURNAL）
    case final        = 10908 // 最终版（VJOURNAL）
    case none         = 10999 // 无状态

    /// 转换为 C 枚举值
    public var cValue: icalproperty_status {
        icalproperty_status(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_status) {
        self = PropertyStatus(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyMethod

/// 日历方法，对应 C 的 `icalproperty_method`
public enum PropertyMethod: Int32, CaseIterable, Sendable {
    case x               = 10500 // 自定义扩展方法
    case publish         = 10501 // 发布（单向发布日历信息）
    case request         = 10502 // 请求（邀请参与者）
    case reply           = 10503 // 回复（响应邀请）
    case add             = 10504 // 添加（向已有事件添加实例）
    case cancel          = 10505 // 取消（取消事件）
    case refresh         = 10506 // 刷新（请求最新版本）
    case counter         = 10507 // 反提议（提出修改建议）
    case declineCounter  = 10508 // 拒绝反提议
    case none            = 10599 // 无方法

    /// 转换为 C 枚举值
    public var cValue: icalproperty_method {
        icalproperty_method(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_method) {
        self = PropertyMethod(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyClass

/// 访问分类，对应 C 的 `icalproperty_class`
public enum PropertyClass: Int32, CaseIterable, Sendable {
    case x            = 10300 // 自定义扩展分类
    case `public`     = 10301 // 公开（默认）
    case `private`    = 10302 // 私密
    case confidential = 10303 // 机密
    case none         = 10399 // 无分类

    /// 转换为 C 枚举值
    public var cValue: icalproperty_class {
        icalproperty_class(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_class) {
        self = PropertyClass(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyTransp

/// 时间透明度，对应 C 的 `icalproperty_transp`
/// 表示事件是否在空闲/忙碌查询中显示为忙碌
public enum PropertyTransp: Int32, CaseIterable, Sendable {
    case x           = 11000 // 自定义扩展透明度
    case opaque      = 11001 // 不透明（显示为忙碌，默认）
    case transparent = 11003 // 透明（不显示为忙碌）
    case none        = 11099 // 无透明度设置

    /// 转换为 C 枚举值
    public var cValue: icalproperty_transp {
        icalproperty_transp(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_transp) {
        self = PropertyTransp(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PropertyAction

/// 闹钟动作，对应 C 的 `icalproperty_action`
public enum PropertyAction: Int32, CaseIterable, Sendable {
    case x         = 10000 // 自定义扩展动作
    case audio     = 10001 // 音频提醒
    case display   = 10002 // 显示提醒
    case email     = 10003 // 邮件提醒
    case procedure = 10004 // 执行程序
    case none      = 10099 // 无动作

    /// 转换为 C 枚举值
    public var cValue: icalproperty_action {
        icalproperty_action(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalproperty_action) {
        self = PropertyAction(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - PartStat

/// 参与者状态，对应 C 的 `icalparameter_partstat`
public enum PartStat: Int32, CaseIterable, Sendable {
    case x           = 20600 // 自定义扩展状态
    case needsAction = 20601 // 需要处理（默认）
    case accepted    = 20602 // 已接受
    case declined    = 20603 // 已拒绝
    case tentative   = 20604 // 暂定
    case delegated   = 20605 // 已委托
    case completed   = 20606 // 已完成（VTODO）
    case inProcess   = 20607 // 进行中（VTODO）
    case failed      = 20608 // 失败
    case none        = 20699 // 无状态

    /// 转换为 C 枚举值
    public var cValue: icalparameter_partstat {
        icalparameter_partstat(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_partstat) {
        self = PartStat(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - Role

/// 参与者角色，对应 C 的 `icalparameter_role`
public enum Role: Int32, CaseIterable, Sendable {
    case x               = 21100 // 自定义扩展角色
    case chair           = 21101 // 主席（会议组织者）
    case reqParticipant  = 21102 // 必须参与者（默认）
    case optParticipant  = 21103 // 可选参与者
    case nonParticipant  = 21104 // 非参与者（仅接收信息）
    case none            = 21199 // 无角色

    /// 转换为 C 枚举值
    public var cValue: icalparameter_role {
        icalparameter_role(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_role) {
        self = Role(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - CUType

/// 日历用户类型，对应 C 的 `icalparameter_cutype`
public enum CUType: Int32, CaseIterable, Sendable {
    case x          = 20100 // 自定义扩展类型
    case individual = 20101 // 个人用户（默认）
    case group      = 20102 // 用户组
    case resource   = 20103 // 资源（如会议室设备）
    case room       = 20104 // 房间
    case unknown    = 20105 // 未知类型
    case none       = 20199 // 无类型

    /// 转换为 C 枚举值
    public var cValue: icalparameter_cutype {
        icalparameter_cutype(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_cutype) {
        self = CUType(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - FBType

/// 空闲/忙碌类型，对应 C 的 `icalparameter_fbtype`
public enum FBType: Int32, CaseIterable, Sendable {
    case x                = 20400 // 自定义扩展类型
    case free             = 20401 // 空闲
    case busy             = 20402 // 忙碌（默认）
    case busyUnavailable  = 20403 // 忙碌且不可用（外出）
    case busyTentative    = 20404 // 暂定忙碌
    case none             = 20499 // 无类型

    /// 转换为 C 枚举值
    public var cValue: icalparameter_fbtype {
        icalparameter_fbtype(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_fbtype) {
        self = FBType(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - RelType

/// 关联类型，对应 C 的 `icalparameter_reltype`
/// 用于 RELATED-TO 属性，描述组件间的关系
public enum RelType: Int32, CaseIterable, Sendable {
    case x        = 20900 // 自定义扩展关联类型
    case parent   = 20901 // 父组件（默认）
    case child    = 20902 // 子组件
    case sibling  = 20903 // 兄弟组件
    case none     = 20999 // 无关联类型

    /// 转换为 C 枚举值
    public var cValue: icalparameter_reltype {
        icalparameter_reltype(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_reltype) {
        self = RelType(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - Encoding

/// 编码类型，对应 C 的 `icalparameter_encoding`
/// 用于 ATTACH 属性的二进制数据编码方式
public enum Encoding: Int32, CaseIterable, Sendable {
    case x      = 20300 // 自定义扩展编码
    case bit8   = 20301 // 8 位编码
    case base64 = 20302 // Base64 编码
    case none   = 20399 // 无编码

    /// 转换为 C 枚举值
    public var cValue: icalparameter_encoding {
        icalparameter_encoding(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalparameter_encoding) {
        self = Encoding(rawValue: Int32(cValue.rawValue)) ?? .none
    }
}

// MARK: - RecurrenceSkip

/// 重复规则跳过类型，对应 C 的 `icalrecurrencetype_skip`
/// 用于 RSCALE 扩展，处理某些日历系统中不存在的日期
public enum RecurrenceSkip: Int32, CaseIterable, Sendable {
    case backward  = 0 // 向前跳（使用前一个有效日期）
    case forward   = 1 // 向后跳（使用后一个有效日期）
    case omit      = 2 // 忽略（跳过该次重复）
    case undefined = 3 // 未定义

    /// 转换为 C 枚举值
    public var cValue: icalrecurrencetype_skip {
        icalrecurrencetype_skip(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalrecurrencetype_skip) {
        self = RecurrenceSkip(rawValue: Int32(cValue.rawValue)) ?? .undefined
    }
}

// MARK: - ValueKind

/// iCalendar 值类型，对应 C 的 `icalvalue_kind`
public enum ValueKind: Int32, CaseIterable, Sendable {
    case any              = 5000 // 任意值类型
    case action           = 5027 // 动作值
    case attach           = 5003 // 附件值（URI 或二进制）
    case binary           = 5011 // 二进制值
    case boolean          = 5021 // 布尔值
    case busytype         = 5032 // 忙碌类型值
    case calAddress       = 5023 // 日历地址值（mailto: URI）
    case carlevel         = 5016 // CAR 级别值
    case `class`          = 5019 // 访问分类值
    case cmd              = 5010 // 命令值
    case color            = 5044 // 颜色值
    case date             = 5002 // 日期值（仅日期，无时间）
    case datetime         = 5028 // 日期时间值
    case datetimeDate     = 5036 // 日期或日期时间值
    case datetimePeriod   = 5015 // 日期时间或时间段值
    case duration         = 5020 // 持续时间值
    case float            = 5013 // 浮点数值
    case geo              = 5004 // 地理坐标值
    case integer          = 5017 // 整数值
    case link             = 5042 // 链接值
    case method           = 5030 // 方法值
    case participantType  = 5037 // 参与者类型值
    case period           = 5014 // 时间段值
    case pollCompletion   = 5034 // 投票完成值
    case pollMode         = 5033 // 投票模式值
    case proximity        = 5039 // 邻近值
    case query            = 5001 // 查询值
    case queryLevel       = 5012 // 查询级别值
    case recur            = 5026 // 重复规则值
    case relatedTo        = 5043 // 关联值
    case requestStatus    = 5009 // 请求状态值
    case resourceType     = 5038 // 资源类型值
    case status           = 5005 // 状态值
    case string           = 5007 // 字符串值
    case taskMode         = 5035 // 任务模式值
    case text             = 5008 // 文本值
    case transp           = 5006 // 透明度值
    case trigger          = 5024 // 触发器值
    case uid              = 5040 // 唯一标识值
    case uri              = 5018 // URI 值
    case utcOffset        = 5029 // UTC 偏移值
    case x                = 5022 // 自定义扩展值
    case xlicclass        = 5025 // libical 内部分类值
    case xmlReference     = 5041 // XML 引用值
    case no               = 5031 // 无效值类型

    /// 转换为 C 枚举值
    public var cValue: icalvalue_kind {
        icalvalue_kind(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalvalue_kind) {
        self = ValueKind(rawValue: Int32(cValue.rawValue)) ?? .no
    }
}

// MARK: - RequestStatus

/// iCalendar 请求状态，对应 C 的 `icalrequeststatus`
/// 用于 REQUEST-STATUS 属性，表示调度请求的处理结果
public enum RequestStatus: Int32, CaseIterable, Sendable {
    case unknown                = 0  // 未知状态
    case success_2_0            = 1  // 2.0 成功
    case fallback_2_1           = 2  // 2.1 降级处理成功
    case igprop_2_2             = 3  // 2.2 忽略不支持的属性
    case igparam_2_3            = 4  // 2.3 忽略不支持的参数
    case igxprop_2_4            = 5  // 2.4 忽略不支持的扩展属性
    case igxparam_2_5           = 6  // 2.5 忽略不支持的扩展参数
    case igcomp_2_6             = 7  // 2.6 忽略不支持的组件
    case forward_2_7            = 8  // 2.7 已转发请求
    case oneevent_2_8           = 9  // 2.8 仅处理一个事件
    case trunc_2_9              = 10 // 2.9 截断处理
    case onetodo_2_10           = 11 // 2.10 仅处理一个待办
    case truncrrule_2_11        = 12 // 2.11 截断重复规则
    case invpropname_3_0        = 13 // 3.0 无效属性名
    case invpropval_3_1         = 14 // 3.1 无效属性值
    case invparam_3_2           = 15 // 3.2 无效参数
    case invparamval_3_3        = 16 // 3.3 无效参数值
    case invcomp_3_4            = 17 // 3.4 无效组件
    case invtime_3_5            = 18 // 3.5 无效时间
    case invrule_3_6            = 19 // 3.6 无效规则
    case invcu_3_7              = 20 // 3.7 无效日历用户
    case noauth_3_8             = 21 // 3.8 无权限
    case badversion_3_9         = 22 // 3.9 不支持的版本
    case toobig_3_10            = 23 // 3.10 请求过大
    case missreqcomp_3_11       = 24 // 3.11 缺少必要组件
    case unkcomp_3_12           = 25 // 3.12 未知组件
    case badcomp_3_13           = 26 // 3.13 不支持的组件
    case nocap_3_14             = 27 // 3.14 不支持的功能
    case invcommand_3_15        = 28 // 3.15 无效命令
    case busy_4_0               = 29 // 4.0 调度资源忙碌
    case storeAccessDenied_4_1  = 30 // 4.1 存储访问被拒绝
    case storeNotFound_4_3      = 32 // 4.3 存储未找到
    case maybe_5_0              = 33 // 5.0 可能支持
    case unavail_5_1            = 34 // 5.1 服务不可用
    case noservice_5_2          = 35 // 5.2 不支持该服务
    case nosched_5_3            = 36 // 5.3 不支持调度
    case containerNotFound_6_1  = 37 // 6.1 容器未找到

    /// 转换为 C 枚举值
    public var cValue: icalrequeststatus {
        icalrequeststatus(rawValue: UInt32(rawValue))
    }

    /// 从 C 枚举值创建
    public init(cValue: icalrequeststatus) {
        self = RequestStatus(rawValue: Int32(cValue.rawValue)) ?? .unknown
    }

    /// 获取主版本号（如 "2.0" 中的 2）
    public var major: Int {
        Int(icalenum_reqstat_major(cValue))
    }

    /// 获取次版本号（如 "2.0" 中的 0）
    public var minor: Int {
        Int(icalenum_reqstat_minor(cValue))
    }

    /// 获取状态码字符串（如 "2.0"）
    public var code: String {
        guard let ptr = icalenum_reqstat_code_r(cValue) else { return "" }
        defer { icalmemory_free_buffer(ptr) }
        return String(cString: ptr)
    }

    /// 从主次版本号创建请求状态
    public static func from(major: Int, minor: Int) -> RequestStatus {
        RequestStatus(cValue: icalenum_num_to_reqstat(Int16(major), Int16(minor)))
    }
}
