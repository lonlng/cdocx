/// @file xml/schema/xml_schema_derivation_method.h

#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace Schema {

/// Provides different methods for preventing derivation.
enum class XmlSchemaDerivationMethod
{
    /// Override default derivation method to allow any derivation.
    Empty = 0,
    /// Refers to derivations by @c Substitution.
    Substitution = 0x0001,
    /// Refers to derivations by @c Extension.
    Extension = 0x0002,
    /// Refers to derivations by @c Restriction.
    Restriction = 0x0004,
    /// Refers to derivations by @c List.
    List = 0x0008,
    /// Refers to derivations by @c Union.
    Union = 0x0010,
    /// @c \#all. Refers to all derivation methods.
    All = 0x00FF,
    /// Accepts the default derivation method.
    None = 0x0100
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::Schema::XmlSchemaDerivationMethod);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml::Schema);

template<>
struct EnumMetaInfo<System::Xml::Schema::XmlSchemaDerivationMethod>
{
    typedef void Flags;
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::Schema::XmlSchemaDerivationMethod, const char_t*>, 8>& values();
};
/// @endcond


