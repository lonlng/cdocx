/// @file xml/xml_output_method.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the method used to serialize the XmlWriter output.
enum class XmlOutputMethod
{
    /// Serialize according to the XML 1.0 rules.
    Xml = 0,
    /// Serialize according to the HTML rules specified by XSLT.
    Html = 1,
    /// Serialize text blocks only.
    Text = 2,
    /// Use the XSLT rules to choose between the XmlOutputMethod::Xml and XmlOutputMethod::Html output methods at runtime.
    AutoDetect = 3
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlOutputMethod>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlOutputMethod, const char_t*>, 4>& values();
};
/// @endcond


