/// @file net/secure_protocols/ssl_policy_errors.h
#pragma once

#include <system/enum_helpers.h>

namespace System {
namespace Net {
namespace Security {

/// Enumerates the policy errors of SSL.
enum class SslPolicyErrors
{
    /// No SSL policy errors.
    None = 0x0,
    /// The certificate is unavailable.
    RemoteCertificateNotAvailable = 0x1,
    /// The certificate name mismatch.
    RemoteCertificateNameMismatch = 0x2,
    /// The certificate chain contains errors.
    RemoteCertificateChainErrors = 0x4
};

/// @cond
/// Declaration of template arithmetic operators for values of the SslPolicyErrors enum type.
DECLARE_ENUM_OPERATORS(System::Net::Security::SslPolicyErrors);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}} // System::Net::Security

/// Inserts using declarations for arithmetic operators declared in namespace System::Net::Security.
DECLARE_USING_ENUM_OPERATORS(System::Net::Security);
