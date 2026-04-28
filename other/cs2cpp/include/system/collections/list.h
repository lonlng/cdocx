/// @file system/collections/list.h
#pragma once

#include <system/details/collections_helper.h>
#include <system/details/comparer_type.h>
#include <system/object.h>
#include <system/collections/ilist.h>
#include <system/array.h>
#include <system/exceptions.h>
#include <system/collections/base_enumerator.h>
#include <system/collections/icomparer.h>
#include <system/collections/algorithms.h>
#include <system/collections/read_only_collection.h>
#include <system/predicate.h>
#include <system/comparison.h>
#include <system/action.h>
#include <system/converter.h>
#include <system/cycles_detection.h>
#include <system/multicast_delegate.h>

#include <fwd.h>

#include <vector>
#include <algorithm>
#include <utility>
#include <cstddef>

namespace System { namespace Collections { namespace Generic {

/// List forward declaration.
template<typename T> class List;

/// List pointer with access operators.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
template<typename T>
class ListPtr : public SharedPtr<List<T>>
{
public:
    /// Initializes null-pointer.
    ListPtr(std::nullptr_t = nullptr) {}
    /// Initializes pointer to specified list.
    /// @param obj List to point to.
    ListPtr(const SharedPtr<List<T> >& obj) : SharedPtr<List<T>>(obj) { }

    /// Accessor.
    /// @param idx Index to access element from.
    /// @return Reference to specified element.
    typename std::vector<T>::reference operator[](int idx) { return (*this)->operator[](idx); }
    /// Accessor.
    /// @param idx Index to access element from.
    /// @return Const reference to specified element.
    typename std::vector<T>::const_reference operator[](int idx) const  { return (*this)->operator[](idx); }

    /// @brief Checks if List pointer is null.
    /// @return True if List pointer is null and false otherwise.
    bool operator == (std::nullptr_t) const
    {
        return SmartPtr<List<T>>::operator == (nullptr);
    }
};

/// List - wrapper around std::vector to be used in translated code.
/// Requires operator == to be impemented for element type.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include <system/collections/list.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create the first list.
///   auto list1 = MakeObject<List<int>>();
///
///   // Fill the first list.
///   list1->Add(3);
///   list1->Add(1);
///   list1->Add(-5);
///   list1->Add(8);
///
///   // Sort the first list.
///   // The first list items will be: {-5, 1, 3, 8}
///   list1->Sort();
///
///   // Remove the item at index 2.
///   // The first list items will be: {-5, 1, 8}
///   list1->RemoveAt(2);
///
///   // Insert the item to index 1.
///   // The first list items will be: {-5, 15, 1, 8}
///   list1->Insert(1, 15);
///
///   // Create the second list.
///   auto list2 = MakeObject<List<int>>();
///
///   // Fill the second list.
///   list2->Add(10);
///   list2->Add(20);
///   list2->Add(30);
///
///   // Append elements from the second list to the first one.
///   list1->AddRange(list2);
///
///   // Print the first list items.
///   for (const auto item: list1)
///   {
///     std::cout << item << ' ';
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// -5 15 1 8 10 20 30
/// */
/// @endcode
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS List
    : virtual public Object
    , public System::Collections::Generic::IList<T>
{
    ASPOSE_COLLECTION_POINTER_MODE_CONTROL(T)

public:
    /// This type.
    typedef T ValueType;
    /// Interface type.
    typedef IList<T> BaseType;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::List<T>, System::BaseTypesInfo<BaseType>);

public:
    /// Underlying data type.
    typedef std::vector<T, ASPOSE_COLLECTION_ALLOCATOR_TYPE> vector_t;

