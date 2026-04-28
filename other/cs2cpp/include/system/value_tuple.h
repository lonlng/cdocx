#pragma once
#include <tuple>
#include <system/object_ext.h>
#include <system/tuple.h>
#include <system/details/apply.h>
#include <system/runtime/compiler_services/ituple.h>

namespace System {

/// Represents a pointer to TypeInfo object that contains information about ValueTuple class.
struct ValueTupleTypeInfo : TypeInfoPtr
{
    /// Constructs an instance of MulticastDelegateTypeInfo class.
    ValueTupleTypeInfo()
        : TypeInfoPtr(u"System::ValueTuple")
    {}
};

/// Class that represents a ValueTuple data structure.
template<typename ... Args>
class ValueTuple : public Details::BoxableObjectBase
{
    /// An alias for the type used to store the tuple's elements.
    using tuple_t = std::tuple<Args...>;
    /// Quantity of elements in tuple
    static constexpr std::size_t tuple_size = sizeof...(Args);

private:
    template <typename... OtherArgs> friend class ValueTuple;
    friend class BoxedValue<ValueTuple<Args...>>;
    typedef ValueTupleTypeInfo ThisTypeInfo;

public:
    ValueTuple()
    {
    }

    /// Constructs a tuple object
    /// @param args The arguments that are passed to the constructor of the ValueTuple object being constructed
    template <typename = std::enable_if_t<(tuple_size > 0)>>
    ValueTuple(Args... args) : m_tuple(std::forward<Args>(args)...)
    {
    }

    /// Returns a reference to the TypeInfo object representing the ValueTuple class type information.
    static const TypeInfo& Type()
    {
        return *static_holder<ThisTypeInfo>();
    }

    /// Gets the reference to value of the ValueTuple object's component.
    /// @tparam Index The number of item the class should return.
    template <std::size_t Index>
    std::tuple_element_t<Index, tuple_t>& Item()
    {
        static_assert(Index < tuple_size, "Index out of ragnge.");

        return std::get<Index>(m_tuple);
    }

    /// Gets the value of the ValueTuple object's component.
    /// @tparam Index The number of item the class should return.
    template <std::size_t Index>
    const std::tuple_element_t<Index, tuple_t>& Item() const
    {
        static_assert(Index < tuple_size, "Index out of ragnge.");

        return std::get<Index>(m_tuple);
    }

    /// Determines if the current and the specified objects are identical.
    /// @param obj An object to compare the current object with
    /// @returns True if the current and the specified objects are identical, otherwise - false
    bool Equals(SharedPtr<Object> obj)
    {
        return System::ObjectExt::Is<ValueTuple>(obj) && Equals<0, Args...>(m_tuple, ObjectExt::Unbox<ValueTuple>(obj).m_tuple);
    }

    bool Equals(const ValueTuple& other)
    {
        return *this == other;
    }

    System::String ToString() const
    {
        System::String result = u"(";
        ToString(m_tuple, result);
        result += u")";
        return result;
    }

    int32_t GetHashCode() const
    {
        int32_t result = 0;
        GetHashCode(m_tuple, result);
        return result;
    }

    const TypeInfo& GetType() const
    {
        return Type();
    }

    bool operator == (const ValueTuple& other) const
    {
        return Equals<0, Args...>(m_tuple, other.m_tuple);
    }

    template<typename ... OtherArgs>
    ValueTuple& operator = (const ValueTuple<OtherArgs...>& otherTuple)
    {
        m_tuple = otherTuple.m_tuple;
        return *this;
    }

    /// Deconstructs object to this value tuple.
    /// @param deconstructiblePtr An object to deconstruct
    template <typename T>
    ValueTuple& operator = (const SharedPtr<T>& deconstructiblePtr)
    {
        System::Details::apply([&](auto&... args) { deconstructiblePtr->Deconstruct(args...); }, m_tuple);
        return *this;
    }

    tuple_t& tuple() {return m_tuple;}
    const tuple_t& tuple() const {return m_tuple;}

private:
    /// Specialization to break the recursion.
    template<std::size_t Index = 0, typename... Types>
    static typename std::enable_if<Index == sizeof...(Types), bool>::type
        Equals(const std::tuple<Types...>& a, const std::tuple<Types...>& b)
    {
        return true;
    }

    /// Service function to compare two ValueTuple objects.
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

    /// Service function to get tuple string representation.
    template<std::size_t Index = 0>
    static typename std::enable_if<Index == tuple_size, void>::type ToString(const tuple_t& tuple, System::String& result) {}
    template<std::size_t Index = 0>
    static typename std::enable_if<Index < tuple_size, void>::type ToString(const tuple_t& tuple, System::String& result)
    {
        if (Index > 0)
        {
            result += u", ";
        }
        result += ObjectExt::ToString(std::get<Index>(tuple));
        ToString<Index + 1>(tuple, result);
    }

