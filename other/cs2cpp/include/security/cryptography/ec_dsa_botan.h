/// @file security/cryptography/ec_dsa_botan.h
#pragma once

#include <security/cryptography/ec_dsa.h>
#include <security/cryptography/ec_key_xml_format.h>
#include <security/cryptography/hash_algorithm_name.h>
#include <memory>

namespace Botan {

class ECDSA_PublicKey;
class ECDSA_PrivateKey;

} // namespace Botan

namespace System { namespace Security { namespace Cryptography {

/// ECDsa algorithm in Botan form.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ECDsaBotan final : public ECDsa
{
    /// This type.
    typedef ECDsaBotan ThisType;
    /// Parent type.
    typedef ECDsa BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    using ECDsa::SignData;
    using ECDsa::VerifyData;

    /// Constructor. Uses default parameters.
    ASPOSECPP_SHARED_API ECDsaBotan();

    /// Constructor.
    /// @param parameters Algorithm parameters.
    ASPOSECPP_SHARED_API ECDsaBotan(const ECParameters& parameters);

    /// Constructor.
    /// @param curve Curve used to create the public/private key pair.
    ASPOSECPP_SHARED_API ECDsaBotan(const ECCurve& curve);

    /// Constructor.
    /// @param key_size Key size in bits.
    ASPOSECPP_SHARED_API ECDsaBotan(int32_t key_size);

    /// Constructor.
    /// @param key Botan public key.
    ASPOSECPP_SHARED_API ECDsaBotan(const Botan::ECDSA_PublicKey& key);

    /// Constructor.
    /// @param key Botan private key.
    ASPOSECPP_SHARED_API ECDsaBotan(const Botan::ECDSA_PrivateKey& key);

    /// Sets key size.
    /// @param value Size of the key to use.
    ASPOSECPP_SHARED_API void set_KeySize(int32_t value) override;

    /// Gets hash algortihm.
    /// @return Hash algorithm name.
    ASPOSECPP_SHARED_API HashAlgorithmName get_HashAlgorithm() const;

    /// Sets hash algortihm.
    /// @param value Hash algorithm name.
    ASPOSECPP_SHARED_API void set_HashAlgorithm(const HashAlgorithmName& value);

    /// Exports explicit parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    ASPOSECPP_SHARED_API ECParameters ExportExplicitParameters(bool include_private_parameters) override;

    /// Exports named or explicit parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    ASPOSECPP_SHARED_API ECParameters ExportParameters(bool include_private_parameters) override;

    /// Initializes object using XML-encoded parameters. Not implemented.
    /// @param xml_string Parameters in XML format.
    ASPOSECPP_SHARED_API void FromXmlString(String xml_string) override;

    /// Initializes object using XML-encoded parameters. Not implemented.
    /// @param xml_string Parameters in XML format.
    /// @param format Format of the XML string.
    ASPOSECPP_SHARED_API void FromXmlString(const String& xml_string, ECKeyXmlFormat format);

    /// Generates a new public/private key pair for the specified curve.
    /// @param curve Curve to use to generate the keys.
    ASPOSECPP_SHARED_API void GenerateKey(const ECCurve& curve) override;

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

    /// Imports all parameters from data structure.
    /// @param parameters Structure to import parameters from.
    ASPOSECPP_SHARED_API void ImportParameters(const ECParameters& parameters) override;

    /// Computes the hash value of the specified data array, and signs the result.
    /// @param data Input data array.
    /// return ECDSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data);

    /// Computes the hash value of the specified data array, and signs the result.
    /// @param data Input data array.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to use as input data.
    /// return ECDSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, int32_t offset, int32_t count);

    /// Computes the hash value of the specified binary stream, and signs the result.
    /// @param stream Binary stream.
    /// return ECDSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const StreamPtr& stream);

    /// Computes the signature of specified input value.
    /// @param hash Hash value of data to be signed.
    /// @return ECDSA signature for specified hash.
    ASPOSECPP_SHARED_API ByteArrayPtr SignHash(const ByteArrayPtr& hash) override;

    /// Exports all parameters in XML format. Not implemented.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return XML-encoded parameters.
    ASPOSECPP_SHARED_API String ToXmlString(bool include_private_parameters) override;

    /// Exports all parameters in XML format.
    /// @param format Format of the result XML string.
    /// @return XML-encoded parameters.
    ASPOSECPP_SHARED_API String ToXmlString(ECKeyXmlFormat format);

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param signature Signature data.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, const ByteArrayPtr& signature);

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to hash.
    /// @param signature Signature data.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const ByteArrayPtr& signature);

    /// Verifies that the signature of the specified binary stream is valid.
    /// @param stream Signed data.
    /// @param signature Signature data.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const StreamPtr& stream, const ByteArrayPtr& signature);

    /// Checks data signature.
    /// @param hash Hash calculated for received data.
    /// @param signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    ASPOSECPP_SHARED_API bool VerifyHash(ByteArrayPtr hash, ByteArrayPtr signature) override;

protected:
    /// Frees data associated with object.
    /// @param disposing True if called from disposing procedure, false otherwise.
    virtual ASPOSECPP_SHARED_API void Dispose(bool disposing);

private:
    struct Implementation;
    std::unique_ptr<Implementation> m_pimpl;

    HashAlgorithmName m_hash_algorithm;

    void VerifyNotDisposed() const;
    void SetupLegalKeySizesValue();
    void GenerateKey(int32_t key_size);
};

}}} // namespace System::Security::Cryptography
