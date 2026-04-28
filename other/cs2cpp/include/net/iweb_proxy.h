/// @file net/iweb_proxy.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>

#include <net/icredentials.h>

namespace System {
namespace Net {

/// This interface used for implementation of proxy access to the WebRequest class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IWebProxy : virtual public System::Object
{
    /// This type.
    typedef IWebProxy ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets credentials for authentication on the proxy server.
    /// @returns Credentials for authentication on the proxy server.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<ICredentials> get_Credentials() = 0;
    /// Sets credentials for authentication on the proxy server.
    /// @param value Credentials to set.
    virtual ASPOSECPP_SHARED_API void set_Credentials(System::SharedPtr<ICredentials> value) = 0;

    /// Returns the proxy URI.
    /// @param destination The resource URI.
    /// @returns The proxy URI.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<Uri> GetProxy(System::SharedPtr<Uri> destination) = 0;
    /// Returns a value that indicates if the proxy must not be used for the specified host.
    /// @param host The host URI to check.
    /// @returns True when the proxy server must not be used, otherwise false.
    virtual ASPOSECPP_SHARED_API bool IsBypassed(System::SharedPtr<Uri> host) = 0;
};
} // namespace Net
} // namespace System
