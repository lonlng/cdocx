/// @file xml/xml_text_writer.h

#pragma once

#include <xml/xml_writer.h>
#include <xml/xml_space.h>
#include <xml/xml_char_type.h>
#include <xml/write_state.h>
#include <xml/formatting.h>
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
namespace IO
{
class Stream;
class TextWriter;
} // namespace IO
namespace Text
{
class Encoding;
} // namespace Text
namespace Xml
{
class XmlTextEncoder;
class XmlTextWriterBase64Encoder;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a writer that provides a fast, non-cached, forward-only way of generating streams or files containing
/// XML data that conforms to the W3C Extensible Markup Language (XML) 1.0 and the Namespaces in XML recommendations.
/// @remarks It is recommended to use the XmlWriter class instead.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlTextWriter : public XmlWriter
{
    typedef XmlTextWriter ThisType;
    typedef XmlWriter BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlTextWriter>;

public:
    using XmlWriter::XmlWriter::WriteStartElement;

public:
    using XmlWriter::XmlWriter::WriteStartAttribute;

private:

    enum class NamespaceState
    {
        Uninitialized,
        NotDeclaredButInScope,
        DeclaredButNotWrittenOut,
        DeclaredAndWrittenOut
    };

    enum class SpecialAttr
    {
        None,
        XmlSpace,
        XmlLang,
        XmlNs
    };

    enum class State
    {
        Start,
        Prolog,
        PostDTD,
        Element,
        Attribute,
        Content,
        AttrOnly,
        Epilog,
        Error,
        Closed
    };

    enum class Token
    {
        PI,
        Doctype,
        Comment,
        CData,
        StartElement,
        EndElement,
        LongEndElement,
        StartAttribute,
        EndAttribute,
        Content,
        Base64,
        RawData,
        Whitespace,
        Empty
    };


private:

    class TagInfo : public System::Object
    {
        typedef TagInfo ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        String name;
        String prefix;
        String defaultNs;
        XmlTextWriter::NamespaceState defaultNsState;
        XmlSpace xmlSpace;
        String xmlLang;
        int32_t prevNsTop;
        int32_t prefixCount;
        bool mixed;

        void Init(int32_t nsTop);
        /// @endcond

        TagInfo();

    protected:

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override;
        #endif

        #ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to members.
        /// @param visitor Visitor to apply.
        ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "XmlTextWriter"; }
    #endif


    };

    class Namespace : public System::Object
    {
        typedef Namespace ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        String prefix;
        String ns;
        bool declared;
        int32_t prevNsIndex;

        void Set(const String& prefix, const String& ns, bool declared);
        /// @endcond

        Namespace();

    };


public:

