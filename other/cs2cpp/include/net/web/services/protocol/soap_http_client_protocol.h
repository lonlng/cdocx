/// @file net/web/services/protocol/soap_http_client_protocol.h
#pragma once
#include <system/iasyncresult.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/uri.h>
#include <xml/xml_writer.h>
#include <cstdint>
#include <net/web_request.h>
#include <system/array.h>
#include <system/async_callback.h>
#include <system/collections/dictionary.h>
#include <net/web/services/protocol/http_web_client_protocol.h>
#include <net/web/services/protocol/soap_protocol_version.h>
#include <system/threading/send_or_post_callback.h>
#include <xml/xml_reader.h>
#include <xml/xml_serializer_implementation.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

class SoapTypeStubInfo;
class SoapClientMessage;

/// The client proxy services must inherit this class when the SOAP is used.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SoapHttpClientProtocol : public System::Web::Services::Protocols::HttpWebClientProtocol
{
public:
    /// Gets the SOAP version.
    /// @returns The SOAP version.
    SoapProtocolVersion get_SoapVersion();
    /// Sets the SOAP version.
    /// @param value The value that must be set.
    void set_SoapVersion(SoapProtocolVersion value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API SoapHttpClientProtocol();

    /// Binds the current instance to the XML Web service.
    void Discover();
    /// Initializes the internal fields.
    /// @internal
    ASPOSECPP_SHARED_API void
        InitializeSerializers(const System::TypeInfo& serviceType,
                              System::SharedPtr<System::Xml::Serialization::XmlSerializerImplementation> impl,
                              String name /*, String ns*/);

protected:
    /// Initiates an asynchronous call.
    /// @param methodName The method name of the derived class that calls the 'BeginInvoke' method.
    /// @param parameters A collection of parameters passed to an XML Web service method.
    /// @param callback A callback to be called when the operation completes.
    /// @param asyncState User-provided data used to uniquely identify each asynchronous call.
    /// @returns An IAsyncResult object representing the initiated asynchronous call.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult>
        BeginInvoke(String methodName, System::ArrayPtr<System::SharedPtr<Object>> parameters, AsyncCallback callback,
                    System::SharedPtr<Object> asyncState);
    /// Waits until the specified asynchronous call completes.
    /// @param asyncResult An IAsyncResult object that represents an asynchronous call.
    /// @returns An array of objects that contains the method result and the output parameters.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<Object>>
        EndInvoke(System::SharedPtr<IAsyncResult> asyncResult);
    /// Creates a WebRequest-class instance for the specified URI.
    /// @param uri The URI that is used to initialize a new WebRequest-class instance.
    /// @returns A newly created WebRequest-class instance.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<Net::WebRequest> GetWebRequest(System::SharedPtr<System::Uri> uri);
    /// Creates an XmlReader-class instance using the specified message.
    /// @param message A SoapClientMessage-class instance that is used to initialize an XmlReader-class instance.
    /// @param bufferSize The initial size of the internal buffer.
    /// @returns A newly created XmlReader-class instance.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<Xml::XmlReader>
        GetReaderForMessage(System::SharedPtr<SoapClientMessage> message, int32_t bufferSize);
    /// Creates an XmlWriter-class instance using the specified message.
    /// @param message A SoapClientMessage-class instance that is used to initialize an XmlWriter-class instance.
    /// @param bufferSize The initial size of the internal buffer.
    /// @returns A newly created XmlWriter-class instance.
    ASPOSECPP_SHARED_API virtual System::SharedPtr<Xml::XmlWriter>
        GetWriterForMessage(System::SharedPtr<SoapClientMessage> message, int32_t bufferSize);
    /// Calls the specified method synchronously.
    /// @param method_name The method name of the XML Web service to call.
    /// @param parameters A collection of parameters passed to an XML Web service method.
    /// @returns An array of objects that contains the method result and the output parameters.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<Object>>
        Invoke(String method_name, System::ArrayPtr<System::SharedPtr<Object>> parameters);
    ASPOSECPP_SHARED_API void InvokeAsync(String methodName, System::ArrayPtr<System::SharedPtr<Object>> parameters,
                                          Threading::SendOrPostCallback callback);
    /// Calls the specified method asynchronously.
    /// @param methodName The method name of the XML Web service to call.
    /// @param parameters A collection of parameters passed to an XML Web service method.
    /// @param callback A callback to be called when the operation completes.
    /// @param userState User-provided data used to uniquely identify each asynchronous call.
    ASPOSECPP_SHARED_API void InvokeAsync(String methodName, System::ArrayPtr<System::SharedPtr<Object>> parameters,
                                          Threading::SendOrPostCallback callback, System::SharedPtr<Object> userState);

private:
    /// The collection of the utility-class instances that are used to work with the SOAP methods.
    static System::SharedPtr<
        System::Collections::Generic::Dictionary<System::String, System::SharedPtr<SoapTypeStubInfo>>>
        soapTypeInfos;
    /// An utility-class instance that ise used to work with the SOAP method.
    System::SharedPtr<SoapTypeStubInfo> soapTypeInfo;
    /// The SOAP version.
    SoapProtocolVersion soapVersion;

    /// Ends the specified asynchronous operation.
    /// @throws System::NotImplementedException
    void AsyncGetRequestStreamDone(System::SharedPtr<IAsyncResult> ar);
    /// @internal
    void AsyncGetResponseDone(System::SharedPtr<IAsyncResult> ar);
    /// Creates a WebRequest-class instance for the specified URI and message.
    /// @param uri The URI that is used to initialize a new WebRequest-class instance.
    /// @param message The message that is used to initialize a new WebRequest-class instance.
    /// @returns A newly created WebRequest-class instance.
    System::SharedPtr<Net::WebRequest> GetRequestForMessage(System::SharedPtr<System::Uri> uri,
                                                            System::SharedPtr<SoapClientMessage> message);
    /// Sends the specified message.
    /// @param s The output stream where the SOAP message will be assigned.
    /// @param message The message to send.
    void SendRequest(System::SharedPtr<IO::Stream> s, System::SharedPtr<SoapClientMessage> message);
    /// Handles the specified response.
    /// @param response A response that must be handled.
    /// @param message A message to initialize.
    /// @returns An array of objects that contains the method result and the output parameters.
    System::ArrayPtr<System::SharedPtr<Object>> ReceiveResponse(System::SharedPtr<Net::WebResponse> response,
                                                                System::SharedPtr<SoapClientMessage> message);
    /// A callback that is called by the asynchronous methods.
    /// @throws System::NotImplementedException
    void InvokeAsyncCallback(System::SharedPtr<IAsyncResult> ar);
};

}}}} // namespace System::Web::Services::Protocols
