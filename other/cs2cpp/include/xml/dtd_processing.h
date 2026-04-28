/// @file xml/dtd_processing.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the options for processing DTDs. The DtdProcessing enumeration is used by the XmlReaderSettings class.
enum class DtdProcessing
{
    /// Specifies that when a DTD is encountered, an XmlException is thrown with a message that states that DTDs are prohibited.
    /// This is the default behavior.
    Prohibit,
    /// Causes the DOCTYPE element to be ignored. No DTD processing occurs, and the DTD/DOCTYPE is lost on output.
    Ignore,
    /// Used for parsing DTDs.
    Parse
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::DtdProcessing>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::DtdProcessing, const char_t*>, 3>& values();
};
/// @endcond


