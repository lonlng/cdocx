/// @file system/special_casts.h
/// Contains the declarations of functions that perform type casting of elements of collections and arrays.
#ifndef _aspose_system_casts_h_
#define _aspose_system_casts_h_

#include <system/collections/ienumerable.h>
#include <system/collections/list.h>
#include <system/object_ext.h>
#include <system/shared_ptr.h>
#include <system/weak_ptr.h>
#include <system/array.h>

namespace System {

/// Performs the explicit casting of elements of the specified enumerable object to different type.
/// @param enumerable Enumerable object containing the elements to cast
/// @returns A pointer to a new collection containing elements of type @p To equivalent to the elements of @p enumerable
/// @tparam To The type to statically cast the elements of the enumerable object to
/// @tparam From The type of enumerable object
template<class To, class From>
typename std::enable_if<!System::detail::has_method_get_Count<From>::value,
Collections::Generic::ListPtr<To>>::type CastEnumerableTo(const From& enumerable)
{
    auto result = MakeObject<Collections::Generic::List<To>>();

    auto enumerator = enumerable->GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto& item = ExplicitCast<To>(enumerator->get_Current());
        result->Add(item);
    }

    return result;
}

/// Performs the explicit casting of elements of the specified enumerable object to different type.
/// @param enumerable is inheritor of Enumerable object with defined get_Count method and containing the elements to cast
/// @returns A pointer to a new collection containing elements of type @p To equivalent to the elements of @p enumerable
/// @tparam To The type to statically cast the elements of the enumerable object to
/// @tparam From The type of enumerable object
template<class To, class From>
typename std::enable_if<System::detail::has_method_get_Count<From>::value,
Collections::Generic::ListPtr<To>>::type CastEnumerableTo(const From& enumerable)
{
    auto result = MakeObject<Collections::Generic::List<To>>(enumerable->get_Count());

    auto enumerator = enumerable->GetEnumerator();
    while (enumerator->MoveNext())
    {
        const auto& item = ExplicitCast<To>(enumerator->get_Current());
        result->Add(item);
    }

    return result;
}


/// Performs casting of elements of the specified array to different type.
/// Override for cases then From is SmartPtr obj
/// @param from Shared pointer to the array containing the elements to cast
/// @returns A pointer to a new array containing elements of type @p To equivalent to the elements of @p from
/// @tparam To The type to cast the elements of the specified array to
/// @tparam From The type of elements of the elements of the arry elements of which to cast
/// @deprecated Added for backward compatibility. Use ExplicitCast instead.
template<typename To, typename From>
std::enable_if_t<System::IsSmartPtr<From>::value, System::SharedPtr<System::Array<To>>>
StaticCastArray(const System::SharedPtr<System::Array<From>>& from)
{
    return ExplicitCast<System::ArrayPtr<To>>(from);
}

/// Performs casting of elements of the specified array to different type.
/// Override for cases then From is Boxable and To is Object[]
/// @param from Shared pointer to the array containing the elements to cast
/// @returns A pointer to a new array containing elements of type @p To equivalent to the elements of @p from
/// @tparam To The type to cast the elements of the specified array to
/// @tparam From The type of elements of the elements of the arry elements of which to cast
/// @deprecated Added for backward compatibility. Use ExplicitCast instead.
template<typename To, typename From>
std::enable_if_t<!System::IsSmartPtr<From>::value && System::IsBoxable<From>::value && std::is_same<To, System::SharedPtr<Object>>::value, System::SharedPtr<System::Array<To>>>
StaticCastArray(const System::SharedPtr<System::Array<From>>& from)
{
    return ExplicitCast<System::ArrayPtr<To>>(from);
}

/// Performs casting of elements of the specified array to different type.
/// @param from Shared pointer to the array containing the elements to cast
/// @returns A pointer to a new array containing elements of type @p To equivalent to the elements of @p from
/// @tparam To The type to cast the elements of the specified array to
/// @tparam From The type of elements of the elements of the arry elements of which to cast
/// @deprecated Added for backward compatibility. Use ExplicitCast instead.
template<class To, class From>
SharedPtr<Array<To>> DynamicCastArray(const SharedPtr<Array<From>>& from)
{
    return ExplicitCast<System::ArrayPtr<To>>(from);
}

} // namespace System

#endif // _aspose_system_casts_h_
