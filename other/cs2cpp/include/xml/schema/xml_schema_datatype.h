/// @file xml/schema/xml_schema_datatype.h

#pragma once

#include <xml/schema/xml_type_code.h>
#include <xml/schema/xml_tokenized_type.h>
#include <xml/schema/xml_schema_datatype_variety.h>
#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
class TypeInfo;
namespace Xml
{
class IXmlNamespaceResolver;
namespace Schema
{
class AutoValidator;
class BinaryFacetsChecker;
class Compiler;
class Datatype_List;
class Datatype_union;
class DatatypeImplementation;
class DateTimeFacetsChecker;
class DurationFacetsChecker;
class FacetsChecker;
class ListFacetsChecker;
class Numeric10FacetsChecker;
class Numeric2FacetsChecker;
class Preprocessor;
class QNameFacetsChecker;
class RestrictionFacets;
class SchemaAttDef;
class SchemaCollectionCompiler;
class SchemaDeclBase;
class SchemaNames;
class StringFacetsChecker;
class TypedObject;
class UnionFacetsChecker;
class XdrBuilder;
class XdrValidator;
class XmlSchemaObject;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
class XmlSchemaSimpleType;
class XmlSchemaType;
class XmlSchemaValidator;
enum class XmlSchemaWhiteSpace;
class XmlUnionConverter;
class XmlValueConverter;
class XsdBuilder;
class XsdValidator;
} // namespace Schema
class XmlNameTable;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// The XmlSchemaDatatype class is an abstract class for mapping XML Schema definition language (XSD) types to runtime types.
class ASPOSECPP_SHARED_CLASS XmlSchemaDatatype : public System::Object
{
    typedef XmlSchemaDatatype ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaDatatype>;

private:
    /// @cond
    friend class AutoValidator;
    friend class TypedObject;
    friend class DatatypeImplementation;
    friend class Datatype_List;
    friend class Datatype_union;
    friend class FacetsChecker;
    friend class FacetsChecker;
    friend class Numeric10FacetsChecker;
    friend class Numeric2FacetsChecker;
    friend class DurationFacetsChecker;
    friend class DateTimeFacetsChecker;
    friend class StringFacetsChecker;
    friend class QNameFacetsChecker;
    friend class BinaryFacetsChecker;
    friend class ListFacetsChecker;
    friend class UnionFacetsChecker;
    friend class Preprocessor;
    friend class SchemaAttDef;
    friend class SchemaDeclBase;
    friend class SchemaCollectionCompiler;
    friend class SchemaNames;
    friend class Compiler;
    friend class XdrBuilder;
    friend class XdrBuilder;
    friend class XdrValidator;
    friend class XmlSchemaType;
    friend class XmlSchemaValidator;
    friend class XmlUnionConverter;
    friend class XsdBuilder;
    friend class XsdValidator;
    /// @endcond

public:

    /// When overridden in a derived class, gets the type of the item.
    /// @returns The type of the item.
    virtual ASPOSECPP_SHARED_API TypeInfo get_ValueType() = 0;
    /// When overridden in a derived class, gets the type for the @c string as specified in
    /// the World Wide Web Consortium (W3C) XML 1.0 specification.
    /// @returns An XmlTokenizedType value for the @c string.
    virtual ASPOSECPP_SHARED_API XmlTokenizedType get_TokenizedType() = 0;
    /// Returns the XmlSchemaDatatypeVariety value for the simple type.
    /// @returns The XmlSchemaDatatypeVariety value for the simple type.
    virtual ASPOSECPP_SHARED_API XmlSchemaDatatypeVariety get_Variety();
    /// Returns the XmlTypeCode value for the simple type.
    /// @returns The XmlTypeCode value for the simple type.
    virtual ASPOSECPP_SHARED_API XmlTypeCode get_TypeCode();

