/// @file system/details/pointer_collection_helpers.h
#ifndef _aspose_system_detail_pointer_collection_helpers_h_
#define _aspose_system_detail_pointer_collection_helpers_h_


#include <system/shared_ptr.h>
#include <system/weak_ptr.h>
#include <system/exceptions.h>
#include "defines.h"

#include <array>
#include <memory>
#include <tuple>
#include <utility>
#include <type_traits>
#include <iostream>
#include <typeinfo>


namespace System { namespace Details { namespace CollectionHelpers {

/// Makes pointer weak.
/// Dummy implementation for non-pointer types to compile.
/// @tparam T Non-pointer type.
template <typename T>
void SetWeakPointer(const T&)
{}
/// Makes pointer weak.
/// @tparam T Pointee type.
/// @param p Pointer to set to weak mode.
template <typename T>
void SetWeakPointer(SmartPtr<T> &p)
{
    p.set_Mode(SmartPtrMode::Weak);
}
/// Makes pointer weak.
/// Casting implementation for specific cases where const_cast is required.
/// @tparam T Pointee type.
/// @param p Pointer to set to weak mode.
template <typename T>
void SetWeakPointer(const SmartPtr<T> &p)
{
    const_cast<SmartPtr<T>&>(p).set_Mode(SmartPtrMode::Weak);
}

/// Sets specific argument of template type to weak pointer mode.
/// Dummy implementation for non-pointer types to compile.
/// @tparam T Non-pointer type.
/// @param argument Template argument index to make weak pointer.
template <typename T>
void SetWeakPointer(uint32_t argument, const T&)
{
    ASPOSE_UNUSED(argument);
}
/// Sets specific argument of template type to weak pointer mode.
/// @tparam T Non-pointer type.
/// @param argument Template argument index to make weak pointer.
/// @param p Pointer to template type object to set argument to weak mode.
template <typename T>
void SetWeakPointer(uint32_t argument, SmartPtr<T> &p)
{
    p->SetTemplateWeakPtr(argument);
}
/// Sets specific argument of template type to weak pointer mode.
/// @param argument Template argument index to make weak pointer.
/// @param o Template type object to set argument to weak mode.
inline void SetWeakPointer(uint32_t argument, Object &o)
{
    o.SetTemplateWeakPtr(argument);
}

/// Sets specific argument of member template type object to weak pointer mode.
/// @tparam T Non-pointer type type.
/// @param argument Template argument index to make weak pointer.
/// @param o Template type object to set argument to weak mode.
template <typename T, typename = typename std::enable_if<!System::IsSmartPtr<T>::value>::type>
void SetMemberWeakPointer(uint32_t argument, T &o)
{
    o.SetTemplateWeakPtr(argument);
}
/// Sets specific argument of member template type object to weak pointer mode.
/// Dummy implementation to use for pointer members which obey different rules.
/// @tparam T Pointer type.
template <typename T, typename = typename std::enable_if<System::IsSmartPtr<T>::value>::type>
void SetMemberWeakPointer(uint32_t, const T&, int = 0)
{}


/// Holds mode for contained pointers.
/// This specialization applies to non-pointers which don't have any pointer mode by definition.
/// @tparam T Element type.
template <typename T, bool = IsSmartPtr<T>::value && !IsWeakPtr<T>::value>
class ContainerPointerMode
{
public:
    /// Use default allocator for non-pointer types.
    typedef std::allocator<T> allocator_type;
    /// Gets allocator to initialize container with.
    /// @return Newly created allocator object.
    inline allocator_type GetAllocator() const
    { 
        return allocator_type();
    }
    /// Sets container elements to weak pointers.
    /// This implementation is for non-pointers, so this call is wrong by definition and present for compilability reasons only.
    template <typename Container>
    void SetWeak(uint32_t, const Container&)
    {
        CODEPORTING_DEBUG_ASSERT(!"Applying weak pointer mode to container of non-pointers");
    }
};

/// Allocator to use with SmartPtr class.
/// Sets proper pointer mode when constructing SmartPtr object.
/// @tparam T Allocated type.
template <typename T>
class SmartPtrAllocator : public std::allocator<T>
{
public:
    /// Ensures using SmartPtrAllocator with different types.
    template <typename U> struct rebind
    {
        /// An alias for a SmartPtrAllocator for type argument of this template.
        using type = SmartPtrAllocator<U>;
    };

