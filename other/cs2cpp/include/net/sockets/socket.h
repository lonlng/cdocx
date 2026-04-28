/// @file net/sockets/socket.h
#pragma once

#include <cstdint>
#include <system/collections/ilist.h>
#include <system/enum_helpers.h>
#include <system/idisposable.h>
#include <system/shared_ptr.h>
#include <system/details/array_view.h>

#include <net/end_point.h>
#include <net/ip_address.h>
#include <net/linger_option.h>
#include <net/socket_type.h>
#include <net/sockets/address_family.h>
#include <net/sockets/io_control_code.h>
#include <net/sockets/ip_packet_information.h>
#include <net/sockets/protocol_type.h>
#include <net/sockets/select_mode.h>
#include <net/sockets/socket_error.h>
#include <net/sockets/socket_flags.h>
#include <net/sockets/socket_option_level.h>
#include <net/sockets/socket_option_name.h>
#include <net/sockets/socket_shutdown.h>
#include <system/array_segment.h>


namespace System { namespace Details {
ASPOSECPP_3RD_PARTY_CLASS(io_service_impl);
ASPOSECPP_3RD_PARTY_CLASS(socket_impl);
}} // namespace System::Details

namespace System { namespace Net { namespace Sockets {

/// The Socket class implements the Berkeley sockets interface.
class ASPOSECPP_SHARED_CLASS Socket : public System::IDisposable
{
    friend class SocketAsyncResult;
    friend class SocketCompletionHandler;

    /// This type.
    typedef Socket ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a value that indicates if the current host supports IPv4.
    /// @returns A value that indicates if the current host supports IPv4.
    static ASPOSECPP_SHARED_API bool get_SupportsIPv4();
    /// Returns a value that indicates if the operating system and network adaptors support IPv4.
    /// @returns A value that indicates if the operating system and network adaptors support IPv4.
    static ASPOSECPP_SHARED_API bool get_OSSupportsIPv4();
    /// Returns a value that indicates if the operating system and network adaptors support IPv6.
    /// @returns A value that indicates if the operating system and network adaptors support IPv6.
    static ASPOSECPP_SHARED_API bool get_OSSupportsIPv6();
    /// Gets the number of bytes received from the network and available for reading.
    /// @returns The number of bytes received from the network and available for reading.
    ASPOSECPP_SHARED_API int32_t get_Available();
    /// Returns the local endpoint.
    /// @returns The local endpoint.
    ASPOSECPP_SHARED_API System::SharedPtr<EndPoint> get_LocalEndPoint();
    /// Returns the remote endpoint.
    /// @returns The remote endpoint.
    ASPOSECPP_SHARED_API System::SharedPtr<EndPoint> get_RemoteEndPoint();
    /// Gets a value that indicates if the socket is in the blocking mode.
    /// @returns A value that indicates if the socket is in the blocking mode.
    ASPOSECPP_SHARED_API bool get_Blocking();
    /// Sets a value that indicates if the socket is in the blocking mode.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Blocking(bool value);
    /// Returns a value that indicates if the socket is connected to the remote host.
    /// @returns A value that indicates if the socket is connected to the remote host.
    ASPOSECPP_SHARED_API bool get_Connected();
    /// Returns the address family.
    /// @returns The address family.
    ASPOSECPP_SHARED_API System::Net::Sockets::AddressFamily get_AddressFamily();
    /// Returns the socket type.
    /// @returns The socket type.
    ASPOSECPP_SHARED_API System::Net::Sockets::SocketType get_SocketType();
    /// Returns the protocol type.
    /// @returns The protocol type.
    ASPOSECPP_SHARED_API System::Net::Sockets::ProtocolType get_ProtocolType();
    /// Returns a value that indicates if the socket is bound to a specific local port.
    /// @returns A value that indicates if the socket is bound to a specific local port.
    ASPOSECPP_SHARED_API bool get_IsBound();
    /// Gets a value that indicates if only one process can bind the socket to a port.
    /// @returns A value that indicates if only one process can bind the socket to a port.
    ASPOSECPP_SHARED_API bool get_ExclusiveAddressUse();
    /// Sets a value that indicates if only one process can bind the socket to a port.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ExclusiveAddressUse(bool value);
    /// Gets the receive buffer size.
    /// @returns The receive buffer size.
    ASPOSECPP_SHARED_API int32_t get_ReceiveBufferSize();
    /// Sets the receive buffer size.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ReceiveBufferSize(int32_t value);
    /// Gets the send buffer size.
    /// @returns The send buffer size.
    ASPOSECPP_SHARED_API int32_t get_SendBufferSize();
    /// Sets the send buffer size.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_SendBufferSize(int32_t value);
    /// Gets a period after which a 'Receive' call will time out.
    /// @returns A period after which a 'Receive' call will time out.
    ASPOSECPP_SHARED_API int32_t get_ReceiveTimeout();
    /// Sets a period after which a 'Receive' call will time out.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ReceiveTimeout(int32_t value);
    /// Gets a period after which a 'Send' call will time out.
    /// @returns A period after which a 'Send' call will time out.
    ASPOSECPP_SHARED_API int32_t get_SendTimeout();
    /// Sets a period after which a 'Send' call will time out.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_SendTimeout(int32_t value);
    /// Gets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @returns A value that indicates if the socket will delay closing in an attempt to send all pending data.
    ASPOSECPP_SHARED_API System::SharedPtr<LingerOption> get_LingerState();
    /// Sets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_LingerState(System::SharedPtr<LingerOption> value);
    /// Gets a value that indicates if the socket is using the Nagle algorithm.
    /// @returns A value that indicates if the socket is using the Nagle algorithm.
    ASPOSECPP_SHARED_API bool get_NoDelay();
    /// Sets a value that indicates if the socket is using the Nagle algorithm.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_NoDelay(bool value);
    /// Gets the TTL value.
    /// @returns The TTL value.
    ASPOSECPP_SHARED_API int16_t get_Ttl();
    /// Sets the TTL value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Ttl(int16_t value);
    /// Gets a value that indicates if the socket allows IP datagrams to be fragmented.
    /// @returns A value that indicates if the socket allows IP datagrams to be fragmented.
    ASPOSECPP_SHARED_API bool get_DontFragment();
    /// Sets a value that indicates if the socket allows IP datagrams to be fragmented.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_DontFragment(bool value);
    /// Gets a value that indicates if the socket receives outgoing multicast packets.
    /// @returns A value that indicates if the socket receives outgoing multicast packets.
    ASPOSECPP_SHARED_API bool get_MulticastLoopback();
    /// Sets a value that indicates if the socket receives outgoing multicast packets.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MulticastLoopback(bool value);
    /// Gets a value that indicates if the socket allows broadcast packets.
    /// @returns A value that indicates if the socket allows broadcast packets.
    ASPOSECPP_SHARED_API bool get_EnableBroadcast();
    /// Sets a value that indicates if the socket allows broadcast packets.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_EnableBroadcast(bool value);
    /// Gets a value indicates if the socket is in the dual-mode.
    /// @returns A value indicates if the socket is in the dual-mode.
    ASPOSECPP_SHARED_API bool get_DualMode();
    /// Sets a value indicates if the socket is in the dual-mode.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_DualMode(bool value);

