/// @file net/sockets/transport_type.h
#pragma once

namespace System {
namespace Net {

/// Defines the transport type allowed for the socket.
enum class TransportType
{
    /// The UDP transport type.
    Udp = 1,
    /// The transport type is connectionless.
    Connectionless = Udp,
    /// The TCP transport type.
    Tcp = 2,
    /// The transport is connection oriented.
    ConnectionOriented = Tcp,
    /// All transport types.
    All = 3
};
} // namespace Net
} // namespace System
