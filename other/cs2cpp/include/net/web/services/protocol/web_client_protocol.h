/// @file net/web/services/protocol/web_client_protocol.h
#pragma once
#include <system/iasyncresult.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/text/encoding.h>
#include <system/type_info.h>
#include <system/uri.h>
#include <cstdint>
#include <net/web_request.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// This base class is used in all XML Web service client proxies that were created using ASP.NET.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT WebClientProtocol : virtual public System::Object
{
public:
    /// The XML Web service URI.
    System::SharedPtr<Uri> uri;
    /// Gets the XML Web service URI.
    /// @returns The XML Web service URI.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_Uri();
    /// Sets the XML Web service URI.
    /// @param uri The URI that must be set.
    ASPOSECPP_SHARED_API void set_Uri(System::SharedPtr<Uri> uri);

    /// Gets the name of the connection group.
    /// @returns The name of the connection group.
    ASPOSECPP_SHARED_API String get_ConnectionGroupName();
    /// Sets the name of the connection group.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ConnectionGroupName(String value);
    /// Gets the authentication information.
    /// @returns The authentication information.
    ASPOSECPP_SHARED_API System::SharedPtr<Net::ICredentials> get_Credentials();
    /// Sets the authentication information.
    /// @param value The authentication information.
    ASPOSECPP_SHARED_API void set_Credentials(System::SharedPtr<Net::ICredentials> value);
    /// Gets a value that indicates if pre-authentication is enabled.
    /// @returns A value that indicates if pre-authentication is enabled.
    ASPOSECPP_SHARED_API bool get_PreAuthenticate();
    /// Sets a value that indicates if pre-authentication is enabled.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_PreAuthenticate(bool value);
    /// Gets the encoding that is used to make the client requests.
    /// @returns The encoding that is used to make the client requests.
    ASPOSECPP_SHARED_API System::SharedPtr<Text::Encoding> get_RequestEncoding();
    /// Sets the encoding that is used to make the client requests.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_RequestEncoding(System::SharedPtr<Text::Encoding> value);
    /// Gets the timespan to wait before the request times out.
    /// @returns The timespan to wait before the request times out.
    ASPOSECPP_SHARED_API int32_t get_Timeout();
    /// Sets the timespan to wait before the request times out.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Timeout(int32_t value);
    /// Gets the XML Web service URL.
    /// @returns The XML Web service URL.
    ASPOSECPP_SHARED_API String get_Url();
    /// Sets the XML Web service URL.
    /// @param value The URL that must be set.
    ASPOSECPP_SHARED_API void set_Url(String value);
    /// Gets a value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @returns The value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @throws System::NotImplementedException
    ASPOSECPP_SHARED_API bool get_UseDefaultCredentials();
    /// Sets a value that indicates if the 'Credential' property is equal to the 'DefaultCredentials' property.
    /// @param value The value that must be set.
    /// @throws System::NotImplementedException
    ASPOSECPP_SHARED_API void set_UseDefaultCredentials(bool value);
    /// Cancels the request.
    ASPOSECPP_SHARED_API virtual void Abort();

protected:
    /// Constructs a new instance.
    WebClientProtocol();

    /// Adds the specified instance of the client protocol handler to the internal cache.
    /// @param type The type of the specified instance of the client protocol handler.
    /// @param value The client protocol handler to add.
    static void AddToCache(const TypeInfo& type, System::SharedPtr<Object> value);
    /// Gets the client protocol handler from the cache.
    /// @param type The type of the client protocol handler.
    static System::SharedPtr<Object> GetFromCache(const TypeInfo& type);
    /// Creates a WebRequest-class instance for the specified URI.
    /// @param uri The URI that is used to initialize a new WebRequest-class instance.
    /// @returns A newly created WebRequest-class instance.
    virtual System::SharedPtr<Net::WebRequest> GetWebRequest(System::SharedPtr<Uri> uri);
    /// Creates a WebResponse-class instance for the specified request.
    /// @param request The request that is used to initialize a new WebResponse-class instance.
    /// @returns A newly created WebRequest-class instance.
    virtual System::SharedPtr<Net::WebResponse> GetWebResponse(System::SharedPtr<Net::WebRequest> request);
    /// Creates a WebResponse-class instance for the specified request.
    /// @param request The request that is used to initialize a new WebResponse-class instance.
    /// @param result IAsyncResult that will be passed into the 'EndGetResponse' method when the response will be
    /// completed.
    /// @returns A newly created WebRequest-class instance.
    virtual System::SharedPtr<Net::WebResponse> GetWebResponse(System::SharedPtr<Net::WebRequest> request,
                                                               System::SharedPtr<IAsyncResult> result);

private:
    /// The name of the connection group.
    String connectionGroupName;
    /// The authentication information.
    System::SharedPtr<Net::ICredentials> credentials;
    /// A value that indicates if pre-authentication is enabled.
    bool preAuthenticate;
    /// The encoding that is used to make the client requests.
    System::SharedPtr<Text::Encoding> requestEncoding;
    /// The timespan to wait before the request times out.
    int32_t timeout;
    /// The current request.
    System::SharedPtr<Net::WebRequest> current_request;
    //    static System::SharedPtr<Collections::Specialized::HybridDictionary> cache;

    /// Static fields initializer.
    static struct __StaticConstructor__
    {
        __StaticConstructor__();
    } s_constructor__;
};

}}}} // namespace System::Web::Services::Protocols
