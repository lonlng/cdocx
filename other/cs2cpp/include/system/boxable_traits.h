/// @file system/boxable_traits.h
#pragma once

#include <type_traits>
#include "defines.h"

namespace System
{
    class String;
    class TypeInfo;

    /// Template predicate that checks if boxing of the specified type is supported.
    /// @tparam T The type to check
    template <typename T>
    struct IsBoxable : std::integral_constant<bool,
        std::is_base_of<Details::BoxableObjectBase, T>::value || std::is_arithmetic<T>::value || std::is_enum<T>::value> {};

    /// @cond
    /// IsBoxable specialization for String.
    template<> struct IsBoxable<String> : std::true_type {};
    /// @endcond

    /// @cond
    /// IsBoxable specialization for TypeInfo.
    template<> struct IsBoxable<TypeInfo> : std::true_type {};
    /// @endcond
}
