/// @file net/sockets/udp_client.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/idisposable.h>
#include <system/iasyncresult.h>
#include <system/async_callback.h>
#include <system/array.h>
#include <net/sockets/socket.h>
#include <net/sockets/address_family.h>
#include <net/ip_end_point.h>
#include <net/ip_address.h>
#include <cstdint>

namespace System { namespace Net { namespace Sockets {

/// Provides User Datagram Protocol (UDP) network services.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS UdpClient : public System::IDisposable
{
    /// This type.
    typedef UdpClient ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Used to provide the underlying network socket.
    /// @returns The underlying network socket.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> get_Client();
    /// Used to provide the underlying network socket.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Client(System::SharedPtr<Socket> value);
    /*
    ASPOSECPP_SHARED_API int32_t get_Available();
    ASPOSECPP_SHARED_API int16_t get_Ttl();
    ASPOSECPP_SHARED_API void set_Ttl(int16_t value);
    ASPOSECPP_SHARED_API bool get_DontFragment();
    ASPOSECPP_SHARED_API void set_DontFragment(bool value);
    ASPOSECPP_SHARED_API bool get_MulticastLoopback();
    ASPOSECPP_SHARED_API void set_MulticastLoopback(bool value);
    ASPOSECPP_SHARED_API bool get_EnableBroadcast();
    ASPOSECPP_SHARED_API void set_EnableBroadcast(bool value);
    ASPOSECPP_SHARED_API bool get_ExclusiveAddressUse();
    ASPOSECPP_SHARED_API void set_ExclusiveAddressUse(bool value);
    */

    /// Initializes a new instance of the UdpClient class.
    ASPOSECPP_SHARED_API UdpClient();
    /// Initializes a new instance of the UdpClient class.
    /// @param family value that specifies the addressing scheme of the socket.
    ASPOSECPP_SHARED_API UdpClient(AddressFamily family);
    /// Initializes a new instance of the UdpClient class.
    /// @param port the local port number from which you intend to communicate.
    ASPOSECPP_SHARED_API UdpClient(int32_t port);
    /// Initializes a new instance of the UdpClient class.
    /// @param port the local port number from which you intend to communicate.
    /// @param family value that specifies the addressing scheme of the socket.
    ASPOSECPP_SHARED_API UdpClient(int32_t port, AddressFamily family);
    /// Initializes a new instance of the UdpClient class.
    /// param local EP the local endpoint to which you bind the UDP connection.
    ASPOSECPP_SHARED_API UdpClient(System::SharedPtr<IPEndPoint> localEP);
    /// Creates a new instance of the UdpClient class and connects to the
    /// specified remote host on the specified port.
    /// @param hostname The name of the remote DNS host to which you intend to connect.
    /// @param port The local port number from which you intend to communicate.
    ASPOSECPP_SHARED_API UdpClient(String hostname, int32_t port);
    /// Closes the UDP connection.
    ASPOSECPP_SHARED_API void Close();
    /// Releases the managed and unmanaged resources used by the UdpClient.
    ASPOSECPP_SHARED_API void Dispose() override;
    /// Establishes a connection to the specified port on the specified host.
    /// @param hostname The name of the remote DNS host to which you intend to connect.
    /// @param port The local port number from which you intend to communicate.
    ASPOSECPP_SHARED_API void Connect(String hostname, int32_t port);
    /// Establishes a connection with the host at the specified address on the specified port.
    /// @param addr The IPAddress of the remote host to which to send data.
    /// @param port The local port number from which you intend to communicate.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<IPAddress> addr, int32_t port);
    /// Establishes a connection to a remote end point.
    /// @param endPoint the endpoint to which you bind the UDP connection.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<IPEndPoint> endPoint);

    /// Sends a UDP datagram to the host at the remote end point.
    /// @param dgram An array of type Byte to send
    /// @param bytes The number of bytes in the datagram.
    /// @param endPoint An IPEndPoint that represents the host and port to which to send the datagram.
    /// @returns The number of bytes that are sent.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> dgram, int32_t bytes,
                                      System::SharedPtr<IPEndPoint> endPoint);
    /// Sends a UDP datagram to the specified port on the specified remote host.
    /// @param dgram An array of type Byte to send
    /// @param bytes The number of bytes in the datagram.
    /// @param hostname A name of the remote host.
    /// @param port A remote port number.
    /// @returns The number of bytes that are sent.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> dgram, int32_t bytes, String hostname, int32_t port);
    /// Sends a UDP datagram to a remote host.
    /// @param dgram An array of type Byte to send.
    /// @param bytes The number of bytes in the datagram.
    /// @returns The number of bytes that are sent.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> dgram, int32_t bytes);

    /// Returns a datagram sent by a server.
    /// @param remoteEP An IPEndPoint that represents the remote host from which the data was sent.
    /// @returns A byte array where received data will be assigned.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> Receive(System::SharedPtr<IPEndPoint>& remoteEP);

protected:
    /// Gets a value that indicates if the current instance is actively listening for the client connections.
    /// @returns A value that indicates if the current instance is actively listening for the client connections.
    ASPOSECPP_SHARED_API bool get_Active();
    /// Sets a value that indicates if the current instance is actively listening for the client connections.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Active(bool value);
    /// Disposes the current instance. This method also disposes the underlying socket.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    ASPOSECPP_SHARED_API virtual void Dispose(bool disposing);
    /// Destructs the current instance.
    ASPOSECPP_SHARED_API ~UdpClient() override;

private:
    /// The maximum UDP packet size.
    static const int32_t MaxUDPSize;
    /// The underlying network socket.
    System::SharedPtr<Socket> m_ClientSocket;
    /// A value that indicates if the current instance is actively listening for the client connections.
    bool m_Active;
    /// The internal buffer that is used in the 'Receive' method.
    System::ArrayPtr<uint8_t> m_Buffer;
    /// An address family.
    AddressFamily m_Family;
    /// Indicates if the current instance is disposed.
    bool m_CleanedUp;
    /// Indicates if the socket allows receiving and sending broadcast packets.
    bool m_IsBroadcast;

    /// Frees the internal resources.
    void FreeResources();
    /// Checks if the socket for the specified address allows receiving and sending broadcast packets.
    /// @returns True when the socket for the specified address allows receiving and sending broadcast packets,
    /// otherwise false.
    void CheckForBroadcast(System::SharedPtr<IPAddress> ipAddress);
    /// Checks if the socket for the specified address allows receiving and sending broadcast packets.
    /// @returns True when the socket for the specified address allows receiving and sending broadcast packets,
    /// otherwise false.
    static bool IsBroadcast(System::SharedPtr<IPAddress> address);
    /// Initializes the internal resources.
    void createClientSocket();
};

}}} // namespace System::Net::Sockets
