/// @file xml/schema/xml_schema_simple_content_extension.h

#pragma once

#include <xml/schema/xml_schema_content.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaAnyAttribute;
class XmlSchemaComplexType;
class XmlSchemaObjectCollection;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c extension element for simple content from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to derive simple types by extension.
/// Such derivations are used to extend the simple type content of the element by adding attributes.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleContentExtension : public XmlSchemaContent
{
    typedef XmlSchemaSimpleContentExtension ThisType;
    typedef XmlSchemaContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleContentExtension>;

private:
    /// @cond
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// Returns the name of a built-in data type or simple type from which this type is extended.
    /// @returns The base type name.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_BaseTypeName();
    /// Sets the name of a built-in data type or simple type from which this type is extended.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the collection of XmlSchemaAttribute and XmlSchemaAttributeGroupRef.
    /// @returns The collection of attributes for the @c simpleType element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Attributes();
    /// Returns the XmlSchemaAnyAttribute to be used for the attribute value.
    /// @returns The XmlSchemaAnyAttribute. Optional.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AnyAttribute();
    /// Sets the XmlSchemaAnyAttribute to be used for the attribute value.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AnyAttribute(const SharedPtr<XmlSchemaAnyAttribute>& value);

    /// Initializes a new instance of the XmlSchemaSimpleContentExtension class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleContentExtension();

protected:

    /// @cond
    void SetAttributes(const SharedPtr<XmlSchemaObjectCollection>& newAttributes);

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleContentExtension"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaObjectCollection> _attributes;
    SharedPtr<XmlSchemaAnyAttribute> _anyAttribute;
    SharedPtr<XmlQualifiedName> _baseTypeName;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


