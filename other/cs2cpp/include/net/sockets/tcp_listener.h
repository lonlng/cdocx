/// @file net/sockets/tcp_listener.h
#pragma once

#include <system/shared_ptr.h>
#include <system/object.h>

#include <net/sockets/tcp_client.h>
#include <net/sockets/socket.h>
#include <net/ip_end_point.h>

namespace System {
namespace Net {
namespace Sockets {

/// Represents a listener for the TCP network services.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS TcpListener : public System::Object
{
    /// This type.
    typedef TcpListener ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the underlying network socket.
    /// @returns The underlying network socket.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> get_Server();
    /// Returns the underlying endpoint.
    /// @returns The underlying endpoint.
    ASPOSECPP_SHARED_API System::SharedPtr<EndPoint> get_LocalEndpoint();
    /// Gets a value that indicates if the current instance allows only one client to use a port.
    /// @returns A value that indicates if the current instance allows only one client to use a port.
    ASPOSECPP_SHARED_API bool get_ExclusiveAddressUse();
    /// Sets a value that indicates if the current instance allows only one client to use a port.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ExclusiveAddressUse(bool value);

    /// Constructs a new instance.
    /// @param localEP The local endpoint to which the listener socket must be bound.
    ASPOSECPP_SHARED_API TcpListener(System::SharedPtr<IPEndPoint> localEP);
    /// Constructs a new instance.
    /// @param localaddr The local IP address.
    /// @param port A port number to listen.
    ASPOSECPP_SHARED_API TcpListener(System::SharedPtr<IPAddress> localaddr, int32_t port);
    /// Constructs a new instance.
    /// @param port A port number to listen.
    ASPOSECPP_SHARED_API TcpListener(int32_t port);

    /// Creates a new instance using the specified port number.
    /// @param port A port number that is used to create the TcpListener-class instance.
    /// @returns A newly created TcpListener-class instance.
    static ASPOSECPP_SHARED_API System::SharedPtr<TcpListener> Create(int32_t port);
    /// Enables or disables the NAT traversal.
    /// @param allowed A value that indicates if the NAT traversal must be enabled or disabled.
    ASPOSECPP_SHARED_API void AllowNatTraversal(bool allowed);
    /// Starts listening for the incoming connections.
    ASPOSECPP_SHARED_API void Start();
    /// Starts listening for the incoming connections.
    /// @param backlog The size of the pending connections queue.
    ASPOSECPP_SHARED_API void Start(int32_t backlog);
    /// Stops listening for the incoming connections.
    ASPOSECPP_SHARED_API void Stop();
    /// Returns a value that indicates if there are pending connection requests.
    /// @returns True when the pending connection requests are present, otherwise false.
    ASPOSECPP_SHARED_API bool Pending();
    /// Accepts the pending connection request and returns the socket that is used to send and receive data.
    /// @returns The socket that is used for sending and receiving data.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> AcceptSocket();
    /// Accepts the pending connection request and returns the TcpClient-class instance that is used for sending and
    /// receiving data.
    /// @returns The TcpClient-class instance that is used for sending and receiving data.
    ASPOSECPP_SHARED_API System::SharedPtr<TcpClient> AcceptTcpClient();
    /// Initiates an asynchronous accept operation.
    /// @param callback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous accept operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginAcceptSocket(AsyncCallback callback, System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous accept operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous accept operation.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> EndAcceptSocket(System::SharedPtr<IAsyncResult> asyncResult);
    /// Initiates an asynchronous accept operation.
    /// @param callback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous accept operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginAcceptTcpClient(AsyncCallback callback, System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous accept operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous accept operation.
    ASPOSECPP_SHARED_API System::SharedPtr<TcpClient> EndAcceptTcpClient(System::SharedPtr<IAsyncResult> asyncResult);

protected:
    /// Returns a value that indicates if the current instance is actively listening for the client connections.
    /// @returns A value that indicates if the current instance is actively listening for the client connections.
    ASPOSECPP_SHARED_API bool get_Active();

private:
    /// The underlying endpoint.
    System::SharedPtr<IPEndPoint> m_ServerSocketEP;
    /// The underlying network socket.
    System::SharedPtr<Socket> m_ServerSocket;
    /// A value that indicates if the current instance is actively listening for the client connections.
    bool m_Active;
    /// A value that indicates if the current instance allows only one client to use a port.
    bool m_ExclusiveAddressUse;
};
} // namespace Sockets
} // namespace Net
} // namespace System
