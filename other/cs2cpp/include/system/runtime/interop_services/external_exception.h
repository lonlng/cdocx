/// @file system/runtime/interop_services/external_exception.h

#pragma once

#include "system/details_exception_with_error_code.h"

namespace System { namespace Runtime { namespace InteropServices {

/// The base exception type for all COM interop exceptions and structured exception handling (SEH) exceptions.
/// Never create instances of this class manually. Use the ExternalException class instead.
/// Never wrap the ExternalException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_ExternalException : public Details_ExceptionWithErrorCode<Details_SystemException>
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = Details_ExceptionWithErrorCode<Details_SystemException>;
    RTTI_INFO_NAMED(System::Runtime::InteropServices::Details_ExternalException, "System::Runtime::ExternalException",
                    ::System::BaseTypesInfo<System::Object>);

protected:
    /// Initializes a new instance of the ExternalException class with default properties.
    ASPOSECPP_SHARED_API Details_ExternalException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_ExternalException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Initializes a new instance of the ExternalException class with a specified error message.
    /// @param message The error message string.
    ASPOSECPP_SHARED_API Details_ExternalException(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_ExternalException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
    /// Initializes a new instance of the ExternalException class with a specified error message and a reference
    /// to the inner exception that is the cause of this exception.
    /// @param message The error message that explains the reason for the exception.
    /// @param innerException The exception that is the cause of the current exception. If the innerException parameter
    /// is not null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_ExternalException(const String& message, const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_ExternalException, CODEPORTING_ARGS(const String& message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException));
    /// Initializes a new instance of the ExternalException class with a specified error message and
    /// the HRESULT of the error.
    /// param message he error message that specifies the reason for the exception.
    /// param The HRESULT of the error.
    ASPOSECPP_SHARED_API Details_ExternalException(const String& message, int32_t errorCode);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_ExternalException, CODEPORTING_ARGS(const String& message, int32_t errorCode), CODEPORTING_ARGS(message, errorCode));
    /// @see Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

private:
    /// The default message
    static const String s_default_message;
    /// Replaces the incoming message parameter with default message if it is null.
    /// @param message Incoming String message.
    /// @return String reference. If the incoming message parameter is null, it is replaced with default message.
    static const String& DefaultMessageIfNull(const String& message);
};

using ExternalException = System::ExceptionWrapper<Details_ExternalException>;
}}} // namespace System::Runtime::InteropServices
