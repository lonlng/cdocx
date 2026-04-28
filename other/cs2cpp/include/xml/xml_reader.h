/// @file xml/xml_reader.h

#pragma once

#include <xml/xml_space.h>
#include <xml/xml_node_type.h>
#include <xml/read_state.h>
#include <system/idisposable.h>
#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
class DateTime;
class DateTimeOffset;
class Decimal;
namespace IO
{
class Stream;
class StringWriter;
class TextReader;
} // namespace IO
class TypeInfo;
namespace Xml
{
enum class ConformanceLevel;
class IDtdInfo;
class IXmlLineInfo;
class IXmlNamespaceResolver;
class ReadContentAsBinaryHelper;
namespace Schema
{
class IXmlSchemaInfo;
class Parser;
} // namespace Schema
class XmlLoader;
class XmlNamespaceManager;
class XmlNameTable;
class XmlParserContext;
class XmlReaderSettings;
class XmlSqlBinaryReader;
class XmlSubtreeReader;
class XmlTextReaderImpl;
class XmlTextWriter;
class XmlWrappingReader;
class XmlWriter;
namespace XPath
{
class XPathDocumentImpl;
} // namespace XPath
class XsdCachingReader;
class XsdValidatingReader;
namespace Xsl
{
namespace XsltOld
{
class ReaderOutput;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a reader that provides fast, noncached, forward-only access to XML data.
class ASPOSECPP_SHARED_CLASS XmlReader : public IDisposable
{
    typedef XmlReader ThisType;
    typedef IDisposable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlReader>;

private:
    /// @cond
    friend class XmlSqlBinaryReader;
    friend class XmlWriter;
    friend class ReadContentAsBinaryHelper;
    friend class XmlWrappingReader;
    friend class XmlReaderSettings;
    friend class XmlSubtreeReader;
    friend class XmlTextReaderImpl;
    friend class XsdCachingReader;
    friend class XsdValidatingReader;
    friend class XmlLoader;
    friend class Schema::Parser;
    friend class XPath::XPathDocumentImpl;
    friend class Xsl::XsltOld::ReaderOutput;
    /// @endcond

public:

