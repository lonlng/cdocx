/// @file system/object_ext.h
#pragma once

#include "defines.h"
#include <system/object_type.h>
#include <system/enum.h>
#include <system/boxed_enum.h>
#include <system/text/string_builder.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/get_hash_code.h>

namespace System { namespace Collections { class IList; } }

namespace System
{

/// Provides static methods that emulate C# Object methods called for non-Object C++ types (strings, numbers, etc.).
/// This is a static type with no instance services.
/// You should never create instances of it by any means.
class ObjectExt : public ObjectType
{
public:
    /// Implements GetHashCode() calls; works on both Object subclasses and unrelated types.
    /// @tparam T Type to calculate hash code for.
    /// @param obj Object to calculate hash code for.
    /// @return Hash code calculated for object passed.
    template <typename T>
    static int GetHashCode(const T& obj)
    {
        return System::GetHashCode<T>(obj);
    }

    template<typename T, typename T2>
    static typename std::enable_if<IsExceptionWrapper<T>::value, bool>::type Equals(const T& obj, const T2& another)
    {
        if (obj.IsNull())
            System::Detail::SmartPtrCounter::ThrowNullReferenceException();
        return obj.Equals(another);
    }

    /// Substitution for C# Object.Equals calls working for any type in C++.
    /// Overload for smart pointer types.
    /// @tparam T First object type.
    /// @tparam T2 Second object type.
    /// @param obj First object.
    /// @param another Second object.
    /// @return True if objects are considered equal, false otherwise.
    template<typename T, typename T2>
    static typename std::enable_if<IsSmartPtr<T>::value, bool>::type Equals(const T& obj, const T2& another)
    {
        return obj->Equals(another);
    }

    /// Substitution for C# Object.Equals calls working for any type in C++.
    /// Overload for structure types.
    /// @tparam T First object type.
    /// @tparam T2 Second object type.
    /// @param obj First object.
    /// @param another Second object.
    /// @return True if objects are considered equal, false otherwise.
    template<typename T, typename T2>
    static typename std::enable_if<!IsExceptionWrapper<T>::value && !IsSmartPtr<T>::value && !std::is_scalar<T>::value, bool>::type Equals(T obj, const T2& another)
    {
        return obj.Equals(another);
    }

    /// Substitution for C# Object.Equals calls working for any type in C++.
    /// Overload for scalar types.
    /// @tparam T First object type.
    /// @tparam T2 Second object type.
    /// @param obj First object.
    /// @param another Second object.
    /// @return True if objects are considered equal, false otherwise.
    template<typename T, typename T2>
    static typename std::enable_if<!IsSmartPtr<T>::value && std::is_scalar<T>::value, bool>::type Equals(const T& obj, const T2& another)
    {
        return (obj == another);
    }

    /// Substitution for C# Object.Equals calls working for any type in C++.
    /// Overload for string literal with string comparison.
    /// @tparam N String literal size.
    /// @param obj String literal.
    /// @param another String.
    /// @return True if strings match, false otherwise.
    template<size_t N>
    static bool Equals(const char_t (&obj)[N], String another)
    {
        return another == obj;
    }


