/// @file xml/schema/xml_type_code.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Represents the W3C XML Schema Definition Language (XSD) schema types.
enum class XmlTypeCode
{
    /// No type information.
    None,
    /// An item such as a node or atomic value.
    Item,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Node,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Document,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Element,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Attribute,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Namespace,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    ProcessingInstruction,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Comment,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    Text,
    /// Any atomic value of a union.
    AnyAtomicType,
    /// An untyped atomic value.
    UntypedAtomic,
    /// A W3C XML Schema @c xs:string type.
    String,
    /// A W3C XML Schema @c xs:boolean type.
    Boolean,
    /// A W3C XML Schema @c xs:decimal type.
    Decimal,
    /// A W3C XML Schema @c xs:float type.
    Float,
    /// A W3C XML Schema @c xs:double type.
    Double,
    /// A W3C XML Schema @c xs:Duration type.
    Duration,
    /// A W3C XML Schema @c xs:dateTime type.
    DateTime,
    /// A W3C XML Schema @c xs:time type.
    Time,
    /// A W3C XML Schema @c xs:date type.
    Date,
    /// A W3C XML Schema @c xs:gYearMonth type.
    GYearMonth,
    /// A W3C XML Schema @c xs:gYear type.
    GYear,
    /// A W3C XML Schema @c xs:gMonthDay type.
    GMonthDay,
    /// A W3C XML Schema @c xs:gDay type.
    GDay,
    /// A W3C XML Schema @c xs:gMonth type.
    GMonth,
    /// A W3C XML Schema @c xs:hexBinary type.
    HexBinary,
    /// A W3C XML Schema @c xs:base64Binary type.
    Base64Binary,
    /// A W3C XML Schema @c xs:anyURI type.
    AnyUri,
    /// A W3C XML Schema @c xs:QName type.
    QName,
    /// A W3C XML Schema @c xs:NOTATION type.
    Notation,
    /// A W3C XML Schema @c xs:normalizedString type.
    NormalizedString,
    /// A W3C XML Schema @c xs:token type.
    Token,
    /// A W3C XML Schema @c xs:language type.
    Language,
    /// A W3C XML Schema @c xs:NMTOKEN type.
    NmToken,
    /// A W3C XML Schema @c xs:Name type.
    Name,
    /// A W3C XML Schema @c xs:NCName type.
    NCName,
    /// A W3C XML Schema @c xs:ID type.
    Id,
    /// A W3C XML Schema @c xs:IDREF type.
    Idref,
    /// A W3C XML Schema @c xs:ENTITY type.
    Entity,
    /// A W3C XML Schema @c xs:integer type.
    Integer,
    /// A W3C XML Schema @c xs:nonPositiveInteger type.
    NonPositiveInteger,
    /// A W3C XML Schema @c xs:negativeInteger type.
    NegativeInteger,
    /// A W3C XML Schema @c xs:long type.
    Long,
    /// A W3C XML Schema @c xs:int type.
    Int,
    /// A W3C XML Schema @c xs:short type.
    Short,
    /// A W3C XML Schema @c xs:byte type.
    Byte,
    /// A W3C XML Schema @c xs:nonNegativeInteger type.
    NonNegativeInteger,
    /// A W3C XML Schema @c xs:unsignedLong type.
    UnsignedLong,
    /// A W3C XML Schema @c xs:unsignedInt type.
    UnsignedInt,
    /// A W3C XML Schema @c xs:unsignedShort type.
    UnsignedShort,
    /// A W3C XML Schema @c xs:unsignedByte type.
    UnsignedByte,
    /// A W3C XML Schema @c xs:positiveInteger type.
    PositiveInteger,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    YearMonthDuration,
    /// This value is used for internal purposes and is not intended to be used directly from your code.
    DayTimeDuration
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlTypeCode>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlTypeCode, const char_t*>, 55>& values();
};
/// @endcond