    /// Returns the XmlReaderSettings object used to create this XmlReader instance.
    /// @returns The XmlReaderSettings object used to create this reader instance.
    /// If this reader was not created using the XmlReader::Create method, this method returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlReaderSettings> get_Settings();
    /// When overridden in a derived class, gets the type of the current node.
    /// @returns One of the enumeration values that specify the type of the current node.
    virtual ASPOSECPP_SHARED_API XmlNodeType get_NodeType() = 0;
    /// When overridden in a derived class, gets the qualified name of the current node.
    /// @returns The qualified name of the current node.
    /// For example, @c Name is @c bk:book for the element <tt><bk:book></tt>.
    ///
    /// The name returned is dependent on the XmlReader::get_NodeType value of the node.
    /// The following node types return the listed values. All other node types return an empty string.
    /// <list type="table"><listheader><term> Node type
    /// </term><description> Name
    /// </description></listheader><item><term>@c Attribute</term><description> The name of the attribute.
    /// </description></item><item><term>@c DocumentType</term><description> The document type name.
    /// </description></item><item><term>@c Element</term><description> The tag name.
    /// </description></item><item><term>@c EntityReference</term><description> The name of the entity referenced.
    /// </description></item><item><term>@c ProcessingInstruction</term><description> The target of the processing instruction.
    /// </description></item><item><term>XmlDeclaration</term><description> The literal string @c xml.
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API String get_Name();
    /// When overridden in a derived class, gets the local name of the current node.
    /// @returns The name of the current node with the prefix removed.
    /// For example, @c LocalName is @c book for the element <tt><bk:book></tt>.
    /// For node types that do not have a name (like @c Text, @c Comment, and so on), this method returns String::Empty.
    virtual ASPOSECPP_SHARED_API String get_LocalName() = 0;
    /// When overridden in a derived class, gets the namespace URI (as defined in the W3C Namespace specification)
    /// of the node on which the reader is positioned.
    /// @returns The namespace URI of the current node; otherwise an empty string.
    virtual ASPOSECPP_SHARED_API String get_NamespaceURI() = 0;
    /// When overridden in a derived class, gets the namespace prefix associated with the current node.
    /// @returns The namespace prefix associated with the current node.
    virtual ASPOSECPP_SHARED_API String get_Prefix() = 0;
    /// When overridden in a derived class, gets a value indicating whether the current node can have a XmlReader::get_Value value.
    /// @returns @c true if the node on which the reader is currently positioned can have a @c Value;
    /// otherwise, @c false. If @c false, the node has a value of String::Empty.
    virtual ASPOSECPP_SHARED_API bool get_HasValue();
    /// When overridden in a derived class, gets the text value of the current node.
    /// @returns The value returned depends on the XmlReader::get_NodeType value of the node.
    ///
    /// The following table lists node types that have a value to return. All other node types return String::Empty.
    /// <list type="table"><listheader><term> Node type
    /// </term><description> Value
    /// </description></listheader><item><term>@c Attribute</term><description> The value of the attribute.
    /// </description></item><item><term>@c CDATA</term><description> The content of the CDATA section.
    /// </description></item><item><term>@c Comment</term><description> The content of the comment.
    /// </description></item><item><term>@c DocumentType</term><description> The internal subset.
    /// </description></item><item><term>@c ProcessingInstruction</term><description> The entire content, excluding the target.
    /// </description></item><item><term>@c SignificantWhitespace</term><description> The white space between markup in a mixed content model.
    /// </description></item><item><term>@c Text</term><description> The content of the text node.
    /// </description></item><item><term>@c Whitespace</term><description> The white space between markup.
    /// </description></item><item><term>XmlDeclaration</term><description> The content of the declaration.
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API String get_Value() = 0;
    /// When overridden in a derived class, gets the depth of the current node in the XML document.
    /// @returns The depth of the current node in the XML document.
    virtual ASPOSECPP_SHARED_API int32_t get_Depth() = 0;
    /// When overridden in a derived class, gets the base URI of the current node.
    /// @returns The base URI of the current node.
    virtual ASPOSECPP_SHARED_API String get_BaseURI() = 0;
    /// When overridden in a derived class, gets a value indicating whether the current node is an empty element
    /// (for example, <tt>\<MyElement/></tt>).
    /// @returns @c true if the current node is an element (XmlReader::get_NodeType equals XmlNodeType::Element)
    /// that ends with <tt>/></tt>; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_IsEmptyElement() = 0;
    /// When overridden in a derived class, gets a value indicating whether the current node is an attribute that
    /// was generated from the default value defined in the DTD or schema.
    /// @returns @c true if the current node is an attribute whose value was generated from the default value defined
    /// in the DTD or schema; @c false if the attribute value was explicitly set.
    virtual ASPOSECPP_SHARED_API bool get_IsDefault();
    /// When overridden in a derived class, gets the quotation mark character used to enclose the value of an attribute node.
    /// @returns The quotation mark character (" or ') used to enclose the value of an attribute node.
    virtual ASPOSECPP_SHARED_API char16_t get_QuoteChar();
    /// When overridden in a derived class, gets the current @c xml:space scope.
    /// @returns One of the XmlSpace values. If no @c xml:space scope exists, this value defaults to XmlSpace::None.
    virtual ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace();
    /// When overridden in a derived class, gets the current @c xml:lang scope.
    /// @returns The current @c xml:lang scope.
    virtual ASPOSECPP_SHARED_API String get_XmlLang();
    /// Returns the schema information that has been assigned to the current node as a result of schema validation.
    /// @returns An IXmlSchemaInfo object containing the schema information for the current node.
    /// Schema information can be set on elements, attributes, or on text nodes with a non-null XmlReader::get_ValueType value.
    /// If the current node is not one of the above node types, or if the XmlReader instance does not report schema information,
    /// this method returns @c nullptr.
    /// If this method is called from an XmlTextReader or an XmlValidatingReader object, this method always returns @c nullptr.
    /// These XmlReader implementations do not expose schema information through the get_SchemaInfo method.
    virtual ASPOSECPP_SHARED_API SharedPtr<Schema::IXmlSchemaInfo> get_SchemaInfo();
    /// Returns The type for the current node.
    /// @returns The type that corresponds to the typed value of the node. The default is String.
    virtual ASPOSECPP_SHARED_API TypeInfo get_ValueType();
    /// When overridden in a derived class, gets the number of attributes on the current node.
    /// @returns The number of attributes on the current node.
    virtual ASPOSECPP_SHARED_API int32_t get_AttributeCount() = 0;
    /// When overridden in a derived class, gets a value indicating whether the reader is positioned at the end of the stream.
    /// @returns @c true if the reader is positioned at the end of the stream; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_EOF() = 0;
    /// When overridden in a derived class, gets the state of the reader.
    /// @returns One of the enumeration values that specifies the state of the reader.
    virtual ASPOSECPP_SHARED_API System::Xml::ReadState get_ReadState() = 0;
    /// When overridden in a derived class, gets the XmlNameTable associated with this implementation.
    /// @returns The XmlNameTable enabling you to get the atomized version of a string within the node.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable() = 0;
    /// Returns a value indicating whether this reader can parse and resolve entities.
    /// @returns @c true if the reader can parse and resolve entities; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_CanResolveEntity();
    /// Returns a value indicating whether the XmlReader implements the binary content read methods.
    /// @returns @c true if the binary content read methods are implemented; otherwise @c false.
    virtual ASPOSECPP_SHARED_API bool get_CanReadBinaryContent();
    /// Returns a value indicating whether the XmlReader implements the XmlReader::ReadValueChunk method.
    /// @returns @c true if the XmlReader implements the XmlReader::ReadValueChunk method; otherwise @c false.
    virtual ASPOSECPP_SHARED_API bool get_CanReadValueChunk();
    /// Returns a value indicating whether the current node has any attributes.
    /// @returns @c true if the current node has attributes; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool get_HasAttributes();

