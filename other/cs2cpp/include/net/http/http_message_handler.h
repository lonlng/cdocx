/// @file net/http/http_message_handler.h
#pragma once

#include <system/idisposable.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/http/http_request_message.h>
#include <net/http/http_response_message.h>

namespace System { namespace Net { namespace Http {

/// Represents a base type for the HTTP message handlers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ABSTRACT HttpMessageHandler : public System::IDisposable
{
    /// This type.
    typedef HttpMessageHandler ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Sends the specified request.
    /// @param request The request to send.
    /// @returns The HTTP response message.
    virtual System::SharedPtr<HttpResponseMessage> Send(System::SharedPtr<HttpRequestMessage> request) = 0;
    /// @copydoc System::IDisposable::Dispose
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Constructs a new instance.
    HttpMessageHandler();

    /// Disposes the current instance.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);
};

}}} // namespace System::Net::Http
