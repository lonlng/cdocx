/// @file xml/formatting.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies formatting options for the XmlTextWriter.
enum class Formatting
{
    /// No special formatting is applied. This is the default.
    None,
    /// Causes child elements to be indented according to the XmlTextWriter::set_Indentation and
    /// XmlTextWriter::set_IndentChar settings.
    ///
    /// This option indents element content only; mixed content is not affected. For the XML 1.0 definitions of these terms,
    /// see the W3C documentation <a href="https://www.w3.org/TR/1998/REC-xml-19980210#sec-element-content">Element Content</a>
    /// and <a href="https://www.w3.org/TR/1998/REC-xml-19980210#sec-mixed-content">Mixed Content</a>.
    Indented
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::Formatting>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Formatting, const char_t*>, 2>& values();
};
/// @endcond


