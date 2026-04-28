/// @file net/web_exception.h
#pragma once

#include <system/exceptions.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/http_web_request.h>
#include <net/web_exception_status.h>

namespace System { namespace Net {

class Details_WebException;
using WebException = System::ExceptionWrapper<Details_WebException>;

/// Represents the exception that is thrown by WebRequest when an error occurs.
/// Never create instances of this class manually. Use the WebException class instead.
/// Never wrap the WebException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_WebException : public System::Details_InvalidOperationException
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = System::Details_InvalidOperationException;

public:
    /// Destructs the current instance.
    virtual ~Details_WebException();

    /// Returns the status code.
    /// @returns The status code.
    ASPOSECPP_SHARED_API WebExceptionStatus get_Status();
    /// Returns the web response with which the current exception is associated.
    /// @returns The web response with which the current exception is associated.
    ASPOSECPP_SHARED_API System::SharedPtr<WebResponse> get_Response();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API Details_WebException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_WebException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Constructs a new instance.
    /// @param message The error description.
    ASPOSECPP_SHARED_API Details_WebException(String message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_WebException, CODEPORTING_ARGS(String message), CODEPORTING_ARGS(message));
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param innerException The inner exception.
    ASPOSECPP_SHARED_API Details_WebException(String message, Exception innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_WebException, CODEPORTING_ARGS(String message, Exception innerException), CODEPORTING_ARGS(message, innerException));
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param status The status code.
    ASPOSECPP_SHARED_API Details_WebException(String message, WebExceptionStatus status);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_WebException, CODEPORTING_ARGS(String message, WebExceptionStatus status), CODEPORTING_ARGS(message, status));
    /// Constructs a new instance.
    /// @param message The exception message.
    /// @param innerException The inner exception.
    /// @param status The status code.
    /// @param response The web response with which the current exception is associated.
    ASPOSECPP_SHARED_API Details_WebException(String message, Exception innerException, WebExceptionStatus status,
                                      System::SharedPtr<WebResponse> response);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_WebException,
        CODEPORTING_ARGS(
            String message, Exception innerException, WebExceptionStatus status,
            System::SharedPtr<WebResponse> response
        ),
        CODEPORTING_ARGS(message, innerException, status, response)
    );

    /// Is not implemented.
    /// @internal
    static Exception CreateCompatibleException(Exception exception);

protected:
    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override { throw System::ExceptionWrapper<Details_WebException>(self); }

private:
    /// The default status code.
    static const WebExceptionStatus DefaultStatus;
    /// The status code.
    WebExceptionStatus _status;
    /// The web response with which the current exception is associated.
    System::SharedPtr<WebResponse> _response;
};

}} // namespace System::Net
