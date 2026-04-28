/// @file xml/schema/inference/xml_schema_inference_exception.h

#pragma once

#include <xml/schema/xml_schema_exception.h>
#include <system/exceptions.h>
#include <cstdint>


/// @cond
namespace System
{
class String;
namespace Xml
{
namespace Schema
{
class XmlSchemaInference;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

class Details_XmlSchemaInferenceException;
using XmlSchemaInferenceException = System::ExceptionWrapper<Details_XmlSchemaInferenceException>;

/// Returns information about errors encountered by the XmlSchemaInference class while inferring a schema from an XML document.
class ASPOSECPP_SHARED_CLASS Details_XmlSchemaInferenceException : public Details_XmlSchemaException
{
    typedef Details_XmlSchemaInferenceException ThisType;
    typedef Details_XmlSchemaException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaInferenceException>;

private:
    /// @cond
    friend class XmlSchemaInference;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// Initializes a new instance of the XmlSchemaInferenceException class.
    ASPOSECPP_SHARED_API Details_XmlSchemaInferenceException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XmlSchemaInferenceException class with the error message specified.
    /// @param message A description of the error.
    ASPOSECPP_SHARED_API Details_XmlSchemaInferenceException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XmlSchemaInferenceException class with the error message specified and
    /// the original Exception that caused the XmlSchemaInferenceException specified.
    /// @param message A description of the error.
    /// @param innerException An Exception object containing the original exception that caused the XmlSchemaInferenceException.
    ASPOSECPP_SHARED_API Details_XmlSchemaInferenceException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS(String message, Exception innerException));

    /// Initializes a new instance of the XmlSchemaInferenceException class with the error message specified,
    /// the original Exception that caused the XmlSchemaInferenceException specified,
    /// and the line number and line position of the error in the XML document specified.
    /// @param message A description of the error.
    /// @param innerException An Exception object containing the original exception that caused the XmlSchemaInferenceException.
    /// @param lineNumber The line number in the XML document that caused the XmlSchemaInferenceException.
    /// @param linePosition The line position in the XML document that caused the XmlSchemaInferenceException.
    ASPOSECPP_SHARED_API Details_XmlSchemaInferenceException(const String& message, Exception innerException, int32_t lineNumber, int32_t linePosition);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS(String message, Exception innerException, int32_t lineNumber, int32_t linePosition));

    /// @cond
    Details_XmlSchemaInferenceException(const String& res, const String& arg);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS(String res, String arg));

    Details_XmlSchemaInferenceException(const String& res, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaInferenceException, CODEPORTING_ARGS(String res, int32_t lineNumber, int32_t linePosition));
    /// @endcond
};

} // namespace Schema
} // namespace Xml
} // namespace System


