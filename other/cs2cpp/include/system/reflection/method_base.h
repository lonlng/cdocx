/// @file system/reflection/method_base.h
#ifndef _aspose_system_reflection_method_base_h_
#define _aspose_system_reflection_method_base_h_

#include "system/shared_ptr.h"
#include "system/reflection/member_info.h"

namespace System { namespace Diagnostics { namespace _StackFrame_private {
class Pimpl;
} } }

namespace System { namespace Reflection {

/// Base information on method.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS MethodBase : public MemberInfo
{
    friend class System::Diagnostics::_StackFrame_private::Pimpl;
protected:
    /// Constructor.
    /// @param full_name Method full name.
    ASPOSECPP_SHARED_API MethodBase(const String& full_name);

public:
    MEMBER_FUNCTION_MAKE_OBJECT(MethodBase, CODEPORTING_ARGS(const String& full_name), CODEPORTING_ARGS(full_name));
    /// Initializes a new instance of the MethodBase class.
    ASPOSECPP_SHARED_API MethodBase();
    /// Indicating the type of the member - method, constructor, event, and so on.
    ASPOSECPP_SHARED_API virtual MemberTypes get_MemberType() const override;

    /// This method allows getting current method name.
    /// Translator substitutes ASPOSE_CURRENT_FUNCTION as parameter automatically. 
    static ASPOSECPP_SHARED_API System::SharedPtr<MemberInfo> GetCurrentMethod(const String& full_name);
};

}}

#endif
