/// @file net/http_web_request.h
#pragma once

#include <cstdint>
#include <system/async_callback.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>
#include <net/cookie_container.h>
#include <net/http/http_response_message.h>
#include <net/iweb_proxy.h>
#include <net/service_point.h>
#include <net/web_request.h>
#include "security/cryptography/x509_certificates/x509_certificate_collection.h"

namespace System { namespace Net {

namespace Http {
    class HttpResponseMessage;
}

class RequestStream;

/// Represents the HTTP web request.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpWebRequest : public System::Net::WebRequest
{
    /// This type.
    typedef HttpWebRequest ThisType;
    /// Parent type.
    typedef System::Net::WebRequest BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Sets the version of the HTTP.
    /// @param version A version of the HTTP to set.
    ASPOSECPP_SHARED_API void set_ProtocolVersion(System::Version version);
    /// @copydoc System::Net::WebRequest::set_Timeout
    ASPOSECPP_SHARED_API void set_Timeout(int timeout) override;
    /// @copydoc System::Net::WebRequest::set_PreAuthenticate
    ASPOSECPP_SHARED_API void set_PreAuthenticate(bool value) override;
    /// Sets the number of bytes of the request data to sent.
    /// @param length The number of bytes to set.
    ASPOSECPP_SHARED_API void set_ContentLength(int64_t length) override;

    /// Gets the 'Accept' HTTP header value.
    /// @returns The 'Accept' HTTP header value.
    ASPOSECPP_SHARED_API String get_Accept();
    /// Sets the 'Accept' HTTP header value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Accept(String value);
    /// Gets a value indicates if the data received from the resource must be buffered.
    /// @returns A value indicates if the data received from the resource must be buffered.
    ASPOSECPP_SHARED_API virtual bool get_AllowReadStreamBuffering();
    /// Sets a value indicates if the data received from the resource must be buffered.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_AllowReadStreamBuffering(bool value);
    /// @copydoc System::Net::WebRequest::get_ContentType
    ASPOSECPP_SHARED_API String get_ContentType() override;
    /// @copydoc System::Net::WebRequest::set_ContentType
    ASPOSECPP_SHARED_API void set_ContentType(String value) override;
    /// Gets a timeout to wait until the 100-Continue status code is received.
    /// @returns A timeout to wait until the 100-Continue status code is received.
    ASPOSECPP_SHARED_API int32_t get_ContinueTimeout();
    /// Sets a timeout to wait until the 100-Continue status code is received.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ContinueTimeout(int32_t value);
    /// Gets a cookie container associated with the current web request.
    /// @returns A cookie container associated with the current web request.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<System::Net::CookieContainer> get_CookieContainer();
    /// Sets a cookie container associated with the current web request.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_CookieContainer(System::SharedPtr<System::Net::CookieContainer> value);
    /// @copydoc System::Net::WebRequest::get_Credentials
    ASPOSECPP_SHARED_API System::SharedPtr<ICredentials> get_Credentials() override;
    /// @copydoc System::Net::WebRequest::set_Credentials
    ASPOSECPP_SHARED_API void set_Credentials(System::SharedPtr<ICredentials> value) override;
    /// Returns a value that indicates if a response is received.
    /// @returns A value that indicates if a response is received.
    ASPOSECPP_SHARED_API virtual bool get_HaveResponse();
    /// @copydoc System::Net::WebRequest::get_Headers
    ASPOSECPP_SHARED_API System::SharedPtr<WebHeaderCollection> get_Headers() override;
    /// @copydoc System::Net::WebRequest::set_Headers
    ASPOSECPP_SHARED_API void set_Headers(System::SharedPtr<WebHeaderCollection> value) override;
    /// @copydoc System::Net::WebRequest::get_Method
    ASPOSECPP_SHARED_API String get_Method() override;
    /// @copydoc System::Net::WebRequest::set_Method
    ASPOSECPP_SHARED_API void set_Method(String value) override;
    /// @copydoc System::Net::WebRequest::get_RequestUri
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_RequestUri() override;
    /// Returns a value that indicates if the current request can use a cookie container.
    /// @returns A value that indicates if the current request can use a cookie container.
    ASPOSECPP_SHARED_API virtual bool get_SupportsCookieContainer();
    /// @copydoc System::Net::WebRequest::get_UseDefaultCredentials
    ASPOSECPP_SHARED_API bool get_UseDefaultCredentials() override;
    /// @copydoc System::Net::WebRequest::set_UseDefaultCredentials
    ASPOSECPP_SHARED_API void set_UseDefaultCredentials(bool value) override;
    /// @copydoc System::Net::WebRequest::get_Proxy
    ASPOSECPP_SHARED_API System::SharedPtr<IWebProxy> get_Proxy() override;
    /// @copydoc System::Net::WebRequest::set_Proxy
    ASPOSECPP_SHARED_API void set_Proxy(System::SharedPtr<IWebProxy> value) override;

    /// Returns a service point that represents the network connection to the resource.
    /// @returns A service point that represents the network connection to the resource.
    ASPOSECPP_SHARED_API System::SharedPtr<ServicePoint> get_ServicePoint();

    /// Gets a value that indicates if the request should follow redirections.
    /// @returns A value that indicates if the request should follow redirections.
    ASPOSECPP_SHARED_API virtual bool get_AllowAutoRedirect();
    /// Sets a value that indicates if the request should follow redirections.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_AllowAutoRedirect(bool value);

    /// Gets a maximum number of allowed redirections.
    /// @returns A maximum number of allowed redirections.
    ASPOSECPP_SHARED_API virtual int get_MaximumAutomaticRedirections();
    /// Sets a maximum number of allowed redirections.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_MaximumAutomaticRedirections(int value);

    /// Constructs a new instance.
    /// @param uri The resource's URI.
    ASPOSECPP_SHARED_API HttpWebRequest(System::SharedPtr<Uri> uri);
    /// @copydoc System::Net::WebRequest::GetResponse
    ASPOSECPP_SHARED_API System::SharedPtr<WebResponse> GetResponse() override;
    /// @copydoc System::Net::WebRequest::Abort
    ASPOSECPP_SHARED_API void Abort() override;
    /// @copydoc System::Net::WebRequest::GetRequestStream
    ASPOSECPP_SHARED_API System::SharedPtr<System::IO::Stream> GetRequestStream() override;
    /// @copydoc System::Net::WebRequest::BeginGetRequestStream
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetRequestStream(AsyncCallback callback,
                                                                               System::SharedPtr<Object> state) override;
    /// @copydoc System::Net::WebRequest::EndGetRequestStream
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream>
        EndGetRequestStream(System::SharedPtr<IAsyncResult> asyncResult) override;
    /// @copydoc System::Net::WebRequest::BeginGetResponse
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginGetResponse(AsyncCallback callback,
                                                                                  System::SharedPtr<Object> state) override;
    /// @copydoc System::Net::WebRequest::EndGetResponse
    ASPOSECPP_SHARED_API System::SharedPtr<WebResponse>
        EndGetResponse(System::SharedPtr<IAsyncResult> asyncResult) override;

    /// Gets a value that indicates if data must be sent in segments.
    /// @returns A value that indicates if data must be sent in segments.
    ASPOSECPP_SHARED_API virtual bool get_SendChunked();
    /// Sets a value that indicates if data must be sent in segments.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_SendChunked(bool value);
    /// Gets a value that indicates if buffering is enabled for sending data.
    /// @returns A value that indicates if buffering is enabled for sending data.
    ASPOSECPP_SHARED_API virtual bool get_AllowWriteStreamBuffering();
    /// Sets a value that indicates if buffering is enabled for sending data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_AllowWriteStreamBuffering(bool value);
    /// Gets a value that indicates if the current request must contain the 'Keep-Alive' header.
    /// @returns A value that indicates if the current request must contain the 'Keep-Alive' header.
    ASPOSECPP_SHARED_API virtual bool get_KeepAlive();
    /// Sets a value that indicates if the current request must contain the 'Keep-Alive' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_KeepAlive(bool value);
    /// Gets the collection of the certificates that are associated with the current request.
    /// @returns The collection of the certificates that are associated with the current request.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<
        System::Security::Cryptography::X509Certificates::X509CertificateCollection>
        get_ClientCertificates();
    /// Sets the collection of the certificates that are associated with the current request.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_ClientCertificates(
        System::SharedPtr<System::Security::Cryptography::X509Certificates::X509CertificateCollection> value);
    /// Gets a value of the 'User-Agent' header.
    /// @returns A value of the 'User-Agent' header.
    ASPOSECPP_SHARED_API virtual System::String get_UserAgent();
    /// Sets a value of the 'User-Agent' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_UserAgent(System::String value);
    /// @copydoc System::Net::WebRequest::get_ContentLength
    ASPOSECPP_SHARED_API int64_t get_ContentLength() override;
    /// @copydoc System::Net::WebRequest::get_PreAuthenticate
    ASPOSECPP_SHARED_API bool get_PreAuthenticate() override;
    /// @copydoc System::Net::WebRequest::get_Timeout
    ASPOSECPP_SHARED_API int32_t get_Timeout() override;
    /// Adds the 'Range' header to the current request.
    /// @param range The beginning or the end of the request range.
    ASPOSECPP_SHARED_API virtual void AddRange(int32_t range);
    /// Adds the 'Range' header to the current request.
    /// @param rangeSpecifier The unit in which ranges are specified.
    /// @param from The beginning of the request range.
    /// @param to The end of the request range.
    ASPOSECPP_SHARED_API virtual void AddRange(System::String rangeSpecifier, int32_t from, int32_t to);

