/// @file net/sockets/tcp_client.h
#pragma once

#include <system/shared_ptr.h>
#include <system/idisposable.h>

#include <net/sockets/socket.h>
#include <net/sockets/network_stream.h>
#include <net/ip_end_point.h>

namespace System {
namespace Net {
namespace Sockets {

/// Represents a client for the TCP network services.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS TcpClient : public System::IDisposable
{
    /// This type.
    typedef TcpClient ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the socket.
    /// @returns The socket.
    ASPOSECPP_SHARED_API System::SharedPtr<Socket> get_Client();
    /// Sets the socket.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Client(System::SharedPtr<Socket> value);
    /// Returns the number of bytes that are received and ready to read.
    /// @returns The number of bytes that are received and ready to read.
    ASPOSECPP_SHARED_API int32_t get_Available();
    /// Returns a value that indicates if the socket is connected to the remote host.
    /// @returns A value that indicates if the socket is connected to the remote host.
    ASPOSECPP_SHARED_API bool get_Connected();
    /// Gets a value that indicates if the current instance allows only one client to use a port.
    /// @returns A value that indicates if the current instance allows only one client to use a port.
    ASPOSECPP_SHARED_API bool get_ExclusiveAddressUse();
    /// Sets a value that indicates if the current instance allows only one client to use a port.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ExclusiveAddressUse(bool value);
    /// Gets the size of the buffer that is used for receiving data.
    /// @returns The size of the buffer that is used for receiving data.
    ASPOSECPP_SHARED_API int32_t get_ReceiveBufferSize();
    /// Sets the size of the buffer that is used for receiving data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ReceiveBufferSize(int32_t value);
    /// Gets the size of the buffer that is used for sending data.
    /// @returns The size of the buffer that is used for sending data.
    ASPOSECPP_SHARED_API int32_t get_SendBufferSize();
    /// Sets the size of the buffer that is used for sending data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_SendBufferSize(int32_t value);
    /// Gets a value that indicates an amount of time after which data receiving will time out.
    /// @returns A value that indicates an amount of time after which data receiving will time out.
    ASPOSECPP_SHARED_API int32_t get_ReceiveTimeout();
    /// Sets a value that indicates an amount of time after which data receiving will time out.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ReceiveTimeout(int32_t value);
    /// Gets a value that indicates an amount of time after which data sending will time out.
    /// @returns A value that indicates an amount of time after which data sending will time out.
    ASPOSECPP_SHARED_API int32_t get_SendTimeout();
    /// Sets a value that indicates an amount of time after which data sending will time out.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_SendTimeout(int32_t value);
    /// Gets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @returns A value that indicates if the socket will delay closing in an attempt to send all pending data.
    ASPOSECPP_SHARED_API System::SharedPtr<LingerOption> get_LingerState();
    /// Sets a value that indicates if the socket will delay closing in an attempt to send all pending data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_LingerState(System::SharedPtr<LingerOption> value);
    /// Gets a value that indicates if the current instance is using the Nagle algorithm.
    /// @returns A value that indicates if the current instance is using the Nagle algorithm.
    ASPOSECPP_SHARED_API bool get_NoDelay();
    /// Sets a value that indicates if the current instance is using the Nagle algorithm.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_NoDelay(bool value);

    /// Constructs a new instance.
    /// @param localEP The endpoint to which the socket is bound.
    ASPOSECPP_SHARED_API TcpClient(System::SharedPtr<IPEndPoint> localEP);
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API TcpClient();
    /// Constructs a new instance.
    /// @param family An address family.
    ASPOSECPP_SHARED_API TcpClient(AddressFamily family);
    /// Constructs a new instance.
    /// @param hostname A remote host name to connect.
    /// @param port A port of the remote host to connect.
    ASPOSECPP_SHARED_API TcpClient(String hostname, int32_t port);

    /// Establishes a connection to the specified remote host.
    /// @param hostname A remote host name to connect.
    /// @param port A port of the remote host to connect.
    ASPOSECPP_SHARED_API void Connect(String hostname, int32_t port);
    /// Establishes a connection to the specified remote host.
    /// @param address The IP address of a remote host.
    /// @param port A port of the remote host to connect.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<IPAddress> address, int32_t port);
    /// Establishes a connection to the specified remote host.
    /// @param remoteEP A remote host to connect.
    ASPOSECPP_SHARED_API void Connect(System::SharedPtr<IPEndPoint> remoteEP);
    /// Establishes a connection to the specified remote host.
    /// @param ipAddresses The IP addresses of a remote host.
    /// @param port A port of the remote host to connect.
    ASPOSECPP_SHARED_API void Connect(System::ArrayPtr<System::SharedPtr<IPAddress>> ipAddresses, int32_t port);
    /// Initiates an asynchronous connect operation.
    /// @param host A remote host name.
    /// @param port A port of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginConnect(String host, int32_t port, AsyncCallback requestCallback, System::SharedPtr<Object> state);
    /// Initiates an asynchronous connect operation.
    /// @param address The IP address of a remote host.
    /// @param port A port of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginConnect(System::SharedPtr<IPAddress> address, int32_t port, AsyncCallback requestCallback, System::SharedPtr<Object> state);
    /// Initiates an asynchronous connect operation.
    /// @param addresses The IP addresses of a remote host.
    /// @param port A port of the remote host.
    /// @param requestCallback A callback that will be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous connect operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous connect operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginConnect(System::ArrayPtr<System::SharedPtr<IPAddress>> addresses, int32_t port, AsyncCallback requestCallback, System::SharedPtr<Object> state);
    /// Waits until the specified asynchronous connect operation completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous connect operation.
    ASPOSECPP_SHARED_API void EndConnect(System::SharedPtr<IAsyncResult> asyncResult);
    /// Returns the stream that is used for sending and receiving data.
    /// @returns The stream that is used for sending and receiving data.
    ASPOSECPP_SHARED_API System::SharedPtr<NetworkStream> GetStream();
    /// Closes the connection and disposes the current instance.
    ASPOSECPP_SHARED_API void Close();

    /// Destructs the current instance.
    virtual ASPOSECPP_SHARED_API ~TcpClient();
};
} // namespace Sockets
} // namespace Net
} // namespace System
