/// @file security/cryptography/padding_mode.h
#pragma once

#include <system/enum.h>

namespace System { namespace Security { namespace Cryptography {

/// Defines how to treat messages that is shorter than block required by crypto operation.s
enum class PaddingMode {
    /// No padding.
    None = 1,
    /// Use PKCS #7 padding string.
    PKCS7 = 2,
    /// Use zero bytes.
    Zeros = 3,
    /// Use ANSIX923 padding string.
    ANSIX923 = 4,
    /// Use ISO10126 padding string.
    ISO10126 = 5,
};

}}}

/// Specialization for System::Security::Cryptography::PaddingMode; contains mapping of enum constants
/// to their string representations.
template<>
struct EnumMetaInfo<System::Security::Cryptography::PaddingMode>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Security::Cryptography::PaddingMode, const char_t*>, 5>& values();
};
