/// @file xml/schema/xml_schema_element.h

#pragma once

#include <xml/schema/xml_schema_particle.h>
#include <xml/schema/xml_schema_form.h>
#include <xml/schema/xml_schema_derivation_method.h>
#include <xml/schema/validation_event_handler.h>
#include <system/string.h>
#include <system/enum_helpers.h>


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
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaElementDecl;
class XmlSchema;
class XmlSchemaComplexType;
class XmlSchemaInference;
class XmlSchemaInfo;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaSet;
class XmlSchemaType;
class XmlSchemaValidator;
class XsdValidator;
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

/// Represents the @c element element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class is the base class for all particle types and is used to describe an element in an XML document.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaElement : public XmlSchemaParticle
{
    typedef XmlSchemaElement ThisType;
    typedef XmlSchemaParticle BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaElement>;

private:
    /// @cond
    friend class XPath::XPathNavigator;
    friend class System::Xml::DocumentSchemaValidator;
    friend class XmlSchemaInference;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchema;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaInfo;
    friend class XmlSchemaValidator;
    friend class XsdValidator;
    /// @endcond

public:

    /// Returns information to indicate if the element can be used in an instance document.
    /// @returns If @c true, the element cannot appear in the instance document. The default is @c false. Optional.
    ASPOSECPP_SHARED_API bool get_IsAbstract();
    /// Sets information to indicate if the element can be used in an instance document.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsAbstract(bool value);
    /// Returns a @c Block derivation.
    /// @returns The attribute used to block a type derivation.
    /// Default value is XmlSchemaDerivationMethod::None. Optional.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_Block();
    /// Sets a @c Block derivation.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Block(XmlSchemaDerivationMethod value);
    /// Returns the default value of the element if its content is a simple type or content of the element is @c textOnly.
    /// @returns The default value for the element. The default is @c nullptr. Optional.
    ASPOSECPP_SHARED_API String get_DefaultValue();
    /// Sets the default value of the element if its content is a simple type or content of the element is @c textOnly.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DefaultValue(const String& value);
    /// Returns the @c Final value to indicate that no further derivations are allowed.
    /// @returns The @c Final value. The default is XmlSchemaDerivationMethod::None. Optional.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_Final();
    /// Sets the @c Final value to indicate that no further derivations are allowed.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Final(XmlSchemaDerivationMethod value);
    /// Returns the fixed value.
    /// @returns The fixed value that is predetermined and unchangeable. The default is @c nullptr. Optional.
    ASPOSECPP_SHARED_API String get_FixedValue();
    /// Sets the fixed value.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_FixedValue(const String& value);
    /// Returns the form for the element.
    /// @returns The form for the element. The default is the XmlSchema::get_ElementFormDefault value. Optional.
    ASPOSECPP_SHARED_API XmlSchemaForm get_Form();
    /// Sets the form for the element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Form(XmlSchemaForm value);
    /// Returns the name of the element.
    /// @returns The name of the element. The default is String::Empty.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns information that indicates if @c xsi:nil can occur in the instance data.
    /// Indicates if an explicit nil value can be assigned to the element.
    /// @returns If nillable is @c true, this enables an instance of the element to have the @c nil attribute set to @c true.
    /// The @c nil attribute is defined as part of the XML Schema namespace for instances.
    /// The default is @c false. Optional.
    ASPOSECPP_SHARED_API bool get_IsNillable();
    /// Sets information that indicates if @c xsi:nil can occur in the instance data.
    /// Indicates if an explicit nil value can be assigned to the element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsNillable(bool value);
    /// Returns the reference name of an element declared in this schema (or another schema indicated by the specified namespace).
    /// @returns The reference name of the element.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_RefName();
    /// Sets the reference name of an element declared in this schema (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_RefName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the name of an element that is being substituted by this element.
    /// @returns The qualified name of an element that is being substituted by this element. Optional.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_SubstitutionGroup();
    /// Sets the name of an element that is being substituted by this element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SubstitutionGroup(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the name of a built-in data type defined in this schema or another schema indicated by the specified namespace.
    /// @returns The name of the built-in data type.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_SchemaTypeName();
    /// Sets the name of a built-in data type defined in this schema or another schema indicated by the specified namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns the type of the element. This can either be a complex type or a simple type.
    /// @returns The type of the element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaType> get_SchemaType();
    /// Sets the type of the element. This can either be a complex type or a simple type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SchemaType(const SharedPtr<XmlSchemaType>& value);
    /// Returns the collection of constraints on the element.
    /// @returns The collection of constraints.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Constraints();
    /// Returns the actual qualified name for the given element.
    /// @returns The qualified name of the element. The post-compilation interpretation of the @c QualifiedName value.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();
    /// Returns an object based on the XmlSchemaElement or XmlSchemaElement of the element,
    /// which holds the post-compilation interpretation of the @c ElementType value.
    /// @returns The run-time object. The post-compilation interpretation of the @c ElementType value.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_ElementType();
    /// Returns an XmlSchemaType object representing the type of the element based on
    /// the XmlSchemaElement::get_SchemaType or XmlSchemaElement::get_SchemaTypeName values of the element.
    /// @returns An XmlSchemaType object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaType> get_ElementSchemaType();
    /// Returns the post-compilation interpretation of the @c Block value.
    /// @returns The post-compilation interpretation of the @c Block value.
    /// The default is the @c BlockDefault value on the @c schema element.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_BlockResolved();
    /// Returns the post-compilation interpretation of the @c Final value.
    /// @returns The post-compilation interpretation of the @c Final value.
    /// Default value is the @c FinalDefault value on the @c schema element.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_FinalResolved();

    /// Initializes a new instance of the XmlSchemaElement class.
    ASPOSECPP_SHARED_API XmlSchemaElement();

protected:

    /// @cond
    bool get_HasNillableAttribute();
    bool get_HasAbstractAttribute();
    bool get_HasDefault();
    bool get_HasConstraints();
    bool get_IsLocalTypeDerivationChecked();
    void set_IsLocalTypeDerivationChecked(bool value);
    SharedPtr<SchemaElementDecl> get_ElementDecl();
    void set_ElementDecl(const SharedPtr<SchemaElementDecl>& value);
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;
    ASPOSECPP_SHARED_API String get_NameString() override;

    SharedPtr<XmlReader> Validate(const SharedPtr<XmlReader>& reader, const SharedPtr<XmlResolver>& resolver, const SharedPtr<XmlSchemaSet>& schemaSet, ValidationEventHandler valEventHandler);
    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);
    void SetElementType(const SharedPtr<XmlSchemaType>& value);
    void SetBlockResolved(XmlSchemaDerivationMethod value);
    void SetFinalResolved(XmlSchemaDerivationMethod value);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    SharedPtr<XmlSchemaObject> Clone(const SharedPtr<XmlSchema>& parentSchema);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaElement();

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
    const char* DBG_class_name() const override { return "XmlSchemaElement"; }
#endif
    /// @endcond

private:

    bool _isAbstract;
    bool _hasAbstractAttribute;
    bool _isNillable;
    bool _hasNillableAttribute;
    bool _isLocalTypeDerivationChecked;
    XmlSchemaDerivationMethod _block;
    XmlSchemaDerivationMethod _final;
    XmlSchemaForm _form;
    String _defaultValue;
    String _fixedValue;
    String _name;
    SharedPtr<XmlQualifiedName> _refName;
    SharedPtr<XmlQualifiedName> _substitutionGroup;
    SharedPtr<XmlQualifiedName> _typeName;
    SharedPtr<XmlSchemaType> _type;
    SharedPtr<XmlQualifiedName> _qualifiedName;
    WeakPtr<XmlSchemaType> _elementType;
    XmlSchemaDerivationMethod _blockResolved;
    XmlSchemaDerivationMethod _finalResolved;
    SharedPtr<XmlSchemaObjectCollection> _constraints;
    SharedPtr<SchemaElementDecl> _elementDecl;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


