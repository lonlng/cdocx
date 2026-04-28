/// @file net/web/services/protocol/soap_message.h
#pragma once

#include <net/web/services/protocol/soap_exception.h>
#include <net/web/services/protocol/soap_message_stage.h>
#include <net/web/services/protocol/soap_protocol_version.h>
#include <net/web/services/protocol/soap_header_collection.h>
#include <net/web/services/protocol/soap_header_direction.h>
#include <cstdint>
#include <system/array.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/type_info.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

class SoapHttpClientProtocol;
class SoapHeaderCollection;
class SoapHeaderMapping;

/// Represent the SOAP message.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ABSTRACT ASPOSECPP_SHARED_CLASS SoapMessage : public System::Object
{

public:
    /// Gets the parameters that are passed into the XML Web service method.
    /// @returns The parameters that are passed into the XML Web service method.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<Object>> get_InParameters();
    /// Sets the parameters that are passed into the XML Web service method.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_InParameters(System::ArrayPtr<System::SharedPtr<Object>> value);
    /// Gets the output parameters passed into the XML Web service method.
    /// @returns The output parameters passed into the XML Web service method.
    ASPOSECPP_SHARED_API System::ArrayPtr<System::SharedPtr<Object>> get_OutParameters();
    /// Sets the output parameters passed into the XML Web service method.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_OutParameters(System::ArrayPtr<System::SharedPtr<Object>> value);
    /// Returns a value of the 'SOAPAction' attribute.
    /// @returns A value of the 'SOAPAction' attribute.
    ASPOSECPP_SHARED_API virtual String get_Action() = 0;
    /// Gets a value of the 'Content-Type' header.
    /// @returns A value of the 'Content-Type' header.
    ASPOSECPP_SHARED_API String get_ContentType();
    /// Sets a value of the 'Content-Type' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ContentType(String value);
    /// Returns the collection of the SOAP headers.
    /// @returns The collection of the SOAP headers.
    ASPOSECPP_SHARED_API System::SharedPtr<SoapHeaderCollection> get_Headers();
    /// Gets the processing stage of a SOAP message.
    /// @returns The processing stage of a SOAP message.
    ASPOSECPP_SHARED_API SoapMessageStage get_Stage();
    /// Gets the stream that contains the SOAP message data.
    /// @returns The stream that contains the SOAP message data.
    ASPOSECPP_SHARED_API System::SharedPtr<System::IO::Stream> get_Stream();
    /// Sets the stream that contains the SOAP message data.
    /// @param stream The stream that must be set.
    ASPOSECPP_SHARED_API void SetStream(System::SharedPtr<System::IO::Stream> stream);
    /// Returns the XML Web service URL.
    /// @returns The XML Web service URL.
    ASPOSECPP_SHARED_API virtual String get_Url() = 0;
    /// Gets a value of the 'Content-Encoding' header.
    /// @returns A value of the 'Content-Encoding' header.
    ASPOSECPP_SHARED_API String get_ContentEncoding();
    /// Sets a value of the 'Content-Encoding' header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ContentEncoding(String value);
    /// Returns a value that indicates if SOAP version 1.2 is used.
    /// @returns A value that indicates if SOAP version 1.2 is used.
    ASPOSECPP_SHARED_API bool get_IsSoap12();
    /// Returns the SOAP version that is used.
    /// @returns The SOAP version that is used.
    ASPOSECPP_SHARED_API virtual SoapProtocolVersion get_SoapVersion();
    /// Sets the stream that contains the SOAP message data.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_InternalStream(System::SharedPtr<System::IO::Stream> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API SoapMessage();

    /// Sets the processing stage of the SOAP message.
    /// @param stage The stage that must be set.
    ASPOSECPP_SHARED_API void SetStage(SoapMessageStage stage);
    /// Gets the input parameter value at the specified index.
    /// @param index The index of the input parameter.
    /// @returns The input parameter value.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetInParameterValue(int32_t index);
    /// Gets the output parameter value at the specified index.
    /// @param index The index of the output parameter.
    /// @returns The output parameter value.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetOutParameterValue(int32_t index);
    /// Gets the return value of the XML Web service method.
    /// @returns The return value of the XML Web service method.
    ASPOSECPP_SHARED_API System::SharedPtr<Object> GetReturnValue();
    /// Sets the collection of the SOAP headers.
    /// @param headers The collection of the SOAP headers to set.
    ASPOSECPP_SHARED_API void SetHeaders(System::SharedPtr<SoapHeaderCollection> headers);
    /// Sets the exception that is thrown by the XML Web service method.
    /// @param ex The exception that must be set.
    ASPOSECPP_SHARED_API void SetException(SoapException ex);
    /// Gets the exception that is thrown by the XML Web service method.
    /// @returns The exception that is thrown by the XML Web service method.
    ASPOSECPP_SHARED_API SoapException get_Exception();
    /// Sets the internal collection of the SOAP headers.
    /// @param target The object to get the SOAP headers from.
    /// @param headers A collection of headers from which the internal collection will be filled.
    /// @param direction The SOAP header direction.
    ASPOSECPP_SHARED_API void CollectHeaders(System::SharedPtr<Object> target,
                        System::ArrayPtr<System::SharedPtr<SoapHeaderMapping>> headers, SoapHeaderDirection direction);
    /// Updates the internal collection of the SOAP headers.
    /// @param target The object to get the SOAP headers from.
    /// @param headersInfo A collection of headers from which the internal collection will be updated.
    ASPOSECPP_SHARED_API void UpdateHeaderValues(System::SharedPtr<Object> target,
                            System::ArrayPtr<System::SharedPtr<SoapHeaderMapping>> headersInfo);
    /// Find the header mapping by specified header type.
    /// @param headersInfo The collection of the header mappings.
    /// @param headerType The header type to look for.
    /// @returns The header mapping.
    ASPOSECPP_SHARED_API System::SharedPtr<SoapHeaderMapping> FindHeader(System::ArrayPtr<System::SharedPtr<SoapHeaderMapping>> headersInfo,
                                                    const TypeInfo& headerType);

protected:
    /// Checks if the current stage contains input parameters.
    virtual void EnsureInStage() = 0;
    /// Checks if the current stage contains output parameters.
    virtual void EnsureOutStage() = 0;
    /// Checks if the current stage is equal to the specified one.
    /// @param stage The stage to compare.
    /// @throws System::InvalidOperationException When the current stage isn't equal to the specified one.
    void EnsureStage(SoapMessageStage stage);

private:
    /// A value of the 'Content-Type' header.
    String content_type;
    /// A value of the 'Content-Encoding' header.
    String content_encoding;
    /// The exception that is thrown by the XML Web service method.
    SoapException exception = nullptr;
    /// The collection of the SOAP headers.
    System::SharedPtr<SoapHeaderCollection> headers;
    /// The processing stage of the SOAP message.
    SoapMessageStage stage;
    /// The stream that contains the SOAP message data.
    System::SharedPtr<System::IO::Stream> stream;
    /// The parameters that are passed into the XML Web service method.
    System::ArrayPtr<System::SharedPtr<Object>> inParameters;
    /// The output parameters passed into the XML Web service method.
    System::ArrayPtr<System::SharedPtr<Object>> outParameters;
    /// The SOAP version.
    SoapProtocolVersion soapVersion;
};

}}}} // namespace System::Web::Services::Protocols
