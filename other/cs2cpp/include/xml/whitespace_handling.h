/// @file xml/whitespace_handling.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies how white space is handled.
enum class WhitespaceHandling
{
    /// Return @c Whitespace and @c SignificantWhitespace nodes. This is the default.
    All = 0,
    /// Return @c SignificantWhitespace nodes only.
    Significant = 1,
    /// Return no @c Whitespace and no @c SignificantWhitespace nodes.
    None = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::WhitespaceHandling>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::WhitespaceHandling, const char_t*>, 3>& values();
};
/// @endcond


