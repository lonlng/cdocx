#pragma once

#include <system/scope_guard.h>
#include <system/exceptions.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/collections/list.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>


namespace System {

namespace Collections {

/// Provides an abstract base class for a strongly typed collection.
/// @tparam T Type of elements of the collection
template<typename T>
class CollectionBase : public virtual Generic::IEnumerable<T>
{
    typedef CollectionBase<T> ThisType;
    typedef Generic::IEnumerable<T> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<CollectionBase>;

    /// Provides an interface for accessing the elements in the collection.
    class ASPOSECPP_SHARED_CLASS ListImpl : public System::Object
    {
        typedef ListImpl ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

    public:

        /// An alias for shared pointer to an instance of this class.
        using Ptr = SharedPtr<ListImpl>;

    private:
        /// @cond
        template<typename FT0> friend class CollectionBase;
        /// @endcond

    public:

        /// Copies the entire collection to a compatible one-dimensional Array,
        /// starting at the specified index of the target array.
        /// @param array The one-dimensional Array that is the destination of the elements copied from the collection.
        /// The Array must have zero-based indexing.
        /// @param index The zero-based index in @p array at which copying begins.
        /// @throws ArgumentNullException @p array is @c nullptr.
        /// @throws ArgumentOutOfRangeException @p index is less than zero.
        /// @throws ArgumentException @p array is multidimensional.
        /// -or-
        /// The number of elements in the collection is greater than the available space
        /// from @p index to the end of the destination @p array.
        ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<T>& array, int32_t index)
        {
            _base->get_InnerList()->CopyTo(array, index);
        }

        /// Returns the element at the specified index.
        /// @param index The zero-based index of the element to get or set.
        /// @returns The element at the specified index.
        /// @throws ArgumentOutOfRangeException @p index is less than zero.
        /// -or-
        /// @p index is equal to or greater than CollectionBase::get_Count.
        ASPOSECPP_SHARED_API T idx_get(int32_t index)
        {
            if (index < 0 || index >= _base->get_Count())
            {
                throw ArgumentOutOfRangeException(u"index");
            }

            return _base->get_InnerList()->idx_get(index);
        }

        /// Sets the element at the specified index.
        /// @param index The zero-based index of the element to get or set.
        /// @param value The element to set.
        /// @throws ArgumentOutOfRangeException @p index is less than zero.
        /// -or-
        /// @p index is equal to or greater than CollectionBase::get_Count.
        ASPOSECPP_SHARED_API void idx_set(int32_t index, T value)
        {
            if (index < 0 || index >= _base->get_Count())
            {
                throw ArgumentOutOfRangeException(u"index");
            }

            _base->OnValidate(value);
            T temp = _base->get_InnerList()->idx_get(index);
            _base->OnSet(index, temp, value);
            _base->get_InnerList()->idx_set(index, value);
            try
            {
                _base->OnSetComplete(index, temp, value);
            }
            catch (...)
            {
                _base->get_InnerList()->idx_set(index, temp);
                throw;
            }

        }

        /// Determines whether the collection contains a specific element.
        /// @param value The element to locate in the collection.
        /// @returns @c true if the collection contains the specified @p value; otherwise, @c false.
        ASPOSECPP_SHARED_API bool Contains(const T& value)
        {
            return _base->get_InnerList()->Contains(value);
        }

        /// Adds a element to the end of the collection.
        /// @param value The element to be added to the end of the collection.
        /// @returns The collection index at which the @p value has been added.
        /// @throws NotSupportedException The collection is read-only.
        /// -or-
        /// The collection has a fixed size.
        ASPOSECPP_SHARED_API int32_t Add(const T& value)
        {
            _base->OnValidate(value);
            _base->OnInsert(_base->get_InnerList()->get_Count(), value);
            _base->get_InnerList()->Add(value);
            int32_t index = _base->get_InnerList()->get_Count() - 1;
            try
            {
                _base->OnInsertComplete(index, value);
            }
            catch (...)
            {
                _base->get_InnerList()->RemoveAt(index);
                throw;
            }

            return index;
        }

        /// Removes the first occurrence of a specific element from the collection.
        /// @param value The element to remove from the collection.
        /// @throws ArgumentException The @p value parameter was not found in the collection.
        /// @throws NotSupportedException The collection is read-only.
        /// -or-
        /// The collection has a fixed size.
        ASPOSECPP_SHARED_API void Remove(const T& value)
        {
            _base->OnValidate(value);
            int32_t index = _base->get_InnerList()->IndexOf(value);
            if (index < 0)
            {
                throw ArgumentException();
            }
            _base->OnRemove(index, value);
            _base->get_InnerList()->RemoveAt(index);
            try
            {
                _base->OnRemoveComplete(index, value);
            }
            catch (...)
            {
                _base->get_InnerList()->Insert(index, value);
                throw;
            }

        }

