/// @file security/cryptography/oid_group.h
#pragma once

#include <cstdint>
#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Security { namespace Cryptography {

/// Identifies Windows OID groups.
enum class OidGroup : int32_t
{
    /// All groups.
    All = 0,
    /// Group represented by CRYPT_HASH_ALG_OID_GROUP_ID.
    HashAlgorithm = 1,
    /// Group represented by CRYPT_ENCRYPT_ALG_OID_GROUP_ID.
    EncryptionAlgorithm = 2,
    /// Group represented by CRYPT_PUBKEY_ALG_OID_GROUP_ID.
    PublicKeyAlgorithm = 3,
    /// Group represented by CRYPT_SIGN_ALG_OID_GROUP_ID.
    SignatureAlgorithm = 4,
    /// Group represented by CRYPT_RDN_ATTR_OID_GROUP_ID.
    Attribute = 5,
    /// Group represented by CRYPT_EXT_OR_ATTR_OID_GROUP_ID.
    ExtensionOrAttribute = 6,
    /// Group represented by CRYPT_ENHKEY_USAGE_OID_GROUP_ID.
    EnhancedKeyUsage = 7,
    /// Group represented by CRYPT_POLICY_OID_GROUP_ID.
    Policy = 8,
    /// Group represented by CRYPT_TEMPLATE_OID_GROUP_ID.
    Template = 9,
    /// Group represented by CRYPT_KDF_OID_GROUP_ID.
    KeyDerivationFunction = 10
};

/// @cond
/// Declaration of template arithmetic operators for values of the OidGroup enum type.
DECLARE_ENUM_OPERATORS(System::Security::Cryptography::OidGroup);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}} // namespace System::Security::Cryptography

/// Inserts using declaratios for arithmetic operators declared in namespace System::Security::Cryptography.
DECLARE_USING_ENUM_OPERATORS(System::Security::Cryptography);  

template<>
struct EnumMetaInfo<System::Security::Cryptography::OidGroup>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Security::Cryptography::OidGroup, const char16_t*>, 11>& values();
};