    /// Service function to get tuple hash code.
    template<std::size_t Index = 0>
    static typename std::enable_if<Index == tuple_size, void>::type GetHashCode(const tuple_t& tuple, int32_t& result) {}
    template<std::size_t Index = 0>
    static typename std::enable_if<Index < tuple_size, void>::type GetHashCode(const tuple_t& tuple, int32_t& result)
    {
        result ^= (ObjectExt::GetHashCode(std::get<Index>(tuple)) << (Index * 2));
        GetHashCode<Index + 1>(tuple, result);
    }

private:
    /// The storage for tuple's elements.
    tuple_t m_tuple;
};

/// Boxed version of value tuple.
/// @tparam name Args tuple element types.
template <typename... Args>
class BoxedValue<ValueTuple<Args...>> : public Runtime::CompilerServices::ITuple
{
    using ValueT = ValueTuple<Args...>;

    typedef System::BoxedValue<ValueTuple<Args...>> thisType;
    typedef System::BaseTypesInfo<System::Object, Runtime::CompilerServices::ITuple> baseTypes;

    typedef TypeInfo::BoxedValue<ValueT> ThisTypeInfo;

    RTTI_INFO_BOXED_CUSTOM(thisType, baseTypes);

public:
    /// Constructs a BoxedValue object that represents the specified value boxed.
    /// @param value A tuple to be boxed
    BoxedValue(const ValueT& value) : m_type_hash(typeid(ValueT).hash_code()), m_value(value)
    {}

    /// @brief Gets actual type of object.
    /// @return TypeInfo object which describes final type.
    const System::TypeInfo& GetType() const override
    {
        return System::ObjectType::GetType<ValueT>();
    }

    /// Determines the equality of the boxed values represented by the current and specified objects.
    /// @param obj The object that represent the boxed value to be compared with the boxed value represented by the
    /// current object
    /// @returns True if the boxed value represented by the current object and @p obj are equal, otherwise - false
    bool Equals(ptr obj) override
    {
        if (!obj || !obj->Is(Type()))
            return false;

        auto boxed = obj.Cast<BoxedValue<ValueT>>();
        return m_value == boxed->m_value;
    }

    /// Returns a hash code for the current object.
    int GetHashCode() const override
    {
        return m_value.GetHashCode();
    }

    /// Returns the string representation of the boxed value.
    String ToString() const override
    {
        return m_value.ToString();
    }

    /// Unboxes the boxed value.
    /// @returns A constant reference to the boxed value represented by the current object.
    const ValueT& unbox() const
    {
        return m_value;
    }

    /// Determines if the type of the boxed value represented by the current object
    /// is @p V.
    /// @returns True if the type of the boxed value represented by the current object is @p V, otherwise - false
    /// @tparam V The type that is comared with the type of boxed value represented by the current object
    template <class V>
    bool is() const
    {
        return typeid(V).hash_code() == m_type_hash;
    }

protected:
    /// Returns the element at position index
    /// @param index of the specified Tuple element.
    /// @returns The element at position index the Tuple
    SharedPtr<Object> idx_get(int index) const override
    {
        if (index >= get_Length())
        {
            throw IndexOutOfRangeException(u"ValueTuple");
        }

        Details::ReturnValueHolder return_value_holder;
        Details::FindItem(index, m_value.m_tuple, return_value_holder);

        return return_value_holder.value;
    }

    /// Returns the number of elemens in this tuple
    int32_t get_Length() const override
    {
        return m_value.tuple_size;
    }

private:
    size_t m_type_hash;
    ValueT m_value;
};

/// @brief Creates tuple on stack.
/// @tparam Args Tuple member types.
/// @param args Tuple member values.
/// @return Newly created tuple.
template <typename... Args>
ValueTuple<Args...> MakeTuple(Args... args)
{
    return ValueTuple<Args...>(args...);
}

/// @brief Creates tuple bound to some values.
/// @tparam Args Tuple member types.
/// @param args Tuple values to bind.
/// @return Newly created tuple bound to given values.
template <typename... Args>
ValueTuple<Args...> TieTuple(Args&&... args)
{
    return ValueTuple<Args&&...>(std::forward<Args>(args)...);
}

/// @brief Gets N-th element of value tuple.
/// @tparam N element index.
/// @tparam Args tuple elements.
/// @param tuple tuple to get element from.
/// @return value of N-th tuple element.
template <std::size_t N, typename... Args>
auto Get(const ValueTuple<Args...>& tuple)
{
    return tuple.template Item<N>();
}

} // namespace System
