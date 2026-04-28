/// @file net/web_request.h
#pragma once

#include <system/async_callback.h>
#include <system/collections/list.h>
#include <system/iasyncresult.h>
#include <system/io/stream.h>
#include <system/string.h>

#include <net/cache/request_cache_policy.h>
#include <net/iweb_proxy.h>
#include <net/iweb_request_create.h>
#include <net/web_header_collection.h>

namespace System { namespace Net { namespace {
class RequestCachePolicy;
}}} // namespace System::Net::

namespace System { namespace Net {

class HttpWebRequest;
class FileWebRequest;
class WebRequest;
class WebResponse;

/// Represents a web request.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT WebRequest : public virtual System::Object
{
public:
    /// Represents an HTTP or HTTPS prefix.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class WebRequestPrefixElement : public System::Object
    {
    public:
        /// The prefix.
        String Prefix;
        /// Creates a new instances of the WebRequest class.
        System::SharedPtr<IWebRequestCreate> Creator;

        /// Constructs a new instance.
        /// @param P The prefix.
        /// @param C Creates a new instances of the WebRequest class.
        WebRequestPrefixElement(String P, System::SharedPtr<IWebRequestCreate> C);
    };

    /// Creates the WebRequest-class instances.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class HttpRequestCreator : public System::Net::IWebRequestCreate
    {
    public:
        /// Creates a new instance of the WebRequest-class using the specified URI.
        /// @param Uri The URI that is used to create a new instance.
        //// @returns A newly created WebRequest-class instance.
        System::SharedPtr<WebRequest> Create(System::SharedPtr<Uri> Uri);
    };

public:
    /// Gets the prefix list.
    /// @returns The prefix list.
    static System::SharedPtr<Collections::Generic::List<System::SharedPtr<WebRequest::WebRequestPrefixElement>>>
        get_PrefixList();
    /// Sets the prefix list.
    /// @param value The prefix list to set.
    static void set_PrefixList(
        System::SharedPtr<Collections::Generic::List<System::SharedPtr<WebRequest::WebRequestPrefixElement>>> value);
    /// Gets the HTTP method.
    /// @returns The HTTP method.
    virtual String get_Method() = 0;
    /// Sets the HTTP method.
    /// @param value The HTTP method to set.
    virtual void set_Method(String value) = 0;
    /// Returns the request URI.
    /// @returns The request URI.
    virtual System::SharedPtr<Uri> get_RequestUri() = 0;
    /// Gets the collection of the HTTP headers.
    /// @returns The collection of the HTTP headers.
    virtual System::SharedPtr<WebHeaderCollection> get_Headers() = 0;
    /// Sets the collection of the HTTP headers.
    /// @param value The collection of the HTTP headers to set.
    virtual void set_Headers(System::SharedPtr<WebHeaderCollection> value) = 0;
    /// Gets the MIME type of the request.
    /// @returns The MIME type of the request.
    virtual String get_ContentType() = 0;
    /// Sets the MIME type of the request.
    /// @param value The MIME type to set.
    virtual void set_ContentType(String value) = 0;
    /// Gets authentication information that is associated with the current request.
    /// @returns Authentication information that is associated with the current request.
    virtual System::SharedPtr<ICredentials> get_Credentials();
    /// Sets authentication information that is associated with the current request.
    /// @param value Authentication information to set.
    virtual void set_Credentials(System::SharedPtr<ICredentials> value);
    /// Gets a value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @returns The value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @throws System::NotImplementedException
    virtual bool get_UseDefaultCredentials();
    /// Sets a value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @param value A value to set.
    virtual void set_UseDefaultCredentials(bool value);
    /// Gets the global HTTP proxy.
    /// @returns The global HTTP proxy.
    static System::SharedPtr<IWebProxy> get_DefaultWebProxy();
    /// Sets the global HTTP proxy.
    /// @param value The proxy to set.
    static void set_DefaultWebProxy(System::SharedPtr<IWebProxy> value);
    /// Gets the HTTP proxy.
    /// @returns The HTTP proxy.
    virtual System::SharedPtr<IWebProxy> get_Proxy();
    /// Sets the HTTP proxy.
    /// @param value The proxy to set.
    virtual void set_Proxy(System::SharedPtr<IWebProxy> value);

    /// Creates a new instance of the WebRequest class using the specified URI.
    /// @param requestUriString The URI that is used to create a new instance of the WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    ASPOSECPP_SHARED_API static System::SharedPtr<WebRequest> Create(String requestUriString);
    /// Creates a new instance of the WebRequest class using the specified URI.
    /// @param requestUri The URI that is used to create a new instance of the WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    ASPOSECPP_SHARED_API static System::SharedPtr<WebRequest> Create(System::SharedPtr<Uri> requestUri);
    /// Creates a WebRequest descendant for the specified URI scheme.
    /// @param requestUri The URI that is used to create a new instance of the WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    static System::SharedPtr<WebRequest> CreateDefault(System::SharedPtr<Uri> requestUri);
    /// Creates a new instance of the WebRequest class using the specified URI.
    /// @param requestUriString The URI that is used to create a new instance of the WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    /// @remarks NotSupportedException will be thrown when the specified URI begins with any scheme except for http://
    /// or https://.
    static System::SharedPtr<HttpWebRequest> CreateHttp(String requestUriString);
    /// Creates a new instance of the WebRequest class using the specified URI.
    /// @param requestUri The URI that is used to create a new instance of the WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    /// @remarks NotSupportedException will be thrown when the specified URI begins with any scheme except for http://
    /// or https://.
    static System::SharedPtr<HttpWebRequest> CreateHttp(System::SharedPtr<Uri> requestUri);
    /// Registers the WebRequest descendant for the specified URI.
    /// @param prefix The URI or the URI prefix.
    /// @param creator Creates new instances of the WebRequest class.
    /// @returns True when the WebRequest descendant is successfully registered for the specified URI, otherwise false.
    static bool RegisterPrefix(String prefix, System::SharedPtr<IWebRequestCreate> creator);
    /// Initiates an asynchronous request for the resource.
    /// @param callback A callback to be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    virtual System::SharedPtr<IAsyncResult> BeginGetResponse(AsyncCallback callback,
                                                             System::SharedPtr<Object> state) = 0;
    /// Waits until the specified asynchronous request for the resource completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous request for the resource.
    /// @returns The web response.
    virtual System::SharedPtr<WebResponse> EndGetResponse(System::SharedPtr<IAsyncResult> asyncResult) = 0;
    /// Initiates an asynchronous operation to get a stream for writing data to the resource.
    /// @param callback A callback to be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous operation.
    virtual System::SharedPtr<IAsyncResult> BeginGetRequestStream(AsyncCallback callback,
                                                                  System::SharedPtr<Object> state) = 0;
    /// Waits until the specified asynchronous operation to get a stream completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous operation to get a stream.
    /// @returns The stream for writing data to the resource.
    virtual System::SharedPtr<IO::Stream> EndGetRequestStream(System::SharedPtr<IAsyncResult> asyncResult) = 0;
    /// Aborts the current request.
    virtual void Abort() = 0;

