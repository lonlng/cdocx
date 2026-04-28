/// @file xml/schema/xml_schema_validation_exception.h

#pragma once

#include <xml/schema/xml_schema_exception.h>
#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class DocumentSchemaValidator;
namespace Schema
{
class XmlSchemaValidator;
} // namespace Schema
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

class Details_XmlSchemaValidationException;
using XmlSchemaValidationException = System::ExceptionWrapper<Details_XmlSchemaValidationException>;

/// Represents the exception thrown when XML Schema Definition Language (XSD) schema validation errors and
/// warnings are encountered in an XML document being validated.
class ASPOSECPP_SHARED_CLASS Details_XmlSchemaValidationException : public Details_XmlSchemaException
{
    typedef Details_XmlSchemaValidationException ThisType;
    typedef Details_XmlSchemaException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaValidationException>;

private:
    /// @cond
    friend class System::Xml::DocumentSchemaValidator;
    friend class XmlSchemaValidator;
    friend class XPath::XPathNavigator;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

public:

    /// Returns the XML node that caused this XmlSchemaValidationException.
    /// @returns The XML node that caused this XmlSchemaValidationException.
    ASPOSECPP_SHARED_API SharedPtr<Object> get_SourceObject();

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// Initializes a new instance of the XmlSchemaValidationException class.
    ASPOSECPP_SHARED_API Details_XmlSchemaValidationException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XmlSchemaValidationException class with the exception message specified.
    /// @param message A @c string description of the error condition.
    ASPOSECPP_SHARED_API Details_XmlSchemaValidationException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XmlSchemaValidationException class with the exception message and
    /// original Exception object that caused this exception specified.
    /// @param message A @c string description of the error condition.
    /// @param innerException The original Exception object that caused this exception.
    ASPOSECPP_SHARED_API Details_XmlSchemaValidationException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String message, Exception innerException));

    /// Initializes a new instance of the XmlSchemaValidationException class with the exception message specified,
    /// and the original Exception object, line number, and line position of the XML that cause this exception specified.
    /// @param message A @c string description of the error condition.
    /// @param innerException The original Exception object that caused this exception.
    /// @param lineNumber The line number of the XML that caused this exception.
    /// @param linePosition The line position of the XML that caused this exception.
    ASPOSECPP_SHARED_API Details_XmlSchemaValidationException(const String& message, Exception innerException, int32_t lineNumber, int32_t linePosition);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String message, Exception innerException, int32_t lineNumber, int32_t linePosition));

    /// @cond
    Details_XmlSchemaValidationException(const String& res, const String& arg, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String res, String arg, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaValidationException(const String& res, const ArrayPtr<String>& args, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaValidationException(const String& res, const ArrayPtr<String>& args, Exception innerException, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, Exception innerException, String sourceUri, int32_t lineNumber, int32_t linePosition));

    Details_XmlSchemaValidationException(const String& res, const ArrayPtr<String>& args, const SharedPtr<Object>& sourceNode);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XmlSchemaValidationException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, SharedPtr<Object> sourceNode));

    /// Sets the XML node that causes the error.
    /// @param sourceObject The source object.
    ASPOSECPP_SHARED_API void SetSourceObject(const SharedPtr<Object>& sourceObject);

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
    const char* DBG_class_name() const override { return "Details_XmlSchemaValidationException"; }
#endif
    /// @endcond

private:

    SharedPtr<Object> _sourceNodeObject;

};

} // namespace Schema
} // namespace Xml
} // namespace System


