/// @file xml/schema/xml_schema_attribute_group.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/string.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class BaseProcessor;
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchemaAnyAttribute;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c attributeGroup element from the XML Schema as specified by the World Wide Web Consortium (W3C).
/// AttributesGroups provides a mechanism to group a set of attribute declarations so that they can be incorporated as a group into complex type definitions.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAttributeGroup : public XmlSchemaAnnotated
{
    typedef XmlSchemaAttributeGroup ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAttributeGroup>;

private:
    /// @cond
    friend class BaseProcessor;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    /// @endcond

public:

    /// Returns the name of the attribute group.
    /// @returns The name of the attribute group.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the attribute group.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns the collection of attributes for the attribute group.
    /// Contains XmlSchemaAttribute and XmlSchemaAttributeGroupRef elements.
    /// @returns The collection of attributes for the attribute group.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Attributes();
    /// Returns the XmlSchemaAnyAttribute component of the attribute group.
    /// @returns The World Wide Web Consortium (W3C) @c anyAttribute element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AnyAttribute();
    /// Sets the XmlSchemaAnyAttribute component of the attribute group.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AnyAttribute(const SharedPtr<XmlSchemaAnyAttribute>& value);
    /// Returns the qualified name of the attribute group.
    /// @returns The qualified name of the attribute group.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();
    /// Returns the redefined attribute group property from the XML Schema.
    /// @returns The redefined attribute group property.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAttributeGroup> get_RedefinedAttributeGroup();

    /// Initializes a new instance of the XmlSchemaAttributeGroup class.
    ASPOSECPP_SHARED_API XmlSchemaAttributeGroup();

protected:

    /// @cond
    SharedPtr<XmlSchemaObjectTable> get_AttributeUses();
    SharedPtr<XmlSchemaAnyAttribute> get_AttributeWildcard();
    void set_AttributeWildcard(const SharedPtr<XmlSchemaAnyAttribute>& value);
    SharedPtr<XmlSchemaAttributeGroup> get_Redefined();
    void set_Redefined(const SharedPtr<XmlSchemaAttributeGroup>& value);
    int32_t get_SelfReferenceCount();
    void set_SelfReferenceCount(int32_t value);
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);
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
    const char* DBG_class_name() const override { return "XmlSchemaAttributeGroup"; }
#endif
    /// @endcond

private:

    String _name;
    SharedPtr<XmlSchemaObjectCollection> _attributes;
    SharedPtr<XmlSchemaAnyAttribute> _anyAttribute;
    SharedPtr<XmlQualifiedName> _qname;
    SharedPtr<XmlSchemaAttributeGroup> _redefined;
    SharedPtr<XmlSchemaObjectTable> _attributeUses;
    SharedPtr<XmlSchemaAnyAttribute> _attributeWildcard;
    int32_t _selfReferenceCount;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


