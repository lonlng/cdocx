/// @file system/collections/specialized/string_collection.h
#ifndef _aspose_system_collections_specialized_string_collection_h
#define _aspose_system_collections_specialized_string_collection_h

#include "system/object.h"
#include "system/string.h"
#include "system/array.h"

#include "system/collections/icollection.h"
#include "system/collections/base_enumerator.h"

namespace System {
namespace Collections {
namespace Specialized {

/// Indexed list of strings.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS StringCollection : public Generic::IEnumerable<System::String>
{
    /// RTTI information.
    RTTI_INFO(StringCollection, ::System::BaseTypesInfo<System::Object>);

public:
    /// Enumerator type to iterate through string collection.
    class Enumerator : public Generic::SimpleEnumerator<std::vector<System::String> >
    {
    public:
        /// Constructs enumerator iterating through specified collection.
        /// @param data Collection to iterate through.
        Enumerator(const SharedPtr<StringCollection>& data) : Generic::SimpleEnumerator<std::vector<System::String> >(data, data->m_data) { }
        /// RTTI information
        RTTI_INFO(StringCollection::Enumerator, ::System::BaseTypesInfo<System::Object>);
    };

    /// Constructs empty string collection.
    ASPOSECPP_SHARED_API StringCollection();

    /// Gets enumerator iterating through current collection.
    /// @return Newly created enumerator iterating through current collection.
    SharedPtr<Generic::IEnumerator<System::String> > GetEnumerator() override
    {
        return MakeObject<Enumerator>(MakeSharedPtr(this));
    }

    /// Gets number of elements in collection.
    /// @return Actual element count.
    ASPOSECPP_SHARED_API int get_Count() const;
    /// Accessor function.
    /// @param index Index to get element at.
    /// @return Reference to string at specified position, either existing or newly created.
    ASPOSECPP_SHARED_API System::String& operator[](int index);
    /// Gets value at specified position.
    /// @param index Index to get string from.
    /// @return String at specified position.
    ASPOSECPP_SHARED_API System::String idx_get(int index) const;
    /// Sets value at specified position.
    /// @param index Index to set string at.
    /// @param value String value to set at specified index.
    ASPOSECPP_SHARED_API void idx_set(int index, const System::String& value);
    /// Adds value to the end of the list.
    /// @param value String to add.
    /// @return Index of inserted element.
    ASPOSECPP_SHARED_API int Add(const System::String& value);
    /// Add elements into container.
    /// @param range Container of elements to insert.
    ASPOSECPP_SHARED_API void AddRange(const ArrayPtr<System::String>& range);
    /// Copy elements to existing arra elements.
    /// @param arr Array to copy data to.
    /// @param index Index in destination array to start data copying at.
    ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<System::String>& arr, const int32_t index) const;
    /// Deletes all elements.
    ASPOSECPP_SHARED_API void Clear();
    /// Checks whether specific string is present in container.
    /// @param value String to look for.
    /// @return True if string is found, false otherwise.
    ASPOSECPP_SHARED_API bool Contains(const System::String& value) const;
    /// Looks for specific string in container.
    /// @param value String to look for.
    /// @return Index of first occurrence of specified string or -1 if not found.
    ASPOSECPP_SHARED_API int IndexOf(const System::String& value) const;
    /// Inserts specific value into container.
    /// @param index Index to insert string into.
    /// @param value Value to insert into specified position.
    ASPOSECPP_SHARED_API void Insert(int index, const System::String& value);
    /// Removes first occurrence of specified string.
    /// @param value String to remove.
    ASPOSECPP_SHARED_API void Remove(const System::String& value);
    /// Removes element at specified position.
    /// @param index Index to remove element at.
    ASPOSECPP_SHARED_API void RemoveAt(int index);

    /// Internal data structure accessor.
    /// @return Reference to internal data structure.
    ASPOSECPP_SHARED_API std::vector<System::String>& data();
    /// Internal data structure accessor.
    /// @return Const reference to internal data structure.
    ASPOSECPP_SHARED_API const std::vector<System::String>& data() const;


    /// Iterator type.
    typedef typename std::vector<System::String>::iterator iterator;
    /// Const iterator type.
    typedef typename std::vector<System::String>::const_iterator const_iterator;
    /// Reverse iterator type.
    typedef typename std::vector<System::String>::reverse_iterator reverse_iterator;
    /// Const reverse iterator type.
    typedef typename std::vector<System::String>::const_reverse_iterator const_reverse_iterator;

