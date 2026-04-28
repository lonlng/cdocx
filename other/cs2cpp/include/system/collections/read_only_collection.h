/// @file system/collections/read_only_collection.h
#ifndef _aspose_system_collection_read_only_collection_h_
#define _aspose_system_collection_read_only_collection_h_

#include <system/diagnostics/debug.h>

#include "fwd.h"
#include "system/object.h"
#include "system/collections/ilist.h"
#include "system/exceptions.h"
#include "system/cycles_detection.h"
#include "system/array.h"

namespace System {
namespace Collections {
namespace ObjectModel {

/// Wraps specific container to access it in read-only mode.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS ReadOnlyCollection
    : virtual public Object
    , public Generic::IList<T>
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(ReadOnlyCollection<T>, System::BaseTypesInfo<System::Object>);

protected:
    /// This pointer.
    typedef SharedPtr<ReadOnlyCollection<T>> ThisPtr;
    /// Wrapped container.
    SharedPtr<Generic::IList<T>> m_list;

public:
    /// Value type.
    typedef T ValueType;
    /// Implemented interface.
    typedef Generic::IList<T> BaseType;

public:
    /// Container of same elements.
    typedef SharedPtr<System::Collections::Generic::IEnumerator<T>> IEnumeratorPtr;

    /// Wraps read-only collection around specific collection.
    /// @param list Collection to wrap.
    ReadOnlyCollection(const SharedPtr<Generic::IList<T>>& list)
    {
        if (!list)
            throw System::ArgumentNullException(u"list");

        m_list = list;
    }

    /// Gets collection enumerator.
    /// @return Pointer to newly created enumerator.
    virtual IEnumeratorPtr GetEnumerator()  override
    {
        return m_list->GetEnumerator();
    }

    /// Gets count of container elements.
    /// @return Actual elements count.
    virtual int get_Count() const override
    {
        return m_list->get_Count();
    }

    /// Checks if collection is read only.
    /// @return true for a read only collection.
    bool get_IsReadOnly() const override { return true; }

    /// Checks if container contains specific item.
    /// @param item Item to look for.
    /// @return true if item is found, false otherwise.
    virtual bool Contains(const T& item) const override
    {
        return m_list->Contains(item);
    }
    /// Looks for specific item in collection.
    /// @param item Item to look for.
    /// @return Index of the first occurrence of specified item or negative value if not found.
    virtual int IndexOf(const T& item) const override
    {
        return m_list->IndexOf(item);
    }

    /// Gets item at specific position.
    /// @param index Index to get element from.
    /// @return Copy of element at specified position.
    virtual T idx_get(int index) const override
    {
        return m_list->idx_get(index);
    }

    /// Copies container elements to existing array elements.
    /// @param array Destination array.
    /// @param index Destination array beginning index.
    virtual void CopyTo(System::ArrayPtr<T> array, int index) override
    {
        m_list->CopyTo(array, index);
    }

    /// Does nothing as read-only collection only wraps data and stores nothing.
    void SetTemplateWeakPtr(uint32_t argument) override
    {
        CODEPORTING_DEBUG_ASSERT(!"ReadOnlyCollection is a wrapper and doesn't own any data, so it can't be used to store weak pointers if referenced container stores shared ones");
    }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return m_list->virtualizeBeginIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return m_list->virtualizeEndIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return m_list->virtualizeBeginConstIterator();
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return m_list->virtualizeEndConstIterator();
    }

protected:
    /// Destructor.
    ~ReadOnlyCollection() override {}

private:
    /// Adds element to collection; inapplicable to ReadOnlyCollection.
    virtual void Add(const T& item) override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Deletes all elements from collection; inapplicable to ReadOnlyCollection.
    virtual void Clear() override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Removes element from collection; inapplicable to ReadOnlyCollection.
    virtual bool Remove(const T& item) override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Removes element from collection; inapplicable to ReadOnlyCollection.
    void RemoveAt(int index) override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Inserts element to collection; inapplicable to ReadOnlyCollection.
    virtual void Insert(int index, const T& item) override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Accesses collection's element; inapplicable to ReadOnlyCollection.
    virtual T& operator[](int index)
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }
    /// Sets collection's element; inapplicable to ReadOnlyCollection.
    virtual void idx_set(int index, T value) override
    {
        throw NotSupportedException(u"Operation not supported on read-only collection");
    }

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Allows loop references detection for ReadOnlyCollection.
    virtual void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        Object::GetSharedMembers(result);
        result.Add("System::Collections::ObjectModel::ReadOnlyCollection<T>::m_list[]", m_list);
    }
#endif

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to collection and elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
    {
        Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
        visitor.add_member(this, m_list.get_shared(), "m_list");
    }

    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "ReadOnlyCollection<T>"; }
#endif
};


} // namespace ObjectModel
} // namespace Collections
} // namespace System

#endif // _aspose_system_collection_read_only_collection_h_