    /// Creates allocator referencing mode variable.
    /// @param mode Pointer to variable storing pointer mode associated with container.
    SmartPtrAllocator(const SmartPtrMode *mode)
        : m_mode(mode)
    {}
    /// Creates allocator constructing pointers of shared mode.
    SmartPtrAllocator()
        : m_mode(nullptr)
    {}
    /// Copy constructor.
    /// @tparam U Allocated type.
    /// @param allocator Allocator to copy mode variable pointer from.
    template <typename U>
    SmartPtrAllocator(const SmartPtrAllocator<U> &allocator)
        : m_mode(allocator.GetMode())
    {}
    
    /// Constructs unknown type.
    /// @tparam U Type to construct.
    /// @tparam Args Constructor argument types.
    /// @param p Pointer to object being constructed.
    /// @param args Constructor arguments.
    template <typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        std::allocator<T>::construct(p, std::forward<Args>(args)...);
    }
    /// Constructs smart pointer type.
    /// @tparam U Pointee type
    /// @tparam Args Constructor argument types.
    /// @param p Pointer to object being constructed.
    /// @param args Constructor arguments.
    template <typename U, typename ...Args>
    void construct(SmartPtr<U> *p, Args &&...args)
    {
        ::new ((void*)p) SmartPtr<U>(std::forward<Args&&>(args)..., m_mode ? *m_mode : SmartPtrMode::Shared);
    }
    /// Moves smart pointer type. Has to keep the mode as this may be due to reallocations inside same container.
    /// @tparam U Pointee type
    /// @param p Pointer to object being constructed.
    /// @param source Source pointer.
    template <typename U>
    void construct(SmartPtr<U> *p, SmartPtr<U> &&source)
    {
        ::new ((void*)p) SmartPtr<U>(std::forward<SmartPtr<U>>(source), source.get_Mode());
    }
    /// Constructs smart pointer type.
    /// @tparam U Pointee type
    /// @tparam Args Constructor argument types.
    /// @param p Pointer to object being constructed.
    /// @param args Constructor arguments.
    template <typename U, typename ...Args>
    void construct(SmartPtr<U> *p, const Args &...args)
    {
        ::new ((void*)p) SmartPtr<U>(std::forward<const Args&>(args)..., m_mode ? *m_mode : SmartPtrMode::Shared);
    }

    /// Gets pointer to mode variable.
    /// @return Pointer to variable holding container mode.
    const SmartPtrMode* GetMode() const
    {
        return m_mode;
    }

private:
    /// Mode variable pointer.
    const SmartPtrMode *m_mode;
};

/// Specialization for containers of pointers.
template <typename T>
class ContainerPointerMode<T, true>
{
public:
    /// Use SmartPtrAllocator to set proper mode when constructing pointers.
    using allocator_type = SmartPtrAllocator<T>;

    /// Creates allocator used to construct pointers with proper mode.
    /// @return Newly created allocator.
    inline allocator_type GetAllocator() const
    { 
        return allocator_type(&m_mode);
    }

