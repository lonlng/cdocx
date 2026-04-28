#pragma once

#include <system/reflection/member_info.h>

namespace System { namespace Reflection {

/// Discovers the attributes of a field and provides access to field metadata.
class ASPOSECPP_SHARED_CLASS FieldInfo : public MemberInfo
{
public:
    /// Gets a value indicating whether the field is static.
    /// @return true if this field is static; otherwise, false.
    ASPOSECPP_SHARED_API bool get_IsStatic();
    /// Gets property value from specific object.
    /// @param obj Object to read property from.
    /// @return Value of specified property for specified object.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Object> GetValue(const System::SharedPtr<System::Object>& obj);
    /// Sets property value to specific object.
    /// @param obj Object to write property to.
    /// @param value Value of property to set.
    ASPOSECPP_SHARED_API void SetValue(const System::SharedPtr<System::Object>& obj, const System::SharedPtr<System::Object>& value);
    /// Gets property type.
    /// @return Type of the field.
    ASPOSECPP_SHARED_API TypeInfo get_FieldType();
};


}
}
