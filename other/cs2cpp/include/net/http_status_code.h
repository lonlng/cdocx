/// @file net/http_status_code.h
#pragma once
#include <system/enum.h>

namespace System { namespace Net {

// HTTP status codes as per RFC 2616.
enum class HttpStatusCode
{
    /// The 'Continue' status code that equals to HTTP status 100.
    Continue = 100,
    /// The 'Switching Protocol' status code that equals to HTTP status 101.
    SwitchingProtocols = 101,
    /// The 'OK' status code that equals to HTTP status 200.
    OK = 200,
    /// The 'Created' status code that equals to HTTP status 201.
    Created = 201,
    /// The 'Accepted' status code that equals to HTTP status 202.
    Accepted = 202,
    /// The 'Non-Authoritative Information' status code that equals to HTTP status 203.
    NonAuthoritativeInformation = 203,
    /// The 'No Content' status code that equals to HTTP status 204.
    NoContent = 204,
    /// The 'Reset Content' status code that equals to HTTP status 205.
    ResetContent = 205,
    /// The 'Partial Content' status code that equals to HTTP status 206.
    PartialContent = 206,
    /// The 'Multiple Choice' status code that equals to HTTP status 300.
    MultipleChoices = 300,
    /// The 'Ambiguous' status code that equals to HTTP status 300.
    Ambiguous = 300,
    /// The 'Moved Permanently' status code that equals to HTTP status 301.
    MovedPermanently = 301,
    /// The 'Moved' status code that equals to HTTP status 301.
    Moved = 301,
    /// The 'Found' status code that equals to HTTP status 302.
    Found = 302,
    /// The 'Redirect' status code that equals to HTTP status 302.
    Redirect = 302,
    /// The 'See Other' status code that equals to HTTP status 303.
    SeeOther = 303,
    /// The 'Redirect' status code that equals to HTTP status 303.
    RedirectMethod = 303,
    /// The 'Not Modified' status code that equals to HTTP status 304.
    NotModified = 304,
    /// The 'Use Proxy' status code that equals to HTTP status 305.
    UseProxy = 305,
    /// The 'Switch Proxy' status code that equals to HTTP status 306.
    Unused = 306,
    /// The 'Temporary Redirect' status code that equals to HTTP status 307.
    TemporaryRedirect = 307,
    /// The 'Redirect Keep Verb' status code that equals to HTTP status 307.
    RedirectKeepVerb = 307,
    /// The 'Permanent Redirect' status code that equals to HTTP status 308.
    PermanentRedirect = 308,
    /// The 'Bad Request' status code that equals to HTTP status 400.
    BadRequest = 400,
    /// The 'Unauthorized' status code that equals to HTTP status 401.
    Unauthorized = 401,
    /// The 'Payment Required' status code that equals to HTTP status 402.
    PaymentRequired = 402,
    /// The 'Forbidden' status code that equals to HTTP status 403.
    Forbidden = 403,
    /// The 'Not Found' status code that equals to HTTP status 404.
    NotFound = 404,
    /// The 'Method Not Allowed' status code that equals to HTTP status 405.
    MethodNotAllowed = 405,
    /// The 'Not Acceptable' status code that equals to HTTP status 406.
    NotAcceptable = 406,
    /// The 'Proxy Authentication Required' status code that equals to HTTP status 407.
    ProxyAuthenticationRequired = 407,
    /// The 'Request Timeout' status code that equals to HTTP status 408.
    RequestTimeout = 408,
    /// The 'Conflict' status code that equals to HTTP status 409.
    Conflict = 409,
    /// The 'Gone' status code that equals to HTTP status 410.
    Gone = 410,
    /// The 'Length Required' status code that equals to HTTP status 411.
    LengthRequired = 411,
    /// The 'Precondition Failed' status code that equals to HTTP status 412.
    PreconditionFailed = 412,
    /// The 'Request Entity Too Large' status code that equals to HTTP status 413.
    RequestEntityTooLarge = 413,
    /// The 'Request-URI Too Long' status code that equals to HTTP status 414.
    RequestUriTooLong = 414,
    /// The 'Unsupported Media Type' status code that equals to HTTP status 415.
    UnsupportedMediaType = 415,
    /// The 'Requested Range Not Satisfiable' status code that equals to HTTP status 416.
    RequestedRangeNotSatisfiable = 416,
    /// The 'Expectation Failed' status code that equals to HTTP status 417.
    ExpectationFailed = 417,
    /// The 'Upgrade Required' status code that equals to HTTP status 426.
    UpgradeRequired = 426,
    /// The 'Internal Server Error' status code that equals to HTTP status 500.
    InternalServerError = 500,
    /// The 'Not Implemented' status code that equals to HTTP status 501.
    NotImplemented = 501,
    /// The 'Bad Gateway' status code that equals to HTTP status 502.
    BadGateway = 502,
    /// The 'Service Unavailable' status code that equals to HTTP status 503.
    ServiceUnavailable = 503,
    /// The 'Gateway Timeout' status code that equals to HTTP status 504.
    GatewayTimeout = 504,
    /// The 'HTTP Version Not Supported' status code that equals to HTTP status 505.
    HttpVersionNotSupported = 505
};

}} // namespace System::Net

/// Specialization for System::Net::HttpStatusCode; contains mapping of enum constants to their string representations.
template <>
struct EnumMetaInfo<System::Net::HttpStatusCode>
{
    /// Returns an array of pairs that associate System::Net::HttpStatusCode enum's constants with their string
    /// representations.
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Net::HttpStatusCode, const char_t*>, 47>& values();
};
