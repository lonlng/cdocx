/// @file net/sockets/socket_option_name.h
#pragma once

#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Defines socket option names for the Socket class.
enum class SocketOptionName
{
    /// Record debugging information.
    Debug = 0x0001,
    /// Indicates if a socket is listening for an incoming connection.
    AcceptConnection = 0x0002,
    /// Indicates if a socket can be bound to the address that is already in use.
    ReuseAddress = 0x0004,
    /// Enables the 'Keep-Alive' packets for a socket connection.
    KeepAlive = 0x0008,
    /// Indicates if a packet is sent directly to the interface addresses.
    DontRoute = 0x0010,
    /// Indicates if a socket can send the broadcast messages.
    Broadcast = 0x0020,
    /// Bypass hardware when possible.
    UseLoopback = 0x0040,
    /// The system will block the process on the close attempt until it is able to transmit the data.
    Linger = 0x0080,
    /// Receives out-of-band data in the normal data stream.
    OutOfBandInline = 0x0100,
    /// Indicates if a socket will be closed without lingering.
    DontLinger = static_cast<int32_t>(~Linger),
    /// A socket will use the bound address exclusively.
    ExclusiveAddressUse = static_cast<int32_t>(~ReuseAddress),
    /// Specifies the send buffer size.
    SendBuffer = 0x1001,
    /// Specifies the receive buffer size.
    ReceiveBuffer = 0x1002,
    /// Specifies the minimum amount of data for the send operations.
    SendLowWater = 0x1003,
    /// Specifies the minimum amount of data for the receive operations.
    ReceiveLowWater = 0x1004,
    /// Specifies the timeout for the synchronous send operations.
    SendTimeout = 0x1005,
    /// Specifies the timeout for the synchronous receive operations.
    ReceiveTimeout = 0x1006,
    /// Returns the error status and clear.
    Error = 0x1007,
    /// Returns a socket type.
    Type = 0x1008,
    /// Indicates if the system should defer the ephemeral port allocation for the outbound connections.
    ReuseUnicastPort = 0x3007,
    /// This option is not supported. It was used to specify the maximum queue length for listening.
    MaxConnections = 0x7fffffff,
    /// Specifies the IP option that must be inserted to outgoing datagrams.
    IPOptions = 1,
    /// The header is included to outgoing datagrams.
    HeaderIncluded = 2,
    /// Change the IP header type of the service field.
    TypeOfService = 3,
    /// The IP time to live.
    IpTimeToLive = 4,
    /// Set the interface for the outgoing multicast packets.
    MulticastInterface = 9,
    /// The IP multicast time to live.
    MulticastTimeToLive = 10,
    /// The IP Multicast loopback.
    MulticastLoopback = 11,
    /// Add an IP group membership.
    AddMembership = 12,
    /// Drop an IP group membership.
    DropMembership = 13,
    /// Don't fragment the IP datagrams.
    DontFragment = 14,
    /// Join the IP group/source.
    AddSourceMembership = 15,
    /// Drop the IP group/source.
    DropSourceMembership = 16,
    /// Block the IP group/source.
    BlockSource = 17,
    /// Unblock the IP group/source.
    UnblockSource = 18,
    /// Receive packet information for IPv4.
    PacketInformation = 19,
    /// Delivers an integer containing the HOP count of the packet.
    HopLimit = 21,
    /// Enables restriction of an IPv6 socket to the specified scope.
    IPProtectionLevel = 23,
    /// The socket is restricted to send and receive IPv6 packets only.
    IPv6Only = 27,
    /// Disables the Nagle algorithm for coalescing the send packets.
    NoDelay = 1,
    /// Use the urgent data as defined in RFC-1222.
    BsdUrgent = 2,
    /// Use the expedited data as defined in RFC-1222.
    Expedited = 2,
    /// Send the UDP datagrams with a checksum set to zero.
    NoChecksum = 1,
    /// Set or get the UDP checksum coverage.
    ChecksumCoverage = 20,
    /// Updates a client socket with the same properties of a listening socket.
    UpdateAcceptContext = 0x700B,
    /// Updates a client socket with the same properties of a listening socket.
    UpdateConnectContext = 0x7010
};
} // namespace Sockets
} // namespace Net
} // namespace System
