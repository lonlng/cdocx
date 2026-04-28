/// @file net/http_response_header.h
#pragma once

#include <system/array.h>
#include <system/object.h>
#include <system/string.h>

namespace System { namespace Net {

/// Enumerates the http response headers.
enum class HttpResponseHeader
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
    /// The 'Accept-Ranges' header.
    AcceptRanges = 20,
    /// The 'Age' header.
    Age = 21,
    /// The 'ETag' header.
    ETag = 22,
    /// The 'Location' header.
    Location = 23,
    /// The 'Proxy-Authenticate' header.
    ProxyAuthenticate = 24,
    /// The 'Retry-After' header.
    RetryAfter = 25,
    /// The 'Server' header.
    Server = 26,
    /// The 'Set-Cookie' header.
    SetCookie = 27,
    /// The 'Vary' header.
    Vary = 28,
    /// The 'WWW-Authenticate' header.
    WwwAuthenticate = 29
};

/// Contains utility methods to work with the HttpResponseHeader enumeration values.
class HttpResponseHeaderExtensions : public System::Object
{
    /// This type.
    typedef HttpResponseHeaderExtensions ThisType;
    /// Parent type.
    typedef System::Object BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the name of the specified header.
    /// @param header The header for which the name must be returned.
    /// @returns The name of the specified header.
    static String GetName(HttpResponseHeader header);

    /// The deleted default constructor.
    HttpResponseHeaderExtensions() = delete;

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
