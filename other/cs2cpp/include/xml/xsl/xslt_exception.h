/// @file xml/xsl/xslt_exception.h

#pragma once

#include <system/exceptions.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
namespace Xsl
{
namespace Runtime
{
class DecimalFormatter;
} // namespace Runtime
class Details_XsltCompileException; using XsltCompileException = System::ExceptionWrapper<Details_XsltCompileException>;
namespace XsltOld
{
class ApplyImportsAction;
class ApplyTemplatesAction;
class AttributeAction;
class AttributeSetAction;
class CallTemplateAction;
class ChooseAction;
class CompiledAction;
class Compiler;
class ContainerAction;
class ElementAction;
class InputScopeManager;
class MessageAction;
class NewInstructionAction;
class NumberAction;
class PrefixQName;
class Processor;
class RootAction;
class SequentialOutput;
class SortAction;
class Stylesheet;
class TemplateAction;
class VariableAction;
class WithParamAction;
class XsltCompileContext;
class XsltOutput;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

class Details_XsltException;
using XsltException = System::ExceptionWrapper<Details_XsltException>;

/// The exception that is thrown when an error occurs while processing an XSLT transformation.
class ASPOSECPP_SHARED_CLASS Details_XsltException : public Details_SystemException
{
    typedef Details_XsltException ThisType;
    typedef Details_SystemException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltException>;

private:
    /// @cond
    friend class Details_XsltCompileException;
    friend class Runtime::DecimalFormatter;
    friend class XsltOld::ApplyImportsAction;
    friend class XsltOld::CompiledAction;
    friend class XsltOld::ApplyTemplatesAction;
    friend class XsltOld::ContainerAction;
    friend class XsltOld::AttributeAction;
    friend class XsltOld::AttributeSetAction;
    friend class XsltOld::CallTemplateAction;
    friend class XsltOld::ChooseAction;
    friend class XsltOld::Compiler;
    friend class XsltOld::Compiler;
    friend class XsltOld::ElementAction;
    friend class XsltOld::MessageAction;
    friend class XsltOld::NewInstructionAction;
    friend class XsltOld::NumberAction;
    friend class XsltOld::RootAction;
    friend class XsltOld::SortAction;
    friend class XsltOld::TemplateAction;
    friend class XsltOld::VariableAction;
    friend class XsltOld::WithParamAction;
    friend class XsltOld::InputScopeManager;
    friend class XsltOld::PrefixQName;
    friend class XsltOld::Processor;
    friend class XsltOld::SequentialOutput;
    friend class XsltOld::Stylesheet;
    friend class XsltOld::XsltCompileContext;
    friend class XsltOld::XsltCompileContext;
    friend class XsltOld::XsltCompileContext;
    friend class XsltOld::XsltOutput;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

public:

    /// Returns the location path of the style sheet.
    /// @returns The location path of the style sheet.
    virtual ASPOSECPP_SHARED_API String get_SourceUri();
    /// Returns the line number indicating where the error occurred in the style sheet.
    /// @returns The line number indicating where the error occurred in the style sheet.
    virtual ASPOSECPP_SHARED_API int32_t get_LineNumber();
    /// Returns the line position indicating where the error occurred in the style sheet.
    /// @returns The line position indicating where the error occurred in the style sheet.
    virtual ASPOSECPP_SHARED_API int32_t get_LinePosition();
    /// Returns the formatted error message describing the current exception.
    /// @returns The formatted error message describing the current exception.
    ASPOSECPP_SHARED_API String get_Message() const override;

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// Initializes a new instance of the XsltException class.
    ASPOSECPP_SHARED_API Details_XsltException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XsltException class with a specified error message.
    /// @param message The message that describes the error.
    ASPOSECPP_SHARED_API Details_XsltException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XsltException class.
    /// @param message The description of the error condition.
    /// @param innerException The Exception which threw the XsltException, if any. This value can be @c nullptr.
    ASPOSECPP_SHARED_API Details_XsltException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltException, CODEPORTING_ARGS(String message, Exception innerException));

    /// @cond
    static XsltException Create(const String& res, const ArrayPtr<String>& args);
    static XsltException Create(const String& res, const ArrayPtr<String>& args, Exception inner);

    Details_XsltException(const String& res, const ArrayPtr<String>& args, const String& sourceUri, int32_t lineNumber, int32_t linePosition, Exception inner);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltException, CODEPORTING_ARGS(String res, ArrayPtr<String> args, String sourceUri, int32_t lineNumber, int32_t linePosition, Exception inner));

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
    const char* DBG_class_name() const override { return "Details_XsltException"; }
#endif
    /// @endcond

private:

    String _res;
    ArrayPtr<String> _args;
    String _sourceUri;
    int32_t _lineNumber;
    int32_t _linePosition;
    String _message;

    static String CreateMessage(const String& res, const ArrayPtr<String>& args, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    static String FormatMessage(const String& key, const ArrayPtr<String>& args);

};

/// The exception that is thrown by the **Load** method when an error is found in the XSLT style sheet.
class ASPOSECPP_SHARED_CLASS Details_XsltCompileException : public Details_XsltException
{
    typedef Details_XsltCompileException ThisType;
    typedef Details_XsltException BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltCompileException>;

private:
    /// @cond
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    /// @endcond

protected:

    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    /// Initializes a new instance of the XsltCompileException class.
    ASPOSECPP_SHARED_API Details_XsltCompileException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltCompileException, CODEPORTING_ARGS());

    /// Initializes a new instance of the XsltCompileException class with a specified error message.
    /// @param message The message that describes the error.
    ASPOSECPP_SHARED_API Details_XsltCompileException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltCompileException, CODEPORTING_ARGS(String message));

    /// Initializes a new instance of the XsltCompileException class specified error message and
    /// a reference to the inner exception that is the cause of this exception.
    /// @param message The message that describes the error.
    /// @param innerException The exception that is the cause of the current exception, or @c nullptr if no inner exception is specified.
    ASPOSECPP_SHARED_API Details_XsltCompileException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltCompileException, CODEPORTING_ARGS(String message, Exception innerException));

    /// Initializes a new instance of the XsltCompileException class.
    /// @param inner The Exception that threw the XsltCompileException.
    /// @param sourceUri The location path of the style sheet.
    /// @param lineNumber The line number indicating where the error occurred in the style sheet.
    /// @param linePosition The line position indicating where the error occurred in the style sheet.
    ASPOSECPP_SHARED_API Details_XsltCompileException(Exception inner, const String& sourceUri, int32_t lineNumber, int32_t linePosition);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_XsltCompileException, CODEPORTING_ARGS(Exception inner, String sourceUri, int32_t lineNumber, int32_t linePosition));

};

} // namespace Xsl
} // namespace Xml
} // namespace System


