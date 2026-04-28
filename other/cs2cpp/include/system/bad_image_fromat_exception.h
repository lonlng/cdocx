/// @file system/bad_image_fromat_exception.h

#pragma once

#include "system/details_exception_with_filename.h"

namespace System {
/// The exception that is thrown when the file image of a dynamic link library (DLL) or an executable program is
/// invalid.
/// Never create instances of this class manually. Use the BadImageFormatException class instead.
/// Never wrap the BadImageFormatException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_BadImageFormatException
    : public Details_ExceptionWithFilename<Details_SystemException>
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = Details_ExceptionWithFilename<Details_SystemException>;
    RTTI_INFO_NAMED(System::Details_BadImageFormatException, "System::BadImageFormatException",
                    ::System::BaseTypesInfo<System::Object>);

protected:
    /// Initializes a new instance of the BadImageFormatException class.
    ASPOSECPP_SHARED_API Details_BadImageFormatException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_BadImageFormatException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Initializes a new instance of the BadImageFormatException class with a specified error message.
    /// @param message The message that describes the error.
    ASPOSECPP_SHARED_API Details_BadImageFormatException(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_BadImageFormatException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
    /// Initializes a new instance of the BadImageFormatException class with a specified error message and a reference
    /// to the inner exception that is the cause of this exception.
    /// @param message The error message that explains the reason for the exception.
    /// @param innerException The exception that is the cause of the current exception. If the inner parameter is not
    /// a null reference, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_BadImageFormatException(const String& message, const Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_BadImageFormatException, CODEPORTING_ARGS(const String& message, const Exception& innerException), CODEPORTING_ARGS(message, innerException));
    /// Initializes a new instance of the BadImageFormatException class with a specified error message and file name.
    /// @param message A message that describes the error.
    /// @param fileName The full name of the file with the invalid image.
    ASPOSECPP_SHARED_API Details_BadImageFormatException(const String& message, const String& fileName);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_BadImageFormatException, CODEPORTING_ARGS(const String& message, const String& fileName), CODEPORTING_ARGS(message, fileName));
    /// Initializes a new instance of the BadImageFormatException class with a specified error message and a reference
    /// to the inner exception that is the cause of this exception.
    /// @param message The error message that explains the reason for the exception.
    /// @param fileName The full name of the file with the invalid image.
    /// @param innerException The exception that is the cause of the current exception. If the inner parameter is not
    /// null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_BadImageFormatException(const String& message, const String& fileName,
                                                         const Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_BadImageFormatException,
        CODEPORTING_ARGS(const String& message, const String& fileName, const Exception& innerException),
        CODEPORTING_ARGS(message, fileName, innerException)
    );
    /// @see System::Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

private:
    /// Default message content
    static const String s_default_message;
    /// Selects the default message if the message argument is null.
    /// @param message The message argument.
    /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
    static const String& DefaultMessageIfNull(const String& message);
};

/// The exception that is thrown when the file image of a dynamic link library (DLL) or an executable program is
/// invalid.
/// Never wrap the BadImageFormatException class instances into System::SmartPtr.
using BadImageFormatException = System::ExceptionWrapper<Details_BadImageFormatException>;
} // namespace System
