/// @file xml/xml_text_reader.h

#pragma once

#include <xml/xml_space.h>
#include <xml/xml_reader.h>
#include <xml/xml_node_type.h>
#include <xml/xml_namespace_scope.h>
#include <xml/whitespace_handling.h>
#include <xml/read_state.h>
#include <xml/ixml_namespace_resolver.h>
#include <xml/ixml_line_info.h>
#include <xml/entity_handling.h>
#include <xml/dtd_processing.h>
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
class TextReader;
} // namespace IO
namespace Text
{
class Encoding;
} // namespace Text
namespace Xml
{
class IDtdInfo;
class XmlDocument;
class XmlLoader;
class XmlNamespaceManager;
class XmlNameTable;
class XmlParserContext;
class XmlResolver;
class XmlTextReaderImpl;
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

/// Represents a reader that provides fast, non-cached, forward-only access to XML data.
/// @remarks It is recommended to use the XmlReader class instead.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlTextReader : public XmlReader, public IXmlLineInfo, public IXmlNamespaceResolver
{
    typedef XmlTextReader ThisType;
    typedef XmlReader BaseType;
    typedef IXmlLineInfo BaseType1;
    typedef IXmlNamespaceResolver BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlTextReader>;

private:
    /// @cond
    friend class XmlReader;
    friend class XmlValidatingReaderImpl;
    friend class XmlDocument;
    friend class XmlLoader;
    friend class Xsl::QueryReaderSettings;
    /// @endcond

public:

    /// Returns the type of the current node.
    /// @returns One of the XmlNodeType values representing the type of the current node.
    ASPOSECPP_SHARED_API XmlNodeType get_NodeType() override;
    /// Returns the qualified name of the current node.
    /// @returns The qualified name of the current node.
    /// For example, @c Name is @c bk:book for the element <tt><bk:book></tt>.
    ///
    /// The name returned is dependent on the XmlTextReader::get_NodeType value of the node.
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
    /// @returns The name of the current node with the prefix removed.
    /// For example, @c LocalName is @c book for the element <tt><bk:book></tt>.
    /// For node types that do not have a name (like @c Text, @c Comment, and so on), this method returns String::Empty.
    ASPOSECPP_SHARED_API String get_LocalName() override;
    /// Returns the namespace URI (as defined in the W3C Namespace specification) of the node on which the reader is positioned.
    /// @returns The namespace URI of the current node; otherwise an empty string.
    ASPOSECPP_SHARED_API String get_NamespaceURI() override;
    /// Returns the namespace prefix associated with the current node.
    /// @returns The namespace prefix associated with the current node.
    ASPOSECPP_SHARED_API String get_Prefix() override;
    /// Returns a value indicating whether the current node can have a XmlTextReader::get_Value other than String::Empty.
    /// @returns @c true if the node on which the reader is currently positioned can have a @c Value; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_HasValue() override;
    /// Returns the text value of the current node.
    /// @returns The value returned depends on the XmlTextReader::get_NodeType value of the node.
    ///
    /// The following table lists node types that have a value to return. All other node types return String::Empty.
    /// <list type="table"><listheader><term> Node Type
    /// </term><description> Value
    /// </description></listheader><item><term>Attribute</term><description> The value of the attribute.
    /// </description></item><item><term>CDATA</term><description> The content of the CDATA section.
    /// </description></item><item><term>Comment</term><description> The content of the comment.
    /// </description></item><item><term>DocumentType</term><description> The internal subset.
    /// </description></item><item><term>ProcessingInstruction</term><description> The entire content, excluding the target.
    /// </description></item><item><term>SignificantWhitespace</term><description> The white space within an <tt>xml:space='preserve'</tt> scope.
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
    /// @returns @c true if the current node is an element (XmlTextReader::get_NodeType value equals XmlNodeType::Element)
    /// that ends with <tt>/></tt>; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_IsEmptyElement() override;
    /// Returns a value indicating whether the current node is an attribute that was
    /// generated from the default value defined in the DTD or schema.
    /// @returns This method always returns @c false. (XmlTextReader does not expand default attributes.)
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
    /// @returns The number of attributes on the current node.
    ASPOSECPP_SHARED_API int32_t get_AttributeCount() override;
    /// Returns a value indicating whether the reader is positioned at the end of the stream.
    /// @returns @c true if the reader is positioned at the end of the stream; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_EOF() override;
    /// Returns the state of the reader.
    /// @returns One of the ReadState values.
    ASPOSECPP_SHARED_API System::Xml::ReadState get_ReadState() override;
    /// Returns the XmlNameTable associated with this implementation.
    /// @returns The XmlNameTable enabling you to get the atomized version of a string within the node.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable() override;
    /// Returns a value indicating whether this reader can parse and resolve entities.
    /// @returns @c true if the reader can parse and resolve entities; otherwise, @c false.
    /// The XmlTextReader class always returns @c true.
    ASPOSECPP_SHARED_API bool get_CanResolveEntity() override;
    /// Returns a value indicating whether the XmlTextReader implements the binary content read methods.
    /// @returns @c true if the binary content read methods are implemented; otherwise @c false.
    /// The XmlTextReader class always returns @c true.
    ASPOSECPP_SHARED_API bool get_CanReadBinaryContent() override;
    /// Returns a value indicating whether the XmlTextReader implements the XmlReader::ReadValueChunk method.
    /// @returns @c true if the XmlTextReader implements the XmlReader::ReadValueChunk method; otherwise @c false.
    /// The XmlTextReader class always returns @c false.
    ASPOSECPP_SHARED_API bool get_CanReadValueChunk() override;
    /// Returns the current line number.
    /// @returns The current line number.
    ASPOSECPP_SHARED_API int32_t get_LineNumber() override;
    /// Returns the current line position.
    /// @returns The current line position.
    ASPOSECPP_SHARED_API int32_t get_LinePosition() override;
    /// Returns a value indicating whether to do namespace support.
    /// @returns @c true to do namespace support; otherwise, @c false. The default is @c true.
    ASPOSECPP_SHARED_API bool get_Namespaces();
    /// Sets a value indicating whether to do namespace support.
    /// @param value The value to set.
    /// @throws InvalidOperationException Setting this value after a read operation has occurred
    /// (XmlTextReader::get_ReadState is not ReadState::Initial).
    ASPOSECPP_SHARED_API void set_Namespaces(bool value);
    /// Returns a value indicating whether to normalize white space and attribute values.
    /// @returns @c true to normalize; otherwise, @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_Normalization();
    /// Sets a value indicating whether to normalize white space and attribute values.
    /// @param value The value to set.
    /// @throws InvalidOperationException Setting this value when the reader is closed
    /// (XmlTextReader::get_ReadState is ReadState::Closed).
    ASPOSECPP_SHARED_API void set_Normalization(bool value);
    /// Returns the encoding of the document.
    /// @returns The encoding value.
    /// If no encoding attribute exists, and there is no byte-order mark, this defaults to UTF-8.
    ASPOSECPP_SHARED_API SharedPtr<System::Text::Encoding> get_Encoding();
    /// Returns a value that specifies how white space is handled.
    /// @returns One of the WhitespaceHandling values.
    /// The default is @c WhitespaceHandling.All (returns @c Whitespace and @c SignificantWhitespace nodes).
    /// @throws ArgumentOutOfRangeException Invalid value specified.
    ASPOSECPP_SHARED_API System::Xml::WhitespaceHandling get_WhitespaceHandling();
    /// Sets a value that specifies how white space is handled.
    /// @param value The value to set.
    /// @throws ArgumentOutOfRangeException Invalid value specified.
    /// @throws InvalidOperationException Setting this value when the reader is closed
    /// (XmlTextReader::get_ReadState is ReadState::Closed).
    ASPOSECPP_SHARED_API void set_WhitespaceHandling(System::Xml::WhitespaceHandling value);
    /// Returns a value indicating whether to allow DTD processing.
    /// @deprecated This method is obsolete. Use XmlTextReader::get_DtdProcessing instead.
    /// @returns @c true to disallow DTD processing; otherwise @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_ProhibitDtd();
    /// Sets a value indicating whether to allow DTD processing.
    /// @deprecated This method is obsolete. Use XmlTextReader::set_DtdProcessing instead.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ProhibitDtd(bool value);
    /// Returns the DtdProcessing enumeration.
    /// @returns The DtdProcessing enumeration.
    ASPOSECPP_SHARED_API System::Xml::DtdProcessing get_DtdProcessing();
    /// Sets the DtdProcessing enumeration.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DtdProcessing(System::Xml::DtdProcessing value);
    /// Returns a value that specifies how the reader handles entities.
    /// @returns One of the EntityHandling values.
    /// If no EntityHandling is specified, it defaults to EntityHandling::ExpandCharEntities.
    ASPOSECPP_SHARED_API System::Xml::EntityHandling get_EntityHandling();
    /// Sets a value that specifies how the reader handles entities.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_EntityHandling(System::Xml::EntityHandling value);
    /// Sets the XmlResolver used for resolving DTD references.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);

    /// Initializes a new instance of the XmlTextReader class with the specified stream.
    /// @param input The stream containing the XML data to read.
    /// @throws ArgumentNullException @p input is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<IO::Stream>& input);
    /// Initializes a new instance of the XmlTextReader class with the specified URL and stream.
    /// @param url The URL to use for resolving external resources.
    /// The XmlTextReader::get_BaseURI is set to this value.
    /// @param input The stream containing the XML data to read.
    /// @throws ArgumentNullException @p input is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url, const SharedPtr<IO::Stream>& input);
    /// Initializes a new instance of the XmlTextReader class with the specified stream and XmlNameTable.
    /// @param input The stream containing the XML data to read.
    /// @param nt The XmlNameTable to use.
    /// @throws NullReferenceException The @p input or @p nt value is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<IO::Stream>& input, const SharedPtr<XmlNameTable>& nt);
    /// Initializes a new instance of the XmlTextReader class with the specified URL, stream and XmlNameTable.
    /// @param url The URL to use for resolving external resources.
    /// The XmlTextReader::get_BaseURI is set to this value.
    /// If @p url is @c nullptr, @c BaseURI is set to String::Empty.
    /// @param input The stream containing the XML data to read.
    /// @param nt The XmlNameTable to use.
    /// @throws NullReferenceException The @p input or @p nt value is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url, const SharedPtr<IO::Stream>& input, const SharedPtr<XmlNameTable>& nt);
    /// Initializes a new instance of the XmlTextReader class with the specified TextReader.
    /// @param input The TextReader containing the XML data to read.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<IO::TextReader>& input);
    /// Initializes a new instance of the XmlTextReader class with the specified URL and TextReader.
    /// @param url The URL to use for resolving external resources.
    /// The XmlTextReader::get_BaseURI is set to this value.
    /// @param input The TextReader containing the XML data to read.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url, const SharedPtr<IO::TextReader>& input);
    /// Initializes a new instance of the XmlTextReader class with the specified TextReader and XmlNameTable.
    /// @param input The TextReader containing the XML data to read.
    /// @param nt The XmlNameTable to use.
    /// @throws NullReferenceException The @p nt value is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<IO::TextReader>& input, const SharedPtr<XmlNameTable>& nt);
    /// Initializes a new instance of the XmlTextReader class with the specified URL, TextReader and XmlNameTable.
    /// @param url The URL to use for resolving external resources.
    /// The XmlTextReader::get_BaseURI is set to this value.
    /// If @p url is @c nullptr, @c BaseURI is set to String::Empty.
    /// @param input The TextReader containing the XML data to read.
    /// @param nt The XmlNameTable to use.
    /// @throws ArgumentNullException The @p nt value is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url, const SharedPtr<IO::TextReader>& input, const SharedPtr<XmlNameTable>& nt);
    /// Initializes a new instance of the XmlTextReader class with the specified stream, XmlNodeType, and XmlParserContext.
    /// @param xmlFragment The stream containing the XML fragment to parse.
    /// @param fragType The XmlNodeType of the XML fragment. This also determines what the fragment can contain.
    /// @param context The XmlParserContext in which the @p xmlFragment is to be parsed.
    /// This includes the XmlNameTable to use, encoding, namespace scope, the current @c xml:lang, and the @c xml:space scope.
    /// @throws XmlException @p fragType is not an Element, Attribute, or Document XmlNodeType::
    /// @throws ArgumentNullException @p xmlFragment is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<IO::Stream>& xmlFragment, XmlNodeType fragType, const SharedPtr<XmlParserContext>& context);
    /// Initializes a new instance of the XmlTextReader class with the specified string, XmlNodeType, and XmlParserContext.
    /// @param xmlFragment The string containing the XML fragment to parse.
    /// @param fragType The XmlNodeType of the XML fragment. This also determines what the fragment string can contain.
    /// @param context The XmlParserContext in which the @p xmlFragment is to be parsed.
    /// This includes the XmlNameTable to use, encoding, namespace scope, the current @c xml:lang, and the @c xml:space scope.
    /// @throws XmlException @p fragType is not an @c Element, @c Attribute, or @c DocumentXmlNodeType.
    /// @throws ArgumentNullException @p xmlFragment is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextReader(const String& xmlFragment, XmlNodeType fragType, const SharedPtr<XmlParserContext>& context);
    /// Initializes a new instance of the XmlTextReader class with the specified file.
    /// @param url The URL for the file containing the XML data.
    /// The XmlTextReader::get_BaseURI is set to this value.
    /// @throws FileNotFoundException The specified file cannot be found.
    /// @throws DirectoryNotFoundException Part of the filename or directory cannot be found.
    /// @throws InvalidOperationException @p url is an empty string.
    /// @throws WebException The remote filename cannot be resolved.
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p url is not a valid URI.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url);
    /// Initializes a new instance of the XmlTextReader class with the specified file and XmlNameTable.
    /// @param url The URL for the file containing the XML data to read.
    /// @param nt The XmlNameTable to use.
    /// @throws NullReferenceException The @p nt value is @c nullptr.
    /// @throws FileNotFoundException The specified file cannot be found.
    /// @throws DirectoryNotFoundException Part of the filename or directory cannot be found.
    /// @throws InvalidOperationException @p url is an empty string.
    /// @throws WebException The remote filename cannot be resolved.
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p url is not a valid URI.
    ASPOSECPP_SHARED_API XmlTextReader(const String& url, const SharedPtr<XmlNameTable>& nt);

