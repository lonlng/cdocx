/// @file xml/schema/xml_schema_type.h

#pragma once

#include <xml/schema/xml_type_code.h>
#include <xml/schema/xml_schema_derivation_method.h>
#include <xml/schema/xml_schema_annotated.h>
#include <xml/schema/validation_event_handler.h>
#include <system/string.h>
#include <system/enum_helpers.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class BaseProcessor;
class Compiler;
class Datatype_List;
class DatatypeImplementation;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaElementDecl;
class XmlAtomicValue;
class XmlSchemaComplexType;
enum class XmlSchemaContentType;
class XmlSchemaDatatype;
class XmlSchemaInfo;
class XmlSchemaSet;
class XmlSchemaSimpleType;
class XmlSchemaValidator;
class XmlUnionConverter;
class XmlValueConverter;
class XsdValidator;
} // namespace Schema
class XmlQualifiedName;
class XmlReader;
class XmlResolver;
class XmlSqlBinaryReader;
namespace XPath
{
class XPathNavigator;
} // namespace XPath
class XsdValidatingReader;
namespace Xsl
{
class XmlQueryTypeFactory;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// The base class for all simple types and complex types.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaType : public XmlSchemaAnnotated
{
    typedef XmlSchemaType ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaType>;

private:
    /// @cond
    friend class System::Xml::XmlSqlBinaryReader;
    friend class XPath::XPathNavigator;
    friend class System::Xml::XsdValidatingReader;
    friend class BaseProcessor;
    friend class DatatypeImplementation;
    friend class Datatype_List;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlAtomicValue;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaInfo;
    friend class XmlSchemaValidator;
    friend class XmlUnionConverter;
    friend class XsdValidator;
    friend class Xsl::XmlQueryTypeFactory;
    friend class Xsl::XmlQueryTypeFactory;
    /// @endcond

public:

    /// Returns the name of the type.
    /// @returns The name of the type.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns the final attribute of the type derivation that indicates if further derivations are allowed.
    /// @returns One of the valid XmlSchemaDerivationMethod values. The default is XmlSchemaDerivationMethod::None.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_Final();
    /// Sets the final attribute of the type derivation that indicates if further derivations are allowed.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Final(XmlSchemaDerivationMethod value);
    /// Returns the qualified name for the type built from the @c Name attribute of this type.
    /// This is a post-schema-compilation value.
    /// @returns The XmlQualifiedName for the type built from the @c Name attribute of this type.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();
    /// Returns the post-compilation interpretation of the XmlSchemaType::get_Final value.
    /// @returns The post-compilation interpretation of the XmlSchemaType::get_Final value.
    /// The default is the @c finalDefault attribute value of the @c schema element.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_FinalResolved();
    /// Returns the post-compilation object type or the built-in XML Schema Definition Language (XSD) data type,
    /// simpleType element, or complexType element.
    /// This is a post-schema-compilation infoset value.
    /// @returns The built-in XSD data type, simpleType element, or complexType element.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_BaseSchemaType();
    /// Returns the post-compilation value for the base type of this schema type.
    /// @returns An XmlSchemaType object representing the base type of this schema type.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaType> get_BaseXmlSchemaType();
    /// Returns the post-compilation information on how this element was derived from its base type.
    /// @returns One of the valid XmlSchemaDerivationMethod values.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_DerivedBy();
    /// Returns the post-compilation value for the data type of the complex type.
    /// @returns The XmlSchemaDatatype post-schema-compilation value.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaDatatype> get_Datatype();
    /// Returns a value indicating if this type has a mixed content model. This call is only valid in a complex type.
    /// @returns @c true if the type has a mixed content model; otherwise, @c false. The default is @c false.
    virtual ASPOSECPP_SHARED_API bool get_IsMixed();
    /// Sets a value indicating if this type has a mixed content model. This call is only valid in a complex type.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_IsMixed(bool value);
    /// Returns the XmlTypeCode of the type.
    /// @returns One of the XmlTypeCode values.
    ASPOSECPP_SHARED_API XmlTypeCode get_TypeCode();

