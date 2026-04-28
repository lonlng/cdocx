/// @file xml/schema/xml_schema_collection.h

#pragma once

#include <xml/schema/validation_event_handler.h>
#include <system/exceptions.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
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
} // namespace Generic
} // namespace Collections
namespace Xml
{
namespace Schema
{
class AutoValidator;
class BaseValidator;
class SchemaInfo;
class SchemaNames;
class XdrValidator;
class XmlSchema;
class XmlSchemaCollectionNode;
class Details_XmlSchemaException; using XmlSchemaException = System::ExceptionWrapper<Details_XmlSchemaException>;
class XsdValidator;
} // namespace Schema
class XmlNameTable;
class XmlReader;
class XmlResolver;
class XmlValidatingReaderImpl;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Contains a cache of XML Schema definition language (XSD) and XML-Data Reduced (XDR) schemas.
/// @deprecated The XmlSchemaCollection class is obsolete. Use XmlSchemaSet instead.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaCollection final : public Collections::Generic::IEnumerable<SharedPtr<System::Xml::Schema::XmlSchema>>
{
    typedef XmlSchemaCollection ThisType;
    typedef Collections::Generic::IEnumerable<SharedPtr<System::Xml::Schema::XmlSchema>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaCollection>;

private:
    /// @cond
    friend class System::Xml::XmlValidatingReaderImpl;
    friend class BaseValidator;
    friend class XdrValidator;
    friend class XsdValidator;
    /// @endcond

public:

    /// Sets an event handler for receiving information about the XDR and XML schema validation errors.
    System::Xml::Schema::ValidationEventHandler ValidationEventHandler;

    /// Returns the number of namespaces defined in this collection.
    /// @returns The number of namespaces defined in this collection.
    ASPOSECPP_SHARED_API int32_t get_Count();
    /// Returns the default XmlNameTable used by the XmlSchemaCollection when loading new schemas.
    /// @returns An XmlNameTable.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();

    /// Initializes a new instance of the XmlSchemaCollection class.
    ASPOSECPP_SHARED_API XmlSchemaCollection();
    /// Initializes a new instance of the XmlSchemaCollection class with the specified XmlNameTable.
    /// The XmlNameTable is used when loading schemas.
    /// @param nametable The XmlNameTable to use.
    ASPOSECPP_SHARED_API XmlSchemaCollection(const SharedPtr<XmlNameTable>& nametable);

    /// Adds the schema located by the given URL into the schema collection.
    /// @param ns The namespace URI associated with the schema.
    /// For XML Schemas, this will typically be the @c targetNamespace.
    /// @param uri The URL that specifies the schema to load.
    /// @returns The XmlSchema added to the schema collection;
    /// @c nullptr if the schema being added is an XDR schema or if there are compilation errors in the schema.
    /// @throws XmlException The schema is not a valid schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const String& ns, const String& uri);
    /// Adds the schema contained in the XmlReader to the schema collection.
    /// @param ns The namespace URI associated with the schema.
    /// For XML Schemas, this will typically be the @c targetNamespace.
    /// @param reader XmlReader containing the schema to add.
    /// @returns The XmlSchema added to the schema collection;
    /// @c nullptr if the schema being added is an XDR schema or if there are compilation errors in the schema.
    /// @throws XmlException The schema is not a valid schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const String& ns, const SharedPtr<XmlReader>& reader);
    /// Adds the schema contained in the XmlReader to the schema collection.
    /// The specified XmlResolver is used to resolve any external resources.
    /// @param ns The namespace URI associated with the schema.
    /// For XML Schemas, this will typically be the @c targetNamespace.
    /// @param reader XmlReader containing the schema to add.
    /// @param resolver The XmlResolver used to resolve namespaces referenced in @c include and
    /// @c import elements or @c x-schema attribute (XDR schemas).
    /// If this is @c nullptr, external references are not resolved.
    /// @returns The XmlSchema added to the schema collection;
    /// @c nullptr if the schema being added is an XDR schema or if there are compilation errors in the schema.
    /// @throws XmlException The schema is not a valid schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const String& ns, const SharedPtr<XmlReader>& reader, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Adds the XmlSchema to the collection.
    /// @param schema The XmlSchema to add to the collection.
    /// @returns The XmlSchema object.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const SharedPtr<XmlSchema>& schema);
    /// Adds the XmlSchema to the collection. The specified XmlResolver is used to resolve any external references.
    /// @param schema The XmlSchema to add to the collection.
    /// @param resolver The XmlResolver used to resolve namespaces referenced in @c include and @c import elements.
    /// If this is @c nullptr, external references are not resolved.
    /// @returns The XmlSchema added to the schema collection.
    /// @throws XmlException The schema is not a valid schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> Add(const SharedPtr<XmlSchema>& schema, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Adds all the namespaces defined in the given collection (including their associated schemas) to this collection.
    /// @param schema The XmlSchemaCollection you want to add to this collection.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<XmlSchemaCollection>& schema);

    /// Returns the XmlSchema associated with the given namespace URI.
    /// @param ns The namespace URI associated with the schema you want to return.
    /// This will typically be the @c targetNamespace of the schema.
    /// @returns The XmlSchema associated with the namespace URI;
    /// @c nullptr if there is no loaded schema associated with the given namespace or
    /// if the namespace is associated with an XDR schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchema> idx_get(const String& ns);

    /// Returns a value indicating whether the @c targetNamespace of the specified XmlSchema is in the collection.
    /// @param schema The XmlSchema object.
    /// @returns @c true if there is a schema in the collection with the same @c targetNamespace; otherwise, @c false.
    ASPOSECPP_SHARED_API bool Contains(const SharedPtr<XmlSchema>& schema);
    /// Returns a value indicating whether a schema with the specified namespace is in the collection.
    /// @param ns The namespace URI associated with the schema.
    /// For XML Schemas, this will typically be the target namespace.
    /// @returns @c true if a schema with the specified namespace is in the collection; otherwise, @c false.
    ASPOSECPP_SHARED_API bool Contains(const String& ns);
    /// Provides support for iteration over the collection of schemas.
    /// @returns An enumerator for iterating over all schemas in the current collection.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlSchema>>> GetEnumerator() override;
    /// Copies all the XmlSchema objects from this collection into the given array starting at the given index.
    /// @param array The array to copy the objects to.
    /// @param index The index in @p array where copying will begin.
    ASPOSECPP_SHARED_API void CopyTo(const ArrayPtr<SharedPtr<XmlSchema>>& array, int32_t index);

protected:

    /// @cond
    void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);
    System::Xml::Schema::ValidationEventHandler get_EventHandler();
    void set_EventHandler(System::Xml::Schema::ValidationEventHandler value);

