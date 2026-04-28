/// @file net/http_request_header.h
#pragma once

#include <system/array.h>
#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Enumerates the request headers.
enum class HttpRequestHeader
{
    /// The 'Cache-Control' header.
    CacheControl = 0,
    /// The 'Connection' header.
    Connection = 1,
    /// The 'Date' header.
    Date = 2,
    /// The 'Keep-Alive' header.
    KeepAlive = 3,
    /// The 'Pragma' header.
    Pragma = 4,
    /// The 'Trailer' header.
    Trailer = 5,
    /// The 'Transfer-Encoding' header.
    TransferEncoding = 6,
    /// The 'Upgrade' header.
    Upgrade = 7,
    /// The 'Via' header.
    Via = 8,
    /// The 'Warning' header.
    Warning = 9,
    /// The 'Allow' header.
    Allow = 10,
    /// The 'Content-Length' header.
    ContentLength = 11,
    /// The 'Content-Type' header.
    ContentType = 12,
    /// The 'Content-Encoding' header.
    ContentEncoding = 13,
    /// The 'Content-Language' header.
    ContentLanguage = 14,
    /// The 'Content-Location' header.
    ContentLocation = 15,
    /// The 'Content-MD5' header.
    ContentMd5 = 16,
    /// The 'Content-Range' header.
    ContentRange = 17,
    /// The 'Expires' header.
    Expires = 18,
    /// The 'Last-Modified' header.
    LastModified = 19,
    /// The 'Accept' header.
    Accept = 20,
    /// The 'Accept-Charset' header.
    AcceptCharset = 21,
    /// The 'Accept-Encoding' header.
    AcceptEncoding = 22,
    /// The 'Accept-Language' header.
    AcceptLanguage = 23,
    /// The 'Authorization' header.
    Authorization = 24,
    /// The 'Cookie' header.
    Cookie = 25,
    /// The 'Expect' header.
    Expect = 26,
    /// The 'From' header.
    From = 27,
    /// The 'Host' header.
    Host = 28,
    /// The 'If-Match' header.
    IfMatch = 29,
    /// The 'If-Modified-Since' header.
    IfModifiedSince = 30,
    /// The 'If-None-Match' header.
    IfNoneMatch = 31,
    /// The 'If-Range' header.
    IfRange = 32,
    /// The 'If-Unmodified-Since' header.
    IfUnmodifiedSince = 33,
    /// The 'Max-Forwards' header.
    MaxForwards = 34,
    /// The 'Proxy-Authorization' header.
    ProxyAuthorization = 35,
    /// The 'Referer' header.
    Referer = 36,
    /// The 'Range' header.
    Range = 37,
    /// The 'TE' header.
    Te = 38,
    /// The 'Translate' header.
    Translate = 39,
    /// The 'User-Agent' header.
    UserAgent = 40
};

/// Contains utility methods to work with the HttpRequestHeader enumeration values.
class HttpRequestHeaderExtensions
{
public:
    /// Returns the string representation of the specified header.
    /// @param header A header to which string representation must be returned.
    /// @returns The string representation of the specified header.
    ASPOSECPP_SHARED_API static String GetName(HttpRequestHeader header);

    /// The deleted default constructor.
    HttpRequestHeaderExtensions() = delete;

private:
    /// The internal array that stores string representations of the HTTP headers.
    static System::ArrayPtr<String> s_names;

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}} // namespace System::Net
