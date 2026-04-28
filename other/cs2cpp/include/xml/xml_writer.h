/// @file xml/xml_writer.h

#pragma once

#include <xml/xml_space.h>
#include <xml/write_state.h>
#include <system/idisposable.h>
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
class TextWriter;
} // namespace IO
namespace Text
{
class StringBuilder;
} // namespace Text
namespace Xml
{
class XmlReader;
class XmlWriterSettings;
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a writer that provides a fast, non-cached, forward-only way to generate streams or files that contain XML data.
class ASPOSECPP_SHARED_CLASS XmlWriter : public IDisposable
{
    typedef XmlWriter ThisType;
    typedef IDisposable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlWriter>;

public:

    /// Returns the XmlWriterSettings object used to create this XmlWriter instance.
    /// @returns The XmlWriterSettings object used to create this writer instance.
    /// If this writer was not created using the XmlWriter::Create method, this method returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlWriterSettings> get_Settings();
    /// When overridden in a derived class, gets the state of the writer.
    /// @returns One of the WriteState values.
    virtual ASPOSECPP_SHARED_API System::Xml::WriteState get_WriteState() = 0;
    /// When overridden in a derived class, gets an XmlSpace representing the current @c xml:space scope.
    /// @returns An XmlSpace representing the current @c xml:space scope.
    ///
    /// <list type="table"><listheader><term> Value
    /// </term><description> Meaning
    /// </description></listheader><item><term>@c None</term><description> This is the default if no @c xml:space scope exists.
    /// </description></item><item><term>@c Default</term><description> The current scope is @c xml:space="default".
    /// </description></item><item><term>@c Preserve</term><description> The current scope is @c xml:space="preserve".
    /// </description></item></list>
    virtual ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace();
    /// When overridden in a derived class, gets the current @c xml:lang scope.
    /// @returns The current @c xml:lang scope.
    virtual ASPOSECPP_SHARED_API String get_XmlLang();

