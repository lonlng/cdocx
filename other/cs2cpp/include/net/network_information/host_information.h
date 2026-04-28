/// @file net/network_information/host_information.h
#pragma once

#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net { namespace NetworkInformation {

/// Represents information about a host.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class HostInformation : public System::Object
{
    /// This type.
    typedef HostInformation ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the host name of the local computer.
    /// @returns The host name of the local computer.
    static String get_HostName();
    /// Returns the domain in which the local computer is registered.
    /// @returns The domain in which the local computer is registered.
    static String get_DomainName();
};

}}} // namespace System::Net::NetworkInformation
