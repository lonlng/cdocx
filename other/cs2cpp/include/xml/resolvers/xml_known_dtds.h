/// @file xml/resolvers/xml_known_dtds.h

#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Resolvers {

/// The Resolvers::XmlKnownDtds enumeration is used by the Resolvers::XmlPreloadedResolver and
/// defines which well-known DTDs that the Resolvers::XmlPreloadedResolver recognizes.
enum class XmlKnownDtds
{
    /// Specifies that the Resolvers::XmlPreloadedResolver will not recognize any of the predefined DTDs.
    None = 0x00,
    /// Specifies that the Resolvers::XmlPreloadedResolver will recognize DTDs and entities that are defined in XHTML 1.0.
    Xhtml10 = 0x01,
    /// Specifies that the Resolvers::XmlPreloadedResolver will recognize DTDs and entities that are defined in RSS 0.91.
    Rss091 = 0x02,
    /// Specifies that the Resolvers::XmlPreloadedResolver will recognize all currently supported DTDs.
    /// This is the default behavior.
    All = 0xFFFF
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::Resolvers::XmlKnownDtds);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Resolvers
} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml::Resolvers);

template<>
struct EnumMetaInfo<System::Xml::Resolvers::XmlKnownDtds>
{
    typedef void Flags;
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Resolvers::XmlKnownDtds, const char_t*>, 4>& values();
};
/// @endcond


