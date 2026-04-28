/// @file xml/schema/xml_schema_info.h

#pragma once

#include <xml/schema/xml_schema_validity.h>
#include <xml/schema/xml_schema_content_type.h>
#include <xml/schema/ixml_schema_info.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
class AttributePSVIInfo;
class DocumentSchemaValidator;
namespace Schema
{
class XmlSchemaAttribute;
class XmlSchemaElement;
class XmlSchemaSimpleType;
class XmlSchemaType;
class XmlSchemaValidator;
} // namespace Schema
class XmlDocument;
class XsdValidatingReader;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the post-schema-validation infoset of a validated XML node.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaInfo : public IXmlSchemaInfo
{
    typedef XmlSchemaInfo ThisType;
    typedef IXmlSchemaInfo BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaInfo>;

private:
    /// @cond
    friend class System::Xml::AttributePSVIInfo;
    friend class System::Xml::XsdValidatingReader;
    friend class System::Xml::DocumentSchemaValidator;
    friend class System::Xml::XmlDocument;
    friend class XmlSchemaValidator;
    /// @endcond

public:

    /// Returns the XmlSchemaValidity value of this validated XML node.
    /// @returns An XmlSchemaValidity value.
    ASPOSECPP_SHARED_API XmlSchemaValidity get_Validity() override;
    /// Sets the XmlSchemaValidity value of this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Validity(XmlSchemaValidity value);
    /// Returns a value indicating if this validated XML node was set as the result of
    /// a default being applied during XML Schema Definition Language (XSD) schema validation.
    /// @returns A @c bool value.
    ASPOSECPP_SHARED_API bool get_IsDefault() override;
    /// Sets a value indicating if this validated XML node was set as the result of
    /// a default being applied during XML Schema Definition Language (XSD) schema validation.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsDefault(bool value);
    /// Returns a value indicating if the value for this validated XML node is @c nil.
    /// @returns A @c bool value.
    ASPOSECPP_SHARED_API bool get_IsNil() override;
    /// Sets a value indicating if the value for this validated XML node is @c nil.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsNil(bool value);
    /// Returns the dynamic schema type for this validated XML node.
    /// @returns An XmlSchemaSimpleType object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_MemberType() override;
    /// Sets the dynamic schema type for this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MemberType(const SharedPtr<XmlSchemaSimpleType>& value);
    /// Returns the static XML Schema Definition Language (XSD) schema type of this validated XML node.
    /// @returns An XmlSchemaType object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaType> get_SchemaType() override;
    /// Sets the static XML Schema Definition Language (XSD) schema type of this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaType(const SharedPtr<XmlSchemaType>& value);
    /// Returns the compiled XmlSchemaElement object that corresponds to this validated XML node.
    /// @returns An XmlSchemaElement object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaElement> get_SchemaElement() override;
    /// Sets the compiled XmlSchemaElement object that corresponds to this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaElement(const SharedPtr<XmlSchemaElement>& value);
    /// Returns the compiled XmlSchemaAttribute object that corresponds to this validated XML node.
    /// @returns An XmlSchemaAttribute object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAttribute> get_SchemaAttribute() override;
    /// Sets the compiled XmlSchemaAttribute object that corresponds to this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaAttribute(const SharedPtr<XmlSchemaAttribute>& value);
    /// Returns the XmlSchemaContentType object that corresponds to the content type of this validated XML node.
    /// @returns An XmlSchemaContentType object.
    ASPOSECPP_SHARED_API XmlSchemaContentType get_ContentType();
    /// Sets the XmlSchemaContentType object that corresponds to the content type of this validated XML node.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ContentType(XmlSchemaContentType value);

    /// Initializes a new instance of the XmlSchemaInfo class.
    ASPOSECPP_SHARED_API XmlSchemaInfo();

protected:

    /// @cond
    SharedPtr<XmlSchemaType> get_XmlType();
    bool get_HasDefaultValue();
    bool get_IsUnionType();

    XmlSchemaInfo(XmlSchemaValidity validity);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlSchemaInfo, CODEPORTING_ARGS(XmlSchemaValidity validity));

    void Clear();

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
    const char* DBG_class_name() const override { return "XmlSchemaInfo"; }
#endif
    /// @endcond

private:

    bool _isDefault;
    bool _isNil;
    SharedPtr<XmlSchemaElement> _schemaElement;
    SharedPtr<XmlSchemaAttribute> _schemaAttribute;
    SharedPtr<XmlSchemaType> _schemaType;
    SharedPtr<XmlSchemaSimpleType> _memberType;
    XmlSchemaValidity _validity;
    XmlSchemaContentType _contentType;

};

} // namespace Schema
} // namespace Xml
} // namespace System


