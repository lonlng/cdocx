/// @file security/cryptography/rsa.h
#pragma once

#include <system/io/stream.h>
#include <security/cryptography/asymmetric_algorithm.h>
#include <security/cryptography/rsa_encryption_padding.h>
#include <security/cryptography/rsa_signature_padding.h>
#include <security/cryptography/rsa_parameters.h>

namespace System { namespace Security { namespace Cryptography {

/// Base class for implementations of RSA algorithm.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT RSA : public AsymmetricAlgorithm
{
    /// This type.
    typedef RSA ThisType;
    /// Parent type.
    typedef AsymmetricAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Checks key exchange algorithm associated with object.
    /// @return Key exchange algorithm name.
    ASPOSECPP_SHARED_API String get_KeyExchangeAlgorithm() override;

    /// Gets signature algorithm associated with CSP object.
    /// @return Signature algorithm name.
    ASPOSECPP_SHARED_API String get_SignatureAlgorithm() override;

    /// Decrypts input data using the specified padding mode.
    /// @param data Byte array to decrypt.
    /// @param padding Padding mode.
    /// @return Decrypted data in byte array format.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr Decrypt(ByteArrayPtr data, SharedPtr<RSAEncryptionPadding> padding);

    /// Decrypts value using private key.
    /// @param rgb Byte array to decrypt.
    /// @return Decrypted data in byte array format.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr DecryptValue(ByteArrayPtr rgb);

    /// Encrypts input data using the specified padding mode.
    /// @param data Byte array to encrypt.
    /// @param padding Padding mode.
    /// @return Encrypted data in byte array format.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr Encrypt(ByteArrayPtr data, SharedPtr<RSAEncryptionPadding> padding);

    /// Encrypts value using private key.
    /// @param rgb Byte array to encrypt.
    /// @return Encrypted data in byte array format.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr EncryptValue(ByteArrayPtr rgb);

    /// Exports all parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    virtual ASPOSECPP_SHARED_API RSAParameters ExportParameters(bool include_private_parameters) = 0;

    /// Imports all parameters from data structure.
    /// @param parameters Structure to import parameters from.
    virtual ASPOSECPP_SHARED_API void ImportParameters(RSAParameters parameters) = 0;

    /// Initializes object using XML-encoded parameters.
    /// @param xml_string Parameters in XML format.
    ASPOSECPP_SHARED_API void FromXmlString(String xml_string) override;

    /// Exports all parameters in XML format.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return XML-encoded parameters.
    ASPOSECPP_SHARED_API String ToXmlString(bool include_private_parameters) override;

    /// Computes the hash value of the specified data array using the specified hash algorithm and padding, and signs the result.
    /// @param data Input data array.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return RSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Computes the hash value of the specified data array using the specified hash algorithm and padding, and signs the result.
    /// @param data Input data array.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to use as input data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return RSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Computes the hash value of the specified binary stream using the specified hash algorithm and padding, and signs the result.
    /// @param stream Binary stream.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return RSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const StreamPtr& stream, const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Computes the signature for the specified hash value.
    /// @param hash Hash value.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return RSA signature for the specified hash.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr SignHash(ByteArrayPtr hash, HashAlgorithmName hash_algorithm,
        SharedPtr<RSASignaturePadding> padding);

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to hash.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Verifies that the signature of the specified binary stream is valid.
    /// @param stream Signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const StreamPtr& stream, const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm,
        const SharedPtr<RSASignaturePadding>& padding);

    /// Verifies that the signature of the specified hash is valid.
    /// @param hash Hash value of the signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return true if signature is valid, otherwise - false.
    virtual ASPOSECPP_SHARED_API bool VerifyHash(ByteArrayPtr hash, ByteArrayPtr signature, const HashAlgorithmName& hash_algorithm,
        SharedPtr<RSASignaturePadding> padding);

    /// Creates default RSA aglorithm implementation.
    static ASPOSECPP_SHARED_API SharedPtr<RSA> Create();

    /// Creates default RSA algorithm implementation.
    /// @param alg_name Must be "System.Security.Cryptography.RSACryptoServiceProvider".
    static ASPOSECPP_SHARED_API SharedPtr<RSA> Create(const String& alg_name);

    /// Creates default RSA algorithm implementation with specifed key size.
    /// @param key_size_in_bits The key size, in bits.
    static ASPOSECPP_SHARED_API SharedPtr<RSA> Create(int32_t key_size_in_bits);

    /// Creates default RSA algorithm implementation with specifed parameters.
    /// @param parameters The parameters for the RSA algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSA> Create(const RSAParameters& parameters);

    /// Creates default RSA algorithm implementation with specifed XML-encoded parameters.
    /// @param xml_string The parameters for the RSA algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSA> CreateFromXmlString(const String& xml_string);

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API RSA();

    /// Computes the hash value of the specified data array using the specified hash algorithm.
    /// @param data Data to hash.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to hash.
    /// @param hash_algorithm Hash algorithm.
    /// @return Hashed data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr HashData(ByteArrayPtr data, int32_t offset, int32_t count, HashAlgorithmName hash_algorithm);

    /// Computes the hash value of the specified binary stream using the specified hash algorithm.
    /// @param stream Bynary stream to hashed.
    /// @param hash_algorithm Hash algorithm.
    /// @return Hashed data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr HashData(StreamPtr stream, HashAlgorithmName hash_algorithm);
};

}}} // namespace System::Security::Cryptography
