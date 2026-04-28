/// @file net/web/services/protocol/soap_message_stage.h
#pragma once

#include <system/enum_helpers.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Enumerates the processing stages of the SOAP messages.
enum class SoapMessageStage
{
    /// The stage that is after deserialization.
    AfterDeserialize = 0x8,
    /// The stage that is after serialization.
    AfterSerialize = 0x2,
    /// The stage that is prior to deserialization.
    BeforeDeserialize = 0x4,
    /// The stage that is prior to serialization.
    BeforeSerialize = 0x1
};

/// @cond
/// Declaration of template arithmetic operators for values of the SoapMessageStage enum type.
DECLARE_ENUM_OPERATORS(System::Web::Services::Protocols::SoapMessageStage);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}}} // namespace System::Web::Services::Protocols

/// Inserts using declarations for arithmetic operators declared in namespace System::Web::Services::Protocols.
DECLARE_USING_ENUM_OPERATORS(System::Web::Services::Protocols);
