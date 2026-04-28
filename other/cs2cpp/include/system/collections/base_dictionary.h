/// @file system/collections/base_dictionary.h
#pragma once

#include <system/collections/idictionary.h>
#include <system/cycles_detection.h>
#include <system/collections/base_enumerator.h>
#include <system/details/hash_quality_checker.h>
#include <system/collections/virtualized_iterator.h>

#include <algorithm>
#include <type_traits>

namespace System { namespace Collections { namespace Generic {

/// Dictionary iterator that provides KeyValuePair notation.
/// @tparam Dict Dictionary class.
template <typename Dict>
class DictionaryIterator
    : public System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>
    , private System::Details::IteratorPointerUpdater<typename Dict::KeyValuePairType, false>
{
    using System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>::m_iterator;
    using System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>::m_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::KeyValuePairType>::m_is_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::KeyValuePairType>::m_pointer;
    using System::Details::IteratorPointerUpdater<typename Dict::KeyValuePairType, false>::InitializeIteratorPointer;
    using System::Details::IteratorPointerUpdater<typename Dict::KeyValuePairType, false>::UpdateIteratorPointer;

public:
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    DictionaryIterator(typename Dict::map_t::const_iterator &&iterator, typename Dict::map_t::const_iterator &&end) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>(
            std::forward<typename Dict::map_t::const_iterator>(iterator),
            std::forward<typename Dict::map_t::const_iterator>(end)
        )
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    DictionaryIterator(const typename Dict::map_t::const_iterator &iterator, const typename Dict::map_t::const_iterator &end)
        : System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>(iterator, end)
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Move constructor.
    /// @param other Iteratro to move data from.
    DictionaryIterator(DictionaryIterator &&other) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>(std::forward(other.m_iterator))
    {
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Destructor.
    virtual ~DictionaryIterator() = default;

    /// Moves the iterator step forward.
    void IncrementIterator() override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>::IteratorIncrementImplementation())
            UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Moves the iterator step back.
    void DecrementIterator() override
    {
        System::Details::IteratorDecrementer<typename Dict::map_t::const_iterator>::decrement(m_iterator);
        UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Moves the iterator by the specified number of steps.
    /// @param offset Number of steps to move the iterator by.
    void ShiftIteratorBy(std::ptrdiff_t offset) override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::KeyValuePairType, typename Dict::map_t::const_iterator>::IteratorShiftImplementation(offset))
            UpdateIteratorPointer(m_pointer, typename Dict::KeyValuePairType(m_iterator->first, m_iterator->second));
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<typename Dict::KeyValuePairType>* CloneIterator() const override
    {
        return new DictionaryIterator(m_iterator, m_end);
    }
};


/// Implements common code for various dictionary-alike data structures (e. g. Dictionary, SortedDictionary).
/// Shouldn't be used directly, except for inheritance when defining containers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam Map Underlying map type.
template<typename Map>
class ASPOSECPP_SHARED_CLASS BaseDictionary : public IDictionary<typename Map::key_type, typename Map::mapped_type>
{
    ASPOSE_MAP_POINTER_MODE_CONTROL(Map)

public:
    void SetTemplateWeakPtr(unsigned int argument) override
    {
        static_assert(std::is_same<decltype(m_map.get_allocator()), typename pointer_mode_t::allocator_type>::value, "Container's allocator is not set to typename pointer_mode_t::allocator_type");
        m_pointer_mode.SetWeak(argument, m_map);
    }

    /// Internal map type.
    typedef Map map_t;

protected:
    pointer_mode_t m_pointer_mode;

private:
    /// Key type name alias.
    typedef typename Map::key_type key_t;
    /// Value type name alias.
    typedef typename Map::mapped_type mapped_t;
    /// Iterator type name alias.
    typedef typename Map::iterator mapIt_t;
    /// Const iterator type name alias
    typedef typename Map::const_iterator stl_const_iterator;

    /// Make sure we use correct allocator with underlying storage type.
    static_assert(std::is_same<allocator_t, typename Map::allocator_type>::value, "Using wrong map type with BaseDictionary");

public:
    /// Collection of keys.
    typedef ICollection<key_t>  KeyCollection;
    /// Collection of values.
    typedef ICollection<mapped_t> ValueCollection;
    /// Key-value pair type.
    typedef KeyValuePair<key_t, mapped_t> KVPair;

