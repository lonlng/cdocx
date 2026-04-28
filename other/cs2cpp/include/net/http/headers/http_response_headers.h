/// @file net/http/headers/http_response_headers.h
#pragma once

#include <system/uri.h>

#include <net/http/headers/authentication_header_value.h>
#include <net/http/headers/entity_tag_header_value.h>
#include <net/http/headers/transfer_coding_header_value.h>
#include <net/http/headers/via_header_value.h>
#include <net/http/headers/http_headers.h>
#include <net/http/headers/http_header_value_collection.h>
#include <net/http/headers/product_info_header_value.h>
#include <net/http/headers/retry_condition_header_value.h>
#include <net/http/headers/cache_control_header_value.h>
#include <net/http/headers/warning_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

class HttpGeneralHeaders;

/// Represents the collection of the 'Response' headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpResponseHeaders final : public System::Net::Http::Headers::HttpHeaders
{
    /// This type.
    typedef HttpResponseHeaders ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::HttpHeaders BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a value of the 'Accept-Ranges' header.
    /// @returns A value of the 'Accept-Ranges' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<String>> get_AcceptRanges();
    /// Gets a value of the 'Age' header.
    /// @returns A value of the 'Age' header.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_Age();
    /// Sets a value of the 'Age' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Age(Nullable<TimeSpan> value);
    /// Gets a value of the 'ETag' header.
    /// @returns A value of the 'ETag' header.
    ASPOSECPP_SHARED_API System::SharedPtr<EntityTagHeaderValue> get_ETag();
    /// Sets a value of the 'ETag' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ETag(System::SharedPtr<EntityTagHeaderValue> value);
    /// Gets a value of the 'Location' header.
    /// @returns A value of the 'Location' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_Location();
    /// Sets a value of the 'Location' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Location(System::SharedPtr<Uri> value);
    /// Returns a value of the 'Proxy-Authenticate' header.
    /// @returns A value of the 'Proxy-Authenticate' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<AuthenticationHeaderValue>>>
        get_ProxyAuthenticate();
    /// Gets a value of the 'Retry-After' header.
    /// @returns A value of the 'Retry-After' header.
    ASPOSECPP_SHARED_API System::SharedPtr<RetryConditionHeaderValue> get_RetryAfter();
    /// Sets a value of the 'Retry-After' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_RetryAfter(System::SharedPtr<RetryConditionHeaderValue> value);
    /// Returns a value of the 'Server' header.
    /// @returns A value of the 'Server' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ProductInfoHeaderValue>>>
        get_Server();
    /// Returns a value of the 'Vary' header.
    /// @returns A value of the 'Vary' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<String>> get_Vary();
    /// Returns a value of the 'WWW-Authenticate' header.
    /// @returns A value of the 'WWW-Authenticate' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<AuthenticationHeaderValue>>>
        get_WwwAuthenticate();
    /// Gets a value of the 'Cache-Control' header.
    /// @returns A value of the 'Cache-Control' header.
    ASPOSECPP_SHARED_API System::SharedPtr<CacheControlHeaderValue> get_CacheControl();
    /// Sets a value of the 'Cache-Control' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_CacheControl(System::SharedPtr<CacheControlHeaderValue> value);
    /// Returns a value of the 'Connection' header.
    /// @returns A value of the 'Connection' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<String>> get_Connection();
    /// Gets a value that indicates if the 'Connection' header value contains 'Close'.
    /// @returns True when the the 'Connection' header value contains 'Close', otherwise false.
    ASPOSECPP_SHARED_API Nullable<bool> get_ConnectionClose();
    /// Sets a value that indicates if the 'Connection' header value contains 'Close'.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ConnectionClose(Nullable<bool> value);
    /// Gets a value of the 'Date' header.
    /// @returns A value of the 'Date' header.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_Date();
    /// Sets a value of the 'Date' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Date(Nullable<DateTimeOffset> value);
    /// Returns a value of the 'Pragma' header.
    /// @returns A value of the 'Pragma' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<NameValueHeaderValue>>>
        get_Pragma();
    /// Returns a value of the 'Trailer' header.
    /// @returns A value of the 'Trailer' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<String>> get_Trailer();
    /// Returns a value of the 'Transfer-Encoding' header.
    /// @returns A value of the 'Transfer-Encoding' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<TransferCodingHeaderValue>>>
        get_TransferEncoding();
    /// Gets a value that indicates if the 'Transfer-Encoding' header value contains 'Chunked'.
    /// @returns True when the the 'Transfer-Encoding' header value contains 'Chunked', otherwise false.
    ASPOSECPP_SHARED_API Nullable<bool> get_TransferEncodingChunked();
    /// Sets a value that indicates if the 'Transfer-Encoding' header value contains 'Chunked'.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_TransferEncodingChunked(Nullable<bool> value);
    /// Returns a value of the 'Upgrade' header.
    /// @returns A value of the 'Upgrade' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ProductHeaderValue>>>
        get_Upgrade();
    /// Returns a value of the 'Via' header.
    /// @returns A value of the 'Via' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ViaHeaderValue>>> get_Via();
    /// Returns a value of the 'Warning' header.
    /// @returns A value of the 'Warning' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<WarningHeaderValue>>>
        get_Warning();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpResponseHeaders();

    /// Adds the known headers to the specified collection.
    /// @param headerSet A collection to which the known headers will be added.
    ASPOSECPP_SHARED_API static void
        AddKnownHeaders(System::SharedPtr<Collections::Generic::HashSet<String>> headerSet);
    /// @copydoc System::Net::Http::Headers::HttpHeaders::AddHeaders
    ASPOSECPP_SHARED_API virtual void AddHeaders(System::SharedPtr<HttpHeaders> sourceHeaders) override;

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    /// The collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        s_parserStore;
    /// The collection of the invalid headers.
    static System::SharedPtr<Collections::Generic::HashSet<String>> s_invalidHeaders;
    /// The collection of the general headers.
    System::SharedPtr<HttpGeneralHeaders> _generalHeaders;
    /// A value of the 'Accept-Ranges' header.
    System::SharedPtr<HttpHeaderValueCollection<String>> _acceptRanges;
    /// A value of the 'WWW-Authenticate' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<AuthenticationHeaderValue>>> _wwwAuthenticate;
    /// A value of the 'Proxy-Authenticate' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<AuthenticationHeaderValue>>> _proxyAuthenticate;
    /// A value of the 'Server' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ProductInfoHeaderValue>>> _server;
    /// A value of the 'Vary' header.
    System::SharedPtr<HttpHeaderValueCollection<String>> _vary;

    /// Creates the collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        CreateParserStore();
    /// Returns the collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        GetParserStore();
    /// Creates the collection of the invalid headers.
    static System::SharedPtr<Collections::Generic::HashSet<String>> CreateInvalidHeaders();

    /// Initializes the static fields.
    static void InitStatic();
};

}}}} // namespace System::Net::Http::Headers
