/// @file xml/schema/xml_schema_set.h

#pragma once

#include <xml/schema/validation_event_handler.h>
#include <system/exceptions.h>
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
template <typename, typename> class KeyValuePair;
template <typename> class List;
template <typename, typename> class SortedList;
} // namespace Generic
} // namespace Collections
class Uri;
namespace Xml
{
namespace Schema
{
class ChameleonKey;
class Compiler;
class ContentValidator;
class SchemaInfo;
class SchemaNames;
class ValidationEventArgs;
class XmlSchema;
class XmlSchemaCompilationSettings;
class Details_XmlSchemaException; using XmlSchemaException = System::ExceptionWrapper<Details_XmlSchemaException>;
class XmlSchemaObject;
class XmlSchemaObjectTable;
class XmlSchemaSubstitutionGroup;
class XmlSchemaValidator;
enum class XmlSeverityType;
} // namespace Schema
class XmlNameTable;
class XmlQualifiedName;
class XmlReader;
class XmlReaderSettings;
class XmlResolver;
class XsdValidatingReader;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Contains a cache of XML Schema definition language (XSD) schemas.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSet : public System::Object
{
    typedef XmlSchemaSet ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSet>;

private:
    /// @cond
    friend class System::Xml::XsdValidatingReader;
    friend class ContentValidator;
    friend class Compiler;
    friend class XmlSchemaValidator;
    /// @endcond

public:

    /// Returns the default XmlNameTable used by the XmlSchemaSet when loading new XML Schema definition language (XSD) schemas.
    /// @returns A table of atomized string objects.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();
    /// Returns a value that indicates whether the XML Schema definition language (XSD) schemas in the XmlSchemaSet have been compiled.
    /// @returns @c true if the schemas in the XmlSchemaSet have been compiled since the last time
    /// a schema was added or removed from the XmlSchemaSet; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_IsCompiled();
    /// Sets the XmlResolver used to resolve namespaces or locations referenced in include and import elements of a schema.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);
    /// Returns the XmlSchemaCompilationSettings for the XmlSchemaSet.
    /// @returns The XmlSchemaCompilationSettings for the XmlSchemaSet.
    /// The default is an XmlSchemaCompilationSettings instance with
    /// the XmlSchemaCompilationSettings::set_EnableUpaCheck value set to @c true.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaCompilationSettings> get_CompilationSettings();
    /// Sets the XmlSchemaCompilationSettings for the XmlSchemaSet.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CompilationSettings(const SharedPtr<XmlSchemaCompilationSettings>& value);
    /// Returns the number of logical XML Schema definition language (XSD) schemas in the XmlSchemaSet.
    /// @returns The number of logical schemas in the XmlSchemaSet.
    ASPOSECPP_SHARED_API int32_t get_Count();
    /// Returns all the global elements in all the XML Schema definition language (XSD) schemas in the XmlSchemaSet.
    /// @returns The collection of global elements.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_GlobalElements();
    /// Returns all the global attributes in all the XML Schema definition language (XSD) schemas in the XmlSchemaSet.
    /// @returns The collection of global attributes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_GlobalAttributes();
    /// Returns all of the global simple and complex types in all the XML Schema definition language (XSD) schemas in the XmlSchemaSet.
    /// @returns The collection of global simple and complex types.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectTable> get_GlobalTypes();

    /// Initializes a new instance of the XmlSchemaSet class.
    ASPOSECPP_SHARED_API XmlSchemaSet();
    /// Initializes a new instance of the XmlSchemaSet class with the specified XmlNameTable.
    /// @param nameTable The XmlNameTable object to use.
    /// @throws ArgumentNullException The XmlNameTable object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API XmlSchemaSet(const SharedPtr<XmlNameTable>& nameTable);

