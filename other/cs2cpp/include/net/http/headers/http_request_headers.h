/// @file net/http/headers/http_request_headers.h
#pragma once

#include <system/uri.h>

#include <net/http/headers/authentication_header_value.h>
#include <net/http/headers/entity_tag_header_value.h>
#include <net/http/headers/http_headers.h>
#include <net/http/headers/media_type_with_quality_header_value.h>
#include <net/http/headers/name_value_with_parameters_header_value.h>
#include <net/http/headers/product_info_header_value.h>
#include <net/http/headers/range_condition_header_value.h>
#include <net/http/headers/range_header_value.h>
#include <net/http/headers/string_with_quality_header_value.h>
#include <net/http/headers/transfer_coding_with_quality_header_value.h>
#include <net/http/headers/http_header_value_collection.h>
#include <net/http/headers/cache_control_header_value.h>
#include <net/http/headers/via_header_value.h>
#include <net/http/headers/warning_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

class HttpGeneralHeaders;

/// Represents the collection of the 'Request' headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpRequestHeaders final : public System::Net::Http::Headers::HttpHeaders
{
    /// This type.
    typedef HttpRequestHeaders ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::HttpHeaders BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a value of the 'Accept' header.
    /// @returns A value of the 'Accept' header.
    ASPOSECPP_SHARED_API
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<MediaTypeWithQualityHeaderValue>>> get_Accept();
    /// Returns a value of the 'Accept-Charset' header.
    /// @returns A value of the 'Accept-Charset' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>>
        get_AcceptCharset();
    /// Returns a value of the 'Accept-Encoding' header.
    /// @returns A value of the 'Accept-Encoding' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>>
        get_AcceptEncoding();
    /// Returns a value of the 'Accept-Language' header.
    /// @returns A value of the 'Accept-Language' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>>
        get_AcceptLanguage();
    /// Gets a value of the 'Authorization' header.
    /// @returns A value of the 'Authorization' header.
    ASPOSECPP_SHARED_API System::SharedPtr<AuthenticationHeaderValue> get_Authorization();
    /// Sets a value of the 'Authorization' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Authorization(System::SharedPtr<AuthenticationHeaderValue> value);
    /// Returns value of the 'Expect' header.
    /// @returns A value of the 'Expect' header.
    ASPOSECPP_SHARED_API
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<NameValueWithParametersHeaderValue>>> get_Expect();
    /// Gets a value that indicates if the 'Expect' header value contains 'Continue'.
    /// @returns True when the 'Expect' header value contains 'Continue', otherwise false.
    ASPOSECPP_SHARED_API Nullable<bool> get_ExpectContinue();
    /// Sets a value that indicates if the 'Expect' header value contains 'Continue'.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ExpectContinue(Nullable<bool> value);
    /// Gets a value of the 'From' header.
    /// @returns A value of the 'From' header.
    ASPOSECPP_SHARED_API String get_From();
    /// Sets a value of the 'From' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_From(String value);
    /// Gets a value of the 'Host' header.
    /// @returns A value of the 'Host' header.
    ASPOSECPP_SHARED_API String get_Host();
    /// Sets a value of the 'Host' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Host(String value);
    /// Returns a value of the 'If-Match' header.
    /// @returns A value of the 'If-Match' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<EntityTagHeaderValue>>>
        get_IfMatch();
    /// Gets a value of the 'If-Modified-Since' header.
    /// @returns A value of the 'If-Modified-Since' header.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_IfModifiedSince();
    /// Sets a value of the 'If-Modified-Since' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_IfModifiedSince(Nullable<DateTimeOffset> value);
    /// Returns a value of the 'If-None-Match' header.
    /// @returns A value of the 'If-None-Match' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<EntityTagHeaderValue>>>
        get_IfNoneMatch();
    /// Gets a value of the 'If-Range' header.
    /// @returns A value of the 'If-Range' header.
    ASPOSECPP_SHARED_API System::SharedPtr<RangeConditionHeaderValue> get_IfRange();
    /// Sets a value of the 'If-Range' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_IfRange(System::SharedPtr<RangeConditionHeaderValue> value);
    /// Gets a value of the 'If-Unmodified-Since' header.
    /// @returns A value of the 'If-Unmodified-Since' header.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_IfUnmodifiedSince();
    /// Sets a value of the 'If-Unmodified-Since' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_IfUnmodifiedSince(Nullable<DateTimeOffset> value);
    /// Gets a value of the 'Max-Forwards' header.
    /// @returns A value of the 'Max-Forwards' header.
    ASPOSECPP_SHARED_API Nullable<int32_t> get_MaxForwards();
    /// Sets a value of the 'Max-Forwards' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MaxForwards(Nullable<int32_t> value);
    /// Gets a value of the 'Proxy-Authorization' header.
    /// @returns A value of the 'Proxy-Authorization' header.
    ASPOSECPP_SHARED_API System::SharedPtr<AuthenticationHeaderValue> get_ProxyAuthorization();
    /// Sets a value of the 'Proxy-Authorization' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ProxyAuthorization(System::SharedPtr<AuthenticationHeaderValue> value);
    /// Gets a value of the 'Range' header.
    /// @returns A value of the 'Range' header.
    ASPOSECPP_SHARED_API System::SharedPtr<RangeHeaderValue> get_Range();
    /// Sets a value of the 'Range' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Range(System::SharedPtr<RangeHeaderValue> value);
    /// Gets a value of the 'Referer' header.
    /// @returns A value of the 'Referer' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_Referrer();
    /// Sets a value of the 'Referer' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Referrer(System::SharedPtr<Uri> value);
    /// Returns a value of the 'TE' header.
    /// @returns A value of the 'TE' header.
    ASPOSECPP_SHARED_API
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<TransferCodingWithQualityHeaderValue>>> get_TE();
    /// Returns a value of the 'User-Agent' header.
    /// @returns A value of the 'User-Agent' header.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ProductInfoHeaderValue>>>
        get_UserAgent();
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
    /// @returns True when the 'Connection' header value contains 'Close', otherwise false.
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
    /// @returns True when the 'Transfer-Encoding' header value contains 'Chunked', otherwise false.
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
    ASPOSECPP_SHARED_API HttpRequestHeaders();

    /// Adds the known headers to the specified collection.
    /// @param headerSet A collection to which the known headers will be added.
    ASPOSECPP_SHARED_API static void
        AddKnownHeaders(System::SharedPtr<Collections::Generic::HashSet<String>> headerSet);
    /// @copydoc System::Net::Http::Headers::HttpHeaders::AddHeaders
    ASPOSECPP_SHARED_API void AddHeaders(System::SharedPtr<HttpHeaders> sourceHeaders) override;

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
    /// A value of the 'Accept' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<MediaTypeWithQualityHeaderValue>>> _accept;
    /// A value of the 'Expect' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<NameValueWithParametersHeaderValue>>> _expect;
    /// A value that indicates if the 'Expect' header value is set.
    bool _expectContinueSet;
    /// A value of the 'If-Match' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<EntityTagHeaderValue>>> _ifMatch;
    /// A value of the 'If-None-Match' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<EntityTagHeaderValue>>> _ifNoneMatch;
    /// A value of the 'TE' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<TransferCodingWithQualityHeaderValue>>> _te;
    /// A value of the 'User-Agent' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<ProductInfoHeaderValue>>> _userAgent;
    /// A value of the 'Accept-Charset' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>> _acceptCharset;
    /// A value of the 'Accept-Encoding' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>> _acceptEncoding;
    /// A value of the 'Accept-Language' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<StringWithQualityHeaderValue>>> _acceptLanguage;

    /// Returns a value of the 'Expect' header.
    System::SharedPtr<HttpHeaderValueCollection<System::SharedPtr<NameValueWithParametersHeaderValue>>>
        get_ExpectCore();

    /// Creates the collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        CreateParserStore();
    /// Returns the collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        GetParserStore();
    /// Creates the collection of the invalid headers.
    static System::SharedPtr<Collections::Generic::HashSet<String>> CreateInvalidHeaders();

    /// Initializes the static fields.
    void InitStatic();
};

}}}} // namespace System::Net::Http::Headers
