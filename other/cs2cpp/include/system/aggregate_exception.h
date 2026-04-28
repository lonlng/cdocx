/// @file system/exception.h
/// @brief Defines the Details_AggregateException class, which represents an exception that is a collection of multiple
/// inner exceptions.
///
/// The Details_AggregateException is used to encapsulate multiple exceptions that may be thrown during parallel or
/// asynchronous operations. It provides methods to access, flatten, and handle the contained exceptions uniformly.
#pragma once

#include <system/exception.h>
#include <system/func.h>

namespace System {
namespace Collections { namespace ObjectModel {
template<typename>
class ReadOnlyCollection;
}}

/// @brief Alias for the exception wrapper around Details_AggregateException.
class Details_AggregateException;
using AggregateException = ExceptionWrapper<Details_AggregateException>;

/// @brief Represents an exception that contains multiple inner exceptions.
///
/// This class is typically used to group several exceptions that occur concurrently,
/// such as in parallel processing or asynchronous task execution scenarios.
/// It allows users to examine, flatten, or selectively handle the contained exceptions.
class ASPOSECPP_SHARED_CLASS Details_AggregateException : public Details_Exception
{
    typedef Details_AggregateException ThisType;
    typedef Details_Exception BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

    friend class ExceptionWrapperHelper;
    template <typename T>
    friend class ExceptionWrapper;

public:
    /// @brief Gets a read-only collection of the inner exceptions.
    /// @return A shared pointer to a read-only collection of Exception objects.
    ASPOSECPP_SHARED_API SharedPtr<Collections::ObjectModel::ReadOnlyCollection<Exception>> get_InnerExceptions();
    /// @brief Overrides the base message to include aggregated information from all inner exceptions.
    /// @return A string representing the composite error message.
    ASPOSECPP_SHARED_API String get_Message() const override;
    /// @brief Gets the number of inner exceptions contained in this aggregate exception.
    /// @return The count of inner exceptions.
    ASPOSECPP_SHARED_API int32_t get_InnerExceptionCount();
    /// @brief Returns the internal array of inner exceptions.
    /// @return An ArrayPtr containing Exception objects.
    const ArrayPtr<Exception>& get_InternalInnerExceptions() { return _innerExceptions; }

    /// @brief Returns the root cause exception by recursively unwrapping inner exceptions.
    /// @return The base (root) exception.
    ASPOSECPP_SHARED_API Exception GetBaseException() const override;
    /// @brief Invokes a handler function on each inner exception and rethrows any unhandled exceptions.
    /// @param predicate A function that takes an Exception and returns true if it is handled.
    /// @note If all exceptions are handled, the method returns normally; otherwise, a new AggregateException
    ///       containing the unhandled exceptions is thrown.
    ASPOSECPP_SHARED_API void Handle(const Func<Exception, bool>& predicate);
    /// @brief Flattens the aggregate exception by unwrapping all nested AggregateExceptions into a single-level list.
    /// @return A new AggregateException containing all non-aggregate inner exceptions from the entire hierarchy.
    ASPOSECPP_SHARED_API AggregateException Flatten();
    /// @brief Returns a string representation of the exception, including all inner exceptions.
    /// @return A detailed string describing the exception and its inner exceptions.
    ASPOSECPP_SHARED_API String ToString() const override;

protected:
    /// @brief Throws this exception instance.
    /// @param self A shared pointer to this exception.
    /// @remarks This function is marked [[noreturn]] and is used internally for exception propagation.
    [[noreturn]] ASPOSECPP_SHARED_API void DoThrow(const ExceptionPtr& self) const override;

    /// @brief Default constructor.
    ASPOSECPP_SHARED_API Details_AggregateException();
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException, CODEPORTING_ARGS());

    /// @brief Constructs an aggregate exception with a custom message.
    /// @param message The error message associated with this exception.
    ASPOSECPP_SHARED_API Details_AggregateException(const String& message);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException, CODEPORTING_ARGS(const String& message));

    /// @brief Constructs an aggregate exception with a message and a single inner exception.
    /// @param message The error message.
    /// @param innerException The inner exception to wrap.
    ASPOSECPP_SHARED_API Details_AggregateException(const String& message, Exception innerException);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException, CODEPORTING_ARGS(const String& message,
        const Exception& innerException));

    /// @brief Constructs an aggregate exception from a collection of inner exceptions.
    /// @param innerExceptions A shared pointer to an IEnumerable of Exception objects.
    ASPOSECPP_SHARED_API Details_AggregateException(const SharedPtr<Collections::Generic::IEnumerable<Exception>>& innerExceptions);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException,
        CODEPORTING_ARGS(const SharedPtr<Collections::Generic::IEnumerable<Exception>>& innerExceptions));

    /// @brief Constructs an aggregate exception from an array of inner exceptions.
    /// @param innerExceptions An array of Exception objects.
    ASPOSECPP_SHARED_API Details_AggregateException(const ArrayPtr<Exception>& innerExceptions);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException,
        CODEPORTING_ARGS(const ArrayPtr<Exception>& innerExceptions));

    /// @brief Constructs an aggregate exception with a message and a collection of inner exceptions.
    /// @param message The error message.
    /// @param innerExceptions A shared pointer to an IEnumerable of Exception objects.
    ASPOSECPP_SHARED_API Details_AggregateException(const String& message,
        const SharedPtr<Collections::Generic::IEnumerable<Exception>>& innerExceptions);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException, CODEPORTING_ARGS(const String& message,
        const SharedPtr<Collections::Generic::IEnumerable<Exception>>& innerExceptions));

    /// @brief Constructs an aggregate exception with a message and an array of inner exceptions.
    /// @param message The error message.
    /// @param innerExceptions An array of Exception objects.
    ASPOSECPP_SHARED_API Details_AggregateException(const String& message, const ArrayPtr<Exception>& innerExceptions);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException, CODEPORTING_ARGS(const String& message,
        const ArrayPtr<Exception>& innerExceptions));

    /// @brief Constructs an aggregate exception with options to clone inner exceptions.
    /// @param message The error message.
    /// @param innerExceptions An array of Exception objects.
    /// @param cloneExceptions If true, the provided exceptions are deep-copied; otherwise, they are referenced
    /// directly.
    ASPOSECPP_SHARED_API Details_AggregateException(const String& message, const ArrayPtr<Exception>& innerExceptions, bool cloneExceptions);
    ASPOSECPP_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_AggregateException,
        CODEPORTING_ARGS(const String& message, const ArrayPtr<Exception>& innerExceptions, bool cloneExceptions));

    /// @brief Virtual destructor.
    ASPOSECPP_SHARED_API virtual ~Details_AggregateException();

#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(Object::shared_members_type& result) const override;
#endif

private:
    ArrayPtr<Exception> _innerExceptions;
    SharedPtr<Collections::ObjectModel::ReadOnlyCollection<Exception>> _rocView;

    /// @brief Internal helper for generating the string representation (non-const version).
    /// @return A string describing the exception and its inner exceptions.
    ASPOSECPP_SHARED_API String ToString_NonConst();
};

} // namespace System
