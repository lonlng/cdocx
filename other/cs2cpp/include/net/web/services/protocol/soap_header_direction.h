/// @file net/web/services/protocol/soap_header_direction.h
#pragma once
#include <system/enum_helpers.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Enumerates the SOAP header directions.
enum class SoapHeaderDirection
{
    /// The SOAP header recipient is the XML Web service.
    In = 0x1,
    /// The SOAP header recipients are both the XML Web service and the XML Web service client.
    InOut = 0x3,
    /// The SOAP header recipient is the XML Web service client.
    Out = 0x2,
    /// The SOAP header is sent to the XML Web service client when an exception is thrown by the XML Web service method.
    Fault = 0x4
};

/// @cond
/// Declaration of template arithmetic operators for values of the SoapHeaderDirection enum type.
DECLARE_ENUM_OPERATORS(System::Web::Services::Protocols::SoapHeaderDirection);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // namespace System::Web::Services::Protocols

/// Inserts using declarations for arithmetic operators declared in namespace System::Web::Services::Protocols.
DECLARE_USING_ENUM_OPERATORS(System::Web::Services::Protocols);
