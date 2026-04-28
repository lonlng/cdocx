/// @file security/cryptography/key_number.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace Security { namespace Cryptography {

/// Key type.
enum class KeyNumber    
{
    /// Asymmetric exchange key.
    Exchange = 1,

    /// Asymmetric exchange key.
    Signature = 2,
};

}}} // namespace System::Security::Cryptography

template<>
struct EnumMetaInfo<System::Security::Cryptography::KeyNumber>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::KeyNumber, const char16_t*>, 2>& values();
};
