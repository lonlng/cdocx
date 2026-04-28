/// @file xml/conformance_level.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the amount of input or output checking that XmlReader and XmlWriter objects perform.
enum class ConformanceLevel
{
    /// The XmlReader or XmlWriter object automatically detects whether document-level or fragment-level checking
    /// should be performed, and does the appropriate checking. If you're wrapping another XmlReader or XmlWriter object,
    /// the outer object doesn't do any additional conformance checking. Conformance checking is left up to the underlying object.
    ///
    /// See the XmlReaderSettings::get_ConformanceLevel and XmlWriterSettings::get_ConformanceLevel methods for details
    /// on how the compliance level is determined.
    Auto = 0,
    /// The XML data is a <a href="https://www.w3.org/TR/2006/REC-xml-20060816/#wf-entities">well-formed XML fragment</a>,
    /// as defined by the W3C.  This conformance level represents an XML document that might not have a root element
    /// but is otherwise well-formed. This level of checking ensures that the stream being read or written can be consumed
    /// by any processor as an <a href="https://www.w3.org/TR/2006/REC-xml-20060816/#wf-entities">XML 1.0 external parsed entity</a>.
    Fragment = 1,
    /// The XML data complies with the rules for a well-formed <a href="https://www.w3.org/TR/2006/REC-xml-20060816/#sec-well-formed">XML 1.0 document</a>,
    /// as defined by the W3C. This level of checking ensures that the stream being read or written can be consumed
    /// by any processor as an <a href="https://www.w3.org/TR/2006/REC-xml-20060816/#sec-well-formed">XML 1.0 document</a>.
    Document = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::ConformanceLevel>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::ConformanceLevel, const char_t*>, 3>& values();
};
/// @endcond


