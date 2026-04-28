/// @file net/web/services/web_service_attribute.h
#pragma once
#include <system/attribute.h>
#include <system/string.h>

namespace System { namespace Web { namespace Services {

/// Adds additional information to the XML Web service.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class WebServiceAttribute final : public System::Attribute
{
    /// This type.
    typedef WebServiceAttribute ThisType;
    /// Parent type.
    typedef System::Attribute BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// The default value of the 'Namespace' property.
    static const String DefaultNamespace;

    /// Gets a message that contains the XML Web service description.
    /// @returns A message that contains the XML Web service description.
    String get_Description();
    /// Sets a message that contains the XML Web service description.
    /// @param value The value that must be set.
    void set_Description(String value);
    /// Gets the XML Web service's name.
    /// @returns The XML Web service's name.
    String get_Name();
    /// Sets the XML Web service's name.
    /// @param value The value that must be set.
    void set_Name(String value);
    /// Gets the default namespace to use for the XML Web service.
    /// @returns The default namespace to use for the XML Web service.
    String get_Namespace();
    /// Sets the default namespace to use for the XML Web service.
    /// @param value The value that must be set.
    void set_Namespace(String value);

    /// Constructs a new instance.
    WebServiceAttribute();

private:
    /// A message that contains the XML Web service description.
    String description;
    /// The XML Web service's name.
    String name;
    /// The default namespace to use for the XML Web service.
    String ns;
};
}}} // namespace System::Web::Services
