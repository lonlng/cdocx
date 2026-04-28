#pragma once

#include <system/enum_helpers.h>
#include <system/enum.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

enum class X509VerificationFlags
{
    NoFlag = 0x00000000,
    IgnoreNotTimeValid = 0x00000001,
    IgnoreCtlNotTimeValid = 0x00000002,
    IgnoreNotTimeNested = 0x00000004,
    IgnoreInvalidBasicConstraints = 0x00000008,
    AllowUnknownCertificateAuthority = 0x00000010,
    IgnoreWrongUsage = 0x00000020,
    IgnoreInvalidName = 0x00000040,
    IgnoreInvalidPolicy = 0x00000080,
    IgnoreEndRevocationUnknown = 0x00000100,
    IgnoreCtlSignerRevocationUnknown = 0x00000200,
    IgnoreCertificateAuthorityRevocationUnknown = 0x00000400,
    IgnoreRootRevocationUnknown = 0x00000800,
    AllFlags = 0x00000FFF
};

/// @cond
DECLARE_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates::X509VerificationFlags);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // System::Security::Cryptography::X509Certificates

DECLARE_USING_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates);
template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X509VerificationFlags>
{
    typedef void Flags;
    static const std::array<std::pair<System::Security::Cryptography::X509Certificates::X509VerificationFlags, const char_t*>, 14>& values();
};
