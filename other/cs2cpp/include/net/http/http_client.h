/// @file net/http/http_client.h
#pragma once

#include <functional>
#include <system/globalization/culture_info.h>
#include <system/io/stream.h>
#include <system/shared_ptr.h>
#include <system/timespan.h>

#include <net/http/headers/http_request_headers.h>
#include <net/http/http_completion_option.h>
#include <net/http/http_content.h>
#include <net/http/http_message_handler.h>
#include <net/http/http_message_invoker.h>
#include <net/http/http_request_message.h>
#include <net/http/http_response_message.h>
#include <net/http_request_exception.h>

namespace System { namespace Net { namespace Http {

/// Represents a base class of an HTTP client for sending requests and receiving responses.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpClient : public System::Net::Http::HttpMessageInvoker
{
    /// This type.
    typedef HttpClient ThisType;
    /// Parent type.
    typedef System::Net::Http::HttpMessageInvoker BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the headers sent with each request.
    /// @returns The headers sent with each request.
    ASPOSECPP_SHARED_API System::SharedPtr<Headers::HttpRequestHeaders> get_DefaultRequestHeaders();
    /// Gets the base address of the resource that is used for sending requests.
    /// @returns The base address of the resource that is used for sending requests.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_BaseAddress();
    /// Sets the base address of the resource that is used for sending requests.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_BaseAddress(System::SharedPtr<Uri> value);
    /// Gets the timespan to wait before the request times out.
    /// @returns The timespan to wait before the request times out.
    ASPOSECPP_SHARED_API TimeSpan get_Timeout();
    /// Sets the timespan to wait before the request times out.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Timeout(TimeSpan value);
    /// Gets the maximum number of bytes of response content.
    /// @returns The maximum number of bytes of response content.
    ASPOSECPP_SHARED_API int64_t get_MaxResponseContentBufferSize();
    /// Sets the maximum number of bytes of response content.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_MaxResponseContentBufferSize(int64_t value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpClient();
    /// Constructs a new instance.
    /// @param handler The HTTP handler used for sending requests.
    ASPOSECPP_SHARED_API HttpClient(System::SharedPtr<HttpMessageHandler> handler);
    /// Constructs a new instance.
    /// @param handler The HTTP handler used for sending requests.
    /// @param disposeHandler The value that indicates if the handler must be disposed when this instance is disposed.
    ASPOSECPP_SHARED_API HttpClient(System::SharedPtr<HttpMessageHandler> handler, bool disposeHandler);

    /// Cancels all pending requests.
    ASPOSECPP_SHARED_API void CancelPendingRequests();

    /// Sends the specified HTTP request.
    /// @param request The HTTP request that must be sent.
    /// @param completionOption The value that indicates when to complete the operation.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpResponseMessage> Send(System::SharedPtr<HttpRequestMessage> request,
                                                                     HttpCompletionOption completionOption);

protected:
    /// @copydoc System::Net::Http::HttpMessageInvoker::Dispose
    void Dispose(bool disposing) override;

private:
    /// The default value of the timespan to wait before the request times out.
    static TimeSpan s_defaultTimeout;
    /// The maximum value of the timespan to wait before the request times out.
    static TimeSpan s_maxTimeout;
    /// The infinite value of the timespan to wait before the request times out.
    static TimeSpan s_infiniteTimeout;
    /// The default value that indicates when to complete the operation.
    static const HttpCompletionOption defaultCompletionOption;
    /// Indicates that the sending operation is started.
    bool _operationStarted;
    /// Indicates that the current instance is disposed.
    bool _disposed;
    /// The request headers sent with each request.
    System::SharedPtr<Headers::HttpRequestHeaders> _defaultRequestHeaders;
    /// The base address of the resource that is used for sending requests.
    System::SharedPtr<Uri> _baseAddress;
    /// The timespan to wait before the request times out.
    TimeSpan _timeout;
    /// The maximum number of bytes of response content.
    int64_t _maxResponseContentBufferSize;

    /// Disposes a content of the specified request.
    /// @param request Unused.
    void DisposeRequestContent(System::SharedPtr<HttpRequestMessage> request);
    /// Sets the value that indicates if the sending operation is started.
    void SetOperationStarted();
    /// Checks if the current instance is disposed or the sending operation is started.
    /// @throws InvalidOperationException When the current instance is disposed or the sending operation is started.
    void CheckDisposedOrStarted();
    /// Checks if the current instance is disposed.
    /// @throws ObjectDisposedException When the current instance is disposed.
    void CheckDisposed();
    /// Checks if the specified request was not sent before.
    /// @param request The request to check.
    /// @throws InvalidOperationException When the specified request was sent before.
    static void CheckRequestMessage(System::SharedPtr<HttpRequestMessage> request);
    /// Prepares the specified request for sending.
    /// @param request The request to prepare.
    void PrepareRequestMessage(System::SharedPtr<HttpRequestMessage> request);
    /// Checks if the specified base address is valid.
    /// @param baseAddress The base address to check.
    /// @param parameterName Unused.
    /// @throws ArgumentException When the absolute URI of the specified base address cannot be calculated or the
    /// specified base address is not an HTTP URI.
    static void CheckBaseAddress(System::SharedPtr<Uri> baseAddress, String parameterName);
    /// Creates a URI-class instance based on the specified string.
    /// @param uri The string representation of an URI.
    System::SharedPtr<Uri> CreateUri(String uri);

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}}} // namespace System::Net::Http
