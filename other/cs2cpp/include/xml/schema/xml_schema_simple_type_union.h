/// @file xml/schema/xml_schema_simple_type_union.h

#pragma once

#include <xml/schema/xml_schema_simple_type_content.h>
#include <system/array.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class Compiler;
class SchemaCollectionCompiler;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaSimpleType;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c union element for simple types from XML Schema as specified by the World Wide Web Consortium (W3C).
/// A @c union datatype can be used to specify the content of a @c simpleType.
/// The value of the @c simpleType element must be any one of a set of alternative datatypes specified in the union.
/// Union types are always derived types and must comprise at least two alternative datatypes.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleTypeUnion : public XmlSchemaSimpleTypeContent
{
    typedef XmlSchemaSimpleTypeUnion ThisType;
    typedef XmlSchemaSimpleTypeContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleTypeUnion>;

private:
    /// @cond
    friend class SchemaCollectionCompiler;
    friend class Compiler;
    /// @endcond

public:

    /// Returns the collection of base types.
    /// @returns The collection of simple type base values.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_BaseTypes();
    /// Returns the array of qualified member names of built-in data types or
    /// @c simpleType elements defined in this schema (or another schema indicated by the specified namespace).
    /// @returns An array that consists of a list of members of built-in data types or simple types.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlQualifiedName>> get_MemberTypes();
    /// Sets the array of qualified member names of built-in data types or
    /// @c simpleType elements defined in this schema (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MemberTypes(const ArrayPtr<SharedPtr<XmlQualifiedName>>& value);
    /// Returns an array of XmlSchemaSimpleType objects representing the type of the @c simpleType element based on
    /// the XmlSchemaSimpleTypeUnion::get_BaseTypes and XmlSchemaSimpleTypeUnion::get_MemberTypes values of the simple type.
    /// @returns An array of XmlSchemaSimpleType objects representing the type of the @c simpleType element.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlSchemaSimpleType>> get_BaseMemberTypes();

    /// Initializes a new instance of the XmlSchemaSimpleTypeUnion class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleTypeUnion();

protected:

    /// @cond
    void SetBaseMemberTypes(const ArrayPtr<SharedPtr<XmlSchemaSimpleType>>& baseMemberTypes);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaSimpleTypeUnion();

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleTypeUnion"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaObjectCollection> _baseTypes;
    ArrayPtr<SharedPtr<XmlQualifiedName>> _memberTypes;
    ArrayPtr<SharedPtr<XmlSchemaSimpleType>> _baseMemberTypes;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


