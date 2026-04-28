/// @file security/cryptography/dsa.h
#pragma once

#include <security/cryptography/asymmetric_algorithm.h>
#include <security/cryptography/dsa_parameters.h>
#include <security/cryptography/hash_algorithm_name.h>

namespace System { namespace Security { namespace Cryptography {

/// Base class for implementations of DSA algorithm.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT DSA : public AsymmetricAlgorithm
{
    /// This type.
    typedef DSA ThisType;
    /// Parent type.
    typedef AsymmetricAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Create DSA signature for the specified data.
    /// @param rgb_hash Data to be signed.
    /// @return DSA signature.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr CreateSignature(ByteArrayPtr rgb_hash) = 0;

    /// Verify DSA signature for the specified data.
    /// @param rgb_hash Data signed with @p rgb_signature.
    /// @param rgb_signature DSA signature.
    /// @return true - if @p rgb_signature matches the DSA signature computed on @p rgb_hash, otherwise - false.
    virtual ASPOSECPP_SHARED_API bool VerifySignature(ByteArrayPtr rgb_hash, ByteArrayPtr rgb_signature) = 0;

    /// Exports all parameters.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return Exported parameters structure.
    virtual ASPOSECPP_SHARED_API DSAParameters ExportParameters(bool include_private_parameters) = 0;

    /// Imports all parameters from data structure.
    /// @param parameters Structure to import parameters from.
    virtual ASPOSECPP_SHARED_API void ImportParameters(DSAParameters parameters) = 0;

    /// Initializes object using XML-encoded parameters.
    /// @param xml_string Parameters in XML format.
    virtual ASPOSECPP_SHARED_API void FromXmlString(String xml_string) override;

    /// Exports all parameters in XML format.
    /// @param include_private_parameters True to export both private and public parameters, false to export public parameters only.
    /// @return XML-encoded parameters.
    virtual ASPOSECPP_SHARED_API String ToXmlString(bool include_private_parameters) override;

    /// Computes the hash value of the specified data array using the specified hash algorithm, and signs the result.
    /// @param data Input data array.
    /// @param hash_algorithm Hash algorithm.
    /// return DSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, const HashAlgorithmName& hash_algorithm);

    /// Computes the hash value of the specified data array using the specified hash algorithm, and signs the result.
    /// @param data Input data array.
    /// @param offset Offset in @p data.
    /// @param count Number of bytes to use as input data.
    /// @param hash_algorithm Hash algorithm.
    /// return DSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const ByteArrayPtr& data, int32_t offset, int32_t count,
        const HashAlgorithmName& hash_algorithm);

    /// Computes the hash value of the specified binary stream using the specified hash algorithm, and signs the result.
    /// @param stream Binary stream.
    /// @param hash_algorithm Hash algorithm.
    /// return DSA signature for the input data.
    ASPOSECPP_SHARED_API ByteArrayPtr SignData(const StreamPtr& stream, const HashAlgorithmName& hash_algorithm);

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

    /// Creates default DSA aglorithm implementation.
    /// @return DSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<DSA> Create();

    /// Creates default DSA algorithm implementation.
    /// @param alg_name Must be "System.Security.Cryptography.DSACryptoServiceProvider".
    /// @return DSA algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<DSA> Create(const String& alg_name);

    /// Creates default DSA algorithm implementation with specifed key size.
    /// @param key_size_in_bits The key size, in bits.
    static ASPOSECPP_SHARED_API SharedPtr<DSA> Create(int32_t key_size_in_bits);

    /// Creates default DSA algorithm implementation with specifed parameters.
    /// @param parameters The parameters for the DSA algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<DSA> Create(const DSAParameters& parameters);

    /// Creates default DSA algorithm implementation with specifed XML-encoded parameters.
    /// @param xml_string The parameters for the DSA algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<DSA> CreateFromXmlString(const String& xml_string);

protected:
    ASPOSECPP_SHARED_API DSA();
    ASPOSECPP_SHARED_API ~DSA();

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
