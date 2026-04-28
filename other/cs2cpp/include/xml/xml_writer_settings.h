/// @file xml/xml_writer_settings.h

#pragma once

#include <xml/xml_output_method.h>
#include <xml/new_line_handling.h>
#include <xml/namespace_handling.h>
#include <xml/conformance_level.h>
#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
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
class DocumentXmlWriter;
class HtmlEncodedRawTextWriter;
class HtmlUtf8RawTextWriter;
class QueryOutputWriter;
class QueryOutputWriterV1;
class XmlAutoDetectWriter;
class XmlCharCheckingWriter;
class XmlEncodedRawTextWriter;
class XmlEncodedRawTextWriterIndent;
class XmlQualifiedName;
class XmlUtf8RawTextWriter;
class XmlUtf8RawTextWriterIndent;
class XmlWellFormedWriter;
class XmlWriter;
namespace Xsl
{
namespace Runtime
{
class XmlQueryDataReader;
class XmlQueryDataWriter;
} // namespace Runtime
class XslCompiledTransform;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

enum class TriState
{
    Unknown = -1,
    False = 0,
    True = 1
};

enum class XmlStandalone
{
    Omit = 0,
    Yes = 1,
    No = 2
};

/// Specifies a set of features to support on the XmlWriter object created by the XmlWriter::Create method.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlWriterSettings final : public System::Object
{
    typedef XmlWriterSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlWriterSettings>;

private:
    /// @cond
    friend class HtmlEncodedRawTextWriter;
    friend class XmlEncodedRawTextWriter;
    friend class HtmlUtf8RawTextWriter;
    friend class XmlUtf8RawTextWriter;
    friend class QueryOutputWriter;
    friend class QueryOutputWriterV1;
    friend class XmlWriter;
    friend class XmlAutoDetectWriter;
    friend class XmlCharCheckingWriter;
    friend class XmlEncodedRawTextWriterIndent;
    friend class XmlUtf8RawTextWriterIndent;
    friend class XmlWellFormedWriter;
    friend class DocumentXmlWriter;
    friend class Xsl::XslCompiledTransform;
    /// @endcond

public:

    /// Returns the type of text encoding to use.
    /// @returns The text encoding to use. The default is Encoding::get_UTF8.
    ASPOSECPP_SHARED_API SharedPtr<System::Text::Encoding> get_Encoding();
    /// Sets the type of text encoding to use.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Encoding(const SharedPtr<System::Text::Encoding>& value);
    /// Returns a value indicating whether to omit an XML declaration.
    /// @returns @c true to omit the XML declaration; otherwise, @c false.
    /// The default is @c false, an XML declaration is written.
    ASPOSECPP_SHARED_API bool get_OmitXmlDeclaration();
    /// Sets a value indicating whether to omit an XML declaration.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_OmitXmlDeclaration(bool value);
    /// Returns a value indicating whether to normalize line breaks in the output.
    /// @returns One of the NewLineHandling values. The default is NewLineHandling::Replace.
    ASPOSECPP_SHARED_API System::Xml::NewLineHandling get_NewLineHandling();
    /// Sets a value indicating whether to normalize line breaks in the output.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NewLineHandling(System::Xml::NewLineHandling value);
    /// Returns the character string to use for line breaks.
    /// @returns The character string to use for line breaks. This can be set to any string value.
    /// However, to ensure valid XML, you should specify only valid white space characters, such as space characters,
    /// tabs, carriage returns, or line feeds.
    /// The default is @c \\r\\n (carriage return, new line).
    ASPOSECPP_SHARED_API String get_NewLineChars();
    /// Sets the character string to use for line breaks.
    /// @param value The value to set.
    /// @throws ArgumentNullException The @c value is @c nullptr.
    ASPOSECPP_SHARED_API void set_NewLineChars(const String& value);
    /// Returns a value indicating whether to indent elements.
    /// @returns @c true to write individual elements on new lines and indent; otherwise, @c false.
    /// The default is @c false.
    ASPOSECPP_SHARED_API bool get_Indent();
    /// Sets a value indicating whether to indent elements.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Indent(bool value);
    /// Returns the character string to use when indenting.
    /// This setting is used when the XmlWriterSettings::set_Indent value is set to @c true.
    /// @returns The character string to use when indenting. This can be set to any string value.
    /// However, to ensure valid XML, you should specify only valid white space characters, such as space characters,
    /// tabs, carriage returns, or line feeds.
    /// The default is two spaces.
    ASPOSECPP_SHARED_API String get_IndentChars();
    /// Sets the character string to use when indenting.
    /// This setting is used when the XmlWriterSettings::set_Indent value is set to @c true.
    /// @param value The value to set.
    /// @throws ArgumentNullException The @c value is @c nullptr.
    ASPOSECPP_SHARED_API void set_IndentChars(const String& value);
    /// Returns a value indicating whether to write attributes on a new line.
    /// @returns @c true to write attributes on individual lines; otherwise, @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_NewLineOnAttributes();
    /// Sets a value indicating whether to write attributes on a new line.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NewLineOnAttributes(bool value);
    /// Returns a value indicating whether the XmlWriter should also close the underlying stream or
    /// TextWriter when the XmlWriter::Close method is called.
    /// @returns @c true to also close the underlying stream or TextWriter; otherwise, @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_CloseOutput();
    /// Sets a value indicating whether the XmlWriter should also close the underlying stream or
    /// TextWriter when the XmlWriter::Close method is called.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CloseOutput(bool value);
    /// Returns the level of conformance that the XML writer checks the XML output for.
    /// @returns One of the enumeration values that specifies the level of conformance
    /// (document, fragment, or automatic detection). The default is ConformanceLevel::Document.
    ASPOSECPP_SHARED_API System::Xml::ConformanceLevel get_ConformanceLevel();
    /// Sets the level of conformance that the XML writer checks the XML output for.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ConformanceLevel(System::Xml::ConformanceLevel value);
    /// Returns a value that indicates whether the XML writer should check to ensure that all characters in the document
    /// conform to the "2.2 Characters" section of the W3C [XML 1.0 Recommendation](https://www.w3.org/TR/REC-xml/#charsets).
    /// @returns @c true to do character checking; otherwise, @c false. The default is @c true.
    ASPOSECPP_SHARED_API bool get_CheckCharacters();
    /// Sets a value that indicates whether the XML writer should check to ensure that all characters in the document
    /// conform to the "2.2 Characters" section of the W3C [XML 1.0 Recommendation](https://www.w3.org/TR/REC-xml/#charsets).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CheckCharacters(bool value);
    /// Returns a value that indicates whether the XmlWriter should remove duplicate namespace declarations when writing XML content.
    /// The default behavior is for the writer to output all namespace declarations that are present in the writer's namespace resolver.
    /// @returns The NamespaceHandling enumeration used to specify whether to remove duplicate namespace declarations in the XmlWriter.
    ASPOSECPP_SHARED_API System::Xml::NamespaceHandling get_NamespaceHandling();
    /// Sets a value that indicates whether the XmlWriter should remove duplicate namespace declarations when writing XML content.
    /// The default behavior is for the writer to output all namespace declarations that are present in the writer's namespace resolver.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NamespaceHandling(System::Xml::NamespaceHandling value);
    /// Returns a value that indicates whether the XmlWriter will add closing tags to all unclosed element tags
    /// when the XmlWriter::Close method is called.
    /// @returns @c true if all unclosed element tags will be closed out; otherwise, @c false.
    /// The default value is @c true.
    ASPOSECPP_SHARED_API bool get_WriteEndDocumentOnClose();
    /// Sets a value that indicates whether the XmlWriter will add closing tags to all unclosed element tags
    /// when the XmlWriter::Close method is called.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_WriteEndDocumentOnClose(bool value);
    /// Returns the method used to serialize the XmlWriter output.
    /// @returns One of the XmlOutputMethod values. The default is XmlOutputMethod::Xml.
    ASPOSECPP_SHARED_API XmlOutputMethod get_OutputMethod();
    /// Returns a value that indicates whether the XmlWriter does not escape URI attributes.
    /// @returns @c true if the XmlWriter does not escape URI attributes; otherwise, @c false.
    /// The default is @c false.
    ASPOSECPP_SHARED_API bool get_DoNotEscapeUriAttributes();
    /// Sets a value that indicates whether the XmlWriter does not escape URI attributes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DoNotEscapeUriAttributes(bool value);

    /// Initializes a new instance of the XmlWriterSettings class.
    ASPOSECPP_SHARED_API XmlWriterSettings();

    /// Resets the members of the settings class to their default values.
    ASPOSECPP_SHARED_API void Reset();
    /// Creates a copy of the XmlWriterSettings instance.
    /// @returns The cloned XmlWriterSettings object.
    ASPOSECPP_SHARED_API SharedPtr<XmlWriterSettings> Clone();

protected:

    /// @cond
    ASPOSECPP_SHARED_API void set_OutputMethod(XmlOutputMethod value);
    SharedPtr<Collections::Generic::List<SharedPtr<XmlQualifiedName>>> get_CDataSectionElements();
    bool get_MergeCDataSections();
    void set_MergeCDataSections(bool value);
    String get_MediaType();
    void set_MediaType(const String& value);
    String get_DocTypeSystem();
    void set_DocTypeSystem(const String& value);
    String get_DocTypePublic();
    void set_DocTypePublic(const String& value);
    XmlStandalone get_Standalone();
    void set_Standalone(XmlStandalone value);
    bool get_AutoXmlDeclaration();
    void set_AutoXmlDeclaration(bool value);
    TriState get_IndentInternal();
    void set_IndentInternal(TriState value);
    bool get_IsQuerySpecific();
    bool get_ReadOnly();
    void set_ReadOnly(bool value);

    SharedPtr<XmlWriter> CreateWriter(const String& outputFileName);
    SharedPtr<XmlWriter> CreateWriter(const SharedPtr<IO::Stream>& output);
    SharedPtr<XmlWriter> CreateWriter(const SharedPtr<IO::TextWriter>& output);
    SharedPtr<XmlWriter> CreateWriter(const SharedPtr<XmlWriter>& output);
    void GetObjectData(const SharedPtr<Xsl::Runtime::XmlQueryDataWriter>& writer);

    XmlWriterSettings(const SharedPtr<Xsl::Runtime::XmlQueryDataReader>& reader);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlWriterSettings, CODEPORTING_ARGS(SharedPtr<Xsl::Runtime::XmlQueryDataReader> reader));
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlWriterSettings();

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
    const char* DBG_class_name() const override { return "XmlWriterSettings"; }
    #endif
    /// @endcond

private:

    SharedPtr<System::Text::Encoding> _encoding;
    bool _omitXmlDecl;
    System::Xml::NewLineHandling _newLineHandling;
    String _newLineChars;
    TriState _indent;
    String _indentChars;
    bool _newLineOnAttributes;
    bool _closeOutput;
    System::Xml::NamespaceHandling _namespaceHandling;
    System::Xml::ConformanceLevel _conformanceLevel;
    bool _checkCharacters;
    bool _writeEndDocumentOnClose;
    XmlOutputMethod _outputMethod;
    SharedPtr<Collections::Generic::List<SharedPtr<XmlQualifiedName>>> _cdataSections;
    bool _doNotEscapeUriAttributes;
    bool _mergeCDataSections;
    String _mediaType;
    String _docTypeSystem;
    String _docTypePublic;
    XmlStandalone _standalone;
    bool _autoXmlDecl;
    bool _isReadOnly;

    void CheckReadOnly(const String& propertyName);
    void Initialize();
    SharedPtr<XmlWriter> AddConformanceWrapper(const SharedPtr<XmlWriter>& baseWriter);

};

} // namespace Xml
} // namespace System

template<>
struct EnumMetaInfo<System::Xml::TriState>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::TriState, const char_t*>, 3>& values();
};
template<>
struct EnumMetaInfo<System::Xml::XmlStandalone>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlStandalone, const char_t*>, 3>& values();
};



