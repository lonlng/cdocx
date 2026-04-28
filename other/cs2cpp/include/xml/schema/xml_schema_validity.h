/// @file xml/schema/xml_schema_validity.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Represents the validity of an XML item validated by the XmlSchemaValidator class.
enum class XmlSchemaValidity
{
    /// The validity of the XML item is not known.
    NotKnown,
    /// The XML item is valid.
    Valid,
    /// The XML item is invalid.
    Invalid
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaValidity>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaValidity, const char_t*>, 3>& values();
};
/// @endcond