    /// Reads the text content at the current position as an Object.
    /// @returns The text content as the most appropriate object type.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadContentAsObject();
    /// Reads the text content at the current position as a Boolean.
    /// @returns The text content as a Boolean object.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API bool ReadContentAsBoolean();
    /// Reads the text content at the current position as a DateTime object.
    /// @returns The text content as a DateTime object.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API DateTime ReadContentAsDateTime();
    /// Reads the text content at the current position as a DateTimeOffset object.
    /// @returns The text content as a DateTimeOffset object.
    virtual ASPOSECPP_SHARED_API DateTimeOffset ReadContentAsDateTimeOffset();
    /// Reads the text content at the current position as a double-precision floating-point number.
    /// @returns The text content as a double-precision floating-point number.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API double ReadContentAsDouble();
    /// Reads the text content at the current position as a single-precision floating point number.
    /// @returns The text content at the current position as a single-precision floating point number.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API float ReadContentAsFloat();
    /// Reads the text content at the current position as a Decimal object.
    /// @returns The text content at the current position as a Decimal object.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API Decimal ReadContentAsDecimal();
    /// Reads the text content at the current position as a 32-bit signed integer.
    /// @returns The text content as a 32-bit signed integer.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API int32_t ReadContentAsInt();
    /// Reads the text content at the current position as a 64-bit signed integer.
    /// @returns The text content as a 64-bit signed integer.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API int64_t ReadContentAsLong();
    /// Reads the text content at the current position as a String object.
    /// @returns The text content as a String object.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws FormatException The string format is not valid.
    virtual ASPOSECPP_SHARED_API String ReadContentAsString();
    /// Reads the content as an object of the type specified.
    /// @param returnType The type of the value to be returned.
    /// @param namespaceResolver An IXmlNamespaceResolver object that is used to resolve any namespace prefixes related to type conversion.
    /// For example, this can be used when converting an XmlQualifiedName object to an @c xs:string.
    /// This value can be @c nullptr.
    /// @returns The concatenated text content or attribute value converted to the requested type.
    /// @throws FormatException The content is not in the correct format for the target type.
    /// @throws InvalidCastException The attempted cast is not valid.
    /// @throws ArgumentNullException The @p returnType value is @c nullptr.
    /// @throws InvalidOperationException The current node is not a supported node type.
    /// @throws OverflowException Read Decimal::MaxValue.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadContentAs(const TypeInfo& returnType, SharedPtr<IXmlNamespaceResolver> namespaceResolver);
    /// Reads the current element and returns the contents as an Object.
    /// @returns A boxed object of the most appropriate type.
    /// The XmlReader::get_ValueType value determines the appropriate type.
    /// If the content is typed as a list type, this method returns an array of boxed objects of the appropriate type.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadElementContentAsObject();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as an Object.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns A boxed object of the most appropriate type.
    /// The XmlReader::get_ValueType value determines the appropriate type.
    /// If the content is typed as a list type, this method returns an array of boxed objects of the appropriate type.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadElementContentAsObject(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a Boolean object.
    /// @returns The element content as a Boolean object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a Boolean object.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API bool ReadElementContentAsBoolean();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a Boolean object.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a Boolean object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API bool ReadElementContentAsBoolean(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a DateTime object.
    /// @returns The element content as a DateTime object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a DateTime object.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API DateTime ReadElementContentAsDateTime();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a DateTime object.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element contents as a DateTime object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API DateTime ReadElementContentAsDateTime(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a double-precision floating-point number.
    /// @returns The element content as a double-precision floating-point number.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a double-precision floating-point number.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API double ReadElementContentAsDouble();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a double-precision floating-point number.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a double-precision floating-point number.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API double ReadElementContentAsDouble(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as single-precision floating-point number.
    /// @returns The element content as a single-precision floating point number.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a single-precision floating-point number.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API float ReadElementContentAsFloat();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a single-precision floating-point number.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a single-precision floating point number.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a single-precision floating-point number.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API float ReadElementContentAsFloat(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a Decimal object.
    /// @returns The element content as a Decimal object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a Decimal.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API Decimal ReadElementContentAsDecimal();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a Decimal object.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a Decimal object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a Decimal.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API Decimal ReadElementContentAsDecimal(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a 32-bit signed integer.
    /// @returns The element content as a 32-bit signed integer.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a 32-bit signed integer.
    virtual ASPOSECPP_SHARED_API int32_t ReadElementContentAsInt();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a 32-bit signed integer.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a 32-bit signed integer.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a 32-bit signed integer.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API int32_t ReadElementContentAsInt(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a 64-bit signed integer.
    /// @returns The element content as a 64-bit signed integer.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a 64-bit signed integer.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API int64_t ReadElementContentAsLong();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a 64-bit signed integer.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a 64-bit signed integer.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a 64-bit signed integer.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API int64_t ReadElementContentAsLong(String localName, String namespaceURI);
    /// Reads the current element and returns the contents as a String object.
    /// @returns The element content as a String object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a String object.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    virtual ASPOSECPP_SHARED_API String ReadElementContentAsString();
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the current element and returns the contents as a String object.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content as a String object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to a String object.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    virtual ASPOSECPP_SHARED_API String ReadElementContentAsString(String localName, String namespaceURI);
    /// Reads the element content as the requested type.
    /// @param returnType The type of the value to be returned.
    /// @param namespaceResolver An IXmlNamespaceResolver object that is used to resolve any namespace prefixes related to type conversion.
    /// @returns The element content converted to the requested typed object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws OverflowException Read Decimal::MaxValue.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadElementContentAs(const TypeInfo& returnType, SharedPtr<IXmlNamespaceResolver> namespaceResolver);
    /// Checks that the specified local name and namespace URI matches that of the current element,
    /// then reads the element content as the requested type.
    /// @param returnType The type of the value to be returned.
    /// @param namespaceResolver An IXmlNamespaceResolver object that is used to resolve any namespace prefixes related to type conversion.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns The element content converted to the requested typed object.
    /// @throws InvalidOperationException The XmlReader is not positioned on an element.
    /// @throws XmlException The current element contains child elements.
    /// The element content cannot be converted to the requested type.
    /// @throws ArgumentNullException The method is called with @c nullptr arguments.
    /// @throws ArgumentException The specified local name and namespace URI do not match that of the current element being read.
    /// @throws OverflowException Read Decimal::MaxValue.
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> ReadElementContentAs(const TypeInfo& returnType, SharedPtr<IXmlNamespaceResolver> namespaceResolver, String localName, String namespaceURI);
    /// When overridden in a derived class, gets the value of the attribute with the specified XmlReader::get_Name value.
    /// @param name The qualified name of the attribute.
    /// @returns The value of the specified attribute.
    /// If the attribute is not found or the value is String::Empty, @c nullptr is returned.
    /// @throws ArgumentNullException @p name is @c nullptr.
    virtual ASPOSECPP_SHARED_API String GetAttribute(String name) = 0;
    /// When overridden in a derived class, gets the value of the attribute with the specified
    /// XmlReader::get_LocalName and XmlReader::get_NamespaceURI values.
    /// @param name The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The value of the specified attribute.
    /// If the attribute is not found or the value is String::Empty, @c nullptr is returned.
    /// This method does not move the reader.
    /// @throws ArgumentNullException @p name is @c nullptr.
    virtual ASPOSECPP_SHARED_API String GetAttribute(String name, String namespaceURI) = 0;
    /// When overridden in a derived class, gets the value of the attribute with the specified index.
    /// @param i The index of the attribute. The index is zero-based. (The first attribute has index 0.)
    /// @returns The value of the specified attribute. This method does not move the reader.
    /// @throws ArgumentOutOfRangeException @p i is out of range.
    /// It must be non-negative and less than the size of the attribute collection.
    virtual ASPOSECPP_SHARED_API String GetAttribute(int32_t i) = 0;

    /// When overridden in a derived class, gets the value of the attribute with the specified index.
    /// @param i The index of the attribute.
    /// @returns The value of the specified attribute.
    virtual ASPOSECPP_SHARED_API String idx_get(int32_t i);
    /// When overridden in a derived class, gets the value of the attribute with the specified XmlReader::get_Name value.
    /// @param name The qualified name of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API String idx_get(String name);
    /// When overridden in a derived class, gets the value of the attribute with the specified
    /// XmlReader::get_LocalName and XmlReader::get_NamespaceURI values.
    /// @param name The local name of the attribute.
    /// @param namespaceURI The namespace URI of the attribute.
    /// @returns The value of the specified attribute. If the attribute is not found, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API String idx_get(String name, String namespaceURI);

    /// When overridden in a derived class, moves to the attribute with the specified XmlReader::get_Name value.
    /// @param name The qualified name of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false. If @c false, the reader's position does not change.
    /// @throws ArgumentException The parameter is an empty string.
    virtual ASPOSECPP_SHARED_API bool MoveToAttribute(String name) = 0;
    /// When overridden in a derived class, moves to the attribute with the specified
    /// XmlReader::get_LocalName and XmlReader::get_NamespaceURI  values.
    /// @param name The local name of the attribute.
    /// @param ns The namespace URI of the attribute.
    /// @returns @c true if the attribute is found; otherwise, @c false. If @c false, the reader's position does not change.
    /// @throws ArgumentNullException Both parameter values are @c nullptr.
    virtual ASPOSECPP_SHARED_API bool MoveToAttribute(String name, String ns) = 0;
    /// When overridden in a derived class, moves to the attribute with the specified index.
    /// @param i The index of the attribute.
    /// @throws ArgumentOutOfRangeException The parameter has a negative value.
    virtual ASPOSECPP_SHARED_API void MoveToAttribute(int32_t i);
    /// When overridden in a derived class, moves to the first attribute.
    /// @returns @c true if an attribute exists (the reader moves to the first attribute);
    /// otherwise, @c false (the position of the reader does not change).
    virtual ASPOSECPP_SHARED_API bool MoveToFirstAttribute() = 0;
    /// When overridden in a derived class, moves to the next attribute.
    /// @returns @c true if there is a next attribute; @c false if there are no more attributes.
    virtual ASPOSECPP_SHARED_API bool MoveToNextAttribute() = 0;
    /// When overridden in a derived class, moves to the element that contains the current attribute node.
    /// @returns @c true if the reader is positioned on an attribute (the reader moves to the element that owns the attribute);
    /// @c false if the reader is not positioned on an attribute (the position of the reader does not change).
    virtual ASPOSECPP_SHARED_API bool MoveToElement() = 0;
    /// When overridden in a derived class, parses the attribute value into one or more @c Text, @c EntityReference, or @c EndEntity nodes.
    /// @returns @c true if there are nodes to return.
    /// @c false if the reader is not positioned on an attribute node when the initial call is made or if all the attribute values have been read.
    /// An empty attribute, such as, <tt>misc=""</tt>, returns @c true with a single node with a value of String::Empty.
    virtual ASPOSECPP_SHARED_API bool ReadAttributeValue() = 0;
    /// When overridden in a derived class, reads the next node from the stream.
    /// @returns @c true if the next node was read successfully; otherwise, @c false.
    /// @throws XmlException An error occurred while parsing the XML.
    virtual ASPOSECPP_SHARED_API bool Read() = 0;
    /// When overridden in a derived class, changes the XmlReader::get_ReadState to ReadState::Closed.
    virtual ASPOSECPP_SHARED_API void Close();
    /// Skips the children of the current node.
    virtual ASPOSECPP_SHARED_API void Skip();
    /// When overridden in a derived class, resolves a namespace prefix in the current element's scope.
    /// @param prefix The prefix whose namespace URI you want to resolve. To match the default namespace, pass an empty string.
    /// @returns The namespace URI to which the prefix maps or @c nullptr if no matching prefix is found.
    virtual ASPOSECPP_SHARED_API String LookupNamespace(const String& prefix) = 0;
    /// When overridden in a derived class, resolves the entity reference for @c EntityReference nodes.
    /// @throws InvalidOperationException The reader is not positioned on an @c EntityReference node;
    /// this implementation of the reader cannot resolve entities (XmlReader::get_CanResolveEntity returns @c false).
    virtual ASPOSECPP_SHARED_API void ResolveEntity() = 0;
    /// Reads the content and returns the Base64 decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported on the current node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlReader implementation does not support this method.
    virtual ASPOSECPP_SHARED_API int32_t ReadContentAsBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count);
    /// Reads the element and decodes the @c Base64 content.
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
    virtual ASPOSECPP_SHARED_API int32_t ReadElementContentAsBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count);
    /// Reads the content and returns the @c BinHex decoded binary bytes.
    /// @param buffer The buffer into which to copy the resulting text. This value cannot be @c nullptr.
    /// @param index The offset into the buffer where to start copying the result.
    /// @param count The maximum number of bytes to copy into the buffer.
    /// The actual number of bytes copied is returned from this method.
    /// @returns The number of bytes written to the buffer.
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws InvalidOperationException The call is not supported on the current node.
    /// @throws ArgumentOutOfRangeException The index into the buffer or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlReader implementation does not support this method.
    virtual ASPOSECPP_SHARED_API int32_t ReadContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count);
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
    virtual ASPOSECPP_SHARED_API int32_t ReadElementContentAsBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count);
    /// Reads large streams of text embedded in an XML document.
    /// @param buffer The array of characters that serves as the buffer to which the text contents are written.
    /// This value cannot be @c nullptr.
    /// @param index The offset within the buffer where the XmlReader can start to copy the results.
    /// @param count The maximum number of characters to copy into the buffer.
    /// The actual number of characters copied is returned from this method.
    /// @returns The number of characters read into the buffer.
    /// The value zero is returned when there is no more text content.
    /// @throws InvalidOperationException The current node does not have a value (XmlReader::get_HasValue is @c false).
    /// @throws ArgumentNullException The @p buffer value is @c nullptr.
    /// @throws ArgumentOutOfRangeException The index into the buffer, or index + count is larger than the allocated buffer size.
    /// @throws NotSupportedException The XmlReader implementation does not support this method.
    /// @throws XmlException The XML data is not well-formed.
    virtual ASPOSECPP_SHARED_API int32_t ReadValueChunk(ArrayPtr<char16_t> buffer, int32_t index, int32_t count);
    /// When overridden in a derived class, reads the contents of an element or text node as a string.
    /// However, it is recommended to use the XmlReader::ReadElementContentAsString method instead,
    /// because it provides a more straightforward way to handle this operation.
    /// @returns The contents of the element or an empty string.
    /// @throws XmlException An error occurred while parsing the XML.
    virtual ASPOSECPP_SHARED_API String ReadString();
    /// Checks whether the current node is a content (non-white space text, @c CDATA, @c Element, @c EndElement, @c EntityReference, or @c EndEntity) node.
    /// If the node is not a content node, the reader skips ahead to the next content node or end of file.
    /// It skips over nodes of the following type: @c ProcessingInstruction, @c DocumentType, @c Comment, @c Whitespace, or @c SignificantWhitespace.
    /// @returns The XmlReader::get_NodeType value of the current node found by the method or XmlNodeType::None if
    /// the reader has reached the end of the input stream.
    /// @throws XmlException Incorrect XML encountered in the input stream.
    virtual ASPOSECPP_SHARED_API XmlNodeType MoveToContent();
    /// Checks that the current node is an element and advances the reader to the next node.
    /// @throws XmlException Incorrect XML was encountered in the input stream.
    virtual ASPOSECPP_SHARED_API void ReadStartElement();
    /// Checks that the current content node is an element with the given XmlReader::get_Name value and
    /// advances the reader to the next node.
    /// @param name The qualified name of the element.
    /// @throws XmlException Incorrect XML was encountered in the input stream.
    /// The XmlReader::get_Name of the element does not match the given @p name.
    virtual ASPOSECPP_SHARED_API void ReadStartElement(String name);
    /// Checks that the current content node is an element with the given XmlReader::get_LocalName and
    /// XmlReader::get_NamespaceURI values and advances the reader to the next node.
    /// @param localname The local name of the element.
    /// @param ns The namespace URI of the element.
    /// @throws XmlException Incorrect XML was encountered in the input stream.
    /// The XmlReader::get_LocalName and XmlReader::get_NamespaceURI values of the element found do not match the given arguments.
    virtual ASPOSECPP_SHARED_API void ReadStartElement(String localname, String ns);
    /// Reads a text-only element.
    /// However, it is recommended to use the XmlReader::ReadElementContentAsString method instead,
    /// because it provides a more straightforward way to handle this operation.
    /// @returns The text contained in the element that was read. An empty string if the element is empty.
    /// @throws XmlException The next content node is not a start tag;
    /// or the element found does not contain a simple text value.
    virtual ASPOSECPP_SHARED_API String ReadElementString();
    /// Checks that the XmlReader::get_Name value of the element found matches the given string before reading a text-only element.
    /// However, it is recommended to use the XmlReader::ReadElementContentAsString method instead,
    /// because it provides a more straightforward way to handle this operation.
    /// @param name The name to check.
    /// @returns The text contained in the element that was read. An empty string if the element is empty.
    /// @throws XmlException If the next content node is not a start tag;
    /// if the element @c Name does not match the given argument;
    /// or if the element found does not contain a simple text value.
    virtual ASPOSECPP_SHARED_API String ReadElementString(String name);
    /// Checks that the XmlReader::get_LocalName and XmlReader::get_NamespaceURI values of the element found
    /// matches the given strings before reading a text-only element.
    /// However, it is recommended to use the XmlReader::ReadElementContentAsString method instead,
    /// because it provides a more straightforward way to handle this operation.
    /// @param localname The local name to check.
    /// @param ns The namespace URI to check.
    /// @returns The text contained in the element that was read. An empty string if the element is empty.
    /// @throws XmlException If the next content node is not a start tag;
    /// if the element @c LocalName or @c NamespaceURI values do not match the given arguments;
    /// or if the element found does not contain a simple text value.
    virtual ASPOSECPP_SHARED_API String ReadElementString(String localname, String ns);
    /// Checks that the current content node is an end tag and advances the reader to the next node.
    /// @throws XmlException The current node is not an end tag or if incorrect XML is encountered in the input stream.
    virtual ASPOSECPP_SHARED_API void ReadEndElement();
    /// Calls XmlReader::MoveToContent and tests if the current content node is a start tag or empty element tag.
    /// @returns @c true if XmlReader::MoveToContent finds a start tag or empty element tag;
    /// @c false if a node type other than XmlNodeType::Element was found.
    /// @throws XmlException Incorrect XML is encountered in the input stream.
    virtual ASPOSECPP_SHARED_API bool IsStartElement();
    /// Calls XmlReader::MoveToContent and tests if the current content node is a start tag or empty element tag and
    /// if the XmlReader::get_Name value of the element found matches the given argument.
    /// @param name The string matched against the @c Name value of the element found.
    /// @returns @c true if the resulting node is an element and the @c Name value matches the specified string.
    /// @c false if a node type other than XmlNodeType::Element was found or
    /// if the element @c Name value does not match the specified string.
    /// @throws XmlException Incorrect XML is encountered in the input stream.
    virtual ASPOSECPP_SHARED_API bool IsStartElement(String name);
    /// Calls XmlReader::MoveToContent and tests if the current content node is a start tag or empty element tag and
    /// if the XmlReader::get_LocalName and XmlReader::get_NamespaceURI values of the element found match the given strings.
    /// @param localname The string to match against the @c LocalName value of the element found.
    /// @param ns The string to match against the @c NamespaceURI value of the element found.
    /// @returns @c true if the resulting node is an element.
    /// @c false if a node type other than XmlNodeType::Element was found or
    /// if the @c LocalName and @c NamespaceURI values of the element do not match the specified strings.
    /// @throws XmlException Incorrect XML is encountered in the input stream.
    virtual ASPOSECPP_SHARED_API bool IsStartElement(String localname, String ns);
    /// Reads until an element with the specified qualified name is found.
    /// @param name The qualified name of the element.
    /// @returns @c true if a matching element is found;
    /// otherwise @c false and the XmlReader is in an end of file state.
    /// @throws ArgumentException The parameter is an empty string.
    virtual ASPOSECPP_SHARED_API bool ReadToFollowing(String name);
    /// Reads until an element with the specified local name and namespace URI is found.
    /// @param localName The local name of the element.
    /// @param namespaceURI The namespace URI of the element.
    /// @returns @c true if a matching element is found;
    /// otherwise @c false and the XmlReader is in an end of file state.
    /// @throws ArgumentNullException Both parameter values are @c nullptr.
    virtual ASPOSECPP_SHARED_API bool ReadToFollowing(String localName, String namespaceURI);
    /// Advances the XmlReader to the next descendant element with the specified qualified name.
    /// @param name The qualified name of the element you wish to move to.
    /// @returns @c true if a matching descendant element is found; otherwise @c false.
    /// If a matching child element is not found, the XmlReader is positioned on the end tag
    /// (XmlReader::get_NodeType value is XmlNodeType::EndElement) of the element.
    /// If the XmlReader is not positioned on an element when XmlReader::ReadToDescendant(String) was called,
    /// this method returns @c false and the position of the XmlReader is not changed.
    /// @throws ArgumentException The parameter is an empty string.
    virtual ASPOSECPP_SHARED_API bool ReadToDescendant(String name);
    /// Advances the XmlReader to the next descendant element with the specified local name and namespace URI.
    /// @param localName The local name of the element you wish to move to.
    /// @param namespaceURI The namespace URI of the element you wish to move to.
    /// @returns @c true if a matching descendant element is found; otherwise @c false.
    /// If a matching child element is not found, the XmlReader is positioned on the end tag
    /// (XmlReader::get_NodeType value is XmlNodeType::EndElement) of the element.
    /// If the XmlReader is not positioned on an element when XmlReader::ReadToDescendant(String,String) was called,
    /// this method returns @c false and the position of the XmlReader is not changed.
    /// @throws ArgumentNullException Both parameter values are @c nullptr.
    virtual ASPOSECPP_SHARED_API bool ReadToDescendant(String localName, String namespaceURI);
    /// Advances the XmlReader to the next sibling element with the specified qualified name.
    /// @param name The qualified name of the sibling element you wish to move to.
    /// @returns @c true if a matching sibling element is found; otherwise @c false.
    /// If a matching sibling element is not found, the XmlReader is positioned on the end tag
    /// (XmlReader::get_NodeType value is XmlNodeType::EndElement) of the parent element.
    /// @throws ArgumentException The parameter is an empty string.
    virtual ASPOSECPP_SHARED_API bool ReadToNextSibling(String name);
    /// Advances the XmlReader to the next sibling element with the specified local name and namespace URI.
    /// @param localName The local name of the sibling element you wish to move to.
    /// @param namespaceURI The namespace URI of the sibling element you wish to move to.
    /// @returns @c true if a matching sibling element is found; otherwise, @c false.
    /// If a matching sibling element is not found, the XmlReader is positioned on the end tag
    /// (XmlReader::get_NodeType value is XmlNodeType::EndElement) of the parent element.
    /// @throws ArgumentNullException Both parameter values are @c nullptr.
    virtual ASPOSECPP_SHARED_API bool ReadToNextSibling(String localName, String namespaceURI);
    /// Returns a value indicating whether the string argument is a valid XML name.
    /// @param str The name to validate.
    /// @returns @c true if the name is valid; otherwise, @c false.
    /// @throws ArgumentNullException The @p str value is @c nullptr.
    static ASPOSECPP_SHARED_API bool IsName(const String& str);
    /// Returns a value indicating whether or not the string argument is a valid XML name token.
    /// @param str The name token to validate.
    /// @returns @c true if it is a valid name token; otherwise @c false.
    /// @throws ArgumentNullException The @p str value is @c nullptr.
    static ASPOSECPP_SHARED_API bool IsNameToken(const String& str);
    /// When overridden in a derived class, reads all the content, including markup, as a string.
    /// @returns All the XML content, including markup, in the current node.
    /// If the current node has no children, an empty string is returned.
    /// If the current node is neither an element nor attribute, an empty string is returned.
    /// @throws XmlException The XML was not well-formed, or an error occurred while parsing the XML.
    virtual ASPOSECPP_SHARED_API String ReadInnerXml();
    /// When overridden in a derived class, reads the content, including markup, representing this node and all its children.
    /// @returns If the reader is positioned on an element or an attribute node, this method returns all the XML content,
    /// including markup, of the current node and all its children; otherwise, it returns an empty string.
    /// @throws XmlException The XML was not well-formed, or an error occurred while parsing the XML.
    virtual ASPOSECPP_SHARED_API String ReadOuterXml();
    /// Returns a new XmlReader instance that can be used to read the current node, and all its descendants.
    /// @returns A new XML reader instance set to ReadState::Initial.
    /// Calling the XmlReader::Read method positions the new reader on the node that was current before the call
    /// to the XmlReader::ReadSubtree method.
    /// @throws InvalidOperationException The XML reader isn't positioned on an element when this method is called.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlReader> ReadSubtree();
    /// Releases all resources used by the current instance of the XmlReader class.
    ASPOSECPP_SHARED_API void Dispose() override;
    /// Creates a new XmlReader instance with specified URI.
    /// @param inputUri The URI for the file that contains the XML data.
    /// The XmlUrlResolver class is used to convert the path to a canonical data representation.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p inputUri value is @c nullptr.
    /// @throws SecurityException The XmlReader does not have sufficient permissions to access the location of the XML data.
    /// @throws FileNotFoundException The file identified by the URI does not exist.
    /// @throws UriFormatException The URI format is not correct.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const String& inputUri);
    /// Creates a new XmlReader instance by using the specified URI and settings.
    /// @param inputUri The URI for the file containing the XML data.
    /// The XmlResolver object on the XmlReaderSettings object is used to convert the path to a canonical data representation.
    /// If XmlReaderSettings::get_XmlResolver value is @c nullptr, a new XmlUrlResolver object is used.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p inputUri value is @c nullptr.
    /// @throws FileNotFoundException The file specified by the URI cannot be found.
    /// @throws UriFormatException The URI format is not correct.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const String& inputUri, const SharedPtr<XmlReaderSettings>& settings);
    /// Creates a new XmlReader instance by using the specified URI, settings, and context information for parsing.
    /// @param inputUri The URI for the file containing the XML data.
    /// The XmlResolver object on the XmlReaderSettings object is used to convert the path to a canonical data representation.
    /// If XmlReaderSettings::get_XmlResolver value is @c nullptr, a new XmlUrlResolver object is used.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @param inputContext The context information required to parse the XML fragment.
    /// The context information can include the XmlNameTable to use, encoding, namespace scope,
    /// the current @c xml:lang and @c xml:space scope, base URI, and document type definition.
    /// This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @c inputUri value is @c nullptr.
    /// @throws SecurityException The XmlReader does not have sufficient permissions to access the location of the XML data.
    /// @throws ArgumentException The XmlReaderSettings::get_NameTable and XmlParserContext::get_NameTable both are non-nullptr values.
    /// (Only one of these @c NameTable values can be set and used).
    /// @throws FileNotFoundException The file specified by the URI cannot be found.
    /// @throws UriFormatException The URI format is not correct.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const String& inputUri, SharedPtr<XmlReaderSettings> settings, const SharedPtr<XmlParserContext>& inputContext);
    /// Creates a new XmlReader instance using the specified stream with default settings.
    /// @param input The stream that contains the XML data.
    /// The XmlReader scans the first bytes of the stream looking for a byte order mark or other sign of encoding.
    /// When encoding is determined, the encoding is used to continue reading the stream,
    /// and processing continues parsing the input as a stream of (Unicode) characters.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    /// @throws SecurityException The XmlReader does not have sufficient permissions to access the location of the XML data.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::Stream>& input);
    /// Creates a new XmlReader instance with the specified stream and settings.
    /// @param input The stream that contains the XML data.
    /// The XmlReader scans the first bytes of the stream looking for a byte order mark or other sign of encoding.
    /// When encoding is determined, the encoding is used to continue reading the stream,
    /// and processing continues parsing the input as a stream of (Unicode) characters.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::Stream>& input, const SharedPtr<XmlReaderSettings>& settings);
    /// Creates a new XmlReader instance using the specified stream, base URI, and settings.
    /// @param input The stream that contains the XML data.
    /// The XmlReader scans the first bytes of the stream looking for a byte order mark or other sign of encoding.
    /// When encoding is determined, the encoding is used to continue reading the stream,
    /// and processing continues parsing the input as a stream of (Unicode) characters.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @param baseUri The base URI for the entity or document being read. This value can be @c nullptr.
    /// **Security Note** The base URI is used to resolve the relative URI of the XML document.
    /// Do not use a base URI from an untrusted source.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::Stream>& input, SharedPtr<XmlReaderSettings> settings, const String& baseUri);
    /// Creates a new XmlReader instance using the specified stream, settings, and context information for parsing.
    /// @param input The stream that contains the XML data.
    /// The XmlReader scans the first bytes of the stream looking for a byte order mark or other sign of encoding.
    /// When encoding is determined, the encoding is used to continue reading the stream,
    /// and processing continues parsing the input as a stream of (Unicode) characters.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @param inputContext The context information required to parse the XML fragment.
    /// The context information can include the XmlNameTable to use, encoding, namespace scope,
    /// the current @c xml:lang and @c xml:space scope, base URI, and document type definition.
    /// This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::Stream>& input, SharedPtr<XmlReaderSettings> settings, const SharedPtr<XmlParserContext>& inputContext);
    /// Creates a new XmlReader instance by using the specified text reader.
    /// @param input The text reader from which to read the XML data.
    /// A text reader returns a stream of Unicode characters,
    /// so the encoding specified in the XML declaration is not used by the XML reader to decode the data stream.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::TextReader>& input);
    /// Creates a new XmlReader instance by using the specified text reader and settings.
    /// @param input The text reader from which to read the XML data.
    /// A text reader returns a stream of Unicode characters,
    /// so the encoding specified in the XML declaration isn't used by the XML reader to decode the data stream.
    /// @param settings The settings for the new XmlReader. This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::TextReader>& input, const SharedPtr<XmlReaderSettings>& settings);
    /// Creates a new XmlReader instance by using the specified text reader, settings, and base URI.
    /// @param input The text reader from which to read the XML data.
    /// A text reader returns a stream of Unicode characters,
    /// so the encoding specified in the XML declaration isn't used by the XmlReader to decode the data stream.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @param baseUri The base URI for the entity or document being read. This value can be @c nullptr.
    /// **Security Note** The base URI is used to resolve the relative URI of the XML document.
    /// Do not use a base URI from an untrusted source.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::TextReader>& input, SharedPtr<XmlReaderSettings> settings, const String& baseUri);
    /// Creates a new XmlReader instance by using the specified text reader, settings, and context information for parsing.
    /// @param input The text reader from which to read the XML data.
    /// A text reader returns a stream of Unicode characters,
    /// so the encoding specified in the XML declaration isn't used by the XML reader to decode the data stream.
    /// @param settings The settings for the new XmlReader instance. This value can be @c nullptr.
    /// @param inputContext The context information required to parse the XML fragment.
    /// The context information can include the XmlNameTable to use, encoding, namespace scope,
    /// the current @c xml:lang and @c xml:space scope, base URI, and document type definition.
    /// This value can be @c nullptr.
    /// @returns An object that is used to read the XML data in the stream.
    /// @throws ArgumentNullException The @p input value is @c nullptr.
    /// @throws ArgumentException The XmlReaderSettings::get_NameTable and XmlParserContext::get_NameTable both are non-nullptr values.
    /// (Only one of these @c NameTable values can be set and used).
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<IO::TextReader>& input, SharedPtr<XmlReaderSettings> settings, const SharedPtr<XmlParserContext>& inputContext);
    /// Creates a new XmlReader instance by using the specified XML reader and settings.
    /// @param reader The object that you want to use as the underlying XML reader.
    /// @param settings The settings for the new XmlReader instance.
    /// The conformance level of the XmlReaderSettings object must either match the conformance level of the underlying reader,
    /// or it must be set to ConformanceLevel::Auto.
    /// @returns An object that is wrapped around the specified XmlReader object.
    /// @throws ArgumentNullException The @p reader value is @c nullptr.
    /// @throws InvalidOperationException If the XmlReaderSettings object specifies a conformance level that is
    /// not consistent with conformance level of the underlying reader.
    /// The underlying XmlReader is in an ReadState::Error or ReadState::Closed state.
    static ASPOSECPP_SHARED_API SharedPtr<XmlReader> Create(const SharedPtr<XmlReader>& reader, SharedPtr<XmlReaderSettings> settings);

