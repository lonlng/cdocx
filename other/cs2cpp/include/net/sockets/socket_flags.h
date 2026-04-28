/// @file net/sockets/socket_flags.h
#pragma once

#include <system/enum_helpers.h>

namespace System {
namespace Net {
namespace Sockets {

/// Provides constant values for the socket messages.
enum class SocketFlags
{
    /// There are no flags used for this call.
    None = 0x0000,
    /// The out-of-band data is being processed.
    OutOfBand = 0x0001,
    /// Peek at an incoming message.
    Peek = 0x0002,
    /// Send a message without using routing tables.
    DontRoute = 0x0004,
    /// A message is too large to fit into the specified buffer. It has been truncated.
    Truncated = 0x0100,
    /// The control data is greater than 64 KB and doesn't fit into the internal buffer. It has been truncated.
    ControlDataTruncated = 0x0200,
    /// A broadcast packet.
    Broadcast = 0x0400,
    /// A multicast packet.
    Multicast = 0x0800,
    /// A message sent or received partially.
    Partial = 0x8000
};

/// @cond
/// Declaration of template arithmetic operators for values of the SocketFlags enum type.
DECLARE_ENUM_OPERATORS(System::Net::Sockets::SocketFlags);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
} // namespace Sockets
} // namespace Net
} // namespace System

/// Inserts using declarations for arithmetic operators declared in namespace System::Net::Sockets.
DECLARE_USING_ENUM_OPERATORS(System::Net::Sockets);
