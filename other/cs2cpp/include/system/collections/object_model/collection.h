/// @file system/collections/object_model/collection.h
#ifndef _aspose_system_collections_object_model_collection_h
#define _aspose_system_collections_object_model_collection_h

#include <iterator>

#include <system/string.h>
#include <system/collections/list.h>

namespace System { namespace Collections { namespace ObjectModel {

/// Base type for generic collection.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam T Element type.
template<class T>
class ASPOSECPP_SHARED_CLASS Collection : public Generic::IList<T>
{
    /// Internal data structure.
    SharedPtr<Generic::IList<T>> items;
public:
    /// Creates empty collection.
    Collection() : items(MakeObject<System::Collections::Generic::List<T>>())
    {}

    Collection(SharedPtr<Generic::IList<T>> list) : items(list)
    {
        if (list == nullptr)
            throw ArgumentNullException(u"list");
    }


    /// Internal data structure accessor.
    /// @return Pointer to internal list.
    SharedPtr<Generic::IList<T>>  get_Items()
    {
        return items;
    }
    /// Internal data structure accessor.
    /// @return Pointer to internal list.
    const Generic::ListPtr<T>  get_Items() const
    {
        return items;
    }

    /// Gets number of elements.
    /// @return Active element count.
    int get_Count() const override
    {
        return items->get_Count();
    }
    /// Gets value at specified index.
    /// @param index Index to get value from.
    /// @return Copy of value at specified index.
    virtual T idx_get(int index) const override
    {
        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }

        return items->idx_get(index);
    }
    /// Sets value at specified index.
    /// @param index Index to set value at.
    /// @param value Value to set at specified index.
    virtual void idx_set(int index, T value) override
    {
        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }
        items->idx_set(index, value);
    }
    /// Gets value at specified index.
    /// @param index Index to get value from.
    /// @return Reference to existing value at specified index.
    T& operator[](int index)
    {
        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }

        return items->idx_get(index);
    }
    /// Gets value at specified index.
    /// @param index Index to get value from.
    /// @return Const reference to existing value at specified index.
    const T& operator[](int index) const
    {
        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }
        return items->idx_get(index);
    }

    /// Adds value to container.
    /// @param item Item to add.
    virtual void Add(const T& item) override
    {
        int index = get_Count();
        InsertItem(index, item);
    }
    /// Deletes all elements.
    void Clear() override
    {
        ClearItems();
    }
    /// Checks if item is present in collection.
    /// @param item to look for.
    /// @return True if item is present, false otherwise.
    bool Contains(const T& item) const override
    {
        return items->Contains(item);
    }
    /// Gets enumerator to iterate through collection.
    /// @return Created enumerator iterating through current collection.
    SharedPtr<Generic::IEnumerator<T> > GetEnumerator() override
    {
        return items->GetEnumerator();
    }
    /// Looks for element in collection.
    /// @param item Item to look for.
    /// @return Index of first occurrence of specified item or -1 if not found.
    int IndexOf(const T& item) const override
    {
        return items->IndexOf(item);
    }
    /// Inserts item into specified position.
    /// @param index Index to insert item into.
    /// @param item Item to insert into specified position.
    void Insert(int index, const T& item) override
    {
        if (index < 0 || index > get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }

        InsertItem(index, item);
    }
    /// Removes specific item.
    /// @param item Item to remove.
    /// @return True if item was found and removed, false otherwise.
    bool Remove(const T& item) override
    {
        int index = items->IndexOf(item);
        if (index < 0)
        {
            return false;
        }

        RemoveItem(index);
        return true;
    }
    /// Removes item at specific position.
    /// @param index Index to remove item at.
    void RemoveAt(int index) override {

        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }

        RemoveItem(index);
    }

    /// Copies collection elements into existing array elements.
    /// @param arr Destination array.
    /// @param index Destination array start index.
    virtual void CopyTo(ArrayPtr<T> arr, int index) override
    {
        items->CopyTo(arr, index);
    }
    
    /// Makes stored pointers weak (if applicable).
    /// @param argument Should be 0 as only one template argument is present.
    void SetTemplateWeakPtr(uint32_t argument) override
    {
        items->SetTemplateWeakPtr(argument);
    }

    /// Iterates elements of the sequence container in the reverse order.
    template <typename U>
    class reverse_iterator_prototype: public Details::BaseIterator<std::bidirectional_iterator_tag, U, std::ptrdiff_t>
    {
        private:
            /// Internal data structure reference.
            SharedPtr<Generic::IList<U>> m_list;
            int m_size;
            int m_index;
        public:
            reverse_iterator_prototype()
                : m_size(0)
                , m_index(-1)
            {}
            reverse_iterator_prototype(const SharedPtr<Generic::IList<U>> &list)
                : m_list(list)
                , m_size(list->get_Count())
                , m_index(m_size-1)
            {}

            const U operator*() const {
                return m_list->idx_get(m_index);
            }

            reverse_iterator_prototype& operator++()
            {
                if (m_index >= 0) {
                    --m_index;
                }
                return *this;
            }

            reverse_iterator_prototype& operator--()
            {
                if (m_index < m_size) {
                    ++m_index;
                }
                return *this;
            }

            bool operator!=(const reverse_iterator_prototype& it) const {
                return m_index != it.m_index;
            }

            bool operator==(const reverse_iterator_prototype& it) const {
                return m_index == it.m_index;
            }
    };

    typedef reverse_iterator_prototype<T> reverse_iterator;
    typedef reverse_iterator_prototype<T> const_reverse_iterator;

    /// Gets a reverse iterator to the last element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the list (first in reverse).
    reverse_iterator rbegin() noexcept { return reverse_iterator(items); }
    /// Gets a reverse iterator for a non-existent element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical element preceding the first element in the list (last in reverse).
    reverse_iterator rend() noexcept { return reverse_iterator(); }

    /// Gets a reverse iterator to the last element of the const-qualified collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the const-qualified list (first in reverse).
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(items); }
    /// Gets a reverse iterator for a non-existent element before the start of the const-qualified collection.
    /// @return A reverse iterator pointing to the theoretical element preceding the first element in the const-qualified list (last in reverse).
    const_reverse_iterator rend() const noexcept { return reverse_iterator(); }

    /// Gets a reverse iterator to the last const-qualified element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last const-qualified element in the list (first in reverse).
    const_reverse_iterator crbegin() const noexcept { return reverse_iterator(items); }
    /// Gets a reverse iterator for a non-existent const-qualified element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical const-qualified element preceding the first element in the list (last in reverse).
    const_reverse_iterator crend() const noexcept { return reverse_iterator(); }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return items->virtualizeBeginIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return items->virtualizeEndIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return items->virtualizeBeginConstIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return items->virtualizeEndConstIterator();
    }

protected:
    /// Destructor.
    ~Collection() override {}

    /// Deletes all items.
    virtual void ClearItems()
    {
        items->Clear();
    }
    /// Inserts item into specified position.
    /// @param index Index to insert item into.
    /// @param item Item to insert into specified position.
    virtual void InsertItem(int index, const T& item)
    {
        items->Insert(index, item);
    }
    /// Removes item from specified position.
    /// @param index Index to remove item from.
    virtual void RemoveItem(int index)
    {
        items->RemoveAt(index);
    }
    /// Sets item at specified position.
    /// @param index Index to set item at.
    /// @param item Value to set at specified position.
    virtual void SetItem(int index, const T& item)
    {
        items->idx_set(index, item);
    }
};

}}} // namespace System::Collections::ObjectModel

#endif // _aspose_system_collections_object_model_collection_h
