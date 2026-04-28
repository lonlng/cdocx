/// @file net/socket_exception.h
#pragma once

#include <cstdint>
#include <system/exceptions.h>

#include <net/sockets/socket_error.h>

namespace System { namespace Net { namespace Sockets {

class Details_SocketException;
using SocketException = System::ExceptionWrapper<Details_SocketException>;

/// Represents the exception thrown when a socket error occurs.
/// Never create instances of this class manually. Use the SocketException class instead.
/// Never wrap the SocketException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_SocketException : public System::Details_Exception
{
    /// This type.
    typedef Details_SocketException ThisType;
    /// Parent type.
    typedef System::Details_Exception BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    RTTI_INFO_DECL();

    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    //typedef System::Details_Exception Base;
    //using BaseType = Base;

public:
    /// Sets the error code.
    /// @param code The error code to set.
    ASPOSECPP_SHARED_API void set_ErrorCode(int32_t code);
    /// Gets the error code.
    /// @returns The error code.
    ASPOSECPP_SHARED_API int32_t get_ErrorCode();
    /// Gets the socket error code.
    /// @returns The socket error code.
    ASPOSECPP_SHARED_API SocketError get_SocketErrorCode();
    /// Sets the socket error code.
    /// @param socketError The socket error code to set.
    ASPOSECPP_SHARED_API void set_SocketErrorCode(SocketError socketError);

protected:
    /// Constructs a new instance.
    /// @param message The error description.
    ASPOSECPP_SHARED_API Details_SocketException(const System::String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SocketException, CODEPORTING_ARGS(const System::String& message), CODEPORTING_ARGS(message));
    /// Constructs a new instance.
    /// @param errorCode The error code.
    ASPOSECPP_SHARED_API Details_SocketException(int32_t errorCode);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SocketException, CODEPORTING_ARGS(int32_t errorCode), CODEPORTING_ARGS(errorCode));
    /// Constructs a new instance.
    /// @param socketError The socket error code.
    ASPOSECPP_SHARED_API Details_SocketException(SocketError socketError);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SocketException, CODEPORTING_ARGS(SocketError socketError), CODEPORTING_ARGS(socketError));
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API Details_SocketException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SocketException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// @copydoc System::Details_Exception::DoThrow
    [[noreturn]] ASPOSECPP_SHARED_API void DoThrow(const ExceptionPtr& self) const override;
    /// Constructs a new instance.
    /// @remarks Used to support the null pointer value.
    ASPOSECPP_SHARED_API Details_SocketException(std::nullptr_t);

    /// Constructs a new instance.
    /// @param message The error description.
    /// @param errorCode The error code.
    Details_SocketException(const System::String& message, int32_t errorCode);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_SocketException, CODEPORTING_ARGS(const System::String& message, int32_t errorCode), CODEPORTING_ARGS(message, errorCode));

private:
    /// The error code.
    int32_t m_errorCode = 0;
    /// The socket error code.
    SocketError m_socketError = SocketError::Success;
};
}}} // namespace System::Net::Sockets
