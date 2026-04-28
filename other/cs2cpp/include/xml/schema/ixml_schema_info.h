/// @file xml/schema/ixml_schema_info.h

#pragma once

#include <xml/schema/xml_schema_validity.h>
#include <system/object.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaAttribute;
class XmlSchemaElement;
class XmlSchemaSimpleType;
class XmlSchemaType;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Defines the post-schema-validation infoset of a validated XML node.
class ASPOSECPP_SHARED_CLASS IXmlSchemaInfo : public virtual System::Object
{
    typedef IXmlSchemaInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the XmlSchemaValidity value of this validated XML node.
    /// @returns An XmlSchemaValidity value of this validated XML node.
    virtual XmlSchemaValidity get_Validity() = 0;
    /// Returns a value indicating if this validated XML node was set as the result of
    /// a default being applied during XML Schema Definition Language (XSD) schema validation.
    /// @returns @c true if this validated XML node was set as the result of
    /// a default being applied during schema validation;
    /// otherwise, @c false.
    virtual bool get_IsDefault() = 0;
    /// Returns a value indicating if the value for this validated XML node is @c nil.
    /// @returns @c true if the value for this validated XML node is @c nil; otherwise, @c false.
    virtual bool get_IsNil() = 0;
    /// Returns the dynamic schema type for this validated XML node.
    /// @returns An XmlSchemaSimpleType object that represents the dynamic schema type for this validated XML node.
    virtual SharedPtr<XmlSchemaSimpleType> get_MemberType() = 0;
    /// Returns the static XML Schema Definition Language (XSD) schema type of this validated XML node.
    /// @returns An XmlSchemaType of this validated XML node.
    virtual SharedPtr<XmlSchemaType> get_SchemaType() = 0;
    /// Returns the compiled XmlSchemaElement that corresponds to this validated XML node.
    /// @returns An XmlSchemaElement that corresponds to this validated XML node.
    virtual SharedPtr<XmlSchemaElement> get_SchemaElement() = 0;
    /// Returns the compiled XmlSchemaAttribute that corresponds to this validated XML node.
    /// @returns An XmlSchemaAttribute that corresponds to this validated XML node.
    virtual SharedPtr<XmlSchemaAttribute> get_SchemaAttribute() = 0;

};

} // namespace Schema
} // namespace Xml
} // namespace System


