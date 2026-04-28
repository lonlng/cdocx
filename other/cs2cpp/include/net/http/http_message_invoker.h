/// @file net/http/http_message_invoker.h
#pragma once

#include <system/idisposable.h>
#include <system/shared_ptr.h>

#include <net/http/http_message_handler.h>

namespace System { namespace Net { namespace Http {

/// Allows applications to call the Send method on an HTTP handler chain.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HttpMessageInvoker : public System::IDisposable
{
    /// This type.
    typedef HttpMessageInvoker ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    /// @param handler The HTTP handler used for sending requests.
    ASPOSECPP_SHARED_API HttpMessageInvoker(System::SharedPtr<HttpMessageHandler> handler);
    /// Constructs a new instance.
    /// @param handler The HTTP handler used for sending requests.
    /// @param disposeHandler The value that indicates if the handler must be disposed when this instance is disposed.
    ASPOSECPP_SHARED_API HttpMessageInvoker(System::SharedPtr<HttpMessageHandler> handler, bool disposeHandler);

    /// Sends the specified request.
    /// @param request The request to send.
    /// @returns The HTTP response message.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<HttpResponseMessage> Send(System::SharedPtr<HttpRequestMessage> request);
    /// Disposes the current instance. This method also disposes the handler if required.
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Disposes the current instance. This method also disposes the handler if required.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);

private:
    /// Indicates that the current instance is disposed.
    bool _disposed;
    /// Indicates that the handler must be disposed when this instance is disposed.
    bool _disposeHandler;
    /// The HTTP handler used for sending requests.
    System::SharedPtr<HttpMessageHandler> _handler;

    /// Checks if the current instance is disposed.
    /// @throws ObjectDisposedException When the current instance is disposed.
    void CheckDisposed();
};

}}} // namespace System::Net::Http
