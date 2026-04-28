/// @file system/do_try_finally.h
/// Contains the definition of service functions used to emulate the behavior of C#'s try-catch-finally statement.
#pragma once

#include <exception>
#include <functional>
#include <system/details/value_init.h>
#include <system/details/is_lambda.h>
#include "defines.h"

// https://stackoverflow.com/a/53365539
// We haven't checked which optinal to include yet
#ifndef INCLUDE_STD_OPTIONAL_EXPERIMENTAL

// Check current standard

// C++17
#   if CODEPORTING_CPP_STANDARD >= 17

// Check for feature test macro for <optinal>
#      if defined(__cpp_lib_optional)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 0

// Check for feature test macro for <experimental/optional>
#      elif defined(__cpp_lib_experimental_optional)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1

// We can't check if headers exist...
// Let's assume experimental to be safe
#       elif !defined(__has_include)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1

// Check if the header "<optional>" exists
#       elif __has_include(<optional>)

// If we're compiling on Visual Studio and are not compiling with C++17, we need to use experimental
#           ifdef _MSC_VER

// Check and include header that defines "_HAS_CXX17"
#               if __has_include(<yvals_core.h>)
#                   include <yvals_core.h>

// Check for enabled C++17 support
#                   if defined(_HAS_CXX17) && _HAS_CXX17
// We're using C++17, so let's use the normal version
#                       define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 0
#                   elif __has_include(<experimental/optional>)
#                       define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1
#                   endif
#               endif

// If the marco isn't defined yet, that means any of the other VS specific checks failed, so we need to use custom implementation
#               ifndef INCLUDE_STD_OPTIONAL_EXPERIMENTAL
#                   define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 2
#               endif

// Not on Visual Studio. Let's use the normal version
#           else // #ifdef _MSC_VER
#               define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 0
#           endif

// Check if the header "<optional>" exists
#       elif __has_include(<experimental/optional>)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1

// Fallback to custom implementation 
#       else
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 2
#       endif

// C++14
#   elif CODEPORTING_CPP_STANDARD >= 14

// Check for feature test macro for <experimental/optional>
#       if defined(__cpp_lib_experimental_optional)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1
#       elif !defined(__has_include)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1

// Check if the header "<experimental/optional>" exists
#       elif __has_include(<experimental/optional>)
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 1

// Fallback to custom implementation 
#       else
#           define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 2
#       endif

// Something else
#   else

// Fallback to custom implementation 
#       define INCLUDE_STD_OPTIONAL_EXPERIMENTAL 2

#   endif

// We previously determined that we need the experimental version
#   if INCLUDE_STD_OPTIONAL_EXPERIMENTAL == 1
// Include it
#       include <experimental/optional>

// We need the alias from std::experimental::filesystem to std::filesystem
namespace std {
    template<typename T>
    using optional = experimental::optional<T>;

    constexpr auto nullopt = std::experimental::nullopt;
}

// It is MSVC with /std:c++14 flag, let's use custom implementation
#   elif INCLUDE_STD_OPTIONAL_EXPERIMENTAL == 2
// Include it
#       include "details/optional.h"

// We need the alias from std::experimental::optional to std::optional
namespace std {
    template<typename T>
    using optional = experimental::optional<T>;

    constexpr auto nullopt = std::experimental::nullopt;
}

// We have a decent compiler and can use the normal version
#   else
// Include it
#       include <optional>
#   endif

#endif // #ifndef INCLUDE_STD_OPTIONAL_EXPERIMENTAL 


namespace System
{
namespace Details
{

/// Represents an invocation agent that invokes particular function object in the destructor.
/// @tparam F The type of the function object to be invoked in the destructor
template <typename F>
class FinallyGuard
{
public:
    /// Constructs an instance of the FunallyGuard class.
    /// @param exception A reference to an std::exception_ptr object which 
    /// will be assigned any exception that is thrown by the specified function object 
    /// when it is invoked
    /// @param finallyBlock The function object to be invoked in the destructor 
    /// of the object being constructed
    FinallyGuard(std::exception_ptr& exception, F&& finallyBlock)
        : mException(exception), mFinallyBlock(std::move(finallyBlock))
    {}

    /// Destructor.
    ~FinallyGuard()
    {
        try
        {
            mFinallyBlock();
        }
        catch (...)
        {
            mException = std::current_exception();
        }
    }
private:
    /// The reference to the exception_ptr object through which 
    /// the exception thrown by the @mFinallyBlock function object
    /// is passed to the user of the current object.
    std::exception_ptr& mException;

