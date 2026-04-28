/// @file net/dns_end_point.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <cstdint>

#include <net/sockets/address_family.h>
#include <net/end_point.h>

namespace System {
namespace Net {

/// Contains information used by the application to connect to the service.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DnsEndPoint : public System::Net::EndPoint
{
    /// This type.
    typedef DnsEndPoint ThisType;
    /// Parent type.
    typedef System::Net::EndPoint BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a host name.
    /// @returns A host name.
    ASPOSECPP_SHARED_API String get_Host();
    /// @copydoc System::Net::EndPoint::get_AddressFamily
    ASPOSECPP_SHARED_API System::Net::Sockets::AddressFamily get_AddressFamily() override;
    /// Returns the port number.
    /// @returns The port number.
    ASPOSECPP_SHARED_API int32_t get_Port();

    /// Constructs a new instance.
    /// @param host The host name.
    /// @param port The port number.
    ASPOSECPP_SHARED_API DnsEndPoint(String host, int32_t port);
    /// Constructs a new instance.
    /// @param host The host name.
    /// @param port The port number.
    /// @param addressFamily An address family to which a newly created class instance must belong.
    ASPOSECPP_SHARED_API DnsEndPoint(String host, int32_t port, System::Net::Sockets::AddressFamily addressFamily);

    /// Compares objects using C# Object.Equals semantics.
    /// @param comparand Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;

private:
    /// The host name.
    String m_host;
    /// The port number.
    int32_t m_port;
    /// The address family to which the current instance belongs.
    System::Net::Sockets::AddressFamily m_family;
};
} // namespace Net
} // namespace System
