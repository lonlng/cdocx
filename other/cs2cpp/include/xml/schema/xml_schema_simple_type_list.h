/// @file xml/schema/xml_schema_simple_type_list.h

#pragma once

#include <xml/schema/xml_schema_simple_type_content.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaObject;
class XmlSchemaSimpleType;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c list element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to define a @c simpleType element as a list of values of a specified data type.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleTypeList : public XmlSchemaSimpleTypeContent
{
    typedef XmlSchemaSimpleTypeList ThisType;
    typedef XmlSchemaSimpleTypeContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleTypeList>;

public:

    /// Returns the name of a built-in data type or @c simpleType element defined in this schema
    /// (or another schema indicated by the specified namespace).
    /// @returns The type name of the simple type list.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_ItemTypeName();
    /// Sets the name of a built-in data type or @c simpleType element defined in this schema
    /// (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ItemTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the @c simpleType element that is derived from the type specified by the base value.
    /// @returns The item type for the simple type element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_ItemType();
    /// Sets the @c simpleType element that is derived from the type specified by the base value.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ItemType(const SharedPtr<XmlSchemaSimpleType>& value);
    /// Returns the XmlSchemaSimpleType representing the type of the @c simpleType element based on
    /// the XmlSchemaSimpleTypeList::get_ItemType and XmlSchemaSimpleTypeList::get_ItemTypeName values of the simple type.
    /// @returns The XmlSchemaSimpleType representing the type of the @c simpleType element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_BaseItemType();
    /// Sets the XmlSchemaSimpleType representing the type of the @c simpleType element based on the
    /// XmlSchemaSimpleTypeList::get_ItemType and XmlSchemaSimpleTypeList::get_ItemTypeName values of the simple type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseItemType(const SharedPtr<XmlSchemaSimpleType>& value);

    /// Initializes a new instance of the XmlSchemaSimpleTypeList class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleTypeList();

protected:

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleTypeList"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _itemTypeName;
    SharedPtr<XmlSchemaSimpleType> _itemType;
    SharedPtr<XmlSchemaSimpleType> _baseItemType;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


