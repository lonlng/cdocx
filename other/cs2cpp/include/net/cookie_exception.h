/// @file net/cookie_exception.h
#pragma once

#include <system/exceptions.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net {

class Details_CookieException;
using CookieException = System::ExceptionWrapper<Details_CookieException>;

/// Represents an exception thrown when the size of CookieContainer is greater than the MaxCookieSize property value.
/// Never create instances of this class manually. Use the CookieException class instead.
/// Never wrap the CookieException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_CookieException : public System::Details_FormatException
{
public:
    /// Destructs the current instance.
    ASPOSECPP_SHARED_API virtual ~Details_CookieException();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API Details_CookieException();
    /// Constructs a new instance.
    /// @remarks Used to support the null pointer value.
    ASPOSECPP_SHARED_API Details_CookieException(std::nullptr_t);
    /// Constructs a new instance.
    /// @param message An error description.
    ASPOSECPP_SHARED_API Details_CookieException(String message);
    /// Constructs a new instance.
    /// @param message An error description.
    /// @param inner A reference to the exception object interpreted as a cause for the exception.
    ASPOSECPP_SHARED_API Details_CookieException(String message, Exception inner);
};

}} // namespace System::Net
