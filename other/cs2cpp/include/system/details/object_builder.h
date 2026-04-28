/// @file system/details/object_builder.h
/// @brief Object builder pattern implementation for fluent interface object construction
#pragma once

#include <system/details/is_template_base_of.h>
#include <system/details/dereference.h>
#include <system/collections/keyvalue_pair.h>
#include <system/object_ext.h>

namespace System {

namespace Collections { namespace Generic {
template<typename, typename>
class IDictionary;
template <typename>
class ICollection;
template<typename T>
class List;
}}

namespace Details {

/// @brief Tag type used to distinguish ObjectBuilder constructors
/// @details Empty struct used for constructor overloading resolution
struct ObjectBuildingTag {};

/// @brief Simplest verctor storage with move semantics to get data
template <typename T>
class ArrayStorage : private std::vector<T>
{
public:
    using ValueType = T;
    void Add(const T& element) {push_back(element);}
    std::vector<T>&& Get() {return std::move(*this);}
};

/// @brief Fluent interface builder for complex object construction
/// @tparam T Type of the object being built (interface type)
/// @tparam M Type of the member object being constructed (can be SharedPtr<T> or any other holder, defaults to T)
/// @details Provides chainable methods for building objects with collections,
/// property settings, and method calls in a single expression
template <typename T, typename M = T>
class ObjectBuilder
{
    /// @brief Metafunction to detect if a type is a System::Collections::Generic::List
    /// @tparam X Type to check
    template <typename X>
    struct IsList : std::false_type {};
    /// @brief Specialization for List types
    /// @tparam E Element type of the list
    template <typename E>
    struct IsList<System::Collections::Generic::List<E>> : std::true_type {};

    /// @brief Metafunction to detect if a type is a ArrayStorage for array initalization
    /// @tparam X Type to check
    template <typename X>
    struct IsArray : std::false_type {};
    /// @brief Specialization for array types
    /// @tparam E Element type of the array
    template <typename E>
    struct IsArray<ArrayStorage<E>> : std::true_type {};

public:
    /// @brief Default constructor is deleted
    ObjectBuilder() = delete;
    /// @brief Copy constructor is deleted
    ObjectBuilder(const ObjectBuilder&) = delete;
    /// @brief Move constructor
    /// @param other Other ObjectBuilder to move from
    ObjectBuilder(ObjectBuilder&& other) : m_member(std::move(other.m_member)), m_reference(Dereference(m_member))
    {}
    /// @brief Constructor with forwarding arguments to construct member
    /// @param tag ObjectBuildingTag for constructor disambiguation
    /// @param args Arguments to forward to member construction
    template <typename... Args>
    ObjectBuilder(ObjectBuildingTag, Args&&... args)
        : m_member(std::forward<Args>(args)...), m_reference(Dereference(m_member))
    {}

    /// @brief Add one element to the built object (generic version)
    /// @tparam Args Types of arguments to add
    /// @param args Arguments to add to the object
    /// @return Reference to this builder for method chaining
    template <typename... Args>
    ObjectBuilder& Add(Args&&... args)
    {
        m_reference.Add(std::forward<Args>(args)...);
        return *this;
    }

    /// @brief Add number of elements from initializer list (non-List specialization)
    /// @tparam X Type parameter for SFINAE (defaults to T)
    /// @param args Initializer list of values to add
    /// @return Reference to this builder for method chaining
    /// @note Enabled only when X is not a List type
    template <typename X = T>
    typename std::enable_if<!IsList<X>::value, ObjectBuilder&>::type Add(std::initializer_list<typename X::ValueType> args)
    {
        for (auto&& arg : args)
        {
            AddElement(arg);
        }
        return *this;
    }

    /// @brief Add elements from initializer list (List specialization)
    /// @tparam X Type parameter for SFINAE (defaults to T)
    /// @param args Initializer list of values to add
    /// @return Reference to this builder for method chaining
    /// @note Enabled only when X is a List type
    /// @details List class has more optimal method AddInitializer to work with number of elements to add
    template <typename X = T>
    typename std::enable_if<IsList<X>::value, ObjectBuilder&>::type Add(std::initializer_list<typename X::ValueType> args)
    {
        m_reference.AddInitializer((int)args.size(), args.begin());
        return *this;
    }


    /// @brief Add elements from enumberable objects
    /// @tparam X Type of enumerable
    /// @param enumerable Enumerable object to add values from
    /// @return Reference to this builder for method chaining
    /// @note Valid only when X is has GetEnumerator() method
    template <typename X>
    ObjectBuilder& AddSpread(const X& enumerable)
    {
        auto enumerator = Dereference(enumerable).GetEnumerator();
        while (Dereference(enumerator).MoveNext())
        {
            m_reference.Add(ExplicitCast<typename T::ValueType>(Dereference(enumerator).get_Current()));
        }
        return *this;
    }