    /// Gets the number of bytes of the request data to sent.
    /// @returns The number of bytes of the request data to sent.
    ASPOSECPP_SHARED_API virtual int64_t get_ContentLength();
    /// Sets the number of bytes of the request data to sent.
    /// @param value The number of bytes to set.
    ASPOSECPP_SHARED_API virtual void set_ContentLength(int64_t value);

    /// Gets the cache policy.
    /// @returns The cache policy.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<System::Net::Cache::RequestCachePolicy> get_CachePolicy();
    /// Sets the cache policy.
    /// @param value The cache policy to set.
    ASPOSECPP_SHARED_API virtual void set_CachePolicy(System::SharedPtr<System::Net::Cache::RequestCachePolicy> value);

    /// Gets the name of the connection group.
    /// @returns The name of the connection group.
    ASPOSECPP_SHARED_API virtual System::String get_ConnectionGroupName();
    /// Sets the name of the connection group.
    /// @param value The name of the connection group to set.
    ASPOSECPP_SHARED_API virtual void set_ConnectionGroupName(System::String value);

    /// Gets a value that indicates if the request must be pre-authenticated.
    /// @returns A value that indicates if the request must be pre-authenticated.
    ASPOSECPP_SHARED_API virtual bool get_PreAuthenticate();
    /// Sets a value that indicates if the request must be pre-authenticated.
    /// @param value A value to set.
    ASPOSECPP_SHARED_API virtual void set_PreAuthenticate(bool value);

    /// Gets an amount of time in milliseconds after which the request will be timed out.
    /// @returns An amount of time in milliseconds after which the request will be timed out.
    ASPOSECPP_SHARED_API virtual int32_t get_Timeout();
    /// Sets an amount of time in milliseconds after which the request will be timed out.
    /// @param timeout A timeout to set.
    ASPOSECPP_SHARED_API virtual void set_Timeout(int32_t timeout);

    /// Returns the web response associated with the current web request.
    /// @returns The web response associated with the current web request.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<WebResponse> GetResponse();
    /// Returns the stream for writing data to the resource.
    /// @returns The stream for writing data to the resource.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<System::IO::Stream> GetRequestStream();

protected:
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API WebRequest();

private:
    /// The prefix list.
    static System::SharedPtr<Collections::Generic::List<System::SharedPtr<WebRequest::WebRequestPrefixElement>>>
        s_prefixList;
    /// Used to lock the current object.
    static System::SharedPtr<Object> s_internalSyncObject;
    /// The global HTTP proxy.
    static System::SharedPtr<IWebProxy> s_DefaultWebProxy;
    /// A value that indicates if the global HTTP proxy is initialized.
    static bool s_DefaultWebProxyInitialized;

    /// Creates a web request for the specified URI.
    /// @param requestUri The URI that is used to create a new instance of the WebRequest class.
    /// @param useUriBase A value that indicates if only URI scheme must be used to create a new instance of the
    /// WebRequest class.
    /// @returns A newly created WebRequest-class instance.
    static System::SharedPtr<WebRequest> Create(System::SharedPtr<Uri> requestUri, bool useUriBase);
};

}} // namespace System::Net
