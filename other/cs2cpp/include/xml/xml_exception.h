/// @file xml/xml_exception.h

#pragma once

#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class Base64Decoder;
class BinHexDecoder;
class BinXmlDateTime;
class BinXmlSqlDecimal;
class DocumentXmlWriter;
class DtdParser;
class HWStack;
class IXmlLineInfo;
class QueryOutputWriter;
class ReadContentAsBinaryHelper;
namespace Schema
{
class BaseValidator;
class DtdValidator;
class Preprocessor;
class SchemaCollectionPreprocessor;
class XdrBuilder;
class XdrValidator;
class XsdValidator;
} // namespace Schema
class Ucs4Decoder1234;
class Ucs4Decoder2143;
class Ucs4Decoder3412;
class Ucs4Decoder4321;
class ValidateNames;
class XmlCharCheckingReader;
class XmlCharCheckingWriter;
class XmlConvert;
class XmlDocument;
class XmlEncodedRawTextWriter;
class XmlLoader;
class XmlNullResolver;
class XmlParserContext;
class XmlQualifiedName;
class XmlReader;
class XmlReaderSettings;
class XmlSqlBinaryReader;
class XmlSubtreeReader;
class XmlSystemPathResolver;
class XmlTextReaderImpl;
class XmlUrlResolver;
class XmlUtf8RawTextWriter;
class XmlValidatingReaderImpl;
class XmlWellFormedWriter;
class XmlWriter;
class XmlWriterSettings;
class XsdValidatingReader;
namespace Xsl
{
namespace XsltOld
{
class XsltCompileContext;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

class Details_XmlException;
using XmlException = System::ExceptionWrapper<Details_XmlException>;

/// Returns detailed information about the last exception.
class ASPOSECPP_SHARED_CLASS Details_XmlException : public Details_SystemException
{
    typedef Details_XmlException ThisType;
    typedef Details_SystemException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlException>;

private:
    /// @cond
    friend class Base64Decoder;
    friend class BinXmlSqlDecimal;
    friend class BinXmlDateTime;
    friend class XmlSqlBinaryReader;
    friend class XmlReader;
    friend class XmlSqlBinaryReader;
    friend class BinHexDecoder;
    friend class XmlEncodedRawTextWriter;
    friend class XmlUtf8RawTextWriter;
    friend class QueryOutputWriter;
    friend class XmlWriter;
    friend class ReadContentAsBinaryHelper;
    friend class XmlCharCheckingReader;
    friend class XmlCharCheckingWriter;
    friend class XmlParserContext;
    friend class XmlReaderSettings;
    friend class XmlSubtreeReader;
    friend class XmlTextReaderImpl;
    friend class XmlTextReaderImpl;
    friend class XmlValidatingReaderImpl;
    friend class XmlWellFormedWriter;
    friend class XmlWriterSettings;
    friend class XsdValidatingReader;
    friend class DocumentXmlWriter;
    friend class XmlDocument;
    friend class XmlLoader;
    friend class HWStack;
    friend class XmlSystemPathResolver;
    friend class Schema::BaseValidator;
    friend class DtdParser;
    friend class Schema::DtdValidator;
    friend class Schema::Preprocessor;
    friend class Schema::SchemaCollectionPreprocessor;
    friend class Schema::XdrBuilder;
    friend class Schema::XdrValidator;
    friend class Schema::XsdValidator;
    friend class ValidateNames;
    friend class XmlConvert;
    friend class Ucs4Decoder4321;
    friend class Ucs4Decoder1234;
    friend class Ucs4Decoder2143;
    friend class Ucs4Decoder3412;
    friend class XmlNullResolver;
    friend class XmlQualifiedName;
    friend class XmlUrlResolver;
    friend class Xsl::XsltOld::XsltCompileContext;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

public:

    /// Returns the line number indicating where the error occurred. Line numbers start at 1.
    /// @returns The line number indicating where the error occurred.
    ASPOSECPP_SHARED_API int32_t get_LineNumber();
    /// Returns the line position indicating where the error occurred. Line position starts at 1.
    /// @returns The line position indicating where the error occurred.
    ASPOSECPP_SHARED_API int32_t get_LinePosition();
    /// Returns the location of the XML file.
    /// @returns The source URI for the XML data. If there is no source URI, this method returns @c nullptr.
    ASPOSECPP_SHARED_API String get_SourceUri();
    /// Returns a message describing the current exception.
    /// @returns The error message that explains the reason for the exception.
    ASPOSECPP_SHARED_API String get_Message() const override;

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// @cond
    String get_ResString();
    /// @endcond

