/// @file xml/new_line_handling.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies how to handle line breaks.
enum class NewLineHandling
{
    /// New line characters are replaced to match the character specified in the XmlWriterSettings::set_NewLineChars value.
    Replace = 0,
    /// New line characters are entitized. This setting preserves all characters when the output is read by a normalizing XmlReader.
    Entitize = 1,
    /// The new line characters are unchanged. The output is the same as the input.
    None = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::NewLineHandling>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::NewLineHandling, const char_t*>, 3>& values();
};
/// @endcond


