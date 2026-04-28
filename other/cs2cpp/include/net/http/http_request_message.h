/// @file net/http/http_request_message.h
#pragma once

#include <net/http/headers/http_request_headers.h>
#include <net/http/http_content.h>
#include <net/http/http_method.h>
#include <cstdint>
#include <system/collections/idictionary.h>
#include <system/idisposable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>
#include <system/version.h>

namespace System { namespace Net { namespace Http {

/// Represents an HTTP request message.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpRequestMessage : public System::IDisposable
{
    /// This type.
    typedef HttpRequestMessage ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the HTTP version.
    /// @returns The HTTP version.
    ASPOSECPP_SHARED_API System::Version get_Version();
    /// Sets the HTTP version.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Version(System::Version value);
    /// Gets content of the HTTP request.
    /// @returns Content of the HTTP request.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpContent> get_Content();
    /// Sets content of the HTTP request.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Content(System::SharedPtr<HttpContent> value);
    /// Gets the HTTP request method.
    /// @returns The HTTP request method.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpMethod> get_Method();
    /// Sets the HTTP request method.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Method(System::SharedPtr<HttpMethod> value);
    /// Gets the URI of the requested resource.
    /// @returns The URI of the requested resource.
    ASPOSECPP_SHARED_API System::SharedPtr<Uri> get_RequestUri();
    /// Sets the URI of the requested resource.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_RequestUri(System::SharedPtr<Uri> value);
    /// Returns the HTTP content headers.
    /// @returns The HTTP content headers.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Net::Http::Headers::HttpRequestHeaders> get_Headers();
    /// Returns the collection of the HTTP request properties.
    /// @returns The collection of the HTTP request properties.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::IDictionary<String, System::SharedPtr<Object>>>
        get_Properties();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpRequestMessage();
    /// Constructs a new instance.
    /// @param method The HTTP method.
    /// @param requestUri The URI of the requested resource.
    ASPOSECPP_SHARED_API HttpRequestMessage(System::SharedPtr<HttpMethod> method, System::SharedPtr<Uri> requestUri);
    /// Constructs a new instance.
    /// @param method The HTTP method.
    /// @param requestUri The URI of the requested resource.
    ASPOSECPP_SHARED_API HttpRequestMessage(System::SharedPtr<HttpMethod> method, String requestUri);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Marks the current request as sent.
    /// @returns False when the current request was marked before, otherwise false.
    ASPOSECPP_SHARED_API bool MarkAsSent();
    /// Disposes the current instance. This method also disposes content of the HTTP request.
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Disposes the current instance. This method also disposes content of the HTTP request.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif
private:
    /// Indicates that the request was not sent before.
    static const int32_t MessageNotYetSent;
    /// Indicates that the request is already sent.
    static const int32_t MessageAlreadySent;
    /// Stores the request sending status.
    int32_t _sendStatus;
    /// The HTTP method.
    System::SharedPtr<HttpMethod> _method;
    /// The URI of the requested resource.
    System::SharedPtr<Uri> _requestUri;
    /// The HTTP content headers.
    System::SharedPtr<Headers::HttpRequestHeaders> _headers;
    /// The HTTP version.
    System::Version _version;
    /// Content of the HTTP request.
    System::SharedPtr<HttpContent> _content;
    /// Indicates if the current instance is disposed.
    bool _disposed;
    /// The collection of the HTTP request properties.
    System::SharedPtr<Collections::Generic::IDictionary<String, System::SharedPtr<Object>>> _properties;

    /// Initializes the current instance using the specified parameters.
    /// @param method The HTTP method.
    /// @param requestUri The URI of the requested resource.
    void InitializeValues(System::SharedPtr<HttpMethod> method, System::SharedPtr<Uri> requestUri);
    /// Checks if the current instance is disposed.
    /// @throws ObjectDisposedException When the current instance is disposed.
    void CheckDisposed();
};

}}} // namespace System::Net::Http
