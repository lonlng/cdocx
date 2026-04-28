/// @file xml/schema/xml_schema_content_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Enumerations for the content model of the complex type.
/// This represents the content in the post-schema-validation information set (infoset).
enum class XmlSchemaContentType
{
    /// Text-only content.
    TextOnly,
    /// Empty content.
    Empty,
    /// Element-only content.
    ElementOnly,
    /// Mixed content.
    Mixed
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaContentType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaContentType, const char_t*>, 4>& values();
};
/// @endcond