    /// Returns the underlying stream object.
    /// @returns The stream to which the XmlTextWriter is writing or @c nullptr if the XmlTextWriter
    /// was constructed using a TextWriter that does not inherit from the StreamWriter class.
    ASPOSECPP_SHARED_API SharedPtr<IO::Stream> get_BaseStream();
    /// Returns a value indicating whether to do namespace support.
    /// @returns @c true to support namespaces; otherwise, @c false.
    /// The default is @c true.
    ASPOSECPP_SHARED_API bool get_Namespaces();
    /// Sets a value indicating whether to do namespace support.
    /// @param value The value to set.
    /// @throws InvalidOperationException You can only change this value when in the WriteState::Start state.
    ASPOSECPP_SHARED_API void set_Namespaces(bool value);
    /// Indicates how the output is formatted.
    /// @returns One of the Formatting values. The default is Formatting::None (no special formatting).
    ASPOSECPP_SHARED_API System::Xml::Formatting get_Formatting();
    /// Indicates how the output is formatted.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Formatting(System::Xml::Formatting value);
    /// Returns how many IndentChars to write for each level in the hierarchy when XmlTextWriter::set_Formatting is
    /// set to Formatting::Indented.
    /// @returns Number of @c IndentChars for each level. The default is 2.
    ASPOSECPP_SHARED_API int32_t get_Indentation();
    /// Sets how many IndentChars to write for each level in the hierarchy when XmlTextWriter::set_Formatting is
    /// set to Formatting::Indented.
    /// @param value The value to set.
    /// @throws ArgumentException Setting @p value to a negative value.
    ASPOSECPP_SHARED_API void set_Indentation(int32_t value);
    /// Returns which character to use for indenting when XmlTextWriter::set_Formatting is set to Formatting::Indented.
    /// @returns The character to use for indenting. The default is space.
    ASPOSECPP_SHARED_API char16_t get_IndentChar();
    /// Sets which character to use for indenting when XmlTextWriter::set_Formatting is set to Formatting::Indented.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IndentChar(char16_t value);
    /// Returns which character to use to quote attribute values.
    /// @returns The character to use to quote attribute values.
    /// This must be a single quote @c ' or a double quote @c ". The default is a double quote.
    ASPOSECPP_SHARED_API char16_t get_QuoteChar();
    /// Sets which character to use to quote attribute values.
    /// @param value The value to set.
    /// @throws ArgumentException Setting this value to something other than either a single or double quote.
    ASPOSECPP_SHARED_API void set_QuoteChar(char16_t value);
    /// Returns the state of the writer.
    /// @returns One of the WriteState values.
    ASPOSECPP_SHARED_API System::Xml::WriteState get_WriteState() override;
    /// Returns an XmlSpace representing the current @c xml:space scope.
    /// @returns An XmlSpace representing the current @c xml:space scope.
    ///
    /// <list type="table"><listheader><term> Value
    /// </term><description> Meaning
    /// </description></listheader><item><term> None
    /// </term><description> This is the default if no @c xml:space scope exists.
    /// </description></item><item><term> Default
    /// </term><description> The current scope is @c xml:space="default".
    /// </description></item><item><term> Preserve
    /// </term><description> The current scope is @c xml:space="preserve".
    /// </description></item></list>
    ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace() override;
    /// Returns the current @c xml:lang scope.
    /// @returns The current @c xml:lang or @c nullptr if there is no @c xml:lang in the current scope.
    ASPOSECPP_SHARED_API String get_XmlLang() override;

    /// Creates an instance of the XmlTextWriter class using the specified stream and encoding.
    /// @param w The stream to which you want to write.
    /// @param encoding The encoding to generate.
    /// If encoding is @c nullptr it writes out the stream as UTF-8
    /// and omits the encoding attribute from the @c ProcessingInstruction.
    /// @throws ArgumentException The encoding is not supported or the stream cannot be written to.
    /// @throws ArgumentNullException @p w is @c nullptr.
    ASPOSECPP_SHARED_API XmlTextWriter(const SharedPtr<IO::Stream>& w, const SharedPtr<Text::Encoding>& encoding);
    /// Creates an instance of the XmlTextWriter class using the specified file.
    /// @param filename The filename to write to.
    /// If the file exists, it truncates it and overwrites it with the new content.
    /// @param encoding The encoding to generate.
    /// If encoding is @c nullptr it writes the file out as UTF-8
    /// and omits the encoding attribute from the @c ProcessingInstruction.
    /// @throws ArgumentException The encoding is not supported;
    /// the filename is empty, contains only white space, or contains one or more invalid characters.
    /// @throws UnauthorizedAccessException Access is denied.
    /// @throws ArgumentNullException The filename is @c nullptr.
    /// @throws DirectoryNotFoundException The directory to write to is not found.
    /// @throws IOException The filename includes an incorrect or invalid syntax for file name, directory name, or volume label syntax.
    /// @throws SecurityException The caller does not have the required permission.
    ASPOSECPP_SHARED_API XmlTextWriter(const String& filename, const SharedPtr<Text::Encoding>& encoding);
    /// Creates an instance of the XmlTextWriter class using the specified TextWriter.
    /// @param w The TextWriter to write to. It is assumed that the TextWriter is already set to the correct encoding.
    ASPOSECPP_SHARED_API XmlTextWriter(const SharedPtr<IO::TextWriter>& w);

