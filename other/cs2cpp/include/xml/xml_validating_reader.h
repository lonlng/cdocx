/// @file xml/xml_validating_reader.h

#pragma once

#include <xml/xml_space.h>
#include <xml/xml_reader.h>
#include <xml/xml_node_type.h>
#include <xml/validation_type.h>
#include <xml/read_state.h>
#include <xml/ixml_namespace_resolver.h>
#include <xml/ixml_line_info.h>
#include <xml/entity_handling.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class IDictionary;
} // namespace Generic
} // namespace Collections
namespace IO
{
class Stream;
} // namespace IO
namespace Text
{
class Encoding;
} // namespace Text
namespace Xml
{
class IDtdInfo;
namespace Schema
{
class XmlSchemaCollection;
} // namespace Schema
enum class XmlNamespaceScope;
class XmlNameTable;
class XmlParserContext;
class XmlResolver;
class XmlValidatingReaderImpl;
namespace Xsl
{
class QueryReaderSettings;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a reader that provides document type definition (DTD), XML-Data Reduced (XDR) schema,
/// and XML Schema definition language (XSD) validation.
/// @deprecated This class is obsolete. It is recommended to use the XmlReaderSettings class and
/// the XmlReader::Create method to create a validating XML reader.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlValidatingReader : public XmlReader, public IXmlLineInfo, public IXmlNamespaceResolver
{
    typedef XmlValidatingReader ThisType;
    typedef XmlReader BaseType;
    typedef IXmlLineInfo BaseType1;
    typedef IXmlNamespaceResolver BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlValidatingReader>;

private:
    /// @cond
    friend class XmlReader;
    friend class Xsl::QueryReaderSettings;
    /// @endcond

public:

    /// Returns the type of the current node.
    /// @returns One of the XmlNodeType values representing the type of the current node.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the qualified name of the current node.
    /// @returns The qualified name of the current node. For example, @c Name is @c bk:book for the element @c <bk:book>.
    ///
    /// The name returned is dependent on the XmlValidatingReader::NodeType of the node.
    /// The following node types return the listed values. All other node types return an empty string.
    /// <list type="table"><listheader><term> Node Type
    /// </term><description> Name
    /// </description></listheader><item><term>Attribute</term><description> The name of the attribute.
    /// </description></item><item><term>DocumentType</term><description> The document type name.
    /// </description></item><item><term>Element</term><description> The tag name.
    /// </description></item><item><term>EntityReference</term><description> The name of the entity referenced.
    /// </description></item><item><term>ProcessingInstruction</term><description> The target of the processing instruction.
    /// </description></item><item><term>XmlDeclaration</term><description> The literal string @c xml.
    /// </description></item></list>
    ASPOSECPP_SHARED_API String get_Name() override;
    /// Returns the local name of the current node.
    /// @returns The name of the current node with the prefix removed. For example, @c LocalName is @c book for the element @c <bk:book>.
    /// For node types that do not have a name (like @c Text, @c Comment, and so on), this method returns String::Empty.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the namespace Uniform Resource Identifier (URI)
    /// (as defined in the World Wide Web Consortium (W3C) Namespace specification) of the node on which the reader is positioned.
    /// @returns The namespace URI of the current node; otherwise an empty string.
    ASPOSECPP_SHARED_API String get_NamespaceURI() override;
    /// Returns the namespace prefix associated with the current node.
    /// @returns The namespace prefix associated with the current node.
    ASPOSECPP_SHARED_API String get_Prefix() override;
    /// Returns a value indicating whether the current node can have a XmlValidatingReader::get_Value other than String::Empty.
    /// @returns @c true if the node on which the reader is currently positioned can have a @c Value; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_HasValue() override;
    /// Returns the text value of the current node.
    /// @returns The value returned depends on the XmlValidatingReader::NodeType of the node.
    ///
    /// The following table lists node types that have a value to return. All other node types return String::Empty.
    /// <list type="table"><listheader><term> Node Type
    /// </term><description> Value
    /// </description></listheader><item><term>Attribute</term><description> The value of the attribute.
    /// </description></item><item><term>CDATA</term><description> The content of the CDATA section.
    /// </description></item><item><term>Comment</term><description> The content of the comment.
    /// </description></item><item><term>DocumentType</term><description> The internal subset.
    /// </description></item><item><term>ProcessingInstruction</term><description> The entire content, excluding the target.
    /// </description></item><item><term>SignificantWhitespace</term><description> The white space between markup in a mixed content model.
    /// </description></item><item><term>Text</term><description> The content of the text node.
    /// </description></item><item><term>Whitespace</term><description> The white space between markup.
    /// </description></item><item><term>XmlDeclaration</term><description> The content of the declaration.
    /// </description></item></list>
    ASPOSECPP_SHARED_API String get_Value() override;
    /// Returns the depth of the current node in the XML document.
    /// @returns The depth of the current node in the XML document.
    ASPOSECPP_SHARED_API int32_t get_Depth() override;
    /// Returns the base URI of the current node.
    /// @returns The base URI of the current node.
    ASPOSECPP_SHARED_API String get_BaseURI() override;
    /// Returns a value indicating whether the current node is an empty element (for example, <tt>\<MyElement/></tt>).
    /// @returns @c true if the current node is an element
    /// (XmlValidatingReader::get_NodeType value equals XmlNodeType::Element) that ends with <tt>/></tt>;
    /// otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_IsEmptyElement() override;
    /// Returns a value indicating whether the current node is an attribute that was generated from
    /// the default value defined in the document type definition (DTD) or schema.
    /// @returns @c true if the current node is an attribute whose value was generated from
    /// the default value defined in the DTD or schema; @c false if the attribute value was explicitly set.
    ASPOSECPP_SHARED_API bool get_IsDefault() override;
    /// Returns the quotation mark character used to enclose the value of an attribute node.
    /// @returns The quotation mark character (" or ') used to enclose the value of an attribute node.
    ASPOSECPP_SHARED_API char16_t get_QuoteChar() override;
    /// Returns the current @c xml:space scope.
    /// @returns One of the XmlSpace values. If no @c xml:space scope exists, this value defaults to XmlSpace::None.
    ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace() override;
    /// Returns the current @c xml:lang scope.
    /// @returns The current @c xml:lang scope.
    ASPOSECPP_SHARED_API String get_XmlLang() override;
    /// Returns the number of attributes on the current node.
    /// @returns The number of attributes on the current node. This number includes default attributes.
    ASPOSECPP_SHARED_API int32_t get_AttributeCount() override;
    /// Returns a value indicating whether the reader is positioned at the end of the stream.
    /// @returns @c true if the reader is positioned at the end of the stream; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_EOF() override;
    /// Returns the state of the reader.
    /// @returns One of the ReadState values.
    ASPOSECPP_SHARED_API System::Xml::ReadState get_ReadState() override;
    /// Returns the XmlNameTable associated with this implementation.
    /// @returns XmlNameTable that enables you to get the atomized version of a string within the node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable() override;
    /// Returns a value indicating whether this reader can parse and resolve entities.
    /// @returns @c true if the reader can parse and resolve entities; otherwise, @c false.
    /// XmlValidatingReader always returns @c true.
    ASPOSECPP_SHARED_API bool get_CanResolveEntity() override;
    /// Returns a value indicating whether the XmlValidatingReader implements the binary content read methods.
    /// @returns @c true if the binary content read methods are implemented; otherwise @c false.
    /// The XmlValidatingReader class returns @c true.
    ASPOSECPP_SHARED_API bool get_CanReadBinaryContent() override;
    /// Returns the current line number.
    /// @returns The current line number. The starting value is 1.
    ASPOSECPP_SHARED_API int32_t get_LineNumber() override;
    /// Returns the current line position.
    /// @returns The current line position. The starting value is 1.
    ASPOSECPP_SHARED_API int32_t get_LinePosition() override;
    /// Returns a schema type object.
    /// @returns XmlSchemaDatatype, XmlSchemaSimpleType, or XmlSchemaComplexType depending whether the node value is
    /// a built in XML Schema definition language (XSD) type or a user defined simpleType or complexType;
    /// @c nullptr if the current node has no schema type.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_SchemaType();
    /// Returns the XmlReader used to construct this XmlValidatingReader.
    /// @returns The XmlReader specified in the constructor.
    ASPOSECPP_SHARED_API SharedPtr<XmlReader> get_Reader();
    /// Returns a value indicating the type of validation to perform.
    /// @returns One of the ValidationType values. If this value is not set, it defaults to ValidationType::Auto.
    ASPOSECPP_SHARED_API System::Xml::ValidationType get_ValidationType();
    /// Sets a value indicating the type of validation to perform.
    /// @param value The value to set.
    /// @throws InvalidOperationException Setting the value after a Read has been called.
    ASPOSECPP_SHARED_API void set_ValidationType(System::Xml::ValidationType value);
    /// Returns a XmlSchemaCollection to use for validation.
    /// @returns The XmlSchemaCollection to use for validation.
    ASPOSECPP_SHARED_API SharedPtr<Schema::XmlSchemaCollection> get_Schemas();
    /// Returns a value that specifies how the reader handles entities.
    /// @returns One of the EntityHandling values.
    /// If no EntityHandling is specified, it defaults to EntityHandling::ExpandEntities.
    ASPOSECPP_SHARED_API System::Xml::EntityHandling get_EntityHandling();
    /// Sets a value that specifies how the reader handles entities.
    /// @param value The value to set.
    /// @throws ArgumentOutOfRangeException Invalid value was specified.
    ASPOSECPP_SHARED_API void set_EntityHandling(System::Xml::EntityHandling value);
    /// Sets the XmlResolver used for resolving external document type definition (DTD) and schema location references.
    /// The XmlResolver is also used to handle any import or include elements found in XML Schema definition language (XSD) schemas.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);
    /// Returns a value indicating whether to do namespace support.
    /// @returns @c true to do namespace support; otherwise, @c false. The default is @c true.
    ASPOSECPP_SHARED_API bool get_Namespaces();
    /// Sets a value indicating whether to do namespace support.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Namespaces(bool value);
    /// Returns the encoding attribute for the document.
    /// @returns The encoding value. If no encoding attribute exists, and there is not byte-order mark, this defaults to UTF-8.
    ASPOSECPP_SHARED_API SharedPtr<System::Text::Encoding> get_Encoding();

    /// Initializes a new instance of the XmlValidatingReader class that validates the content returned from the given XmlReader.
    /// @param reader The XmlReader to read from while validating. The current implementation supports only XmlTextReader.
    /// @throws ArgumentException The reader specified is not an XmlTextReader.
    ASPOSECPP_SHARED_API XmlValidatingReader(const SharedPtr<XmlReader>& reader);
    /// Initializes a new instance of the XmlValidatingReader class with the specified values.
    /// @param xmlFragment The string containing the XML fragment to parse.
    /// @param fragType The XmlNodeType of the XML fragment. This also determines what the fragment string can contain (see table below).
    /// @param context The XmlParserContext in which the XML fragment is to be parsed.
    /// This includes the NameTable to use, encoding, namespace scope, current @c xml:lang, and @c xml:space scope.
    /// @throws XmlException @p fragType is not one of the node types listed in the table below.
    ///
    /// The following table lists valid values for `fragType` and how the reader parses each of the different node types.
    /// <list type="table"><listheader><term> XmlNodeType
    /// </term><description> Fragment May Contain
    /// </description></listheader><item><term>Element</term><description> Any valid element content
    /// (for example, any combination of elements, comments, processing instructions, cdata, text, and entity references).
    /// </description></item><item><term>Attribute</term><description> The value of an attribute (the part inside the quotes).
    /// </description></item><item><term>Document</term><description> The contents of an entire XML document;
    /// this enforces document level rules.
    /// </description></item></list>
    ASPOSECPP_SHARED_API XmlValidatingReader(const String& xmlFragment, XmlNodeType fragType, const SharedPtr<XmlParserContext>& context);
    /// Initializes a new instance of the XmlValidatingReader class with the specified values.
    /// @param xmlFragment The stream containing the XML fragment to parse.
    /// @param fragType The XmlNodeType of the XML fragment. This determines what the fragment can contain (see table below).
    /// @param context The XmlParserContext in which the XML fragment is to be parsed.
    /// This includes the XmlNameTable to use, encoding, namespace scope, current @c xml:lang, and @c xml:space scope.
    /// @throws XmlException @p fragType is not one of the node types listed in the table below.
    ///
    /// The following table lists valid values for `fragType` and how the reader parses each of the different node types.
    /// <list type="table"><listheader><term> XmlNodeType
    /// </term><description> Fragment May Contain
    /// </description></listheader><item><term>Element</term><description> Any valid element content
    /// (for example, any combination of elements, comments, processing instructions, cdata, text, and entity references).
    /// </description></item><item><term>Attribute</term><description> The value of an attribute (the part inside the quotes).
    /// </description></item><item><term>Document</term><description> The contents of an entire XML document;
    /// this enforces document level rules.
    /// </description></item></list>
    ASPOSECPP_SHARED_API XmlValidatingReader(const SharedPtr<IO::Stream>& xmlFragment, XmlNodeType fragType, const SharedPtr<XmlParserContext>& context);

    /// Returns the value of the attribute with the specified name.
    /// @param name The qualified name of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    ASPOSECPP_SHARED_API String GetAttribute(String name) override;
    /// Returns the value of the attribute with the specified local name and namespace Uniform Resource Identifier (URI).
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    /// This method does not move the reader.
    ASPOSECPP_SHARED_API String GetAttribute(String localName, String namespaceURI) override;
    /// Returns the value of the attribute with the specified index.
    /// @param i The index of the attribute. The index is zero-based. (The first attribute has index 0.)
    /// @returns The value of the specified attribute.
    /// @throws ArgumentOutOfRangeException The @p i parameter is less than 0 or
    /// greater than or equal to XmlValidatingReader::get_AttributeCount value.
    ASPOSECPP_SHARED_API String GetAttribute(int32_t i) override;
    /// Moves to the attribute with the specified name.
    /// @param name The qualified name of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false.
    /// If @c false, the position of the reader does not change.
    ASPOSECPP_SHARED_API bool MoveToAttribute(String name) override;
    /// Moves to the attribute with the specified local name and namespace Uniform Resource Identifier (URI).
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false.
    /// If @c false, the position of the reader does not change.
    ASPOSECPP_SHARED_API bool MoveToAttribute(String localName, String namespaceURI) override;
    /// Moves to the attribute with the specified index.
    /// @param i The index of the attribute.
    /// @throws ArgumentOutOfRangeException The @p i parameter is less than 0 or
    /// greater than or equal to XmlReader::get_AttributeCount value.
    ASPOSECPP_SHARED_API void MoveToAttribute(int32_t i) override;
    /// Moves to the first attribute.
    /// @returns @c true if an attribute exists (the reader moves to the first attribute);
    /// otherwise, @c false (the position of the reader does not change).
    ASPOSECPP_SHARED_API bool MoveToFirstAttribute() override;
    /// Moves to the next attribute.
    /// @returns @c true if there is a next attribute; @c false if there are no more attributes.
    ASPOSECPP_SHARED_API bool MoveToNextAttribute() override;
    /// Moves to the element that contains the current attribute node.
    /// @returns @c true if the reader is positioned on an attribute (the reader moves to the element that owns the attribute);
    /// @c false if the reader is not positioned on an attribute (the position of the reader does not change).
    ASPOSECPP_SHARED_API bool MoveToElement() override;
    /// Parses the attribute value into one or more @c Text, @c EntityReference, or @c EndEntity nodes.
    /// @returns @c true if there are nodes to return.
    /// @c false if the reader is not positioned on an attribute node when the initial call is made or if all the attribute values have been read.
    /// An empty attribute, such as, @c misc="", returns @c true with a single node with a value of String::Empty.
    ASPOSECPP_SHARED_API bool ReadAttributeValue() override;
    /// Reads the next node from the stream.
    /// @returns @c true if the next node was read successfully; @c false if there are no more nodes to read.
    ASPOSECPP_SHARED_API bool Read() override;
    /// Changes the XmlReader::get_ReadState to Closed.
    ASPOSECPP_SHARED_API void Close() override;
    /// Resolves a namespace prefix in the current element's scope.
    /// @param prefix The prefix whose namespace Uniform Resource Identifier (URI) you want to resolve.
    /// To match the default namespace, pass an empty string.
    /// @returns The namespace URI to which the prefix maps or @c nullptr if no matching prefix is found.
    ASPOSECPP_SHARED_API String LookupNamespace(const String& prefix) override;
    /// Resolves the entity reference for @c EntityReference nodes.
    /// @throws InvalidOperationException The reader is not positioned on an @c EntityReference node.
    ASPOSECPP_SHARED_API void ResolveEntity() override;
    /// Reads the content and returns the Base64 decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported on the current node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    ASPOSECPP_SHARED_API int32_t ReadContentAsBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the element and decodes the Base64 content.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The current node is not an element node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlValidatingReader implementation does not support this method.
    /// @throws XmlException The element contains mixed-content.
    /// @throws FormatException The content cannot be converted to the requested type.
    ASPOSECPP_SHARED_API int32_t ReadElementContentAsBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the content and returns the BinHex decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported on the current node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlValidatingReader implementation does not support this method.
    ASPOSECPP_SHARED_API int32_t ReadContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the element and decodes the BinHex content.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The current node is not an element node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlValidatingReader implementation does not support this method.
    /// @throws XmlException The element contains mixed-content.
    /// @throws FormatException The content cannot be converted to the requested type.
    ASPOSECPP_SHARED_API int32_t ReadElementContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the contents of an element or text node as a string.
    /// @returns The contents of the element or text node.
    /// This can be an empty string if the reader is positioned on something other than an element or text node,
    /// or if there is no more text content to return in the current context.
    ASPOSECPP_SHARED_API String ReadString() override;
    /// Returns a value indicating whether the class can return line information.
    /// @returns @c true if the class can return line information; otherwise, @c false.
    ASPOSECPP_SHARED_API bool HasLineInfo() override;

    /// Adds an event handler for receiving information about document type definition (DTD),
    /// XML-Data Reduced (XDR) schema, and XML Schema definition language (XSD) schema validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_add(Args... value)
    {
        throw NotImplementedException();
    }

    /// Removes an event handler for receiving information about document type definition (DTD),
    /// XML-Data Reduced (XDR) schema, and XML Schema definition language (XSD) schema validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_remove(Args... value)
    {
        throw NotImplementedException();
    }

    /// Returns the runt-ime type for the specified XML Schema definition language (XSD) type.
    /// @returns The run-time type for the specified XML Schema type.
    ASPOSECPP_SHARED_API SharedPtr<Object> ReadTypedValue();

protected:

    /// @cond
    SharedPtr<XmlValidatingReaderImpl> get_Impl();
    ASPOSECPP_SHARED_API SharedPtr<IDtdInfo> get_DtdInfo() override;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlValidatingReader();

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
    const char* DBG_class_name() const override { return "XmlValidatingReader"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlValidatingReaderImpl> _impl;

    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) override;
    ASPOSECPP_SHARED_API String LookupPrefix(const String& namespaceName) override;

};

} // namespace Xml
} // namespace System


