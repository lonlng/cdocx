/// @file net/http/http_response_message.h
#pragma once

#include <system/idisposable.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/http/headers/http_response_headers.h>
#include <net/http/http_request_message.h>
#include <net/http_status_code.h>

namespace System { namespace Net { namespace Http {

/// Represents an HTTP response message.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpResponseMessage : public System::IDisposable
{
    /// This type.
    typedef HttpResponseMessage ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the HTTP version.
    /// @returns The HTTP version.
    ASPOSECPP_SHARED_API System::Version get_Version() const;
    /// Sets the HTTP version.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Version(System::Version value);
    /// Gets content of the HTTP response.
    /// @returns Content of the HTTP response.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpContent> get_Content() const;
    /// Sets content of the HTTP response.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_Content(System::SharedPtr<HttpContent> value);
    /// Gets the HTTP status code.
    /// @returns The HTTP status code.
    ASPOSECPP_SHARED_API HttpStatusCode get_StatusCode() const;
    /// Sets the HTTP status code.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_StatusCode(HttpStatusCode value);
    /// Gets the Reason-Phrase that is sent by servers together with the status code.
    /// @returns The Reason-Phrase that is sent by servers together with the status code.
    ASPOSECPP_SHARED_API String get_ReasonPhrase() const;
    /// Sets the Reason-Phrase that is sent by servers together with the status code.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_ReasonPhrase(String value);
    /// Returns the HTTP content headers.
    /// @returns The HTTP content headers.
    ASPOSECPP_SHARED_API System::SharedPtr<Headers::HttpResponseHeaders> get_Headers() const;
    /// Gets the HTTP request message.
    /// @returns The HTTP request message.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpRequestMessage> get_RequestMessage() const;
    /// Sets the HTTP request message.
    /// @param value The value that will be set.
    ASPOSECPP_SHARED_API void set_RequestMessage(System::SharedPtr<HttpRequestMessage> value);
    /// Checks if the status code indicates that the action requested by the client was received, understood, and
    /// accepted.
    /// @returns True when the status code belongs to 2xx, otherwise false.
    ASPOSECPP_SHARED_API bool get_IsSuccessStatusCode() const;

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API HttpResponseMessage();
    /// Constructs a new instance.
    /// @param statusCode The HTTP status code.
    ASPOSECPP_SHARED_API HttpResponseMessage(HttpStatusCode statusCode);

    /// Checks the status code. HttpRequestException will be thrown when the status code doesn't belong to 2xx.
    /// @returns The current instance.
    /// @throws HttpRequestException When the status code doesn't belong to 2xx.
    ASPOSECPP_SHARED_API System::SharedPtr<HttpResponseMessage> EnsureSuccessStatusCode();
    /// System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Disposes the current instance. This method also disposes content of the HTTP response.
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Disposes the current instance. This method also disposes content of the HTTP response.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// @copydoc System::Object::GetSharedMembers
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    /// The 'OK' status code.
    static const HttpStatusCode defaultStatusCode;
    /// The HTTP status code.
    HttpStatusCode _statusCode;
    /// The HTTP content headers.
    mutable System::SharedPtr<Headers::HttpResponseHeaders> _headers;
    /// The Reason-Phrase that is sent by servers together with the status code.
    String _reasonPhrase;
    /// The HTTP request message.
    System::SharedPtr<HttpRequestMessage> _requestMessage;
    /// The HTTP version.
    System::Version _version;
    /// The HTTP content.
    System::SharedPtr<HttpContent> _content;
    /// Indicates if the current instance is disposed.
    bool _disposed;

    /// Checks if the specified string contains the newline characters.
    /// @param value The string to check.
    /// @returns True when the string contains the newline characters, otherwise false.
    bool ContainsNewLineCharacter(String value);
    /// Checks if the current instance is disposed.
    /// @throws ObjectDisposedException When the current instance is disposed.
    void CheckDisposed();
};

}}} // namespace System::Net::Http
