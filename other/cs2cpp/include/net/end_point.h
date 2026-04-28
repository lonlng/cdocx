/// @file net/end_point.h
#pragma once

#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/socket_address.h>
#include <net/sockets/address_family.h>

namespace System { namespace Details {
ASPOSECPP_3RD_PARTY_CLASS(io_endpoint_impl);
}} // namespace System::Details

namespace System { namespace Net {

/// The abstract class contains a network address.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT EndPoint : public System::Object
{
    /// This type.
    typedef EndPoint ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the address family to which the current instance belongs.
    /// @returns The address family to which the current instance belongs.
    virtual ASPOSECPP_SHARED_API System::Net::Sockets::AddressFamily get_AddressFamily();
    /// Create a new instance of the EndPoint class using the specified socket address.
    /// @param socketAddress The socket address that will be used to initialize a new instance.
    /// @returns A newly created EndPoint-class instance.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<EndPoint> Create(System::SharedPtr<SocketAddress> socketAddress);

    /// A pointer to implementation.
    typedef std::shared_ptr<System::Details::io_endpoint_impl> ImplPtr;

    /// Returns a pointer to implementation.
    /// @returns A pointer to implementation.
    virtual ASPOSECPP_SHARED_API ImplPtr GetImpl() const = 0;
};
}} // namespace System::Net
