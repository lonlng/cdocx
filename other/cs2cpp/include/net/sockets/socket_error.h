/// @file net/sockets/socket_error.h
#pragma once

#include <system/exceptions.h>
#include <cstdint>

namespace System {
namespace Net {
namespace Sockets {

/// Enumerates the socket error types.
enum class SocketError
{
    /// A socket operation completed successfully.
    Success = 0,
    /// An unspecified socket error occurred.
    SocketError = -1,
    /// A blocking socket call is cancelled.
    Interrupted = 10004,
    /// Access to a socket is denied.
    AccessDenied = 10013,
    /// An invalid pointer address is detected.
    Fault = 10014,
    /// An invalid argument is provided.
    InvalidArgument = 10022,
    /// There are too many open sockets in the underlying socket provider.
    TooManyOpenSockets = 10024,
    /// An operation cannot be immediately completed on a non-blocking socket.
    WouldBlock = 10035,
    /// A blocking operation is in progress.
    InProgress = 10036,
    /// A non-blocking socket already has a running operation.
    AlreadyInProgress = 10037,
    /// An attempt to call a socket operation on non-socket.
    NotSocket = 10038,
    /// A required address is omitted from a socket operation.
    DestinationAddressRequired = 10039,
    /// A datagram is too long.
    MessageSize = 10040,
    /// A protocol type is not supported by this socket.
    ProtocolType = 10041,
    /// An unknown, invalid, or unsupported option or level is used.
    ProtocolOption = 10042,
    /// A protocol is not implemented or not configured.
    ProtocolNotSupported = 10043,
    /// An address family doesn't support the specified socket.
    SocketNotSupported = 10044,
    /// A protocol family doesn't support an address family.
    OperationNotSupported = 10045,
    /// A protocol family is not implemented or not configured.
    ProtocolFamilyNotSupported = 10046,
    /// The specified address family is not supported.
    AddressFamilyNotSupported = 10047,
    /// An address can be used only once.
    AddressAlreadyInUse = 10048,
    /// The selected IP address is not valid in this context.
    AddressNotAvailable = 10049,
    /// The network is not available.
    NetworkDown = 10050,
    /// No route to the remote host exists.
    NetworkUnreachable = 10051,
    /// An application tried to set 'Keep-Alive' on a connection that has already timed out.
    NetworkReset = 10052,
    /// A connection is aborted.
    ConnectionAborted = 10053,
    /// A connection is reset by a remote peer.
    ConnectionReset = 10054,
    /// No free buffer space is available for a socket operation.
    NoBufferSpaceAvailable = 10055,
    /// A socket is already connected.
    IsConnected = 10056,
    /// An application tried to send or receive data, and a socket is not connected.
    NotConnected = 10057,
    /// A request to send or receive data is forbidden because the socket has already been closed.
    Shutdown = 10058,
    /// A connection attempt timed out, or a connected host has failed to respond.
    TimedOut = 10060,
    /// A remote host is actively refusing a connection.
    ConnectionRefused = 10061,
    /// An operation failed because a remote host is down.
    HostDown = 10064,
    /// No network route to the specified host exists.
    HostUnreachable = 10065,
    /// Too many processes are using the underlying socket provider.
    ProcessLimit = 10067,
    /// A network subsystem is unavailable.
    SystemNotReady = 10091,
    /// A version of the underlying socket provider is out of range.
    VersionNotSupported = 10092,
    /// The underlying socket provider is not initialized.
    NotInitialized = 10093,
    /// A graceful shutdown is in progress.
    Disconnecting = 10101,
    /// The specified class is not found.
    TypeNotFound = 10109,
    /// The specified host is unknown.
    HostNotFound = 11001,
    /// A name of a host cannot be resolved.
    TryAgain = 11002,
    /// An error is unrecoverable or a requested database cannot be located.
    NoRecovery = 11003,
    /// A requested name or IP address is not found on the name server.
    NoData = 11004,
};
} // namespace Sockets
} // namespace Net
} // namespace System
