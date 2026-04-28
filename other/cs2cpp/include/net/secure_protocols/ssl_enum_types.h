/// @file net/secure_protocols/ssl_enum_types.h
#pragma once
#include <system/enum.h>

namespace System { namespace Security { namespace Authentication {

/// Enumerates the cryptographic protocols.
enum class SslProtocols
{
    /// The operating system chooses a protocol to use.
    None = 0,
    /// The SSL 2.0 protocol.
    Ssl2 = 12,
    /// The SSL 3.0 protocol.
    Ssl3 = 48,
    /// The TLS 1.0 protocol.
    Tls = 192,
    /// Permits only the SSL 3.0 or TLS 1.0 protocols to be used.
    Default = 240,
    /// The TLS 1.1 protocol.
    Tls11 = 768,
    /// The TLS 1.2 protocol.
    Tls12 = 3072
};

/// Enumerates the cipher algorithms.
enum class CipherAlgorithmType
{
    /// No encryption algorithm is used.
    None = 0,
    /// No encryption algorithm is used with a 'Null' cipher algorithm.
    Null = 24576,
    /// The DES algorithm.
    Des = 26113,
    /// The RC2 algorithm.
    Rc2 = 26114,
    /// The 3DES algorithm.
    TripleDes = 26115,
    /// The AES algorithm with a 128 bit key.
    Aes128 = 26126,
    /// The AES algorithm with a 192 bit key.
    Aes192 = 26127,
    /// The AES algorithm with a 256 bit key.
    Aes256 = 26128,
    /// The AES algorithm.
    Aes = 26129,
    /// The RC4 algorithm.
    Rc4 = 26625
};

/// Enumerates the hash algorithms.
enum class HashAlgorithmType
{
    /// No hash algorithm is used.
    None = 0,
    /// The Message Digest 5 hash algorithm.
    Md5 = 32771,
    /// The Secure Hash Algorithm 1.
    Sha1 = 32772
};
}}} // namespace System::Security::Authentication

/// Specialization for System::Security::Authentication::SslProtocols contains mapping of enum constants to their string
/// representations.
template <>
struct EnumMetaInfo<System::Security::Authentication::SslProtocols>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const
        std::array<std::pair<System::Security::Authentication::SslProtocols, const char_t*>, 7>&
        values();
};
