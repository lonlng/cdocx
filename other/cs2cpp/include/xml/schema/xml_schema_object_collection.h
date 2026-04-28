/// @file xml/schema/xml_schema_object_collection.h

#pragma once

#include <xml/schema/xml_schema_object.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/collections/ienumerator.h>
#include <system/collections/collection_base.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaComplexType;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// A collection of XmlSchemaObjects.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaObjectCollection : public Collections::CollectionBase<SharedPtr<System::Xml::Schema::XmlSchemaObject>>
{
    typedef XmlSchemaObjectCollection ThisType;
    typedef Collections::CollectionBase<SharedPtr<System::Xml::Schema::XmlSchemaObject>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaObjectCollection>;

private:
    /// @cond
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// Initializes a new instance of the XmlSchemaObjectCollection class.
    ASPOSECPP_SHARED_API XmlSchemaObjectCollection();
    /// Initializes a new instance of the XmlSchemaObjectCollection class that takes an XmlSchemaObject.
    /// @param parent The XmlSchemaObject.
    ASPOSECPP_SHARED_API XmlSchemaObjectCollection(const SharedPtr<XmlSchemaObject>& parent);

    /// Returns the XmlSchemaObject at the specified index.
    /// @param index The index of the XmlSchemaObject.
    /// @returns The XmlSchemaObject at the specified index.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> idx_get(int32_t index);
    /// Sets the XmlSchemaObject at the specified index.
    /// @param index The index of the XmlSchemaObject.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void idx_set(int32_t index, SharedPtr<XmlSchemaObject> value);

    /// Returns an enumerator for iterating through the XmlSchemaObjects contained in the XmlSchemaObjectCollection.
    /// @returns The iterator returns XmlSchemaObjectEnumerator.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlSchemaObject>>> GetEnumerator() override;
    /// Adds an XmlSchemaObject to the XmlSchemaObjectCollection.
    /// @param item The XmlSchemaObject.
    /// @returns The index at which the item has been added.
    /// @throws ArgumentOutOfRangeException @p index is less than zero.
    /// or
    /// @p index is greater than get_Count value.
    /// @throws InvalidCastException The XmlSchemaObject parameter specified is not of type XmlSchemaExternal or
    /// its derived types XmlSchemaImport, XmlSchemaInclude, and XmlSchemaRedefine.
    ASPOSECPP_SHARED_API int32_t Add(const SharedPtr<XmlSchemaObject>& item);
    /// Inserts an XmlSchemaObject to the XmlSchemaObjectCollection.
    /// @param index The zero-based index at which an item should be inserted.
    /// @param item The XmlSchemaObject to insert.
    /// @throws ArgumentOutOfRangeException @p index is less than zero.
    /// or
    /// @p index is greater than get_Count value.
    ASPOSECPP_SHARED_API void Insert(int32_t index, const SharedPtr<XmlSchemaObject>& item);
    /// Returns the collection index corresponding to the specified XmlSchemaObject.
    /// @param item The XmlSchemaObject whose index you want to return.
    /// @returns The index corresponding to the specified XmlSchemaObject.
    ASPOSECPP_SHARED_API int32_t IndexOf(const SharedPtr<XmlSchemaObject>& item);
    /// Indicates if the specified XmlSchemaObject is in the XmlSchemaObjectCollection.
    /// @param item The XmlSchemaObject.
    /// @returns @c true if the specified qualified name is in the collection; otherwise, returns @c false.
    /// If @c nullptr is supplied, @c false is returned because there is no qualified name with a null name.
    ASPOSECPP_SHARED_API bool Contains(const SharedPtr<XmlSchemaObject>& item);
    /// Removes an XmlSchemaObject from the XmlSchemaObjectCollection.
    /// @param item The XmlSchemaObject to remove.
    ASPOSECPP_SHARED_API void Remove(const SharedPtr<XmlSchemaObject>& item);
    /// Copies all the XmlSchemaObjects from the collection into the given array, starting at the given index.
    /// @param array The array that is the destination of the elements copied from the XmlSchemaObjectCollection.
    /// The array must have zero-based indexing.
    /// @param index The zero-based index in the array at which copying begins.
    /// @throws ArgumentNullException @p array is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index is less than zero.
    /// @throws ArgumentException @p array is multi-dimensional.
    /// or
    /// @p index is equal to or greater than the length of @p array.
    /// or
    /// The number of elements in the source XmlSchemaObject is greater than the available space from
    /// index to the end of the destination array.
    /// @throws InvalidCastException The type of the source XmlSchemaObject cannot be
    /// cast automatically to the type of the destination array.
    ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<SharedPtr<XmlSchemaObject>>& array, int32_t index);
    /// @copydoc System::Object::SetTemplateWeakPtr
    ASPOSECPP_SHARED_API void SetTemplateWeakPtr(uint32_t argument) override;