        /// Searches for the specified element and returns the zero-based index of
        /// the first occurrence within the entire collection.
        /// @param value The element to locate in the collection.
        /// @returns The zero-based index of the first occurrence of @p value within the entire collection, if found;
        /// otherwise, -1.
        ASPOSECPP_SHARED_API int32_t IndexOf(const T& value)
        {
            return _base->get_InnerList()->IndexOf(value);
        }

        /// Inserts an element into the collection at the specified index.
        /// @param index The zero-based index at which @p value should be inserted.
        /// @param value The element to insert.
        /// @throws ArgumentOutOfRangeException @p index is less than zero.
        /// -or-
        /// @p index is greater than CollectionBase::Count.
        /// @throws NotSupportedException The collection is read-only.
        /// -or-
        /// The collection has a fixed size.
        ASPOSECPP_SHARED_API void Insert(int32_t index, const T& value)
        {
            if (index < 0 || index > _base->get_Count())
            {
                throw ArgumentOutOfRangeException(u"index");
            }

            _base->OnValidate(value);
            _base->OnInsert(index, value);
            _base->get_InnerList()->Insert(index, value);
            try
            {
                _base->OnInsertComplete(index, value);
            }
            catch (...)
            {
                _base->get_InnerList()->RemoveAt(index);
                throw;
            }

        }


    protected:

        /// @cond
        virtual ASPOSECPP_SHARED_API ~ListImpl()
        {
        }

        ListImpl(const SharedPtr<CollectionBase<T>>& base_)
            : _base(base_.get())
        {
        }

        MEMBER_FUNCTION_MAKE_OBJECT(ListImpl, CODEPORTING_ARGS(const SharedPtr<CollectionBase<T>>& base_), CODEPORTING_ARGS(base_));

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override
        {
            System::Object::GetSharedMembers(result);

            result.Add("System::Collections::CollectionBase::ListImpl::_base", this->_base);
        }
        #endif
        /// @endcond

        #ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to members.
        /// @param visitor Visitor to apply.
        ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
        {
            System::Object::DBG_for_each_member(visitor);

            visitor.add_self(this);

            visitor.add_member(this, _base, "_base");
        }
        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "ListImpl"; }
    #endif

    private:

        CollectionBase<T>* const _base;

    };


public:

    /// Returns the number of elements that the collection can contain.
    /// @returns The number of elements that the collection can contain.
    int32_t get_Capacity()
    {
        return get_InnerList()->get_Capacity();
    }

    /// Sets the number of elements that the collection can contain.
    /// @param value The value to set.
    /// @throws ArgumentOutOfRangeException The @p value is set to a value that is less than CollectionBase::get_Count.
    /// @throws OutOfMemoryException There is not enough memory available on the system.
    void set_Capacity(int32_t value)
    {
        get_InnerList()->set_Capacity(value);
    }

    /// Returns the number of elements contained in the collection instance.
    /// This method cannot be overridden.
    /// @returns The number of elements contained in the collection instance.
    /// Retrieving the value of this method is an O(1) operation.
    int32_t get_Count()
    {
        return _list->get_Count();
    }

    /// Removes all objects from the collection instance. This method cannot be overridden.
    void Clear()
    {
        OnClear();
        get_InnerList()->Clear();
        OnClearComplete();
    }

    /// Removes the element at the specified index of the collection instance. This method is not overridable.
    /// @param index The zero-based index of the element to remove.
    /// @throws ArgumentOutOfRangeException @p index is less than zero.
    /// -or-
    /// @p index is equal to or greater than CollectionBase::Count.
    void RemoveAt(int32_t index)
    {
        if (index < 0 || index >= get_Count())
        {
            throw ArgumentOutOfRangeException(u"index");
        }

        T temp = get_InnerList()->idx_get(index);
        OnValidate(temp);
        OnRemove(index, temp);
        get_InnerList()->RemoveAt(index);
        try
        {
            OnRemoveComplete(index, temp);
        }
        catch (...)
        {
            get_InnerList()->Insert(index, temp);
            throw;
        }

    }

    /// Returns an enumerator that iterates through the collection instance.
    /// @returns An IEnumerator for the collection instance.
    SharedPtr<Generic::IEnumerator<T>> GetEnumerator() override
    {
        return get_InnerList()->GetEnumerator();
    }

