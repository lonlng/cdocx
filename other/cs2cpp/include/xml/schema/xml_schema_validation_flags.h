/// @file xml/schema/xml_schema_validation_flags.h

#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Specifies schema validation options used by the XmlSchemaValidator and XmlReader classes.
enum class XmlSchemaValidationFlags
{
    /// Do not process identity constraints, inline schemas, schema location hints, or report schema validation warnings.
    None = 0x0000,
    /// Process inline schemas encountered during validation.
    ProcessInlineSchema = 0x0001,
    /// Process schema location hints (@c xsi:schemaLocation, @c xsi:noNamespaceSchemaLocation) encountered during validation.
    ProcessSchemaLocation = 0x0002,
    /// Report schema validation warnings encountered during validation.
    ReportValidationWarnings = 0x0004,
    /// Process identity constraints (@c xs:ID, @c xs:IDREF, @c xs:key, @c xs:keyref, @c xs:unique) encountered during validation.
    ProcessIdentityConstraints = 0x0008,
    /// Allow xml:* attributes even if they are not defined in the schema.
    /// The attributes will be validated based on their data type.
    AllowXmlAttributes = 0x0010
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::Schema::XmlSchemaValidationFlags);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml::Schema);

template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaValidationFlags>
{
    typedef void Flags;
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaValidationFlags, const char_t*>, 6>& values();
};
/// @endcond


