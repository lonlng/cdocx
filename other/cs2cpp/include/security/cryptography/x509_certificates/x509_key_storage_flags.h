/// @file security/cryptography/x509_certificates/x509_key_storage_flags.h
#pragma once

#include <cstdint>
#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Defines how to store key.
enum class X509KeyStorageFlags : int32_t
{
    /// Use default key set.
    DefaultKeySet = 0,
    /// Use user-associated store instead of machine-local one.
    UserKeySet = 1,
    /// Use local machine store instead of user one.
    MachineKeySet = 2,
    /// Marks imported keys as exportable.
    Exportable = 4,
    /// Notify user that the key is being used.
    UserProtected = 8,
    /// The key is persisted when importing certificate.
    PersistKeySet = 16
};

/// @cond
/// Declaration of template arithmetic operators for values of the X509KeyStorageFlags enum type.
DECLARE_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates::X509KeyStorageFlags);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // namespace System::Security::Cryptography::X509Certificates

/// Inserts using declaratios for arithmetic operators declared in namespace System::Security::Cryptography::X509Certificates.
DECLARE_USING_ENUM_OPERATORS(System::Security::Cryptography::X509Certificates);  

template<>
struct EnumMetaInfo<System::Security::Cryptography::X509Certificates::X509KeyStorageFlags>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::X509Certificates::X509KeyStorageFlags, const char16_t*>, 6>& values();
};
