/// @file security/cryptography/ec_dsa.h
#pragma once

#include <security/cryptography/asymmetric_algorithm.h>
#include <security/cryptography/hash_algorithm_name.h>
#include <security/cryptography/ec_curve.h>
#include <security/cryptography/ec_parameters.h>

namespace System { namespace Security { namespace Cryptography {

/// Base class for implementations of ECDsa algorithm.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT ECDsa : public AsymmetricAlgorithm
{
    /// This type.
    typedef ECDsa ThisType;
    /// Parent type.
    typedef AsymmetricAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets key exchange algorithm to use.
    /// @return Algorithm name.
    ASPOSECPP_SHARED_API String get_KeyExchangeAlgorithm() override;

    /// Gets signature algorithm to use.
    /// @return Algorithm name.
    ASPOSECPP_SHARED_API String get_SignatureAlgorithm() override;

    /// Exports explicit parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    virtual ASPOSECPP_SHARED_API ECParameters ExportExplicitParameters(bool include_private_parameters);

    /// Exports named or explicit parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    virtual ASPOSECPP_SHARED_API ECParameters ExportParameters(bool include_private_parameters);

    /// Generates a new public/private key pair for the specified curve.
    /// @param curve Curve to use to generate the keys.
    virtual ASPOSECPP_SHARED_API void GenerateKey(const ECCurve& curve);

    /// Imports all parameters from data structure.
    /// @param parameters Structure to import parameters from.
    virtual ASPOSECPP_SHARED_API void ImportParameters(const ECParameters& parameters);

    /// Computes the hash value of the specified data array using the specified hash algorithm, and signs the result.
    /// @param data Input data array.
    /// @param hash_algorithm Hash algorithm.
    /// return ECDSA signature for the input data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, const HashAlgorithmName& hash_algorithm);

    /// Computes the hash value of the specified data array using the specified hash algorithm, and signs the result.
    /// @param data Input data array.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to use as input data.
    /// @param hash_algorithm Hash algorithm.
    /// return ECDSA signature for the input data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const HashAlgorithmName& hash_algorithm);

    /// Computes the hash value of the specified binary stream using the specified hash algorithm, and signs the result.
    /// @param stream Binary stream.
    /// @param hash_algorithm Hash algorithm.
    /// return ECDSA signature for the input data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr SignData(const StreamPtr& stream, const HashAlgorithmName& hash_algorithm);

    /// Computes the signature of specified input value.
    /// @param hash Hash value of data to be signed.
    /// @return ECDSA signature for specified hash.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr SignHash(const ByteArrayPtr& hash) = 0;

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm);

    /// Verifies that the signature of the specified data is valid.
    /// @param data Signed data.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to hash.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm);

    /// Verifies that the signature of the specified binary stream is valid.
    /// @param stream Signed data.
    /// @param signature Signature data.
    /// @param hash_algorithm Hash algorithm.
    /// return true if signature is valid, otherwise - false.
    ASPOSECPP_SHARED_API bool VerifyData(const StreamPtr& stream, const ByteArrayPtr& signature, const HashAlgorithmName& hash_algorithm);

    /// Checks data signature.
    /// @param hash Hash calculated for received data.
    /// @param signature Signature as received.
    /// @return True if signature is valid, false otherwise.
    virtual ASPOSECPP_SHARED_API bool VerifyHash(ByteArrayPtr hash, ByteArrayPtr signature) = 0;

    /// Creates default ECDSA aglorithm implementation.
    /// @return ECDSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<ECDsa> Create();

    /// Creates default ECDSA aglorithm implementation with newly created key over the specified curve.
    /// @param curve Curve to use for key creation.
    /// @return ECDSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<ECDsa> Create(const ECCurve& curve);

    /// Creates default ECDSA aglorithm implementation using the specified parameters.
    /// @param parameters Parameters representing the key.
    /// @return ECDSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<ECDsa> Create(const ECParameters& parameters);

    /// Creates specified ECDSA aglorithm implementation.
    /// @param algorithm Algorithm name.
    /// @return ECDSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<ECDsa> Create(const String& algorithm);

protected:
    ASPOSECPP_SHARED_API ECDsa();

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
