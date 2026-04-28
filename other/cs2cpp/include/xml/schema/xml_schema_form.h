/// @file xml/schema/xml_schema_form.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Indicates if attributes or elements need to be qualified with a namespace prefix.
enum class XmlSchemaForm
{
    /// Element and attribute form is not specified in the schema.
    None,
    /// Elements and attributes must be qualified with a namespace prefix.
    Qualified,
    /// Elements and attributes are not required to be qualified with a namespace prefix.
    Unqualified
};

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaForm>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaForm, const char_t*>, 3>& values();
};
/// @endcond

