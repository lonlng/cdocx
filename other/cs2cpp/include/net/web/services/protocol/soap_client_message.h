/// @file net/web/services/protocol/soap_client_message.h
#pragma once
#include <system/object.h>
#include <system/shared_ptr.h>

#include "soap_message.h"

namespace System { namespace Web { namespace Services { namespace Protocols {

class SoapHttpClientProtocol;
class SoapClientMethod;
class SoapMethodStubInfo;

/// Represents the data in a SOAP request sent or a SOAP response received.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SoapClientMessage final : public System::Web::Services::Protocols::SoapMessage
{
    /// This type.
    typedef SoapClientMessage ThisType;
    /// Parent type.
    typedef System::Web::Services::Protocols::SoapMessage BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    RTTI_INFO_DECL();

public:
    /// Method stub information.
    System::SharedPtr<SoapMethodStubInfo> MethodStubInfo;
    /// A collection of parameters.
    System::ArrayPtr<System::SharedPtr<Object>> Parameters;

    /// @copydoc System::Web::Services::Protocols::SoapMessage::get_Action
    ASPOSECPP_SHARED_API String get_Action() override;
    /// Returns an instance of the client proxy class.
    /// @returns An instance of the client proxy class.
    ASPOSECPP_SHARED_API System::SharedPtr<SoapHttpClientProtocol> get_Client();
    /// Returns a value that indicates if a client doesn't wait for a server to finish processing a method.
    /// @returns A value that indicates if a client doesn't wait for a server to finish processing a method.
    ASPOSECPP_SHARED_API virtual bool get_OneWay();
    /// @copydoc System::Web::Services::Protocols::SoapMessage::get_Url
    ASPOSECPP_SHARED_API String get_Url() override;

    /// @copydoc System::Web::Services::Protocols::SoapMessage::get_SoapVersion
    ASPOSECPP_SHARED_API SoapProtocolVersion get_SoapVersion() override;
    /// Constructs a new instance.
    /// @param client An instance of the client proxy class.
    /// @param msi Method stub information.
    /// @param url The URL of an XML web service.
    /// @param parameters A collection of parameters.
    ASPOSECPP_SHARED_API SoapClientMessage(System::SharedPtr<SoapHttpClientProtocol> client, System::SharedPtr<SoapMethodStubInfo> msi,
                      String url, System::ArrayPtr<System::SharedPtr<Object>> parameters);

protected:
    /// @copydoc System::Web::Services::Protocols::SoapMessage::EnsureInStage
    void EnsureInStage() override;
    /// @copydoc System::Web::Services::Protocols::SoapMessage::EnsureOutStage
    void EnsureOutStage() override;

private:
    /// An instance of the client proxy class.
    System::SharedPtr<SoapHttpClientProtocol> client;
    /// The URL of an XML web service.
    String url;
};

}}}} // namespace System::Web::Services::Protocols
