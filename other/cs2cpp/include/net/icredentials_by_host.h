/// @file net/icredentials_by_host.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <cstdint>

namespace System {
namespace Net {

class NetworkCredential;

/// Provides the authentication interface for retrieving credentials for a host, port, and authentication type.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ICredentialsByHost : public virtual System::Object
{
    /// This type.
    typedef ICredentialsByHost ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns credentials for the specified host and authentication type.
    /// @param host The host that authenticates the client.
    /// @param port The host port number.
    /// @param authenticationType The authentication type.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<NetworkCredential> GetCredential(String host, int32_t port, String authenticationType) = 0;
};
} // namespace Net
} // namespace System
