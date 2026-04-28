/// @file net/sockets/socket_option_level.h
#pragma once

#include <net/sockets/protocol_type.h>

namespace System {
namespace Net {
namespace Sockets {

/// Defines socket option levels for the 'Socket' class.
enum class SocketOptionLevel
{
    /// The specified socket options apply to all sockets.
    Socket = 0xffff,
    /// The specified socket options apply to the IP sockets.
    IP = static_cast<int32_t>(System::Net::Sockets::ProtocolType::IP),
    /// The specified socket options apply to the IPv6 sockets.
    IPv6 = static_cast<int32_t>(System::Net::Sockets::ProtocolType::IPv6),
    /// The specified socket options apply to the TCP sockets.
    Tcp = static_cast<int32_t>(System::Net::Sockets::ProtocolType::Tcp),
    /// The specified socket options apply to the UDP sockets.
    Udp = static_cast<int32_t>(System::Net::Sockets::ProtocolType::Udp)
};
} // namespace Sockets
} // namespace Net
} // namespace System
