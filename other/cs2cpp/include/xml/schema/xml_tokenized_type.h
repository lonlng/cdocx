/// @file xml/schema/xml_tokenized_type.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Represents the XML type for the string.
/// This allows the string to be read as a particular XML type, for example a CDATA section type.
enum class XmlTokenizedType
{
    /// CDATA type.
    CDATA = 0,
    /// ID type.
    ID = 1,
    /// IDREF type.
    IDREF = 2,
    /// IDREFS type.
    IDREFS = 3,
    /// ENTITY type.
    ENTITY = 4,
    /// ENTITIES type.
    ENTITIES = 5,
    /// NMTOKEN type.
    NMTOKEN = 6,
    /// NMTOKENS type.
    NMTOKENS = 7,
    /// NOTATION type.
    NOTATION = 8,
    /// ENUMERATION type.
    ENUMERATION = 9,
    /// QName type.
    QName = 10,
    /// NCName type.
    NCName = 11,
    /// No type.
    None = 12
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlTokenizedType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlTokenizedType, const char_t*>, 13>& values();
};
/// @endcond


