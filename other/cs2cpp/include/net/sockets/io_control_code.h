/// @file net/sockets/io_control_code.h
#pragma once

#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the IO control codes.
enum class IOControlCode : int64_t
{
    /// Enable or disable the asynchronous I/O mode of the socket.
    AsyncIO = 0x8004667D,
    /// Mark the socket as nonblocking.
    NonBlockingIO = 0x8004667E,
    /// Return the number of bytes available for reading.
    DataToRead = 0x4004667F,
    /// Return information about out-of-band data waiting to be received.
    OobDataRead = 0x40047307,
    /// Associate this socket with the specified handle of a companion interface.
    AssociateHandle = 0x88000001,
    /// Replace the oldest queued datagram with an incoming one when the incoming message queues are full.
    EnableCircularQueuing = 0x28000002,
    /// Discards current contents of the sending queue associated with this socket.
    Flush = 0x28000004,
    /// Return a SOCKADDR structure that contains the broadcast address for the address family of the current socket.
    GetBroadcastAddress = 0x48000005,
    /// Retrieve a pointer to the specified extension function supported by the associated service provider.
    GetExtensionFunctionPointer = 0xC8000006,
    /// Retrieve the QOS structure associated with the socket.
    GetQos = 0xC8000007,
    /// Return the QOS attributes for the socket group.
    GetGroupQos = 0xC8000008,
    /// Control whether data sent by an application on the local computer (not necessarily by the same socket) in a
    /// multicast session will be received by a socket joined to the multicast destination group on the loopback
    /// interface.
    MultipointLoopback = 0x88000009,
    /// Control the number of times a multicast packet can be forwarded by a router, also known as TTL, or hop count.
    MulticastScope = 0x8800000A,
    /// Set the QOS attributes for the socket.
    SetQos = 0x8800000B,
    /// Set the QOS attributes for the socket group.
    SetGroupQos = 0x8800000C,
    /// Return a handle for the socket that is valid in the context of a companion interface.
    TranslateHandle = 0xC800000D,
    /// Return the interface addresses that can be used to connect to the specified remote address.
    RoutingInterfaceQuery = 0xC8000014,
    /// Enable receiving a notification when the local interface used to access a remote endpoint changes.
    RoutingInterfaceChange = 0x88000015,
    /// Return the list of the local interfaces that the socket can bind to.
    AddressListQuery = 0x48000016,
    /// Enable receiving a notification when the list of the local interfaces for the socket's protocol family changes.
    AddressListChange = 0x28000017,
    /// Retrieve the underlying provider's SOCKET handle.
    QueryTargetPnpHandle = 0x48000018,
    /// Control whether the socket receives notification when a namespace query becomes invalid.
    NamespaceChange = 0x88000019,
    /// Sort a list of IPv6 and IPv4 destination addresses to determine the best available address for making a
    /// connection.
    AddressListSort = 0xC8000019,
    /// Enable receiving all IPv4 packets on the network.
    ReceiveAll = 0x98000001,
    /// Enable receiving all multicast IPv4 packets on the network.
    ReceiveAllMulticast = 0x98000002,
    /// Enable receiving all IGMP packets on the network.
    ReceiveAllIgmpMulticast = 0x98000003,
    /// Control sending TCP keep-alive packets and the interval at which they are sent.
    KeepAliveValues = 0x98000004,
    /// This value is equal to the Winsock 2 'SIO_ABSORB_RTRALERT' constant.
    AbsorbRouterAlert = 0x98000005,
    /// Set the interface used for the outgoing unicast packets.
    UnicastInterface = 0x98000006,
    /// This value is equal to the Winsock 2 'SIO_LIMIT_BROADCASTS' constant.
    LimitBroadcasts = 0x98000007,
    /// Bind the socket to a specified interface index.
    BindToInterface = 0x98000008,
    /// Set the interface used for the outgoing multicast packets.
    MulticastInterface = 0x98000009,
    /// Join a multicast group using an interface identified by its index.
    AddMulticastGroupOnInterface = 0x9800000A,
    /// Remove the socket from a multicast group.
    DeleteMulticastGroupFromInterface = 0x9800000B
};
} // namespace Sockets
} // namespace Net
} // namespace System