    /// Iterator type.
    typedef typename vector_t::iterator iterator;
    /// Const iterator type.
    typedef typename vector_t::const_iterator const_iterator;
    /// Reverse iterator type.
    typedef typename vector_t::reverse_iterator reverse_iterator;
    /// Const reverse iterator type.
    typedef typename vector_t::const_reverse_iterator const_reverse_iterator;

protected:
    /// Pointer type.
    typedef SharedPtr<List<T> > ThisPtr;
    /// Underlting data structure.
    vector_t m_data;

public:
    /// Container holding elements of same type we hold.
    typedef SharedPtr<IEnumerable<T> > IEnumerablePtr;
    /// Enumerator type.
    typedef SharedPtr<IEnumerator<T> > IEnumeratorPtr;

    /// Creates empty list.
    List() : ASPOSE_COLLECTION_INIT_ALLOCATOR() {}
    /// Creates list with pre-defined capacity.
    /// @param capacity Number of elements to reserve.
    /// @throw ArgumentOutOfRangeException if capacity is less than zero.
    List(int capacity) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        if (capacity < 0)
        {
            throw ArgumentOutOfRangeException(u"capacity");
        }
        m_data.reserve(capacity);
    }
    /// Copy constructor.
    /// @param collection Collection to copy data from.
    /// @throw ArgumentNullException if collection is nullptr.
    List(IEnumerablePtr collection) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        AddRange(collection);
        TrimExcess();
    }

    /// Adds elements to list; used when translating initializers.
    /// @param size Number of elements to insert.
    /// @param inits Elements to insert.
    void AddInitializer(int size, const T* inits)
    {
        m_data.reserve(m_data.size() + size);
        for (int i = 0; i < size; ++i)
            m_data.push_back(inits[i]);
    }

    /// Gets iterator to the first element of collection.
    /// @return An iterator pointing to the first element in the list.
    iterator begin() noexcept { return m_data.begin(); }
    /// Gets iterator for a non-existent element behind the end of the collection.
    /// @return An iterator pointing to the theoretical element placed after the end element in the list.
    iterator end() noexcept { return m_data.end(); }

    /// Gets iterator to the first element of the const-qualified collection.
    /// @return An iterator pointing to the first element in the const-qualified instance of the list.
    const_iterator begin() const noexcept { return m_data.begin(); }
    /// Gets iterator for a non-existent element behind the end of the const-qualified collection.
    /// @return An iterator pointing to the theoretical element placed after the end element in the const-qualified instance of the list.
    const_iterator end() const noexcept { return m_data.end(); }

    /// Gets iterator to the first const-qualified element of collection.
    /// @return An iterator pointing to the first const-qualified element in the list.
    const_iterator cbegin() const noexcept { return m_data.cbegin(); }
    /// Gets iterator for a non-existent const-qualified element behind the end of the collection.
    /// @return An iterator pointing to the theoretical const-qualified element placed after the end element in the list.
    const_iterator cend() const noexcept { return m_data.cend(); }

    /// Gets a reverse iterator to the last element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the list (first in reverse).
    reverse_iterator rbegin() noexcept { return m_data.rbegin(); }
    /// Gets a reverse iterator for a non-existent element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical element preceeding the first element in the list (last in reverse).
    reverse_iterator rend() noexcept { return m_data.rend(); }

    /// Gets a reverse iterator to the last element of the const-qualified collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the const-qualified list (first in reverse).
    const_reverse_iterator rbegin() const noexcept { return m_data.rbegin(); }
    /// Gets a reverse iterator for a non-existent element before the start of the const-qualified collection.
    /// @return A reverse iterator pointing to the theoretical element preceeding the first element in the const-qualified list (last in reverse).
    const_reverse_iterator rend() const noexcept { return m_data.rend(); }

    /// Gets a reverse iterator to the last const-qualified element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last const-qualified element in the list (first in reverse).
    const_reverse_iterator crbegin() const noexcept { return m_data.crbegin(); }
    /// Gets a reverse iterator for a non-existent const-qualified element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical const-qualified element preceeding the first element in the list (last in reverse). 
    const_reverse_iterator crend() const noexcept { return m_data.crend(); }