    /// Adds an event handler for receiving information about XML Schema definition language (XSD) schema validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_add(Args... value)
    {
        _eventHandler.disconnect(_internalEventHandler);
        _eventHandler.connect(value...);
        if (_eventHandler == nullptr)
        {
            _eventHandler = _internalEventHandler;
        }
    }
    /// Removes an event handler for receiving information about XML Schema definition language (XSD) schema validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_remove(Args... value)
    {
        _eventHandler.disconnect(value...);
        if (_eventHandler == nullptr)
        {
            _eventHandler = _internalEventHandler;
        }
    }

    /// Adds the XML Schema definition language (XSD) schema at the URL specified to the XmlSchemaSet.
    /// @param targetNamespace The schema @p targetNamespace value,
    /// or @c nullptr to use the @p targetNamespace specified in the schema.
    /// @param schemaUri The URL that specifies the schema to load.
    /// @returns An XmlSchema object if the schema is valid.
    /// If the schema is not valid and a ValidationEventHandler is specified,
    /// then @c nullptr is returned and the appropriate validation event is raised.
    /// Otherwise, an XmlSchemaException is thrown.
    /// @throws XmlSchemaException The schema is not valid.
    /// @throws ArgumentNullException The URL passed as a parameter is @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(String targetNamespace, const String& schemaUri);
    /// Adds the XML Schema definition language (XSD) schema contained in the XmlReader to the XmlSchemaSet.
    /// @param targetNamespace The schema @p targetNamespace value,
    /// or @c nullptr to use the @p targetNamespace specified in the schema.
    /// @param schemaDocument The XmlReader object.
    /// @returns An XmlSchema object if the schema is valid.
    /// If the schema is not valid and a ValidationEventHandler is specified,
    /// then @c nullptr is returned and the appropriate validation event is raised.
    /// Otherwise, an XmlSchemaException is thrown.
    /// @throws XmlSchemaException The schema is not valid.
    /// @throws ArgumentNullException The XmlReader object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(String targetNamespace, const SharedPtr<XmlReader>& schemaDocument);
    /// Adds all the XML Schema definition language (XSD) schemas in the given XmlSchemaSet to the XmlSchemaSet.
    /// @param schemas The XmlSchemaSet object.
    /// @throws XmlSchemaException A schema in the XmlSchemaSet is not valid.
    /// @throws ArgumentNullException The XmlSchemaSet object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<XmlSchemaSet>& schemas);
    /// Adds the given XmlSchema to the XmlSchemaSet.
    /// @param schema The XmlSchema object to add to the XmlSchemaSet.
    /// @returns An XmlSchema object if the schema is valid.
    /// If the schema is not valid and a ValidationEventHandler is specified,
    /// then @c nullptr is returned and the appropriate validation event is raised.
    /// Otherwise, an XmlSchemaException is thrown.
    /// @throws XmlSchemaException The schema is not valid.
    /// @throws ArgumentNullException The XmlSchema object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const SharedPtr<XmlSchema>& schema);
    /// Removes the specified XML Schema definition language (XSD) schema from the XmlSchemaSet.
    /// @param schema The XmlSchema object to remove from the XmlSchemaSet.
    /// @returns The XmlSchema object removed from the XmlSchemaSet or
    /// @c nullptr if the schema was not found in the XmlSchemaSet.
    /// @throws XmlSchemaException The schema is not a valid schema.
    /// @throws ArgumentNullException The XmlSchema passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Remove(const SharedPtr<XmlSchema>& schema);
    /// Removes the specified XML Schema definition language (XSD) schema and
    /// all the schemas it imports from the XmlSchemaSet.
    /// @param schemaToRemove The XmlSchema object to remove from the XmlSchemaSet.
    /// @returns @c true if the XmlSchema object and all its imports were successfully removed;
    /// otherwise, @c false.
    /// @throws ArgumentNullException The XmlSchema passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API bool RemoveRecursive(const SharedPtr<XmlSchema>& schemaToRemove);
    /// Indicates whether an XML Schema definition language (XSD) schema with
    /// the specified target namespace URI is in the XmlSchemaSet.
    /// @param targetNamespace The schema @p targetNamespace property.
    /// @returns @c true if a schema with the specified target namespace URI is in the XmlSchemaSet;
    /// otherwise, @c false.
    ASPOSECPP_SHARED_API bool Contains(String targetNamespace);
    /// Indicates whether the specified XML Schema definition language (XSD) XmlSchema object is in the XmlSchemaSet.
    /// @param schema The XmlSchema object.
    /// @returns @c true if the XmlSchema object is in the XmlSchemaSet; otherwise, @c false.
    /// @throws ArgumentNullException The XmlSchemaSet passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API bool Contains(const SharedPtr<XmlSchema>& schema);
    /// Compiles the XML Schema definition language (XSD) schemas added to the XmlSchemaSet into one logical schema.
    /// @throws XmlSchemaException An error occurred when validating and compiling the schemas in the XmlSchemaSet.
    ASPOSECPP_SHARED_API void Compile();
    /// Reprocesses an XML Schema definition language (XSD) schema that already exists in the XmlSchemaSet.
    /// @param schema The schema to reprocess.
    /// @returns An XmlSchema object if the schema is a valid schema.
    /// If the schema is not valid and a ValidationEventHandler is specified,
    /// @c nullptr is returned and the appropriate validation event is raised.
    /// Otherwise, an XmlSchemaException is thrown.
    /// @throws XmlSchemaException The schema is not valid.
    /// @throws ArgumentNullException The XmlSchema object passed as a parameter is @c nullptr.
    /// @throws ArgumentException The XmlSchema object passed as a parameter does not already exist in the XmlSchemaSet.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Reprocess(SharedPtr<XmlSchema> schema);
    /// Copies all the XmlSchema objects from the XmlSchemaSet to the given array, starting at the given index.
    /// @param schemas The array to copy the objects to.
    /// @param index The index in the array where copying will begin.
    ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<SharedPtr<XmlSchema>>& schemas, int32_t index);
    /// Returns a collection of all the XML Schema definition language (XSD) schemas in the XmlSchemaSet.
    /// @returns An IList object containing all the schemas that have been added to the XmlSchemaSet.
    /// If no schemas have been added to the XmlSchemaSet, an empty collection is returned.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IList<SharedPtr<XmlSchema>>> Schemas();
    /// Returns a collection of all the XML Schema definition language (XSD) schemas in
    /// the XmlSchemaSet that belong to the given namespace.
    /// @param targetNamespace The schema @p targetNamespace property.
    /// @returns An IList object containing all the schemas that have been added to
    /// the XmlSchemaSet that belong to the given namespace.
    /// If no schemas have been added to the XmlSchemaSet, an empty collection is returned.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::List<SharedPtr<XmlSchema>>> Schemas(String targetNamespace);

protected:

    /// @cond
    SharedPtr<XmlSchemaObjectTable> elements;
    SharedPtr<XmlSchemaObjectTable> attributes;
    SharedPtr<XmlSchemaObjectTable> schemaTypes;
    SharedPtr<XmlSchemaObjectTable> substitutionGroups;

    SharedPtr<Object> get_InternalSyncObject();
    SharedPtr<XmlSchemaObjectTable> get_SubstitutionGroups();
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<Uri>, SharedPtr<XmlSchema>>> get_SchemaLocations();
    SharedPtr<XmlSchemaObjectTable> get_TypeExtensions();
    SharedPtr<SchemaInfo> get_CompiledInfo();
    SharedPtr<XmlReaderSettings> get_ReaderSettings();
    SharedPtr<Collections::Generic::SortedList<int32_t, SharedPtr<XmlSchema>>> get_SortedSchemas();

    void Add(String targetNamespace, const SharedPtr<XmlReader>& reader, const SharedPtr<Collections::Generic::Dictionary<String, String>>& validatedNamespaces);
    SharedPtr<XmlSchema> FindSchemaByNSAndUrl(const SharedPtr<Uri>& schemaUri, const String& ns, const ArrayPtr<Collections::Generic::KeyValuePair<SharedPtr<Uri>, SharedPtr<XmlSchema>>>& locationsTable);
    SharedPtr<XmlSchema> Remove(const SharedPtr<XmlSchema>& schema, bool forceCompile);
    bool PreprocessSchema(SharedPtr<XmlSchema>& schema, const String& targetNamespace);
    SharedPtr<XmlSchema> ParseSchema(const String& targetNamespace, const SharedPtr<XmlReader>& reader);
    void CopyFromCompiledSet(const SharedPtr<XmlSchemaSet>& otherSet);
    SharedPtr<System::Xml::XmlResolver> GetResolver();
    System::Xml::Schema::ValidationEventHandler& GetEventHandler();
    SharedPtr<SchemaNames> GetSchemaNames(const SharedPtr<XmlNameTable>& nt);
    bool IsSchemaLoaded(const SharedPtr<Uri>& schemaUri, String targetNamespace, SharedPtr<XmlSchema>& schema);
    bool GetSchemaByUri(const SharedPtr<Uri>& schemaUri, SharedPtr<XmlSchema>& schema);
    String GetTargetNamespace(const SharedPtr<XmlSchema>& schema);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaSet();

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
    const char* DBG_class_name() const override { return "XmlSchemaSet"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlNameTable> _nameTable;
    SharedPtr<SchemaNames> _schemaNames;
    SharedPtr<Collections::Generic::SortedList<int32_t, SharedPtr<XmlSchema>>> _schemas;
    System::Xml::Schema::ValidationEventHandler _internalEventHandler;
    System::Xml::Schema::ValidationEventHandler _eventHandler;
    bool _isCompiled;
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<Uri>, SharedPtr<XmlSchema>>> _schemaLocations;
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<ChameleonKey>, SharedPtr<XmlSchema>>> _chameleonSchemas;
    SharedPtr<Collections::Generic::Dictionary<String, String>> _targetNamespaces;
    bool _compileAll;
    SharedPtr<SchemaInfo> _cachedCompiledInfo;
    SharedPtr<XmlReaderSettings> _readerSettings;
    SharedPtr<XmlSchema> _schemaForSchema;
    SharedPtr<XmlSchemaCompilationSettings> _compilationSettings;
    SharedPtr<XmlSchemaObjectTable> _typeExtensions;
    SharedPtr<Object> _internalSyncObject;

    SharedPtr<XmlSchema> Add(const String& targetNamespace, SharedPtr<XmlSchema> schema);
    void SetDtdProcessing(const SharedPtr<XmlReader>& reader);
    void AddSchemaToSet(const SharedPtr<XmlSchema>& schema);
    void ProcessNewSubstitutionGroups(const SharedPtr<XmlSchemaObjectTable>& substitutionGroupsTable, bool resolve);
    void ResolveSubstitutionGroup(const SharedPtr<XmlSchemaSubstitutionGroup>& substitutionGroup, const SharedPtr<XmlSchemaObjectTable>& substTable);
    void ClearTables();
    void RemoveSchemaFromCaches(const SharedPtr<XmlSchema>& schema);
    void RemoveSchemaFromGlobalTables(const SharedPtr<XmlSchema>& schema);
    bool AddToTable(const SharedPtr<XmlSchemaObjectTable>& table, const SharedPtr<XmlQualifiedName>& qname, const SharedPtr<XmlSchemaObject>& item);
    void VerifyTables();
    void InternalValidationCallback(const SharedPtr<Object>& sender, const SharedPtr<ValidationEventArgs>& e);
    void SendValidationEvent(XmlSchemaException e, XmlSeverityType severity);

};

} // namespace Schema
} // namespace Xml
} // namespace System


