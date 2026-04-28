/// @file xml/xml_reader_settings.h

#pragma once

#include <xml/validation_type.h>
#include <xml/schema/xml_schema_validation_flags.h>
#include <xml/schema/validation_event_handler.h>
#include <xml/dtd_processing.h>
#include <xml/conformance_level.h>
#include <system/object.h>
#include <system/enum_helpers.h>
#include <cstdint>


/// @cond
namespace System
{
namespace IO
{
class Stream;
class TextReader;
} // namespace IO
class String;
class Uri;
namespace Xml
{
namespace Schema
{
class XmlSchemaSet;
} // namespace Schema
class XmlCharCheckingReader;
class XmlNameTable;
class XmlParserContext;
class XmlReader;
class XmlResolver;
class XmlSqlBinaryReader;
class XmlTextReaderImpl;
class XmlValidatingReaderImpl;
namespace XPath
{
class XPathNavigatorReader;
} // namespace XPath
class XsdValidatingReader;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Specifies a set of features to support on the XmlReader object created by the XmlReader::Create method.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlReaderSettings final : public System::Object
{
    typedef XmlReaderSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlReaderSettings>;

private:
    /// @cond
    friend class XmlSqlBinaryReader;
    friend class XmlReader;
    friend class XmlCharCheckingReader;
    friend class XmlTextReaderImpl;
    friend class XmlValidatingReaderImpl;
    friend class XsdValidatingReader;
    friend class Schema::XmlSchemaSet;
    friend class XPath::XPathNavigatorReader;
    /// @endcond

public:

    /// Returns the XmlNameTable used for atomized string comparisons.
    /// @returns The XmlNameTable that stores all the atomized strings used by
    /// all XmlReader instances created using this XmlReaderSettings object.
    /// The default is @c nullptr.
    /// The created XmlReader instance will use a new empty NameTable if this value is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();
    /// Sets the XmlNameTable used for atomized string comparisons.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NameTable(const SharedPtr<XmlNameTable>& value);
    /// Sets the XmlResolver used to access external documents.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);
    /// Returns line number offset of the XmlReader object.
    /// @returns The line number offset. The default is 0.
    ASPOSECPP_SHARED_API int32_t get_LineNumberOffset();
    /// Sets line number offset of the XmlReader object.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_LineNumberOffset(int32_t value);
    /// Returns line position offset of the XmlReader object.
    /// @returns The line position offset. The default is 0.
    ASPOSECPP_SHARED_API int32_t get_LinePositionOffset();
    /// Sets line position offset of the XmlReader object.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_LinePositionOffset(int32_t value);
    /// Returns the level of conformance which the XmlReader will comply.
    /// @returns One of the enumeration values that specifies the level of conformance that the XML reader will enforce.
    /// The default is ConformanceLevel::Document.
    ASPOSECPP_SHARED_API System::Xml::ConformanceLevel get_ConformanceLevel();
    /// Sets the level of conformance which the XmlReader will comply.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ConformanceLevel(System::Xml::ConformanceLevel value);
    /// Returns a value indicating whether to do character checking.
    /// @returns @c true to do character checking; otherwise @c false. The default is @c true.
    ASPOSECPP_SHARED_API bool get_CheckCharacters();
    /// Sets a value indicating whether to do character checking.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CheckCharacters(bool value);
    /// Returns a value indicating the maximum allowable number of characters in an XML document.
    /// A zero (0) value means no limits on the size of the XML document.
    /// A non-zero value specifies the maximum size, in characters.
    /// @returns The maximum allowable number of characters in an XML document. The default is 0.
    ASPOSECPP_SHARED_API int64_t get_MaxCharactersInDocument();
    /// Sets a value indicating the maximum allowable number of characters in an XML document.
    /// A zero (0) value means no limits on the size of the XML document.
    /// A non-zero value specifies the maximum size, in characters.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MaxCharactersInDocument(int64_t value);
    /// Returns a value indicating the maximum allowable number of characters in a document that result from expanding entities.
    /// @returns The maximum allowable number of characters from expanded entities. The default is 0.
    ASPOSECPP_SHARED_API int64_t get_MaxCharactersFromEntities();
    /// Sets a value indicating the maximum allowable number of characters in a document that result from expanding entities.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MaxCharactersFromEntities(int64_t value);
    /// Returns a value indicating whether to ignore insignificant white space.
    /// @returns @c true to ignore white space; otherwise @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_IgnoreWhitespace();
    /// Sets a value indicating whether to ignore insignificant white space.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IgnoreWhitespace(bool value);
    /// Returns a value indicating whether to ignore processing instructions.
    /// @returns @c true to ignore processing instructions; otherwise @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_IgnoreProcessingInstructions();
    /// Sets a value indicating whether to ignore processing instructions.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IgnoreProcessingInstructions(bool value);
    /// Returns a value indicating whether to ignore comments.
    /// @returns @c true to ignore comments; otherwise @c false. The default is @c false.
    ASPOSECPP_SHARED_API bool get_IgnoreComments();
    /// Sets a value indicating whether to ignore comments.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IgnoreComments(bool value);
    /// Returns a value indicating whether to prohibit document type definition (DTD) processing.
    /// @deprecated This method is obsolete. Use XmlTextReader::get_DtdProcessing instead.
    /// @returns @c true to prohibit DTD processing; otherwise @c false. The default is @c true.
    ASPOSECPP_SHARED_API bool get_ProhibitDtd();
    /// Sets a value indicating whether to prohibit document type definition (DTD) processing.
    /// @deprecated This method is obsolete. Use XmlTextReader::set_DtdProcessing instead.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ProhibitDtd(bool value);
    /// Returns a value that determines the processing of DTDs.
    /// @returns One of the enumeration values that determines the processing of DTDs.
    /// The default is DtdProcessing::Prohibit.
    ASPOSECPP_SHARED_API System::Xml::DtdProcessing get_DtdProcessing();
    /// Sets a value that determines the processing of DTDs.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DtdProcessing(System::Xml::DtdProcessing value);
    /// Returns a value indicating whether the underlying stream or TextReader should be closed when the reader is closed.
    /// @returns @c true to close the underlying stream or TextReader when the reader is closed; otherwise @c false.
    /// The default is @c false.
    ASPOSECPP_SHARED_API bool get_CloseInput();
    /// Sets a value indicating whether the underlying stream or TextReader should be closed when the reader is closed.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CloseInput(bool value);
    /// Returns a value indicating whether the XmlReader will perform validation or type assignment when reading.
    /// @returns One of the ValidationType values that indicates whether XmlReader will perform validation or
    /// type assignment when reading.
    /// The default is ValidationType::None.
    ASPOSECPP_SHARED_API System::Xml::ValidationType get_ValidationType();
    /// Sets a value indicating whether the XmlReader will perform validation or type assignment when reading.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ValidationType(System::Xml::ValidationType value);
    /// Returns a value indicating the schema validation settings.
    /// This setting applies to XmlReader objects that validate schemas
    /// (XmlReaderSettings::get_ValidationType value is ValidationType::Schema).
    /// @returns A bitwise combination of enumeration values that specify validation options.
    /// XmlSchemaValidationFlags::ProcessIdentityConstraints and XmlSchemaValidationFlags::AllowXmlAttributes are enabled by default.
    /// XmlSchemaValidationFlags::ProcessInlineSchema, XmlSchemaValidationFlags::ProcessSchemaLocation and
    /// XmlSchemaValidationFlags::ReportValidationWarnings are disabled by default.
    ASPOSECPP_SHARED_API Schema::XmlSchemaValidationFlags get_ValidationFlags();
    /// Sets a value indicating the schema validation settings.
    /// This setting applies to XmlReader objects that validate schemas
    /// (XmlReaderSettings::get_ValidationType value is ValidationType::Schema).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ValidationFlags(Schema::XmlSchemaValidationFlags value);
    /// Returns the XmlSchemaSet to use when performing schema validation.
    /// @returns The XmlSchemaSet to use when performing schema validation.
    /// The default is an empty XmlSchemaSet object.
    ASPOSECPP_SHARED_API SharedPtr<Schema::XmlSchemaSet> get_Schemas();
    /// Sets the XmlSchemaSet to use when performing schema validation.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Schemas(const SharedPtr<Schema::XmlSchemaSet>& value);