    // IEnumerable<T> interface
    /// Enumerator to iterate through list elements.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class Enumerator : public SimpleEnumerator<vector_t>
    {
    public:
        /// Creates enumerator iterating through specific list.
        /// @param data List to iterate through.
        Enumerator(const ThisPtr& data) : SimpleEnumerator<vector_t>(data, data->m_data) { }
        /// RTTI information.
        RTTI_INFO_TEMPLATE_CLASS(List<T>::Enumerator, System::BaseTypesInfo<System::Object>);
    };
    /// Gets enumerator to iterate through list elements.
    /// @return Pointer to newly created enumerator.
    IEnumeratorPtr GetEnumerator() override
    {
        return MakeObject<Enumerator>(std::move(MakeSharedPtr(this)));
    }

    // end of IEnumerable<T> interface

    // ICollection<T> interface
    /// Gets number of elements in current list.
    /// @return Actual number of elements.
    int get_Count() const override
    {
        return (int)m_data.size();
    }
    /// Adds element to the end of list.
    /// @param item Item to add.
    void Add(const T& item) override
    {
        m_data.push_back(item);
    }
    /// Deletes all elements.
    void Clear() override
    {
        m_data.clear();
    }
    /// Checks if item is present in list.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    bool Contains(const T& item) const override
    {
        return FindInData(m_data.begin(), m_data.end(), item) != m_data.end();
    }
    /// Removes first instance of specific item from list.
    /// @param item Item to remove.
    /// @return True if item was found and removed, false otherwise.
    bool Remove(const T& item) override
    {
        iterator it = FindInData(m_data.begin(), m_data.end(), item);
        if (it != m_data.end())
        {
            m_data.erase(it);
            return true;
        }
        return false;
    }

    //inherits get_IsReadOnly()
    /// Copies list elements into existing array elements.
    /// @param array Destination array.
    /// @param arrayIndex Destination array starting index.
    void CopyTo(System::ArrayPtr<T> array, int arrayIndex) override
    {
        this->CopyTo(0, array, arrayIndex, ASPOSECPP_CHECKED_CAST(int, m_data.size()));
    }

    // end of ICollection<T> interface

    // IList<T> interface
    /// Gets first index of specific item.
    /// @param item Item to look for.
    /// @return Index of first occurance of specified item or -1 if not found.
    int IndexOf(const T& item) const override
    {
        const_iterator it = FindInData(m_data.begin(), m_data.end(), item);
        if (it != m_data.end())
        {
            return ASPOSECPP_CHECKED_CAST(int, it - m_data.begin());
        }

        return -1;
    }
    /// Inserts item at specified position.
    /// @param index Index to insert item into.
    /// @param item Item to insert.
    void Insert(int index, const T& item) override
    {
        if (index < 0 || static_cast<size_t>(index) > m_data.size()) {
            throw ArgumentOutOfRangeException(u"index");
        }

        m_data.insert(m_data.begin() + index, item);
    }
    /// Removes item at specified position.
    /// @param index Index to delete item at.
    void RemoveAt(int index) override
    {
        if (Details::IsOutOfBounds(index, m_data)) {
            throw ArgumentOutOfRangeException(u"index");
        }
        m_data.erase(m_data.begin() + index);
    }

    /// Gets element at specific position.
    /// @param index Index to get element from.
    /// @return Copy of element at specified position.
    T idx_get(int index) const override
    {
        return operator[](index);
    }
    /// Sets element at specific position.
    /// @param index Index to set element at.
    /// @param value Value to set to specified position.
    void idx_set(int index, T value) override
    {
        operator[](index) = value;
    }

    // end of IList<T> interface
    /// Gets current list capacity.
    /// @return Capacity (not size) of the list.
    int get_Capacity() const
    {
        return (int)m_data.capacity();
    }
    /// Sets list capacity.
    /// @param capacity Capacity to set (can't be less than current size).
    void set_Capacity(int capacity)
    {
        if (capacity < (int)m_data.size()) {
            throw ArgumentOutOfRangeException(u"capacity");
        }
        m_data.reserve(capacity);
    }