    /// Converts stored pointers to weak.
    /// @tparam Container Container type.
    /// @param argument Container type template argument to treat as weak pointer.
    /// @param container Container to switch to weak pointer mode.
    template <typename Container>
    void SetWeak(uint32_t argument, Container &container)
    {
        ASPOSE_UNUSED(argument);
        CODEPORTING_DEBUG_ASSERT(argument == 0);

        if (m_mode == SmartPtrMode::Weak)
            return;

        m_mode = SmartPtrMode::Weak;
        for (auto &item : container)
            SetWeakPointer(item);
    }

private:
    /// Pointer mode to store.
    SmartPtrMode m_mode = SmartPtrMode::Shared;
};

/// Helper class to control pointer mode on map's keys or values separately.
/// Specialization for non-pointer elements.
/// @tparam T Key or value type.
template <typename T, bool = IsSmartPtr<T>::value && !IsWeakPtr<T>::value>
struct MapPointerHelper
{
    /// Helper class to store map keys or values pointers mode.
    class storage_type
    {
    public:
        /// Applies weak pointer mode to container of non-pointers.
        /// @tparam Container Container type.
        /// @tparam Element Element type.
        /// @tparam field Field to apply weak mode to.
        template <typename Container, typename Element, Element Container::value_type::*field>
        inline void SetWeak(const Container&)
        {
            CODEPORTING_DEBUG_ASSERT(!"Applying weak pointer mode to non-pointer");
        }
    };
    /// Helper class to prepare arguments for constructors invocations.
    typedef class StorageReference {
    public:
        /// Creates helper class responsible for preparing constructor arguments.
        inline StorageReference(const storage_type&) {}
        /// Packs arguments for constructor invocation.
        /// @tparam U Constructed type.
        /// @tparam Q Constructor arguments types.
        /// @param values Constructor arguments.
        /// @return Tuple of arguments to call constructor with.
        template <typename U, typename ...Q>
        inline std::tuple<const Q&...> Pack(const U*, const Q &...values) const
        {
            return std::tuple<const Q&...>(values...);
        }
        /// Packs arguments for constructor invocation.
        /// @tparam U Constructed type.
        /// @tparam Q Constructor arguments types.
        /// @param values Tuple of constructor arguments.
        /// @return Tuple of arguments to call constructor with.
        template <typename U, typename ...Q>
        inline std::tuple<Q...>&& Pack(const U*, std::tuple<Q...> &&values) const
        {
            return std::forward<std::tuple<Q...>>(values);
        }
        /// Sets mode of specified element.
        /// @tparam U Element type.
        template <typename U>
        inline void Set(const U&) const
        {}
    } storage_reference;
};
/// Specialization for smart pointers.
template <typename T>
struct MapPointerHelper<T, true>
{
    /// Helper class to store map keys or values pointers mode.
    class storage_type {
    public:
        /// Applies weak pointer mode to container of non-pointers.
        /// @tparam Container Container type.
        /// @tparam Element Element type.
        /// @tparam field Field to apply weak mode to.
        /// @param container Container to apply weak pointer mode to elements of.
        template <typename Container, typename Element, Element Container::value_type::*field>
        inline void SetWeak(Container &container)
        {
            if (m_mode == SmartPtrMode::Weak)
                return;

            m_mode = SmartPtrMode::Weak;
            for (auto &item : container)
                SetWeakPointer(item.*field);
        }
        /// Gets pointer to mode variable.
        /// @return Pointer to variable storing pointer mode to use with container.
        inline const SmartPtrMode* GetReference() const
        {
            return &m_mode;
        }
    private:
        SmartPtrMode m_mode = SmartPtrMode::Shared;
    };
    /// Helper class to prepare arguments for constructors invocations.
    typedef class StorageReference {
    public:
        /// Creates helper class responsible for preparing constructor arguments.
        /// @param storage Reference to pointer mode holder.
        inline StorageReference(const storage_type &storage) : m_mode(storage.GetReference()) {}

        /// Packs arguments for constructor invocation.
        /// @tparam U Constructed type.
        /// @tparam Q Constructor arguments types.
        /// @param values Constructor arguments.
        /// @return Tuple of arguments to call constructor with.
        template <typename U, typename ...Q>
        inline std::tuple<const Q&...> Pack(const U*, const Q &...values) const
        {
            return std::tuple<const Q&...>(values...);
        }
        /// Packs arguments for constructor invocation.
        /// @tparam U Constructed type.
        /// @tparam Q Constructor arguments types.
        /// @param values Constructor arguments tuple.
        /// @return Tuple of arguments to call constructor with.
        template <typename U, typename ...Q>
        inline std::tuple<Q...>&& Pack(const U*, std::tuple<Q...> &&values) const
        {
            return std::forward<std::tuple<Q...>>(values);
        }
        /// Packs arguments for constructor invocation.
        /// @tparam Q Constructor arguments types.
        /// @param values Constructor arguments.
        /// @return Tuple of arguments to call constructor with.
        template <typename ...Q>
        inline std::tuple<const Q&..., SmartPtrMode> Pack(const T*, const Q &...values) const
        {
            return std::tuple<const Q&..., SmartPtrMode>(values..., m_mode ? *m_mode : SmartPtrMode::Shared);
        }
        /// Packs arguments for constructor invocation.
        /// @tparam U Constructed type.
        /// @tparam Q Constructor arguments types.
        /// @param values Constructor arguments tuple.
        /// @return Tuple of arguments to call constructor with.
        template <typename ...Q>
        inline std::tuple<Q..., SmartPtrMode> Pack(const T*, std::tuple<Q...> &&values) const
        {
            return std::tuple_cat(std::forward<std::tuple<Q...>>(values), std::make_tuple(m_mode ? *m_mode : SmartPtrMode::Shared));
        }
        /// Sets mode of specified element.
        /// @tparam U Element type.
        template <typename U>
        inline void Set(const U&) const
        {}
        /// Sets mode of specified element.
        /// @param ptr Pointer to apply actual mode to.
        inline void Set(T &ptr) const
        {
            if (m_mode) ptr.set_Mode(*m_mode);
        }
        /// Sets mode of specified element.
        /// @param ptr Pointer to apply actual mode to.
        inline void Set(const T &ptr) const
        {
            if (m_mode) const_cast<T&>(ptr).set_Mode(*m_mode);
        }
    private:
        /// Pointer to variable storing actual pointer mode to use.
        const SmartPtrMode *const m_mode;
    } storage_reference;
};

/// Composite class storing independent pointer modes to use for map keys and map values and providing complex allocator initializing stored pointers as required.
/// Specialization for maps of non-pointer elements.
template <typename Key, typename Value, bool = (IsSmartPtr<Key>::value && !IsWeakPtr<Key>::value) || (IsSmartPtr<Value>::value && !IsWeakPtr<Value>::value)>
class MapPointerMode
{
public:
    /// Use default allocator.
    typedef std::allocator<std::pair<const Key, Value>> allocator_type;
    /// Gets allocator to use with map.
    /// @return Newly created allocator.
    inline allocator_type GetAllocator() const
    { 
        return allocator_type();
    }
    /// Makes stored map keys or values weak pointers.
    /// @tparam Container Container type.
    template <typename Container>
    void SetWeak(uint32_t, const Container&)
    {
        CODEPORTING_DEBUG_ASSERT(!"Applying weak pointer mode to container of non-pointers");
    }
};

/// Allocator to use with map-like data structures to control pointer modes of newly allocated keys and/or values.
/// @param T Allocated type.
/// @param Key Key type.
/// @param Value Value type.
template <typename T, typename Key, typename Value>
class SmartPtrPairAllocator : public std::allocator<T>
{
public:
    /// Use same allocator family with different types.
    template <typename U> struct rebind
    {
        /// An alias for a SmarPtrPairAllocator parameterized with @p U, @p Key and @p Value types.
        using type = SmartPtrPairAllocator<U, Key, Value>;
    };

