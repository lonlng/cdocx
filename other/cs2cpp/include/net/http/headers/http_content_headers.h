/// @file net/http/headers/http_content_headers.h
#pragma once

#include <cstdint>
#include <system/array.h>
#include <system/collections/dictionary.h>
#include <system/collections/hashset.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>

#include <net/http/headers/content_disposition_header_value.h>
#include <net/http/headers/content_range_header_value.h>
//#include <net/http/headers/http_header_parser.h>
#include <net/http/headers/http_header_value_collection.h>
#include <net/http/headers/http_headers.h>
#include <net/http/headers/media_type_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents the collection of the 'Content' headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpContentHeaders final : public System::Net::Http::Headers::HttpHeaders
{
    /// This type.
    typedef HttpContentHeaders ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::HttpHeaders BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a value of the 'Allow' header.
    /// @returns A value of the 'Allow' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<String>> get_Allow();
    /// Gets a value of the 'Content-Disposition' header.
    /// @returns A value of the 'Content-Disposition' header.
    ASPOSECPP_SHARED_API System::SharedPtr<ContentDispositionHeaderValue> get_ContentDisposition();
    /// Sets a value of the 'Content-Disposition' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentDisposition(System::SharedPtr<ContentDispositionHeaderValue> value);
    /// Gets a value of the 'Content-Encoding' header.
    /// @returns A value of the 'Content-Encoding' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<String>> get_ContentEncoding();
    /// Gets a value of the 'Content-Language' header.
    /// @returns A value of the 'Content-Language' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<String>> get_ContentLanguage();
    /// Gets a value of the 'Content-Length' header.
    /// @returns A value of the 'Content-Length' header.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_ContentLength();
    /// Sets a value of the 'Content-Length' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentLength(Nullable<int64_t> value);
    /// Gets a value of the 'Content-Location' header.
    /// @returns A value of the 'Content-Location' header.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_ContentLocation();
    /// Sets a value of the 'Content-Location' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentLocation(System::SharedPtr<Uri> value);
    /// Gets a value of the 'Content-MD5' header.
    /// @returns A value of the 'Content-MD5' header.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> get_ContentMD5();
    /// Sets a value of the 'Content-MD5' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentMD5(System::ArrayPtr<uint8_t> value);
    /// Gets a value of the 'Content-Range' header.
    /// @returns A value of the 'Content-Range' header.
    ASPOSECPP_SHARED_API System::SharedPtr<ContentRangeHeaderValue> get_ContentRange();
    /// Sets a value of the 'Content-Range' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentRange(System::SharedPtr<ContentRangeHeaderValue> value);
    /// Gets a value of the 'Content-Type' header.
    /// @returns A value of the 'Content-Type' header.
    ASPOSECPP_SHARED_API System::SharedPtr<MediaTypeHeaderValue> get_ContentType();
    /// Sets a value of the 'Content-Type' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ContentType(System::SharedPtr<MediaTypeHeaderValue> value);
    /// Gets a value of the 'Expires' header.
    /// @returns A value of the 'Expires' header.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_Expires();
    /// Sets a value of the 'Expires' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Expires(Nullable<DateTimeOffset> value);
    /// Gets a value of the 'Last-Modified' header.
    /// @returns A value of the 'Last-Modified' header.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_LastModified();
    /// Sets a value of the 'Last-Modified' header.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_LastModified(Nullable<DateTimeOffset> value);

    /// Constructs a new instance.
    /// @param calculateLengthFunc The function that is used to calculate the content length.
    ASPOSECPP_SHARED_API HttpContentHeaders(HeaderFunc<Nullable<int64_t>> calculateLengthFunc);

    /// Adds the known headers to the specified collection.
    /// @param headerSet A collection to which the known headers will be added.
    ASPOSECPP_SHARED_API static void AddKnownHeaders(System::SharedPtr<Collections::Generic::HashSet<String>> headerSet);

private:
    /// The collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        s_parserStore;
    /// The collection of the invalid headers.
    static System::SharedPtr<Collections::Generic::HashSet<String>> s_invalidHeaders;
    /// The function that is used to calculate the content length.
    HeaderFunc<Nullable<int64_t>> _calculateLengthFunc;
    /// Indicates if the content length is set.
    bool _contentLengthSet;
    /// A value of the 'Allow' header.
    System::SharedPtr<HttpHeaderValueCollection<String>> _allow;
    /// A value of the 'Content-Encoding' header.
    System::SharedPtr<HttpHeaderValueCollection<String>> _contentEncoding;
    /// A value of the 'Content-Language' header.
    System::SharedPtr<HttpHeaderValueCollection<String>> _contentLanguage;

    /// Creates a new collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        CreateParserStore();
    /// Returns the collection of the HTTP parsers.
    static System::SharedPtr<Collections::Generic::Dictionary<String, System::SharedPtr<HttpHeaderParser>>>
        GetParserStore();
    /// Creates a new instance of an invalid headers collection.
    static System::SharedPtr<Collections::Generic::HashSet<String>> CreateInvalidHeaders();
    /// Returns the collection of the invalid headers.
    static System::SharedPtr<Collections::Generic::HashSet<String>> GetInvalidHeaders();

    /// Initializes the static fields.
    void InitStatic();
};

}}}} // namespace System::Net::Http::Headers
