/// @file net/authentication_schemes.h
#pragma once

#include <system/enum_helpers.h>

#include <cstdint>

namespace System {
namespace Net {

/// Enumerates the authentication schemes.
enum class AuthenticationSchemes
{
    /// No authentication is required.
    None = 0x00000000,
    /// Digest access authentication.
    Digest = 0x00000001,
    /// Negotiates with the client which authentication scheme will be used (NTML or Kerberos).
    Negotiate = 0x00000002,
    /// NTLM authentication.
    Ntlm = 0x00000004,
    /// Basic authentication.
    Basic = 0x00000008,
    /// Anonymous authentication.
    Anonymous = 0x00008000,
    /// Windows authentication.
    IntegratedWindowsAuthentication = static_cast<int32_t>(Negotiate | Ntlm)
};

/// @cond
/// Declaration of template arithmetic operators for values of the AuthenticationSchemes enum type.
DECLARE_ENUM_OPERATORS(System::Net::AuthenticationSchemes);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
} // namespace Net
} // namespace System

/// Inserts using declarations for arithmetic operators declared in namespace System::Net.
DECLARE_USING_ENUM_OPERATORS(System::Net);