    /// The function object that is invoked in the destructor of the 
    /// current object.
    F mFinallyBlock;
};

/// The factory function that constructs instances of FinallyGuard class.
/// @param exception A reference to an std::exception_ptr object that 
/// is passed to the constructor of FinallyGuard class
/// @param f The function object that is passed to the FinallyGuard class
/// @tparam F The template parameter that specifies the template instance 
/// of the FinallyGuard<> class object of which is created by the factory function
template<typename F>
FinallyGuard<F> MakeFinallyGuard(std::exception_ptr& exception, F&& f)
{
    return FinallyGuard<F>(exception, std::move(f));
}

/// Implements the main functionality provided by DoTryFinally() function.
/// @param tryBlock The function object whose body contains the implementation of the try[-catch] part
/// of the try[-catch]-finally statemet being emulated
/// @param finallyBlock The function object whose body contains the implementation of the finally part
/// of the try[-catch]-finally statement being emulated
/// @tparam T The type of the function object that implements the try[-catch] part of the
/// try[-catch]-finally statement being emulated
/// @tparam F The type of the function object that implements the finally part of the
/// try[-catch]-finally statement being emulated
template <typename T, typename F>
void DoTryFinallyImpl(T&& tryBlock, F&& finallyBlock)
{
    std::exception_ptr exception;
    {
        auto finally_guard = MakeFinallyGuard(exception, std::move(finallyBlock));

        try
        {
            tryBlock();
        }
        catch (...)
        {
            exception = std::current_exception();
        }
    }

    if (exception)
    {
        std::rethrow_exception(exception);
    }
}


} // namespace Details

// lambda - [](){}
/// The sigle function that emulates behavior of C#'s try[-catch]-finally statement. 
/// During translation of C#'s try[-catch]-finally statement with translator's option 
/// finally_statement_as_lambda set to true, the statement is translated 
/// into the invocation of this method.
/// @param tryBlock The function object whose body contains the implementation of the try[-catch] part
/// of the try[-catch]-finally statemet being emulated
/// @param finallyBlock The function object whose body contains the implementation of the finally part
/// of the try[-catch]-finally statement being emulated
/// @tparam T The type of the function object that implements the try[-catch] part of the
/// try[-catch]-finally statement being emulated
/// @tparam F The type of the function object that implements the finally part of the
/// try[-catch]-finally statement being emulated
template<typename T, typename F>
std::enable_if_t<Details::is_lambda_void_void<T>::value>
DoTryFinally(T&& tryBlock, F&& finallyBlock)
{
    Details::DoTryFinallyImpl(tryBlock, finallyBlock);
}

// lambda - [](bool&){}
/// The sigle function that emulates behavior of C#'s try[-catch]-finally statement. 
/// During translation of C#'s try[-catch]-finally statement with translator's option 
/// finally_statement_as_lambda set to true, the statement is translated 
/// into the invocation of this method. This overload handles the case in which the return value of
/// the function object that implements the try[-catch] part of the try[-catch]-finally statement
/// is bool.
/// @param tryBlock The function object whose body contains the implementation of the try[-catch] part
/// of the try[-catch]-finally statemet being emulated
/// @param finallyBlock The function object whose body contains the implementation of the finally part
/// of the try[-catch]-finally statement being emulated
/// @tparam T The type of the function object that implements the try[-catch] part of the
/// try[-catch]-finally statement being emulated
/// @tparam F The type of the function object that implements the finally part of the
/// try[-catch]-finally statement being emulated
template<typename T, typename F>
std::enable_if_t<Details::is_lambda_void_boolref<T>::value, bool>
DoTryFinally(T&& tryBlock, F&& finallyBlock)
{
    bool isReturned = true;
    Details::DoTryFinallyImpl([&]() { tryBlock(isReturned); }, finallyBlock);
    return isReturned;
}

// lambda - [](bool&) -> type {}
/// The sigle function that emulates behavior of C#'s try[-catch]-finally statement. 
/// During translation of C#'s try[-catch]-finally statement with translator's option 
/// finally_statement_as_lambda set to true, the statement is translated 
/// into the invocation of this method. This overload handles the case in which the return value of
/// the function object that implements the try[-catch] part of the try[-catch]-finally statement
/// is bool&.
/// @param tryBlock The function object whose body contains the implementation of the try[-catch] part
/// of the try[-catch]-finally statemet being emulated
/// @param finallyBlock The function object whose body contains the implementation of the finally part
/// of the try[-catch]-finally statement being emulated
/// @tparam T The type of the function object that implements the try[-catch] part of the
/// try[-catch]-finally statement being emulated
/// @tparam F The type of the function object that implements the finally part of the
/// try[-catch]-finally statement being emulated
template<typename T, typename F>
std::enable_if_t<Details::is_lambda_nonovoid_boolref<T>::value, std::optional<Details::ResultOf<T, bool&>>>
DoTryFinally(T&& tryBlock, F&& finallyBlock)
{
    using ReturnValueType = Details::ResultOf<T, bool&>;
    ReturnValueType returnValue;

    bool isReturned = true;

    Details::DoTryFinallyImpl([&]() { returnValue = tryBlock(isReturned); }, finallyBlock);

    return isReturned ? std::optional<ReturnValueType>(returnValue) : std::nullopt;
}

} // namespace System
