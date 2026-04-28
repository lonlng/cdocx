/// @file net/web/services/protocol/http_web_client_protocol.h
#pragma once
#include <security/cryptography/x509_certificates/x509_certificate_collection.h>
#include <system/iasyncresult.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/type_info.h>

#include <net/cookie_container.h>
#include <net/http_web_response.h>
#include <net/iweb_proxy.h>
#include <net/web/services/protocol/web_client_protocol.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// This base class is used in all XML Web service client proxies that use HTTP.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT HttpWebClientProtocol : public System::Web::Services::Protocols::WebClientProtocol
{
public:
    /// Gets a value that indicates if the client follows server redirects.
    /// @returns A value that indicates if the client follows server redirects.
    ASPOSECPP_SHARED_API bool get_AllowAutoRedirect();
    /// Sets a value that indicates if the client follows server redirects.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_AllowAutoRedirect(bool value);
    /// Returns the collection of the client certificates.
    /// @returns The collection of the client certificates.
    ASPOSECPP_SHARED_API System::SharedPtr<Security::Cryptography::X509Certificates::X509CertificateCollection>
        get_ClientCertificates();
    /// Gets a container that is used to store cookies.
    /// @returns A container that is used to store cookies.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Net::CookieContainer> get_CookieContainer();
    /// Sets a container that is used to store cookies.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_CookieContainer(System::SharedPtr<System::Net::CookieContainer> value);
    /// Gets a value that indicates if decompression is enabled.
    /// @returns A value that indicates if decompression is enabled.
    ASPOSECPP_SHARED_API bool get_EnableDecompression();
    /// Sets a value that indicates if decompression is enabled.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_EnableDecompression(bool value);
    /// Gets proxy information.
    /// @returns Proxy information.
    ASPOSECPP_SHARED_API System::SharedPtr<Net::IWebProxy> get_Proxy();
    /// Sets proxy information.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Proxy(System::SharedPtr<Net::IWebProxy> value);
    /// Gets a value of the 'User-Agent' header.
    /// @returns A value of the 'User-Agent' header.
    ASPOSECPP_SHARED_API String get_UserAgent();
    /// Sets a value of the 'User-Agent' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_UserAgent(String value);
    /// Gets a value that indicates if the connection sharing is enabled when the client uses NTLM authentication.
    /// @returns A value that indicates if the connection sharing is enabled when the client uses NTLM authentication.
    ASPOSECPP_SHARED_API bool get_UnsafeAuthenticatedConnectionSharing();
    /// Sets a value that indicates if the connection sharing is enabled when the client uses NTLM authentication.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_UnsafeAuthenticatedConnectionSharing(bool value);

    /// Appends cookies from the specified request to the internal cookie container.
    /// @param response The response from which the cookies will be taken.
    ASPOSECPP_SHARED_API virtual void CheckForCookies(System::SharedPtr<Net::HttpWebResponse> response);
    /// @internal
    void UnregisterMapping(System::SharedPtr<Object> userState);

protected:
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpWebClientProtocol();

    /// @copydoc System::Web::Services::Protocols::WebClientProtocol::GetWebRequest
    ASPOSECPP_SHARED_API System::SharedPtr<Net::WebRequest> GetWebRequest(System::SharedPtr<Uri> uri) override;
    /// @copydoc System::Web::Services::Protocols::WebClientProtocol::GetWebResponse
    ASPOSECPP_SHARED_API System::SharedPtr<Net::WebResponse>
        GetWebResponse(System::SharedPtr<Net::WebRequest> request) override;
    /// @copydoc System::Web::Services::Protocols::WebClientProtocol::GetWebResponse(System::SharedPtr<Net::WebRequest> request, System::SharedPtr<IAsyncResult> result)
    ASPOSECPP_SHARED_API System::SharedPtr<Net::WebResponse>
        GetWebResponse(System::SharedPtr<Net::WebRequest> request, System::SharedPtr<IAsyncResult> result) override;
    /// @throws System::NotImplementedException
    ASPOSECPP_SHARED_API void CancelAsync(System::SharedPtr<Object> userState);

private:
    /// A value that indicates if the client follows server redirects.
    bool allowAutoRedirect;
    /// A value that indicates if the decompression is enabled.
    bool enableDecompression;
    /// The collection of the client certificates.
    System::SharedPtr<Security::Cryptography::X509Certificates::X509CertificateCollection> clientCertificates;
    /// A container that is used to store cookies.
    System::SharedPtr<System::Net::CookieContainer> cookieContainer;
    /// Proxy information.
    System::SharedPtr<Net::IWebProxy> proxy;
    /// A value of the 'User-Agent' header.
    String userAgent;
    /// A value that indicates if the connection sharing is enabled when the client uses NTLM authentication.
    bool _unsafeAuthenticated;
};

}}}} // namespace System::Web::Services::Protocols
