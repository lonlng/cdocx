/// @file xml/schema/xml_schema_exception.h

#pragma once

#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class DtdParser;
namespace Schema
{
class Asttree;
class BaseProcessor;
class BaseValidator;
class BinaryFacetsChecker;
class CompiledIdentityConstraint;
class Compiler;
class Datatype_dayTimeDuration;
class Datatype_doubleXdr;
class Datatype_duration;
class Datatype_floatXdr;
class Datatype_List;
class Datatype_NOTATION;
class Datatype_QName;
class Datatype_QNameXdr;
class Datatype_union;
class Datatype_yearMonthDuration;
class DatatypeImplementation;
class DateTimeFacetsChecker;
class DtdValidator;
class DurationFacetsChecker;
class FacetsChecker;
class ListFacetsChecker;
class Numeric10FacetsChecker;
class Numeric2FacetsChecker;
class Parser;
class Preprocessor;
class QNameFacetsChecker;
class SchemaAttDef;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaElementDecl;
class SchemaInfo;
class StringFacetsChecker;
class UnionFacetsChecker;
class XdrBuilder;
class XdrValidator;
class Details_XmlSchemaInferenceException; using XmlSchemaInferenceException = System::ExceptionWrapper<Details_XmlSchemaInferenceException>;
class XmlSchemaObject;
class XmlSchemaParticle;
class XmlSchemaSet;
class Details_XmlSchemaValidationException; using XmlSchemaValidationException = System::ExceptionWrapper<Details_XmlSchemaValidationException>;
class XmlSchemaValidator;
class XsdBuilder;
class XsdValidator;
} // namespace Schema
class XmlConvert;
class XmlTextReaderImpl;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

class Details_XmlSchemaException;
using XmlSchemaException = System::ExceptionWrapper<Details_XmlSchemaException>;

/// Returns detailed information about the schema exception.
class ASPOSECPP_SHARED_CLASS Details_XmlSchemaException : public Details_SystemException
{
    typedef Details_XmlSchemaException ThisType;
    typedef Details_SystemException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaException>;

private:
    /// @cond
    friend class XmlTextReaderImpl;
    friend class Asttree;
    friend class BaseValidator;
    friend class BaseProcessor;
    friend class CompiledIdentityConstraint;
    friend class DatatypeImplementation;
    friend class Datatype_List;
    friend class Datatype_union;
    friend class Datatype_duration;
    friend class Datatype_yearMonthDuration;
    friend class Datatype_dayTimeDuration;
    friend class Datatype_QName;
    friend class Datatype_NOTATION;
    friend class Datatype_doubleXdr;
    friend class Datatype_floatXdr;
    friend class Datatype_QNameXdr;
    friend class DtdParser;
    friend class DtdValidator;
    friend class XmlSchemaParticle;
    friend class FacetsChecker;
    friend class FacetsChecker;
    friend class Numeric10FacetsChecker;
    friend class Numeric2FacetsChecker;
    friend class DurationFacetsChecker;
    friend class DateTimeFacetsChecker;
    friend class StringFacetsChecker;
    friend class QNameFacetsChecker;
    friend class BinaryFacetsChecker;
    friend class ListFacetsChecker;
    friend class UnionFacetsChecker;
    friend class Details_XmlSchemaInferenceException;
    friend class Parser;
    friend class Preprocessor;
    friend class SchemaAttDef;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class SchemaElementDecl;
    friend class SchemaInfo;
    friend class Compiler;
    friend class XdrBuilder;
    friend class XdrValidator;
    friend class XmlSchemaSet;
    friend class Details_XmlSchemaValidationException;
    friend class XmlSchemaValidator;
    friend class XsdBuilder;
    friend class XsdValidator;
    friend class XmlConvert;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

public:

