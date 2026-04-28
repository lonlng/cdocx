/// @file security/cryptography/x509_certificates/x509_content_type.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Format of X.509 certificate.
enum class X509ContentType
{
    /// Unknown certificate.
    Unknown = 0,
    /// Single certificate.
    Cert = 1,
    /// Serialized single certificate.
    SerializedCert = 2,
    /// PKCS #12-formatted certificate.
    Pkcs12 = 3,
    /// PFX-formatted certificate.
    Pfx = 3,
    /// Serialized cerificate store.
    SerializedStore = 4,
    /// Serfificated PKCS #7-formatted certificate.
    Pkcs7 = 5,
    /// Authenticode X.509 certificate.
    Authenticode = 6
};

}}}} // namespace System::Security::Cryptography::X509Certificates

template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X509ContentType>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::X509Certificates::X509ContentType, const char16_t*>, 8>& values();
};
