/// @file net/web/services/web_service_binding_attribute.h
#pragma once
#include <system/attribute.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Web { namespace Services {

class WsiProfiles;

/// Used to declare a binding that defines one or more methods of the XML Web service.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS WebServiceBindingAttribute final : public System::Attribute
{
    /// This type.
    typedef WebServiceBindingAttribute ThisType;
    /// Parent type.
    typedef System::Attribute BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the location where the binding is defined.
    /// @returns The location where the binding is defined.
    ASPOSECPP_SHARED_API String get_Location();
    /// Sets the location where the binding is defined.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Location(String value);
    /// Gets the binding's name.
    /// @returns The binding's name.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the binding's name.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Name(String value);
    /// Gets the namespace that is associated with the binding.
    /// @returns The namespace that is associated with the binding.
    ASPOSECPP_SHARED_API String get_Namespace();
    /// Sets the namespace that is associated with the binding.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Namespace(String value);
    /// Gets a value that indicates if the binding emits conformance claims.
    /// @returns A value that indicates if the binding emits conformance claims.
    ASPOSECPP_SHARED_API bool get_EmitConformanceClaims();
    /// Sets a value that indicates if the binding emits conformance claims.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_EmitConformanceClaims(bool value);
    /// Gets the WSI specification.
    /// @returns The WSI specification.
    ASPOSECPP_SHARED_API System::SharedPtr<WsiProfiles> get_ConformsTo();
    /// Sets the WSI specification.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_ConformsTo(System::SharedPtr<WsiProfiles> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API WebServiceBindingAttribute();
    /// Constructs a new instance.
    /// @param name The binding's name.
    ASPOSECPP_SHARED_API WebServiceBindingAttribute(String name);
    /// Constructs a new instance.
    /// @param name The binding's name.
    /// @param ns The namespace that is associated with the binding.
    ASPOSECPP_SHARED_API WebServiceBindingAttribute(String name, String ns);
    /// Constructs a new instance.
    /// @param name The binding's name.
    /// @param ns The namespace that is associated with the binding.
    /// @param location The location where the binding is defined.
    ASPOSECPP_SHARED_API WebServiceBindingAttribute(String name, String ns, String location);

private:
    /// The location where the binding is defined.
    String location;
    /// The binding's name.
    String name;
    /// The namespace that is associated with the binding.
    String ns;
    /// A value that indicates if the binding emits conformance claims.
    bool emitConformanceClaims;
    /// The WSI specification.
    System::SharedPtr<WsiProfiles> conformsTo;
};

}}} // namespace System::Web::Services
