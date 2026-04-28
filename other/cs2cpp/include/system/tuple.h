#pragma once
#include <tuple>
#include <system/object.h>
#include <system/object_ext.h>
#include <system/runtime/compiler_services/ituple.h>

namespace System {

template<typename ...Args>
class Tuple;

namespace Details {

/// Checks that a type is wrapped in Tuple and SharedPtr classes.
/// @tparam T The type to check.
template <typename T>
struct IsTuple { static constexpr bool value = false; };

/// Specialization for the wrapped type.
/// @tparam T The type to check.
template <typename T>
struct IsTuple<SharedPtr<Tuple<T>>> { static constexpr bool value = true; };

/// The maximum possible index for accessing an item of a Tuple.
static constexpr int32_t MaxTupleIndex = 7;

/// Specialization to check that the 8-th item is a Tuple.
/// @tparam Index The index of the current processed item.
/// @tparam Args types of a tuple elements.
template<std::size_t Index = 0, typename... Args>
typename std::enable_if<Index == MaxTupleIndex, void>::type
    CheckRest()
{
    if(!IsTuple<typename std::tuple_element<Index, std::tuple<Args...>>::type>::value)
    {
        throw ArgumentException(u"The last element of an 8-tuple must be of type Tuple");
    }
}

/// Specialization to break the recursion and check size of a Tuple.
template<std::size_t Index = 0, typename... Args>
typename std::enable_if<Index != MaxTupleIndex, void>::type
    CheckRest()
{
    static_assert(Index <= MaxTupleIndex, "The Tuple class can store only 8 items");
}

/// Service structure to hold return value for index access.
struct ReturnValueHolder
{
    /// Saves the value
    /// Specialization for value types for converting to Object
    /// @tparam T The type of the stored value.
    template<typename T>
    typename std::enable_if<!IsSmartPtr<T>::value, void>::type Hold(T& returnValue)
    {
        value = ObjectExt::Box(returnValue);
    }

    /// Saves the value
    /// Specialization for Object types
    /// @tparam T The type of the stored value.
    /// @param returnValue 
    template<typename T>
    typename std::enable_if<IsSmartPtr<T>::value, void>::type Hold(T& returnValue)
    {
        value = returnValue;
    }

    /// The stored value.
    SharedPtr<Object> value;
};

/// Specialization to break the recursion.
template<std::size_t I = 0, typename RetHolder, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
/// @cond
    FindItem(int, const std::tuple<Tp...>& , RetHolder&)
/// @endcond
{ }

/// Specialization to find the required index in a tuple.
/// @tparam Index The index of the current processed item.
/// @tparam RetHolder The type of a return value.
/// @tparam Args types of a tuple elements.
template<std::size_t Index = 0, typename RetHolder, typename... Args>
typename std::enable_if< Index < sizeof...(Args), void>::type
    FindItem(int index, const std::tuple<Args...>& tuple, RetHolder& holder)
{
    if (index == 0)
    {
        holder.Hold(std::get<Index>(tuple));
    }
    else
    {
        FindItem<Index + 1, RetHolder, Args...>(index - 1, tuple, holder);
    }
}

} // namespace Details

/// Class that represents a tuple data structure.
/// Maximum number of items is 8.
/// @code
/// #include "system/smart_ptr.h"
/// #include "system/tuple.h"
/// #include <iostream>
///
/// int main()
/// {
///   const auto tuple = System::MakeObject<System::Tuple<int, int, int>>(32, 16, 128);
///
///   std::cout <<
///     "Item 1: " << tuple->get_Item<0>() << std::endl <<
///     "Item 2: " << tuple->get_Item<1>() << std::endl <<
///     "Item 3: " << tuple->get_Item<2>() << std::endl;
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Item 1: 32
/// Item 2: 16
/// Item 3: 128
/// */
/// @endcode
/// @tparam Args The tuple elements types.
template<typename ... Args>
class Tuple : public Runtime::CompilerServices::ITuple
{
private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Tuple<Args...>, System::BaseTypesInfo<Runtime::CompilerServices::ITuple>);

