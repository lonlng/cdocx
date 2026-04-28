/// @file xml/namespace_handling.h

#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies whether to remove duplicate namespace declarations in the XmlWriter.
enum class NamespaceHandling
{
    /// Specifies that duplicate namespace declarations will not be removed.
    Default = 0x0,
    /// Specifies that duplicate namespace declarations will be removed. For the duplicate namespace to be removed,
    /// the prefix and the namespace must match.
    OmitDuplicates = 0x1
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::NamespaceHandling);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml);

template<>
struct EnumMetaInfo<System::Xml::NamespaceHandling>
{
    typedef void Flags;
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::NamespaceHandling, const char_t*>, 2>& values();
};
/// @endcond


