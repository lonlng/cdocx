/// @file net/web/services/protocol/soap_parameter_style.h
#pragma once

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Enumerates the parameters formats in a SOAP message.
enum class SoapParameterStyle
{
    /// If 'SoapDocumentServiceAttribute' is not applied to the class, then the default value is 'Wrapped'.
    Default,
    /// The parameters are placed in XML elements that follow the 'Body' element.
    Bare,
    /// The parameters are encapsulated within a single XML element that follows the 'Body' element.
    Wrapped
};
}}}} // namespace System::Web::Services::Protocols
