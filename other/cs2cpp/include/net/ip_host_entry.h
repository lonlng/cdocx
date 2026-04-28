/// @file net/ip_host_entry.h
#pragma once

#include <system/array.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/ip_address.h>

namespace System { namespace Net {

/// Represents information about an internet host address.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IPHostEntry : public System::Object
{
    /// This type.
    typedef IPHostEntry ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the host name.
    /// @returns The host name.
    ASPOSECPP_SHARED_API String get_HostName() const;
    /// Sets the host name.
    /// @param value The host name to set.
    ASPOSECPP_SHARED_API void set_HostName(String value);
    /// Gets the collection of aliases of the host.
    /// @returns The collection of aliases of the host.
    ASPOSECPP_SHARED_API System::ArrayPtr<String> get_Aliases();
    /// Sets a collection of aliases of the host.
    /// @param value The collection of aliases that must be set.
    ASPOSECPP_SHARED_API void set_Aliases(System::ArrayPtr<String> value);
    /// Gets the collection of IP addresses of the host.
    /// @returns The collection of IP addresses of the host.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<IPAddress>> get_AddressList();
    /// Sets a collection of IP addresses of the host.
    /// @param value The collection of IP addresses that must be set.
    ASPOSECPP_SHARED_API void set_AddressList(System::ArrayPtr<System::SharedPtr<IPAddress>> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API IPHostEntry();
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    /// The host name.
    String hostName;
    /// The collection of aliases of the host.
    System::ArrayPtr<String> aliases;
    /// The collection of IP addresses of the host.
    System::ArrayPtr<System::SharedPtr<IPAddress>> addressList;
};
}} // namespace System::Net
