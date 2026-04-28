/// @file net/secure_protocols/negotiate_enum_types.h
#pragma once

namespace System {
namespace Net {
namespace Security {

/// WebRequest-specific authentication flags
enum class AuthenticationLevel
{
    /// No authentication is required for the client and server.
    None = 0,
    /// The request does not fail if the server is not authenticated.
    MutualAuthRequested = 1,
    /// The current application will receive 'IOException' when the server is not authenticated.
    MutualAuthRequired = 2
};
}}} // namespace System::Net::Security
