/// @file system/reflection/target_invocation_exception.h

#pragma once

#include "system/exceptions.h"

namespace System { namespace Reflection {

/// TargetInvocationException is thrown by methods invoked through reflection.
/// Never create instances of this class manually. Use the TargetInvocationException class instead.
/// Never wrap the TargetInvocationException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_TargetInvocationException : public System::Details_ApplicationException
{
    friend class System::ExceptionWrapperHelper;
    template <typename T>
    friend class System::ExceptionWrapper;
    RTTI_INFO_NAMESPACE(Details_TargetInvocationException, System::BaseTypesInfo<System::Details_ApplicationException>)
protected:
    using BaseType = System::Details_ApplicationException;
    /// Initializes a new instance of the Details_TargetInvocationException class.
    ASPOSECPP_SHARED_API Details_TargetInvocationException();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_TargetInvocationException, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// Initializes a new instance of the Details_TargetInvocationException class with a specified error message.
    /// @param message The message that describes the error.
    ASPOSECPP_SHARED_API Details_TargetInvocationException(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_TargetInvocationException, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));
    /// Initializes a new instance of the Details_TargetInvocationException class with error message
    /// and an inner exception that is the cause of this exception.
    /// @param message The message describing the exception.
    /// @param innerException The exception that is the cause of the current exception. If the inner parameter is not
    /// null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_TargetInvocationException(
        const String& message,
        const System::ExceptionWrapper<System::Details_Exception>& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_TargetInvocationException,
        CODEPORTING_ARGS(const String& message, const System::ExceptionWrapper<System::Details_Exception>& innerException),
        CODEPORTING_ARGS(message, innerException)
    );
    /// Initializes a new instance of the Details_TargetInvocationException class with default error message
    /// and an inner exception that is the cause of this exception.
    /// @param innerException The exception that is the cause of the current exception. If the inner parameter is not
    /// null, the current exception is raised in a catch block that handles the inner exception.
    ASPOSECPP_SHARED_API Details_TargetInvocationException(const System::ExceptionWrapper<System::Details_Exception>& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_TargetInvocationException,
        CODEPORTING_ARGS(const System::ExceptionWrapper<System::Details_Exception>& innerException),
        CODEPORTING_ARGS(innerException)
    );
    /// Initializes a new instance of the Details_TargetInvocationException class from the
    /// serialization information captured at the streaming context.
    /// @param info The serialization information.
    /// @param context The streaming context.
    ASPOSECPP_SHARED_API Details_TargetInvocationException(
        const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info,
        System::Runtime::Serialization::StreamingContext context);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_TargetInvocationException,
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context),
        CODEPORTING_ARGS(info, context));
    /// @see System::Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

private:
    /// Default message content
    static const String s_default_message;
    /// Selects the default message if the message argument is null.
    /// @param message The message argument.
    /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
    static const String& DefaultMessageIfNull(const String& message);
};

/// TargetInvocationException is thrown by methods invoked through reflection.
/// Never wrap the TargetInvocationException class instances into System::SmartPtr.
using TargetInvocationException = System::ExceptionWrapper<Details_TargetInvocationException>;
}} // namespace System::Reflection
