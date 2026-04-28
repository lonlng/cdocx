/// @file system/exception.h
/// Contains the declaration of System::Exception class.
#ifndef _aspose_system_exception_h_
#define _aspose_system_exception_h_

#include <system/details/is_forwarding_of.h>
#include <system/object.h>
#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/runtime/serialization/streaming_context.h>
#include <exception>
#include <type_traits>
#include <cstdint>
#include <memory>

namespace System
{
namespace Runtime { namespace Serialization {
class SerializationInfo;
}}

class Details_Exception;

/// Type alias used by exception wrappers
using ExceptionPtr = System::SmartPtr<Details_Exception>;

template<class T>
class ExceptionWrapper;

/// @cond
/// Utility class to workaround gcc compile time error, that
/// prevents to see private BaseType aslias even when ExceptionWrapper
/// is declared as a friend class of Exception
class ExceptionWrapperHelper
{
    template<class T> friend class System::ExceptionWrapper;

    template <class T>
    class BaseTypeProvider
    {
    public:
        static typename T::BaseType Dummy;
        using BaseType = decltype(ExceptionWrapperHelper::BaseTypeProvider<T>::Dummy);
    };
};
/// @endcond

/// @cond
/// Base exception class that implements logic for correct exception handling
/// Contains smart pointer to exception instance
class ASPOSECPP_SHARED_CLASS ExceptionWrapperBase : public ExceptionWrapperType, public std::exception
{
public:
    /// Constructs a null-instance of ExceptionWrapper that does not represent any exception.
    ASPOSECPP_SHARED_API ExceptionWrapperBase(std::nullptr_t);

    /// Constructs a instance of ExceptionWrapper class that contains.
    /// @param ptr Smart pointer to the instance of Exception class.
    ASPOSECPP_SHARED_API ExceptionWrapperBase(const ExceptionPtr& ptr);

    /// Calls the exception what() implementation.
    /// @returns The description of the exception.
    virtual ASPOSECPP_SHARED_API const char* what() const noexcept override;

    /// Returns smart pointer to the instance of Exception class that wrapper contains.
    /// @returns ptr Smart pointer to the instance of Exception class.
    ExceptionPtr Get() const { return m_ptr; }

    /// Determines if the current Exception object is a null-object i.e. does not represent any exception.
    /// @returns True if the current Exception object is a null-object, otherwise - false
    ASPOSECPP_SHARED_API bool IsNull() const;

    /// Determines if the current and the specified Exception objects are equal.
    /// @param e The Exception object to compare the current object with
    /// @returns True if the currnent and the specified objects are the same object or both represent the same exception or both do not represent any exceptions (are null-objects), otherwise - false 
    ASPOSECPP_SHARED_API bool operator == (const ExceptionWrapperBase &e) const;

    /// Determines if the current Exception object is a null-object i.e. does not represent any exception.
    /// @returns True if the current Exception object is a null-object, otherwise - false
    ASPOSECPP_SHARED_API bool operator == (const std::nullptr_t) const;

    /// Determines if the current Exception object is not a null-object i.e. represents an exception.
    /// @returns True if the current Exception object is not a null-object, otherwise - false
    ASPOSECPP_SHARED_API bool operator != (const std::nullptr_t) const;

    /// Determines if the current and the specified Exception objects are equal.
    /// @param e The Exception object to compare the current object with
    /// @returns True if the currnent and the specified objects are the same object or both represent the same exception or both do not represent any exceptions (are null-objects), otherwise - false 
    ASPOSECPP_SHARED_API bool Equals(const ExceptionWrapperBase &e) const;

    /// @brief Checks if exception object is of specific type or its child type. Follows C# 'is' semantics.
    /// @param target Specifies target type to check against.
    /// @return True if C# 'is'-style check is positive and false otherwise.
    ASPOSECPP_SHARED_API bool Is(const System::TypeInfo &target) const;

    /// Calls GetHashCode() on exception pointer.
    /// @return Result of GetHashCode() call on referenced object (if any) or 0.
    ASPOSECPP_SHARED_API int GetHashCode() const;