    /// Initializes a new instance of the XmlReaderSettings class.
    ASPOSECPP_SHARED_API XmlReaderSettings();

    /// Adds an event handler that occurs when the reader encounters validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_add(Args... value)
    {
        CheckReadOnly(u"ValidationEventHandler");
        _valEventHandler.connect(value...);
    }
    /// Removes an event handler that occurs when the reader encounters validation errors.
    /// @param value A bound or static method or ValidationEventHandler instance.
    template<class... Args> void ValidationEventHandler_remove(Args... value)
    {
        CheckReadOnly(u"ValidationEventHandler");
        _valEventHandler.disconnect(value...);
    }

    /// Resets the members of the settings class to their default values.
    ASPOSECPP_SHARED_API void Reset();
    /// Creates a copy of the XmlReaderSettings instance.
    /// @returns The cloned XmlReaderSettings object.
    ASPOSECPP_SHARED_API SharedPtr<XmlReaderSettings> Clone();
    // For internal purposes
    ASPOSECPP_SHARED_API void CheckReadOnly(const String& propertyName);

protected:

    /// @cond
    bool get_IsXmlResolverSet();
    void set_IsXmlResolverSet(bool value);
    bool get_ReadOnly();
    void set_ReadOnly(bool value);

    SharedPtr<System::Xml::XmlResolver> GetXmlResolver();
    SharedPtr<System::Xml::XmlResolver> GetXmlResolver_CheckConfig();
    System::Xml::Schema::ValidationEventHandler& GetEventHandler();
    SharedPtr<XmlReader> CreateReader(const String& inputUri, const SharedPtr<XmlParserContext>& inputContext);
    SharedPtr<XmlReader> CreateReader(const SharedPtr<IO::Stream>& input, const SharedPtr<Uri>& baseUri, String baseUriString, const SharedPtr<XmlParserContext>& inputContext);
    SharedPtr<XmlReader> CreateReader(const SharedPtr<IO::TextReader>& input, String baseUriString, const SharedPtr<XmlParserContext>& inputContext);
    SharedPtr<XmlReader> CreateReader(const SharedPtr<XmlReader>& reader);
    SharedPtr<XmlReader> AddValidation(SharedPtr<XmlReader> reader);
    SharedPtr<XmlReader> AddConformanceWrapper(const SharedPtr<XmlReader>& baseReader);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlReaderSettings();

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
    const char* DBG_class_name() const override { return "XmlReaderSettings"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlNameTable> _nameTable;
    SharedPtr<System::Xml::XmlResolver> _xmlResolver;
    int32_t _lineNumberOffset;
    int32_t _linePositionOffset;
    System::Xml::ConformanceLevel _conformanceLevel;
    bool _checkCharacters;
    int64_t _maxCharactersInDocument;
    int64_t _maxCharactersFromEntities;
    bool _ignoreWhitespace;
    bool _ignorePIs;
    bool _ignoreComments;
    System::Xml::DtdProcessing _dtdProcessing;
    System::Xml::ValidationType _validationType;
    Schema::XmlSchemaValidationFlags _validationFlags;
    SharedPtr<Schema::XmlSchemaSet> _schemas;
    System::Xml::Schema::ValidationEventHandler _valEventHandler;
    bool _closeInput;
    bool _isReadOnly;
    bool pr_IsXmlResolverSet;

    void Initialize();
    void Initialize(const SharedPtr<System::Xml::XmlResolver>& resolver);
    static SharedPtr<System::Xml::XmlResolver> CreateDefaultResolver();
    SharedPtr<XmlReader> AddValidationAndConformanceWrapper(SharedPtr<XmlReader> reader);
    SharedPtr<XmlValidatingReaderImpl> CreateDtdValidatingReader(const SharedPtr<XmlReader>& baseReader);

};

} // namespace Xml
} // namespace System