protected:

    /// @cond
    static const int32_t DefaultBufferSize;
    static const int32_t BiggerBufferSize;
    static const int32_t MaxStreamLengthForDefaultBufferSize;
    static const int32_t AsyncBufferSize;

    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNamespaceManager> get_NamespaceManager();
    bool get_IsDefaultInternal();
    virtual ASPOSECPP_SHARED_API SharedPtr<IDtdInfo> get_DtdInfo();
    /// @endcond

    /// Optionally releases all resources used by the current instance of the XmlReader class.
    /// @param disposing @c true to release the resources; @c false to do nothing.
    virtual ASPOSECPP_SHARED_API void Dispose(bool disposing);

    /// @cond
    static bool IsTextualNode(XmlNodeType nodeType);
    static bool CanReadContentAs(XmlNodeType nodeType);
    static bool HasValueInternal(XmlNodeType nodeType);
    void CheckElement(const String& localName, const String& namespaceURI);
    Exception CreateReadContentAsException(const String& methodName);
    Exception CreateReadElementContentAsException(const String& methodName);
    bool CanReadContentAs();
    static Exception CreateReadContentAsException(const String& methodName, XmlNodeType nodeType, const SharedPtr<IXmlLineInfo>& lineInfo);
    static Exception CreateReadElementContentAsException(const String& methodName, XmlNodeType nodeType, const SharedPtr<IXmlLineInfo>& lineInfo);
    String InternalReadContentAsString();
    static ConformanceLevel GetV1ConformanceLevel(const SharedPtr<XmlReader>& reader);
    static SharedPtr<XmlReader> CreateSqlReader(const SharedPtr<IO::Stream>& input, SharedPtr<XmlReaderSettings> settings, const SharedPtr<XmlParserContext>& inputContext);
    static int32_t CalcBufferSize(const SharedPtr<IO::Stream>& input);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlReader();

private:

    static uint32_t s_isTextualNodeBitmap;
    static uint32_t s_canReadContentAsBitmap;
    static uint32_t s_hasValueBitmap;

    void WriteNode(const SharedPtr<XmlWriter>& xtw, bool defattr);
    void WriteAttributeValue(const SharedPtr<XmlWriter>& xtw);
    SharedPtr<XmlWriter> CreateWriterForInnerOuterXml(const SharedPtr<IO::StringWriter>& sw);
    void SetNamespacesFlag(const SharedPtr<XmlTextWriter>& xtw);
    bool SkipSubtree();
    static String AddLineInfo(String message, const SharedPtr<IXmlLineInfo>& lineInfo);
    bool SetupReadElementContentAsXxx(const String& methodName);
    void FinishReadElementContentAsXxx();
    static SharedPtr<XmlTextReaderImpl> GetXmlTextReaderImpl(const SharedPtr<XmlReader>& reader);

};

} // namespace Xml
} // namespace System


