/// @file system/reflection/method_info.h
#pragma once
#include <system/object.h>
#include <system/string.h>
#include <system/reflection/member_info.h>

namespace System { namespace Reflection {

/// Represents information on class method.
class ASPOSECPP_SHARED_CLASS MethodInfo : public MemberInfo
{
public:
    /// Initializes a new instance of the MethodInfo class.
    /// @param name Method name.
    ASPOSECPP_SHARED_API MethodInfo(const String& name);

    /// Gets a MemberTypes value indicating that this member is a method.
    ASPOSECPP_SHARED_API virtual MemberTypes get_MemberType() const override;

};

}}
