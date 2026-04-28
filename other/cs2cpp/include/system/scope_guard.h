/// @file system/scope_guard.h
/// Contains the declaration System::ScopeGuard class.
#ifndef _aspose_system_scope_guard_h_
#define _aspose_system_scope_guard_h_

#include <exception>

namespace System
{

/// The service class that provides services for running a particular function object
/// when an instance of the class goes out of scope.
/// @tparam F The type of the function object invoked by the instances of the ScopedGuard class
template <typename F>
struct ScopeGuard
{
    /// Constructs an instance that is set up to invoke the specified function object.
    /// @param f The function object to be invoked in the destructor of the object being constructed.
    ScopeGuard(F f) : f(f), disabled(false)
    {}
#if defined(_MSC_VER)
#pragma warning(push)
// Warning C4722: destructor never returns, potential memory leak.
#pragma warning(disable : 4722)
#endif
    /// Invokes the function object passed to the constructor.
    ~ScopeGuard() noexcept(false)
    {
        if (!disabled)
        {
#ifdef __cpp_lib_uncaught_exceptions
            if (std::uncaught_exceptions() > 0)
#else
            if (std::uncaught_exception()) // Deprecated since C++ 17
#endif
            {
                // "finally" during exception (unwinding stack)
                // need prevent double exception and process termination
                try
                {
                    f();
                }
                catch (...)
                {
                }
            }
            else
            {
                f();
            }
        }
    }
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

    /// Disables guard invocation
    void Disable()
    {
        disabled = true;
    }

private:
    /// The function object to be inovked in the destructor.
    F f;
    bool disabled;
};

// auto guard = MakeScopeGuard([&](){
//     .....
// });
/// A factory function that creates instances of ScopedGuard class.
/// @param f The function object to pass to ScopedGuard class' constructor.
/// @returns A new instance of ScopedGuard class
/// @tparam The type of the function object to be invoked by the constructed ScopedGuard object
template <typename F>
ScopeGuard<F> MakeScopeGuard(F f)
{
    return ScopeGuard<F>(f);
};

} // namespace System
#endif // _aspose_system_scope_guard_h_