    /// Creates allocator with controllable key and/or value pointer modes.
    /// @param key Reference to variable storing key pointer mode (if applicable).
    /// @param value Reference to variable storing value pointer mode (if applicable).
    SmartPtrPairAllocator(const typename MapPointerHelper<Key>::storage_reference &key, const typename MapPointerHelper<Value>::storage_reference &value)
        : m_key(key), m_value(value)
    {}
    /// Copy constructor.
    /// @tparam U Allocator type.
    /// @param other Allocator to get control variables pointers from.
    template <typename U>
    SmartPtrPairAllocator(const SmartPtrPairAllocator<U, Key, Value> &other)
        : m_key(other.GetKey()), m_value(other.GetValue())
    {}

    /// Constructs unknown type.
    /// @tparam U Type to construct.
    /// @tparam Args Constructor argument types.
    /// @param p Pointer to object being constructed.
    /// @param args Constructor arguments.
    template <typename U, typename ...Args>
    void construct(U *p, Args &&...args)
    {
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::forward<Args>(args)...);
    }
    /// Copy-constructs key-value pair.
    /// @tparam K Destination key type.
    /// @tparam V Destination value type.
    /// @tparam K2 Source key type.
    /// @tparam V2 Source value type.
    /// @param p Destination pair.
    /// @param value Source pair.
    template <typename K, typename V, typename K2, typename V2>
    void construct(std::pair<K, V> *p, const std::pair<K2, V2> &value)
    {
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::piecewise_construct,
                                                            m_key.Pack(&value.first, value.first),
                                                            m_value.Pack(&value.second, value.second));
    }
    /// Copy-constructs key-value pair.
    /// @tparam K Destination key type.
    /// @tparam V Destination value type.
    /// @tparam K2 Source key type.
    /// @tparam V2 Source value type.
    /// @param p Destination pair.
    /// @param value Source pair.
    template <typename K, typename V, typename K2, typename V2>
    void construct(std::pair<K, V> *p, std::pair<K2, V2> &value)
    {
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::piecewise_construct,
                                                            m_key.Pack(&value.first, value.first),
                                                            m_value.Pack(&value.second, value.second));
    }
    /// Copy-constructs key-value pair.
    /// @tparam K Destination key type.
    /// @tparam V Destination value type.
    /// @tparam K2 Source key type.
    /// @tparam V2 Source value type.
    /// @param p Destination pair.
    /// @param value Source pair.
    template <typename K, typename V, typename K2, typename V2>
    void construct(std::pair<K, V> *p, std::pair<K2, V2> &&value)
    {
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::piecewise_construct,
                                                            m_key.Pack(&value.first, value.first),
                                                            m_value.Pack(&value.second, value.second));
    }
    /// Constructs key-value pair.
    /// @tparam K Key type.
    /// @tparam V Value type.
    /// @param p Destination pair.
    /// @param key Key initializer.
    /// @param value Value initializer.
    template <typename K, typename V>
    void construct(std::pair<K, V> *p, K &&key, V &&value)
    {
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::piecewise_construct, m_key.Pack(&key, key),
                                                            m_value.Pack(&value, value));
    }
    /// Constructs key-value pair.
    /// @tparam K Key type.
    /// @tparam V Value type.
    /// @tparam Tuple1 Tuple of key constructor arguments.
    /// @tparam Tuple2 Tuple of value constructor arguments.
    /// @param p Destination pair.
    /// @param tuple1 Key constructor arguments.
    /// @param tuple2 Value constructor arguments.
    template <typename K, typename V, typename ...Tuple1, typename ...Tuple2>
    void construct(std::pair<K, V> *p, const decltype(std::piecewise_construct)&, const std::tuple<Tuple1...> &tuple1, const std::tuple<Tuple2...> &tuple2)
    {
        std::allocator_traits<std::allocator<T>>::construct(
            *this, p, std::piecewise_construct, m_key.Pack(&p->first, tuple1), m_value.Pack(&p->second, tuple2));
    }
    /// Constructs key-value pair.
    /// @tparam K Key type.
    /// @tparam V Value type.
    /// @tparam Tuple1 Tuple of key constructor arguments.
    /// @tparam Tuple2 Tuple of value constructor arguments.
    /// @param p Destination pair.
    /// @param tuple1 Key constructor arguments.
    /// @param tuple2 Value constructor arguments.
    template <typename K, typename V, typename ...Tuple1, typename ...Tuple2>
    void construct(std::pair<K, V> *p, const decltype(std::piecewise_construct)&, std::tuple<Tuple1...> &&tuple1, std::tuple<Tuple2...> &&tuple2)
    {
        std::allocator_traits<std::allocator<T>>::construct(
            *this, p, std::piecewise_construct, m_key.Pack(&p->first, std::forward<std::tuple<Tuple1...>>(tuple1)),
            m_value.Pack(&p->second, std::forward<std::tuple<Tuple2...>>(tuple2)));
    }
    /// Constructs key-value pair using unexpected set of construvtor arguments.
    /// Constructs pair first, then applies pointer types.
    /// @tparam K Key type.
    /// @tparam V Value type.
    /// @tparam Args Pair constructor arguments types.
    /// @param p Destination pair.
    /// @param args Pair constructor arguments.
    template <typename K, typename V, typename ...Args>
    void construct(std::pair<K, V> *p, Args &&...args)
    {
#ifdef _DEBUG
        std::cerr << "Using " << typeid(*this).name() << "::construct(std::pair<K,V>*, Args&&...) is not recommended. Define better overload if possible" << std::endl;
#endif
        std::allocator_traits<std::allocator<T>>::construct(*this, p, std::forward<Args>(args)...);
        m_key.Set(p->first);
        m_value.Set(p->second);
    }

    /// Gets reference to key pointer mode variable (if applicable).
    /// @return Object incapsulating pointer to key pointer mode (if applicable).
    const typename MapPointerHelper<Key>::storage_reference GetKey() const
    {
        return m_key;
    }
    /// Gets reference to value pointer mode variable (if applicable).
    /// @return Object incapsulating pointer to value pointer mode (if applicable).
    const typename MapPointerHelper<Value>::storage_reference GetValue() const
    {
        return m_value;
    }

