/// @file net/web/services/protocol/soap_header_attribute.h
#pragma once
#include <system/attribute.h>
#include <system/enum_helpers.h>
#include <system/string.h>

#include <net/web/services/protocol/soap_header_direction.h>

namespace System { namespace Web { namespace Services { namespace Protocols {

/// Specifies the SOAP header that the XML Web service method or the XML Web service client can process.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SoapHeaderAttribute final : public System::Attribute
{
    /// This type.
    typedef SoapHeaderAttribute ThisType;
    /// Parent type.
    typedef System::Attribute BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the SOAP header direction.
    /// @returns The SOAP header direction.
    ASPOSECPP_SHARED_API SoapHeaderDirection get_Direction();
    /// Sets the SOAP header direction.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Direction(SoapHeaderDirection value);
    /// Gets a member variable name of the XML SOAP service that is used to receive the SOAP header contents.
    /// @returns A member variable name of the XML SOAP service that is used to receive the SOAP header contents.
    ASPOSECPP_SHARED_API String get_MemberName();
    /// Sets a member variable name of the XML SOAP service that is used to receive the SOAP header contents.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MemberName(String value);
    /// Gets a value that indicates if the SOAP header must be understood and processed by the recipient XML Web service
    /// or XML Web service client.
    /// @returns A value that indicates if the SOAP header must be understood and processed by the recipient XML Web
    /// service or XML Web service client.
    /// @deprecated
    [[deprecated]] ASPOSECPP_SHARED_API bool get_Required();
    /// Sets a value that indicates if the SOAP header must be understood and processed by the recipient XML Web service
    /// or XML Web service client.
    /// @param value The value that must be set.
    /// @deprecated
    [[deprecated]] ASPOSECPP_SHARED_API void set_Required(bool value);

    /// Constructs a new instance.
    /// @param memberName A member variable name of the XML SOAP service that is used to receive the SOAP header
    /// contents.
    ASPOSECPP_SHARED_API SoapHeaderAttribute(String memberName);

private:
    /// The SOAP header direction.
    SoapHeaderDirection direction;
    /// A member variable name of the XML SOAP service that is used to receive the SOAP header contents.
    String memberName;
    /// A value that indicates if the SOAP header must be understood and processed by the recipient XML Web service or
    /// XML Web service client.
    bool required;
};

}}}} // namespace System::Web::Services::Protocols