    /// Returns the value of the attribute with the specified name.
    /// @param name The qualified name of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    ASPOSECPP_SHARED_API String GetAttribute(String name) override;
    /// Returns the value of the attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    /// This method does not move the reader.
    ASPOSECPP_SHARED_API String GetAttribute(String localName, String namespaceURI) override;
    /// Returns the value of the attribute with the specified index.
    /// @param i The index of the attribute. The index is zero-based. (The first attribute has index 0.)
    /// @returns The value of the specified attribute.
    /// @throws ArgumentOutOfRangeException The @p i parameter is less than 0 or
    /// greater than or equal to XmlTextReader::get_AttributeCount value.
    ASPOSECPP_SHARED_API String GetAttribute(int32_t i) override;
    /// Moves to the attribute with the specified name.
    /// @param name The qualified name of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false.
    /// If @c false, the reader's position does not change.
    ASPOSECPP_SHARED_API bool MoveToAttribute(String name) override;
    /// Moves to the attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false.
    /// If @c false, the reader's position does not change.
    ASPOSECPP_SHARED_API bool MoveToAttribute(String localName, String namespaceURI) override;
    /// Moves to the attribute with the specified index.
    /// @param i The index of the attribute.
    /// @throws ArgumentOutOfRangeException The @p i parameter is less than 0 or
    /// greater than or equal to XmlTextReader::get_AttributeCount value.
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
    /// @throws XmlException An error occurred while parsing the XML.
    ASPOSECPP_SHARED_API bool Read() override;
    /// Changes the XmlReader::get_ReadState to @c Closed.
    ASPOSECPP_SHARED_API void Close() override;
    /// Skips the children of the current node.
    ASPOSECPP_SHARED_API void Skip() override;
    /// Resolves a namespace prefix in the current element's scope.
    /// @param prefix The prefix whose namespace URI you want to resolve.
    /// To match the default namespace, pass an empty string. This string does not have to be atomized.
    /// @returns The namespace URI to which the prefix maps or @c nullptr if no matching prefix is found.
    /// @throws ArgumentNullException The XmlTextReader::get_Namespaces value is set to @c true and the @p prefix value is @c nullptr.
    ASPOSECPP_SHARED_API String LookupNamespace(const String& prefix) override;
    /// Resolves the entity reference for @c EntityReference nodes.
    ASPOSECPP_SHARED_API void ResolveEntity() override;
    /// Reads the content and returns the @c Base64 decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported in the current node.
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
    /// @throws NotSupportedException The XmlTextReader implementation does not support this method.
    /// @throws XmlException The element contains mixed-content.
    /// @throws FormatException The content cannot be converted to the requested type.
    ASPOSECPP_SHARED_API int32_t ReadElementContentAsBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the content and returns the @c BinHex decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported on the current node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlTextReader implementation does not support this method.
    ASPOSECPP_SHARED_API int32_t ReadContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the element and decodes the @c BinHex content.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The current node is not an element node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlReader implementation does not support this method.
    /// @throws XmlException The element contains mixed-content.
    /// @throws FormatException The content cannot be converted to the requested type.
    ASPOSECPP_SHARED_API int32_t ReadElementContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Reads the contents of an element or a text node as a string.
    /// @returns The contents of the element or text node.
    /// This can be an empty string if the reader is positioned on something other than an element or text node,
    /// or if there is no more text content to return in the current context.
    /// @c Note: The text node can be either an element or an attribute text node.
    /// @throws XmlException An error occurred while parsing the XML.
    /// @throws InvalidOperationException An invalid operation was attempted.
    ASPOSECPP_SHARED_API String ReadString() override;
    /// Returns a value indicating whether the class can return line information.
    /// @returns @c true if the class can return line information; otherwise, @c false.
    ASPOSECPP_SHARED_API bool HasLineInfo() override;
    /// Returns a collection that contains all namespaces currently in-scope.
    /// @param scope An XmlNamespaceScope value that specifies the type of namespace nodes to return.
    /// @returns An IDictionary object that contains all the current in-scope namespaces.
    /// If the reader is not positioned on an element, an empty dictionary (no namespaces) is returned.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) override;
    /// Resets the state of the reader to ReadState::Initial.
    /// @throws InvalidOperationException Calling @c ResetState if the reader was constructed using an XmlParserContext.
    /// @throws XmlException Documents in a single stream do not share the same encoding.
    ASPOSECPP_SHARED_API void ResetState();
    /// Returns the remainder of the buffered XML.
    /// @returns A TextReader containing the remainder of the buffered XML.
    ASPOSECPP_SHARED_API SharedPtr<IO::TextReader> GetRemainder();
    /// Reads the text contents of an element into a character buffer.
    /// This method is designed to read large streams of embedded text by calling it successively.
    /// @param buffer The array of characters that serves as the buffer to which the text contents are written.
    /// @param index The position within @p buffer where the method can begin writing text contents.
    /// @param count The number of characters to write into @p buffer.
    /// @returns The number of characters read.
    /// This can be 0 if the reader is not positioned on an element or if there is no more text content to return in the current context.
    /// @throws ArgumentException @p count is greater than the space specified in the @p buffer (buffer size - @p index).
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index < 0 or @p count < 0.
    ASPOSECPP_SHARED_API int32_t ReadChars(const ArrayPtr<char16_t>& buffer, int32_t index, int32_t count);
    /// Decodes Base64 and returns the decoded binary bytes.
    /// @param array The array of characters that serves as the buffer to which the text contents are written.
    /// @param offset The zero-based index into the array specifying where the method can begin to write to the buffer.
    /// @param len The number of bytes to write into the buffer.
    /// @returns The number of bytes written to the buffer.
    /// @throws XmlException The Base64 sequence is not valid.
    /// @throws ArgumentNullException The value of @p array is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p offset < 0, or @p len < 0, or @p len > @p array.get_Length - @p offset.
    ASPOSECPP_SHARED_API int32_t ReadBase64(const ArrayPtr<uint8_t>& array, int32_t offset, int32_t len);
    /// Decodes @c BinHex and returns the decoded binary bytes.
    /// @param array The byte array that serves as the buffer to which the decoded binary bytes are written.
    /// @param offset The zero-based index into the array specifying where the method can begin to write to the buffer.
    /// @param len The number of bytes to write into the buffer.
    /// @returns The number of bytes written to your buffer.
    /// @throws XmlException The @c BinHex sequence is not valid.
    /// @throws ArgumentNullException The value of @p array is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p offset < 0, or @p len < 0, or @p len > @p array.get_Length - @p offset.
    ASPOSECPP_SHARED_API int32_t ReadBinHex(const ArrayPtr<uint8_t>& array, int32_t offset, int32_t len);

protected:

    /// @cond
    SharedPtr<XmlTextReaderImpl> get_Impl();
    ASPOSECPP_SHARED_API SharedPtr<XmlNamespaceManager> get_NamespaceManager() override;
    void set_XmlValidatingReaderCompatibilityMode(bool value);
    ASPOSECPP_SHARED_API SharedPtr<IDtdInfo> get_DtdInfo() override;
    /// @endcond

    /// Initializes a new instance of the XmlTextReader.
    ASPOSECPP_SHARED_API XmlTextReader();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlTextReader, CODEPORTING_ARGS());

    /// Initializes a new instance of the XmlTextReader class with the specified XmlNameTable.
    /// @param nt The XmlNameTable to use.
    ASPOSECPP_SHARED_API XmlTextReader(const SharedPtr<XmlNameTable>& nt);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlTextReader, CODEPORTING_ARGS(SharedPtr<XmlNameTable> nt));

    virtual ASPOSECPP_SHARED_API ~XmlTextReader();

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
    const char* DBG_class_name() const override { return "XmlTextReader"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlTextReaderImpl> _impl;

    ASPOSECPP_SHARED_API String LookupPrefix(const String& namespaceName) override;

};

} // namespace Xml
} // namespace System


