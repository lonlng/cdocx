/// @file xml/schema/xml_schema.h

#pragma once

#include <xml/schema/xml_schema_object.h>
#include <xml/schema/xml_schema_form.h>
#include <xml/schema/xml_schema_derivation_method.h>
#include <xml/schema/validation_event_handler.h>
#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename> class IList;
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace IO
{
class Stream;
class TextReader;
class TextWriter;
} // namespace IO
class Uri;
namespace Xml
{
namespace Schema
{
class ChameleonKey;
class Compiler;
class Parser;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaInfo;
class XmlSchemaAnnotation;
class XmlSchemaCollection;
class XmlSchemaCompilationSettings;
class XmlSchemaObjectCollection;
class XmlSchemaObjectTable;
class XmlSchemaSet;
class XmlSchemaValidator;
class XsdBuilder;
class XsdValidator;
} // namespace Schema
class XmlAttribute;
class XmlDocument;
class XmlNamespaceManager;
class XmlNameTable;
class XmlReader;
class XmlResolver;
class XmlWriter;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// An in-memory representation of an XML Schema, as specified in the World Wide Web Consortium (W3C)
/// <a href="https://www.w3.org/TR/xmlschema-1/">XML Schema Part 1: Structures</a> and
/// <a href="https://www.w3.org/TR/xmlschema-2/">XML Schema Part 2: Datatypes</a>.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchema : public XmlSchemaObject
{
    typedef XmlSchema ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchema>;

private:
    /// @cond
    friend class ChameleonKey;
    friend class Parser;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchemaCollection;
    friend class XmlSchemaSet;
    friend class XmlSchemaValidator;
    friend class XsdBuilder;
    friend class XsdValidator;
    /// @endcond

public:

    /// The XML schema namespace. This field is constant.
    static const ASPOSECPP_SHARED_API String Namespace;
    /// The XML schema instance namespace. This field is constant.
    static const ASPOSECPP_SHARED_API String InstanceNamespace;

    /// Returns the form for attributes declared in the target namespace of the schema.
    /// @returns The XmlSchemaForm value that indicates if attributes from the target namespace are
    /// required to be qualified with the namespace prefix.
    /// The default is XmlSchemaForm::None.
    ASPOSECPP_SHARED_API XmlSchemaForm get_AttributeFormDefault();
    /// Sets the form for attributes declared in the target namespace of the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AttributeFormDefault(XmlSchemaForm value);
    /// Returns the @c blockDefault attribute which sets the default value of the @c block attribute on
    /// element and complex types in the @c targetNamespace of the schema.
    /// @returns An XmlSchemaDerivationMethod value representing the different methods for preventing derivation.
    /// The default value is XmlSchemaDerivationMethod::None.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_BlockDefault();
    /// Sets the @c blockDefault attribute which sets the default value of the @c block attribute on
    /// element and complex types in the @c targetNamespace of the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BlockDefault(XmlSchemaDerivationMethod value);
    /// Returns the @c finalDefault attribute which sets the default value of the @c final attribute on
    /// elements and complex types in the target namespace of the schema.
    /// @returns An XmlSchemaDerivationMethod value representing the different methods for preventing derivation.
    /// The default value is XmlSchemaDerivationMethod::None.
    ASPOSECPP_SHARED_API XmlSchemaDerivationMethod get_FinalDefault();
    /// Sets the @c finalDefault attribute which sets the default value of the @c final attribute on
    /// elements and complex types in the target namespace of the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_FinalDefault(XmlSchemaDerivationMethod value);
    /// Returns the form for elements declared in the target namespace of the schema.
    /// @returns The XmlSchemaForm value that indicates if elements from the target namespace are
    /// required to be qualified with the namespace prefix.
    /// The default is XmlSchemaForm::None.
    ASPOSECPP_SHARED_API XmlSchemaForm get_ElementFormDefault();
    /// Sets the form for elements declared in the target namespace of the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ElementFormDefault(XmlSchemaForm value);
    /// Returns the Uniform Resource Identifier (URI) of the schema target namespace.
    /// @returns The schema target namespace.
    ASPOSECPP_SHARED_API String get_TargetNamespace();
    /// Sets the Uniform Resource Identifier (URI) of the schema target namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_TargetNamespace(const String& value);
    /// Returns the version of the schema.
    /// @returns The version of the schema. The default value is String::Empty.
    ASPOSECPP_SHARED_API String get_Version();
    /// Sets the version of the schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Version(const String& value);
    /// Returns the collection of included and imported schemas.
    /// @returns An XmlSchemaObjectCollection of the included and imported schemas.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Includes();
    /// Returns the collection of schema elements in the schema and is used to add
    /// new element types at the @c schema element level.
    /// @returns An XmlSchemaObjectCollection of schema elements in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Items();
    /// Indicates if the schema has been compiled.
    /// @returns @c true if schema has been compiled, otherwise, @c false.
    /// The default value is @c false.
    ASPOSECPP_SHARED_API bool get_IsCompiled();
    /// Returns the post-schema-compilation value for all the attributes in the schema.
    /// @returns An XmlSchemaObjectTable collection of all the attributes in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_Attributes();
    /// Returns the post-schema-compilation value of all the global attribute groups in the schema.
    /// @returns An XmlSchemaObjectTable collection of all the global attribute groups in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_AttributeGroups();
    /// Returns the post-schema-compilation value of all schema types in the schema.
    /// @returns An XmlSchemaObjectCollection of all schema types in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_SchemaTypes();
    /// Returns the post-schema-compilation value for all the elements in the schema.
    /// @returns An XmlSchemaObjectTable collection of all the elements in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_Elements();
    /// Returns the string ID.
    /// @returns The ID of the string. The default value is String::Empty.
    ASPOSECPP_SHARED_API String get_Id();
    /// Sets the string ID.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Id(const String& value);
    /// Returns the qualified attributes which do not belong to the schema target namespace.
    /// @returns An array of qualified XmlAttribute objects that do not belong to the schema target namespace.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlAttribute>> get_UnhandledAttributes();
    /// Sets the qualified attributes which do not belong to the schema target namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_UnhandledAttributes(const ArrayPtr<SharedPtr<XmlAttribute>>& value);
    /// Returns the post-schema-compilation value of all the groups in the schema.
    /// @returns An XmlSchemaObjectTable collection of all the groups in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_Groups();
    /// Returns the post-schema-compilation value for all notations in the schema.
    /// @returns An XmlSchemaObjectTable collection of all notations in the schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_Notations();

    /// Initializes a new instance of the XmlSchema class.
    ASPOSECPP_SHARED_API XmlSchema();

    /// Reads an XML Schema from the supplied IO::TextReader.
    /// @param reader The IO::TextReader containing the XML Schema to read.
    /// @param validationEventHandler The validation event handler that receives information about the XML Schema syntax errors.
    /// @returns The XmlSchema object representing the XML Schema.
    /// @throws XmlSchemaException An XmlSchemaException is raised if no ValidationEventHandler is specified.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Read(const SharedPtr<IO::TextReader>& reader, ValidationEventHandler validationEventHandler);
    /// Reads an XML Schema  from the supplied stream.
    /// @param stream The supplied data stream.
    /// @param validationEventHandler The validation event handler that receives information about XML Schema syntax errors.
    /// @returns The XmlSchema object representing the XML Schema.
    /// @throws XmlSchemaException An XmlSchemaException is raised if no ValidationEventHandler is specified.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Read(const SharedPtr<IO::Stream>& stream, ValidationEventHandler validationEventHandler);
    /// Reads an XML Schema from the supplied XmlReader.
    /// @param reader The XmlReader containing the XML Schema to read.
    /// @param validationEventHandler The validation event handler that receives information about the XML Schema syntax errors.
    /// @returns The XmlSchema object representing the XML Schema.
    /// @throws XmlSchemaException An XmlSchemaException is raised if no ValidationEventHandler is specified.
    static ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Read(const SharedPtr<XmlReader>& reader, ValidationEventHandler validationEventHandler);
    /// Writes the XML Schema to the supplied data stream.
    /// @param stream The supplied data stream.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<IO::Stream>& stream);
    /// Writes the XML Schema to the supplied Stream using the XmlNamespaceManager specified.
    /// @param stream The supplied data stream.
    /// @param namespaceManager The XmlNamespaceManager.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<IO::Stream>& stream, const SharedPtr<XmlNamespaceManager>& namespaceManager);
    /// Writes the XML Schema to the supplied IO::TextWriter.
    /// @param writer The IO::TextWriter to write to.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<IO::TextWriter>& writer);
    /// Writes the XML Schema to the supplied TextWriter.
    /// @param writer The IO::TextWriter to write to.
    /// @param namespaceManager The XmlNamespaceManager.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<IO::TextWriter>& writer, const SharedPtr<XmlNamespaceManager>& namespaceManager);
    /// Writes the XML Schema to the supplied XmlWriter.
    /// @param writer The XmlWriter to write to.
    /// @throws ArgumentNullException The @p writer parameter is null.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<XmlWriter>& writer);
    /// Writes the XML Schema to the supplied XmlWriter.
    /// @param writer The XmlWriter to write to.
    /// @param namespaceManager The XmlNamespaceManager.
    ASPOSECPP_SHARED_API void Write(const SharedPtr<XmlWriter>& writer, const SharedPtr<XmlNamespaceManager>& namespaceManager);
    /// Compiles the XML Schema Object Model (SOM) into schema information for validation.
    /// Used to check the syntactic and semantic structure of the programmatically built SOM.
    /// Semantic validation checking is performed during compilation.
    /// @param validationEventHandler The validation event handler that receives information about XML Schema validation errors.
    ASPOSECPP_SHARED_API void Compile(ValidationEventHandler validationEventHandler);
    /// Compiles the XML Schema Object Model (SOM) into schema information for validation.
    /// Used to check the syntactic and semantic structure of the programmatically built SOM.
    /// Semantic validation checking is performed during compilation.
    /// @param validationEventHandler The validation event handler that receives information about the XML Schema validation errors.
    /// @param resolver The XmlResolver used to resolve namespaces referenced in @c include and @c import elements.
    ASPOSECPP_SHARED_API void Compile(ValidationEventHandler validationEventHandler, const SharedPtr<XmlResolver>& resolver);

protected:

    /// @cond
    bool get_IsCompiledBySet();
    void set_IsCompiledBySet(bool value);
    bool get_IsPreprocessed();
    void set_IsPreprocessed(bool value);
    bool get_IsRedefined();
    void set_IsRedefined(bool value);
    SharedPtr<XmlSchemaObjectTable> get_IdentityConstraints();
    SharedPtr<Uri> get_BaseUri();
    void set_BaseUri(const SharedPtr<Uri>& value);
    int32_t get_SchemaId();
    bool get_IsChameleon();
    void set_IsChameleon(bool value);
    SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<XmlSchemaObject>>> get_Ids();
    SharedPtr<XmlDocument> get_Document();
    int32_t get_ErrorCount();
    void set_ErrorCount(int32_t value);
    ASPOSECPP_SHARED_API String get_IdAttribute() override;
    ASPOSECPP_SHARED_API void set_IdAttribute(String value) override;
    SharedPtr<XmlNameTable> get_NameTable();
    SharedPtr<Collections::Generic::List<SharedPtr<XmlSchema>>> get_ImportedSchemas();
    SharedPtr<Collections::Generic::List<String>> get_ImportedNamespaces();

    bool CompileSchema(const SharedPtr<XmlSchemaCollection>& xsc, const SharedPtr<XmlResolver>& resolver, const SharedPtr<SchemaInfo>& schemaInfo, const String& ns, ValidationEventHandler validationEventHandler, const SharedPtr<XmlNameTable>& nameTable, bool CompileContentModel);
    void CompileSchemaInSet(const SharedPtr<XmlNameTable>& nameTable, ValidationEventHandler eventHandler, const SharedPtr<XmlSchemaCompilationSettings>& compilationSettings);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    SharedPtr<XmlSchema> DeepClone();
    void SetIsCompiled(bool isCompiled);
    ASPOSECPP_SHARED_API void SetUnhandledAttributes(ArrayPtr<SharedPtr<XmlAttribute>> moreAttributes) override;
    ASPOSECPP_SHARED_API void AddAnnotation(SharedPtr<XmlSchemaAnnotation> annotation) override;
    void GetExternalSchemasList(const SharedPtr<Collections::Generic::IList<SharedPtr<XmlSchema>>>& extList, const SharedPtr<XmlSchema>& schema);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchema();

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
    const char* DBG_class_name() const override { return "XmlSchema"; }
#endif

    /// @endcond

private:

    XmlSchemaForm _attributeFormDefault;
    XmlSchemaForm _elementFormDefault;
    XmlSchemaDerivationMethod _blockDefault;
    XmlSchemaDerivationMethod _finalDefault;
    String _targetNs;
    String _version;
    SharedPtr<XmlSchemaObjectCollection> _includes;
    SharedPtr<XmlSchemaObjectCollection> _items;
    String _id;
    ArrayPtr<SharedPtr<XmlAttribute>> _moreAttributes;
    bool _isCompiled;
    bool _isCompiledBySet;
    bool _isPreprocessed;
    bool _isRedefined;
    int32_t _errorCount;
    SharedPtr<XmlSchemaObjectTable> _attributes;
    SharedPtr<XmlSchemaObjectTable> _attributeGroups;
    SharedPtr<XmlSchemaObjectTable> _elements;
    SharedPtr<XmlSchemaObjectTable> _types;
    SharedPtr<XmlSchemaObjectTable> _groups;
    SharedPtr<XmlSchemaObjectTable> _notations;
    SharedPtr<XmlSchemaObjectTable> _identityConstraints;
    static int32_t s_globalIdCounter;
    SharedPtr<Collections::Generic::List<SharedPtr<XmlSchema>>> _importedSchemas;
    SharedPtr<Collections::Generic::List<String>> _importedNamespaces;
    int32_t _schemaId;
    SharedPtr<Uri> _baseUri;
    bool _isChameleon;
    System::DynamicWeakPtr<Collections::Generic::Dictionary<String, SharedPtr<XmlSchemaObject>>, System::SmartPtrMode::Shared, 1> _ids;
    SharedPtr<XmlDocument> _document;
    SharedPtr<XmlNameTable> _nameTable;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


