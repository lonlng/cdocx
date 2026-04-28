/// @file xml/xml_space.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the current @c xml:space scope.
enum class XmlSpace
{
    /// No @c xml:space scope.
    None = 0,
    /// The @c xml:space scope equals @c default.
    Default = 1,
    /// The @c xml:space scope equals @c preserve.
    Preserve = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlSpace>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlSpace, const char_t*>, 3>& values();
};
/// @endcond


