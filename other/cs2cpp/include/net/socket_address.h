/// @file net/socket_address.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <cstdint>

#include <net/sockets/address_family.h>

namespace System {
namespace Net {

/// Used to store serialized information about the EndPoint class instances.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SocketAddress : public System::Object
{
    /// This type.
    typedef SocketAddress ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the address family.
    /// @returns The address family.
    ASPOSECPP_SHARED_API Sockets::AddressFamily get_Family();
    /// Returns the underlying buffer size.
    /// @returns The underlying buffer size.
    ASPOSECPP_SHARED_API int32_t get_Size();

    /// Gets a value of the underlying buffer at the specified index.
    /// @param offset The element index.
    /// @returns A value of the underlying buffer at the specified index.
    ASPOSECPP_SHARED_API uint8_t idx_get(int32_t offset);
    /// Sets a value of the underlying buffer at the specified index.
    /// @param offset The element index.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void idx_set(int32_t offset, uint8_t value);

    /// Constructs a new instance.
    /// @param family The address family.
    ASPOSECPP_SHARED_API SocketAddress(Sockets::AddressFamily family);
    /// Constructs a new instance.
    /// @param family The address family.
    /// @param size The underlying buffer size.
    ASPOSECPP_SHARED_API SocketAddress(Sockets::AddressFamily family, int32_t size);

    /// Compares objects using C# Object.Equals semantics.
    /// @param comparand Object to compare current one to.
    /// @return True if objects are considered equal and false otherwise.
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> comparand) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
};
} // namespace Net
} // namespace System
