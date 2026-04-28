/// @file net/sockets/select_mode.h
#pragma once

namespace System {
namespace Net {
namespace Sockets {

/// Specifies the mode for polling the status of the socket.
enum class SelectMode
{
    /// The 'read' status mode.
    SelectRead = 0,
    /// The 'write' status mode.
    SelectWrite = 1,
    /// The 'error' status mode.
    SelectError = 2
};
} // namespace Sockets
} // namespace Net
} // namespace System
