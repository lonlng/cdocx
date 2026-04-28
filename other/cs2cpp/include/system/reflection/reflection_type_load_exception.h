/// @file system/reflection/reflection_type_load_exception.h

#pragma once

#include "system/array.h"
#include "system/smart_ptr.h"
#include "system/exceptions.h"

namespace System { namespace Reflection {

/// ReflectionTypeLoadException is thrown by the Module.GetTypes method if any of the classes in a module fail to load.
/// Never create instances of this class manually. Use the ReflectionTypeLoadException class instead.
/// Never wrap the ReflectionTypeLoadException class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_ReflectionTypeLoadException : public System::Details_Exception
{
    friend class System::ExceptionWrapperHelper;
    template <typename T>
    friend class System::ExceptionWrapper;
    RTTI_INFO_NAMESPACE(Details_ReflectionTypeLoadException, System::BaseTypesInfo<System::Details_Exception>)
public:
    /// Returns the type information of the causes of the exception.
    /// @returns An array of type information.
    virtual System::ArrayPtr<System::TypeInfo> get_Types() const;
    /// Returns the exceptions causing this exception.
    /// @returns An array of exceptions.
    virtual System::ArrayPtr<System::Exception> get_LoaderExceptions() const;

protected:
    using BaseType = System::Details_Exception;
    /// Initializes a new instance of the Details_ReflectionTypeLoadException class with a default error message
    /// and an arrays of type infos and exceptions that are the cause of this exception.
    /// @param types The type infos of the cause of the exceptions.
    /// @param exceptions The exceptions that are the cause of the current exception.
    ASPOSECPP_SHARED_API Details_ReflectionTypeLoadException(
        const System::ArrayPtr<TypeInfo>& types,
        const System::ArrayPtr<System::Exception>& exceptions);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_ReflectionTypeLoadException,
        CODEPORTING_ARGS(const System::ArrayPtr<TypeInfo>& types, const System::ArrayPtr<System::Exception>& exceptions),
        CODEPORTING_ARGS(types, exceptions)
    );
    /// Initializes a new instance of the Details_ReflectionTypeLoadException class with an error message
    /// and an arrays of type infos and exceptions that are the cause of this exception.
    /// @param types The type infos of the cause of the exceptions.
    /// @param exceptions The exceptions that are the cause of the current exception.
    /// @param message The exception message information.
    ASPOSECPP_SHARED_API Details_ReflectionTypeLoadException(
        const System::ArrayPtr<TypeInfo>& types, 
        const System::ArrayPtr<System::Exception>& exceptions, 
        const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_ReflectionTypeLoadException,
        CODEPORTING_ARGS(const System::ArrayPtr<TypeInfo>& types, const System::ArrayPtr<System::Exception>& exceptions, const String& message),
        CODEPORTING_ARGS(types, exceptions, message)
    );
    /// Initializes a new instance of the Details_ReflectionTypeLoadException class from the
    /// serialization information captured at the streaming context.
    /// @param info The serialization information.
    /// @param context The streaming context.
    ASPOSECPP_SHARED_API Details_ReflectionTypeLoadException(
        const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info,
        System::Runtime::Serialization::StreamingContext context);
    MEMBER_FUNCTION_MAKE_OBJECT(
        Details_ReflectionTypeLoadException,
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context),
        CODEPORTING_ARGS(info, context)
    );
    /// @see System::Exception::DoThrow
    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

private:
    /// Type informations of the cause of the exceptions.
    System::ArrayPtr<System::TypeInfo> m_types;
    /// Exceptions themselves.
    System::ArrayPtr<System::Exception> m_exceptions;
    /// Default message content
    static const String s_default_message;
    /// Selects the default message if the message argument is null.
    /// @param message The message argument.
    /// @returns A default message is returned if the message argument is null, otherwise the message argument is returned.
    static const String& DefaultMessageIfNull(const String& message);
};

/// ReflectionTypeLoadException is thrown by the Module.GetTypes method if any of the classes in a module fail to load.
/// Never wrap the ReflectionTypeLoadException class instances into System::SmartPtr.
using ReflectionTypeLoadException = System::ExceptionWrapper<Details_ReflectionTypeLoadException>;
}} // namespace System::Reflection
