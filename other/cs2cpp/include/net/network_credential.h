/// @file net/network_credential.h
#pragma once

#include <net/icredentials_by_host.h>
#include <net/icredentials.h>

namespace System {
namespace Net {

/// Provides credentials for the password-based authentication schemes.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS NetworkCredential : public System::Net::ICredentials, public System::Net::ICredentialsByHost, public virtual System::Object
{
    /// This type.
    typedef NetworkCredential ThisType;
    /// Parent type.
    typedef System::Net::ICredentials BaseType;
    /// Parent type.
    typedef System::Net::ICredentialsByHost BaseType1;
    /// Parent type.
    typedef System::Object BaseType2;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the username.
    /// @returns The username.
    ASPOSECPP_SHARED_API String get_UserName();
    /// Sets the username.
    /// @param value The username to set.
    ASPOSECPP_SHARED_API void set_UserName(String value);
    /// Gets the password.
    /// @returns The password.
    ASPOSECPP_SHARED_API String get_Password();
    /// Sets the password.
    /// @param value The password to set.
    ASPOSECPP_SHARED_API void set_Password(String value);
    /// Gets the domain that verifies the credentials.
    /// @returns The domain that verifies the credentials.
    ASPOSECPP_SHARED_API String get_Domain();
    /// Sets the domain that verifies the credentials.
    /// @param value The domain to set.
    ASPOSECPP_SHARED_API void set_Domain(String value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API NetworkCredential();
    /// Constructs a new instance.
    /// @param userName The username.
    /// @param password The password.
    ASPOSECPP_SHARED_API NetworkCredential(String userName, String password);
    /// Constructs a new instance.
    /// @param userName The username.
    /// @param password The password.
    /// @param domain The domain that verifies the credentials.
    ASPOSECPP_SHARED_API NetworkCredential(String userName, String password, String domain);

    /// Returns credentials for the specified URI and authentication type.
    /// @param uri The URI.
    /// @param authenticationType The authentication type.
    ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(System::SharedPtr<Uri> uri, String authenticationType) override;
    /// Returns credentials for the specified host name, port, and authentication type.
    /// @param host The host name.
    /// @param port The port number.
    /// @param authenticationType The authentication type.
    ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(String host, int32_t port, String authenticationType) override;

private:
    /// The domain that verifies the credentials.
    System::String m_domain;
    /// The username.
    System::String m_userName;
    /// The password.
    System::String m_password;
};
} // namespace Net
} // namespace System
