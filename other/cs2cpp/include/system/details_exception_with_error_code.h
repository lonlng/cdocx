// @file system/details_exception_with_error_code.h

#pragma once

#include "system/convert.h"
#include "system/exceptions.h"

namespace System {
/// The template class for an exception with an error code.
/// @tparam T An exception base class.
template <typename T, typename = std::enable_if<std::is_base_of<Exception, T>::value>>
class Details_ExceptionWithErrorCode : public T
{
    /// The default value of HResult. It is used when the error code value is not passed.
    static const int32_t DEFAULT_HRESULT = -2147467259;

protected:
    /// Initializes a new instance of the ExceptionWithErrorCode class with default properties.
    Details_ExceptionWithErrorCode() : T()
    {
        T::m_HResult = DEFAULT_HRESULT;
    }
    /// Initializes a new instance of the ExceptionWithErrorCode class with a specified error message.
    /// @param message The error message string.
    Details_ExceptionWithErrorCode(const String& message) : T(message)
    {
        T::m_HResult = DEFAULT_HRESULT;
    }
    /// Initializes a new instance of the ExceptionWithErrorCode class with a specified error message and a reference
    /// to the inner exception that is the cause of this exception.
    /// @param message The error message that explains the reason for the exception.
    /// @param innerException The exception that is the cause of the current exception. If the innerException parameter
    /// is not null, the current exception is raised in a catch block that handles the inner exception.
    Details_ExceptionWithErrorCode(const String& message, const System::Exception& innerException)
        : T(message, innerException)
    {
        T::m_HResult = DEFAULT_HRESULT;
    }
    /// Initializes a new instance of the ExceptionWithErrorCode class with a specified error message and
    /// the HRESULT of the error.
    /// param message he error message that specifies the reason for the exception.
    /// param The HRESULT of the error.
    Details_ExceptionWithErrorCode(const String& message, int32_t errorCode) : T(message)
    {
        T::m_HResult = errorCode;
    }
    /// @see System::Exception::ExtraDescription
    virtual String ExtraDescription() const override
    {
        return Convert::ToString(T::m_HResult);
    }

public:
    /// Gets the HRESULT of the error.
    virtual int32_t get_ErrorCode() const
    {
        return T::m_HResult;
    }
    /// @see System::Exception::get_Message
    virtual String get_Message() const override
    {
        return T::m_message == nullptr ? T::DefaultMessage() : T::m_message;
    }
};
} // namespace System
