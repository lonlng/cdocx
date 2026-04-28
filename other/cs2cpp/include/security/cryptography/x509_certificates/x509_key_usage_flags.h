/// @file security/cryptography/x509_certificates/x509_key_usage_flags.h
#pragma once

#include <cstdint>
#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Defines how the certificate key can be used.
enum class X509KeyUsageFlags : int32_t
{
    /// No key usage parameters.
    None = 0x0000,
    /// Key can be used only for encryption.
    EncipherOnly = 0x0001,
    /// Key can be used to sign a certificate revocation list 
    CrlSign = 0x0002,
    /// Key can be used to sign certificates.
    KeyCertSign = 0x0004,
    /// Key can be used to determine key agreement.
    KeyAgreement = 0x0008,
    /// Key can be used for data encryption.
    DataEncipherment = 0x0010,
    /// Key can be used for key encryption.
    KeyEncipherment = 0x0020,
    /// Key can be used for authentication.
    NonRepudiation = 0x0040,
    /// Key can be used as a digital signature.
    DigitalSignature = 0x0080,
    /// Key can be used only for decryption.
    DecipherOnly = 0x8000,
};

/// @cond
/// Declaration of template arithmetic operators for values of the X509KeyUsageFlags enum type.
DECLARE_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates::X509KeyUsageFlags);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // namespace System::Security::Cryptography::X509Certificates

/// Inserts using declaratios for arithmetic operators declared in namespace System::Security::Cryptography::X509Certificates.
DECLARE_USING_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates);  

template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X509KeyUsageFlags>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::X509Certificates::X509KeyUsageFlags, const char16_t*>, 10>& values();
};