    /// Calls ToString() on exception pointer.
    /// @return Result of ToString() call on referenced object.
    ASPOSECPP_SHARED_API String ToString() const;

protected:
    /// Pointer to real Exception class.
    ExceptionPtr m_ptr;
};
/// @endcond

/// Template that represents wrapper of exceptions that are derived from Exception class
template <typename T>
class ASPOSECPP_SHARED_CLASS ExceptionWrapper /** @cond */ : public ExceptionWrapper<typename ExceptionWrapperHelper::BaseTypeProvider<T>::BaseType> /** @endcond */
{
private:
    using ExceptionBaseType = typename ExceptionWrapperHelper::BaseTypeProvider<T>::BaseType;

public:
    /// Implicit cast operator to SharedPtr<Object>
    operator SharedPtr<Object>()
    {
        return ExceptionWrapper<ExceptionBaseType>::m_ptr.ToObjectPtr();
    }

    /// Used for casting functions.
    using ExceptionType = T;

    static void* operator new(std::size_t) = delete;
    static void* operator new[](std::size_t) = delete;

    /// Shortcut to get System::TypeInfo object for the Exception type.
    /// @returns Const reference to TypeInfo structure which describes Exception type.
    static const System::TypeInfo& Type() { return T::Type(); }

    /// Constructs a null-instance of ExceptionWrapper class that does not represent any exception.
    ExceptionWrapper(std::nullptr_t) : ExceptionWrapper<ExceptionBaseType>(nullptr) {}

    /// Constructs a instance of ExceptionWrapper class that contains passed pointer.
    /// @param ptr Smart pointer to the instance of Exception class.
    ExceptionWrapper(const ExceptionPtr& ptr) : ExceptionWrapper<T>(static_cast<T*>(ptr.get())) {}

    /// Copy constructor.
    /// @param other Other instance of wrapper class that must be copied.
    ExceptionWrapper(const ExceptionWrapper& other) : ExceptionWrapper<ExceptionBaseType>(other.m_ptr) {}

    /// Move constructor.
    /// @param other Other instance of wrapper class that must be moved.
    ExceptionWrapper(ExceptionWrapper&& other) noexcept
        : ExceptionWrapper<ExceptionBaseType>(std::forward<ExceptionPtr>(other.m_ptr)) {}

    /// Assignment operator.
    /// @param other Other instance of wrapper class that must be assigned.
    /// @returns Instance with new assigned value.
    ExceptionWrapper& operator=(const ExceptionWrapper& other)
    {
        if (this != &other)
            ExceptionWrapper<ExceptionBaseType>::m_ptr = other.m_ptr;

        return *this;
    }

    /// Move assignment operator.
    /// @param other Other instance of wrapper class that must be moved.
    /// @returns Instance with new moved value.
    ExceptionWrapper& operator=(ExceptionWrapper&& other) noexcept
    {
        if (this != &other)
            ExceptionWrapper<ExceptionBaseType>::m_ptr = std::move(other.m_ptr);

        return *this;
    }

    /// Constructor that forwards parameters to the Exception class constructors
    /// and creates smart pointer that holds new Exception class instance.
    template <typename ...Args,
              typename = std::enable_if_t<
                  !System::Details::IsForwardingOf<ExceptionPtr, Args...>::value &&
                  !System::Details::IsForwardingOf<ExceptionWrapper<T>, Args...>::value>>
    explicit ExceptionWrapper(Args&& ...args)
        : ExceptionWrapper<ExceptionBaseType>(
            static_pointer_cast<Details_Exception>(
                T::MakeObject(
                    std::forward<Args>(args)...
                )
            )
        )
    {}

    /// Allows to access members of the Exception object.
    /// @returns Raw pointer to the Exception object.
    /// @throw System::NullReferenceException if pointer is null.
    T* operator->() const
    {
        return static_cast<T*>(ExceptionWrapper<ExceptionBaseType>::m_ptr.GetObjectNotNull());
    }

protected:
    /// Constructs a instance of ExceptionWrapper class that contains passed instance.
    /// @param ptr Raw pointer to the instance of Exception class.
    ExceptionWrapper(T* ptr) : ExceptionWrapper<ExceptionBaseType>(static_cast<ExceptionBaseType*>(ptr)) {}
};

/// @cond
template <typename T>
struct ASPOSECPP_SHARED_CLASS CastResult<ExceptionWrapper<T>>
{
    /// An alias for a MusticastDelegate<T> type.
    typedef ExceptionWrapper<T> type;
};
/// @endcond

/// @cond
/// Template class specialization for Exception class
template <>
class ASPOSECPP_SHARED_CLASS ExceptionWrapper<Details_Exception> : public ExceptionWrapperBase
{
public:
    /// Implicit cast operator to SharedPtr<Object>
    ASPOSECPP_SHARED_API operator SharedPtr<Object>();

    /// Used for casting functions.
    using ExceptionType = Details_Exception;

