/// @file net/sockets/protocol_type.h
#pragma once

#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the protocol types.
enum class ProtocolType
{
    /// The Internet Protocol.
    IP = 0,
    /// The IPv6 Hop by Hop Options header.
    IPv6HopByHopOptions = 0,
    /// The Internet Control Message Protocol.
    Icmp = 1,
    /// The Internet Group Management Protocol.
    Igmp = 2,
    /// The Gateway To Gateway Protocol.
    Ggp = 3,
    /// The Internet Protocol version 4.
    IPv4 = 4,
    /// The Transmission Control Protocol.
    Tcp = 6,
    /// The PARC Universal Packet Protocol.
    Pup = 12,
    /// The User Datagram Protocol.
    Udp = 17,
    /// The Internet Datagram Protocol.
    Idp = 22,
    /// The Internet Protocol version 6.
    IPv6 = 41,
    /// The IPv6 Routing header.
    IPv6RoutingHeader = 43,
    /// The IPv6 Fragment header.
    IPv6FragmentHeader = 44,
    /// The IPv6 Encapsulating Security Payload header.
    IPSecEncapsulatingSecurityPayload = 50,
    /// The IPv6 Authentication header.
    IPSecAuthenticationHeader = 51,
    /// The Internet Control Message Protocol for IPv6.
    IcmpV6 = 58,
    /// The IPv6 No next header.
    IPv6NoNextHeader = 59,
    /// The IPv6 Destination Options header.
    IPv6DestinationOptions = 60,
    /// The Net Disk protocol.
    ND = 77,
    /// The Raw IP packet protocol.
    Raw = 255,
    /// An unspecified protocol.
    Unspecified = 0,
    /// The Internet Packet Exchange protocol.
    Ipx = 1000,
    /// The Sequenced Packet Exchange protocol.
    Spx = 1256,
    /// The Sequenced Packet Exchange version 2 protocol.
    SpxII = 1257,
    /// An unknown protocol.
    Unknown = static_cast<int32_t>(-1)
};
} // namespace Sockets
} // namespace Net
} // namespace System
