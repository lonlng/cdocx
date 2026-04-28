#pragma once
#include <system/object_ext.h>
#include <system/collections/ilist_ng.h>
#include <system/collections/ienumerator_impl.h>

namespace System {
namespace Collections {

/// Stub that implements System::Collections::IList interface on System::Collections::Generic::List object
/// Implementation for reference types
template <typename T>
class ASPOSECPP_SHARED_CLASS IListImplRefType : virtual public System::Collections::IList
{
public:
    /// Creates new object instance
    /// @param list generic collection to wrap
    IListImplRefType(System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<T>>> list) : m_list(list)
    {};

    /// Converting object value into partucular type reference
    static System::SharedPtr<T> UnboxValue(System::SharedPtr<System::Object> value)
    {
        return System::ExplicitCast<T>(value);
    }

    /// Converting type reference into object value into object
    static System::SharedPtr<System::Object> BoxValue(System::SharedPtr<T> value)
    {
        return (value);
    }

    /// Gets the element at the specified index.
    /// @param index index of the element
    /// @param dummy fake param to help resolve disambiguity
    virtual SharedPtr<System::Object>  idx_get(int index, int dummy = 0) const override
    {
        return BoxValue(m_list->idx_get(index));
    }

    /// Inserts element into specified position, shifting other elements.
    /// @param index Index to insert elements onto.
    /// @param value Item to insert at specified index.
    virtual void Insert(int index, System::SharedPtr<System::Object> value) override
    {
        m_list->Insert(index, UnboxValue(value));
    }

    /// Gets index of first appearance of item in container.
    /// @param value Item to look for.
    /// @return Index of first appearance of item in container or -1 if not found.
    virtual int IndexOf(System::SharedPtr<System::Object> value) const override
    {
        return m_list->IndexOf(UnboxValue(value));
    }

    /// Removes item at specified position.
    /// @param index Index to delete item at.
    virtual void RemoveAt(int index) override
    {
        m_list->RemoveAt(index);
    }

    /// Adds element to the end of list.
    /// @param item Item to add.
    virtual int Add(SharedPtr<System::Object> item) override
    {
        m_list->Add(UnboxValue(item));
        return m_list->get_Count() - 1;
    }

    /// Deletes all elements.
    virtual void Clear() override
    {
        m_list->Clear();
    }

    /// Checks if item is present in list.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    virtual bool Contains(SharedPtr<System::Object> item) const override
    {
        return m_list->Contains(UnboxValue(item));
    }

    /// Removes first instance of specific item from list.
    /// @param item Item to remove.
    virtual void Remove(SharedPtr<System::Object> item) override
    {
        m_list->Remove(UnboxValue(item));
    }

    /// ICollection.get_Count() methods implementation
    /// Gets number of elements in collection.
    /// @return Number of elements.
    virtual int get_Count() const override
    {
        return m_list->get_Count();
    }

    /// IEnumerable.GetEnumerator() implementation
    /// Returns an enumerator that iterates through a collection.
    virtual SharedPtr<System::Collections::IEnumerator> GetEnumerator() override
    {
        return System::MakeObject<System::Collections::IEnumeratorImplRefType<T>>(m_list->GetEnumerator());
    }

private:
    System::SharedPtr<System::Collections::Generic::List<System::SharedPtr<T>>> m_list;
};

/// Stub that implements System::Collections::IList interface on System::Collections::Generic::List object
/// Implementation for value types
template <typename T>
    class IListImplValueType : virtual public System::Collections::IList
{
public:
    /// Creates new object instance
    /// @param list generic collection to wrap
    IListImplValueType(System::SharedPtr<System::Collections::Generic::IList<T>> list)
        : m_list(list)
    {}

    /// Gets the element at the specified index.
    /// @param index index of the element
    /// @param dummy fake param to help resolve disambiguity
    virtual SharedPtr<System::Object>  idx_get(int index, int dummy = 0) const override
    {
        return ObjectExt::Box(m_list->idx_get(index));
    }

    /// Inserts element into specified position, shifting other elements.
    /// @param index Index to insert elements onto.
    /// @param value Item to insert at specified index.
    virtual void Insert(int index, System::SharedPtr<System::Object> value) override
    {
        m_list->Insert(index, ObjectExt::Unbox<T>(value));
    }

    /// Gets index of first appearance of item in container.
    /// @param value Item to look for.
    /// @return Index of first appearance of item in container or -1 if not found.
    virtual int IndexOf(System::SharedPtr<System::Object> value) const override
    {
        return m_list->IndexOf(ObjectExt::Unbox<T>(value));
    }

    /// Removes item at specified position.
    /// @param index Index to delete item at.
    virtual void RemoveAt(int index) override
    {
        m_list->RemoveAt(index);
    }

    /// Adds element to the end of list.
    /// @param item Item to add.
    int Add(SharedPtr<System::Object> item) override
    {
        m_list->Add(ObjectExt::Unbox<T>(item));
        return m_list->get_Count() - 1;
    }

    /// Deletes all elements.
    virtual void Clear() override
    {
        m_list->Clear();
    }

    /// Checks if item is present in list.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    virtual bool Contains(SharedPtr<System::Object> item) const override
    {
        return m_list->Contains(ObjectExt::Unbox<T>(item));
    }

    /// Removes first instance of specific item from list.
    /// @param item Item to remove.
    virtual void Remove(SharedPtr<System::Object> item) override
    {
        m_list->Remove(ObjectExt::Unbox<T>(item));
    }

    /// ICollection.get_Count() methods implementation
    /// Gets number of elements in collection.
    /// @return Number of elements.
    virtual int get_Count() const override
    {
        return m_list->get_Count();
    }

    /// IEnumerable.GetEnumerator() implementation
    /// Returns an enumerator that iterates through a collection.
    virtual SharedPtr<System::Collections::IEnumerator> GetEnumerator() override
    {
        return System::MakeObject<System::Collections::IEnumeratorImplValueType<T>>(m_list->GetEnumerator());
    }

private:
    System::SharedPtr<System::Collections::Generic::IList<T>> m_list;
};

}} // namespace System::Collections
