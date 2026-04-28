/// @file xml/write_state.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the state of the XmlWriter.
enum class WriteState
{
    /// Indicates that the XmlWriter::Write method has not yet been called.
    Start,
    /// Indicates that the prolog is being written.
    Prolog,
    /// Indicates that an element start tag is being written.
    Element,
    /// Indicates that an attribute value is being written.
    Attribute,
    /// Indicates that element content is being written.
    Content,
    /// Indicates that the XmlWriter::Close method has been called.
    Closed,
    /// An exception has been thrown, which has left the XmlWriter in an invalid state.
    /// You can call the XmlWriter::Close method to put the XmlWriter in the WriteState::Closed state.
    /// Any other XmlWriter method calls results in an InvalidOperationException.
    Error
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::WriteState>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::WriteState, const char_t*>, 7>& values();
};
/// @endcond