    /// Writes the XML declaration with the version "1.0".
    /// @throws InvalidOperationException This is not the first write method called after the constructor.
    ASPOSECPP_SHARED_API void WriteStartDocument() override;
    /// Writes the XML declaration with the version "1.0" and the standalone attribute.
    /// @param standalone If @c true, it writes "standalone=yes"; if @c false, it writes "standalone=no".
    /// @throws InvalidOperationException This is not the first write method called after the constructor.
    ASPOSECPP_SHARED_API void WriteStartDocument(bool standalone) override;
    /// Closes any open elements or attributes and puts the writer back in the Start state.
    /// @throws ArgumentException The XML document is invalid.
    ASPOSECPP_SHARED_API void WriteEndDocument() override;
    /// Writes the DOCTYPE declaration with the specified name and optional attributes.
    /// @param name The name of the DOCTYPE. This must be non-empty.
    /// @param pubid If non-null it also writes PUBLIC "pubid" "sysid" where @p pubid and @p sysid are replaced with the value of the given arguments.
    /// @param sysid If @p pubid is null and @p sysid is non-null it writes SYSTEM "sysid" where @p sysid is replaced with the value of this argument.
    /// @param subset If non-null it writes [subset] where subset is replaced with the value of this argument.
    /// @throws InvalidOperationException This method was called outside the prolog (after the root element).
    /// @throws ArgumentException @p name is @c nullptr or String::Empty
    /// or the value for @p name would result in invalid XML.
    ASPOSECPP_SHARED_API void WriteDocType(const String& name, const String& pubid, const String& sysid, const String& subset) override;
    /// Writes the specified start tag and associates it with the given namespace and prefix.
    /// @param prefix The namespace prefix of the element.
    /// @param localName The local name of the element.
    /// @param ns The namespace URI to associate with the element.
    /// If this namespace is already in scope and has an associated prefix then the writer automatically writes that prefix also.
    /// @throws InvalidOperationException The writer is closed.
    ASPOSECPP_SHARED_API void WriteStartElement(const String& prefix, const String& localName, const String& ns) override;
    /// Closes one element and pops the corresponding namespace scope.
    ASPOSECPP_SHARED_API void WriteEndElement() override;
    /// Closes one element and pops the corresponding namespace scope.
    ASPOSECPP_SHARED_API void WriteFullEndElement() override;
    /// Writes the start of an attribute.
    /// @param prefix @c Namespace prefix of the attribute.
    /// @param localName @c LocalName of the attribute.
    /// @param ns @c NamespaceURI of the attribute.
    /// @throws ArgumentException @p localName is either @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API void WriteStartAttribute(const String& prefix, const String& localName, const String& ns) override;
    /// Closes the previous XmlTextWriter::WriteStartAttribute call.
    ASPOSECPP_SHARED_API void WriteEndAttribute() override;
    /// Writes out a <tt><![CDATA[...]]></tt> block containing the specified text.
    /// @param text Text to place inside the CDATA block.
    /// @throws ArgumentException The text would result in a non-well formed XML document.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteCData(String text) override;
    /// Writes out a comment <tt><!--...--></tt> containing the specified text.
    /// @param text Text to place inside the comment.
    /// @throws ArgumentException The text would result in a non-well formed XML document.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteComment(String text) override;
    /// Writes out a processing instruction with a space between the name and text as follows: <tt><?name text?></tt>.
    /// @param name Name of the processing instruction.
    /// @param text Text to include in the processing instruction.
    /// @throws ArgumentException The text would result in a non-well formed XML document.
    /// @p name is either @c nullptr or String::Empty.
    ///
    /// This method is being used to create an XML declaration after XmlTextWriter::WriteStartDocument has already been called.
    ASPOSECPP_SHARED_API void WriteProcessingInstruction(String name, String text) override;
    /// Writes out an entity reference as @c &amp;name;.
    /// @param name Name of the entity reference.
    /// @throws ArgumentException The text would result in a non-well formed XML document or @p name is either @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API void WriteEntityRef(const String& name) override;
    /// Forces the generation of a character entity for the specified Unicode character value.
    /// @param ch Unicode character for which to generate a character entity.
    /// @throws ArgumentException The character is in the surrogate pair character range, @c 0xd800 - @c 0xdfff;
    /// or the text would result in a non-well formed XML document.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteCharEntity(char16_t ch) override;
    /// Writes out the given white space.
    /// @param ws The string of white space characters.
    /// @throws ArgumentException The string contains non-white space characters.
    ASPOSECPP_SHARED_API void WriteWhitespace(String ws) override;
    /// Writes the given text content.
    /// @param text Text to write.
    /// @throws ArgumentException The text string contains an invalid surrogate pair.
    ASPOSECPP_SHARED_API void WriteString(const String& text) override;
    /// Generates and writes the surrogate character entity for the surrogate character pair.
    /// @param lowChar The low surrogate. This must be a value between @c 0xDC00 and @c 0xDFFF.
    /// @param highChar The high surrogate. This must be a value between @c 0xD800 and @c 0xDBFF.
    /// @throws Exception An invalid surrogate character pair was passed.
    ASPOSECPP_SHARED_API void WriteSurrogateCharEntity(char16_t lowChar, char16_t highChar) override;
    /// Writes text one buffer at a time.
    /// @param buffer Character array containing the text to write.
    /// @param index The position in the buffer indicating the start of the text to write.
    /// @param count The number of characters to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// The buffer length minus @p index is less than @p count;
    /// the call results in surrogate pair characters being split or an invalid surrogate pair being written.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteChars(ArrayPtr<char16_t> buffer, int32_t index, int32_t count) override;
    /// Writes raw markup manually from a character buffer.
    /// @param buffer Character array containing the text to write.
    /// @param index The position within the buffer indicating the start of the text to write.
    /// @param count The number of characters to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// The buffer length minus @p index is less than @p count.
    ASPOSECPP_SHARED_API void WriteRaw(ArrayPtr<char16_t> buffer, int32_t index, int32_t count) override;
    /// Writes raw markup manually from a string.
    /// @param data String containing the text to write.
    ASPOSECPP_SHARED_API void WriteRaw(const String& data) override;
    /// Encodes the specified binary bytes as base64 and writes out the resulting text.
    /// @param buffer Byte array to encode.
    /// @param index The position within the buffer indicating the start of the bytes to write.
    /// @param count The number of bytes to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentException The buffer length minus @p index is less than @p count.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteBase64(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Encodes the specified binary bytes as binhex and writes out the resulting text.
    /// @param buffer Byte array to encode.
    /// @param index The position in the buffer indicating the start of the bytes to write.
    /// @param count The number of bytes to write.
    /// @throws ArgumentNullException @p buffer is @c nullptr.
    /// @throws ArgumentException The buffer length minus @p index is less than @p count.
    /// @throws ArgumentOutOfRangeException @p index or @p count is less than zero.
    /// @throws InvalidOperationException The XmlTextWriter::get_WriteState value is WriteState::Closed.
    ASPOSECPP_SHARED_API void WriteBinHex(ArrayPtr<uint8_t> buffer, int32_t index, int32_t count) override;
    /// Closes this stream and the underlying stream.
    ASPOSECPP_SHARED_API void Close() override;
    /// Flushes whatever is in the buffer to the underlying streams and also flushes the underlying stream.
    ASPOSECPP_SHARED_API void Flush() override;
    /// Writes out the specified name, ensuring it is a valid name according to
    /// the <a href="https://www.w3.org/TR/1998/REC-xml-19980210#NT-Name">W3C XML 1.0 recommendation</a>.
    /// @param name Name to write.
    /// @throws ArgumentException @p name is not a valid XML name; or @p name is either @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API void WriteName(const String& name) override;
    /// Writes out the namespace-qualified name. This method looks up the prefix that is in scope for the given namespace.
    /// @param localName The local name to write.
    /// @param ns The namespace URI to associate with the name.
    /// @throws ArgumentException @p localName is either @c nullptr or String::Empty.
    /// @p localName is not a valid name according to the W3C Namespaces spec.
    ASPOSECPP_SHARED_API void WriteQualifiedName(const String& localName, const String& ns) override;
    /// Returns the closest prefix defined in the current namespace scope for the namespace URI.
    /// @param ns Namespace URI whose prefix you want to find.
    /// @returns The matching prefix. Or @c nullptr if no matching namespace URI is found in the current scope.
    /// @throws ArgumentException @p ns is either @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API String LookupPrefix(String ns) override;
    /// Writes out the specified name, ensuring it is a valid @c NmToken according to
    /// the <a href="https://www.w3.org/TR/1998/REC-xml-19980210#NT-Name">W3C XML 1.0 recommendation</a>.
    /// @param name Name to write.
    /// @throws ArgumentException @p name is not a valid @c NmToken; or @p name is either @c nullptr or String::Empty.
    ASPOSECPP_SHARED_API void WriteNmToken(const String& name) override;

protected:

