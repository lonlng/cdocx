/// @file security/cryptography/hash_algorithm.h
#ifndef _aspose_cryptography_hash_algorithm_h_
#define _aspose_cryptography_hash_algorithm_h_

#include "i_crypto_transform.h"
#include "system/exceptions.h"
#include "system/array.h"
#include "system/io/stream.h"

#ifdef ASPOSECPPLIB_BEING_BUILT
#include <botan/hash.h>
#else
#include <cstdint>
#endif


namespace Botan {
    /// Hash function type forward declaration.
    ASPOSECPP_3RD_PARTY_CLASS(HashFunction);
}


namespace System{ namespace Security{ namespace Cryptography{

/// Base class for hashing algorithms.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT HashAlgorithm : public ICryptoTransform
{
public:
    /// Destructor.
    virtual ASPOSECPP_SHARED_API ~HashAlgorithm();

    /// Hashes buffer.
    /// @param buffer Source buffer.
    /// @return Calculated hash value.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> ComputeHash(const ArrayPtr<uint8_t>& buffer);
    /// Hashes buffer slice.
    /// @param buffer Source buffer.
    /// @param offset Offset in the source buffer.
    /// @param count Number of bytes to use from the source buffer.
    /// @return Calculated hash value.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> ComputeHash(const ArrayPtr<uint8_t>& buffer, int offset, int count);
    /// Reads stream until end and calculates hash for the data read.
    /// @param inputStream Stream to read data from.
    /// @return Calculated hash value for the whole stream data.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> ComputeHash(SharedPtr<IO::Stream> const& inputStream);
    /// Creates hash algorithm based on name.
    /// @param hashName One of the following values: "MD5", "SHA1", "SHA256", "SHA384", "SHA512", "RIPEMD160" or any of them with "System.Security.Cryptography." prefix.
    static ASPOSECPP_SHARED_API SharedPtr<HashAlgorithm> Create(const String& hashName);

    /// Resets hasher into initial state.
    ASPOSECPP_SHARED_API virtual void Initialize();
    /// Gets value of calculated hash code.
    /// @return Hash code value.
    ASPOSECPP_SHARED_API virtual ArrayPtr<uint8_t> get_Hash();
    /// Gets size of calculated hash value in bytes.
    /// @return Number of bytes in calculated hash value.
    ASPOSECPP_SHARED_API virtual int get_HashSize();
    /// Processes block of data and copies data to output array.
    /// @param inputBuffer Buffer to read data from.
    /// @param inputOffset Input buffer offset.
    /// @param inputCount Number of bytes to process.
    /// @param outputBuffer Output buffer to copy data into; nullptr to do no copying.
    /// @param outputOffset Output buffer offset.
    /// @return Number of bytes written.
    ASPOSECPP_SHARED_API int TransformBlock(ArrayPtr<uint8_t> inputBuffer, int inputOffset, int inputCount, ArrayPtr<uint8_t> outputBuffer, int outputOffset) override;
    /// Processes last block of data and calculates hash.
    /// @param inputBuffer Buffer to read data from.
    /// @param inputOffset Input buffer offset.
    /// @param inputCount Number of bytes to process.
    /// @return Hash calculated for the whole data sequence.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> TransformFinalBlock(ArrayPtr<uint8_t> inputBuffer, int inputOffset, int inputCount) override;

    /// Input block size.
    /// @return Number of bytes in input block.
    ASPOSECPP_SHARED_API int get_InputBlockSize() override;
    /// Output block size.
    /// @return Number of bytes in output block.
    ASPOSECPP_SHARED_API int get_OutputBlockSize() override;

protected:
    /// Size of computed hash code, in bits.
    int HashSizeValue; // please don't replace it with m_hash_size_value because it corresponds to C# protected field.

    /// Constructor.
    ASPOSECPP_SHARED_API HashAlgorithm();
    /// Constructor.
    /// @param hash_function Hash function to use.
    ASPOSECPP_SHARED_API HashAlgorithm( std::unique_ptr<Botan::HashFunction> hash_function );

    /// Passes data which is written into the object to the actual hash algorithm.
    /// @param array Data to pass to hash algorithm.
    /// @param ibStart Data offset.
    /// @param cbSize Data size.
    ASPOSECPP_SHARED_API virtual void HashCore(System::ArrayPtr<uint8_t> array, int32_t ibStart, int32_t cbSize);
    /// Finishes hash calculation.
    /// @return Hash code calculated by algorithm.
    ASPOSECPP_SHARED_API virtual System::ArrayPtr<uint8_t> HashFinal();

private:
    /// Hash function to wrap.
    std::unique_ptr<Botan::HashFunction> m_bt_hash_function;
    /// Calculated hash value.
    std::vector<uint8_t> m_hash_value;
};


}}}// namespace System{ namespace Security{ namespace Cryptography{

#endif // hash_algorithm_h