protected:

    /// @c OnInsert is invoked before the standard @c Insert behavior.
    /// For more information, see CollectionBase::OnInsert method.
    /// @param index The index of XmlSchemaObject.
    /// @param item The item.
    ASPOSECPP_SHARED_API void OnInsert(int32_t index, const SharedPtr<XmlSchemaObject>& item) override;
    /// @c OnSet is invoked before the standard @c Set behavior.
    /// For more information, see CollectionBase::OnSet method.
    /// @param index The index of XmlSchemaObject.
    /// @param oldValue The old value.
    /// @param newValue The new value.
    ASPOSECPP_SHARED_API void OnSet(int32_t index, const SharedPtr<XmlSchemaObject>& oldValue,
                                                   const SharedPtr<XmlSchemaObject>& newValue) override;
    /// @c OnClear is invoked before the standard @c Clear behavior.
    /// For more information, see CollectionBase::OnClear method.
    ASPOSECPP_SHARED_API void OnClear() override;
    /// @c OnRemove is invoked before the standard @c Remove behavior.
    /// For more information, see CollectionBase::OnRemove method.
    /// @param index The index of XmlSchemaObject.
    /// @param item The item.
    ASPOSECPP_SHARED_API void OnRemove(int32_t index, const SharedPtr<XmlSchemaObject>& item) override;

    /// @cond
    SharedPtr<XmlSchemaObjectCollection> Clone();
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaObjectCollection();

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlSchemaObjectCollection"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaObject> _parent;

    void Add(const SharedPtr<XmlSchemaObjectCollection>& collToAdd);

};

/// Represents the enumerator for the XmlSchemaObjectCollection.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaObjectEnumerator : public Collections::Generic::IEnumerator<SharedPtr<System::Xml::Schema::XmlSchemaObject>>
{
    typedef XmlSchemaObjectEnumerator ThisType;
    typedef Collections::Generic::IEnumerator<SharedPtr<System::Xml::Schema::XmlSchemaObject>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaObjectEnumerator>;

private:
    /// @cond
    friend class XmlSchemaObjectCollection;
    /// @endcond

public:

    /// Returns the current XmlSchemaObject in the collection.
    /// @returns The current XmlSchemaObject.
    ASPOSECPP_SHARED_API const SharedPtr<XmlSchemaObject>& get_Current() const override;

    /// Resets the enumerator to the start of the collection.
    ASPOSECPP_SHARED_API void Reset() override;
    /// Moves to the next item in the collection.
    /// @returns @c false at the end of the collection.
    ASPOSECPP_SHARED_API bool MoveNext() override;
    /// Does nothing.
    ASPOSECPP_SHARED_API void Dispose() override;

    /// Clones current iterator.
    /// @return Copy of the current iterator.
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<System::Xml::Schema::XmlSchemaObject>>* CloneIterator() const override;

protected:

    /// @cond
    XmlSchemaObjectEnumerator(const SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlSchemaObject>>>& enumerator);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlSchemaObjectEnumerator, CODEPORTING_ARGS(SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlSchemaObject>>> enumerator));

    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlSchemaObjectEnumerator"; }
#endif
    /// @endcond

private:

    SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlSchemaObject>>> _enumerator;
    mutable SharedPtr<XmlSchemaObject> m_CurrentHolder;

};

} // namespace Schema
} // namespace Xml
} // namespace System


