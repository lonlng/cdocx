/// @file xml/schema/xml_schema_simple_type_restriction.h

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

/// Represents the @c restriction element for simple types from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used restricting @c simpleType element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleTypeRestriction : public XmlSchemaSimpleTypeContent
{
    typedef XmlSchemaSimpleTypeRestriction ThisType;
    typedef XmlSchemaSimpleTypeContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleTypeRestriction>;

public:

    /// Returns the name of the qualified base type.
    /// @returns The qualified name of the simple type restriction base type.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_BaseTypeName();
    /// Sets the name of the qualified base type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns information on the base type.
    /// @returns The base type for the @c simpleType element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_BaseType();
    /// Sets information on the base type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseType(const SharedPtr<XmlSchemaSimpleType>& value);
    /// Returns an Xml Schema facet.
    /// @returns One of the following facet classes:
    /// XmlSchemaLengthFacet, XmlSchemaMinLengthFacet, XmlSchemaMaxLengthFacet, XmlSchemaPatternFacet,
    /// XmlSchemaEnumerationFacet, XmlSchemaMaxInclusiveFacet, XmlSchemaMaxExclusiveFacet, XmlSchemaMinInclusiveFacet,
    /// XmlSchemaMinExclusiveFacet, XmlSchemaFractionDigitsFacet, XmlSchemaTotalDigitsFacet, XmlSchemaWhiteSpaceFacet.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Facets();

    /// Initializes a new instance of the XmlSchemaSimpleTypeRestriction class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleTypeRestriction();

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleTypeRestriction"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _baseTypeName;
    SharedPtr<XmlSchemaSimpleType> _baseType;
    SharedPtr<XmlSchemaObjectCollection> _facets;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


