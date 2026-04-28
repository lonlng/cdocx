/// @file net/web/services/protocol/soap_document_method_attribute.h
#pragma once
#include <system/attribute.h>

#include <net/web/services/description/soap_format_extensions.h>
#include <net/web/services/protocol/soap_parameter_style.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Specifies that all SOAP messages passed or returned from the method use the Document formatting.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SoapDocumentMethodAttribute final : public System::Attribute
{
    /// This type.
    typedef SoapDocumentMethodAttribute ThisType;
    /// Parent type.
    typedef System::Attribute BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a value of the 'SOAPAction' attribute.
    /// @returns A value of the 'SOAPAction' attribute.
    ASPOSECPP_SHARED_API String get_Action();
    /// Sets a value of the 'SOAPAction' attribute.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Action(String value);
    /// Gets the binding for which an XML web service method is implementing an operation.
    /// @returns The binding for which an XML web service method is implementing an operation.
    ASPOSECPP_SHARED_API String get_Binding();
    /// Sets the binding for which an XML web service method is implementing an operation.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Binding(String value);
    /// Gets a value that indicates if a client doesn't wait for a server to finish processing a method.
    /// @returns A value that indicates if a client doesn't wait for a server to finish processing a method.
    ASPOSECPP_SHARED_API bool get_OneWay();
    /// Sets a value that indicates if the client doesn't wait for the server to finish processing a method.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_OneWay(bool value);
    /// Gets a value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    /// element.
    /// @returns A value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    // element.
    ASPOSECPP_SHARED_API SoapParameterStyle get_ParameterStyle();
    /// Sets a value that indicates if parameters are encapsulated within a single XML element beneath the 'Body'
    /// element.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ParameterStyle(SoapParameterStyle value);
    /// Gets the name of the XML element associated with the SOAP request, which is defined in a service description as
    /// an operation.
    /// @returns The name of the XML element associated with the SOAP request, which is defined in a service description
    /// as an operation.
    ASPOSECPP_SHARED_API String get_RequestElementName();
    /// Sets the name of the XML element associated with the SOAP request, which is defined in a service description as
    /// an operation.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_RequestElementName(String value);
    /// Gets the namespace associated with the SOAP request.
    /// @returns The namespace associated with the SOAP request.
    ASPOSECPP_SHARED_API String get_RequestNamespace();
    /// Sets the namespace associated with the SOAP request.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_RequestNamespace(String value);
    /// Gets the name of the XML element associated with the SOAP response.
    /// @returns The name of the XML element associated with the SOAP response.
    ASPOSECPP_SHARED_API String get_ResponseElementName();
    /// Sets the name of the XML element associated with the SOAP response.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ResponseElementName(String value);
    /// Gets the namespace associated with the SOAP response.
    /// @returns The namespace associated with the SOAP response.
    ASPOSECPP_SHARED_API String get_ResponseNamespace();
    /// Sets the namespace associated with the SOAP response.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ResponseNamespace(String value);
    /// Gets a value that determines the message encoding method.
    /// @returns A value that determines the message encoding method.
    ASPOSECPP_SHARED_API Description::SoapBindingUse get_Use();
    /// Sets a value that determines the message encoding method.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Use(Description::SoapBindingUse value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API SoapDocumentMethodAttribute();
    /// Constructs a new instance.
    /// @param action A value of the 'SOAPAction' attribute.
    ASPOSECPP_SHARED_API SoapDocumentMethodAttribute(String action);

private:
    /// A value of the 'SOAPAction' attribute.
    String action;
    /// The binding for which an XML web service method is implementing an operation.
    String binding;
    /// A value that indicates if a client doesn't wait for a server to finish processing a method.
    bool oneWay;
    /// A value that indicates if parameters are encapsulated within a single XML element beneath the 'Body' element.
    SoapParameterStyle parameterStyle;
    /// The name of the XML element associated with the SOAP request which is defined in a service description as an
    /// operation.
    String requestElementName;
    /// The namespace associated with the SOAP request.
    String requestNamespace;
    /// The name of the XML element associated with the SOAP response.
    String responseElementName;
    /// The namespace associated with the SOAP response.
    String responseNamespace;
    /// A value that determines the message encoding method.
    Description::SoapBindingUse use;
};

}}}} // namespace System::Web::Services::Protocols