private:
    /// Stores reference to key pointer mode variable (if applicable).
    typename MapPointerHelper<Key>::storage_reference m_key;
    /// Stores reference to value pointer mode variable (if applicable).
    typename MapPointerHelper<Value>::storage_reference m_value;
};

/// Composite class storing independent pointer modes to use for vector keys and vector values and providing complex allocator initializing stored pointers as required.
/// Specialization for maps of non-pointer elements.
template <typename Key, typename Value, bool = (IsSmartPtr<Key>::value && !IsWeakPtr<Key>::value) || (IsSmartPtr<Value>::value && !IsWeakPtr<Value>::value)>
class VectorPairPointerMode
{
public:
    /// Use default allocator.
    typedef std::allocator<std::pair<Key, Value>> allocator_type;
    /// Gets allocator to use with map.
    /// @return Newly created allocator.
    inline allocator_type GetAllocator() const
    {
        return allocator_type();
    }

    /// Makes stored map keys or values weak pointers.
    /// @tparam Container Container type.
    template <typename Container>
    void SetWeak(unsigned int, const Container&)
    {
        CODEPORTING_DEBUG_ASSERT(!"Applying weak pointer mode to container of non-pointers");
    }
};

/// Specialization for vector where either keys or values or both are smart pointers.
/// @tparam Key Key type.
/// @tparam Value Value type.
template <typename Key, typename Value>
class VectorPairPointerMode<Key, Value, true>
{
public:
    /// Use SmartPtrPairAllocator to set proper pointer modes to pairs being allocated.
    using allocator_type = SmartPtrPairAllocator<std::pair<Key, Value>, Key, Value>;
    /// Gets allocator to use on container.
    /// @return Newly created allocator.
    inline allocator_type GetAllocator() const
    {
        return allocator_type(m_key, m_value);
    }

