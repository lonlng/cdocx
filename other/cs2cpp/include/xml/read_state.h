/// @file xml/read_state.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the state of the reader.
enum class ReadState
{
    /// The XmlReader::Read method has not been called.
    Initial = 0,
    /// The XmlReader::Read method has been called. Additional methods may be called on the reader.
    Interactive = 1,
    /// An error occurred that prevents the read operation from continuing.
    Error = 2,
    /// The end of the file has been reached successfully.
    EndOfFile = 3,
    /// The XmlReader::Close method has been called.
    Closed = 4
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::ReadState>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::ReadState, const char_t*>, 5>& values();
};
/// @endcond


