/// @file drawing/known_color.h
#pragma once

#include <system/component_model/type_converter.h>

namespace System { namespace Drawing {

/// Converts ImageFormat objects from one data type to another.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ImageFormatConverter : public ComponentModel::TypeConverter
{
    typedef ImageFormatConverter ThisType;
    typedef System::ComponentModel::TypeConverter BaseType;

    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    using ComponentModel::TypeConverter::ConvertFrom;
    using ComponentModel::TypeConverter::ConvertTo;

    /// Constructs a new instance of ImageFormatConverter.
    ASPOSECPP_SHARED_API ImageFormatConverter();

    /// Converts objects.
    /// @param context Object conversion context information.
    /// @param culture Culture to use when converting objects.
    /// @param value Object to convert.
    /// @return converted object.
    ASPOSECPP_SHARED_API SharedPtr<Object> ConvertFrom(
        const SharedPtr<ComponentModel::ITypeDescriptorContext>& context,
        const SharedPtr<Globalization::CultureInfo>& culture,
        const SharedPtr<Object>& value) override;

    /// Converts object to specific type.
    /// @param context Object conversion context information.
    /// @param culture Culture to use when converting objects.
    /// @param value Object to convert.
    /// @param destinationType Type to convert to.
    /// @return Converted object.
    ASPOSECPP_SHARED_API SharedPtr<Object> ConvertTo(
        const SharedPtr<ComponentModel::ITypeDescriptorContext>& context,
        const SharedPtr<Globalization::CultureInfo>& culture,
        const SharedPtr<Object>& value,
        const TypeInfo& destinationType) override;
};

}} // namespace System::Drawing