    /// Implemented interface.
    typedef IDictionary<typename Map::key_type, typename Map::mapped_type> BaseType;

    /// Iterator type.
    typedef KVPairIterator<KVPair, Map> iterator;
    /// Const iterator type.
    typedef KVPairIterator<KVPair, Map> const_iterator;

    /// Creates empty data structure.
    BaseDictionary() : ASPOSE_MAP_INIT_ALLOCATOR() {}

    /// Forwarding constructor to push arguments into underlying map constructor.
    /// @tparam Args Types of arguments to forward to map.
    /// @param args Arguments to forward to underlying map.
    template<class... Args>
    BaseDictionary(int, const Args&... args)
        : m_map(args..., ASPOSE_COLLECTION_ALLOCATOR)
    {}

    /// Copying constructor.
    /// @tparam Args Types of map constructor arguments.
    /// @param src Object to copy data from.
    /// @param args Arguments to forward to underlying map constructor.
    template<class... Args>
    BaseDictionary(BaseType* src, const Args&... args)
        : m_map(args..., ASPOSE_COLLECTION_ALLOCATOR)
    {
        CopyFrom(src);
    }

    /// Copying constructor.
    /// @param src Object to copy data from.
    BaseDictionary(BaseType* src) : ASPOSE_MAP_INIT_ALLOCATOR()
    {
        CopyFrom(src);
    }

    // IEnumerable
    /// Creates enumerator instance, should be implemented by subclass.
    /// @return Enumerator bound to this object.
    SharedPtr< IEnumerator<KeyValuePair<key_t, mapped_t> > > GetEnumerator() override = 0;

    // ICollection
    /// Gets elements count.
    /// @return Number of elements (key-value pairs) being held currently.
    int32_t get_Count() const override
    {
        return static_cast<int32_t>(m_map.size());
    }
    /// Deletes all elements.
    void Clear() override
    {
        m_map.clear();
    }

    // IDictionary interface
    /// Accessor function.
    /// @param key Dictionary key to access.
    /// @return Reference to existing (or created) value keyed by @p key.
    virtual mapped_t& operator[](const key_t& key)
    {
        return m_map[key];
    }
    /// Keyed getter function.
    /// @param key Key to get value at.
    /// @return Copy of element at @p key position.
    /// @throw KeyNotFoundException if element is not found.
    mapped_t idx_get(const key_t& key) const override
    {
        CheckIfNull(key);
        auto it = m_map.find(key);
        if (it == m_map.end())
        {
            throw KeyNotFoundException();
        }

        return it->second;
    }
    /// Keyed setter function. Alters or creates element.
    /// @param key Key to set value at.
    /// @param value Value to set.
    void idx_set(const key_t& key, mapped_t value) override
    {
        CheckIfNull(key);
        m_map[key] = value;
#if defined(ASPOSE_DETECT_BAD_QUALITY_HASH)
        System::Details::CheckHashFunctionQuality(m_map);
#endif
    }
    /// Adds key-value pair into dictionary.
    /// @param key Key to insert value for.
    /// @param value Value to insert.
    /// @throw ArgumentException If key already exists.
    void Add(const key_t& key, const mapped_t& value) override
    {
        CheckIfNull(key);
        // insert never replaces values
        auto op_result = m_map.insert(std::make_pair(key, value));
        if (! op_result.second)
        {
            throw System::ArgumentException(u"key");
        }
#if defined(ASPOSE_DETECT_BAD_QUALITY_HASH)
        System::Details::CheckHashFunctionQuality(m_map);
#endif
    }
    /// Checks if key is present in dictionary.
    /// @param key Key to look for.
    /// @return true if key is present, false otherwise.
    bool ContainsKey(const key_t& key) const override
    {
        CheckIfNull(key);
        return m_map.find(key) != m_map.end();
    }
    /// Removes specific key from dictionary.
    /// @param key Key to remove.
    /// @return true if key was found and removed, false otherwise.
    bool Remove(const key_t& key) override
    {
        CheckIfNull(key);
        auto it = m_map.find(key);

        if (it != m_map.end())
        {
            m_map.erase(it);
            return true;
        }

        return false;
    }
    /// Looks for keyed value and retreives it if found.
    /// @param key Key to look for.
    /// @param value Reference to store found value at.
    /// @return true if value is found and retreived, false otherwise.
    bool TryGetValue(const key_t& key, mapped_t& value) const override
    {
        auto it = m_map.find(key);

        if (it != m_map.end())
        {
            value = it->second;
            return true;
        }

        // There should be the System::Default<mapped_t>() call, but it has a lot of restrictions,
        // e.g. System::Default doesn't work with C# structures and delegates
        value = mapped_t();
        return false;
    }