    /// Constructs a new instance.
    /// @param socketType The socket type.
    /// @param protocolType The protocol type.
    ASPOSECPP_SHARED_API Socket(System::Net::Sockets::SocketType socketType,
                                System::Net::Sockets::ProtocolType protocolType);
    /// Constructs a new instance.
    /// @param addressFamily The address family.
    /// @param socketType The socket type.
    /// @param protocolType The protocol type.
    ASPOSECPP_SHARED_API Socket(System::Net::Sockets::AddressFamily addressFamily,
                                System::Net::Sockets::SocketType socketType,
                                System::Net::Sockets::ProtocolType protocolType);

    /// Initiates an asynchronous send operation.
    /// @param buffer A buffer to read data from.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behaviour.
    /// @param callback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous send operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous send operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginSend(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                   int32_t size, SocketFlags socketFlags,
                                                                   AsyncCallback callback,
                                                                   System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous send operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous send operation.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t EndSend(System::SharedPtr<IAsyncResult> asyncResult);
    /// Waits until the specified asynchronous send operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous send operation.
    /// @param errorCode The output parameter where the error code will be assigned when the send operation fails.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t EndSend(System::SharedPtr<IAsyncResult> asyncResult, SocketError& errorCode);

    /// Initiates an asynchronous write operation.
    /// @param buffer A buffer where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The receive behaviour.
    /// @param callback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous receive operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous receive operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginReceive(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                      int32_t size, SocketFlags socketFlags,
                                                                      AsyncCallback callback,
                                                                      System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous receive operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous receive operation.
    /// @returns The number of bytes that are received.
    ASPOSECPP_SHARED_API int32_t EndReceive(System::SharedPtr<IAsyncResult> asyncResult);
    /// Waits until the specified asynchronous receive operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous receive operation.
    /// @param errorCode The output parameter where the error code will be assigned when the receive operation fails.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t EndReceive(System::SharedPtr<IAsyncResult> asyncResult, SocketError& errorCode);

