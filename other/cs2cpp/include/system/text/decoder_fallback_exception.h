/// @file system/text/decoder_fallback_exception.h
#ifndef _aspose_system_text_decoder_fallback_exception_h_
#define _aspose_system_text_decoder_fallback_exception_h_

#include "system/array.h"
#include "system/exceptions.h"

namespace System { namespace Text {

/// Exception thrown by DecoderExceptionFallback when decoding fails.
/// Never create instances of this class manually. Use the DecoderFallbackException class instead.
/// Never wrap the DecoderFallbackException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_DecoderFallbackException : public System::Details_ArgumentException
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;

    typedef System::Details_ArgumentException BaseType;

public:
    /// Gets byte array that triggered error.
    /// @return Byte array that broke decoding.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> get_BytesUnknown();
    /// Gets position of byte that triggered error in input array.
    /// @return Index of erroneous byte in input array.
    ASPOSECPP_SHARED_API int get_Index();

protected:
    /// Default constructor.
    ASPOSECPP_SHARED_API Details_DecoderFallbackException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_DecoderFallbackException, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Constructor.
    /// @param message Message to throw.
    ASPOSECPP_SHARED_API Details_DecoderFallbackException(const System::String &message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_DecoderFallbackException, CODEPORTING_ARGS(const System::String &message), CODEPORTING_ARGS(message));

    /// Constructor.
    /// @param message Message to throw.
    /// @param bytesUnknown Array of bytes which triggered the error.
    /// @param index Index of byte that triggered error.
    ASPOSECPP_SHARED_API Details_DecoderFallbackException(const System::String &message, const ArrayPtr<uint8_t>& bytesUnknown, int index);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_DecoderFallbackException, CODEPORTING_ARGS(const System::String &message, const ArrayPtr<uint8_t>& bytesUnknown, int index), CODEPORTING_ARGS(message, bytesUnknown, index));

    /// Constructor.
    /// @param message Message to throw.
    /// @param innerException Wrapped exception.
    ASPOSECPP_SHARED_API Details_DecoderFallbackException(const System::String &message, const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_DecoderFallbackException, CODEPORTING_ARGS(const System::String &message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException));

    /// Throws exception instance wrapped by exception wrapper.
    /// @param self Exception instance to be thrown.
    [[noreturn]] ASPOSECPP_SHARED_API void DoThrow(const System::ExceptionPtr& self) const override;

    /// Array of bytes that triggered decoder error.
    System::ArrayPtr<uint8_t>  m_bytesUnknown;
    /// Index of byte that triggered error in input array.
    int m_index = 0;
};

using DecoderFallbackException = System::ExceptionWrapper<Details_DecoderFallbackException>;
}}

#endif
