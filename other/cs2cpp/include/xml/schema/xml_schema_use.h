/// @file xml/schema/xml_schema_use.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Indicator of how the attribute is used.
enum class XmlSchemaUse
{
    /// Attribute use not specified.
    None,
    /// Attribute is optional.
    Optional,
    /// Attribute cannot be used.
    Prohibited,
    /// Attribute must appear once.
    Required
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaUse>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaUse, const char_t*>, 4>& values();
};
/// @endcond


