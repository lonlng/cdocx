/// @file security/cryptography/rsa_encryption_padding_mode.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace Security { namespace Cryptography {

/// Padding mode used with RSA encryption or decryption operations.
enum class RSAEncryptionPaddingMode
{
    /// PKCS #1 v1.5.
    Pkcs1 = 0,

    /// Optimal Asymmetric Encryption Padding.
    Oaep = 1,
};

}}} // namespace System::Security::Cryptography

template<>
struct EnumMetaInfo<System::Security::Cryptography::RSAEncryptionPaddingMode>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::RSAEncryptionPaddingMode, const char16_t*>, 2>& values();
};
