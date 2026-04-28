/// @file system/func.h
/// Contains the declaration of System::Func class and supporting classes.
#pragma once

#include "defines.h"
#include <functional>
#include <tuple>
#include <utility>
#include "system/multicast_delegate.h"

namespace System
{
namespace Detail
{

    /// Helper class that reorders Func arguments to get return type from after argument types.
    /// @tparam Reordered Call type that accumulates actual call type.
    /// @tparam FuncArgs Remaining arguments of System::Func.
    template <typename Reordered, typename ...FuncArgs> struct FuncArgsReorderer;

    /// Helper class that reorders Func arguments to get return type from after argument types.
    /// Specialization for at least one argument prior to return type.
    /// @tparam ReorderedArgs Arguments that are already sorted out.
    /// @tparam FirstArg Next argument to sort out.
    /// @tparam OtherArgs Remaining arguments.s
    template <typename ...ReorderedArgs, typename FirstArg, typename ...OtherArgs>
    struct FuncArgsReorderer<void(ReorderedArgs...), FirstArg, OtherArgs...>
        : FuncArgsReorderer<void(ReorderedArgs..., FirstArg), OtherArgs...>
    {};

    /// Helper class that reorders Func arguments to get return type from after argument types.
    /// Specialization for at least one argument prior to return type.
    /// @tparam ReorderedArgs Arguments that are sorted out.
    /// @tparam ReturnType Return type of the function.
    template <typename ...ReorderedArgs, typename ReturnType>
    struct FuncArgsReorderer<void(ReorderedArgs...), ReturnType>
    {
        /// Call type in C++ style.
        using type = ReturnType(ReorderedArgs...);
    };

} // namespace Detail

/// Function delegate.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
/// @code
/// #include "system/func.h"
/// #include <iostream>
///
/// // This function accepts an instance of the System::Func delegate as a parameter.
/// void Print(int x, const System::Func<int, int> &func)
/// {
///   std::cout << func(x) << std::endl;
/// }
///
/// int main()
/// {
///   // Create an instance of the System::Func delegate.
///   auto func = static_cast<System::Func<int, int>>([](int x) -> int
///   {
///     return x * x;
///   });
///
///   // Pass the created instance as a function argument.
///   Print(1, func);
///   Print(2, func);
///   Print(3, func);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1
/// 4
/// 9
/// */
/// @endcode
/// @tparam Args Call arguments, then mandatory return type.
template<typename... Args>
class Func : public MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>
{
    // There's no way to avoid using external template argument parser class as argument pack must be the last template argument, and in .Net Func arguments preceded the return value.
    // Also, there's no way to just alias MulticastDelegate, as this way deducing Func arguments doesn't work, and we have LINQ tests where it should.
public:
    /// Default constructor that creates null-Func.
    Func()
        : MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>()
    {}
    /// Constructor that constructs Func object and assigns value (either actual callback or nullptr) to it.
    /// @tparam T Argument type.
    /// @param arg Argument.
    template <typename T>
    Func(T &&arg)
        : MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>(arg)
    {}
    /// Copy constructor.
    /// @param func Object to copy data from.
    Func(const Func &func)
        : MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>(func)
    {}
    /// Move constructor.
    /// @param func Object to move data from.
    Func(Func &&func) noexcept
        : MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>(std::move(func))
    {}
    /// Destructor.
    ~Func()
    {}

    /// Copy assignment.
    /// @param other Func delegate to copy to current object.
    /// @return Reference to this.
    Func& operator = (const Func &other)
    {
        MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>::operator = (other);
        return *this;
    }
    /// Move assignment.
    /// @param other Func delegate to move to current object. The state can be changed.
    /// @return Reference to this.
    Func& operator = (Func &&other) noexcept
    {
        MulticastDelegate<typename ::System::Detail::FuncArgsReorderer<void(), Args...>::type>::operator = (std::move(other));
        return *this;
    }
};

} // namespace System
