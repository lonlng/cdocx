/// @file net/http_known_header_names.h
#pragma once

#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Contains the string values of the known header names.
class ASPOSECPP_SHARED_CLASS HttpKnownHeaderNames
{
public:
    /// The 'Accept' header name.
    static ASPOSECPP_SHARED_API const String Accept;
    /// The 'Accept-Charset' header name.
    static ASPOSECPP_SHARED_API const String AcceptCharset;
    /// The 'Accept-Encoding' header name.
    static ASPOSECPP_SHARED_API const String AcceptEncoding;
    /// The 'Accept-Language' header name.
    static ASPOSECPP_SHARED_API const String AcceptLanguage;
    /// The 'Accept-Ranges' header name.
    static ASPOSECPP_SHARED_API const String AcceptRanges;
    /// The 'Age' header name.
    static ASPOSECPP_SHARED_API const String Age;
    /// The 'Allow' header name.
    static ASPOSECPP_SHARED_API const String Allow;
    /// The 'Authorization' header name.
    static ASPOSECPP_SHARED_API const String Authorization;
    /// The 'Cache-Control' header name.
    static ASPOSECPP_SHARED_API const String CacheControl;
    /// The 'Connection' header name.
    static ASPOSECPP_SHARED_API const String Connection;
    /// The 'Content-Disposition' header name.
    static ASPOSECPP_SHARED_API const String ContentDisposition;
    /// The 'Content-Encoding' header name.
    static ASPOSECPP_SHARED_API const String ContentEncoding;
    /// The 'Content-Language' header name.
    static ASPOSECPP_SHARED_API const String ContentLanguage;
    /// The 'Content-Length' header name.
    static ASPOSECPP_SHARED_API const String ContentLength;
    /// The 'Content-Location' header name.
    static ASPOSECPP_SHARED_API const String ContentLocation;
    /// The 'Content-MD5' header name.
    static ASPOSECPP_SHARED_API const String ContentMD5;
    /// The 'Content-Range' header name.
    static ASPOSECPP_SHARED_API const String ContentRange;
    /// The 'Content-Type' header name.
    static ASPOSECPP_SHARED_API const String ContentType;
    /// The 'Cookie' header name.
    static ASPOSECPP_SHARED_API const String Cookie;
    /// The 'Cookie2' header name.
    static ASPOSECPP_SHARED_API const String Cookie2;
    /// The 'Date' header name.
    static ASPOSECPP_SHARED_API const String Date;
    /// The 'ETag' header name.
    static ASPOSECPP_SHARED_API const String ETag;
    /// The 'Expect' header name.
    static ASPOSECPP_SHARED_API const String Expect;
    /// The 'Expires' header name.
    static ASPOSECPP_SHARED_API const String Expires;
    /// The 'From' header name.
    static ASPOSECPP_SHARED_API const String From;
    /// The 'Host' header name.
    static ASPOSECPP_SHARED_API const String Host;
    /// The 'If-Match' header name.
    static ASPOSECPP_SHARED_API const String IfMatch;
    /// The 'If-Modified-Since' header name.
    static ASPOSECPP_SHARED_API const String IfModifiedSince;
    /// The 'If-None-Match' header name.
    static ASPOSECPP_SHARED_API const String IfNoneMatch;
    /// The 'If-Range' header name.
    static ASPOSECPP_SHARED_API const String IfRange;
    /// The 'If-Unmodified-Since' header name.
    static ASPOSECPP_SHARED_API const String IfUnmodifiedSince;
    /// The 'Keep-Alive' header name.
    static ASPOSECPP_SHARED_API const String KeepAlive;
    /// The 'Last-Modified' header name.
    static ASPOSECPP_SHARED_API const String LastModified;
    /// The 'Location' header name.
    static ASPOSECPP_SHARED_API const String Location;
    /// The 'Max-Forwards' header name.
    static ASPOSECPP_SHARED_API const String MaxForwards;
    /// The 'Origin' header name.
    static ASPOSECPP_SHARED_API const String Origin;
    /// The 'P3P' header name.
    static ASPOSECPP_SHARED_API const String P3P;
    /// The 'Pragma' header name.
    static ASPOSECPP_SHARED_API const String Pragma;
    /// The 'Proxy-Authenticate' header name.
    static ASPOSECPP_SHARED_API const String ProxyAuthenticate;
    /// The 'Proxy-Authorization' header name.
    static ASPOSECPP_SHARED_API const String ProxyAuthorization;
    /// The 'Proxy-Connection' header name.
    static ASPOSECPP_SHARED_API const String ProxyConnection;
    /// The 'Range' header name.
    static ASPOSECPP_SHARED_API const String Range;
    /// The 'Referer' header name.
    static ASPOSECPP_SHARED_API const String Referer;
    /// The 'Retry-After' header name.
    static ASPOSECPP_SHARED_API const String RetryAfter;
    /// The 'Sec-WebSocket-Accept' header name.
    static ASPOSECPP_SHARED_API const String SecWebSocketAccept;
    /// The 'Sec-WebSocket-Extensions' header name.
    static ASPOSECPP_SHARED_API const String SecWebSocketExtensions;
    /// The 'Sec-WebSocket-Key' header name.
    static ASPOSECPP_SHARED_API const String SecWebSocketKey;
    /// The 'Sec-WebSocket-Protocol' header name.
    static ASPOSECPP_SHARED_API const String SecWebSocketProtocol;
    /// The 'Sec-WebSocket-Version' header name.
    static ASPOSECPP_SHARED_API const String SecWebSocketVersion;
    /// The 'Server' header name.
    static ASPOSECPP_SHARED_API const String Server;
    /// The 'Set-Cookie' header name.
    static ASPOSECPP_SHARED_API const String SetCookie;
    /// The 'Set-Cookie2' header name.
    static ASPOSECPP_SHARED_API const String SetCookie2;
    /// The 'TE' header name.
    static ASPOSECPP_SHARED_API const String TE;
    /// The 'Trailer' header name.
    static ASPOSECPP_SHARED_API const String Trailer;
    /// The 'Transfer-Encoding' header name.
    static ASPOSECPP_SHARED_API const String TransferEncoding;
    /// The 'Upgrade' header name.
    static ASPOSECPP_SHARED_API const String Upgrade;
    /// The 'User-Agent' header name.
    static ASPOSECPP_SHARED_API const String UserAgent;
    /// The 'Vary' header name.
    static ASPOSECPP_SHARED_API const String Vary;
    /// The 'Via' header name.
    static ASPOSECPP_SHARED_API const String Via;
    /// The 'WWW-Authenticate' header name.
    static ASPOSECPP_SHARED_API const String WWWAuthenticate;
    /// The 'Warning' header name.
    static ASPOSECPP_SHARED_API const String Warning;
    /// The 'X-AspNet-Version' header name.
    static ASPOSECPP_SHARED_API const String XAspNetVersion;
    /// The 'X-Powered-By' header name.
    static ASPOSECPP_SHARED_API const String XPoweredBy;

    /// The deleted default constructor.
    HttpKnownHeaderNames() = delete;
};

}} // namespace System::Net