    /// Binds the socket with to the specified local endpoint.
    /// @param localEP The local endpoint to which the socket is bound.
    ASPOSECPP_SHARED_API void Bind(System::SharedPtr<EndPoint> localEP);
    /// Establishes a connection to the specified remote endpoint.
    /// @param remoteEP The remote endpoint.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<EndPoint> remoteEP);
    /// Establishes a connection to the specified remote endpoint.
    /// @param address The remote host IP address.
    /// @param port The port number of the remote host.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<IPAddress> address, int32_t port);
    /// Establishes a connection to the specified remote endpoint.
    /// @param host The remote host name.
    /// @param port The port number of the remote host.
    ASPOSECPP_SHARED_API void Connect(String host, int32_t port);
    /// Establishes a connection to the specified remote endpoint.
    /// @param addresses The IP addresses of the remote host.
    /// @param port The port number of the remote host.
    ASPOSECPP_SHARED_API void Connect(System::ArrayPtr<System::SharedPtr<IPAddress>> addresses, int32_t port);

    /// Initiates an asynchronous connect operation.
    /// @param remoteEP The remote endpoint.
    /// @param callback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult>
        BeginConnect(System::SharedPtr<EndPoint> remoteEP, AsyncCallback callback, System::SharedPtr<Object> state);
    /// Initiates an asynchronous connect operation.
    /// @param host The remote host name.
    /// @param port The port number of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult>
        BeginConnect(String host, int32_t port, AsyncCallback requestCallback, System::SharedPtr<Object> state);
    /// Initiates an asynchronous connect operation.
    /// @param address The remote host IP address.
    /// @param port The port number of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each  asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginConnect(System::SharedPtr<IPAddress> address,
                                                                      int32_t port, AsyncCallback requestCallback,
                                                                      System::SharedPtr<Object> state);
    /// Initiates an asynchronous connect operation.
    /// @param addresses The IP addresses of the remote host.
    /// @param port The port number of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult>
        BeginConnect(System::ArrayPtr<System::SharedPtr<IPAddress>> addresses, int32_t port,
                     AsyncCallback requestCallback, System::SharedPtr<Object> state);

    /// Closes the socket connection.
    ASPOSECPP_SHARED_API void Close();
    /// Closes the socket connection with the specified timeout to allow queued data to be sent.
    /// @param timeout A number of milliseconds to wait.
    ASPOSECPP_SHARED_API void Close(int timeout);

    /// Waits until the specified asynchronous connect operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous connect operation.
    ASPOSECPP_SHARED_API void EndConnect(System::SharedPtr<IAsyncResult> asyncResult);

    /// Changes the socket state to 'listen'.
    /// @param backlog The maximum number of pending connections.
    ASPOSECPP_SHARED_API void Listen(int32_t backlog);
    /// Creates a new socket for the newly created connection.
    /// @returns A new socket for the newly created connection.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> Accept();
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param size The number of bytes from the specified data that must be send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> buffer, int32_t size, SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param size The number of bytes from the specified data that must be send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::Details::ArrayView<uint8_t> buffer, int32_t size, SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param size The number of bytes from the specified data that must be send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t Send(System::Details::StackArray<uint8_t, N> &buffer, int32_t size, SocketFlags socketFlags)
    {
        return Send(static_cast<System::Details::ArrayView<uint8_t>>(buffer), size, socketFlags);
    }

    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> buffer, SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::Details::ArrayView<uint8_t> buffer, SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t Send(System::Details::StackArray<uint8_t, N> &buffer, SocketFlags socketFlags)
    {
        return Send(static_cast<System::Details::ArrayView<uint8_t>>(buffer), socketFlags);
    }

    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> buffer);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::Details::ArrayView<uint8_t> buffer);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t Send(System::Details::StackArray<uint8_t, N> &buffer)
    {
        return Send(static_cast<System::Details::ArrayView<uint8_t>>(buffer));
    }

