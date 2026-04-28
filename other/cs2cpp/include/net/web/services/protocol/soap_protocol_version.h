/// @file net/web/services/protocol/soap_protocol_version.h
#pragma once
namespace System { namespace Web { namespace Services { namespace Protocols {

/// Enumerates the versions of SOAP.
enum class SoapProtocolVersion
{
    /// The default value.
    Default,
    /// SOAP version 1.1.
    Soap11,
    /// SOAP version 1.2.
    Soap12
};
}}}} // namespace System::Web::Services::Protocols