    /// An alias for the type used to store the tuple's elements.
    using tuple_t = std::tuple<Args...>;

public:
    /// Constructs a tuple object
    /// @param args The arguments that are passed to the constructor of the Tuple object being constructed
    Tuple(Args... args)
        : m_tuple(std::forward<Args>(args)...)
    {
        Details::CheckRest<std::tuple_size<tuple_t>::value - 1, Args...>();
    }

    /// Gets the value of the Tuple object's component.
    /// @tparam Index The number of item the class should return.
    template<int32_t Index>
    typename std::tuple_element<Index, tuple_t>::type get_Item() const
    {
        return std::get<Index>(m_tuple);
    }
    
    /// Determines if the current and the specified objects are identical.
    /// @param obj An object to compare the current object with
    /// @returns True if the current and the specified objects are identical, otherwise - false
    bool Equals(SharedPtr<Object> obj) override
    {
        if (obj.get() == this)
        {
            return true;
        }

        auto tuple = System::AsCast<Tuple<Args...>>(obj);
        if (tuple == nullptr)
        {
            return false;
        }
        
        return Equals<0, Args...>(m_tuple, tuple->m_tuple);
    }

protected: // System::Runtime::CompilerServices::ITuple
    
    /// Returns the element at position index
    /// @param index of the specified Tuple element.
    /// @returns The element at position index the Tuple
    SharedPtr<Object> idx_get(int index) const override
    {
        if (index >= get_Length())
        {
            throw IndexOutOfRangeException(u"Tuple");
        }

        Details::ReturnValueHolder return_value_holder;
        Details::FindItem(index, m_tuple, return_value_holder);
        
        return return_value_holder.value;
    }

    /// Returns the number of positions in this data structure.
    int32_t get_Length() const override
    {
        return static_cast<int32_t>(std::tuple_size<tuple_t>{});
    }

private:
    /// Specialization to break the recursion.
    template<std::size_t Index = 0, typename... Types>
    static typename std::enable_if<Index == sizeof...(Types), bool>::type
        Equals(const std::tuple<Types...>& a, const std::tuple<Types...>& b)
    {
        return true;
    }

    /// Service function to compare two Tuple objects.
    /// @tparam Index The index of the current processed item.
    /// @tparam Types The Types of a tuple elements.
    template<std::size_t Index = 0, typename... Types>
    static typename std::enable_if<Index < sizeof...(Types), bool>::type
        Equals(const std::tuple<Types...>& a, const std::tuple<Types...>& b)
    {
        if (!ObjectExt::Equals(std::get<Index>(a), std::get<Index>(b)))
        {
            return false;
        }

        return Equals<Index + 1, Types...>(a, b);
    }

private:
    /// The storage for tuple's elements.
    tuple_t m_tuple;
};

/// Provides static methods for creating tuple objects.
/// @code
/// #include "system/smart_ptr.h"
/// #include "system/tuple.h"
/// #include <iostream>
///
/// int main()
/// {
///   const auto tuple = System::TupleFactory::Create(256, 16, 64);
///
///   std::cout <<
///     "Item 1: " << tuple->get_Item<0>() << std::endl <<
///     "Item 2: " << tuple->get_Item<1>() << std::endl <<
///     "Item 3: " << tuple->get_Item<2>() << std::endl;
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// Item 1: 256
/// Item 2: 16
/// Item 3: 64
/// */
/// @endcode
class TupleFactory
{
public:
    /// Creates a new tuple object.
    template<typename ... Args>
    static SharedPtr<Tuple<Args...>> Create(Args... args)
    {
        return MakeObject<Tuple<Args...>>(std::forward<Args>(args)...);
    }

    /// Creates a new 8-tuple. The 8th element is stored inside Tuple.
    template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename TRest>
    static SharedPtr<Tuple<T1, T2, T3, T4, T5, T6, T7, SharedPtr<Tuple<TRest>>>> Create(T1 item1, T2 item2, T3 item3, T4 item4, T5 item5, T6 item6, T7 item7, TRest rest)
    {
        return MakeObject<Tuple<T1, T2, T3, T4, T5, T6, T7, SharedPtr<Tuple<TRest>>>>(item1, item2, item3, item4, item5, item6, item7, MakeObject<Tuple<TRest>>(rest));
    }
};

} // namespace System
