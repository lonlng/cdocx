/// @file xml/schema/xml_schema_datatype_variety.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Specifies the W3C XML schema data type variety of the type.
enum class XmlSchemaDatatypeVariety
{
    /// A W3C XML schema atomic type.
    Atomic,
    /// A W3C XML schema list type.
    List,
    /// A W3C XML schema union type.
    Union
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaDatatypeVariety>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaDatatypeVariety, const char_t*>, 3>& values();
};
/// @endcond