    /// Returns an iterator to the first element of the container.
    /// If the container is empty, the returned iterator will be equal to end().
    /// @returns An iterator pointing to the first element of the container.
    ASPOSECPP_SHARED_API iterator begin() noexcept;
    /// Returns an iterator to the first element of the const-qualified container.
    /// If the container is empty, the returned iterator will be equal to end().
    /// @returns An iterator pointing to the first element of the const-qualified container.
    ASPOSECPP_SHARED_API const_iterator begin() const noexcept;
    /// Returns an iterator to the first const-qualified element of the container.
    /// If the container is empty, the returned iterator will be equal to cend().
    /// @returns An iterator pointing to the first const-qualified element of the container.
    ASPOSECPP_SHARED_API const_iterator cbegin() const noexcept;
    /// Returns an iterator to the element following the last element of the container.
    /// This element acts as a placeholder; attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical element placed after the last element of the container.
    ASPOSECPP_SHARED_API iterator end() noexcept;
    /// Returns an iterator to the element following the last element of the const-qualified container.
    /// This element acts as a placeholder; attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical element placed after the last element of the const-qualified container.
    ASPOSECPP_SHARED_API const_iterator end() const noexcept;
    /// Returns an iterator to the element following the last element of the container.
    /// This element acts as a placeholder; attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical const-qualified element placed after the last element of the container.
    ASPOSECPP_SHARED_API const_iterator cend() const noexcept;
    /// Returns a reverse iterator to the first element of the reversed container. 
    /// It corresponds to the last element of the non-reversed container.
    /// If the container is empty, the returned iterator is equal to rend().
    /// @returns An iterator pointing to the last element of the container.
    ASPOSECPP_SHARED_API reverse_iterator rbegin() noexcept;
    /// Returns a reverse iterator to the first element of the reversed container. 
    /// It corresponds to the last element of the non-reversed container.
    /// If the container is empty, the returned iterator is equal to rend().
    /// @returns An iterator pointing to the last element of the const-qualified container.
    ASPOSECPP_SHARED_API const_reverse_iterator rbegin() const noexcept;
    /// Returns a reverse iterator to the first element of the reversed container. 
    /// It corresponds to the last element of the non-reversed container.
    /// If the container is empty, the returned iterator is equal to crend().
    /// @returns An iterator pointing to the last const-qualified element of the container.
    ASPOSECPP_SHARED_API const_reverse_iterator crbegin() const noexcept;
    /// Returns a reverse iterator to the element following the last element of the reversed container.
    /// It corresponds to the element preceding the first element of the non-reversed container.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical element preceding the first element of the container.
    ASPOSECPP_SHARED_API reverse_iterator rend() noexcept;
    /// Returns a reverse iterator to the element following the last element of the reversed container.
    /// It corresponds to the element preceding the first element of the non-reversed container.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical element preceding the first element of the const-qualified container.
    ASPOSECPP_SHARED_API const_reverse_iterator rend() const noexcept;
    /// Returns a reverse iterator to the element following the last element of the reversed container.
    /// It corresponds to the element preceding the first element of the non-reversed container.
    /// This element acts as a placeholder, attempting to access it results in undefined behavior.
    /// @returns An iterator pointing to the theoretical const-qualified element preceding the first element of the container.
    ASPOSECPP_SHARED_API const_reverse_iterator crend() const noexcept;

    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeBeginIterator() override;
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeEndIterator() override;
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeBeginConstIterator() const override;
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<System::String>* virtualizeEndConstIterator() const override;

protected:
    /// Destructor.
    ASPOSECPP_SHARED_API ~StringCollection() override;

    /// Internal data structure.
    std::vector<System::String> m_data;

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to container and elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
    {
        visitor.add_self(this);
    }

    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "StringCollection<T>"; }
#endif
};

/// Stirng collection poiner with access operator.
class StringCollectionPtr : public SharedPtr<StringCollection>
{
public:
    /// Constructs null pointer.
    StringCollectionPtr() {}
    /// Constructs pointer to specific collection.
    /// @param obj Collection to point to.
    StringCollectionPtr(const SharedPtr<StringCollection>& obj) : SharedPtr<StringCollection>(obj) { }

    /// Accessor function.
    /// @param idx Index to get element at.
    /// @return Reference to string at specified position, either existing or newly created.
    System::String& operator[] (int idx) const
    {
        return (**this)[idx];
    }
};

} // namespace Specialized
} // namespace Collections
} // namespace System

#endif // _aspose_system_collections_specialized_string_collection_h