    /// Returns the Uniform Resource Identifier (URI) location of the schema that caused the exception.
    /// @returns The URI location of the schema that caused the exception.
    ASPOSECPP_SHARED_API String get_SourceUri();
    /// Returns the line number indicating where the error occurred.
    /// @returns The line number indicating where the error occurred.
    ASPOSECPP_SHARED_API int32_t get_LineNumber();
    /// Returns the line position indicating where the error occurred.
    /// @returns The line position indicating where the error occurred.
    ASPOSECPP_SHARED_API int32_t get_LinePosition();
    /// The @c XmlSchemaObject that produced the XmlSchemaException.
    /// @returns A valid object instance represents a structural validation error in the XML Schema Object Model (SOM).
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> get_SourceSchemaObject();
    /// Returns the description of the error condition of this exception.
    /// @returns The description of the error condition of this exception.
    ASPOSECPP_SHARED_API String get_Message() const override;

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// @cond
    String get_GetRes();
    ArrayPtr<String> get_Args();
    /// @endcond

    /// Initializes a new instance of the XmlSchemaException class.
    ASPOSECPP_SHARED_API Details_XmlSchemaException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XmlSchemaException class with the exception message specified.
    /// @param message A @c string description of the error condition.
    ASPOSECPP_SHARED_API Details_XmlSchemaException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XmlSchemaException class with the exception message and
    /// original Exception object that caused this exception specified.
    /// @param message A @c string description of the error condition.
    /// @param innerException The original Exception object that caused this exception.
    ASPOSECPP_SHARED_API Details_XmlSchemaException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String message, Exception innerException));

    /// Initializes a new instance of the XmlSchemaException class with the exception message specified,
    /// and the original Exception object, line number, and line position of the XML that cause this exception specified.
    /// @param message A @c string description of the error condition.
    /// @param innerException The original Exception object that caused this exception.
    /// @param lineNumber The line number of the XML that caused this exception.
    /// @param linePosition The line position of the XML that caused this exception.
    ASPOSECPP_SHARED_API Details_XmlSchemaException(const String& message, Exception innerException, int32_t lineNumber, int32_t linePosition);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String message, Exception innerException, int32_t lineNumber, int32_t linePosition));

    /// @cond
    Details_XmlSchemaException(const String& res, const ArrayPtr<String>& args);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, ArrayPtr<String> args));

    Details_XmlSchemaException(const String& res, const String& arg);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, String arg));

    Details_XmlSchemaException(const String& res, const String& arg, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, String arg, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaException(const String& res, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaException(const String& res, const ArrayPtr<String>& args, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaException(const String& res, const SharedPtr<XmlSchemaObject>& source);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, SharedPtr<XmlSchemaObject> source));

    Details_XmlSchemaException(const String& res, const String& arg, const SharedPtr<XmlSchemaObject>& source);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, String arg, SharedPtr<XmlSchemaObject> source));

    Details_XmlSchemaException(const String& res, const ArrayPtr<String>& args, const SharedPtr<XmlSchemaObject>& source);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, SharedPtr<XmlSchemaObject> source));

    Details_XmlSchemaException(const String& res, const ArrayPtr<String>& args, Exception innerException, const String& sourceUri, int32_t lineNumber, int32_t linePosition, const SharedPtr<XmlSchemaObject>& source);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, Exception innerException, String sourceUri, int32_t lineNumber, int32_t linePosition, SharedPtr<XmlSchemaObject> source));

    static String CreateMessage(const String& res, const ArrayPtr<String>& args);
    void SetSource(const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    void SetSchemaObject(const SharedPtr<XmlSchemaObject>& source);
    void SetSource(const SharedPtr<XmlSchemaObject>& source);

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
    const char* DBG_class_name() const override { return "Details_XmlSchemaException"; }
#endif
    /// @endcond

private:

    String _res;
    ArrayPtr<String> _args;
    String _sourceUri;
    int32_t _lineNumber;
    int32_t _linePosition;
    SharedPtr<XmlSchemaObject> _sourceSchemaObject;
    String _message;

};

} // namespace Schema
} // namespace Xml
} // namespace System


