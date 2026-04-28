/// @file net/network_information/ip_global_properties.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>

namespace System {
namespace Net {
namespace NetworkInformation {

/// Represents an information about the network connection of the local computer.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IPGlobalProperties : public System::Object
{
    /// This type.
    typedef IPGlobalProperties ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    /// @returns A newly created class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPGlobalProperties> GetIPGlobalProperties();

    /// Returns the domain in which the local computer is registered.
    /// @returns The domain in which the local computer is registered.
    virtual ASPOSECPP_SHARED_API String get_DomainName();
    /// Returns the host name of the local computer.
    /// @returns The host name of the local computer.
    virtual ASPOSECPP_SHARED_API String get_HostName();
};
}}} // namespace System::Net::NetworkInformation