    /// Null-instance.
    static ASPOSECPP_SHARED_API ExceptionWrapper<Details_Exception> NullException;

    static void* operator new(std::size_t) = delete;
    static void* operator new[](std::size_t) = delete;
    
    /// Shortcut to get System::TypeInfo object for the Exception type.
    /// @returns Const reference to TypeInfo structure which describes Exception type.
    static const ASPOSECPP_SHARED_API System::TypeInfo& Type();

    /// Constructs a null-instance of ExceptionWrapper class that does not represent any exception.
    ASPOSECPP_SHARED_API ExceptionWrapper(std::nullptr_t);

    /// Constructs an instance of ExceptionWrapper class.
    ASPOSECPP_SHARED_API ExceptionWrapper();

    /// Constructs a instance of ExceptionWrapper class that contains passed pointer.
    /// @param ptr Smart pointer to the instance of Exception class.
    ASPOSECPP_SHARED_API ExceptionWrapper(const ExceptionPtr& ptr);

    /// Constructs an instance of ExceptionWrapper class and pass parameters to Exception class constructor.
    /// @param message String that contains the error destription
    ASPOSECPP_SHARED_API ExceptionWrapper(const String& message);

    /// Constructs an instance of ExceptionWrapper class and pass parameters to Exception class constructor.
    /// @param message String that contains the error destription
    /// @param innerException A reference to the exception object interpreted as a cause for the exception represented by the Exception being constructed 
    ASPOSECPP_SHARED_API ExceptionWrapper(const String &message, const ExceptionWrapper<Details_Exception>& innerException);

    /// Constructs an instance of ExceptionWrapper class and pass parameters to Exception class constructor.
    /// @param info SerializationInfo object holding serialized exception.
    /// @param context Streaming context bound to serialization info passed.
    ASPOSECPP_SHARED_API ExceptionWrapper(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context);

    /// Allows to access members of the Exception object.
    /// @returns Raw pointer to the Exception object.
    /// @throw System::NullReferenceException if pointer is null.
    ASPOSECPP_SHARED_API Details_Exception* operator->() const;

    /// Method that must be called in catch blocks to rethrow exception
    /// @throw System::NullReferenceException if pointer is null.
    [[noreturn]] ASPOSECPP_SHARED_API void Throw() const;

protected:
    /// Constructs a instance of ExceptionWrapper class that contains passed instance.
    /// @param ptr Raw pointer to the instance of Exception class.
    ASPOSECPP_SHARED_API ExceptionWrapper(Details_Exception* ptr);
};
/// @endcond

/// Represents an exception.
/// Never create instances of this class manually. Use the Exception class instead.
/// Never wrap the Exception class instances into System::SmartPtr.
class ASPOSECPP_SHARED_CLASS Details_Exception : public System::Object
{
    RTTI_INFO_NAMED(System::Details_Exception, "System::Exception", ::System::BaseTypesInfo<System::Object>);

    template <typename T> friend class ExceptionWrapper;

public:
    // imitate to C# .Message property for correct translation
    /// Returns the string containing the error destcription.
    virtual ASPOSECPP_SHARED_API String get_Message() const;

    /// Returns the string containing the stack trace.
    virtual ASPOSECPP_SHARED_API String get_StackTrace() const;

    /// Returns a reference to the object representing the inner exception.
    virtual ASPOSECPP_SHARED_API ExceptionWrapper<Details_Exception> get_InnerException() const;

    /// Returns the copy of Exception object representing the inner-most exception.
    virtual ASPOSECPP_SHARED_API ExceptionWrapper<Details_Exception> GetBaseException() const;

    /// Returns a 32-bit integer value which is a HRESULT code associated with the exception reprsented by the current object.
    ASPOSECPP_SHARED_API int32_t get_HResult() const;

    /// Sets HRESULT, a coded numerical value that is assigned to a specific exception.
    ASPOSECPP_SHARED_API void set_HResult(int32_t value);

    /// Returns the string representation of the current object.
    virtual ASPOSECPP_SHARED_API String ToString() const override;

    /// Implements what() method which is called by ExceptionWrapper class.
    /// Despite of the fact that this class is not inherited from std::exception
    /// derived classes can use protected/private members to implement their logic.
    /// Moving this method implementation to the ExceptionWrapper may broke that logic.
    /// @returns The description of the exception.
    virtual ASPOSECPP_SHARED_API const char* what() const noexcept;

