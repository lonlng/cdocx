/// @file net/ip_address.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/array.h>
#include <cstdint>

#include <net/sockets/address_family.h>

namespace System {
namespace Details {
ASPOSECPP_3RD_PARTY_CLASS(ip_address_impl);
} // namespace Details
} // namespace System

namespace System {
namespace Net {

/// Represents the IP address.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS IPAddress : public System::Object
{
    /// This type.
    typedef IPAddress ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The IPv4 address that indicates if the server must listen all network interfaces.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> Any;
    /// The IPv4 loopback address.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> Loopback;
    /// The IPv4 broadcast address.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> Broadcast;
    /// The IPv4 address that indicates if the server mustn't listen any network interface.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> None;
    /// The IPv6 address that indicates if the server must listen all network interfaces.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> IPv6Any;
    /// The IPv6 loopback address.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> IPv6Loopback;
    /// The IPv6 address that indicates if the server mustn't listen any network interface.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> IPv6None;

    /// Returns the address family.
    /// @returns The address family.
    ASPOSECPP_SHARED_API System::Net::Sockets::AddressFamily get_AddressFamily();
    /// Gets the scope identifier of the IPv6 address.
    /// @returns The scope identifier of the IPv6 address.
    ASPOSECPP_SHARED_API int64_t get_ScopeId();
    /// Sets the scope identifier of the IPv6 address.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ScopeId(int64_t value);
    /// Returns a value that indicates if the address is an global IPv6 multicast address.
    /// @returns A value that indicates if the address is a global IPv6 multicast address.
    ASPOSECPP_SHARED_API bool get_IsIPv6Multicast();
    /// Returns a value that indicates if the address is an IPv6 link-local address.
    /// @returns A value that indicates if the address is an IPv6 link-local address.
    ASPOSECPP_SHARED_API bool get_IsIPv6LinkLocal();
    /// Returns a value that indicates if the address is an IPv6 site-local address.
    /// @returns A value that indicates if the address is an IPv6 site-local address.
    ASPOSECPP_SHARED_API bool get_IsIPv6SiteLocal();
    /// Returns a value that indicates if the address is an IPv6 Teredo address.
    /// @returns A value that indicates if the address is an IPv6 Teredo address.
    ASPOSECPP_SHARED_API bool get_IsIPv6Teredo();
    /// Returns a value that indicates if the address is an IPv4 address and is mapped to an IPv6 address.
    /// @returns A value that indicates if the address is an IPv4 address and is mapped to an IPv6 address.
    ASPOSECPP_SHARED_API bool get_IsIPv4MappedToIPv6();

    /// Constructs a new instance.
    /// @param newAddress The integer representation of an IP address.
    ASPOSECPP_SHARED_API IPAddress(int64_t newAddress);
    /// Constructs a new instance.
    /// @param address The byte array that contains an IP address.
    /// @param scopeid The scope identifier.
    ASPOSECPP_SHARED_API IPAddress(System::ArrayPtr<uint8_t> address, int64_t scopeid);
    /// Constructs a new instance.
    /// @param address The byte array that contains an IP address.
    ASPOSECPP_SHARED_API IPAddress(System::ArrayPtr<uint8_t> address);

    /// Tries to convert a passed string to an instance of the IPAddress class.
    /// @param ipString A string to parse.
    /// @param address An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static ASPOSECPP_SHARED_API bool TryParse(String ipString, System::SharedPtr<IPAddress>& address);
    /// Converts a passed string to an instance of the IPAddress class.
    /// @param ipString A string to parse.
    /// @returns An instance of the IPAddress class.
    static ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> Parse(String ipString);
    /// Returns a byte array of the IP address.
    /// @returns A byte array of the IP address.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> GetAddressBytes();
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Converts the specified host byte order to the corresponding network byte order.
    /// @param host The value to convert.
    /// @returns The corresponding network byte order.
    static ASPOSECPP_SHARED_API int64_t HostToNetworkOrder(int64_t host);
    /// Converts the specified host byte order to the corresponding network byte order.
    /// @param host The value to convert.
    /// @returns The corresponding network byte order.
    static ASPOSECPP_SHARED_API int32_t HostToNetworkOrder(int32_t host);
    /// Converts the specified host byte order to the corresponding network byte order.
    /// @param host The value to convert.
    /// @returns The corresponding network byte order.
    static ASPOSECPP_SHARED_API int16_t HostToNetworkOrder(int16_t host);
    /// Converts the specified network byte order to the corresponding host byte order.
    /// @param network The value to convert.
    /// @returns The corresponding host byte order.
    static ASPOSECPP_SHARED_API int64_t NetworkToHostOrder(int64_t network);
    /// Converts the specified network byte order to the corresponding host byte order.
    /// @param network The value to convert.
    /// @returns The corresponding host byte order.
    static ASPOSECPP_SHARED_API int32_t NetworkToHostOrder(int32_t network);
    /// Converts the specified network byte order to the corresponding host byte order.
    /// @param network The value to convert.
    /// @returns The corresponding host byte order.
    static ASPOSECPP_SHARED_API int16_t NetworkToHostOrder(int16_t network);
    /// Returns a value that indicates if the specified address is a loopback address.
    /// @param address The address to check.
    /// @returns True when the specified address is a loopback address, otherwise false.
    static ASPOSECPP_SHARED_API bool IsLoopback(System::SharedPtr<IPAddress> address);
    /// Compares objects using C# Object.Equals semantics.
    /// @param comparand Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Maps the address to the IPv6 address.
    /// @returns The corresponding IPv6 address.
    ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> MapToIPv6();
    /// Maps the address to the IPv4 address.
    /// @returns The corresponding IPv4 address.
    ASPOSECPP_SHARED_API System::SharedPtr<IPAddress> MapToIPv4();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API IPAddress();
    /// A pointer to the implementation type.
    typedef std::shared_ptr<System::Details::ip_address_impl> ImplPtr;
    /// Returns a pointer to implementation.
    /// @returns A pointer to implementation.
    ASPOSECPP_SHARED_API ImplPtr GetImpl() const;
    /// Sets a pointer to implementation.
    /// @param impl A pointer that must be set.
    ASPOSECPP_SHARED_API void SetImpl(ImplPtr impl);

private:
    /// A pointer to implementation.
    ImplPtr ip_address;
};
} // namespace Net
} // namespace System