    /// When overridden in a derived class, writes the XML declaration with the version "1.0".
    /// @throws InvalidOperationException This is not the first write method called after the constructor.
    virtual ASPOSECPP_SHARED_API void WriteStartDocument() = 0;
    /// When overridden in a derived class, writes the XML declaration with the version "1.0" and the standalone attribute.
    /// @param standalone If @c true, it writes "standalone=yes"; if @c false, it writes "standalone=no".
    /// @throws InvalidOperationException This is not the first write method called after the constructor.
    virtual ASPOSECPP_SHARED_API void WriteStartDocument(bool standalone) = 0;
    /// When overridden in a derived class, closes any open elements or attributes and puts the writer back in the Start state.
    /// @throws ArgumentException The XML document is invalid.
    virtual ASPOSECPP_SHARED_API void WriteEndDocument() = 0;
    /// When overridden in a derived class, writes the DOCTYPE declaration with the specified name and optional attributes.
    /// @param name The name of the DOCTYPE. This must be non-empty.
    /// @param pubid If non-null it also writes PUBLIC "pubid" "sysid" where @p pubid and @p sysid are replaced with the value of the given arguments.
    /// @param sysid If @p pubid is @c nullptr and @p sysid is non-null it writes SYSTEM "sysid" where @p sysid is replaced with the value of this argument.
    /// @param subset If non-null it writes [subset] where subset is replaced with the value of this argument.
    /// @throws InvalidOperationException This method was called outside the prolog (after the root element).
    /// @throws ArgumentException The value for @p name would result in invalid XML.
    virtual ASPOSECPP_SHARED_API void WriteDocType(const String& name, const String& pubid, const String& sysid, const String& subset) = 0;
    /// When overridden in a derived class, writes the specified start tag and associates it with the given namespace.
    /// @param localName The local name of the element.
    /// @param ns The namespace URI to associate with the element.
    /// If this namespace is already in scope and has an associated prefix, the writer automatically writes that prefix also.
    /// @throws InvalidOperationException The writer is closed.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteStartElement(const String& localName, const String& ns);
    /// When overridden in a derived class, writes the specified start tag and associates it with the given namespace and prefix.
    /// @param prefix The namespace prefix of the element.
    /// @param localName The local name of the element.
    /// @param ns The namespace URI to associate with the element.
    /// @throws InvalidOperationException The writer is closed.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    virtual ASPOSECPP_SHARED_API void WriteStartElement(const String& prefix, const String& localName, const String& ns) = 0;
    /// When overridden in a derived class, writes out a start tag with the specified local name.
    /// @param localName The local name of the element.
    /// @throws InvalidOperationException The writer is closed.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteStartElement(const String& localName);
    /// When overridden in a derived class, closes one element and pops the corresponding namespace scope.
    /// @throws InvalidOperationException This results in an invalid XML document.
    virtual ASPOSECPP_SHARED_API void WriteEndElement() = 0;
    /// When overridden in a derived class, closes one element and pops the corresponding namespace scope.
    virtual ASPOSECPP_SHARED_API void WriteFullEndElement() = 0;
    /// When overridden in a derived class, writes an attribute with the specified local name, namespace URI, and value.
    /// @param localName The local name of the attribute.
    /// @param ns The namespace URI to associate with the attribute.
    /// @param value The value of the attribute.
    /// @throws InvalidOperationException The state of writer is not WriteState::Element or writer is closed.
    /// @throws ArgumentException The @c xml:space or @c xml:lang attribute value is invalid.
    ASPOSECPP_SHARED_API void WriteAttributeString(const String& localName, const String& ns, const String& value);
    /// When overridden in a derived class, writes out the attribute with the specified local name and value.
    /// @param localName The local name of the attribute.
    /// @param value The value of the attribute.
    /// @throws InvalidOperationException The state of writer is not WriteState::Element or writer is closed.
    /// @throws ArgumentException The @c xml:space or @c xml:lang attribute value is invalid.
    ASPOSECPP_SHARED_API void WriteAttributeString(const String& localName, const String& value);
    /// When overridden in a derived class, writes out the attribute with the specified prefix, local name, namespace URI, and value.
    /// @param prefix The namespace prefix of the attribute.
    /// @param localName The local name of the attribute.
    /// @param ns The namespace URI of the attribute.
    /// @param value The value of the attribute.
    /// @throws InvalidOperationException The state of writer is not WriteState::Element or writer is closed.
    /// @throws ArgumentException The @c xml:space or @c xml:lang attribute value is invalid.
    /// @throws XmlException The @p localName or @p ns is @c nullptr.
    ASPOSECPP_SHARED_API void WriteAttributeString(const String& prefix, const String& localName, const String& ns, const String& value);
    /// Writes the start of an attribute with the specified local name and namespace URI.
    /// @param localName The local name of the attribute.
    /// @param ns The namespace URI of the attribute.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteStartAttribute(const String& localName, const String& ns);
    /// When overridden in a derived class, writes the start of an attribute with the specified prefix, local name, and namespace URI.
    /// @param prefix The namespace prefix of the attribute.
    /// @param localName The local name of the attribute.
    /// @param ns The namespace URI for the attribute.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    virtual ASPOSECPP_SHARED_API void WriteStartAttribute(const String& prefix, const String& localName, const String& ns) = 0;
    /// Writes the start of an attribute with the specified local name.
    /// @param localName The local name of the attribute.
    /// @throws InvalidOperationException The writer is closed.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteStartAttribute(const String& localName);
    /// When overridden in a derived class, closes the previous XmlWriter::WriteStartAttribute(String,String) call.
    virtual ASPOSECPP_SHARED_API void WriteEndAttribute() = 0;
    /// When overridden in a derived class, writes out a <tt><![CDATA[...]]></tt> block containing the specified text.
    /// @param text The text to place inside the CDATA block.
    /// @throws ArgumentException The text would result in a non-well formed XML document.
    virtual ASPOSECPP_SHARED_API void WriteCData(String text) = 0;
    /// When overridden in a derived class, writes out a comment <tt><!--...--></tt> containing the specified text.
    /// @param text Text to place inside the comment.
    /// @throws ArgumentException The text would result in a non-well-formed XML document.
    virtual ASPOSECPP_SHARED_API void WriteComment(String text) = 0;
    /// When overridden in a derived class, writes out a processing instruction with a space between the name and text as follows: <tt><?name text?></tt>.
    /// @param name The name of the processing instruction.
    /// @param text The text to include in the processing instruction.
    /// @throws ArgumentException The text would result in a non-well formed XML document.
    /// @p name is either @c nullptr or String::Empty.
    ///
    /// This method is being used to create an XML declaration after XmlWriter::WriteStartDocument has already been called.
    virtual ASPOSECPP_SHARED_API void WriteProcessingInstruction(String name, String text) = 0;
    /// When overridden in a derived class, writes out an entity reference as @c &amp;name;.
    /// @param name The name of the entity reference.
    /// @throws ArgumentException @p name is either @c nullptr or String::Empty.
    virtual ASPOSECPP_SHARED_API void WriteEntityRef(const String& name) = 0;
    /// When overridden in a derived class, forces the generation of a character entity for the specified Unicode character value.
    /// @param ch The Unicode character for which to generate a character entity.
    /// @throws ArgumentException The character is in the surrogate pair character range, @c 0xd800 - @c 0xdfff.
    virtual ASPOSECPP_SHARED_API void WriteCharEntity(char16_t ch) = 0;
    /// When overridden in a derived class, writes out the given white space.
    /// @param ws The string of white space characters.
    /// @throws ArgumentException The string contains non-white space characters.
    virtual ASPOSECPP_SHARED_API void WriteWhitespace(String ws) = 0;
    /// When overridden in a derived class, writes the given text content.
    /// @param text The text to write.
    /// @throws ArgumentException The text string contains an invalid surrogate pair.
    virtual ASPOSECPP_SHARED_API void WriteString(const String& text) = 0;
    /// When overridden in a derived class, generates and writes the surrogate character entity for the surrogate character pair.
    /// @param lowChar The low surrogate. This must be a value between 0xDC00 and 0xDFFF.
    /// @param highChar The high surrogate. This must be a value between 0xD800 and 0xDBFF.
    /// @throws ArgumentException An invalid surrogate character pair was passed.
    virtual ASPOSECPP_SHARED_API void WriteSurrogateCharEntity(char16_t lowChar, char16_t highChar) = 0;
    /// When overridden in a derived class, writes text one buffer at a time.
    /// @param buffer Character array containing the text to write.
    /// @param index The position in the buffer indicating the start of the text to write.
    /// @param count The number of characters to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// or
    /// The buffer length minus @p index is less than @p count;
    /// the call results in surrogate pair characters being split or an invalid surrogate pair being written.
    /// @throws ArgumentException The @p buffer parameter value is not valid.
    virtual ASPOSECPP_SHARED_API void WriteChars(ArrayPtr<char16_t> buffer, int32_t index, int32_t count) = 0;
    /// When overridden in a derived class, writes raw markup manually from a character buffer.
    /// @param buffer Character array containing the text to write.
    /// @param index The position within the buffer indicating the start of the text to write.
    /// @param count The number of characters to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// or
    /// The buffer length minus @p index is less than @p count.
    virtual ASPOSECPP_SHARED_API void WriteRaw(ArrayPtr<char16_t> buffer, int32_t index, int32_t count) = 0;
    /// When overridden in a derived class, writes raw markup manually from a string.
    /// @param data String containing the text to write.
    /// @throws ArgumentException @p data is either @c nullptr or String::Empty.
    virtual ASPOSECPP_SHARED_API void WriteRaw(const String& data) = 0;
    /// When overridden in a derived class, encodes the specified binary bytes as Base64 and writes out the resulting text.
    /// @param buffer Byte array to encode.
    /// @param index The position in the buffer indicating the start of the bytes to write.
    /// @param count The number of bytes to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// or
    /// The buffer length minus @p index is less than @p count.
    virtual ASPOSECPP_SHARED_API void WriteBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) = 0;
    /// When overridden in a derived class, encodes the specified binary bytes as @c BinHex and writes out the resulting text.
    /// @param buffer Byte array to encode.
    /// @param index The position in the buffer indicating the start of the bytes to write.
    /// @param count The number of bytes to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws InvalidOperationException The writer is closed or in error state.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// or
    /// The buffer length minus @p index is less than @p count.
    virtual ASPOSECPP_SHARED_API void WriteBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count);
    /// When overridden in a derived class, closes this stream and the underlying stream.
    /// @throws InvalidOperationException A call is made to write more output after @c Close has been called or
    /// the result of this call is an invalid XML document.
    virtual ASPOSECPP_SHARED_API void Close();
    /// When overridden in a derived class, flushes whatever is in the buffer to the underlying streams and
    /// also flushes the underlying stream.
    virtual ASPOSECPP_SHARED_API void Flush() = 0;
    /// When overridden in a derived class, returns the closest prefix defined in the current namespace scope for the namespace URI.
    /// @param ns The namespace URI whose prefix you want to find.
    /// @returns The matching prefix or @c nullptr if no matching namespace URI is found in the current scope.
    /// @throws ArgumentException @p ns is either @c nullptr or String::Empty.
    virtual ASPOSECPP_SHARED_API String LookupPrefix(String ns) = 0;
    /// When overridden in a derived class, writes out the specified name, ensuring it is a valid NmToken according to
    /// the W3C XML 1.0 recommendation (https://www.w3.org/TR/1998/REC-xml-19980210#NT-Name).
    /// @param name The name to write.
    /// @throws ArgumentException @p name is not a valid NmToken; or @p name is either @c nullptr or String::Empty.
    virtual ASPOSECPP_SHARED_API void WriteNmToken(const String& name);
    /// When overridden in a derived class, writes out the specified name, ensuring it is a valid name according to
    /// the W3C XML 1.0 recommendation (https://www.w3.org/TR/1998/REC-xml-19980210#NT-Name).
    /// @param name The name to write.
    /// @throws ArgumentException @p name is not a valid XML name; or @p name is either @c nullptr or String::Empty.
    virtual ASPOSECPP_SHARED_API void WriteName(const String& name);
    /// When overridden in a derived class, writes out the namespace-qualified name.
    /// This method looks up the prefix that is in scope for the given namespace.
    /// @param localName The local name to write.
    /// @param ns The namespace URI for the name.
    /// @throws ArgumentException @p localName is either @c nullptr or String::Empty.
    /// @p localName is not a valid name.
    virtual ASPOSECPP_SHARED_API void WriteQualifiedName(const String& localName, const String& ns);
    /// Writes the object value.
    /// @param value The object value to write.
    /// @throws ArgumentException An invalid value was specified.
    /// @throws ArgumentNullException The @p value is @c nullptr.
    /// @throws InvalidOperationException The writer is closed or in error state.
    virtual ASPOSECPP_SHARED_API void WriteValue(SharedPtr<Object> value);
    /// Writes a String value.
    /// @param value The String value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(const String& value);
    /// Writes a Boolean value.
    /// @param value The Boolean value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(bool value);
    /// Writes a DateTime value.
    /// @param value The DateTime value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(DateTime value);
    /// Writes a DateTimeOffset value.
    /// @param value The DateTimeOffset value to write.
    virtual ASPOSECPP_SHARED_API void WriteValue(DateTimeOffset value);
    /// Writes a Double value.
    /// @param value The Double value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(double value);
    /// Writes a single-precision floating-point number.
    /// @param value The single-precision floating-point number to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(float value);
    /// Writes a Decimal value.
    /// @param value The Decimal value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(Decimal value);
    /// Writes a Int32 value.
    /// @param value The Int32 value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(int32_t value);
    /// Writes a Int64 value.
    /// @param value The Int64 value to write.
    /// @throws ArgumentException An invalid value was specified.
    virtual ASPOSECPP_SHARED_API void WriteValue(int64_t value);
    /// When overridden in a derived class, writes out all the attributes found at the current position in the XmlReader.
    /// @param reader The XmlReader from which to copy the attributes.
    /// @param defattr @c true to copy the default attributes from the XmlReader; otherwise, @c false.
    /// @throws ArgumentNullException @p reader is @c nullptr.
    /// @throws XmlException The reader is not positioned on an @c element, @c attribute or XmlDeclaration node.
    virtual ASPOSECPP_SHARED_API void WriteAttributes(SharedPtr<XmlReader> reader, bool defattr);
    /// When overridden in a derived class, copies everything from the reader to the writer and moves the reader to the start of the next sibling.
    /// @param reader The XmlReader to read from.
    /// @param defattr @c true to copy the default attributes from the XmlReader; otherwise, @c false.
    /// @throws ArgumentNullException @p reader is @c nullptr.
    /// @throws ArgumentException @p reader contains invalid characters.
    virtual ASPOSECPP_SHARED_API void WriteNode(SharedPtr<XmlReader> reader, bool defattr);
    /// Copies everything from the XPathNavigator object to the writer. The position of the XPathNavigator remains unchanged.
    /// @param navigator The XPathNavigator to copy from.
    /// @param defattr @c true to copy the default attributes; otherwise, @c false.
    /// @throws ArgumentNullException @p navigator is @c nullptr.
    virtual ASPOSECPP_SHARED_API void WriteNode(SharedPtr<XPath::XPathNavigator> navigator, bool defattr);
    /// Writes an element with the specified local name and value.
    /// @param localName The local name of the element.
    /// @param value The value of the element.
    /// @throws ArgumentException The @p localName value is @c nullptr or an empty string.
    /// or
    /// The parameter values are not valid.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteElementString(const String& localName, const String& value);
    /// Writes an element with the specified local name, namespace URI, and value.
    /// @param localName The local name of the element.
    /// @param ns The namespace URI to associate with the element.
    /// @param value The value of the element.
    /// @throws ArgumentException The @p localName value is @c nullptr or an empty string.
    /// or
    /// The parameter values are not valid.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteElementString(const String& localName, const String& ns, const String& value);
    /// Writes an element with the specified prefix, local name, namespace URI, and value.
    /// @param prefix The prefix of the element.
    /// @param localName The local name of the element.
    /// @param ns The namespace URI of the element.
    /// @param value The value of the element.
    /// @throws ArgumentException The @p localName value is @c nullptr or an empty string.
    /// or
    /// The parameter values are not valid.
    /// @throws EncoderFallbackException There is a character in the buffer that is a valid XML character but is not valid for the output encoding.
    /// For example, if the output encoding is ASCII, you should only use characters from the range of 0 to 127 for element and attribute names.
    /// The invalid character might be in the argument of this method or in an argument of previous methods that were writing to the buffer.
    /// Such characters are escaped by character entity references when possible (for example, in text nodes or attribute values).
    /// However, the character entity reference is not allowed in element and attribute names, comments, processing instructions, or CDATA sections.
    ASPOSECPP_SHARED_API void WriteElementString(const String& prefix, const String& localName, const String& ns, const String& value);
    /// Releases all resources used by the current instance of the XmlWriter class.
    ASPOSECPP_SHARED_API void Dispose() override;
    /// Creates a new XmlWriter instance using the specified filename.
    /// @param outputFileName The file to which you want to write.
    /// The XmlWriter creates a file at the specified path and writes to it in XML 1.0 text syntax.
    /// The @p outputFileName must be a file system path.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p url value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const String& outputFileName);
    /// Creates a new XmlWriter instance using the filename and XmlWriterSettings object.
    /// @param outputFileName The file to which you want to write.
    /// The XmlWriter creates a file at the specified path and writes to it in XML 1.0 text syntax.
    /// The @p outputFileName must be a file system path.
    /// @param settings The XmlWriterSettings object used to configure the new XmlWriter instance.
    /// If this is @c nullptr, a XmlWriterSettings with default settings is used.
    /// If the XmlWriter is being used with the XslCompiledTransform:Transform(String,SharedPtr<XmlWriter>) method,
    /// you should use the XslCompiledTransform::get_OutputSettings value to obtain an XmlWriterSettings object with the correct settings.
    /// This ensures that the created XmlWriter object has the correct output settings.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p url value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const String& outputFileName, SharedPtr<XmlWriterSettings> settings);
    /// Creates a new XmlWriter instance using the specified stream.
    /// @param output The stream to which you want to write.
    /// The XmlWriter writes XML 1.0 text syntax and appends it to the specified stream.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p stream value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<IO::Stream>& output);
    /// Creates a new XmlWriter instance using the stream and XmlWriterSettings object.
    /// @param output The stream to which you want to write.
    /// The XmlWriter writes XML 1.0 text syntax and appends it to the specified stream.
    /// @param settings The XmlWriterSettings object used to configure the new XmlWriter instance.
    /// If this is @c nullptr, a XmlWriterSettings with default settings is used.
    /// If the XmlWriter is being used with the XslCompiledTransform:Transform(String,SharedPtr<XmlWriter>) method,
    /// you should use the XslCompiledTransform::get_OutputSettings value to obtain an XmlWriterSettings object with the correct settings.
    /// This ensures that the created XmlWriter object has the correct output settings.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p stream value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<IO::Stream>& output, SharedPtr<XmlWriterSettings> settings);
    /// Creates a new XmlWriter instance using the specified TextWriter.
    /// @param output The TextWriter to which you want to write.
    /// The XmlWriter writes XML 1.0 text syntax and appends it to the specified TextWriter.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p text value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<IO::TextWriter>& output);
    /// Creates a new XmlWriter instance using the TextWriter and XmlWriterSettings objects.
    /// @param output The TextWriter to which you want to write.
    /// The XmlWriter writes XML 1.0 text syntax and appends it to the specified TextWriter.
    /// @param settings The XmlWriterSettings object used to configure the new XmlWriter instance.
    /// If this is @c nullptr, a XmlWriterSettings with default settings is used.
    /// If the XmlWriter is being used with the XslCompiledTransform:Transform(String,SharedPtr<XmlWriter>) method,
    /// you should use the XslCompiledTransform::get_OutputSettings value to obtain an XmlWriterSettings object with the correct settings.
    /// This ensures that the created XmlWriter object has the correct output settings.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p text value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<IO::TextWriter>& output, SharedPtr<XmlWriterSettings> settings);
    /// Creates a new XmlWriter instance using the specified Text::StringBuilder.
    /// @param output The Text::StringBuilder to which to write to.
    /// Content written by the XmlWriter is appended to the Text::StringBuilder.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p builder value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<Text::StringBuilder>& output);
    /// Creates a new XmlWriter instance using the Text::StringBuilder and XmlWriterSettings objects.
    /// @param output The Text::StringBuilder to which to write to.
    /// Content written by the XmlWriter is appended to the Text::StringBuilder.
    /// @param settings The XmlWriterSettings object used to configure the new XmlWriter instance.
    /// If this is @c nullptr, a XmlWriterSettings with default settings is used.
    /// If the XmlWriter is being used with the XslCompiledTransform:Transform(String,SharedPtr<XmlWriter>) method,
    /// you should use the XslCompiledTransform::get_OutputSettings value to obtain an XmlWriterSettings object with the correct settings.
    /// This ensures that the created XmlWriter object has the correct output settings.
    /// @returns An XmlWriter object.
    /// @throws ArgumentNullException The @p builder value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<Text::StringBuilder>& output, SharedPtr<XmlWriterSettings> settings);
    /// Creates a new XmlWriter instance using the specified XmlWriter object.
    /// @param output The XmlWriter object that you want to use as the underlying writer.
    /// @returns An XmlWriter object that is wrapped around the specified XmlWriter object.
    /// @throws ArgumentNullException The @p writer value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<XmlWriter>& output);
    /// Creates a new XmlWriter instance using the specified XmlWriter and XmlWriterSettings objects.
    /// @param output The XmlWriter object that you want to use as the underlying writer.
    /// @param settings The XmlWriterSettings object used to configure the new XmlWriter instance.
    /// If this is @c nullptr, a XmlWriterSettings with default settings is used.
    /// If the XmlWriter is being used with the XslCompiledTransform:Transform(String,SharedPtr<XmlWriter>) method,
    /// you should use the XslCompiledTransform::get_OutputSettings value to obtain an XmlWriterSettings object with the correct settings.
    /// This ensures that the created XmlWriter object has the correct output settings.
    /// @returns An XmlWriter object that is wrapped around the specified XmlWriter object.
    /// @throws ArgumentNullException The @p writer value is @c nullptr.
    static ASPOSECPP_SHARED_API SharedPtr<XmlWriter> Create(const SharedPtr<XmlWriter>& output, SharedPtr<XmlWriterSettings> settings);

protected:

    /// Optionally releases all resources used by the current instance of the XmlWriter class.
    /// @param disposing @c true to release the resources; @c false to do nothing.
    virtual ASPOSECPP_SHARED_API void Dispose(bool disposing);

    virtual ASPOSECPP_SHARED_API ~XmlWriter();

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
    const char* DBG_class_name() const override { return "XmlWriter"; }
    #endif
    /// @endcond

private:

    ArrayPtr<char16_t> _writeNodeBuffer;
    static const int32_t WriteNodeBufferSize;

    void WriteLocalNamespaces(const SharedPtr<XPath::XPathNavigator>& nsNav);

};

} // namespace Xml
} // namespace System


