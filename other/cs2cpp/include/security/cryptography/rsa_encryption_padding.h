/// @file security/cryptography/rsa_encryption_padding.h
#pragma once

#include <system/iequatable.h>
#include <security/cryptography/rsa_encryption_padding_mode.h>
#include <security/cryptography/hash_algorithm_name.h>

namespace System { namespace Security { namespace Cryptography {

/// Padding mode and parameters for RSA encryption or decryption operations.
class ASPOSECPP_SHARED_CLASS RSAEncryptionPadding final
    : public IEquatable<SharedPtr<RSAEncryptionPadding>>
{
    /// This type.
    typedef RSAEncryptionPadding ThisType;
    /// Parent type.
    typedef Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets PKCS #1 v1.5 mode.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> get_Pkcs1();

    /// Gets OAEP mode with SHA1 hash algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> get_OaepSHA1();

    /// Gets OAEP mode with SHA256 hash algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> get_OaepSHA256();

    /// Gets OAEP mode with SHA384 hash algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> get_OaepSHA384();

    /// Gets OAEP mode with SHA512 hash algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> get_OaepSHA512();

    /// Creates RSAEncryptionPadding with OAEP mode and specified hash algorithm.
    static ASPOSECPP_SHARED_API SharedPtr<RSAEncryptionPadding> CreateOaep(const HashAlgorithmName& hash_algorithm);

    /// Gets the padding mode.
    RSAEncryptionPaddingMode get_Mode() const
    {
        return m_mode;
    }

    /// Gets the hash algorithm used with OAEP.
    const HashAlgorithmName& get_OaepHashAlgorithm() const
    {
        return m_oaep_hash_algorithm;
    }

    ASPOSECPP_SHARED_API int GetHashCode() const override;
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<Object> other) override;
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<RSAEncryptionPadding> other) override;
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    const RSAEncryptionPaddingMode m_mode;
    const HashAlgorithmName m_oaep_hash_algorithm;

    RSAEncryptionPadding(RSAEncryptionPaddingMode mode, const HashAlgorithmName& oaep_hash_algorithm)
        : m_mode(mode)
        , m_oaep_hash_algorithm(oaep_hash_algorithm)
    {}
    MEMBER_FUNCTION_MAKE_OBJECT(RSAEncryptionPadding, CODEPORTING_ARGS(RSAEncryptionPaddingMode mode, const HashAlgorithmName& oaep_hash_algorithm), CODEPORTING_ARGS(mode, oaep_hash_algorithm));

    ASPOSECPP_SHARED_API ~RSAEncryptionPadding();
};

inline bool operator ==(const SharedPtr<RSAEncryptionPadding>& left, const SharedPtr<RSAEncryptionPadding>& right)
{
    if (left.get() == nullptr)
        return right.get() == nullptr;

    return left->Equals(right);
}

inline bool operator !=(const SharedPtr<RSAEncryptionPadding>& left, const SharedPtr<RSAEncryptionPadding>& right)
{
    return !(left == right);
}

}}} // namespace System::Security::Cryptography
