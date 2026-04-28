/// @file net/web/services/protocol/soap_service_routing_style.h
#pragma once
namespace System { namespace Web { namespace Services { namespace Protocols {

/// Enumerates options of how a SOAP message is routed to the XML Web service.
enum class SoapServiceRoutingStyle
{
    /// The SOAP message is routed on the basis of the 'SOAPAction' attribute.
    SoapAction = 0x0,
    /// The SOAP message is routed on the basis of the first child element after the 'Body' element.
    RequestElement = 0x1
};
}}}} // namespace System::Web::Services::Protocols
