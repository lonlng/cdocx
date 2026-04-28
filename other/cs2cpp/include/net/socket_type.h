/// @file net/socket_type.h
#pragma once

#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the socket types.
enum class SocketType
{
    /// The type that supports reliable, two-way, connection-based byte streams without duplication of data and without
    /// preservation of boundaries.
    Stream = 1,
    /// The type that supports datagrams, which are connectionless, unreliable messages of a fixed maximum length.
    Dgram = 2,
    /// The type that supports access to the underlying transport protocol.
    Raw = 3,
    /// The type that supports connectionless, message-oriented, reliably delivered messages, and preserves message
    /// boundaries in data.
    Rdm = 4,
    /// The type that provides connection-oriented and reliable two-way transfer of ordered byte streams across a
    /// network.
    Seqpacket = 5,
    /// An unknown type.
    Unknown = static_cast<int32_t>(-1)
};
} // namespace Sockets
} // namespace Net
} // namespace System