    /// Applies weak pointer mode to map keys or values.
    /// @tparam Container Map type.
    /// @param argument 0 for keys, 1 for values.
    /// @param container Container to change pointer types for.
    template <typename Container>
    void SetWeak(unsigned int argument, Container &container)
    {
        switch (argument)
        {
        case 0:
            m_key.template SetWeak<Container, decltype(Container::value_type::first), &Container::value_type::first>(container);
            break;
        case 1:
            m_value.template SetWeak<Container, decltype(Container::value_type::second), &Container::value_type::second>(container);
            break;
        default:
            CODEPORTING_DEBUG_ASSERT(argument == 0 || argument == 1);
            break;
        }
    }

private:
    /// Stores key pointer type (if applicable).
    typename MapPointerHelper<Key>::storage_type m_key;
    /// Stores value pointer type (if applicable).
    typename MapPointerHelper<Value>::storage_type m_value;
};

/// Specialization for map where either keys or values or both are smart pointers.
/// @tparam Key Key type.
/// @tparam Value Value type.
template <typename Key, typename Value>
class MapPointerMode<Key, Value, true>
{
public:
    /// Use SmartPtrPairAllocator to set proper pointer modes to pairs being allocated.
    using allocator_type = SmartPtrPairAllocator<std::pair<const Key, Value>, Key, Value>;
    /// Gets allocator to use on container.
    /// @return Newly created allocator.
    inline allocator_type GetAllocator() const
    { 
        return allocator_type(m_key, m_value);
    }

    /// Applies weak pointer mode to map keys or values.
    /// @tparam Container Map type.
    /// @param argument 0 for keys, 1 for values.
    /// @param container Container to change pointer types for.
    template <typename Container>
    void SetWeak(uint32_t argument, Container &container)
    {
        switch (argument)
        {
        case 0:
            m_key.template SetWeak<Container, decltype(Container::value_type::first), &Container::value_type::first>(container);
            break;
        case 1:
            m_value.template SetWeak<Container, decltype(Container::value_type::second), &Container::value_type::second>(container);
            break;
        default:
            CODEPORTING_DEBUG_ASSERT(argument == 0 || argument == 1);
            break;
        }
    }

private:
    /// Stores key pointer type (if applicable).
    typename MapPointerHelper<Key>::storage_type m_key;
    /// Stores value pointer type (if applicable).
    typename MapPointerHelper<Value>::storage_type m_value;
};

} } } //System::Details::CollectionHelpers

