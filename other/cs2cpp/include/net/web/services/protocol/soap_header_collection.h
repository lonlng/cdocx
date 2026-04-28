/// @file net/web/services/protocol/soap_header_collection.h
#pragma once
#include <cstdint>
#include <system/array.h>
#include <system/collections/list.h>
#include <system/shared_ptr.h>

#include <net/web/services/protocol/soap_header.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Contains a collection of instances of the SoapHeader class.
class ASPOSECPP_SHARED_CLASS SoapHeaderCollection : public System::Collections::Generic::List<System::SharedPtr<SoapHeader>>
{
public:
    /// Initializes a new instance of the SoapHeaderCollection class.
    ASPOSECPP_SHARED_API SoapHeaderCollection();
};

}}}} // namespace System::Web::Services::Protocols
