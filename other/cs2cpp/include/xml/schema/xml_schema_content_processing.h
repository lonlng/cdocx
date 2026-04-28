/// @file xml/schema/xml_schema_content_processing.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Provides information about the validation mode of @c any and @c anyAttribute element replacements.
enum class XmlSchemaContentProcessing
{
    /// Document items are not validated.
    None,
    /// Document items must consist of well-formed XML and are not validated by the schema.
    ///
    /// The XML processor attempts to notify the client through a validation event handler with
    /// ValidationEventArgs::set_Severity(XmlSeverityType::Warning) that no validation took place for the given item.
    /// If a validation event handler has not been set up, no information is returned when the warning is produced.
    Skip,
    /// If the associated schema is found, the document items will be validated. No errors will be thrown otherwise.
    ///
    /// If the item is not validated, the XML processor attempts to notify the client through
    /// a validation event handler with ValidationEventArgs::set_Severity(XmlSeverityType::Warning).
    /// If a validation event handler has not been set up, no information is returned when the warning is produced.
    Lax,
    /// The schema processor must find a schema associated with the indicated namespace to validate the document items.
    ///
    /// If the processor cannot find a schema or if the items are not valid,
    /// the XML processor attempts to notify the client through a validation event handler with
    /// ValidationEventArgs::set_Severity(XmlSeverityType::Warning).
    /// If a validation error occurs and a validation event handler is not provided, an exception is thrown.
    Strict
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaContentProcessing>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaContentProcessing, const char_t*>, 4>& values();
};
/// @endcond


