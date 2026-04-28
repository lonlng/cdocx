/// @file xml/schema/xml_schema_simple_content_restriction.h

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
class XmlSchemaSimpleType;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c restriction element for simple content from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to derive simple types by restriction.
/// Such derivations can be used to restrict the range of values for the element to a subset of the values specified in the inherited simple type.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleContentRestriction : public XmlSchemaContent
{
    typedef XmlSchemaSimpleContentRestriction ThisType;
    typedef XmlSchemaContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleContentRestriction>;

private:
    /// @cond
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// Returns the name of the built-in data type or simple type from which this type is derived.
    /// @returns The name of the base type.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_BaseTypeName();
    /// Sets the name of the built-in data type or simple type from which this type is derived.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the simple type base value.
    /// @returns The simple type base value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_BaseType();
    /// Sets the simple type base value.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseType(const SharedPtr<XmlSchemaSimpleType>& value);
    /// Returns an Xml Schema facet.
    /// @returns One of the following facet classes:
    /// XmlSchemaLengthFacet, XmlSchemaMinLengthFacet, XmlSchemaMaxLengthFacet, XmlSchemaPatternFacet,
    /// XmlSchemaEnumerationFacet, XmlSchemaMaxInclusiveFacet, XmlSchemaMaxExclusiveFacet, XmlSchemaMinInclusiveFacet,
    /// XmlSchemaMinExclusiveFacet, XmlSchemaFractionDigitsFacet, XmlSchemaTotalDigitsFacet, XmlSchemaWhiteSpaceFacet.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Facets();
    /// Returns the XmlSchemaAttribute and XmlSchemaAttributeGroupRef collection of attributes for the simple type.
    /// @returns The collection of attributes for a simple type.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Attributes();
    /// Returns an XmlSchemaAnyAttribute to be used for the attribute value.
    /// @returns The XmlSchemaAnyAttribute for the attribute value. Optional.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AnyAttribute();
    /// Sets an XmlSchemaAnyAttribute to be used for the attribute value.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AnyAttribute(const SharedPtr<XmlSchemaAnyAttribute>& value);

    /// Initializes a new instance of the XmlSchemaSimpleContentRestriction class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleContentRestriction();

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleContentRestriction"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _baseTypeName;
    SharedPtr<XmlSchemaSimpleType> _baseType;
    SharedPtr<XmlSchemaObjectCollection> _facets;
    SharedPtr<XmlSchemaObjectCollection> _attributes;
    SharedPtr<XmlSchemaAnyAttribute> _anyAttribute;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