    /// Adds all elements from collection (or itself) to the end of current list.
    /// @param collection Collection to copy elements from.
    /// @throw ArgumentNullException if collection is nullptr.
    void AddRange(IEnumerablePtr collection)
    {
        InsertRange(static_cast<int>(m_data.size()), collection);
    }

    /// Gets read-only reference to this collection.
    /// @return Newly created read-only wrapper around current list.
    SharedPtr<System::Collections::ObjectModel::ReadOnlyCollection<T>> AsReadOnly()
    {
        return MakeObject<System::Collections::ObjectModel::ReadOnlyCollection<T>>(this);
    }

    /// Looks for item in a sorted list.
    /// @param item Item to look for.
    /// @return Index of the item in sorted list or complement of closest index.
    int BinarySearch(const T &item) const
    {
        return _net_binnary_search(m_data, 0, ASPOSECPP_CHECKED_CAST(int, m_data.size()), item);
    }
    /// Looks for item in a sorted list.
    /// @param item Item to look for.
    /// @param comparer Comparer to use.
    /// @return Index of the item in sorted list or complement of closest index.
    int BinarySearch(const T &item, const SharedPtr<System::Collections::Generic::IComparer<T> >& comparer) const
    {
        return _net_binnary_search(m_data, 0, ASPOSECPP_CHECKED_CAST(int, m_data.size()), item, comparer);
    }
    /// Looks for item in a sorted list.
    /// @param index Range beginning.
    /// @param count Range size.
    /// @param item Item to look for.
    /// @param comparer Comparer to use.
    /// @return Index of the item in sorted list or complement of closest index.
    int BinarySearch(int index, int count, const T &item, const SharedPtr<System::Collections::Generic::IComparer<T> >& comparer) const
    {
        if (index < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)) {
            throw ArgumentException(u"index or count");
        }

