/// @file system/details_exception_with_filename.h

#pragma once

#include <type_traits>
#include "system/exception.h"
#include "system/environment.h"

namespace System {
/// The template class for an exception with a file name.
/// @tparam T An exception base class.
template <typename T, typename = std::enable_if<std::is_base_of<Exception, T>::value>>
class Details_ExceptionWithFilename : public T
{
    String m_fileName;

protected:
    /// Initializes a new instance with an empty file name.
    Details_ExceptionWithFilename() : T(), m_fileName(nullptr) {}
    /// Initializes a new instance with a specified error message and an empty file name.
    /// @param message The error message that explains the reason for the exception.
    Details_ExceptionWithFilename(const String& message) : T(message), m_fileName(nullptr) {}
    /// Initializes a new instance with a specified error message, a reference to the inner exception that is the cause
    /// of this exception, and an empty file name.
    /// @param message The error message that explains the reason for the exception.
    /// @param innerException The exception that is the cause of the current exception.
    Details_ExceptionWithFilename(const String& message, const Exception& innerException)
        : T(message, innerException), m_fileName(nullptr) {};
    /// Initializes a new instance with a specified error message and a specified filename.
    /// @param message The error message that explains the reason for the exception.
    /// @param fileName The full name of the file with the invalid image.
    Details_ExceptionWithFilename(const String& message, const String& fileName) : T(message), m_fileName(fileName) {}
    /// Initializes a new instance with a specified error message, a reference to the inner exception that is the cause
    /// of this exception, and a specified file name.
    /// @param message The error message that explains the reason for the exception.
    /// @param fileName The full name of the file with the invalid image.
    /// @param innerException The exception that is the cause of the current exception.
    Details_ExceptionWithFilename(const String& message, const String& fileName, const Exception& innerException)
        : T(message, innerException), m_fileName(fileName) {}
    /// @see System::Exception::ExtraDescription
    virtual String ExtraDescription() const override
    {
        return m_fileName;
    }

public:
    /// Gets the name of the file that causes this exception.
    virtual String get_FileName() const
    {
        return m_fileName;
    }
    /// @see System::Exception::get_Message
    virtual String get_Message() const override
    {
        return T::m_message;
    }
    /// @see System::Exception::ToString
    virtual String ToString() const override
    {
        String result = T::ToString();
        if (!m_fileName.IsNullOrEmpty())
        {
            result += System::Environment::get_NewLine() + u"Filename: '" + m_fileName + u"'";
        }
        return result;
    }
};
} // namespace System
