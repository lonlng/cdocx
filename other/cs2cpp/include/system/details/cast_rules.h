///@file system/details/cast_rules.h
#pragma once

#include <defines.h>
#include <system/smart_ptr.h>
#include <system/object.h>
#include <system/string.h>
#include <system/constraints.h>
#include <system/nullable.h>
#include <system/exceptions.h>
#include <system/object_ext.h>

#include <type_traits>
#include <string>

namespace System { namespace Collections { namespace Generic { namespace Details { namespace CastRules {

/// Contains the functions to determine the cast type.
/// @tparam Source The source type.
/// @tparam Result The result type.
template <typename Source, typename Result>
struct CastType
{
    static constexpr bool None = std::is_same<Source, Result>::value;
    static constexpr bool Static = IsSmartPtr<Source>::value && IsSmartPtr<Result>::value && Constraints::IsBaseOf<Result, Source>::value && !None;
    static constexpr bool Dynamic = IsSmartPtr<Source>::value && IsSmartPtr<Result>::value && !None && !Static;
    static constexpr bool NullableBoxing = std::is_same<Result, Nullable<Source>>::value;
    static constexpr bool NullableUnboxing = std::is_same<Source, Nullable<Result>>::value;
    static constexpr bool Boxing = IsBoxable<Source>::value && std::is_same<Result, SmartPtr<Object>>::value;
    static constexpr bool Unboxing = std::is_same<Source, SmartPtr<Object>>::value && IsBoxable<Result>::value;
    static constexpr bool Invalid = !(None || Static || Dynamic || NullableBoxing || NullableUnboxing || Boxing || Unboxing);
};

/// Casts the source type to the result type.
/// Used when the source and the result types are the same.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::None, Result> Cast(Source value)
{
    return value;
}

/// Casts the source type to the result type.
/// Used when the source type can be statically cast to the result type.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Static, Result> Cast(Source value)
{
    return Result(value);
}

/// Casts the source type to the result type.
/// Used when the types aren't the same and the source type cannot be statically cast to the result type.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Dynamic, Result> Cast(Source value)
{
    return ExplicitCast<typename Result::Pointee_>(value);
}

/// Casts the source type to the result type.
/// Used when the source type is being boxed to the Nullable class instance.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::NullableBoxing, Result> Cast(Source value)
{
    return Result(value);
}

/// Casts the source type to the result type.
/// Used when the source type is being unboxed from the Nullable class instance.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
/// @throws NullReferenceException Is thrown when the source value is nullptr.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::NullableUnboxing, Result> Cast(Source value)
{
    if (value == nullptr)
        throw NullReferenceException(u"Can not unbox null value");

    return static_cast<Result>(value);
}

/// Casts the source type to the result type.
/// Used when the source type is being boxed to the Object class instance.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Boxing, Result> Cast(Source value)
{
    return ObjectExt::Box(value);
}

/// Casts the source type to the result type.
/// Used when the source type is being unboxed from the Object class instance.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Unboxing, Result> Cast(Source value)
{
    return ObjectExt::Unbox<Result>(value);
}

/// Casts the source type to the result type.
/// Used when the casting is invalid or the conversion is explicit.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns The cast result.
/// @throws ThrowInvalidCastException This exception is always thrown.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Invalid, Result> Cast(Source)
{
    System::Details::ThrowInvalidCastException();
}

// CanCast() implementation

/// Checks that the represented value is nullptr.
/// @tparam T The value type.
/// @returns Always returns false.
template <typename T>
bool IsNull(T)
{
    return false;
}

/// Checks that the represented value is nullptr.
/// @tparam T The value type.
/// @param value The value that must be checked.
/// @returns True if the value is nullptr, otherwise false.
template <typename T>
bool IsNull(SharedPtr<T> value)
{
    return value == nullptr;
}

/// Checks that the represented value is nullptr.
/// @tparam T The value type.
/// @param value The value that must be checked.
/// @returns True if the value is nullptr, otherwise false.
template <typename T>
bool IsNull(Nullable<T> value)
{
    return value == nullptr;
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns True when a non nullptr value is returns after casting, otherwise false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::None, bool> CanCast(Source value)
{
    return !IsNull(value);
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns True when a non nullptr value is returns after casting, otherwise false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Static, bool> CanCast(Source value)
{
    return value != nullptr;
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns True when a non nullptr value is returns after casting, otherwise false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Dynamic, bool> CanCast(Source value)
{
    return ObjectExt::Is<Result>(value);
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns Always returns true.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::NullableBoxing, bool> CanCast(Source)
{
    return true;
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns True when a non nullptr value is returns after casting, otherwise false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::NullableUnboxing, bool> CanCast(Source value)
{
    return value != nullptr;
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns Always returns true.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Boxing, bool> CanCast(Source)
{
    return true;
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns True if the cast operation was successfully done, otherwise false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Unboxing, bool> CanCast(Source value)
{
    if (value == nullptr)
        return false;

    return value->Is(ObjectExt::GetType<Result>());
}

/// Checks the cast possibility.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @returns Always returns false.
template <typename Source, typename Result>
std::enable_if_t<CastType<Source, Result>::Invalid, bool> CanCast(Source)
{
    return false;
}

}}}}} // namespace CastRules