/// Defines all members to make it possible controlling sequental container's pointer mode (weak or shared).
/// Does not define data type or 'm_data' member itself as they are too important to hide inside the macro.
/// @param element_type Type of element stored.
#define ASPOSE_COLLECTION_POINTER_MODE_CONTROL(element_type) \
public: \
    typedef System::Details::CollectionHelpers::ContainerPointerMode<element_type> pointer_mode_t; \
    void SetTemplateWeakPtr(uint32_t argument) override \
    { \
        static_assert(std::is_same<decltype(m_data.get_allocator()), typename pointer_mode_t::allocator_type>::value, "Container's allocator is not set to typename pointer_mode_t::allocator_type"); \
        m_pointer_mode.SetWeak(argument, m_data); \
    } \
protected: \
    pointer_mode_t m_pointer_mode;

namespace System { namespace Collections { namespace Generic { namespace Detail { template <typename Key, typename Mapped, typename Comparer> class FlatMap; }}}}

/// Defines all members to make it possible controlling map-styled container's pointer mode (weak or shared).
/// @param map_t Type of map-styled container.
#define ASPOSE_MAP_POINTER_MODE_CONTROL(map_t) \
public: \
    template <class T> \
    struct IsFlatMap : System::detail::is_a<T, System::Collections::Generic::Detail::FlatMap> {}; \
     \
    typedef typename std::conditional<IsFlatMap<map_t>::value, \
        System::Details::CollectionHelpers::VectorPairPointerMode<typename map_t::key_type, typename map_t::mapped_type>, \
        System::Details::CollectionHelpers::MapPointerMode<typename map_t::key_type, typename map_t::mapped_type> \
    >::type pointer_mode_t; \
protected: \
    typedef typename pointer_mode_t::allocator_type allocator_t;

/// Defines all members to make it possible controlling map-styled container's pointer mode (weak or shared).
/// Does not define data type or 'm_data' member itself as they are too important to hide inside the macro.
/// @param key_type Type of key.
/// @param mapped_type Type of mapped value.
#define ASPOSE_STL_MAP_POINTER_MODE_CONTROL(key_type, mapped_type) \
public: \
    typedef typename System::Details::CollectionHelpers::MapPointerMode<key_type, mapped_type> pointer_mode_t; \
    typedef typename pointer_mode_t::allocator_type allocator_t; \
    void SetTemplateWeakPtr(uint32_t argument) override \
    { \
        static_assert(std::is_same<decltype(m_map.get_allocator()), typename pointer_mode_t::allocator_type>::value, "Container's allocator is not set to typename pointer_mode_t::allocator_type"); \
        m_pointer_mode.SetWeak(argument, m_map); \
    } \
protected: \
    pointer_mode_t m_pointer_mode;

/// Defines the type of collection allocator.
#define ASPOSE_COLLECTION_ALLOCATOR_TYPE typename pointer_mode_t::allocator_type
/// Initializes container with proper allocator.
#define ASPOSE_COLLECTION_INIT_ALLOCATOR() m_data(m_pointer_mode.GetAllocator())
/// Allocator value to initializes container with.
#define ASPOSE_COLLECTION_ALLOCATOR m_pointer_mode.GetAllocator()

/// Defines the type of map's allocator.
#define ASPOSE_MAP_ALLOCATOR_TYPE(key_type, mapped_type) typename System::Details::CollectionHelpers::MapPointerMode<key_type, mapped_type>::allocator_type
#define ASPOSE_VECTOR_ALLOCATOR_TYPE(key_type, mapped_type) typename System::Details::CollectionHelpers::VectorPairPointerMode<key_type, mapped_type>::allocator_type
/// Initializes map-styled container with proper allocator.
#define ASPOSE_MAP_INIT_ALLOCATOR() m_map(m_pointer_mode.GetAllocator())

#endif //_aspose_system_detail_pointer_collection_helpers_h_
