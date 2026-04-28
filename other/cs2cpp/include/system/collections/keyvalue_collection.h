/// @file system/collections/keyvalue_collection.h
#pragma once

#include <system/collections/base_enumerator.h>
#include <system/collections/base_kv_collection.h>

namespace System { namespace Collections { namespace Generic {

/// Dictionary iterator that provides key access.
/// @tparam Dict Dictionary class.
template <typename Dict>
class KeyIterator
    : public System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>
    , private System::Details::IteratorPointerUpdater<typename Dict::map_t::key_type, false>
{
    using System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>::m_iterator;
    using System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>::m_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::map_t::key_type>::m_is_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::map_t::key_type>::m_pointer;
    using System::Details::IteratorPointerUpdater<typename Dict::map_t::key_type, false>::InitializeIteratorPointer;
    using System::Details::IteratorPointerUpdater<typename Dict::map_t::key_type, false>::UpdateIteratorPointer;

public:
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    KeyIterator(typename Dict::map_t::const_iterator &&iterator, typename Dict::map_t::const_iterator &&end) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>(
            std::forward<typename Dict::map_t::const_iterator>(iterator),
            std::forward<typename Dict::map_t::const_iterator>(end)
        )
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    KeyIterator(const typename Dict::map_t::const_iterator &iterator, const typename Dict::map_t::const_iterator &end)
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>(iterator, end)
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Move constructor.
    /// @param other Iterator to move data from.
    KeyIterator(KeyIterator &&other) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>(std::forward(other.m_iterator))
    {
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Destructor. 
    virtual ~KeyIterator() = default;

    /// Moves the iterator step forward.
    void IncrementIterator() override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>::IteratorIncrementImplementation())
            UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Moves the iterator step back.
    void DecrementIterator() override
    {
        System::Details::IteratorDecrementer<typename Dict::map_t::const_iterator>::decrement(m_iterator);
        m_is_end = false;
        UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Moves the iterator by the specified number of steps.
    /// @param offset Number of steps to move the iterator by.
    void ShiftIteratorBy(std::ptrdiff_t offset) override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::map_t::key_type, typename Dict::map_t::const_iterator>::IteratorShiftImplementation(offset))
            UpdateIteratorPointer(m_pointer, m_iterator->first);
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<typename Dict::map_t::key_type>* CloneIterator() const override
    {
        return new KeyIterator(m_iterator, m_end);
    }
};


/// Collection of Dictionary's keys. References collection, doesn't copy anything.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @param Dict Dictionary type.
template <typename Dict>
class ASPOSECPP_SHARED_CLASS _KeyCollection : public BaseKVCollection<Dict, typename Dict::map_t::key_type>
{
public:
    /// Key type.
    typedef typename Dict::map_t::key_type TKey;

    /// Initializes collection referencing specified dictionary.
    /// @param dict Dictionary to reference.
    _KeyCollection(const typename Dict::Ptr& dict) : BaseKVCollection<Dict, typename Dict::map_t::key_type>(dict) {}

    // IEnumerable
    /// Enumerator to iterate through keys.
    class Enumerator : public BaseEnumerator<typename Dict::map_t, TKey>
    {
    public:
        /// Creates key enumerator for specified dictionary.
        /// @param dict Dictionary to reference.
        Enumerator(const typename Dict::Ptr& dict) : BaseEnumerator<typename Dict::map_t, TKey>(dict, dict->data()) { }
        /// Gets current key.
        /// @return Current key.
        MakeConstRef_t<TKey> get_Current() const override
        {
            if (this->IsValid())
                return this->m_it->first;
            else
                return System::Default<TKey>();
        }
    };
    /// Gets enumerator iterating through keys.
    /// @return Pointer to newly created enumerator.
    SharedPtr<IEnumerator<TKey> > GetEnumerator() override { return MakeObject<Enumerator>(this->m_dict); }

    /// Checks if item is present in container.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    bool Contains(const TKey& item) const override
    {
        return this->m_dict->ContainsKey(item);
    }

    // IList
    /// Implements IList method. Not supported.
    TKey idx_get(int index) const override { ASPOSE_UNUSED(index); throw System::InvalidOperationException(); }

