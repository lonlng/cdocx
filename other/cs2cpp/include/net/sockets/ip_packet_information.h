/// @file net/sockets/ip_packet_information.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>

#include <net/ip_address.h>

namespace System {
namespace Net {
namespace Sockets {

/// Represents information about the packet.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IPPacketInformation : public System::Object
{
    /// This type.
    typedef IPPacketInformation ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend ASPOSECPP_SHARED_API bool operator ==(IPPacketInformation left, IPPacketInformation right);
    friend ASPOSECPP_SHARED_API bool operator !=(IPPacketInformation left, IPPacketInformation right);

public:
    /// Returns the address from which the package is received.
    /// @returns The address from which the package is received.
    ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> get_Address();
    /// Returns the network interface information.
    /// @returns The network interface information.
    ASPOSECPP_SHARED_API int32_t get_Interface();

    /// Constructs a new instance.
    /// @param address The address from which the package is received.
    /// @param networkInterface The network interface information.
    ASPOSECPP_SHARED_API IPPacketInformation(System::SharedPtr<IPAddress> address, int32_t networkInterface);

    /// @brief Compares two objects using C# Object.Equals semantics.
    /// @param comparand The object to compare the current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API IPPacketInformation();

private:
    /// The address from which the package is received.
    System::SharedPtr<IPAddress> m_address;
    /// The network interface information.
    int32_t m_networkInterface;
};

ASPOSECPP_SHARED_API bool operator ==(IPPacketInformation left, IPPacketInformation right);
ASPOSECPP_SHARED_API bool operator !=(IPPacketInformation left, IPPacketInformation right);
} // namespace Sockets
} // namespace Net
} // namespace System
