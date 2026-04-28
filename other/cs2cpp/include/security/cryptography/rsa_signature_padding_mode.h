/// @file security/cryptography/rsa_signature_padding_mode.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace Security { namespace Cryptography {

/// Padding mode used with RSA signature creation or verification operations.
enum class RSASignaturePaddingMode
{
    /// PKCS #1 v1.5.
    Pkcs1 = 0,

    /// Probabilistic Signature Scheme.
    Pss = 1,
};

}}} // namespace System::Security::Cryptography

template<>
struct EnumMetaInfo<System::Security::Cryptography::RSASignaturePaddingMode>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::RSASignaturePaddingMode, const char16_t*>, 2>& values();
};
