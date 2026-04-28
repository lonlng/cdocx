/// @file net/web_exception_status.h
#pragma once

namespace System { namespace Net {

/// Enumerates the status codes of the WebException class.
enum class WebExceptionStatus
{
    /// No errors occurred.
    Success = 0,
    /// The name resolver service could not resolve the host name.
    NameResolutionFailure = 1,
    /// The remote service point could not be contacted at the transport level.
    ConnectFailure = 2,
    /// A complete response is not received from the remote server.
    ReceiveFailure = 3,
    /// A complete request could not be sent to the remote server.
    SendFailure = 4,
    /// The request was a pipelined request and the connection was closed before the response was received.
    PipelineFailure = 5,
    /// The request was canceled or an unclassifiable error occurred.
    RequestCanceled = 6,
    /// The response received from the server was complete but indicated a protocol-level error.
    ProtocolError = 7,
    /// The connection was prematurely closed.
    ConnectionClosed = 8,
    /// A server certificate could not be validated.
    TrustFailure = 9,
    /// An error occurred while establishing a connection using SSL.
    SecureChannelFailure = 10,
    /// The server response was not a valid HTTP response.
    ServerProtocolViolation = 11,
    /// The connection for a request that specifies the 'Keep-Alive' header was closed unexpectedly.
    KeepAliveFailure = 12,
    /// An internal asynchronous request is pending.
    Pending = 13,
    /// No response was received during the time-out period for a request.
    Timeout = 14,
    /// The name resolver service could not resolve the proxy host name.
    ProxyNameResolutionFailure = 15,
    /// An exception of unknown type has occurred.
    UnknownError = 16,
    /// A message that exceeded the specified limit was received.
    MessageLengthLimitExceeded = 17,
    /// The specified cache entry was not found.
    CacheEntryNotFound = 18,
    /// The request was not permitted by the cache policy.
    RequestProhibitedByCachePolicy = 19,
    /// This request was not permitted by the proxy.
    RequestProhibitedByProxy = 20
};
}} // namespace System::Net
