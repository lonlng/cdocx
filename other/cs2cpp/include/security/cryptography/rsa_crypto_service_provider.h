/// @file security/cryptography/rsa_crypto_service_provider.h
#pragma once

#include <system/io/stream.h>

#include <security/cryptography/rsa.h>
#include <security/cryptography/i_csp_asymmetric_algorithm.h>
#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

namespace Details {
    struct RSACryptoServiceProviderPimpl;
    struct RSAPKCS1SignatureFormatterPimpl;
    struct RSAPKCS1SignatureDeformatterPimpl;
}

/// RSA algorithm in CSP form.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RSACryptoServiceProvider final : public RSA, public ICspAsymmetricAlgorithm
{
    /// Pointer implementation friendship.
    friend struct Details::RSAPKCS1SignatureFormatterPimpl;
    /// Pointer implementation friendship.
    friend struct Details::RSAPKCS1SignatureDeformatterPimpl;

    /// This type.
    typedef RSACryptoServiceProvider ThisType;
    /// Parent type 1.
    typedef RSA BaseType;
    /// Parent type 2.
    typedef ICspAsymmetricAlgorithm BaseType1;
    /// Parent types information.
    typedef System::BaseTypesInfo<BaseType, BaseType1> ThisBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructor. Uses default parameters.
    ASPOSECPP_SHARED_API RSACryptoServiceProvider();

    /// Constructor. Not implemented.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API RSACryptoServiceProvider(const SharedPtr<CspParameters>& parameters);

    /// Constructor.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API RSACryptoServiceProvider(const RSAParameters& parameters);

    /// Constructor.
    /// @param key_size Key size in bits.
    ASPOSECPP_SHARED_API RSACryptoServiceProvider(int32_t key_size);

    /// Constructor. Not implemented.
    /// @param key_size Key size in bits.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API RSACryptoServiceProvider(int32_t key_size, const SharedPtr<CspParameters>& parameters);

    /// Gets a CspKeyContainerInfo object.
    ASPOSECPP_SHARED_API SharedPtr<CspKeyContainerInfo> get_CspKeyContainerInfo() override;

    /// Checks key exchange algorithm associated with object.
    /// @return Key exchange algorithm name.
    ASPOSECPP_SHARED_API String get_KeyExchangeAlgorithm() override;

    /// Gets key size used by algorithm.
    /// @return Key size in bits.
    ASPOSECPP_SHARED_API int32_t get_KeySize() override;

    /// Checks whether key is persisted in CSP object.
    /// @return True if key is persisted, false otherwise.
    ASPOSECPP_SHARED_API bool get_PersistKeyInCsp() const;

    /// Defines whether key is persisted in CSP object.
    /// @param value True to persist the key, false otherwise.
    ASPOSECPP_SHARED_API void set_PersistKeyInCsp(bool value);

    /// Checks if public key only is present in CSP object.
    /// @return True if public key is present and private one is not, false otherwise.
    ASPOSECPP_SHARED_API bool get_PublicOnly() const;

    /// Gets signature algorithm associated with CSP object.
    /// @return Signature algorithm name.
    ASPOSECPP_SHARED_API String get_SignatureAlgorithm() override;

    /// Checks whether the key persists in machine store instead of user store.
    /// @return True if the key should be persisted in machine store, false if it should be persisted in user store.
    static ASPOSECPP_SHARED_API bool get_UseMachineKeyStore();

    /// Defines whether the key persists in machine store instead of user store.
    /// @param value True if the key should be persisted in machine store, false if it should be persisted in user store.
    static ASPOSECPP_SHARED_API void set_UseMachineKeyStore(bool value);

    /// Decrypts message. Not implemented.
    /// @param rgb Data to decrypt.
    /// @param use_oaep True to use OAEP padding, false to use PKCS#1 v1.5 padding.
    /// @return Decrypted data array.
    ASPOSECPP_SHARED_API ByteArrayPtr Decrypt(const ByteArrayPtr& rgb, bool use_oaep);

    /// Decrypts input data using the specified padding mode.
    /// @param data Byte array to decrypt.
    /// @param padding Padding mode.
    /// @return Decrypted data in byte array format.
    ASPOSECPP_SHARED_API ByteArrayPtr Decrypt(ByteArrayPtr data, SharedPtr<RSAEncryptionPadding> padding) override;

    /// Encrypts message. Not implemented.
    /// @param rgb Data to encrypt.
    /// @param use_oaep True to use OAEP padding, false to use PKCS#1 v1.5 padding.
    /// @return Encrypted data array.
    ASPOSECPP_SHARED_API ByteArrayPtr Encrypt(const ByteArrayPtr& rgb, bool use_oaep);

    /// Encrypts input data using the specified padding mode.
    /// @param data Byte array to encrypt.
    /// @param padding Padding mode.
    /// @return Encrypted data in byte array format.
    ASPOSECPP_SHARED_API ByteArrayPtr Encrypt(ByteArrayPtr data, SharedPtr<RSAEncryptionPadding> padding) override;

    /// Exports blob with information on key. Not implemented.
    /// @param include_private_parameters Whether to include private key parameters in blob.
    /// @return Blob with key information.
    ASPOSECPP_SHARED_API ByteArrayPtr ExportCspBlob(bool include_private_parameters) override;

    /// Exports CSP parameters.
    /// @param include_private_parameters Whether to include private key parameters in blob.
    /// @return Data structure with CSP parameters.
    ASPOSECPP_SHARED_API RSAParameters ExportParameters(bool include_private_parameters) override;

    /// Imports blob with information on key. Not implemented.
    /// @param key_blob Previously exported blob with key information.
    ASPOSECPP_SHARED_API void ImportCspBlob(ByteArrayPtr key_blob) override;

    /// Imports CSP parameters.
    /// @param parameters Data structure with CSP parameters.
    ASPOSECPP_SHARED_API void ImportParameters(RSAParameters parameters) override;

    /// Computes the signature of specified input value.
    /// @param buffer Buffer to read input data from.
    /// @param halg Hash algorithm to use.
    /// @return RSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& buffer, const SharedPtr<Object>& halg);

    /// Computes the signature of specified input value.
    /// @param input_stream Stream to read data being signed from.
    /// @param halg Hash algorithm to use.
    /// @return RSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const SharedPtr<IO::Stream>& input_stream, const SharedPtr<Object>& halg);

    /// Computes the signature of specified input value.
    /// @param buffer Buffer to read input data from.
    /// @param offset Input buffer slice beginning index.
    /// @param count Input buffer slice size.
    /// @param halg Hash algorithm to use.
    /// @return RSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& buffer, int32_t offset, int32_t count, const SharedPtr<Object>& halg);

    /// Computes the signature for the specified hash value.
    /// @param hash Hash value.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return RSA signature for the specified hash.
    ASPOSECPP_SHARED_API ByteArrayPtr SignHash(ByteArrayPtr hash, HashAlgorithmName hash_algorithm,
        SharedPtr<RSASignaturePadding> padding) override;

    /// Computes the signature of specified input value. Not implemented.
    /// @param rgb_hash Hash value of data to be signed.
    /// @param str Hash algorithm identifier used to create the hash.
    /// @return RSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignHash(const ByteArrayPtr& rgb_hash, const String& str);

    /// Checks data signature.
    /// @param buffer Data to check signature for.
    /// @param halg Hash algorithm to use.
    /// @param signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& buffer, const SharedPtr<Object>& halg, const ByteArrayPtr& signature);

    /// Checks data signature.
    /// @param rgb_hash Hash calculated for received data.
    /// @param str Name of hash algorithm used.
    /// @param rgb_signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    ASPOSECPP_SHARED_API bool VerifyHash(const ByteArrayPtr& rgb_hash, const String& str, const ByteArrayPtr& rgb_signature);

    /// Verifies that the signature of the specified hash is valid.
    /// @param hash Hash value of the signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// @param padding Padding mode.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyHash(ByteArrayPtr hash, ByteArrayPtr signature, const HashAlgorithmName& hash_algorithm,
        SharedPtr<RSASignaturePadding> padding) override;

    /// Frees data associated with object.
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Computes the hash value of the specified data array using the specified hash algorithm.
    /// @param data Data to hash.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to hash.
    /// @param hash_algorithm Hash algorithm.
    /// @return Hashed data.
    ASPOSECPP_SHARED_API ByteArrayPtr HashData(ByteArrayPtr data, int32_t offset, int32_t count, HashAlgorithmName hash_algorithm) override;

    /// Computes the hash value of the specified binary stream using the specified hash algorithm.
    /// @param stream Bynary stream to hashed.
    /// @param hash_algorithm Hash algorithm.
    /// @return Hashed data.
    ASPOSECPP_SHARED_API ByteArrayPtr HashData(StreamPtr stream, HashAlgorithmName hash_algorithm) override;

private:
    /// Key size in bits.
    int32_t m_key_size;
    /// Whether the key is persisted in CSP object.
    bool m_persist_key_in_csp;
    /// True to use machine store for private key, false to use user store.
    static bool s_use_machine_key_store;
    /// Implementation.
    std::unique_ptr<Details::RSACryptoServiceProviderPimpl> m_pimpl;

    void VerifyNotDisposed() const;
    void VerifyPrivateKeyExists() const;
    void SetupLegalKeySizesValue();

    ByteArrayPtr SignHash(const ByteArrayPtr& hash_value, const SharedPtr<HashAlgorithm>& hash_algorithm);
    bool VerifyHash(const ByteArrayPtr& rgb_hash, const SharedPtr<HashAlgorithm>& hash_algorithm, const ByteArrayPtr& rgb_signature);
};

}}} // namespace System::Security::Cryptography
