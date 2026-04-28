#pragma once

#include "system/reflection/method_base.h"
#include "system/type_info_ext.h"

namespace System {
namespace Reflection {

///  Provides access to constructor metadata.
class ASPOSECPP_SHARED_CLASS ConstructorInfo : public MethodBase
{
public:
    /// Initializes a new instance of the ConstructorInfo class for constructor without parameters
    /// @param full_name name of the constructor
    /// @param default_constructor function pointer to the constructor
    ASPOSECPP_SHARED_API ConstructorInfo(const String & full_name, std::function<System::Object::ptr()> default_constructor);
    /// Gets the class that declares this member.
    /// NOT IMPLEMENTED.
    /// @throws NotImplementedException Always
    ASPOSECPP_SHARED_API TypeInfo get_DeclaringType();
    /// Gets a MemberTypes value indicating that this member is a constructor.
    ASPOSECPP_SHARED_API virtual MemberTypes get_MemberType() const override;
    /// Invokes the method or constructor represented by the current instance, using the specified parameters.
    /// @param parameters specified parameters (not supported)
    ASPOSECPP_SHARED_API System::SharedPtr<System::Object> Invoke(const System::ArrayPtr<System::SharedPtr<System::Object>>& parameters);

protected:
    std::function<System::Object::ptr()> m_default_constructor;

private:

};

}
}