    /// Gets a value of the 'Referer' header.
    /// @returns A value of the 'Referer' header.
    ASPOSECPP_SHARED_API virtual System::String get_Referer();
    /// Sets a value of the 'Referer' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API virtual void set_Referer(System::String value);

    /// @copydoc System::Net::WebRequest::get_ConnectionGroupName
    ASPOSECPP_SHARED_API System::String get_ConnectionGroupName() override;
    /// @copydoc System::Net::WebRequest::set_ConnectionGroupName
    ASPOSECPP_SHARED_API void set_ConnectionGroupName(System::String value) override;

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    /// The default value of a timeout to wait until the 100-Continue status code is received.
    static const int32_t DefaultContinueTimeout;
    /// The collection of the HTTP headers.
    System::SharedPtr<WebHeaderCollection> _webHeaderCollection;
    /// The request's URI.
    System::SharedPtr<Uri> _requestUri;
    /// The HTTP method.
    String _originVerb;
    /// A timeout to wait until the 100-Continue status code is received.
    int32_t _continueTimeout;
    /// A value that indicates if the data received from the resource must be buffered.
    bool _allowReadStreamBuffering;
    /// A cookie container associated with the current web request.
    System::SharedPtr<System::Net::CookieContainer> _cookieContainer;
    /// Credentials that are associated with the web request.
    System::SharedPtr<ICredentials> _credentials;
    /// Proxy information.
    System::SharedPtr<IWebProxy> _proxy;
    /// @internal
    /// @remarks Unused.
    int32_t _beginGetRequestStreamCalled;
    /// @internal
    /// @remarks Unused.
    int32_t _beginGetResponseCalled;
    /// @internal
    /// @remarks Unused.
    int32_t _endGetRequestStreamCalled;
    /// @internal
    /// @remarks Unused.
    int32_t _endGetResponseCalled;
    /// A stream that is used to write data of the web request.
    System::SharedPtr<RequestStream> _requestStream;
    /// @internal
    /// @remarks Unused.
    AsyncCallback _requestStreamCallback;
    /// @internal
    /// @remarks Unused.
    AsyncCallback _responseCallback;
    /// @internal
    /// @remarks Unused.
    int32_t _abortCalled;
    /// The number of bytes of data to send.
    int64_t _contentLength;
    /// A value that indicates if HTTP version 1.0 is used.
    bool _isVersionHttp10;
    /// A timeout in milliseconds to wait before the request times out.
    int32_t _timeout;
    /// A value that indicates if the 'Authorization' header is sent with the web request.
    bool m_PreAuthenticate;