    SharedPtr<SchemaInfo> GetSchemaInfo(const String& ns);
    SharedPtr<SchemaNames> GetSchemaNames(const SharedPtr<XmlNameTable>& nt);
    SharedPtr<XmlSchema> Add(const String& ns, const SharedPtr<SchemaInfo>& schemaInfo, const SharedPtr<XmlSchema>& schema, bool compile);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaCollection();

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
    const char* DBG_class_name() const override { return "XmlSchemaCollection"; }
#endif
    /// @endcond

private:

    SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<XmlSchemaCollectionNode>>> _collection;
    SharedPtr<XmlNameTable> _nameTable;
    SharedPtr<SchemaNames> _schemaNames;
    SharedPtr<Object> _wLock;
    bool _isThreadSafe;
    SharedPtr<System::Xml::XmlResolver> _xmlResolver;

    SharedPtr<XmlSchema> Add(String ns, const SharedPtr<SchemaInfo>& schemaInfo, const SharedPtr<XmlSchema>& schema, bool compile, const SharedPtr<System::Xml::XmlResolver>& resolver);
    void AddNonThreadSafe(const String& ns, const SharedPtr<XmlSchemaCollectionNode>& node);
    void Add(const String& ns, const SharedPtr<XmlSchemaCollectionNode>& node);
    void SendValidationEvent(XmlSchemaException e);

};

/// Supports a simple iteration over a collection. This class cannot be inherited.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaCollectionEnumerator final : public Collections::Generic::IEnumerator<SharedPtr<System::Xml::Schema::XmlSchema>>
{
    typedef XmlSchemaCollectionEnumerator ThisType;
    typedef Collections::Generic::IEnumerator<SharedPtr<System::Xml::Schema::XmlSchema>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaCollectionEnumerator>;

private:
    /// @cond
    friend class AutoValidator;
    friend class XmlSchemaCollection;
    /// @endcond

public:

    /// Returns the current XmlSchema in the collection.
    /// @returns The current XmlSchema in the collection.
    ASPOSECPP_SHARED_API const SharedPtr<XmlSchema>& get_Current() const override;

    /// Advances the enumerator to the next schema in the collection.
    /// @returns @c true if the move was successful; @c false if the enumerator has passed the end of the collection.
    ASPOSECPP_SHARED_API bool MoveNext() override;
    ASPOSECPP_SHARED_API void Dispose() override;

    /// Clones current iterator.
    /// @return Copy of the current iterator.
    ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<System::Xml::Schema::XmlSchema>>* CloneIterator() const override;

protected:

    /// @cond
    SharedPtr<XmlSchemaCollectionNode> get_CurrentNode();

    XmlSchemaCollectionEnumerator(const SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<XmlSchemaCollectionNode>>>& collection);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlSchemaCollectionEnumerator, CODEPORTING_ARGS(SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<XmlSchemaCollectionNode>>> collection));

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
    const char* DBG_class_name() const override { return "XmlSchemaCollectionEnumerator"; }
#endif
    /// @endcond

private:

    SharedPtr<Collections::Generic::IEnumerator<Collections::Generic::KeyValuePair<String, SharedPtr<XmlSchemaCollectionNode>>>> _enumerator;
    mutable SharedPtr<XmlSchema> m_CurrentHolder;

    ASPOSECPP_SHARED_API void Reset() override;

};

} // namespace Schema
} // namespace Xml
} // namespace System


