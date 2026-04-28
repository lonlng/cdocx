/// @file security/cryptography/base64_transforms.h
#pragma once
#include <cstdint>
#include <security/cryptography/i_crypto_transform.h>
#include <system/array.h>

namespace System { namespace Security { namespace Cryptography {

/// Specifies whether white space should be ignored in the base 64 transformation
enum class FromBase64TransformMode
{
    /// White space should be ignored
    IgnoreWhiteSpaces = 0,
    /// White space should not be ignored.
    DoNotIgnoreWhiteSpaces = 1
};

/// Converts the CryptoStream class instance to base 64.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ToBase64Transform : public System::Security::Cryptography::ICryptoTransform
{
public:
    /// Input block size.
    /// @return Number of bytes in input block.
    ASPOSECPP_SHARED_API int32_t get_InputBlockSize();
    /// Output block size.
    /// @return Number of bytes in output block.
    ASPOSECPP_SHARED_API int32_t get_OutputBlockSize();
    /// Gets a value indicating whether multiple blocks can be transformed.
    ASPOSECPP_SHARED_API bool get_CanTransformMultipleBlocks();
    /// Gets a value indicating whether the current transform can be reused.
    ASPOSECPP_SHARED_API virtual bool get_CanReuseTransform();
    /// Processes block of data and copies data to output array.
    /// @param inputBuffer Buffer to read data from.
    /// @param inputOffset Input buffer offset.
    /// @param inputCount Number of bytes to process.
    /// @param outputBuffer Output buffer to copy data into; nullptr to do no copying.
    /// @param outputOffset Output buffer offset.
    /// @return Number of bytes written.
    ASPOSECPP_SHARED_API int32_t TransformBlock(System::ArrayPtr<uint8_t> inputBuffer, int32_t inputOffset,
                                                int32_t inputCount, System::ArrayPtr<uint8_t> outputBuffer,
                                                int32_t outputOffset);
    /// Processes last block of data and calculates output value.
    /// @param inputBuffer Buffer to read data from.
    /// @param inputOffset Input buffer offset.
    /// @param inputCount Number of bytes to process.
    /// @return Output calculated for the whole input sequence.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> TransformFinalBlock(System::ArrayPtr<uint8_t> inputBuffer,
                                                                       int32_t inputOffset, int32_t inputCount);
    /// Releases operating system resources acquired by the current object.
    ASPOSECPP_SHARED_API void Dispose();
    /// Releases all resources.
    ASPOSECPP_SHARED_API void Clear();
    /// Destructor.
    ASPOSECPP_SHARED_API virtual ~ToBase64Transform();

protected:
    ASPOSECPP_SHARED_API virtual void Dispose(bool disposing);
};

/// Converts the CryptoStream class instance from base 64.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS FromBase64Transform : public System::Security::Cryptography::ICryptoTransform
{
public:
    /// Input block size.
    /// @return Number of bytes in input block.
    ASPOSECPP_SHARED_API int32_t get_InputBlockSize();
    /// Output block size.
    /// @return Number of bytes in output block.
    ASPOSECPP_SHARED_API int32_t get_OutputBlockSize();
    /// Gets a value indicating whether multiple blocks can be transformed.
    ASPOSECPP_SHARED_API bool get_CanTransformMultipleBlocks();
    /// Gets a value indicating whether the current transform can be reused.
    ASPOSECPP_SHARED_API virtual bool get_CanReuseTransform();
    /// Constructor.
    ASPOSECPP_SHARED_API FromBase64Transform();
    /// Constructor.
    /// @param whitespaces Specifies whether white space handling mode
    ASPOSECPP_SHARED_API FromBase64Transform(FromBase64TransformMode whitespaces);

    ASPOSECPP_SHARED_API int32_t TransformBlock(System::ArrayPtr<uint8_t> inputBuffer, int32_t inputOffset,
                                                int32_t inputCount, System::ArrayPtr<uint8_t> outputBuffer,
                                                int32_t outputOffset);
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> TransformFinalBlock(System::ArrayPtr<uint8_t> inputBuffer,
                                                                       int32_t inputOffset, int32_t inputCount);
    /// Releases operating system resources acquired by the current object.
    ASPOSECPP_SHARED_API void Dispose();
    /// Releases all resources.
    ASPOSECPP_SHARED_API void Clear();

    /// Destructor.
    ASPOSECPP_SHARED_API virtual ~FromBase64Transform();

protected:
    ASPOSECPP_SHARED_API virtual void Dispose(bool disposing);

private:
    System::ArrayPtr<uint8_t> _inputBuffer;
    int32_t _inputIndex;
    FromBase64TransformMode _whitespaces;

    System::ArrayPtr<uint8_t> DiscardWhiteSpaces(System::ArrayPtr<uint8_t> inputBuffer, int32_t inputOffset,
                                                 int32_t inputCount);
    void Reset();
};

}}} // namespace System::Security::Cryptography
