/// @file system/text/encoder_fallback_exception.h
#ifndef _aspose_system_text_encoder_fallback_exception_h_
#define _aspose_system_text_encoder_fallback_exception_h_

#include "system/exceptions.h"

namespace System { namespace Text {

/// Exception thrown by EncoderExceptionFallback when encoding fails.
/// Never create instances of this class manually. Use the EncoderFallbackException class instead.
/// Never wrap the EncoderFallbackException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_EncoderFallbackException : public System::Details_ArgumentException
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;

    typedef System::Details_ArgumentException BaseType;

public:
    /// Gets character that triggered error.
    /// @return Character that broke encoding.
    char_t get_CharUnknown() { return m_charUnknown;  };
    /// Gets high character of pair that triggered error.
    /// @return High character from the pair that broke encoding.
    char_t get_CharUnknownHigh() { return m_charUnknownHigh; };
    /// Gets low character of pair that triggered error.
    /// @return Low character from the pair that broke encoding.
    char_t get_CharUnknownLow() { return m_charUnknownLow;  };
    /// Gets position of character that triggered error in input array.
    /// @return Index of erroneous character in input array.
    int get_Index() { return m_index; };

protected:
    /// Default constructor.
    ASPOSECPP_SHARED_API Details_EncoderFallbackException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_EncoderFallbackException, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Constructor.
    /// @param message Message to throw.
    ASPOSECPP_SHARED_API Details_EncoderFallbackException(const System::String &message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_EncoderFallbackException, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message));

    /// Constructor.
    /// @param message Message to throw.
    /// @param innerException Wrapped exception.
    ASPOSECPP_SHARED_API Details_EncoderFallbackException(const System::String &message, const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_EncoderFallbackException, CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException));

    /// Constructor.
    /// @param message Message to throw.
    /// @param charUnknown Character which triggered the error.
    /// @param index Index of character that triggered error.
    ASPOSECPP_SHARED_API Details_EncoderFallbackException(const System::String &message, char_t charUnknown, int index);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_EncoderFallbackException, CODEPORTING_ARGS(const System::String &message, char_t charUnknown, int index), CODEPORTING_ARGS(message, charUnknown, index));

    /// Constructor.
    /// @param message Message to throw.
    /// @param charUnknownHigh High part of surrogate pair that triggered error.
    /// @param charUnknownLow Low part of surrogate pair that triggered error.
    /// @param index Index of character that triggered error.
    ASPOSECPP_SHARED_API Details_EncoderFallbackException(const System::String &message, char_t charUnknownHigh, char_t charUnknownLow, int index);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_EncoderFallbackException, CODEPORTING_ARGS(const System::String &message, char_t charUnknownHigh, char_t charUnknownLow, int index), CODEPORTING_ARGS(message, charUnknownHigh, charUnknownLow, index));

    /// Throws exception instance wrapped by exception wrapper.
    /// @param self Exception instance to be thrown.
    [[noreturn]] ASPOSECPP_SHARED_API void DoThrow(const System::ExceptionPtr& self) const override;

    /// Unknown character.
    char_t m_charUnknown = char_t();
    /// High character from unknown pair.
    char_t m_charUnknownHigh = char_t();
    /// Low character from unknown pair.
    char_t m_charUnknownLow = char_t();
    /// Index of character that triggered error in input array.
    int m_index = 0;
};

using EncoderFallbackException = System::ExceptionWrapper<Details_EncoderFallbackException>;
}}

#endif