    /// Substitution for C# ToString method to work on any C++ type.
    /// @param obj String literal to convert to string.
    /// @return String representation of @p obj.
    static inline String ToString(const char_t * obj)
    {
        return String(obj);
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Nullable type.
    /// @param obj Nullable object to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static inline String ToString(const Nullable<T> & obj)
    {
        return (obj.IsNull() ? u"" : ToString(obj.get_Value()));
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Enum type.
    /// @param obj Enum value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<std::is_enum<T>::value, String>::type ToString(const T& obj)
    {
        String str = Enum<T>::GetName(obj);
        return !str.IsNullOrEmpty() ? str : System::Convert::ToString(static_cast<typename std::underlying_type<T>::type>(obj));
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Smart pointer type.
    /// @param obj SmartPtr value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<IsSmartPtr<T>::value, String>::type ToString(const T& obj)
    {
        return obj->ToString();
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Smart pointer type or ExceptionWrapper.
    /// @param obj Smart pointer or ExceptionWrapper to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<IsSmartPtr<T>::value || std::is_pointer<T>::value || IsExceptionWrapper<T>::value, String>::type ToString(T& obj)
    {
        return obj->ToString();
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Scalar type.
    /// @param obj Scalar value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value && std::is_scalar<T>::value && !std::is_enum<T>::value, String>::type ToString(T& obj)
    {
        return System::Convert::ToString(obj);
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Scalar type.
    /// @param obj Scalar value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value && std::is_scalar<T>::value && !std::is_enum<T>::value, String>::type ToString(T&& obj)
    {
        return System::Convert::ToString(obj);
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Structure type.
    /// @param obj Structure value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<!IsExceptionWrapper<T>::value && !IsSmartPtr<T>::value && !std::is_scalar<T>::value && !IsNullable<T>::value, String>::type ToString(T& obj)
    {
        return obj.ToString();
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Structure type.
    /// @param obj Structure value to convert to string.
    /// @return String representation of @p obj.
    template <typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value && !std::is_scalar<T>::value && !IsNullable<T>::value, String>::type ToString(const T& obj)
    {
        return obj.ToString();
    }

    /// Substitution for C# ToString method to work on any C++ type.
    /// @tparam T Scalar type.
    /// @param obj Scalar value to convert to string.
    /// @return String representation of @p obj.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value && !std::is_scalar<T>::value && !IsNullable<T>::value && !std::is_reference<T>::value, String>::type ToString(T&& obj)
    {
        return obj.ToString();
    }

    /// Boxes value types for converting to Object.
    /// Implementation for enum types.
    /// @tparam T Enum type.
    /// @param value Enum value to box.
    /// @return Smart pointer to object keeping boxed value.
    template<typename T>
    static typename std::enable_if<std::is_enum<T>::value, System::SmartPtr<System::Object>>::type Box(const T& value)
    {
        return System::MakeObject<BoxedEnum<T>>(value);
    }

    /// Boxes value types for converting to Object.
    /// Implementation for non-enum types.
    /// @tparam T Value type.
    /// @param value Value to box.
    /// @return Smart pointer to object keeping boxed value.
    template<typename T>
    static typename std::enable_if<!std::is_enum<T>::value && !IsNullable<T>::value, System::SmartPtr<System::Object>>::type Box(const T& value)
    {
        return System::MakeObject<BoxedValue<T>>(value);
    }

    /// Boxes Nullable types for converting to Object.
    /// @tparam T Value type.
    /// @param value Value to box.
    /// @return Smart pointer to object keeping boxed value.
    template<typename T>
    static typename std::enable_if <IsNullable<T>::value, System::SmartPtr<System::Object>>::type Box(const T& value)
    {
        if (value == nullptr)
            return nullptr;

        return System::MakeObject<BoxedValue<typename T::ValueType>>(value.get_Value());
    }

    /// Unboxes value types after converting to Object.
    /// Implementation for enum types.
    /// @tparam T Enum type.
    /// @param obj Object to unbox.
    /// @return Enum value.
    template<typename T>
    static typename std::enable_if<std::is_enum<T>::value, T>::type Unbox(const SmartPtr<Object>& obj)
    {
        using UT = typename std::underlying_type<T>::type;

        if (obj && obj->Is(BoxedEnum<T>::Type()))
        {
            auto boxed = obj.template Cast<BoxedEnum<T>>();
            return static_cast<T>(boxed->unbox());
        }
        using UT = typename std::underlying_type<T>::type;
        if (obj && obj->Is(ObjectExt::GetType<UT>()))
        {
            auto boxed = obj.Cast<BoxedValue<UT>>();
            return static_cast<T>(boxed->unbox());
        }


        throw InvalidCastException();
    }

    /// Unboxes value types after converting to Object.
    /// Implementation for non-enum & non-nullable types.
    /// @tparam T Value type.
    /// @param obj Object to unbox.
    /// @return Unboxed value.
    template<class T>
    static typename std::enable_if<!std::is_enum<T>::value && detail::has_operator_equal<T>::value, T>::type Unbox(const SmartPtr<Object>& obj)
    {
        if (obj)
        {
            if (obj->Is(ObjectExt::GetType<T>()))
            {
                auto boxed = obj.template Cast<BoxedValue<T>>();
                return boxed->unbox();
            }

            throw InvalidCastException();
        }
        throw NullReferenceException();
    }

    /// Unboxes value types after converting to Object.
    /// Implementation for non-enum & non-nullable types.
    /// @tparam T Value type.
    /// @param obj Object to unbox.
    /// @return Unboxed value.
    template<class T>
    static typename std::enable_if<!std::is_enum<T>::value && !detail::has_operator_equal<T>::value, T>::type Unbox(const SmartPtr<Object>& obj)
    {
            
        if (obj && obj->Is(BoxedValue<T>::Type()))
        {
            auto boxed = obj.template Cast<BoxedValue<T>>();
            return boxed->unbox();
        }
        
        throw InvalidCastException();
    }

    /// Unboxes enum types to integer.
    /// @tparam T Destination integer type.
    /// @tparam E Source enum type.
    /// @param e Value to unbox.
    /// @return Integer representation of enum.
    template<class T, class E>
    static typename std::enable_if<std::is_enum<E>::value && std::numeric_limits<T>::is_integer, T>::type Unbox(E e)
    {
        return static_cast<T>(e);
    }

    /// Converts enum types.
    /// @tparam T Destination enum type.
    /// @tparam E Source enum type.
    /// @param e Value to unbox.
    /// @return Converted enum value.
    template<class T, class E>
    static typename std::enable_if<std::is_enum<E>::value && std::is_enum<T>::value, T>::type Unbox(E e)
    {
        return static_cast<T>(e);
    }

    /// Unboxes string from boxed value.
    /// @throw Nothing.
    /// @param obj Boxed string value.
    /// @return If @p obj is a boxed string, returns unboxed value, otherwise returns empty string.
    static ASPOSECPP_SHARED_API String UnboxStringSafe(const SmartPtr<Object>& obj);

    /// Unboxes object to nullable type.
    /// @tparam T Destination type.
    /// @param obj Object to unbox.
    /// @param safe If true, return nullptr on failure, otherwise throw InvalidCastException.
    /// @return Unboxed nullable value (could be null).
    template<class T>
    static Nullable<T> UnboxToNullable(const SmartPtr<Object>& obj, bool safe = true)
    {
        if (obj)
        {
            if (obj->Is(ObjectExt::GetType<T>()))
            {
                auto boxed = obj.template Cast<BoxedValue<T>>();
                return Nullable<T>(boxed->unbox());
            }
        }

        if (!obj || safe)
            return Nullable<T>(nullptr);

        throw InvalidCastException();
    }

    /// Implements 'is' operator translation.
    /// Specialization for boxable (value) types which exactly is that they are
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator. Ignored.
    /// @return Always true
    template <class T>
    static typename std::enable_if<System::IsBoxable<T>::value, bool>::type Is(const T& obj)
    {
        return true;
    }

    /// Implements 'is' operator translation.
    /// Specialization for pointer types optimized for 'final' classes.
    /// @tparam T Target type.
    /// @tparam U Tested type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<std::is_convertible<T, Object>::value && std::is_final<T>::value &&
                                   !System::IsBoxable<T>::value && System::IsSmartPtr<U>::value,
        bool>::type Is(const U& obj)
    {
        if (obj == nullptr)
            return false;

        return typeid(*obj.get()) == typeid(T);
    }

    /// Implements 'is' operator translation.
    /// Specialization for pointer types.
    /// @tparam T Target type.
    /// @tparam U Tested type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<std::is_convertible<T, Object>::value&& !std::is_final<T>::value &&
                                   !System::IsBoxable<T>::value && System::IsSmartPtr<U>::value,
        bool>::type Is(const U& obj)
    {
        if (!obj)
            return false;

        return dynamic_cast<T*>(obj.get()) != nullptr;
    }

    /// Implements 'is' operator translation.
    /// Specialization for value types.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static typename std::enable_if<std::is_convertible<T, Object>::value,
        bool>::type Is(const Object& obj)
    {
        return obj.Is(T::Type());
    }

    /// Implements 'is' operator translation.
    /// Specialization for unconvertible types.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return Always returns false as types are unconvertible.
    template<class T>
    static typename std::enable_if<!std::is_convertible<T, Object>::value,
        bool>::type Is(const Object& obj)
    {
        return false;
    }

    /// Implements 'is' operator translation.
    /// Specialization for pointer types.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<IsSmartPtr<T>::value, bool>::type Is(const SmartPtr<U>& obj)
    {
        if (!obj)
            return false;

        return dynamic_cast<typename T::Pointee_*>(obj.get()) != nullptr;
    }

    /// Implements 'is' operator translation.
    /// Specialization for exception wrapper types.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<IsExceptionWrapper<T>::value, bool>::type Is(const ExceptionWrapper<U>& obj)
    {
        if (obj == nullptr)
            return false;

        return Is<SmartPtr<typename T::ExceptionType>>(obj.Get());
    }

    /// Implements 'is' operator translation.
    /// Specialization for nullable types.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static typename std::enable_if<IsNullable<T>::value, bool>::type Is(const SmartPtr<Object>& obj)
    {
        if (!obj)
            return false;

        if (obj->Is(System::ObjectExt::GetType<typename T::ValueType>()))
            return true;

        return false;
    }

    /// Implements 'is' operator translation.
    /// Specialization for boxable types with == operator defined.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static typename std::enable_if<
        System::IsBoxable<T>::value && !IsNullable<T>::value && !std::is_enum<T>::value && detail::has_operator_equal<T>::value,
        bool
    >::type Is(const SmartPtr<Object>& obj)
    {
        if (!obj)
            return false;

        if (obj->Is(System::ObjectExt::GetType<T>()))
        {
            return true;
        }

        if (obj->Is(Nullable<T>::Type()))
        {
            auto boxed = obj.Cast<BoxedValue<Nullable<T>>>();
            return !boxed->unbox().IsNull();
        }

        return false;
    }

    /// Implements 'is' operator translation.
    /// Specialization for boxable types without defined ==.
    /// @tparam T Target type.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static typename std::enable_if<
        System::IsBoxable<T>::value && !IsNullable<T>::value && !std::is_enum<T>::value && !detail::has_operator_equal<T>::value,
        bool
    >::type Is(const SmartPtr<Object>& obj)
    {
        if (!obj)
            return false;

        if (obj->Is(TypeInfo::BoxedValueType<T>()))
        {
            return true;
        }

        return false;
    }

    /// Implements 'is' operator translation.
    /// Specialization value types boxed to interfaces
    /// @tparam T Target type.
    /// @tparam V Type of the pointed object.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template <class T, class V>
    static typename std::enable_if<
        System::IsBoxable<T>::value && !IsNullable<T>::value && !std::is_enum<T>::value && !std::is_same<V, Object>::value,
        bool>::type Is(const SmartPtr<V>& obj)
    {
        return dynamic_cast<T*>(obj.get()) != nullptr;
    }

    /// Implements 'is' operator translation.
    /// Specialization for enum types.
    /// @tparam T Target type.
    /// @tparam U Type of the pointed object.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<std::is_enum<T>::value, bool>::type Is(const SmartPtr<U>& obj)
    {
        if (!obj)
            return false;

        if (obj->Is(TypeInfo::BoxedValueType<T>()))
            return Enum<T>::IsDefined(Unbox<T>(obj));

        return false;
    }

    /// Implements 'is' operator translation.
    /// Specialization for enum types vs weak pointers.
    /// @tparam T Target type.
    /// @tparam U Type of the pointed object.
    /// @param obj Object to test for 'is' operator.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static typename std::enable_if<std::is_enum<T>::value, bool>::type Is(const WeakPtr<U>& obj)
    {
        if (!obj)
            return false;

        if (obj->Is(TypeInfo::BoxedValueType<T>()))
            return Enum<T>::IsDefined(Unbox<T>(obj));

        return false;
    }

private:
    /// Implementation for 'is' operator translation.
    /// @tparam T Target type.
    /// @tparam U Expression type.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static bool IsImpl()
    {
        TypeInfo typeU = ObjectExt::GetType<U>();
        TypeInfo typeT = ObjectExt::GetType<T>();
        return typeU == typeT || typeU.IsSubclassOf(typeT);
    }

public:
    /// Implements 'is' operator translation.
    /// Specialization for Nullable type
    /// @tparam T Target type.
    /// @param value Nullable type.
    /// @return True if 'is' returns true, false otherwise.
    template<class T, class U>
    static bool Is(const Nullable<U>& value)
    {
        if (value == nullptr)
            return false;

        return IsImpl<T, U>();
    }

    /// Implements 'is' operator translation.
    /// Specialization for string literal.
    /// @tparam T Target type.
    /// @param str String literal.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static bool Is(const char16_t* str)
    {
        if (str == nullptr)
            return false;

        return IsImpl<T, System::String>();
    }

    /// Implements 'is' operator translation.
    /// Specialization for integer literal.
    /// @tparam T Target type.
    /// @param value integer literal.
    /// @return True if 'is' returns true, false otherwise.
    template<class T>
    static bool Is(int32_t value)
    {
        ASPOSE_UNUSED(value);

        return IsImpl<T, System::Int32>();
    }

    /// Checks if object is a boxed value.
    /// @param obj Object to test for being boxed value.
    /// @return True if @p obj is a boxed value, false otherwise.
    static ASPOSECPP_SHARED_API bool IsBoxedValue(const SmartPtr<Object>& obj);

    /// Converts unknown type to Object, handling both smart pointer type and value type situations.
    /// @tparam T Type to convert to Object.
    /// @param obj Object to convert.
    /// @return Smart pointer to Object being either converted pointer or boxed value.
    template<typename T>
    static typename std::enable_if<IsSmartPtr<T>::value, System::SmartPtr<Object> >::type UnknownToObject(T obj)
    {
        return obj.template Cast<Object>();
    }

    /// Converts unknown type to Object, handling both smart pointer type and value type situations.
    /// @tparam T Type to convert to Object.
    /// @param obj Object to convert.
    /// @return Smart pointer to Object being either converted pointer or boxed value.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value, System::SmartPtr<Object> >::type UnknownToObject(const T& obj)
    {
        return Box<T>(obj);
    }

    /// Converts Object to unknown type, handling both smart pointer type and bpxed value situations.
    /// @tparam T Type to convert Object to.
    /// @param obj Object to convert.
    /// @return Either unboxed value or converted pointer.
    template<typename T>
    static typename std::enable_if<IsSmartPtr<T>::value, T>::type ObjectToUnknown(SmartPtr<Object> obj)
    {
        return obj.template Cast<typename T::Pointee_>();
    }

    /// Converts Object to unknown type, handling both smart pointer type and boxed value situations.
    /// @tparam T Type to convert Object to.
    /// @param obj Object to convert.
    /// @return Either unboxed value or converted pointer.
    template<typename T>
    static typename std::enable_if<!IsSmartPtr<T>::value, T>::type ObjectToUnknown(SmartPtr<Object> obj)
    {
        return System::ObjectExt::Unbox<T>(obj);
    }
        
    /// Checks whether unknown type object is nullptr.
    /// Overload for non-scalar types.
    /// @tparam T Object type.
    /// @param obj Object to check.
    /// @return True if 'obj == nullptr' is true, false otherwise. 
    template<typename T>
    static typename std::enable_if<!std::is_scalar<T>::value, bool>::type UnknownIsNull(T obj)
    {
        return obj == nullptr;
    }

    /// Checks whether unknown type object is nullptr.
    /// Overload for scalar types.
    /// @tparam T Object type.
    /// @param obj Object to check.
    /// @return Always returns false.
    template<typename T>
    static typename std::enable_if<std::is_scalar<T>::value, bool>::type UnknownIsNull(T obj)
    {
        return false;
    }
    
    /// Implementation of '??' operator translation for non-nullable types.
    /// Overload for case if RT2 is convertable to RT1 
    /// @tparam T0 LHS value type.
    /// @tparam T1 Type of lambda encapsulating RHS expression.
    /// @param value LHS value.
    /// @param func RHS expression.
    /// @return If LHS value is not null, returns LHS, otherwise calculates RHS expression and returns result.
    template<typename RT1, typename RT2, typename F>
    static typename std::conditional<std::is_convertible<RT2, RT1>::value, RT1, RT2>::type CoalesceInternal(RT1 value, F func)
    {
        return value != nullptr ? value : func();
    }


    /// Implementation of '??' operator translation for non-nullable types.
    /// @tparam T0 LHS value type.
    /// @tparam T1 Type of lambda encapsulating RHS expression.
    /// @param value LHS value.
    /// @param func RHS expression.
    /// @return If LHS value is not null, returns LHS, otherwise calculates RHS expression and returns result.
    template<typename T0, typename T1>
    static auto Coalesce(T0 value, T1 func)
    {
        using retval_t = System::Details::ResultOf<T1>;
        return CoalesceInternal<T0, retval_t, typename std::function<retval_t()>>(value, func);
    }

    /// Implementation of '??' operator translation for nullable types.
    /// @tparam T0 LHS value type.
    /// @tparam T1 Type of lambda encapsulating RHS expression.
    /// @param value LHS value.
    /// @param func RHS expression.
    /// @return If LHS value is not null, returns LHS, otherwise calculates RHS expression and returns result.
    template<typename T0, typename T1>
    static T0 Coalesce(System::Nullable<T0> value, T1 func)
    {
        return !value.IsNull() ? value.get_Value() : func();
    }

    /// Implementation of '??=' operator translation
    /// @tparam T0 LHS value type.
    /// @tparam T1 Type of lambda encapsulating RHS expression.
    /// @param value LHS value.
    /// @param func RHS expression.
    /// @return If LHS value is not null, returns LHS, otherwise calculates RHS expression and returns result.
    template <typename T0, typename T1>
    static auto CoalesceAssign(T0& value, T1 func) -> T0&
    {
        if (value == nullptr)
        {
            value = func();
        }
        return value;
    }

    /// Boxes enum types for being propagated as Object.
    /// @tparam T Enum type to box.
    /// @param enumValue Enum value to box.
    /// @return Boxed enum value.
    template<typename T>
    static SmartPtr<System::BoxedValueBase> BoxEnum(T enumValue)
    {
        return SmartPtr<System::BoxedValueBase>(new System::BoxedEnum<T>(enumValue));
    }
    
    /// Converts array fundamental values (which C# does implicitly but C++ apparently does not).
    /// @tparam To Target type.
    /// @tparam From Source types.
    /// @param args Values to convert and push to target array.
    /// @return Array containing converted copies of all arguments in the same order.
    template<typename To, typename ...From>
    static typename std::enable_if<(std::is_fundamental<To>::value), std::array<To, sizeof...(From)>>::type ArrayInitializerCast(From ...args)
    {
        return std::array<To, sizeof...(From)>({ static_cast<To>(args)... });
    }

    static ASPOSECPP_SHARED_API SmartPtr<System::Collections::IList> CastToIList(const SmartPtr<Object>& obj);

    template<typename T>
    static typename std::enable_if<System::IsBoxable<T>::value, System::SharedPtr<System::Object>>::type ExplicitCastToObject(const T& value)
    {
        return ObjectExt::Box(value);
    }

    template<typename T>
    static typename std::enable_if<System::IsSmartPtr<T>::value, System::SharedPtr<System::Object>>::type ExplicitCastToObject(const T& value)
    {
        return value;
    }
};

/// Emulates C#-style floating point comparison where two NaNs are considered equal even though according to IEC 60559:1989 NaN is not equal to any value,
/// including NaN.
/// @param obj LHS floating point value.
/// @param another RHS floating point value.
/// @return True if @p obj and @p another are both NaN or equal, false otherwise.
template<>
inline bool ObjectExt::Equals<float, float>(const float& obj, const float& another)
{
    return (std::isnan(obj) && std::isnan(another)) ? true : obj == another;
}

/// Emulates C#-style floating point comparison where two NaNs are considered equal even though according to IEC 60559:1989 NaN is not equal to any value,
/// including NaN.
/// @param obj LHS floating point value.
/// @param another RHS floating point value.
/// @return True if @p obj and @p another are both NaN or equal, false otherwise.
template<>
inline bool ObjectExt::Equals<double, double>(const double& obj, const double& another)
{
    return (std::isnan(obj) && std::isnan(another)) ? true : obj == another;
}

/// Boxes string values.
/// @param value Value to box.
/// @return Boxed value or null, if source string is null.
template<>
inline SmartPtr<Object> ObjectExt::Box<String>(const String& value)
{
    return value.IsNull() ? nullptr : MakeObject<BoxedValue<String>>(value);
}

/// Unboxes string values.
/// @param obj Object to unbox
/// @return String representation of boxed string, can be null if boxed string was null.
template<>
inline String ObjectExt::Unbox<String>(const SmartPtr<Object>& obj)
{
    if (obj == nullptr)
        return String();

    if (obj && obj->Is(String::Type()))
    {
        auto boxed = obj.Cast<BoxedValue<String>>();
        return boxed->unbox();
    }

    throw InvalidCastException();
}

namespace Details {

/// Special traits to detect arrays of object-derived classes or pointers to array of object-derived classes 
template<typename T>
struct IsObjectArray : std::false_type {};
template <typename O>
struct IsObjectArray<System::Array<SmartPtr<O>>> : std::is_base_of<System::Object, O> {};
template <>
struct IsObjectArray<System::Array<String>> : std::true_type {};
template <typename A>
struct IsObjectArray<SmartPtr<A>> : IsObjectArray<A> {};


/// Contains constants to determine way to cast soruce type to result type.
/// @tparam Source The source type.
/// @tparam Result The result type.
template <typename Source, typename Result>
struct CastType
{
    /// Same types, no cast is needed
    static constexpr bool None = std::is_same<Source, Result>::value;

    /// Cast between arithmetic types or enums
    static constexpr bool StaticArithmetic =
        (std::is_enum<Source>::value || std::is_arithmetic<Source>::value) &&
        (std::is_enum<Result>::value || std::is_arithmetic<Result>::value);
    /// Cast from IntPtr
    static constexpr bool StaticIntPtr =
        (std::is_same<Source, IntPtr>::value && (std::is_arithmetic<Result>::value || std::is_pointer<Result>::value)) ||
        (std::is_same<Result, IntPtr>::value && (std::is_arithmetic<Source>::value || std::is_pointer<Source>::value));
    /// Cast from chars pointer to String
    static constexpr bool StaticString = std::is_same<Result, String>::value && std::is_constructible<String, Source>::value;
    /// Static cast using constructor cast is needed
    static constexpr bool Static = !None && (StaticArithmetic || StaticIntPtr || StaticString);

    /// Cast between two exception wrappers
    static constexpr bool Exception = !None &&
        IsExceptionWrapper<Source>::value && IsExceptionWrapper<Result>::value &&
        (std::is_convertible<Result, Source>::value || std::is_base_of<Result, Source>::value);
    /// Cast from common object to exception wrapper
    static constexpr bool ObjectToException = !None &&
        std::is_same<SharedPtr<System::Object>, Source>::value && IsExceptionWrapper<Result>::value;

    /// Cast array of object to array of objects of other type, all other arrays cast as whole objects
    static constexpr bool Array = !None && IsObjectArray<Result>::value && IsObjectArray<Source>::value;

    /// Cast to smart pointer
    static constexpr bool ToSmartPointer = std::is_base_of<System::Object, Result>::value &&
                                      !IsExceptionWrapper<Result>::value && !IsBoxable<Result>::value;
    /// Cast raw pointer to smart pointer
    static constexpr bool RawPointer = ToSmartPointer && std::is_pointer<Source>::value &&
                                       std::is_base_of<Object, std::remove_pointer_t<Source>>::value;
    /// Cast smart pointer to smart pointer (but without expicit SmartPtr<...> in result type)
    static constexpr bool Pointer = !None && !Array && ToSmartPointer && IsSmartPtr<Source>::value;
    /// Cast smart pointer to smart pointer (with expicit SmartPtr<...> in result type)
    static constexpr bool PointerToPointer = !None && !Array && IsSmartPtr<Source>::value && IsSmartPtr<Result>::value;

    /// Unboxing object and box it to nullable
    static constexpr bool UnboxingToNullable =
        (std::is_same<Source, SmartPtr<Object>>::value || std::is_same<Source, std::nullptr_t>::value) &&
        IsNullable<Result>::value;

    /// Unboxing some other smart pointer and box it to nullable
    static constexpr bool InterfaceUnboxingToNullable =
        !std::is_same<Source, SmartPtr<Object>>::value && IsSmartPtr<Source>::value && IsNullable<Result>::value;

    /// Unboxing some other smart pointer to boxable-derived
    static constexpr bool InterfaceUnboxing = !std::is_same<Source, SmartPtr<Object>>::value &&
                                              IsSmartPtr<Source>::value && !IsNullable<Result>::value &&
                                              std::is_base_of<Details::BoxableObjectBase, Result>::value;

    /// Boxing nullable object
    static constexpr bool NullableBoxing = !UnboxingToNullable && (std::is_same<Result, Nullable<Source>>::value ||
                                           (IsNullable<Result>::value && std::is_same<Source, std::nullptr_t>::value));
    /// Unboxing nullable object
    static constexpr bool NullableUnboxing = std::is_same<Source, Nullable<Result>>::value;

    /// Common for any boxing cast
    static constexpr bool BoxingCommon = !None && (std::is_base_of<Object, Result>::value || IsSmartPtr<Result>::value);
    /// Box enums to objects
    static constexpr bool EnumBoxing = BoxingCommon && std::is_enum<Source>::value;
    /// Moving copy of stack object to heap
    static constexpr bool HeapifyBoxing = std::is_same<Result, SharedPtr<Source>>::value;
    /// Moving copy of non-trivial boxable object to heap and getting interface from it
    static constexpr bool InterfaceBoxing = BoxingCommon && !HeapifyBoxing && !std::is_same<Result, Object>::value &&
                                          std::is_base_of<Details::BoxableObjectBase, Source>::value;
    /// Box other boxable data to objects
    static constexpr bool Boxing = BoxingCommon && !EnumBoxing && !HeapifyBoxing && !InterfaceBoxing && IsBoxable<Source>::value;
    /// Box strings to objects
    static constexpr bool StringBoxing = BoxingCommon && !Boxing && !Pointer && !std::is_same<Source, std::nullptr_t>::value &&
        std::is_constructible<String, Source>::value;

    /// Unboxing from any object to value
    static constexpr bool Unboxing =
        !UnboxingToNullable && !InterfaceUnboxing && IsSmartPtr<Source>::value && IsBoxable<Result>::value;

    /// Unboxing directly to string
    static constexpr bool UnboxingToString = std::is_same<Result, String>::value && std::is_same<Source, SmartPtr<Object>>::value;

    /// All other casts from nullptr
    static constexpr bool Null = !Static && !UnboxingToNullable && !NullableBoxing &&
                                 std::is_same<Source, std::nullptr_t>::value;

    /// Attempt to unbox to non-object type, uncomplilable in C# but can happen during templates instantiation
    static constexpr bool InvalidUnboxing = Unboxing && !InterfaceUnboxingToNullable && !InterfaceUnboxing && !std::is_same<Source, SmartPtr<Object>>::value;
};

} // namespace Details

/// Casts the source type to the result type using explicit cast.
/// Used when the source and the result types are the same.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::None, Result> ExplicitCast(const Source& value)
{
    return value;
}

/// Casts the source type to the result type using explicit cast.
/// Used when simple constructor-like cast is needed.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Static, Result> ExplicitCast(const Source& value)
{
    return Result(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for exception wrappers.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Exception, Result> ExplicitCast(const Source& value)
{
    return value.Get().template Cast<typename Result::ExceptionType, std::true_type>() ? Result(value.Get())
                                                                                       : Result(nullptr);
}

/// Casts the source type to the result type using explicit cast.
/// Used for casting object to exception.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::ObjectToException, Result> ExplicitCast(const Source& value)
{
    auto exception_ptr = value.template Cast<typename Result::ExceptionType, std::true_type>();
    return exception_ptr ? Result(exception_ptr.template Cast<System::Details_Exception, std::true_type>())
                         : Result(nullptr);
}

/// Casts the source type to the result type using explicit cast.
/// Used when the source and result both are smart pointers (without expicit SmartPtr<...> in result type).
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Pointer, typename CastResult<Result>::type>
    ExplicitCast(const Source& value)
{
    return value.template Cast<Result, std::true_type>();
}

/// Casts the source type to the result type using explicit cast.
/// Used when the casting raw pointer to smart pointer.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::RawPointer, typename CastResult<std::remove_pointer_t<Result>>::type>
    ExplicitCast(Source value)
{
    return ExplicitCast<Result>(SmartPtr<std::remove_pointer_t<Source>>(value));
}

/// Casts the source type to the result type using explicit cast.
/// Used when the source and result both are smart pointers (with expicit SmartPtr<...> in result type).
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::PointerToPointer, Result>
    ExplicitCast(const Source& value)
{
    return ExplicitCast<typename Result::Pointee_>(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for unboxing object to nullable.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::UnboxingToNullable, Result>
    ExplicitCast(const Source& value)
{
    return ObjectExt::UnboxToNullable<typename Result::ValueType>(value, false);
}

/// Casts the source type to the result type using explicit cast.
/// Used to box nullable.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::NullableBoxing, Result> ExplicitCast(const Source& value)
{
    return Result(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for unboxing nullable object.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::NullReferenceException If value is empty.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::NullableUnboxing, Result> ExplicitCast(const Source& value)
{
    if (value == nullptr)
        throw NullReferenceException(u"Can not unbox null value");

    return static_cast<Result>(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for enum boxing
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::EnumBoxing, SmartPtr<BoxedValueBase>>
    ExplicitCast(const Source& value)
{
    return ObjectExt::BoxEnum(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for copying value types to heap when value type should be referenced as smart pointer (in generics constrained with interface type
/// but specialized with structure implementing this interface).
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::HeapifyBoxing, typename CastResult<Result>::type>
    ExplicitCast(const Source& value)
{
    return MakeObject<Source>(value).template Cast<typename Result::Pointee_, std::true_type>();
}

/// Casts the source type to the result type using explicit cast.
/// Used for getting interfaces from value types.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::InterfaceBoxing, typename CastResult<Result>::type>
    ExplicitCast(const Source& value)
{
    return MakeObject<Source>(value).template Cast<Result, std::true_type>();
}

/// Casts the source type to the result type using explicit cast.
/// Used for common boxing
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Boxing, typename CastResult<Result>::type>
    ExplicitCast(const Source& value)
{
    return ObjectExt::Box(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for System::String boxing
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::StringBoxing, typename CastResult<Result>::type>
    ExplicitCast(const Source& value)
{
    return ObjectExt::Box<String>(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for unboxing interfaces
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::InterfaceUnboxing, Result> ExplicitCast(const Source& value)
{
    return *(value.template Cast<Result, std::true_type>());
}

/// Casts the source type to the result type using explicit cast.
/// Used for common unboxing
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Unboxing, Result> ExplicitCast(const Source& value)
{
    return ObjectExt::Unbox<Result>(value);
}

/// Casts the source type to the result type using explicit cast.
/// Used for nullptr casting
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Null, typename CastResult<Result>::type> ExplicitCast(const Source& value)
{
    return typename CastResult<Result>::type(nullptr);
}

/// Casts the source type to the result type using explicit cast.
/// Used for casting between arrays.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
/// @throw System::InvalidCastException If no cast available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Array, typename CastResult<Result>::type> ExplicitCast(const Source& value)
{
    if (!value)
        return nullptr;

    auto result = MakeArray<typename Result::ValueType>(value->data().size());
    std::transform(value->data().begin(), value->data().end(), result->data().begin(),
                   [](const auto& value) {return ExplicitCast<typename Result::ValueType>(value);});

    return result;
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used when simple constructor-like cast is needed.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Static, Result> AsCast(const Source& value)
{
    return Result(value);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used when the source and the result types are the same.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::None, Result> AsCast(const Source& value)
{
    return value;
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for exception wrappers.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result. Returns nullptr if no conversion available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Exception, Result> AsCast(const Source& value)
{
    return value.Get().template Cast<typename Result::ExceptionType, std::false_type>() ? Result(value.Get())
                                                                                        : Result(nullptr);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for casting object to exception.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result. Returns nullptr if no conversion available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::ObjectToException, Result> AsCast(const Source& value)
{
    auto exception_ptr = value.template Cast<typename Result::ExceptionType, std::false_type>();
    return exception_ptr ? Result(exception_ptr.template Cast<System::Details_Exception, std::false_type>())
                         : Result(nullptr);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used when the source and result both are smart pointers.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result. Returns nullptr if no conversion available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Pointer, typename CastResult<Result>::type>
    AsCast(const Source& value)
{
    return value.template Cast<Result, std::false_type>();
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used when the source and result both are smart pointers (with expicit SmartPtr<...> in result type).
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result. Returns nullptr if no conversion available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::PointerToPointer, Result>
    AsCast(const Source& value)
{
    return AsCast<typename Result::Pointee_>(value);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for unboxing object to nullable.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.  Returns empty nullable if no conversion available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::UnboxingToNullable, Result>
    AsCast(const Source& value)
{
    return ObjectExt::UnboxToNullable<typename Result::ValueType>(value, true);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Invalid unboxing to non-object type.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns Always returns null.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::InterfaceUnboxingToNullable, Result> AsCast(const Source& value)
{
    Result result;
    if (ObjectExt::Is<typename Result::ValueType>(value))
    {
        result = *(value.template Cast<typename Result::ValueType, std::false_type>());
    }
    return result;
}

/// Invalid unboxing to non-object type.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns Always returns null.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::InvalidUnboxing, Result> AsCast(const Source& value)
{
    return Default<Result>();
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for boxing nullable object.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::NullableBoxing, Result> AsCast(const Source& value)
{
    return Result(value);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for boxing common object.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::InterfaceBoxing, typename CastResult<Result>::type>
    AsCast(const Source& value)
{
    if (!ObjectExt::Is<Result>(value))
    {
        return nullptr;
    }

    return MakeObject<Source>(value).template Cast<Result, std::false_type>();
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for boxing common object.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Boxing, typename CastResult<Result>::type>
    AsCast(const Source& value)
{
    return ObjectExt::Box(value).template Cast<typename Result::Pointee_, std::false_type>();
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for string unboxing.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::UnboxingToString, Result> AsCast(const Source& value)
{
    return ObjectExt::UnboxStringSafe(value);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used for nullptr casing.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Null, typename CastResult<Result>::type> AsCast(const Source& value)
{
    return typename CastResult<Result>::type(nullptr);
}

/// Casts the source type to the result type using 'as' operator cast.
/// Used to cast between arrays.
/// @tparam Source The source type.
/// @tparam Result The result type.
/// @param value Object to cast.
/// @returns The cast result. Returns nullptr if no conversion for any array member is available.
template <typename Result, typename Source>
std::enable_if_t<Details::CastType<Source, Result>::Array, typename CastResult<Result>::type> AsCast(const Source& value)
{
    if (!value)
        return nullptr;

    auto result = MakeArray<typename Result::ValueType>(value->data().size());
    auto d_it = result->data().begin();
    auto s_it = value->data().begin();
    while (s_it != value->data().end())
    {
        auto& source_element = *(s_it++);
        auto& result_element = *(d_it++);

        result_element = AsCast<typename Result::ValueType>(source_element);

        // Fail entire cast if any element fails
        if (source_element != nullptr && result_element == nullptr)
            return nullptr;
    }

    return result;
}

/// Implementation of '?.' operator translation
/// @tparam T0 expression type.
/// @tparam T1 Type of lambda encapsulating 'WhenTrue' expression.
/// @param expr expression value.
/// @param func 'WhenTrue' expression bound to functor.
/// @return If expr value is not null, returns func called with its value as first argument, otherwise returns null.
template <typename T0, typename T1>
static auto SafeInvoke(T0&& expr, T1&& func)
{
    // The type which 'func' actually returns
    using retval_t = decltype(func(expr));

    // The type which function SafeInvoke will return. Non-nullable types will be wrapped by 'Nullable<>' class template.
    using result_t = typename std::conditional<
        std::is_base_of<Details::BoxableObjectBase, retval_t>::value || std::is_arithmetic<retval_t>::value || std::is_enum<retval_t>::value,
        System::Nullable<retval_t>,
        retval_t>::type;

    return expr != nullptr ? result_t(func(expr)) : result_t(nullptr);
}

} // namespace System