    /// @cond
    XmlTextWriter();
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlTextWriter, CODEPORTING_ARGS());
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlTextWriter();

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
    const char* DBG_class_name() const override { return "XmlTextWriter"; }
    #endif
    /// @endcond

private:

    SharedPtr<IO::TextWriter> _textWriter;
    SharedPtr<XmlTextEncoder> _xmlEncoder;
    SharedPtr<Text::Encoding> _encoding;
    System::Xml::Formatting _formatting;
    bool _indented;
    int32_t _indentation;
    char16_t _indentChar;
    ArrayPtr<XmlTextWriter::TagInfo> _stack;
    int32_t _top;
    ArrayPtr<XmlTextWriter::State> _stateTable;
    XmlTextWriter::State _currentState;
    XmlTextWriter::Token _lastToken;
    SharedPtr<XmlTextWriterBase64Encoder> _base64Encoder;
    char16_t _quoteChar;
    char16_t _curQuoteChar;
    bool _namespaces;
    XmlTextWriter::SpecialAttr _specialAttr;
    String _prefixForXmlNs;
    bool _flush;
    ArrayPtr<XmlTextWriter::Namespace> _nsStack;
    int32_t _nsTop;
    SharedPtr<Collections::Generic::Dictionary<String, int32_t>> _nsHashtable;
    bool _useNsHashtable;
    XmlCharType _xmlCharType;
    static const int32_t NamespaceStackInitialSize;
    static const int32_t MaxNamespacesWalkCount;
    static ArrayPtr<String> s_stateName;
    static ArrayPtr<String> s_tokenName;
    static ArrayPtr<XmlTextWriter::State> s_stateTableDefault;
    static ArrayPtr<XmlTextWriter::State> s_stateTableDocument;

    String PrepareElementPrefix(const String& prefix, const String& ns);
    String PrepareAttributePrefix(const String& prefix, const String*& localName, const String& ns);
    void StartDocument(int32_t standalone);
    void AutoComplete(XmlTextWriter::Token token);
    void AutoCompleteAll();
    void InternalWriteEndElement(bool longFormat);
    void WriteEndStartTag(bool empty);
    void WriteEndAttributeQuote();
    void Indent(bool beforeEndElement);
    void PushNamespace(const String& prefix, const String& ns, bool declared);
    void AddNamespace(const String& prefix, const String& ns, bool declared);
    void AddToNamespaceHashtable(int32_t namespaceIndex);
    void PopNamespaces(int32_t indexFrom, int32_t indexTo);
    String GeneratePrefix();
    void InternalWriteProcessingInstruction(const String& name, const String& text);
    int32_t LookupNamespace(const String& prefix);
    int32_t LookupNamespaceInCurrentScope(const String& prefix);
    String FindPrefix(const String& ns);
    void InternalWriteName(const String& name, bool isNCName);
    void ValidateName(const String& name, bool isNCName);
    void HandleSpecialAttribute();
    void VerifyPrefixXml(const String& prefix, const String& ns);
    void PushStack();
    void FlushEncoders();

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace Xml
} // namespace System


