/// @file xml/validation_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the type of validation to perform.
enum class ValidationType
{
    /// No validation is performed, and no validation errors are thrown. This setting creates an XML 1.0 compliant non-validating parser.
    ///
    /// Calls to XmlReader::ResolveEntity report default attributes and resolve general entities. The DOCTYPE is not used for validation purposes.
    None,
    /// Validates if DTD or schema information is found.
    ///
    /// @deprecated This field is obsolete. It applies only to the obsolete XmlValidatingReader class.
    Auto,
    /// Validates according to the DTD.
    DTD,
    /// Validate according to XML-Data Reduced (XDR) schemas, including inline XDR schemas.
    /// XDR schemas are recognized using the @c x-schema namespace prefix or the XmlValidatingReader::get_Schemas value.
    ///
    /// @deprecated This field is obsolete. It applies only to the obsolete XmlValidatingReader class.
    XDR,
    /// Validate according to XML Schema definition language (XSD) schemas, including inline XML Schemas.
    /// XML Schemas are associated with namespace URIs either by using the @c schemaLocation attribute or
    /// the provided @c Schemas.
    Schema
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::ValidationType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::ValidationType, const char_t*>, 5>& values();
};
/// @endcond