    /// @copydoc System::Collections::Generic::IEnumerable<TKey>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<TKey>* virtualizeBeginIterator() override
    {
        return new KeyIterator<Dict>(this->m_dict->data().begin(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TKey>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<TKey>* virtualizeEndIterator() override
    {
        return new KeyIterator<Dict>(this->m_dict->data().end(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TKey>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<TKey>* virtualizeBeginConstIterator() const override
    {
        return new KeyIterator<Dict>(this->m_dict->data().begin(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TKey>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<TKey>* virtualizeEndConstIterator() const override
    {
        return new KeyIterator<Dict>(this->m_dict->data().end(), this->m_dict->data().end());
    }

protected:
    /// Destructor.
    ~_KeyCollection() override {}
};

/// Dictionary iterator that provides value access.
/// @tparam Dict Dictionary class.
template <typename Dict>
class ValueIterator
    : public System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>
    , private System::Details::IteratorPointerUpdater<typename Dict::map_t::mapped_type, false>
{
    using System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>::m_iterator;
    using System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>::m_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::map_t::mapped_type>::m_is_end;
    using System::Details::VirtualizedIteratorBase<typename Dict::map_t::mapped_type>::m_pointer;
    using System::Details::IteratorPointerUpdater<typename Dict::map_t::mapped_type, false>::InitializeIteratorPointer;
    using System::Details::IteratorPointerUpdater<typename Dict::map_t::mapped_type, false>::UpdateIteratorPointer;

public:
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    ValueIterator(typename Dict::map_t::const_iterator &&iterator, typename Dict::map_t::const_iterator &&end) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>(
            std::forward<typename Dict::map_t::const_iterator>(iterator),
            std::forward<typename Dict::map_t::const_iterator>(end)
        )
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Constructor.
    /// @param iterator Iterator to hold.
    /// @param end Iterator to the end of the container.
    ValueIterator(const typename Dict::map_t::const_iterator &iterator, const typename Dict::map_t::const_iterator &end)
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>(iterator, end)
    {
        InitializeIteratorPointer(m_pointer);
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Move constructor.
    /// @param other Iteratro to move data from.
    ValueIterator(ValueIterator &&other) noexcept
        : System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>(std::forward(other.m_iterator))
    {
        if (!m_is_end)
            UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Destructor.
    virtual ~ValueIterator() = default;

    /// Moves the iterator step forward.
    void IncrementIterator() override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>::IteratorIncrementImplementation())
            UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Moves the iterator step back.
    void DecrementIterator() override
    {
        System::Details::IteratorDecrementer<typename Dict::map_t::const_iterator>::decrement(m_iterator);
        m_is_end = false;
        UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Moves the iterator by the specified number of steps.
    /// @param offset Number of steps to move the iterator by.
    void ShiftIteratorBy(std::ptrdiff_t offset) override
    {
        if (System::Details::NativeIteratorWrapperBase<typename Dict::map_t::mapped_type, typename Dict::map_t::const_iterator>::IteratorShiftImplementation(offset))
            UpdateIteratorPointer(m_pointer, m_iterator->second);
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<typename Dict::map_t::mapped_type>* CloneIterator() const override
    {
        return new ValueIterator(m_iterator, m_end);
    }
};


/// Collection of Dictionary's values. References collection, doesn't copy anything.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @param Dict Dictionary type.
template <typename Dict>
class ASPOSECPP_SHARED_CLASS _ValueCollection : public BaseKVCollection<Dict, typename Dict::map_t::mapped_type>
{
public:
    /// Value type.
    typedef typename Dict::map_t::mapped_type TValue;

    /// Initializes collection referencing specified dictionary.
    /// @param dict Dictionary to reference.
    _ValueCollection(const typename Dict::Ptr& dict) : BaseKVCollection<Dict, typename Dict::map_t::mapped_type>(dict) {}

    // IEnumerable
    /// Enumerator to iterate through values.
    class Enumerator : public BaseEnumerator<typename Dict::map_t, TValue>
    {
    public:
        /// Creates value enumerator for specified dictionary.
        /// @param dict Dictionary to reference.
        Enumerator(const typename Dict::Ptr& dict) : BaseEnumerator<typename Dict::map_t, TValue>(dict, dict->data()) { }
        /// Gets current value.
        /// @return Current value.
        MakeConstRef_t<TValue> get_Current() const override
        {
            if (this->IsValid())
                return this->m_it->second;
            else
                return System::Default<TValue>();
        }
    };
    /// Gets enumerator iterating through values.
    /// @return Pointer to newly created enumerator.
    SharedPtr<IEnumerator<TValue> > GetEnumerator() override { return MakeObject<Enumerator>(this->m_dict); }

    /// Checks if item is present in container.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    bool Contains(const TValue& item) const override
    {
        return this->m_dict->ContainsValue(item);
    }

    // IList
    /// Implements IList method. Not supported.
    TValue idx_get(int index) const override { ASPOSE_UNUSED(index); throw System::InvalidOperationException(); }

    /// @copydoc System::Collections::Generic::IEnumerable<TValue>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<TValue>* virtualizeBeginIterator() override
    {
        return new ValueIterator<Dict>(this->m_dict->data().begin(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TValue>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<TValue>* virtualizeEndIterator() override
    {
        return new ValueIterator<Dict>(this->m_dict->data().end(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TValue>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<TValue>* virtualizeBeginConstIterator() const override
    {
        return new ValueIterator<Dict>(this->m_dict->data().begin(), this->m_dict->data().end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<TValue>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<TValue>* virtualizeEndConstIterator() const override
    {
        return new ValueIterator<Dict>(this->m_dict->data().end(), this->m_dict->data().end());
    }

protected:
    /// Destructor.
    ~_ValueCollection() override {}
};

}}} // namespace System::Collections::Generic
