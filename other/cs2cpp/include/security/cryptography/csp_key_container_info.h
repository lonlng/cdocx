/// @file security/cryptography/csp_key_container_info.h
#pragma once

#include <system/object.h>
#include <security/cryptography/csp_parameters.h>
#include <security/cryptography/key_number.h>

namespace System { namespace Security { namespace Cryptography {

/// Additional information about a cryptographic key pair.
class ASPOSECPP_SHARED_CLASS CspKeyContainerInfo final : public virtual Object
{
    /// This type.
    typedef CspKeyContainerInfo ThisType;
    /// Parent type.
    typedef Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Consturctor.
    /// @param parameters Parameters.
    ASPOSECPP_SHARED_API CspKeyContainerInfo(const SharedPtr<CspParameters>& parameters);

    /// Gets a flag indicating whether a key in a container is accessible.
    ASPOSECPP_SHARED_API bool get_Accessible() const;

    /// Gets a flag indicating whether a key can be exported from a container.
    ASPOSECPP_SHARED_API bool get_Exportable() const;

    /// Gets a flag indicating whether a key is a hardware key.
    ASPOSECPP_SHARED_API bool get_HardwareDevice() const;

    /// Gets a key container name.
    ASPOSECPP_SHARED_API String get_KeyContainerName() const;

    /// Gets a KeyNumber object.
    ASPOSECPP_SHARED_API SharedPtr<KeyNumber> get_KeyNumber() const;

    /// Gets a flag indicating whether a key is loaded from machine key store.
    ASPOSECPP_SHARED_API bool get_MachineKeyStore() const;

    /// Gets a flag indicating whether a key is protected from copy.
    ASPOSECPP_SHARED_API bool get_Protected() const;

    /// Gets provider name.
    ASPOSECPP_SHARED_API String get_ProviderName() const;

    /// Gets provider type.
    ASPOSECPP_SHARED_API int32_t get_ProviderType() const;

    /// Gets a flag indicating whether a key was randomly generated.
    ASPOSECPP_SHARED_API bool get_RandomlyGenerated() const;

    /// Gets a flag indicating whether a key can be removed from a container.
    ASPOSECPP_SHARED_API bool get_Removable() const;

    /// Gets a unique container name.
    ASPOSECPP_SHARED_API String get_UniqueKeyContainerName() const;

private:
    ASPOSECPP_SHARED_API ~CspKeyContainerInfo();
};

}}} // namespace System::Security::Cryptography
