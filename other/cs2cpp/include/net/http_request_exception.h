/// @file net/http_request_exception.h
#pragma once

#include <system/exceptions.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http {

class Details_HttpRequestException;
using HttpRequestException = System::ExceptionWrapper<Details_HttpRequestException>;

/// The base exception class is thrown by the HttpClient and HttpMessageHandler classes.
/// Never create instances of this class manually. Use the HttpRequestException class instead.
/// Never wrap the HttpRequestException class instances into System::SmartPtr.
class Details_HttpRequestException : public System::Details_Exception
{
    /// Parent type.
    typedef System::Details_Exception Base;

public:
    using BaseType = Base;

    /// Constructs a new instance.
    Details_HttpRequestException();
    /// Constructs a new instance.
    /// @remarks Used to support the null pointer value.
    Details_HttpRequestException(std::nullptr_t);
    /// Constructs a new instance.
    /// @param message An error description.
    Details_HttpRequestException(String message);
    /// Constructs a new instance.
    /// @param message An error description.
    /// @param inner A reference to the exception object interpreted as a cause for the exception.
    Details_HttpRequestException(String message, Exception inner);
};

}}} // namespace System::Net::Http
