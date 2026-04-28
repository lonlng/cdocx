/// @file security/cryptography/x509_certificates/x500_distinguished_name_flags.h
#pragma once

#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// X509 certificate distinguished name formatting rules.
enum class X500DistinguishedNameFlags
{
    /// No special characteristics.
    None = 0,
    /// Name is reserved.
    Reversed = 1,
    /// Use semicolons.
    UseSemicolons = 16,
    /// Name doesn't use plus sign.
    DoNotUsePlusSign = 32,
    /// Disables quotes in name.
    DoNotUseQuotes = 64,
    /// Enables using commas.
    UseCommas = 128,
    /// Enables using new lines.
    UseNewLines = 256,
    /// Switches from using Unicode to using UTF-8 encoding.
    UseUTF8Encoding = 4096,
    /// Switches to T61 encoding.
    UseT61Encoding = 8192,
    /// Forces using UTF-8 when encoding specific X500 keys.
    ForceUTF8Encoding = 16384
};

/// @cond
/// Declaration of template arithmetic operators for values of the X500DistinguishedNameFlags enum type.
DECLARE_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates::X500DistinguishedNameFlags);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // namespace System::Security::Cryptography::X509Certificates

/// Inserts using declaratios for arithmetic operators declared in namespace System::Security::Cryptography::X509Certificates.
DECLARE_USING_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates);  

template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X500DistinguishedNameFlags>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::X509Certificates::X500DistinguishedNameFlags, const char16_t*>, 10>& values();
};
