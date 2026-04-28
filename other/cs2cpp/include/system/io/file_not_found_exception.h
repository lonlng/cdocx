/// @file system/io/file_not_found_exception.h

#pragma once

#include "system/details_exception_with_filename.h"

namespace System { namespace IO {
/// The exception that is thrown when an attempt to access a file that does not exist on disk fails.
/// Never create instances of this class manually. Use the FileNotFoundException class instead.
/// Never wrap the FileNotFoundException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_FileNotFoundException : public Details_ExceptionWithFilename<Details_IOException>
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = Details_ExceptionWithFilename<Details_IOException>;
    RTTI_INFO_NAMED(System::IO::Details_FileNotFoundException, "System::IO::FileNotFoundException",
                    ::System::BaseTypesInfo<System::Object>);

protected:
    /// Initializes a new instance of the FileNotFoundException class with its message string set to a
    /// system-supplied message.
    ASPOSECPP_SHARED_API Details_FileNotFoundException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_FileNotFoundException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Initializes a new instance of the FileNotFoundException class with a specified error message.
    /// @param message A description of the error. The content of message is intended to be understood by humans.
    /// The caller of this constructor is required to ensure that this string has been localized for the current
    /// system culture.
    ASPOSECPP_SHARED_API Details_FileNotFoundException(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_FileNotFoundException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
    /// Initializes a new instance of the FileNotFoundException class with a specified error message and
    /// a reference to the inner exception that is the cause of this exception.
    /// @param message A description of the error. The content of message is intended to be understood by humans.
    /// The caller of this constructor is required to ensure that this string has been localized for the current
    /// system culture.
    /// @param innerException The exception that is the cause of the current exception. If the innerException parameter
    /// is not null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_FileNotFoundException(const String& message, const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_FileNotFoundException, CODEPORTING_ARGS(const String& message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException));
    /// Initializes a new instance of the FileNotFoundException class with a specified error message, and the file name
    /// that cannot be found.
    /// @param message A description of the error, or null to use a system-supplied message with the given fileName.
    /// The content of message should be understood by humans. The caller of this constructor must ensure that this
    /// string has been localized for the current system culture.
    /// @param fileName The full name of the file with the invalid image.
    ASPOSECPP_SHARED_API Details_FileNotFoundException(const String& message, const String& fileName);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_FileNotFoundException, CODEPORTING_ARGS(const String& message, const String& fileName), CODEPORTING_ARGS(message, fileName));
    /// Initializes a new instance of the FileNotFoundException class with a specified error message, the file name
    /// that cannot be found, and a reference to the inner exception that is the cause of this exception.
    /// @param message The error message that explains the reason for the exception.
    /// @param fileName The full name of the file with the invalid image.
    /// @param innerException The exception that is the cause of the current exception. If the innerException parameter
    /// is not null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_FileNotFoundException(const String& message, const String& fileName,
                                                       const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_FileNotFoundException,
        CODEPORTING_ARGS(const String& message, const String& fileName, const System::Exception& innerException),
        CODEPORTING_ARGS(message, fileName, innerException)
    );
    /// @see Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

private:
    /// Default message content
    static const String s_default_message;
    /// Selects the default message if the message argument is null.
    /// @param message The message argument.
    /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
    static const String& DefaultMessageIfNull(const String& message);
};

/// The exception that is thrown when an attempt to access a file that does not exist on disk fails.
/// Never wrap the FileNotFoundException class instances into System::SmartPtr.
using FileNotFoundException = System::ExceptionWrapper<Details_FileNotFoundException>;
}} // namespace System::IO
