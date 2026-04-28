#pragma once

#include <system/enum.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

enum class X509RevocationFlag
{
    EndCertificateOnly = 0,
    EntireChain = 1,
    ExcludeRoot = 2
};

}}}} // System::Security::Cryptography::X509Certificates

template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X509RevocationFlag>
{
    static const std::array<std::pair<System::Security::Cryptography::X509Certificates::X509RevocationFlag, const char_t*>, 3>& values();
};
