#pragma once

#include <system/enum_helpers.h>

namespace System {

namespace Reflection {

/// Marks each type of member
enum class MemberTypes
{
    /// Specifies that the member is a constructor.
    Constructor = 1,
    /// Specifies that the member is an event.
    Event = 2,
    /// Specifies that the member is a field.
    Field = 4,
    /// Specifies that the member is a method.
    Method = 8,
    /// Specifies that the member is a property.
    Property = 16,
    /// Specifies that the member is a type.
    TypeInfo = 32,
    /// Specifies that the member is a custom member type.
    Custom = 64,
    /// Specifies that the member is a nested type.
    NestedType = 128,
    /// Specifies all member types.
    All = 191
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Reflection::MemberTypes);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Reflection
} // namespace System

DECLARE_USING_ENUM_OPERATORS(System::Reflection);