    /// Throws exception instance wrapped by exception wrapper.
    /// @param self Exception instance to be thrown.
    [[noreturn]] virtual ASPOSECPP_SHARED_API void DoThrow(const ExceptionPtr& self) const;

protected:
    /// Constructs an instance of Exception class.
    ASPOSECPP_SHARED_API Details_Exception();
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Exception, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Constructs an instance of Exception class and assigns the specified error message to it.
    /// @param message String that contains the error destription
    ASPOSECPP_SHARED_API Details_Exception(const String& message);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Exception, CODEPORTING_ARGS(const String& message), CODEPORTING_ARGS(message));

    /// Constructs an instance of Exception class and assigns the specified error message and a reference to the inner exception object. 
    /// @param message String that contains the error destription
    /// @param innerException A reference to the exception object interpreted as a cause for the exception represented by the Exception being constructed 
    ASPOSECPP_SHARED_API Details_Exception(const String &message, const ExceptionWrapper<Details_Exception>& innerException);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Exception, CODEPORTING_ARGS(const String &message, const ExceptionWrapper<Details_Exception>& innerException), CODEPORTING_ARGS(message, innerException));

    /// Deserializes exception.
    /// @param info SerializationInfo object holding serialized exception.
    /// @param context Streaming context bound to serialization info passed.
    ASPOSECPP_SHARED_API Details_Exception(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context);
    MEMBER_FUNCTION_MAKE_OBJECT(Details_Exception,
        CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context),
        CODEPORTING_ARGS(info, context)
    );

    /// The error description.
    String m_message;
    /// The Exception object representing the inner exception.
    System::ExceptionWrapper<Details_Exception> m_innerexception;

    /// A string describing the std::exception portion of the current object.
    mutable std::string m_std_message;

    /// HRESULT code associated with the exception represented by the current object.
    mutable int32_t m_HResult;

    // Use it in derived classes
    /// Returns a string containing additional description of the exception.
    virtual ASPOSECPP_SHARED_API String ExtraDescription() const;

    /// Returns a default description of the exception based on type
    String DefaultMessage() const;

private:
    /// Returns a string containing the full description of the exception.
    /// @param message A message to format.
    virtual ASPOSECPP_SHARED_API String FullMessage(const String& message) const;

    Details_Exception(const Details_Exception&) = delete;
    Details_Exception& operator=(const Details_Exception&) = delete;
};

/// Alias to be used instead of Details::Exception.
using Exception = ExceptionWrapper<Details_Exception>;

/// Prints value to ostream. Mostly used for debug.
ASPOSECPP_SHARED_API void PrintTo(const Details_Exception& exception, std::ostream* stream);

/// Prints value to ostream. Mostly used for debug.
template <typename T>
void PrintTo(const ExceptionWrapper<T>& exception_wrapper, std::ostream* stream)
{
    T* exception = exception_wrapper.operator->();
    if (exception == nullptr)
        *stream << "nullptr";
    else
        PrintTo(*exception, stream);
}

/// Insert data into the stream using UTF-8 encoding.
/// @param stream Output stream to insert data to.
/// @param exception Data to insert.
/// @return \p stream.
inline std::ostream& operator<<(std::ostream& stream, const Exception& exception)
{
    if (exception != nullptr)
        stream << exception->ToString();
    return stream;
}

/// Insert data into the stream.
/// @param stream Output stream to insert data to.
/// @param exception Data to insert.
/// @return \p stream.
inline std::wostream& operator<<(std::wostream& stream, const Exception& exception)
{
    if (exception != nullptr)
        stream << exception->ToString();
    return stream;
}

} // namespace System

/// Determines if the specified Exception objects are not equal.
/// @param e1 The first comparand
/// @param e2 The second comparand
/// @returns False if both objects are the same object or both represent the same exception or both do not represent any exceptions (are null-objects), otherwise - true 
ASPOSECPP_SHARED_API bool operator != (const System::ExceptionWrapperBase& e1, const System::ExceptionWrapperBase& e2);

/// Determines if the specified Exception object is a null-object i.e. does not represent any exception.
/// @param e The Exception object to check
/// @returns True if the specified Exception object is a null-object, otherwise - false
ASPOSECPP_SHARED_API bool operator == (std::nullptr_t, const System::ExceptionWrapperBase &e);

/// Determines if the specified Exception object is not a null-object i.e. represents an exception.
/// @param e The Exception object to check
/// @returns True if the specified Exception object is not a null-object, otherwise - false
ASPOSECPP_SHARED_API bool operator != (std::nullptr_t, const System::ExceptionWrapperBase &e);

#endif // _aspose_system_exception_h_