    /// Returns a value that indicates if the web request is already sent.
    /// @returns A value that indicates if the web request is already sent.
    /// @remarks Always returns false.
    bool get_RequestSubmitted();

    /// Returns the collection of the "well known" headers.
    /// @returns The collection of the "well known" headers.
    static const System::ArrayPtr<String>& WellKnownContentHeaders();

    /// Sets the header value.
    /// @param HeaderName The name of the header whose value must be set.
    /// @param value The value that must be set.
    void SetSpecialHeaders(String HeaderName, String value);
    /// Not implemented.
    /// @internal
    void CheckAbort();
    /// Checks if the specified header is "well known".
    /// @param header The name of the header that must be checked.
    /// @returns True if the specified header is "well known", otherwise false.
    bool IsWellKnownContentHeader(String header);

    /// The name of a connection group.
    String _connectionGroupName;
    /// A value that indicates if the request should follow redirections.
    bool _allowAutoRedirect = true;
    /// A maximum number of redirections.
    int _maximumAutomaticRedirections = 50;
    /// A value that indicates if the current request must contain the 'Keep-Alive' header.
    bool _keepAlive;
    /// A value of the 'User-Agent' header.
    String _userAgent;

    /// Sends the web request.
    /// @param requestUri The resource's URI to which the web request must be sent.
    /// @param verb The HTTP method that is used for sending the web request.
    /// @param useCredentials A value that indicates if credentials must be sent.
    /// @returns A web response.
    SharedPtr<Http::HttpResponseMessage> DoRequest(const SharedPtr<Uri>& requestUri,
        const String& verb, bool useCredentials=true);
};

}} // namespace System::Net
