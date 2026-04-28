/// @file xml/schema/xml_schema_attribute.h

#pragma once

#include <xml/schema/xml_schema_use.h>
#include <xml/schema/xml_schema_form.h>
#include <xml/schema/xml_schema_annotated.h>
#include <xml/schema/validation_event_handler.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
class DocumentSchemaValidator;
namespace Schema
{
class Compiler;
class Preprocessor;
class SchemaAttDef;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaInfo;
class XmlSchemaComplexType;
class XmlSchemaDatatype;
class XmlSchemaObject;
class XmlSchemaSet;
class XmlSchemaSimpleType;
class XmlSchemaValidator;
} // namespace Schema
class XmlQualifiedName;
class XmlReader;
class XmlResolver;
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c attribute element from the XML Schema as specified by the World Wide Web Consortium (W3C).
/// Attributes provide additional information for other document elements.
/// The attribute tag is nested between the tags of a document's element for the schema.
/// The XML document displays attributes as named items in the opening tag of an element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAttribute : public XmlSchemaAnnotated
{
    typedef XmlSchemaAttribute ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAttribute>;

private:
    /// @cond
    friend class XPath::XPathNavigator;
    friend class System::Xml::DocumentSchemaValidator;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class SchemaInfo;
    friend class Compiler;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaValidator;
    /// @endcond

public:

    /// Returns the default value for the attribute.
    /// @returns The default value for the attribute. The default is @c nullptr. Optional.
    ASPOSECPP_SHARED_API String get_DefaultValue();
    /// Sets the default value for the attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DefaultValue(const String& value);
    /// Returns the fixed value for the attribute.
    /// @returns The fixed value for the attribute. The default is null. Optional.
    ASPOSECPP_SHARED_API String get_FixedValue();
    /// Sets the fixed value for the attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_FixedValue(const String& value);
    /// Returns the form for the attribute.
    /// @returns One of the XmlSchemaForm values.
    /// The default is the XmlSchema::get_AttributeFormDefault value of the schema element containing the attribute.
    /// Optional.
    ASPOSECPP_SHARED_API XmlSchemaForm get_Form();
    /// Sets the form for the attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Form(XmlSchemaForm value);
    /// Returns the name of the attribute.
    /// @returns The name of the attribute.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the attribute.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns the name of an attribute declared in this schema (or another schema indicated by the specified namespace).
    /// @returns The name of the attribute declared.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_RefName();
    /// Sets the name of an attribute declared in this schema (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_RefName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the name of the simple type defined in this schema (or another schema indicated by the specified namespace).
    /// @returns The name of the simple type.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_SchemaTypeName();
    /// Sets the name of the simple type defined in this schema (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the attribute type to a simple type.
    /// @returns The simple type defined in this schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_SchemaType();
    /// Sets the attribute type to a simple type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaType(const SharedPtr<XmlSchemaSimpleType>& value);
    /// Returns information about how the attribute is used.
    /// @returns One of the following values: None, Prohibited, Optional, or Required. The default is Optional. Optional.
    ASPOSECPP_SHARED_API XmlSchemaUse get_Use();
    /// Sets information about how the attribute is used.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Use(XmlSchemaUse value);
    /// Returns the qualified name for the attribute.
    /// @returns The post-compilation interpretation of the @c QualifiedName value.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();
    /// Returns the object based on the XmlSchemaAttribute::get_SchemaType or
    /// XmlSchemaAttribute::get_SchemaTypeName value of the attribute that holds
    /// the post-compilation interpretation of the @c AttributeType value.
    /// @deprecated It is recommended to use get_AttributeSchemaType method instead.
    /// @returns The object that holds the post-compilation interpretation of the @c AttributeType value.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_AttributeType();
    /// Returns an XmlSchemaSimpleType object representing the type of the attribute based on
    /// the XmlSchemaAttribute::get_SchemaType or XmlSchemaAttribute::get_SchemaTypeName value of the attribute.
    /// @returns An XmlSchemaSimpleType object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> get_AttributeSchemaType();

    /// Initializes a new instance of the XmlSchemaAttribute class.
    ASPOSECPP_SHARED_API XmlSchemaAttribute();

protected:

    /// @cond
    SharedPtr<XmlSchemaDatatype> get_Datatype();
    SharedPtr<SchemaAttDef> get_AttDef();
    void set_AttDef(const SharedPtr<SchemaAttDef>& value);
    bool get_HasDefault();
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

    SharedPtr<XmlReader> Validate(const SharedPtr<XmlReader>& reader, const SharedPtr<XmlResolver>& resolver, const SharedPtr<XmlSchemaSet>& schemaSet, ValidationEventHandler valEventHandler);
    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);
    void SetAttributeType(const SharedPtr<XmlSchemaSimpleType>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaAttribute();

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
    const char* DBG_class_name() const override { return "XmlSchemaAttribute"; }
#endif
    /// @endcond

private:

    String _defaultValue;
    String _fixedValue;
    String _name;
    XmlSchemaForm _form;
    XmlSchemaUse _use;
    SharedPtr<XmlQualifiedName> _refName;
    SharedPtr<XmlQualifiedName> _typeName;
    SharedPtr<XmlQualifiedName> _qualifiedName;
    SharedPtr<XmlSchemaSimpleType> _type;
    SharedPtr<XmlSchemaSimpleType> _attributeType;
    SharedPtr<SchemaAttDef> _attDef;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


