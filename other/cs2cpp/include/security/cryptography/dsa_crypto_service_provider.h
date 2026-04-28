/// @file security/cryptography/dsa_crypto_service_provider.h
#pragma once

#include <security/cryptography/dsa.h>
#include <security/cryptography/i_csp_asymmetric_algorithm.h>
#include <memory>

namespace System { namespace Security { namespace Cryptography {

namespace Details { struct DSACryptoServiceProviderPimpl; }

/// DSA algorithm in CSP form.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DSACryptoServiceProvider final : public DSA, public ICspAsymmetricAlgorithm
{
    /// This type.
    typedef DSACryptoServiceProvider ThisType;
    /// Parent type 1.
    typedef DSA BaseType;
    /// Parent type 2.
    typedef ICspAsymmetricAlgorithm BaseType1;
    /// Parent types information.
    typedef System::BaseTypesInfo<BaseType, BaseType1> ThisBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    using DSA::SignData;
    using DSA::VerifyData;

    /// Constructor. Uses default parameters.
    ASPOSECPP_SHARED_API DSACryptoServiceProvider();

    /// Constructor.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API DSACryptoServiceProvider(const DSAParameters& parameters);

    /// Constructor. Not implemented.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API DSACryptoServiceProvider(const SharedPtr<CspParameters>& parameters);

    /// Constructor.
    /// @param key_size Key size in bits.
    ASPOSECPP_SHARED_API DSACryptoServiceProvider(int32_t key_size);

    /// Constructor. Not implemented.
    /// @param key_size Key size in bits.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API DSACryptoServiceProvider(int32_t key_size, const SharedPtr<CspParameters>& parameters);

    /// Gets a CspKeyContainerInfo object.
    ASPOSECPP_SHARED_API SharedPtr<CspKeyContainerInfo> get_CspKeyContainerInfo() override;

    /// Checks whether key is persisted in CSP object.
    /// @return True if key is persisted, false otherwise.
    ASPOSECPP_SHARED_API bool get_PersistKeyInCsp() const;

    /// Defines whether key is persisted in CSP object.
    /// @param value True to persist the key, false otherwise.
    ASPOSECPP_SHARED_API void set_PersistKeyInCsp(bool value);

    /// Checks if public key only is present in CSP object.
    /// @return True if public key is present and private one is not, false otherwise.
    ASPOSECPP_SHARED_API bool get_PublicOnly() const;

    /// Checks whether the key persists in machine store instead of user store.
    /// @return True if the key should be persisted in machine store, false if it should be persisted in user store.
    static ASPOSECPP_SHARED_API bool get_UseMachineKeyStore();

    /// Defines whether the key persists in machine store instead of user store.
    /// @param value True if the key should be persisted in machine store, false if it should be persisted in user store.
    static ASPOSECPP_SHARED_API void set_UseMachineKeyStore(bool value);

    /// Checks key exchange algorithm associated with object.
    /// @return Key exchange algorithm name.
    ASPOSECPP_SHARED_API String get_KeyExchangeAlgorithm() override;

    /// Gets key size.
    /// @return Size of the key to use.
    ASPOSECPP_SHARED_API int32_t get_KeySize() override;

    /// Gets signature algorithm to use.
    /// @return Algorithm name.
    ASPOSECPP_SHARED_API String get_SignatureAlgorithm() override;

    /// Create DSA signature for the specified data.
    /// @param rgb_hash Data to be signed.
    /// @return DSA signature.
    ASPOSECPP_SHARED_API ByteArrayPtr CreateSignature(ByteArrayPtr rgb_hash) override;

    /// Verify DSA signature for the specified data.
    /// @param rgb_hash Data signed with @p rgb_signature.
    /// @param rgb_signature DSA signature.
    /// @return true - if @p rgb_signature matches the DSA signature computed on @p rgb_hash, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifySignature(ByteArrayPtr rgb_hash, ByteArrayPtr rgb_signature) override;

    /// Exports blob with information on key. Not implemented.
    /// @param include_private_parameters Whether to include private key parameters in blob.
    /// @return Blob with key information.
    ASPOSECPP_SHARED_API ByteArrayPtr ExportCspBlob(bool include_private_parameters) override;

    /// Exports CSP parameters.
    /// @param include_private_parameters Whether to include private key parameters in blob.
    /// @return Data structure with CSP parameters.
    ASPOSECPP_SHARED_API DSAParameters ExportParameters(bool include_private_parameters) override;

    /// Imports blob with information on key. Not implemented.
    /// @param key_blob Previously exported blob with key information.
    ASPOSECPP_SHARED_API void ImportCspBlob(ByteArrayPtr key_blob) override;

    /// Imports all parameters from data structure.
    /// @param parameters Structure to import parameters from.
    ASPOSECPP_SHARED_API void ImportParameters(DSAParameters parameters) override;

    /// Computes the signature of specified input value.
    /// @param buffer Buffer to read input data from.
    /// @return DSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& buffer);

    /// Computes the signature of specified input value.
    /// @param input_stream Stream to read data being signed from.
    /// @return DSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const SharedPtr<IO::Stream>& input_stream);

    /// Computes the signature of specified input value.
    /// @param buffer Buffer to read input data from.
    /// @param offset Input buffer slice beginning index.
    /// @param count Input buffer slice size.
    /// @return DSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& buffer, int32_t offset, int32_t count);

    /// Computes the signature of specified input value.
    /// @param rgb_hash Hash value of data to be signed.
    /// @param str Hash algorithm identifier used to create the hash.
    /// @return DSA signature for specified data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignHash(const ByteArrayPtr& rgb_hash, const String& str);

    /// Checks data signature.
    /// @param buffer Data to check signature for.
    /// @param signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& buffer, const ByteArrayPtr& signature);

    /// Checks data signature.
    /// @param rgb_hash Hash calculated for received data.
    /// @param str Name of hash algorithm used.
    /// @param rgb_signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    ASPOSECPP_SHARED_API bool VerifyHash(const ByteArrayPtr& rgb_hash, const String& str, const ByteArrayPtr& rgb_signature);

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
    /// Whether the key is persisted in CSP object.
    bool m_persist_key_in_csp = false;
    /// True to use machine store for private key, false to use user store.
    static bool s_use_machine_key_store;

    /// Implementation.
    std::unique_ptr<Details::DSACryptoServiceProviderPimpl> m_pimpl;

    ASPOSECPP_SHARED_API ~DSACryptoServiceProvider();

    void VerifyNotDisposed() const;
    void VerifyPrivateKeyExists() const;
    void SetupLegalKeySizesValue();
};

}}} // namespace System::Security::Cryptography
