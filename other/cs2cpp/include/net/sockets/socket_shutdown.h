/// @file net/sockets/socket_shutdown.h
#pragma once

namespace System {
namespace Net {
namespace Sockets {

/// Defines constants used by the Socket.Shutdown method.
enum class SocketShutdown
{
    /// Disables the socket for receiving.
    Receive = 0x00,
    /// Disables the socket for sending.
    Send = 0x01,
    /// Disables the socket for both sending and receiving.
    Both = 0x02
};
} // namespace Sockets
} // namespace Net
} // namespace System