    /// @copydoc System::Object::SetTemplateWeakPtr
    void SetTemplateWeakPtr(uint32_t argument) override
    {
        switch (argument)
        {
            case 0:
                System::Details::CollectionHelpers::SetWeakPointer(0, _list);
                System::Details::CollectionHelpers::SetWeakPointer(0, _impl);
                break;

        }
    }

protected:

    /// Returns a List containing the list of elements in the collection instance.
    /// @returns A List representing the collection instance itself.
    /// Retrieving the value of this method is an O(1) operation.
    SharedPtr<System::Collections::Generic::List<T>> get_InnerList()
    {
        return _list;
    }

    /// Returns a ListImpl containing the list of elements in the collection instance.
    /// @returns A ListImpl representing the collection instance itself.
    SharedPtr<ListImpl> get_List()
    {
        return _impl;
    }

    /// Initializes a new instance of the Collections::CollectionBase class with the default initial capacity.
    CollectionBase()
    {
        System::Details::ThisProtector __local_self_ref(this);

        _list = System::MakeObject<System::Collections::Generic::List<T>>();
        _impl = ListImpl::MakeObject(MakeSharedPtr(this));
    }

    /// Initializes a new instance of the Collections::CollectionBase class with the specified capacity.
    /// @param capacity The number of elements that the new list can initially store.
    CollectionBase(int32_t capacity)
    {
        System::Details::ThisProtector __local_self_ref(this);

        _list = System::MakeObject<System::Collections::Generic::List<T>>(capacity);
        _impl = ListImpl::MakeObject(MakeSharedPtr(this));
    }

    /// Performs additional custom processes before setting a value in the collection instance.
    /// @param index The zero-based index at which @p oldValue can be found.
    /// @param oldValue The value to replace with @p newValue.
    /// @param newValue The new value of the element at @p index.
    virtual void OnSet(int32_t index, const T& oldValue, const T& newValue)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(oldValue);
        ASPOSE_UNUSED(newValue);
    }

    /// Performs additional custom processes before inserting a new element into the collection instance.
    /// @param index The zero-based index at which to insert @p value.
    /// @param value The new value of the element at @p index.
    virtual void OnInsert(int32_t index, const T& value)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(value);
    }

    /// Performs additional custom processes when clearing the contents of the collection instance.
    virtual void OnClear()
    {
    }

    /// Performs additional custom processes when removing an element from the collection instance.
    /// @param index The zero-based index at which @p value can be found.
    /// @param value The value of the element to remove from @p index.
    virtual void OnRemove(int32_t index, const T& value)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(value);
    }

    /// Performs additional custom processes when validating a value.
    /// @param value The object to validate.
    /// @throws ArgumentNullException @p value is @c nullptr.
    virtual void OnValidate(const T& value)
    {
        if (value == nullptr)
        {
            throw ArgumentNullException(u"value");
        }
    }

    /// Performs additional custom processes after setting a value in the collection instance.
    /// @param index The zero-based index at which @p oldValue can be found.
    /// @param oldValue The value to replace with @p newValue.
    /// @param newValue The new value of the element at @p index.
    virtual void OnSetComplete(int32_t index, const T& oldValue, const T& newValue)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(oldValue);
        ASPOSE_UNUSED(newValue);
    }

    /// Performs additional custom processes after inserting a new element into the collection instance.
    /// @param index The zero-based index at which to insert @p value.
    /// @param value The new value of the element at @p index.
    virtual void OnInsertComplete(int32_t index, const T& value)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(value);
    }

    /// Performs additional custom processes after clearing the contents of the collection instance.
    virtual void OnClearComplete()
    {
    }

    /// Performs additional custom processes after removing an element from the collection instance.
    /// @param index The zero-based index at which @p value can be found.
    /// @param value The value of the element to remove from @p index.
    virtual void OnRemoveComplete(int32_t index, const T& value)
    {
        ASPOSE_UNUSED(index);
        ASPOSE_UNUSED(value);
    }

    virtual ~CollectionBase()
    {
    }

/// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        System::Object::GetSharedMembers(result);

        result.Add("System::Collections::CollectionBase::_list", this->_list);
        result.Add("System::Collections::CollectionBase::_impl", this->_impl);
    }
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
    {
        System::Object::DBG_for_each_member(visitor);

        visitor.add_self(this);

        visitor.add_member(this, _list, "_list");
        visitor.add_member(this, _impl, "_impl");
    }
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "CollectionBase"; }
    #endif
/// @endcond
private:

    SharedPtr<System::Collections::Generic::List<T>> _list;
    SharedPtr<ListImpl> _impl;

};

} // namespace Collections
} // namespace System


