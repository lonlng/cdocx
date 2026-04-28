/// @file net/http/http_client_handler.h
#pragma once
#include <system/idisposable.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/cookie_container.h>
#include <net/http/http_message_handler.h>
#include <net/iweb_proxy.h>

namespace System { namespace Net { namespace Http {

/// Represents the default message handler used by the HttpClient class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpClientHandler : public HttpMessageHandler
{
    /// This type.
    typedef HttpClientHandler ThisType;
    /// Parent type.
    typedef System::Net::Http::HttpMessageHandler BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpClientHandler();
    /// @copydoc System::IDisposable::Dispose
    ASPOSECPP_SHARED_API void Dispose() override;
    /// @copydoc System::Net::Http::HttpMessageHandler::Send
    ASPOSECPP_SHARED_API System::SharedPtr<HttpResponseMessage> Send(System::SharedPtr<HttpRequestMessage> request) override;
    /// Gets the authentication information.
    /// @returns The authentication information.
    ASPOSECPP_SHARED_API System::SharedPtr<ICredentials> get_Credentials();
    /// Sets the authentication information.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Credentials(System::SharedPtr<ICredentials> value);
    /// Gets the cookie container that is used to store server cookies.
    /// @returns The cookie container that is used to store server cookies.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Net::CookieContainer> get_CookieContainer();
    /// Sets the cookie container that is used to store server cookies.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_CookieContainer(System::SharedPtr<System::Net::CookieContainer> value);
    /// Sets the value that indicates if the current instance uses the cookie container to store server cookies and if
    /// the instance uses server cookies when sending requests.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_UseCookies(bool value);
    /// Sets the proxy information.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Proxy(System::SharedPtr<IWebProxy> value);
    /// Sets the value that indicates if the current instance uses the proxy for sending requests.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_UseProxy(bool value);
    /// Gets an amount of time in milliseconds after which the request will be timed out.
    /// @param timeout An amount of time in milliseconds after which the request will be timed out.
    ASPOSECPP_SHARED_API void set_Timeout(int32_t timeout);

protected:
    /// The cookie container.
    System::SharedPtr<System::Net::CookieContainer> _cookieContainer;
    /// The authentication information.
    System::SharedPtr<ICredentials> _credentials;
    /// The proxy information.
    System::SharedPtr<IWebProxy> _proxy;
    int32_t _timeout;

    /// @copydoc System::Net::Http::HttpMessageHandler::Dispose
    void Dispose(bool disposing) override;
};

}}} // namespace System::Net::Http
