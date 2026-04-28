/// @file net/web/services/protocol/soap_document_service_attribute.h
#pragma once
#include <system/attribute.h>

#include <net/web/services/description/soap_format_extensions.h>
#include <net/web/services/protocol/soap_parameter_style.h>
#include <net/web/services/protocol/soap_service_routing_style.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Sets the default format for the SOAP requests and responses.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class SoapDocumentServiceAttribute final : public System::Attribute
{
    /// This type.
    typedef SoapDocumentServiceAttribute ThisType;
    /// Parent type.
    typedef System::Attribute BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    /// element.
    /// @returns A value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    // element.
    SoapParameterStyle get_ParameterStyle();
    /// Sets a value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    /// element.
    /// @param value The value that must be set.
    void set_ParameterStyle(SoapParameterStyle value);
    /// Gets a value that shows how the SOAP messages are routed to the service.
    /// @returns A value that shows how the SOAP messages are routed to the service.
    SoapServiceRoutingStyle get_RoutingStyle();
    /// Sets a value that shows how the SOAP messages are routed to the service.
    /// @param value The value that must be set.
    void set_RoutingStyle(SoapServiceRoutingStyle value);
    /// Gets the parameter formatting.
    /// @returns The parameter formatting.
    Description::SoapBindingUse get_Use();
    /// Sets the parameter formatting.
    /// @param value The value that must be set.
    void set_Use(Description::SoapBindingUse value);

    /// Constructs a new instance.
    SoapDocumentServiceAttribute();
    /// Constructs a new instance.
    /// @param use The parameter formatting.
    SoapDocumentServiceAttribute(Description::SoapBindingUse use);
    /// Constructs a new instance.
    /// @param use The parameter formatting.
    /// @param paramStyle A value that indicates if parameters are encapsulated within a single XML element beneath the
    /// 'Body' element.
    SoapDocumentServiceAttribute(Description::SoapBindingUse use, SoapParameterStyle paramStyle);

private:
    /// A value that indicates if parameters are encapsulated within a single XML element beneath the 'Body' element.
    SoapParameterStyle paramStyle;
    /// A value that shows how the SOAP messages are routed to the service.
    SoapServiceRoutingStyle routingStyle;
    /// The parameter formatting.
    Description::SoapBindingUse use;
};

}}}} // namespace System::Web::Services::Protocols