    /// Sends the specified data to the socket.
    /// @param buffers A collection of byte arrays from which data must be sent.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers);
    /// Sends the specified data to the socket.
    /// @param buffers A collection of byte arrays from which data must be sent.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers,
                                      SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffers A collection of byte arrays from which data must be sent.
    /// @param socketFlags The send behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the send operation fails.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers,
                                      SocketFlags socketFlags, SocketError& errorCode);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                      SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                      SocketFlags socketFlags);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t Send(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size, SocketFlags socketFlags)
    {
        return Send(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size, socketFlags);
    }

    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the send operation fails.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                      SocketFlags socketFlags, SocketError& errorCode);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the send operation fails.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t Send(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                      SocketFlags socketFlags, SocketError& errorCode);
    /// Sends the specified data to the socket.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the send operation fails.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t Send(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                 SocketFlags socketFlags, SocketError& errorCode)
    {
        return Send(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size, socketFlags, errorCode);
    }

    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                        SocketFlags socketFlags, System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                        SocketFlags socketFlags, System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes in the specified array starting from the 'offset' parameter.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t SendTo(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                   SocketFlags socketFlags, System::SharedPtr<EndPoint> remoteEP)
    {
        return SendTo(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size, socketFlags, remoteEP);
    }

    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param size The number of bytes in the specified array.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::ArrayPtr<uint8_t> buffer, int32_t size, SocketFlags socketFlags,
                                        System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param size The number of bytes in the specified array.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::Details::ArrayView<uint8_t> buffer, int32_t size, SocketFlags socketFlags,
                                        System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param size The number of bytes in the specified array.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t SendTo(System::Details::StackArray<uint8_t, N> &buffer, int32_t size, SocketFlags socketFlags,
                   System::SharedPtr<EndPoint> remoteEP)
    {
        return SendTo(static_cast<System::Details::ArrayView<uint8_t>>(buffer), size, socketFlags, remoteEP);
    }

    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::ArrayPtr<uint8_t> buffer, SocketFlags socketFlags,
                                        System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::Details::ArrayView<uint8_t> buffer, SocketFlags socketFlags,
                                        System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param socketFlags The send behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t SendTo(System::Details::StackArray<uint8_t, N> &buffer, SocketFlags socketFlags,
                   System::SharedPtr<EndPoint> remoteEP)
    {
        return SendTo(static_cast<System::Details::ArrayView<uint8_t>>(buffer), socketFlags, remoteEP);
    }
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::ArrayPtr<uint8_t> buffer, System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    ASPOSECPP_SHARED_API int32_t SendTo(System::Details::ArrayView<uint8_t> buffer, System::SharedPtr<EndPoint> remoteEP);
    /// Sends the specified data to the specified endpoint.
    /// @param buffer The data to send.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of sent bytes.
    template<std::size_t N>
    int32_t SendTo(System::Details::StackArray<uint8_t, N> &buffer, System::SharedPtr<EndPoint> remoteEP)
    {
        return SendTo(static_cast<System::Details::ArrayView<uint8_t>>(buffer), remoteEP);
    }
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::ArrayPtr<uint8_t> buffer, int32_t size, SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::Details::ArrayView<uint8_t> buffer, int32_t size, SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t Receive(System::Details::StackArray<uint8_t, N> &buffer, int32_t size, SocketFlags socketFlags)
    {
        return Receive(static_cast<System::Details::ArrayView<uint8_t>>(buffer), size, socketFlags);
    }
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::ArrayPtr<uint8_t> buffer, SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::Details::ArrayView<uint8_t> buffer, SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t Receive(System::Details::StackArray<uint8_t, N> &buffer, SocketFlags socketFlags)
    {
        return Receive(static_cast<System::Details::ArrayView<uint8_t>>(buffer), socketFlags);
    }
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::ArrayPtr<uint8_t> buffer);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::Details::ArrayView<uint8_t> buffer);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t Receive(System::Details::StackArray<uint8_t, N> &buffer)
    {
        return Receive(static_cast<System::Details::ArrayView<uint8_t>>(buffer));
    }
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                         SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                         SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t Receive(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                    SocketFlags socketFlags)
    {
        return Receive(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size, socketFlags);
    }
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the receive operation fails.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                         SocketFlags socketFlags, SocketError& errorCode);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the receive operation fails.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                         SocketFlags socketFlags, SocketError& errorCode);
    /// Receives data from the socket and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param errorCode The output parameter where the error code will be assigned when the receive operation fails.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t Receive(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                    SocketFlags socketFlags, SocketError& errorCode)
    {
        return Receive(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size, socketFlags, errorCode);
    }
    /// Receives data from the socket and writes it to the specified byte arrays.
    /// @param buffers The byte arrays where the received data will be assigned.
    /// @returns The number of bytes that are received.
    ASPOSECPP_SHARED_API int32_t Receive(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers);
    /// Receives data from the socket and writes it to the specified byte arrays.
    /// @param buffers The byte arrays where the received data will be assigned.
    /// @param socketFlags The receive behaviour.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers,
                                         SocketFlags socketFlags);
    /// Receives data from the socket and writes it to the specified byte arrays.
    /// @param buffers The byte arrays where the received data will be assigned.
    /// @param socketFlags The receive behaviour.
    /// @param errorCode The output parameter where the error code will be assigned when the receive operation fails.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t Receive(System::SharedPtr<Collections::Generic::IList<ArraySegment<uint8_t>>> buffers,
                                         SocketFlags socketFlags, SocketError& errorCode);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @param ipPacketInformation The output parameter where information about the packet will be assigned.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveMessageFrom(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                                    SocketFlags& socketFlags, System::SharedPtr<EndPoint>& remoteEP,
                                                    IPPacketInformation& ipPacketInformation);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @param ipPacketInformation The output parameter where information about the packet will be assigned.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveMessageFrom(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                                    SocketFlags& socketFlags, System::SharedPtr<EndPoint>& remoteEP,
                                                    IPPacketInformation& ipPacketInformation);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @param ipPacketInformation The output parameter where information about the packet will be assigned.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t ReceiveMessageFrom(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                               SocketFlags& socketFlags, System::SharedPtr<EndPoint>& remoteEP,
                               IPPacketInformation& ipPacketInformation)
    {
        return ReceiveMessageFrom(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size,
                                  socketFlags, remoteEP, ipPacketInformation);
    }
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::ArrayPtr<uint8_t> buffer, int32_t offset, int32_t size,
                                             SocketFlags socketFlags, System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::Details::ArrayView<uint8_t> buffer, int32_t offset, int32_t size,
                                             SocketFlags socketFlags, System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t ReceiveFrom(System::Details::StackArray<uint8_t, N> &buffer, int32_t offset, int32_t size,
                        SocketFlags socketFlags, System::SharedPtr<EndPoint>& remoteEP)
    {
        return ReceiveFrom(static_cast<System::Details::ArrayView<uint8_t>>(buffer), offset, size,
                           socketFlags, remoteEP);
    }
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::ArrayPtr<uint8_t> buffer, int32_t size, SocketFlags socketFlags,
                                             System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::Details::ArrayView<uint8_t> buffer, int32_t size, SocketFlags socketFlags,
                                             System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param size The number of bytes to receive that will be assigned to the specified byte array from the 'offset'
    /// index.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t ReceiveFrom(System::Details::StackArray<uint8_t, N> &buffer, int32_t size, SocketFlags socketFlags,
                        System::SharedPtr<EndPoint>& remoteEP)
    {
        return ReceiveFrom(static_cast<System::Details::ArrayView<uint8_t>>(buffer), size, socketFlags, remoteEP);
    }
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::ArrayPtr<uint8_t> buffer, SocketFlags socketFlags,
                                             System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::Details::ArrayView<uint8_t> buffer, SocketFlags socketFlags,
                                             System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param socketFlags The receive behavior.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t ReceiveFrom(System::ArrayPtr<uint8_t> buffer, SocketFlags socketFlags,
                        System::SharedPtr<EndPoint>& remoteEP)
    {
        return ReceiveFrom(static_cast<System::Details::ArrayView<uint8_t>>(buffer), socketFlags, remoteEP);
    }
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::ArrayPtr<uint8_t> buffer, System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    ASPOSECPP_SHARED_API int32_t ReceiveFrom(System::Details::ArrayView<uint8_t> buffer, System::SharedPtr<EndPoint>& remoteEP);
    /// Receives data from the specified endpoint and writes it to the specified byte array.
    /// @param buffer The byte array where the received data will be assigned.
    /// @param remoteEP The remote endpoint.
    /// @returns The number of received bytes.
    template<std::size_t N>
    int32_t ReceiveFrom(System::Details::StackArray<uint8_t, N> &buffer, System::SharedPtr<EndPoint>& remoteEP)
    {
        return ReceiveFrom(static_cast<System::Details::ArrayView<uint8_t>>(buffer), remoteEP);
    }
    /// Sets low-level operating modes for the socket.
    /// @param ioControlCode The control code of the operation to perform.
    /// @param optionInValue The byte array that contains the input data.
    /// @param optionOutValue The byte array that contains the output data.
    /// @returns The number of bytes in the @p optionOutValue parameter.
    ASPOSECPP_SHARED_API int32_t IOControl(int32_t ioControlCode, System::ArrayPtr<uint8_t> optionInValue,
                                           System::ArrayPtr<uint8_t> optionOutValue);
    /// Sets low-level operating modes for the socket.
    /// @param ioControlCode The control code of the operation to perform.
    /// @param optionInValue The byte array that contains the input data.
    /// @param optionOutValue The byte array that contains the output data.
    /// @returns The number of bytes in the @p optionOutValue parameter.
    ASPOSECPP_SHARED_API int32_t IOControl(IOControlCode ioControlCode, System::ArrayPtr<uint8_t> optionInValue,
                                           System::ArrayPtr<uint8_t> optionOutValue);
    /// Sets the specified socket option to the specified value.
    /// @param optionLevel The socket option level.
    /// @param optionName The name of the option that must be updated.
    /// @param optionValue The value that must be set to the specified option.
    ASPOSECPP_SHARED_API void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName,
                                              int32_t optionValue);
    /// Sets the specified socket option to the specified value.
    /// @param optionLevel The socket option level.
    /// @param optionName The name of the option that must be updated.
    /// @param optionValue The value that must be set to the specified option.
    ASPOSECPP_SHARED_API void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName,
                                              System::ArrayPtr<uint8_t> optionValue);
    /// Sets the specified socket option to the specified value.
    /// @param optionLevel The socket option level.
    /// @param optionName The name of the option that must be updated.
    /// @param optionValue The value that must be set to the specified option.
    ASPOSECPP_SHARED_API void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName,
                                              bool optionValue);
    /// Sets the specified socket option to the specified value.
    /// @param optionLevel The socket option level.
    /// @param optionName The name of the option that must be updated.
    /// @param optionValue The value that must be set to the specified option.
    ASPOSECPP_SHARED_API void SetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName,
                                              System::SharedPtr<Object> optionValue);
    /// Returns the value that corresponds to the specified option name.
    /// @param optionLevel The socket option level.
    /// @param optionName The option name.
    /// @returns The value that corresponds to the specified option name.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetSocketOption(SocketOptionLevel optionLevel,
                                                                   SocketOptionName optionName);
    /// Gets the value that corresponds to the specified option name.
    /// @param optionLevel The socket option level.
    /// @param optionName The option name.
    /// @param optionValue The output parameter where the corresponding value will be assigned.
    ASPOSECPP_SHARED_API void GetSocketOption(SocketOptionLevel optionLevel, SocketOptionName optionName,
                                              System::ArrayPtr<uint8_t> optionValue);
    /// Returns the value that corresponds to the specified option name.
    /// @param optionLevel The socket option level.
    /// @param optionName The option name.
    /// @param optionLength The option length.
    /// @returns The value that corresponds to the specified option name.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> GetSocketOption(SocketOptionLevel optionLevel,
                                                                   SocketOptionName optionName, int32_t optionLength);
    /// Returns the status of the socket based on the specified polling mode.
    /// @param microSeconds The amount of time in milliseconds to wait for a response.
    /// @param mode The polling mode.
    /// @returns The status of the socket based on the specified polling mode.
    ASPOSECPP_SHARED_API bool Poll(int32_t microSeconds, SelectMode mode);
    /// Disables the send and receive operations of the socket.
    /// @param how Specifies the operation that will no longer be allowed.
    ASPOSECPP_SHARED_API void Shutdown(SocketShutdown how);
    /// @copydoc System::IDisposable::Dispose
    ASPOSECPP_SHARED_API void Dispose() override;

    /// Destructs the current instance.
    virtual ASPOSECPP_SHARED_API ~Socket();

    /// The socket implementation.
    typedef std::shared_ptr<System::Details::socket_impl> ImplPtr;
    /// Returns a pointer to implementation.
    ImplPtr GetImpl() const;

    /// Sets the connection timeout.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ConnectionTimeout(int32_t value);


private:
    /// Provides the I/O functionality.
    std::shared_ptr<System::Details::io_service_impl> io_service;
    /// A pointer to implementation.
    ImplPtr socket;
    /// The protocol type.
    ProtocolType protocol;
    /// The socket type.
    System::Net::Sockets::SocketType socketType;
    /// The remote endpoint.
    System::SharedPtr<EndPoint> rightEndPoint;
    /// The connection timeout.
    int32_t connectionTimeout;
    /// A period after which a 'Receive' call will time out.
    int32_t receiveTimeout;
    /// A period after which a 'Send' call will time out.
    int32_t sendTimeout;
};
}}} // namespace System::Net::Sockets
