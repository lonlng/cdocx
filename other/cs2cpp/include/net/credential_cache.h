/// @file net/credential_cache.h
#pragma once

#include <system/uri.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <cstdint>

#include <net/network_credential.h>
#include <net/icredentials_by_host.h>
#include <net/icredentials.h>

namespace System {
namespace Net {

/// Provides the credentials storage.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS CredentialCache : public System::Net::ICredentials, public System::Net::ICredentialsByHost
{
    /// This type.
    typedef CredentialCache ThisType;
    /// Parent type.
    typedef System::Net::ICredentials BaseType;
    /// Parent type.
    typedef System::Net::ICredentialsByHost BaseType1;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the system credentials of the application.
    static ASPOSECPP_SHARED_API System::SharedPtr<ICredentials> get_DefaultCredentials();
    /// Returns the network credentials of the current user or application.
    static ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> get_DefaultNetworkCredentials();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API CredentialCache();

    /// Adds the specified network credentials to the cache.
    /// @param uriPrefix The resource's URI prefix with which the credentials are associated.
    /// @param authenticationType The authentication scheme.
    /// @param credential The credentials to add.
    ASPOSECPP_SHARED_API void Add(System::SharedPtr<Uri> uriPrefix, String authenticationType, System::SharedPtr<NetworkCredential> credential);
    /// Adds the specified network credentials to the cache.
    /// @param host The host name with which the credentials are associated.
    /// @param port The port number.
    /// @param authenticationType The authentication scheme.
    /// @param credential The credentials to add.
    ASPOSECPP_SHARED_API void Add(String host, int32_t port, String authenticationType, System::SharedPtr<NetworkCredential> credential);
    /// Removes network credentials for the specified URI prefix and authentication type.
    /// @param uriPrefix The URI prefix.
    /// @param authenticationType The authentication type.
    ASPOSECPP_SHARED_API void Remove(System::SharedPtr<Uri> uriPrefix, String authenticationType);
    /// Removes network credentials for the specified host name, port, and authentication type.
    /// @param host The host name with which the credentials are associated.
    /// @param port The port number.
    /// @param authenticationType An authentication type.
    ASPOSECPP_SHARED_API void Remove(String host, int32_t port, String authenticationType);
    /// Returns credentials for the specified URI prefix and authentication type.
    /// @param uriPrefix The URI prefix.
    /// @param authenticationType An authentication type.
    ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(System::SharedPtr<Uri> uriPrefix, String authenticationType) override;
    /// Returns credentials for the specified host name, port, and authentication type.
    /// @param host The host name with which the credentials are associated.
    /// @param port The port number.
    /// @param authenticationType The authentication type.
    ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(String host, int32_t port, String authenticationType) override;
};
} // namespace Net
} // namespace System