        return _net_binnary_search(m_data, index, count, item, comparer);
    }

    /// Creates a list of elements converted to different type.
    /// @tparam OutputType Output list element type.
    /// @param converter Converter to use for items conversion.
    /// @return A newly created list of converted elements.
    template <typename OutputType>
    SharedPtr<List<OutputType>> ConvertAll(Converter<T, OutputType> converter)
    {
        if (converter.IsNull()) {
            throw System::ArgumentNullException(u"converter");
        }
        SharedPtr<List<OutputType>> res = System::MakeObject<List<OutputType>>((int)m_data.size());
        for (size_t i = 0; i < m_data.size(); i++) {
            res->Add(converter(m_data[i]));
        }
        return res;
    }

    /// Copies all elements into existing array elements.
    /// @param array Array to copy elements into.
    void CopyTo(const System::ArrayPtr<T>& array)
    {
        this->CopyTo(0, array, 0, ASPOSECPP_CHECKED_CAST(int, m_data.size()));
    }
    /// Copies elements starting from the specified index into existing array elements.
    /// @param index A 0-based index of the element in the list represented by the current object to start
    /// copying from
    /// @param array Array to copy elements into.
    /// @param arrayIndex Beginning position in desitnation array.
    /// @param count Number of elements to copy.
    void CopyTo(int index, const System::ArrayPtr<T>& array, int arrayIndex, int count)
    {
        if (!array) {
            throw ArgumentNullException(u"array");
        }

        if (index < 0 || arrayIndex < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index, arrayIndex or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)
            || Details::IsOutOfSize(arrayIndex + count, array->data()) ) {
            throw ArgumentException(u"index, arrayIndex or count");
        }

        std::copy(m_data.begin() + index, m_data.begin() + index + count, array->data().begin() + arrayIndex);
    }

    /// Checks if element adhering to specific predicate exists in list.
    /// @param match Predicate to check elements with.
    /// @return True if matching element is found, false otherwise.
    bool Exists(System::Predicate<T> match)
    {
        if (match.IsNull()) {
            throw ArgumentNullException(u"match");
        }
        return FindIndex(match) != -1;
    }
    /// Looks for element adhering to specific predicate.
    /// @param predicate Predicate to check elements with.
    /// @return Value of matching element or nullprtr if not found.
    T Find(System::Predicate<T> predicate)
    {
        if (predicate.IsNull()) {
            throw ArgumentNullException(u"predicate");
        }
        for (iterator it = m_data.begin(); it != m_data.end(); ++it)
        {
            if (predicate(*it))
                return (*it);
        }
        return  System::Default<T>();
    }
    /// Looks for elements adhering to specific predicate.
    /// @param match Predicate to check elements with.
    /// @return List of matching elements (if any) or empty list.
    ListPtr<T> FindAll(System::Predicate<T> match)
    {
        if (match.IsNull()) {
            throw ArgumentNullException(u"match");
        }
        ListPtr<T> list = MakeObject<List<T>>();
        for (iterator it = m_data.begin(); it != m_data.end(); ++it)
        {
            if (match(*it))
                list->Add(*it);
        }
        return list;
    }
    /// Looks for element adhering to specific predicate.
    /// @param match Predicate to check elements with.
    /// @return Index of matching element or -1 if not found.
    int FindIndex(System::Predicate<T> match)
    {
        return FindIndex(0, ASPOSECPP_CHECKED_CAST(int, m_data.size()), match);
    }
    /// Looks for element adhering to specific predicate.
    /// @param startIndex Index to start search from.
    /// @param match Predicate to check elements with.
    /// @return Index of matching element or -1 if not found.
    int FindIndex(int startIndex, System::Predicate<T> match)
    {
        return FindIndex(startIndex, ASPOSECPP_CHECKED_CAST(int, m_data.size()) - startIndex, match);
    }
    /// Looks for element adhering to specific predicate.
    /// @param startIndex Index to start search from.
    /// @param count Number of elements to look through.
    /// @param match Predicate to check elements with.
    /// @return Index of matching element or -1 if not found.
    int FindIndex(int startIndex, int count, System::Predicate<T> match)
    {
        if (match.IsNull()) {
            throw ArgumentNullException(u"match");
        }

        if (count < 0 || startIndex < 0
            || Details::IsOutOfSize(startIndex + count, m_data))
        {
            throw ArgumentOutOfRangeException(u"startIndex or count");
        }

        if (m_data.empty()) {
            return -1;
        }

        int const num = startIndex + count;
        for (int index = startIndex; index < num; ++index)
        {
            auto& item = m_data[index];
            if (match(item)) {
                return index;
            }
        }
        return -1;
    }
    /// Looks for last element adhering to specific predicate.
    /// @param match Predicate to check elements with.
    /// @return Value of matching element or nullptr if not found.
    T FindLast(System::Predicate<T> match)
    {
        if (match.IsNull()) {
            throw ArgumentNullException(u"match");
        }
        T res = System::Default<T>();
        for (iterator it = m_data.begin(); it != m_data.end(); ++it)
        {
            if (match(*it))
                res = (*it);
        }
        return res;
    }

    /// Applies action to all elements in list.
    /// @param action Action to apply.
    void ForEach(System::Action<T> action)
    {
        if (action.IsNull()) {
            throw ArgumentNullException(u"action");
        }
        auto data_size = m_data.size();
        for (iterator it = m_data.begin(); it != m_data.end(); ++it)
        {
            action(*it);
            if (m_data.size() != data_size)
            {
                throw InvalidOperationException();
            }
        }
    }

    /// Creates slice of list.
    /// @param index Range start index.
    /// @param count Range size.
    /// @return List containing a slice of current list.
    ThisPtr GetRange(int index, int count)
    {
        if (index < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)) {
            throw ArgumentException(u"index or count");
        }

        ThisPtr rv = MakeObject<List<T> >(count);
        for (auto i = index; i < (index + count); ++i)
        {
            rv->m_data.push_back(m_data[i]);
        }

        return rv;
    }

    /// Looks for specific item in list.
    /// @param item Item to look for.
    /// @param index Index to start lookup at.
    /// @return Index of first instance of specified item or -1 if not found.
    int IndexOf(const T& item, int index) const
    {
        if (Details::IsOutOfBounds(index, m_data)) {
            throw ArgumentOutOfRangeException(u"index");
        }
        auto it = FindInData(m_data.begin() + index, m_data.end(), item);
        if (it != m_data.end())
        {
            return ASPOSECPP_CHECKED_CAST(int, it - m_data.begin());
        }

        return -1;
    }

    /// Inserts data range at specific position.
    /// @param index Index to insert data at.
    /// @param collection Collection of elements to insert.
    /// @throw ArgumentOutOfRangeException if index is less than zero.
    /// @throw ArgumentNullException if collection is nullptr.
    void InsertRange(int index, IEnumerablePtr collection)
    {
        if (!collection) {
            throw ArgumentNullException(u"collection");
        }

        if (index < 0 || static_cast<size_t>(index) > m_data.size()) {
            throw ArgumentOutOfRangeException(u"index");
        }

        if (collection.GetObjectOrNull() == this) {
            m_data.reserve(m_data.size() * 2);
            m_data.insert(m_data.begin() + index, m_data.begin(), m_data.end());
        }
        else
        {
            IEnumeratorPtr it = collection->GetEnumerator();
            while (it->MoveNext())
            {
                m_data.insert(m_data.begin() + index++, it->Current());
            }
        }
    }

    /// Searches for the specified object and returns the zero-based index of the last occurrence within the entire list
    /// @param item The object to locate in the list
    /// @return The zero-based index of the last occurrence of item within the entire the List, if found; otherwise, -1.
    int32_t LastIndexOf(const T& item) const
    {
        auto rit = FindInData(m_data.rbegin(), m_data.rend(), item);
        if (rit != m_data.rend())
        {
            return ASPOSECPP_CHECKED_CAST(int, rit.base() - m_data.begin() - 1);
        }

        return -1;
    }
    
    /// Searches for the specified object and returns the zero-based index of the last occurrence within the range of elements
    /// in the List that extends from the first element to the specified index.
    /// @param item The object to locate in the list
    /// @param index The zero-based starting index of the backward search.
    /// @return The zero-based index of the last occurrence of item within the range of elements in the List that extends 
    /// from the first element to index, if found; otherwise, -1.
    int32_t LastIndexOf(const T& item, int32_t index) const
    {
        using namespace Collections::Generic::Details;
        if (index < 0 || IsOutOfBounds(index, m_data))
        {
            throw ArgumentOutOfRangeException(u"startIndex or count");
        }

        auto rbegin = m_data.rbegin() + m_data.size() - index - 1;
        auto rend = m_data.rend();
        auto rit = FindInData(rbegin, rend, item);
        if (rit != rend)
        {
            return ASPOSECPP_CHECKED_CAST(int, rit.base() - m_data.begin()) - 1;
        }
        return -1;
    }

    /// Searches for the specified object and returns the zero-based index of the last occurrence within the range of elements
    /// in the List that contains the specified number of elements and ends at the specified index.
    /// @param item The object to locate in the List
    /// @param index The zero-based starting index of the backward search.
    /// @param count The number of elements in the section to search.
    /// @return The zero-based index of the last occurrence of item within the range of elements in the List that contains 
    /// count number of elements and ends at index, if found; otherwise, -1.
    int32_t LastIndexOf(const T& item, int32_t index, int32_t count) const
    {
        using namespace Collections::Generic::Details;
        if (index < 0 || count < 0
                || IsOutOfBounds(index, m_data) || IsOutOfSize(count, m_data)
                || (index - count + 1) < 0)
        {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        auto rbegin = m_data.rbegin() + m_data.size() - index - 1;
        auto rend = rbegin + count;
        auto rit = FindInData(rbegin, rend, item);

        if (rit != rend)
        {
            return ASPOSECPP_CHECKED_CAST(int, rit.base() - m_data.begin()) - 1;
        }
        return -1;
    }

    /// Removes all elements matching specific predicate.
    /// @param match Predicate to check elements with.
    /// @return Number of removed elements.
    int RemoveAll(Predicate<T> match)
    {
        if (match.IsNull()) {
            throw ArgumentNullException(u"match");
        }

        typename vector_t::size_type removed = 0;

        for (typename vector_t::size_type index = 0; index < m_data.size(); )
        {
            if (match(m_data[index]))
            {
                m_data.erase(m_data.begin() + index);
                ++removed;
            }
            else
            {
                ++index;
            }
        }

        return ASPOSECPP_CHECKED_CAST(int, removed);
    }
    /// Removes slice of list.
    /// @param index Slice beginning position.
    /// @param count Number of elements to remove.
    void RemoveRange(int index, int count)
    {
        if (index < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)) {
            throw ArgumentException(u"index or count");
        }

        m_data.erase(m_data.begin() + index, m_data.begin() + index + count);
    }
    /// Reverses elements order of the whole list.
    void Reverse()
    {
        std::reverse(m_data.begin(), m_data.end());
    }
    /// Reverses elements order of the list slice.
    /// @param index Slice beginning index.
    /// @param count Slice size.
    void Reverse(int index, int count)
    {
        if (index < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)) {
            throw ArgumentException(u"index or count");
        }

        std::reverse(m_data.begin() + index, m_data.begin() + index + count);
    }
    /// Sorts elements in the list.
    /// @param comparator Comparator to use.
    void Sort(const SharedPtr<System::Collections::Generic::IComparer<T> >& comparator)
    {
        ComparerAdapter<T> adapter(comparator);
        std::sort(m_data.begin(), m_data.end(), adapter);
    }
    /// Sorts elements in the list using default comparator.
    void Sort()
    {
        std::sort(m_data.begin(), m_data.end(), Details::ComparerType<ValueType>());
    }
    /// Sorts elements in the list slice.
    /// @param index Slice beginning index.
    /// @param count Slice size.
    /// @param comparator Comparator to use.
    void Sort(int index, int count, SharedPtr<System::Collections::Generic::IComparer<T> > comparator)
    {
        if (index < 0 || count < 0) {
            throw ArgumentOutOfRangeException(u"index or count");
        }

        if (Details::IsOutOfSize(index + count, m_data)) {
            throw ArgumentException(u"index or count");
        }

        ComparerAdapter<T> adapter(comparator);
        std::sort(m_data.begin() + index, m_data.begin() + index + count, adapter);
    }
    /// Sorts elements in the list.
    /// @param comparison Comparison to use.
    void Sort(Comparison<T> comparison, bool) //second (bool) param to solve ambiguous call issue
    {
        if (comparison.IsNull()) {
            throw ArgumentNullException(u"comparison");
        }
        std::sort(m_data.begin(), m_data.end(), comparison);
    }

    /// Converst list to array.
    /// @return Newly created array with copies of all elements.
    ArrayPtr<T> ToArray() const
    {
        typename vector_t::size_type size = m_data.size();
        auto result = MakeObject<Array<T> >(ASPOSECPP_CHECKED_CAST(int, size));
        std::copy(m_data.begin(), m_data.end(), result->data().begin());

        return result;
    }
    /// Makes list capacity to fit its size.
    void TrimExcess()
    {
        m_data.shrink_to_fit();
    }

    /// Determines whether every element in the collection matches the conditions defined by the specified predicate.
    /// @param match Predicate to check elements with.
    /// @return True if every element matches the conditions, false otherwise.
    bool TrueForAll(System::Predicate<T> match)
    {
        if (match.IsNull())
        {
            throw ArgumentNullException(u"match");
        }
        for (iterator it = m_data.begin(); it != m_data.end(); ++it)
        {
            if (!match(*it))
                return false;
        }
        return true;
    }

    /// Accessor function.
    /// @param index Index to get element from.
    /// @return Reference to element at specified position.
    typename vector_t::reference operator[](int index)
    {
        if (Details::IsOutOfBounds(index, m_data)) {
            throw ArgumentOutOfRangeException(u"index");
        }
        return m_data[static_cast<typename vector_t::size_type>(index)];
    }
    /// Accessor function.
    /// @param index Index to get element from.
    /// @return Const reference to element at specified position.
    typename vector_t::const_reference operator[](int index) const
    {
        if (Details::IsOutOfBounds(index, m_data)) {
            throw ArgumentOutOfRangeException(u"index");
        }
        return m_data[static_cast<typename vector_t::size_type>(index)];
    }

    /// Underlying data structure access function.
    /// @return Reference to underlying vector.
    vector_t& data() { return m_data; }
    /// Underlying data structure access function.
    /// @return Const reference to underlying vector.
    const vector_t& data() const { return m_data; }
    /// C++ specific
    /// @param list Range to insert into container.
    void _add_range(std::initializer_list<T> list)
    {
        std::for_each(list.begin(), list.end(), [this](const T &v) { m_data.push_back(v); });
    }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, iterator>(begin(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, iterator>(end(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, const_iterator>(begin(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, const_iterator>(end(), end());
    }

private:
    /// Data lookup function implementation for the types containing IsEqual method.
    /// @tparam Item type, same as @p T.
    /// @tparam I Iterator type.
    /// @param begin Range beginning.
    /// @param end Range end.
    /// @param item Item to look for.
    /// @return Iterator to found item or end if not found.
    template <typename Q, typename I>
    typename std::enable_if<Details::IsEqualExist<Q>::value, I>::type FindInData(I begin, I end, const Q &item) const
    {
        return std::find(begin, end, item);
    }
    /// Data lookup function implementation for the types not containing IsEqual method. Not implemented.
    /// @tparam Item type, same as @p T.
    /// @tparam I Iterator type.
    /// @param begin Range beginning.
    /// @param end Range end.
    /// @param item Item to look for.
    /// @return Iterator to found item or end if not found.
    template <typename Q, typename I>
    typename std::enable_if<!Details::IsEqualExist<Q>::value, I>::type FindInData(I begin, I end, const Q &item) const
    {
        throw System::NotImplementedException(ASPOSE_CURRENT_FUNCTION);
    }
    /// Data lookup function implementation for pointer types.
    /// @tparam Pointee type.
    /// @tparam I Iterator type.
    /// @param begin Range beginning.
    /// @param end Range end.
    /// @param item Item to look for.
    /// @return Iterator to found item or end if not found.
    template <typename Q, typename I>
    I FindInData(I begin, I end, const System::SharedPtr<Q> &item) const
    {
        return std::find_if(begin, end, [&item](const System::SharedPtr<Q> &element)
        {
            return element == nullptr ? item == nullptr : element.ToObjectPtr()->Equals(item.ToObjectPtr());
        });
    }

protected:
    /// Destructor.
    ~List() override {}

#ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to container and elements.
        /// @param visitor Visitor to apply.
        void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
        {
            visitor.add_self(this);
            DBG::for_each_of_Object(this, m_data, visitor);
        }

        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "List<T>"; }
#endif

#ifdef ASPOSE_GET_SHARED_MEMBERS
    DEFINE_GET_SHARED_MEMBERS(m_data)
#endif
};

}}} // namespace System::Collections::Generic
