/// @file security/cryptography/rsa_signature_padding.h
#pragma once

#include <system/iequatable.h>
#include <security/cryptography/rsa_signature_padding_mode.h>
#include <security/cryptography/hash_algorithm_name.h>

namespace System { namespace Security { namespace Cryptography {

/// Padding mode and parameters for RSA signature creation or verification operations.
class ASPOSECPP_SHARED_CLASS RSASignaturePadding final
    : public IEquatable<SharedPtr<RSASignaturePadding>>
{
    /// This type.
    typedef RSASignaturePadding ThisType;
    /// Parent type.
    typedef Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets PKCS #1 v1.5 mode.
    static ASPOSECPP_SHARED_API SharedPtr<RSASignaturePadding> get_Pkcs1();

    /// Gets PSS mode.
    static ASPOSECPP_SHARED_API SharedPtr<RSASignaturePadding> get_Pss();

    /// Gets the padding mode.
    RSASignaturePaddingMode get_Mode() const
    {
        return m_mode;
    }

    ASPOSECPP_SHARED_API int GetHashCode() const override;
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<Object> other) override;
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<RSASignaturePadding> other) override;
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    const RSASignaturePaddingMode m_mode;

    RSASignaturePadding(RSASignaturePaddingMode mode)
        : m_mode(mode)
    {}
    MEMBER_FUNCTION_MAKE_OBJECT(RSASignaturePadding, CODEPORTING_ARGS(RSASignaturePaddingMode mode), CODEPORTING_ARGS(mode));

    ASPOSECPP_SHARED_API ~RSASignaturePadding();
};

inline bool operator ==(const SharedPtr<RSASignaturePadding>& left, const SharedPtr<RSASignaturePadding>& right)
{
    if (left.get() == nullptr)
        return right.get() == nullptr;

    return left->Equals(right);
}

inline bool operator !=(const SharedPtr<RSASignaturePadding>& left, const SharedPtr<RSASignaturePadding>& right)
{
    return !(left == right);
}

}}} // namespace System::Security::Cryptography
