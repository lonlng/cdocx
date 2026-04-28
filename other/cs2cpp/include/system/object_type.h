/// @file system/object_ext.h
#pragma once

#include <system/object.h>
#include <system/smart_ptr.h>
#include <system/weak_ptr.h>
#include <system/convert.h>
#include <system/decimal.h>
#include <system/nullable.h>
#include <system/int32.h>
#include <system/int64.h>
#include <system/void.h>

#include <initializer_list>
#include <array>
#include <utility>
#include <type_traits>

namespace System
{

/// Provides static methods that implement object type getters.
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
class ObjectType
{
public:
    /// Implements typeof() translation.
    /// Overload for smart pointers.
    /// @tparam T Pointer object type.
    /// @param obj Object to get TypeInfo for.
    /// @return Const reference to TypeInfo structure describing the final class of object passed.
    template<typename T>
    static inline typename std::enable_if<IsSmartPtr<T>::value, const System::TypeInfo&>::type GetType(const T& obj)
    {
        return obj->GetType();
    }

    /// Implements typeof() translation.
    /// Overload for structures.
    /// @tparam T Structure type.
    /// @param obj Object to get TypeInfo for.
    /// @return Const reference to TypeInfo structure describing the final class of object passed.
    template<typename T>
    static inline typename std::enable_if<!IsExceptionWrapper<T>::value && !IsSmartPtr<T>::value && !std::is_fundamental<T>::value && !std::is_enum<T>::value && !IsNullable<T>::value, const System::TypeInfo&>::type GetType(const T& obj)
    {
        return obj.GetType();
    }

    /// Implements typeof() translation.
    /// Overload for exceptions.
    /// @tparam T Exception type.
    /// @param obj Object to get TypeInfo for.
    /// @return Const reference to TypeInfo structure describing the final class of object passed.
    template<typename T>
    static inline typename std::enable_if<IsExceptionWrapper<T>::value, const System::TypeInfo&>::type GetType(const T& obj)
    {
        return obj.Get()->GetType();
    }

    /// Implements typeof() translation.
    /// Overload for primitive types.
    /// @tparam T Primitive type.
    /// @param obj IGNORED
    /// @return Const reference to TypeInfo structure describing the type of object passed.
    template<typename T>
    static inline typename std::enable_if<std::is_fundamental<T>::value || std::is_enum<T>::value, const System::TypeInfo&>::type GetType(const T obj)
    {
        return GetType<T>();
    }

    /// Implements typeof() translation.
    /// Overload for Nullable types.
    /// @tparam T Nullable type.
    /// @param obj IGNORED
    /// @return Const reference to TypeInfo structure describing the type of object passed.
    template<typename T>
    static inline typename std::enable_if<IsNullable<T>::value, const System::TypeInfo&>::type GetType(const T obj)
    {
        if (!obj.get_HasValue())
        {
            // Getting type of empty nullable throws an exception
            Details::ThrowNullableNullReference();
        }

        return GetType<typename T::ValueType>();
    }

    /// Implements typeof() translation.
    /// Overload for primitive types.
    /// @tparam T Primitive type.
    /// @return Const reference to TypeInfo structure describing the type specified.
    template <typename T>
    static inline typename std::enable_if<std::is_fundamental<T>::value && !std::is_enum<T>::value, const System::TypeInfo&>::type GetType()
    {
        return TypeInfo::BoxedValueType<T>();
    }

    /// Implements typeof() translation.
    /// Overload for enum types.
    /// @tparam T Primitive type.
    /// @return Const reference to TypeInfo structure describing the type specified.
    template <typename T>
    static inline typename std::enable_if<std::is_enum<T>::value, const System::TypeInfo&>::type GetType()
    {
        return TypeInfo::BoxedValueType<T>();
    }

    /// Implements typeof() translation.
    /// Overload for structures and pointers.
    /// @tparam T Primitive type.
    /// @return Const reference to TypeInfo structure describing the strcture specified.
    template <typename T>
    static inline typename std::enable_if<(!std::is_fundamental<T>::value && !std::is_enum<T>::value && !IsBoxable<T>::value) || IsExceptionWrapper<T>::value, const System::TypeInfo&>::type GetType()
    {
        return T::Type(); // Works for pointers as well - they redirect Type() call to Pointee_::Type()
    }

    /// Implements typeof() translation.
    /// Overload for Nullable.
    /// @tparam T Nullable type.
    /// @return Const reference to TypeInfo structure describing the strcture specified.
    template <typename T>
    static inline typename std::enable_if<IsNullable<T>::value, const System::TypeInfo&>::type GetType()
    {
        return T::Type(); // Works for pointers as well - they redirect Type() call to Pointee_::Type()
    }

    /// Implements typeof() translation.
    /// Overload for MutlicastDelegate.
    /// @tparam T MutlicastDelegate type.
    /// @return Const reference to TypeInfo structure describing the strcture specified.
    template <typename T>
    static inline typename std::enable_if<detail::is_a<T, MulticastDelegate>::value, const System::TypeInfo&>::type GetType()
    {
        return T::Type(); // Works for pointers as well - they redirect Type() call to Pointee_::Type()
    }

    /// Implements typeof() translation.
    /// Overload for structures and pointers.
    /// @tparam T Primitive type.
    /// @return Const reference to TypeInfo structure describing the strcture specified or pointee type if called for SmartPtr.
    template <typename T>
    static inline typename std::enable_if<
        !std::is_fundamental<T>::value &&
        !std::is_enum<T>::value &&
        IsBoxable<T>::value &&
        !detail::is_a<T, MulticastDelegate>::value &&
        !IsNullable<T>::value,
        const System::TypeInfo&>::type GetType()
    {
        return TypeInfo::BoxedValueType<T>(); // Works for pointers as well - they redirect Type() call to Pointee_::Type()
    }

    /// Implements typeof() translation.
    /// Overload for string type.
    /// @tparam T Primitive type.
    /// @return Const reference to TypeInfo structure describing String type.
    static inline const System::TypeInfo& GetType(const String& obj)
    {
        ASPOSE_UNUSED(obj);
        return System::String::Type();
    }
};

/// Implements typeof() translation.
/// Overload for uint8_t.
template <>
inline const System::TypeInfo& ObjectType::GetType<uint8_t>()
{
    return System::Byte::Type();
}

/// Implements typeof() translation.
/// Overload for char16_t
template <>
inline const System::TypeInfo& ObjectType::GetType<char16_t>()
{
    return System::Char::Type();
}

/// Implements typeof() translation.
/// Overload for int32_t
template <>
inline const System::TypeInfo& ObjectType::GetType<int32_t>()
{
    return System::Int32::Type();
}

/// Implements typeof() translation.
/// Overload for int64_t
template <>
inline const System::TypeInfo& ObjectType::GetType<int64_t>()
{
    return System::Int64::Type();
}

/// Implements typeof() translation.
/// Overload for bool
template <>
inline const System::TypeInfo& ObjectType::GetType<bool>()
{
    return System::Boolean::Type();
}

/// Implements typeof() translation.
/// Overload for String
template <>
inline const System::TypeInfo& ObjectType::GetType<System::String>()
{
    return System::String::Type();
}

/// Implements typeof() translation.
/// Overload for DateTime
template <>
inline const System::TypeInfo& ObjectType::GetType<System::DateTime>()
{
    return System::DateTime::Type();
}

/// Implements typeof() translation.
/// Overload for Void
template <>
inline const System::TypeInfo& ObjectType::GetType<void>()
{
    return System::Void::Type();
}

} // namespace System
