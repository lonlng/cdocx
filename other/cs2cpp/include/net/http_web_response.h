/// @file net/http_web_response.h
#pragma once

#include <system/collections/ienumerable.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/uri.h>

#include <net/cookie_collection.h>
#include <net/cookie_container.h>
#include <net/http/http_response_message.h>
#include <net/http_status_code.h>
#include <net/web_header_collection.h>
#include <net/web_response.h>

namespace System { namespace Net {

/// Represents the HTTP web response.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpWebResponse : public System::Net::WebResponse
{
    /// This type.
    typedef HttpWebResponse ThisType;
    /// Parent type.
    typedef System::Net::WebResponse BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// @copydoc System::Net::WebResponse::get_ContentLength
    ASPOSECPP_SHARED_API int64_t get_ContentLength() override;
    /// @copydoc System::Net::WebResponse::get_ContentType
    ASPOSECPP_SHARED_API String get_ContentType() override;
    /// Returns cookies associated with the web response.
    /// @returns Cookies associated with the web response.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<CookieCollection> get_Cookies();
    /// @copydoc System::Net::WebResponse::get_Headers
    ASPOSECPP_SHARED_API System::SharedPtr<WebHeaderCollection> get_Headers() override;
    /// Returns the HTTP method.
    /// @returns The HTTP method.
    ASPOSECPP_SHARED_API virtual String get_Method();
    /// @copydoc System::Net::WebResponse::get_ResponseUri
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_ResponseUri() override;
    /// Returns the HTTP status code associated with the web response.
    /// @returns The HTTP status code associated with the web response.
    ASPOSECPP_SHARED_API virtual HttpStatusCode get_StatusCode();
    /// Returns the string representation of the status code.
    /// @returns The string representation of the status code.
    ASPOSECPP_SHARED_API virtual String get_StatusDescription();
    /// @copydoc System::Net::WebResponse::get_SupportsHeaders
    ASPOSECPP_SHARED_API bool get_SupportsHeaders() override;
    /// Returns the corresponding value for the specified header name.
    /// @param headerName The header name.
    /// @returns The corresponding value for the specified header name.
    ASPOSECPP_SHARED_API String GetResponseHeader(String headerName);

    /// Constructs a new instance.
    /// @param _message The response message.
    /// @param requestUri The resource's URI.
    /// @param cookieContainer The cookie container.
    ASPOSECPP_SHARED_API HttpWebResponse(System::SharedPtr<Http::HttpResponseMessage> _message,
                                         System::SharedPtr<Uri> requestUri,
                                         System::SharedPtr<CookieContainer> cookieContainer);

    /// @copydoc System::Net::WebResponse::GetResponseStream
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream> GetResponseStream() override;
    /// @copydoc System::Net::WebResponse::Close
    ASPOSECPP_SHARED_API void Close() override;

    /// Not implemented.
    /// @internal
    ASPOSECPP_SHARED_API System::String get_CharacterSet()
    {
        throw NotImplementedException(ASPOSE_CURRENT_FUNCTION);
    }

protected:
    /// @copydoc System::Net::WebResponse::Dispose
    void Dispose(bool disposing) override;
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    /// The response message.
    System::SharedPtr<Http::HttpResponseMessage> _httpResponseMessage;
    /// The resource's URI.
    System::SharedPtr<Uri> _requestUri;
    /// Cookies that are associated with the web response.
    System::SharedPtr<CookieCollection> _cookies;
    /// The HTTP header collection of the web response.
    System::SharedPtr<WebHeaderCollection> _webHeaderCollection;

    /// Checks if the current instance is disposed.
    /// @throws ObjectDisposedException When the current instance is disposed.
    void CheckDisposed();
    /// Returns the string representation of the specified HTTP headers' values.
    /// @param values HTTP headers' values.
    /// @returns The string representation of the specified HTTP headers' values.
    String GetHeaderValueAsString(System::SharedPtr<Collections::Generic::IEnumerable<String>> values);
};

}} // namespace System::Net