    /// @brief Set key-value pairs from initializer list
    /// @tparam X Type parameter for SFINAE (defaults to T)
    /// @param args Initializer list of key-value pairs
    /// @return Reference to this builder for method chaining
    template <typename X = T>
    ObjectBuilder& Set(std::initializer_list<typename X::KeyValuePairType> args)
    {
        auto& data = m_reference.data();
        for (auto&& arg : args)
        {
            data[arg.get_Key()] = arg.get_Value();
        }
        return *this;
    }

    /// @brief Call member function on the built object
    /// @tparam Ret Return type of the member function
    /// @tparam Args Argument types of the member function
    /// @param fnc Pointer to member function to call
    /// @param args Arguments to pass to the member function
    /// @return Reference to this builder for method chaining
    template <typename Ret, typename... Args>
    ObjectBuilder& operator()(Ret (T::*fnc)(Args...), Args... args)
    {
        (m_reference.*fnc)(args...);
        return *this;
    }

    /// @brief Apply a functor to the built object
    /// @tparam F Functor type
    /// @param functor Functor to apply to the object
    /// @return Reference to this builder for method chaining
    template <typename F>
    ObjectBuilder& operator()(F functor)
    {
        functor(m_reference);
        return *this;
    }

    /// @brief Retrieve the built object for common case
    /// @return R-value reference to the built object
    /// @note This should be the final call in the builder chain
    template <typename X = T>
    typename std::enable_if<!IsArray<X>::value, M&&>::type Get()
    {
        return std::move(m_member);
    }

    /// @brief Retrieve the built object for arrays
    /// @return Smart pointer to built array
    /// @note This should be the final call in the builder chain
    template <typename X = T>
    typename std::enable_if<IsArray<X>::value, ArrayPtr<typename M::ValueType>>::type Get()
    {
        return MakeArray<typename M::ValueType>(m_member.Get());
    }

private:
    /// @brief Add a key-value pair element
    /// @tparam K Key type
    /// @tparam V Value type
    /// @param element Key-value pair to add
    template<typename K, typename V>
    void AddElement(const Collections::Generic::KeyValuePair<K, V>& element)
    {
        m_reference.Add(element.get_Key(), element.get_Value());
    }

    /// @brief Add a single element (generic version)
    /// @tparam T Element type
    /// @param element Element to add
    template<typename E>
    void AddElement(E&& element)
    {
        m_reference.Add(element);
    }

    M   m_member;       ///< The object being built
    T&  m_reference;    ///< Reference to the object for method calls
};

} // namespace Details

/// @brief Build an object with shared ownership
/// @tparam T Type of object to build
/// @tparam Args Argument types for object construction
/// @param args Arguments to forward to object constructor
/// @return ObjectBuilder configured for shared pointer construction
/// @details Creates a SharedPtr<T> and returns a builder for it
/// @note Object construction must be finished with Get() call
template <typename T, typename... Args>
Details::ObjectBuilder<T, SharedPtr<T>> BuildObject(Args&&... args)
{
    return {Details::ObjectBuildingTag(), MakeObject<T>(std::forward<Args>(args)...)};
}

/// @brief Starts initialization of an object with shared ownership
/// @tparam T Type of object to initialize
/// @param object Object to initialize
/// @return ObjectBuilder configured for shared pointer construction
/// @note Object initialization must be finished with Get() call
template <typename T>
Details::ObjectBuilder<T, SharedPtr<T>> InitObject(const SharedPtr<T>& object)
{
    return {Details::ObjectBuildingTag(), object};
}

/// @brief Build an array
/// @tparam T Element type of array to build
/// @return ObjectBuilder configured for array construction
/// @details Creates a ArrayPtr<T> and returns a builder for it
/// @note Object construction must be finished with Get() call
template <typename T>
Details::ObjectBuilder<Details::ArrayStorage<T>> BuildArray()
{
    return {Details::ObjectBuildingTag()};
}

/// @brief Build an object with direct ownership
/// @tparam T Type of object to build
/// @tparam Args Argument types for object construction
/// @param args Arguments to forward to object constructor
/// @return ObjectBuilder configured for direct object construction
/// @note Object construction must be finished with Get() call
template <typename T, typename... Args>
Details::ObjectBuilder<T> Build(Args&&... args)
{
    return {Details::ObjectBuildingTag(), std::forward<Args>(args)...};
}

} // namespace System
