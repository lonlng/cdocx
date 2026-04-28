/// @file xml/schema/xml_severity_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Represents the severity of the validation event.
enum class XmlSeverityType
{
    /// Indicates a validation error occurred when validating the instance document.
    /// This applies to document type definitions (DTDs) and XML Schema definition language (XSD) schemas.
    /// The World Wide Web Consortium (W3C) validity constraints are considered errors.
    /// If no validation event handler has been created, errors throw an exception.
    Error,
    /// Indicates that a validation event occurred that is not an error.
    /// A warning is typically issued when there is no DTD,
    /// or XML Schema to validate a particular element or attribute against.
    /// Unlike errors, warnings do not throw an exception if there is no validation event handler.
    Warning
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSeverityType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSeverityType, const char_t*>, 2>& values();
};
/// @endcond


