/// @file system/component_model/win_32_exception.h

#pragma once

#include "system/details_exception_with_error_code.h"

namespace System { namespace ComponentModel {

/// Throws an exception for a Win32 error code.
/// Never create instances of this class manually. Use the Win32Exception class instead.
/// Never wrap the Win32Exception class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_Win32Exception : public Details_ExceptionWithErrorCode<Details_SystemException>
{
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;
    using BaseType = Details_ExceptionWithErrorCode<Details_SystemException>;
    RTTI_INFO_NAMED(System::ComponentModel::Details_Win32Exception, "System::ComponentModel::Win32Exception",
                    System::BaseTypesInfo<System::Object>);
    /// The Win32 error code.
    int32_t m_nativeErrorCode;

protected:
    /// Initializes a new instance of the Win32Exception class with the last Win32 error that occurred.
    ASPOSECPP_SHARED_API Details_Win32Exception();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Win32Exception, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Initializes a new instance of the Win32Exception class with the specified error.
    /// @param error The Win32 error code associated with this exception.
    ASPOSECPP_SHARED_API Details_Win32Exception(int32_t error);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Win32Exception, CODEPORTING_ARGS(int32_t error), CODEPORTING_ARGS(error));
    /// Initializes a new instance of the Win32Exception class with the specified detailed description.
    /// @param message A detailed description of the error.
    ASPOSECPP_SHARED_API Details_Win32Exception(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Win32Exception, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
    /// Initializes a new instance of the Win32Exception class with the specified error and the specified detailed
    /// description.
    /// @param error The Win32 error code associated with this exception.
    /// @param message A detailed description of the error.
    ASPOSECPP_SHARED_API Details_Win32Exception(int32_t error, const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Win32Exception, CODEPORTING_ARGS(int32_t error, const String& message), CODEPORTING_ARGS(error, message));
    /// Initializes a new instance of the Win32Exception class with the specified detailed description and
    /// the specified exception.
    /// @param message A detailed description of the error.
    /// @param innerException A reference to the inner exception that is the cause of this exception.
    ASPOSECPP_SHARED_API Details_Win32Exception(const String& message, const System::Exception& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Win32Exception, CODEPORTING_ARGS(const String& message, const System::Exception& innerException), CODEPORTING_ARGS(message, innerException));
    /// @see Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;
    /// @see System::Exception::ExtraDescription
    virtual ASPOSECPP_SHARED_API String ExtraDescription() const override;

public:
    /// Gets the Win32 error code associated with this exception.
    virtual ASPOSECPP_SHARED_API int32_t get_NativeErrorCode() const;
};

using Win32Exception = System::ExceptionWrapper<Details_Win32Exception>;

}} // namespace System::ComponentModel