    // BaseDictionary interface
    /// Checks if value is present in dictionary. Uses operator == to compare values.
    /// @param value Value to look for.
    /// @return true if value is found, false otherwise.
    bool ContainsValue(const mapped_t& value)
    {
        for (const auto& itr : m_map)
        {
            if (itr.second == value)
                return true;
        }
        return false;
    }

    /// Underlying data storage accessor.
    /// @return Reference to underlying data storage.
    Map& data() { return m_map; }
    /// Underlying data storage accessor.
    /// @return Const reference to underlying data storage.
    const Map& data() const { return m_map; }
    /// C++ specific
    /// @param list Range to insert into container.
    void _add_range(std::initializer_list<typename Map::value_type> list)
    {
        std::for_each(list.begin(), list.end(), [this](const typename Map::value_type &v) { m_map.insert(v); });
    }

    /// Returns value if found; or <c>Value()</c> otherwise
    mapped_t GetValueOrDefault(const key_t& key) const override
    {
        auto it = m_map.find(key);

        if (it != m_map.end())
        {
            return it->second;
        }

        return mapped_t();
    }

    /// Returns value if found; or <c>defaultValue</c> otherwise.
    mapped_t GetValueOrDefault(const key_t& key, const mapped_t& defaultValue) const override
    {
        auto it = m_map.find(key);

        if (it != m_map.end())
        {
            return it->second;
        }

        return defaultValue;
    }

    /// Returns value if found; or <c>null</c> otherwise. Make sense only for reference types
    mapped_t GetValueOrNull(const key_t& key) const override
    {
        auto it = m_map.find(key);

        if (it != m_map.end())
        {
            return it->second;
        }

        return mapped_t();
    }

    /// Returns an iterator to the KVPair-wrapper for key-value-element of the container. Implemented in C# style -
    /// iterator should be return the KVPair-object with get_Key() and get_Value() interface.
    /// If the container is empty, the returned iterator will be equal to end().
    /// @return An iterator pointing to the first element of collection.
    const_iterator begin() const noexcept
    {
        return m_map.begin();
    }

    /// Returns an iterator to the KVPair-wrapper for key-value-element following the last element of the container.
    /// Implemented in C# style - iterator should be return the KVPair-object with get_Key() and get_Value() interface.
    /// This element acts as a placeholder; attempting to access it results in undefined behavior.
    /// @return An iterator pointing to the theoretical element placed after the end element of collection.
    const_iterator end() const noexcept
    {
        return m_map.end();
    }

    /// Returns an iterator to the first element of the container. Implemented in STL-style.
    /// If the container is empty, the returned iterator will be equal to end().
    /// @return An iterator pointing to the first const-qualified element of collection.
    stl_const_iterator cbegin() const noexcept
    {
        return m_map.cbegin();
    }