    /// Returns an XmlSchemaSimpleType that represents the built-in simple type of the simple type that is specified by the qualified name.
    /// @param qualifiedName The XmlQualifiedName of the simple type.
    /// @returns The XmlSchemaSimpleType that represents the built-in simple type.
    /// @throws ArgumentNullException The XmlQualifiedName parameter is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> GetBuiltInSimpleType(const SharedPtr<XmlQualifiedName>& qualifiedName);
    /// Returns an XmlSchemaSimpleType that represents the built-in simple type of the specified simple type.
    /// @param typeCode One of the XmlTypeCode values representing the simple type.
    /// @returns The XmlSchemaSimpleType that represents the built-in simple type.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleType> GetBuiltInSimpleType(XmlTypeCode typeCode);
    /// Returns an XmlSchemaComplexType that represents the built-in complex type of the complex type specified.
    /// @param typeCode One of the XmlTypeCode values representing the complex type.
    /// @returns The XmlSchemaComplexType that represents the built-in complex type.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchemaComplexType> GetBuiltInComplexType(XmlTypeCode typeCode);
    /// Returns an XmlSchemaComplexType that represents the built-in complex type of the complex type specified by qualified name.
    /// @param qualifiedName The XmlQualifiedName of the complex type.
    /// @returns The XmlSchemaComplexType that represents the built-in complex type.
    /// @throws ArgumentNullException The XmlQualifiedName parameter is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchemaComplexType> GetBuiltInComplexType(const SharedPtr<XmlQualifiedName>& qualifiedName);
    /// Returns a value indicating if the derived schema type specified is derived from the base schema type specified.
    /// @param derivedType The derived XmlSchemaType to test.
    /// @param baseType The base XmlSchemaType to test the derived XmlSchemaType against.
    /// @param except One of the XmlSchemaDerivationMethod values representing a type derivation method to exclude from testing.
    /// @returns @c true if the derived type is derived from the base type; otherwise, @c false.
    static ASPOSECPP_SHARED_API bool IsDerivedFrom(SharedPtr<XmlSchemaType> derivedType, const SharedPtr<XmlSchemaType>& baseType, XmlSchemaDerivationMethod except);

    /// Initializes a new instance of the XmlSchemaType class.
    ASPOSECPP_SHARED_API XmlSchemaType();

protected:

    /// @cond
    SharedPtr<XmlValueConverter> get_ValueConverter();
    XmlSchemaContentType get_SchemaContentType();
    SharedPtr<SchemaElementDecl> get_ElementDecl();
    void set_ElementDecl(const SharedPtr<SchemaElementDecl>& value);
    SharedPtr<XmlSchemaType> get_Redefined();
    void set_Redefined(const SharedPtr<XmlSchemaType>& value);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_DerivedFrom();
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

    SharedPtr<XmlReader> Validate(const SharedPtr<XmlReader>& reader, const SharedPtr<XmlResolver>& resolver, const SharedPtr<XmlSchemaSet>& schemaSet, ValidationEventHandler valEventHandler);
    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);
    void SetFinalResolved(XmlSchemaDerivationMethod value);
    void SetBaseSchemaType(const SharedPtr<XmlSchemaType>& value);
    void SetDerivedBy(XmlSchemaDerivationMethod value);
    void SetDatatype(const SharedPtr<XmlSchemaDatatype>& value);
    void SetContentType(XmlSchemaContentType value);
    static bool IsDerivedFromDatatype(const SharedPtr<XmlSchemaDatatype>& derivedDataType, const SharedPtr<XmlSchemaDatatype>& baseDataType, XmlSchemaDerivationMethod except);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaType();

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
    const char* DBG_class_name() const override { return "XmlSchemaType"; }
#endif
    /// @endcond

private:

    String _name;
    XmlSchemaDerivationMethod _final;
    XmlSchemaDerivationMethod _derivedBy;
    SharedPtr<XmlSchemaType> _baseSchemaType;
    SharedPtr<XmlSchemaDatatype> _datatype;
    XmlSchemaDerivationMethod _finalResolved;
    SharedPtr<SchemaElementDecl> _elementDecl;
    SharedPtr<XmlQualifiedName> _qname;
    SharedPtr<XmlSchemaType> _redefined;
    XmlSchemaContentType _contentType;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


