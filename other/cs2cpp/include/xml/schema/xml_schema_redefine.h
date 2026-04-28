/// @file xml/schema/xml_schema_redefine.h

#pragma once

#include <xml/schema/xml_schema_external.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaAnnotation;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c redefine element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to allow simple and complex types, groups and attribute groups from external schema files to be redefined in the current schema.
/// This class can also be used to provide versioning for the schema elements.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaRedefine : public XmlSchemaExternal
{
    typedef XmlSchemaRedefine ThisType;
    typedef XmlSchemaExternal BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaRedefine>;

public:

    /// Returns the collection of the following classes:
    /// XmlSchemaAnnotation, XmlSchemaAttributeGroup, XmlSchemaComplexType, XmlSchemaSimpleType, and XmlSchemaGroup.
    /// @returns The elements contained within the redefine element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Items();
    /// Returns the XmlSchemaObjectTable , for all attributes in the schema,
    /// which holds the post-compilation interpretation of the @c AttributeGroups value.
    /// @returns The XmlSchemaObjectTable for all attributes in the schema.
    /// The post-compilation interpretation of the @c AttributeGroups value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_AttributeGroups();
    /// Returns the XmlSchemaObjectTable, for all simple and complex types in the schema,
    /// which holds the post-compilation interpretation of the @c SchemaTypes value.
    /// @returns The XmlSchemaObjectTable for all schema types in the schema.
    /// The post-compilation interpretation of the @c SchemaTypes value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_SchemaTypes();
    /// Returns the XmlSchemaObjectTable, for all groups in the schema,
    /// which holds the post-compilation interpretation of the @c Groups value.
    /// @returns The XmlSchemaObjectTable for all groups in the schema.
    /// The post-compilation interpretation of the @c Groups value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_Groups();

    /// Initializes a new instance of the XmlSchemaRedefine class.
    ASPOSECPP_SHARED_API XmlSchemaRedefine();

protected:

    /// @cond
    ASPOSECPP_SHARED_API void AddAnnotation(SharedPtr<XmlSchemaAnnotation> annotation) override;

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
    const char* DBG_class_name() const override { return "XmlSchemaRedefine"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaObjectCollection> _items;
    SharedPtr<XmlSchemaObjectTable> _attributeGroups;
    SharedPtr<XmlSchemaObjectTable> _types;
    SharedPtr<XmlSchemaObjectTable> _groups;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