    /// Initializes a new instance of the XmlException class.
    ASPOSECPP_SHARED_API Details_XmlException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XmlException class with a specified error message.
    /// @param message The error description.
    ASPOSECPP_SHARED_API Details_XmlException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XmlException class.
    /// @param message The description of the error condition.
    /// @param innerException The Exception that threw the XmlException, if any. This value can be @c nullptr.
    ASPOSECPP_SHARED_API Details_XmlException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String message, Exception innerException));

    /// Initializes a new instance of the XmlException class with the specified message, inner exception, line number, and line position.
    /// @param message The error description.
    /// @param innerException The exception that is the cause of the current exception. This value can be @c nullptr.
    /// @param lineNumber The line number indicating where the error occurred.
    /// @param linePosition The line position indicating where the error occurred.
    ASPOSECPP_SHARED_API Details_XmlException(const String& message, Exception innerException, int32_t lineNumber, int32_t linePosition);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String message, Exception innerException, int32_t lineNumber, int32_t linePosition));

    /// @cond
    Details_XmlException(const String& message, Exception innerException, int32_t lineNumber, int32_t linePosition, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String message, Exception innerException, int32_t lineNumber, int32_t linePosition, String sourceUri));

    Details_XmlException(const String& res, const ArrayPtr<String>& args);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args));

    Details_XmlException(const String& res, const String& arg);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg));

    Details_XmlException(const String& res, const String& arg, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg, String sourceUri));

    Details_XmlException(const String& res, const String& arg, const SharedPtr<IXmlLineInfo>& lineInfo);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg, SharedPtr<IXmlLineInfo> lineInfo));

    Details_XmlException(const String& res, const String& arg, Exception innerException, const SharedPtr<IXmlLineInfo>& lineInfo);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg, Exception innerException, SharedPtr<IXmlLineInfo> lineInfo));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, const SharedPtr<IXmlLineInfo>& lineInfo);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, SharedPtr<IXmlLineInfo> lineInfo));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, const SharedPtr<IXmlLineInfo>& lineInfo, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, SharedPtr<IXmlLineInfo> lineInfo, String sourceUri));

    Details_XmlException(const String& res, const String& arg, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg, int32_t lineNumber, int32_t linePosition));

    Details_XmlException(const String& res, const String& arg, int32_t lineNumber, int32_t linePosition, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, String arg, int32_t lineNumber, int32_t linePosition, String sourceUri));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, int32_t lineNumber, int32_t linePosition));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, int32_t lineNumber, int32_t linePosition, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, int32_t lineNumber, int32_t linePosition, String sourceUri));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, Exception innerException, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, Exception innerException, int32_t lineNumber, int32_t linePosition));

    Details_XmlException(const String& res, const ArrayPtr<String>& args, Exception innerException, int32_t lineNumber, int32_t linePosition, const String& sourceUri);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, Exception innerException, int32_t lineNumber, int32_t linePosition, String sourceUri));

    static ArrayPtr<String> BuildCharExceptionArgs(const String& data, int32_t invCharIndex);
    static ArrayPtr<String> BuildCharExceptionArgs(const ArrayPtr<char16_t>& data, int32_t length, int32_t invCharIndex);
    static ArrayPtr<String> BuildCharExceptionArgs(char16_t invChar, char16_t nextChar);
    static bool IsCatchableException(Exception e);

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
    const char* DBG_class_name() const override { return "Details_XmlException"; }
    #endif
    /// @endcond

private:

    String _res;
    ArrayPtr<String> _args;
    int32_t _lineNumber;
    int32_t _linePosition;
    String _sourceUri;
    String _message;

    static String FormatUserMessage(const String& message, int32_t lineNumber, int32_t linePosition);
    static String CreateMessage(const String& res, const ArrayPtr<String>& args, int32_t lineNumber, int32_t linePosition);

};

} // namespace Xml
} // namespace System