    /// Returns an iterator to the element following the last element of the container. Implemented in STL-style.
    /// This element acts as a placeholder; attempting to access it results in undefined behavior.
    /// @return An iterator pointing to the theoretical const-qualified element placed after the end element of collection.
    stl_const_iterator cend() const noexcept
    {
        return m_map.cend();
    }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<KVPair>* virtualizeBeginIterator() override
    {
        return new DictionaryIterator<BaseDictionary>(m_map.begin(), m_map.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<KVPair>* virtualizeEndIterator() override
    {
        return new DictionaryIterator<BaseDictionary>(m_map.end(), m_map.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<KVPair>* virtualizeBeginConstIterator() const override
    {
        return new DictionaryIterator<BaseDictionary>(m_map.begin(), m_map.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<KVPair>* virtualizeEndConstIterator() const override
    {
        return new DictionaryIterator<BaseDictionary>(m_map.end(), m_map.end());
    }

protected:
    /// Underlying C++ data structure.
    Map m_map;

    // ICollection
    /// Checks if key-value pair is present in dictionary, comparing both keys and values.
    /// @param item Item to look for.
    /// @return true if item is found, false otherwise.
    bool Contains(const KeyValuePair<key_t, mapped_t>& item) const override
    {
        auto it = m_map.find(item.m_pair.first);

        return it != m_map.end() && it->second == item.m_pair.second;
    }
    /// Removes specified key-value pair from dictionary, compares both keys and values.
    /// @param item Item to remove.
    /// @return true if pair was found and deleted, false otherwise.
    bool Remove(const KeyValuePair<key_t, mapped_t>& item) override
    {
        auto it = m_map.find(item.m_pair.first);

        if (it != m_map.end() && it->second == item.m_pair.second)
        {
            m_map.erase(it);
            return true;
        }

        return false;
    }

#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop references detection mechanics for dictionary type.
    /// @return Data structure holding information on shared pointers owned by dictionary.
    virtual void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        Object::GetSharedMembers(result);
        result.PopulateSharedMembers("System::Collections::Generic::BaseDictionary<Map>::m_map[]", m_map);
    }
#endif

private:
    /// Copies data from another dictionary.
    /// @param src Source dictionary.
    void CopyFrom(BaseType* src)
    {
        if (nullptr == src)
            throw ArgumentNullException(u"Argument cannot be nullptr");

        SharedPtr<IEnumerator<KeyValuePair<key_t, mapped_t> > > enumerator = src->GetEnumerator();
        while (enumerator->MoveNext())
            BaseDictionary<Map>::Add(enumerator->get_Current());
    }
    /// Inserts KeyValuePair into dictionary.
    /// @param item Pair to insert.
    void Add(const KeyValuePair<key_t, mapped_t>& item) override
    {
        m_map.insert(item.m_pair);
    }
    /// Returns exception being thrown read-only dictionaries' non-const methods.
    static NotSupportedException ReadOnlyException()
    {
        return NotSupportedException(u"The collection is readonly");
    }

protected:
    /// Destructor.
    ~BaseDictionary() override {}

#ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to collection and its elements.
        /// @param visitor Visitor to apply.
        void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
        {
            visitor.add_self(this);
            DBG::for_each_of_Object(this, m_map, visitor);
        }

        /// Gets class name.
        /// @return Current class name.
        const char* DBG_class_name() const override { return "BaseDictionary<T>"; }
#endif

private:
    /// @brief Checks if the object has the equality operator.
    /// @tparam T Type of object to compare.
    /// @return Always returns false as value type does not have the equality operator.
    template <typename T, class = void>
    struct has_equality_operator : std::false_type {};
    /// @brief Checks if the object has the equality operator.
    /// @tparam T Type of object to compare.
    /// @return Always returns true as value type has the equality operator.
    template <typename T>
    struct has_equality_operator<T, typename std::enable_if<!std::is_enum<T>::value, decltype((void)(std::declval<T>() == nullptr))>::type> : std::true_type
    {};

    /// @brief Checks if the instance is null.
    /// @tparam instance Type of object to check.
    /// @note throws an System::ArgumentNullException if the instance is equal to null.
    template <typename T>
    typename std::enable_if<has_equality_operator<T>::value, void>::type CheckIfNull(const T& instance) const
    {
        if (instance == nullptr) 
        {
            throw System::ArgumentNullException(u"key");
        }
    }
    /// @brief Checks if the instance is null.
    /// @tparam instance Type of object to check.
    /// @note an sfinae stub.    
    template <typename T>
    typename std::enable_if<!has_equality_operator<T>::value, void>::type CheckIfNull(const T& instance) const
    {
    }

};

}}} // namespace System::Collections::Generic
