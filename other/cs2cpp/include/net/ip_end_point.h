/// @file net/ip_end_point.h
#pragma once

#include <cstdint>

#include <net/ip_address.h>
#include <net/end_point.h>

namespace System {
namespace Net {

/// Represents a network endpoint that contains an IP address and a port.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IPEndPoint : public System::Net::EndPoint
{
    /// This type.
    typedef IPEndPoint ThisType;
    /// Parent type.
    typedef System::Net::EndPoint BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The minimal port number.
    static ASPOSECPP_SHARED_API const int32_t MinPort;
    /// The maximum port number.
    static ASPOSECPP_SHARED_API const int32_t MaxPort;

    /// A value that indicates if any port can be used.
    static const int32_t AnyPort;
    /// The endpoint for any IPv4 address and any port.
    static System::SharedPtr<IPEndPoint> Any;
    /// The endpoint for any IPv6 address and any port.
    static System::SharedPtr<IPEndPoint> IPv6Any;

    /// @copydoc System::Net::EndPoint::get_AddressFamily
    ASPOSECPP_SHARED_API System::Net::Sockets::AddressFamily get_AddressFamily() override;
    /// Gets the endpoint address.
    /// @returns The endpoint address.
    ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> get_Address();
    /// Sets the endpoint address.
    /// @param value The endpoint address that must be set.
    ASPOSECPP_SHARED_API void set_Address(System::SharedPtr<IPAddress> value);
    /// Gets the port number.
    /// @returns The port number.
    ASPOSECPP_SHARED_API int32_t get_Port();
    /// Sets the port number.
    /// @param value The port number that must be set.
    ASPOSECPP_SHARED_API void set_Port(int32_t value);

    /// Constructs a new instance.
    /// @param address The host IP address.
    /// @param port The port number.
    ASPOSECPP_SHARED_API IPEndPoint(int64_t address, int32_t port);
    /// Constructs a new instance.
    /// @param address The host IP address.
    /// @param port The port number.
    ASPOSECPP_SHARED_API IPEndPoint(System::SharedPtr<IPAddress> address, int32_t port);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Net::EndPoint::Create
    ASPOSECPP_SHARED_API System::SharedPtr<EndPoint> Create(System::SharedPtr<SocketAddress> socketAddress) override;
    /// Compares objects using C# Object.Equals semantics.
    /// @param comparand Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;

    /// @copydoc System::Net::EndPoint::GetImpl
    ASPOSECPP_SHARED_API ImplPtr GetImpl() const override;

private:
    /// A pointer to implementation.
    ImplPtr io_endpoint;
};
} // namespace Net
} // namespace System