    /// When overridden in a derived class, validates the @c string specified against a built-in or user-defined simple type.
    /// @param s The @c string to validate against the simple type.
    /// @param nameTable The XmlNameTable to use for atomization while parsing the @c string if
    /// this XmlSchemaDatatype object represents the @c xs:NCName type.
    /// @param nsmgr The IXmlNamespaceResolver object to use while parsing the @c string if
    /// this XmlSchemaDatatype object represents the @c xs:QName type.
    /// @returns An Object that can be cast safely to the type returned by the XmlSchemaDatatype::get_ValueType call.
    /// @throws XmlSchemaValidationException The input value is not a valid instance of this W3C XML Schema type.
    /// @throws ArgumentNullException The value to parse cannot be @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ParseValue(String s, SharedPtr<XmlNameTable> nameTable, SharedPtr<IXmlNamespaceResolver> nsmgr) = 0;
    /// Converts the value specified, whose type is one of the valid representations of the XML schema type
    /// represented by the XmlSchemaDatatype, to the run-time type specified.
    /// @param value The input value to convert to the specified type.
    /// @param targetType The target type to convert the input value to.
    /// @returns The converted input value.
    /// @throws ArgumentNullException The Object or Type parameter is @c nullptr.
    /// @throws InvalidCastException The type represented by the XmlSchemaDatatype does not support
    /// a conversion from type of the value specified to the type specified.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ChangeType(SharedPtr<Object> value, const TypeInfo& targetType);
    /// Converts the value specified, whose type is one of the valid representations of the XML schema type
    /// represented by the XmlSchemaDatatype, to the run-time type specified using the IXmlNamespaceResolver if
    /// the XmlSchemaDatatype represents the @c xs:QName type or a type derived from it.
    /// @param value The input value to convert to the specified type.
    /// @param targetType The target type to convert the input value to.
    /// @param namespaceResolver An IXmlNamespaceResolver used for resolving namespace prefixes.
    /// This is only of use if the XmlSchemaDatatype represents the @c xs:QName type or a type derived from it.
    /// @returns The converted input value.
    /// @throws ArgumentNullException The Object or Type parameter is @c nullptr.
    /// @throws InvalidCastException The type represented by the XmlSchemaDatatype does not support
    /// a conversion from type of the value specified to the type specified.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ChangeType(SharedPtr<Object> value, const TypeInfo& targetType, SharedPtr<IXmlNamespaceResolver> namespaceResolver);
    /// This method always returns @c false.
    /// @param datatype The XmlSchemaDatatype.
    /// @returns Always returns @c false.
    virtual ASPOSECPP_SHARED_API bool IsDerivedFrom(SharedPtr<XmlSchemaDatatype> datatype);

protected:

    /// @cond
    virtual bool get_HasLexicalFacets() = 0;
    virtual bool get_HasValueFacets() = 0;
    virtual SharedPtr<XmlValueConverter> get_ValueConverter() = 0;
    virtual SharedPtr<RestrictionFacets> get_Restriction() = 0;
    virtual void set_Restriction(SharedPtr<RestrictionFacets> value) = 0;
    virtual SharedPtr<System::Xml::Schema::FacetsChecker> get_FacetsChecker() = 0;
    virtual XmlSchemaWhiteSpace get_BuiltInWhitespaceFacet() = 0;
    String get_TypeCodeString();

    virtual int32_t Compare(SharedPtr<Object> value1, SharedPtr<Object> value2) = 0;
    virtual SharedPtr<Object> ParseValue(String s, SharedPtr<XmlNameTable> nameTable, SharedPtr<IXmlNamespaceResolver> nsmgr, bool createAtomicValue) = 0;
    virtual Exception TryParseValue(String s, SharedPtr<XmlNameTable> nameTable, SharedPtr<IXmlNamespaceResolver> nsmgr, SharedPtr<Object>& typedValue) = 0;
    virtual Exception TryParseValue(SharedPtr<Object> value, SharedPtr<XmlNameTable> nameTable, SharedPtr<IXmlNamespaceResolver> namespaceResolver, SharedPtr<Object>& typedValue) = 0;
    virtual SharedPtr<XmlSchemaDatatype> DeriveByRestriction(SharedPtr<XmlSchemaObjectCollection> facets, SharedPtr<XmlNameTable> nameTable, SharedPtr<XmlSchemaType> schemaType) = 0;
    virtual SharedPtr<XmlSchemaDatatype> DeriveByList(SharedPtr<XmlSchemaType> schemaType) = 0;
    virtual void VerifySchemaValid(SharedPtr<XmlSchemaObjectTable> notations, SharedPtr<XmlSchemaObject> caller) = 0;
    virtual bool IsEqual(SharedPtr<Object> o1, SharedPtr<Object> o2) = 0;
    virtual bool IsComparable(SharedPtr<XmlSchemaDatatype> dtype) = 0;
    String TypeCodeToString(XmlTypeCode typeCode);
    static String ConcatenatedToString(const SharedPtr<Object>& value);
    static SharedPtr<XmlSchemaDatatype> FromXmlTokenizedType(XmlTokenizedType token);
    static SharedPtr<XmlSchemaDatatype> FromXmlTokenizedTypeXsd(XmlTokenizedType token);
    static SharedPtr<XmlSchemaDatatype> FromXdrName(const String& name);
    static SharedPtr<XmlSchemaDatatype> DeriveByUnion(const ArrayPtr<SharedPtr<XmlSchemaSimpleType>>& types, const SharedPtr<XmlSchemaType>& schemaType);
    static String XdrCanonizeUri(const String& uri, const SharedPtr<XmlNameTable>& nameTable, const SharedPtr<SchemaNames>& schemaNames);
    /// @endcond

};

} // namespace Schema
} // namespace Xml
} // namespace System


