/// @file system/details/patterns.h
#pragma once

#include <utility>
#include <tuple>
#include <system/object_ext.h>
#include <system/value_tuple.h>
#include <system/details/apply.h>
#include <system/details/dereference.h>

namespace System { namespace Details {

template <typename T>
struct DeconstructArgs;

template <typename T, typename... Args>
struct DeconstructArgs<void (T::*)(Args&...)>
{
    using type = std::tuple<Args...>;
};

template <typename T, typename... Args>
struct DeconstructArgs<void (T::*)(Args&...) const>
{
    using type = std::tuple<Args...>;
};

/// Utility metafunction that deduces arguments tuple of object's 'Deconstruct' method.
template <typename T>
using DeconstructTuple = typename DeconstructArgs<decltype(&T::Deconstruct)>::type;

} // Details

/// Implements 'is' declaration pattern translation
/// @tparam PatternT type to check.
/// @tparam ExpressionT left expression type.
/// @tparam ResultT type of result expression.
/// @param left expression which will be checked.
/// @param result variable which will be assigned to checked type.
/// @return true if type check is successfull, false otherwise.
template <class PatternT, class ExpressionT, class ResultT>
bool Is(const ExpressionT& left, ResultT& result)
{
    if (ObjectExt::Is<PatternT>(left))
    {
        result = ExplicitCast<PatternT>(left);
        return true;
    }
    else
    {
        return false;
    }
}

/// Implements 'is' constant pattern translation
/// @tparam ExpressionT left expression type.
/// @tparam ConstantT type of constant expression.
/// @param left expression which will be checked.
/// @param constant expression which will be compared with left one.
/// @return true if type check is successfull, false otherwise.
template <class ExpressionT, class ConstantT>
std::enable_if_t<!std::is_base_of<Details::Pattern, ConstantT>::value, bool> Is(const ExpressionT& left,
                                                                                const ConstantT& constant)
{
    ConstantT value;
    return Is<ConstantT>(left, value) && Equals(constant, value);
}

/// Implements '<' relative pattern translation
/// @tparam ExpressionT left expression type.
/// @tparam ConstantT type of constant expression.
/// @param left expression which will be checked.
/// @param constant expression which will be compared with left one.
/// @return true if type check is successfull, false otherwise.
template <class ExpressionT, class ConstantT>
bool Less(const ExpressionT& left, const ConstantT& constant)
{
    ConstantT value;
    return Is<ConstantT>(left, value) && value < constant;
}

/// Implements '>' relative pattern translation
/// @tparam ExpressionT left expression type.
/// @tparam ConstantT type of constant expression.
/// @param left expression which will be checked.
/// @param constant expression which will be compared with left one.
/// @return true if type check is successfull, false otherwise.
template <class ExpressionT, class ConstantT>
bool Greater(const ExpressionT& left, const ConstantT& constant)
{
    ConstantT value;
    return Is<ConstantT>(left, value) && value > constant;
}

/// Implements '<=' relative pattern translation
/// @tparam ExpressionT left expression type.
/// @tparam ConstantT type of constant expression.
/// @param left expression which will be checked.
/// @param constant expression which will be compared with left one.
/// @return true if type check is successfull, false otherwise.
template <class ExpressionT, class ConstantT>
bool LEqual(const ExpressionT& left, const ConstantT& constant)
{
    ConstantT value;
    return Is<ConstantT>(left, value) && value <= constant;
}

/// Implements '>=' relative pattern translation
/// @tparam ExpressionT left expression type.
/// @tparam ConstantT type of constant expression.
/// @param left expression which will be checked.
/// @param constant expression which will be compared with left one.
/// @return true if type check is successfull, false otherwise.
template <class ExpressionT, class ConstantT>
bool GEqual(const ExpressionT& left, const ConstantT& constant)
{
    ConstantT value;
    return Is<ConstantT>(left, value) && value >= constant;
}

/// Implements 'var' pattern translation
/// @tparam ExpressionT variable type.
/// @param var reference to variable to be initialized.
/// @param value value to be assigned to variable.
/// @return always true (this pattern always hits).
template <class ExpressionT>
bool Set(ExpressionT& var, const ExpressionT& value)
{
    var = value;
    return true;
}

/// Checks if object is tuple (implements ITuple interface). Used in positional pattern implementation
/// @param object object to check.
/// @param length expected tuple length
/// @returns is object is tuple and its length equal to expected one
inline bool IsTuple(const SharedPtr<Object>& object, int32_t length)
{
    auto tuple = AsCast<Runtime::CompilerServices::ITuple>(object);
    return tuple && tuple->get_Length() == length;
}

/// Function to get N-th element of tuple given. Overload for base object.
/// @tparam N element index.
/// @param object object to inspect.
/// @return value of N-th tuple element casted to object.
template <std::size_t N>
auto Get(const SharedPtr<Object>& object)
{
    return ExplicitCast<Runtime::CompilerServices::ITuple>(object)->idx_get(N);
}

/// Function to get N-th element of tuple given. Overload for objects with Deconstruct method.
/// @tparam N element index.
/// @tparam T type of inspected object.
/// @param object object to inspect.
/// @return value of N-th tuple element.
template <std::size_t N, typename T>
auto Get(const T& object)
{
    Details::DeconstructTuple<T> tuple;
    System::Details::apply([&](auto&... args) { const_cast<T&>(object).Deconstruct(args...); }, tuple);
    return std::get<N>(tuple);
}

/// Function to get N-th element of tuple given. Overload for shared pointers.
/// @tparam N element index.
/// @tparam T type of inspected object.
/// @param object object to inspect.
/// @return value of N-th tuple element.
template <std::size_t index, typename T>
auto Get(const SharedPtr<T>& pointer)
{
    return Get<index>(*pointer);
}

namespace Details { namespace Patterns {

/// @brief Pattern that matches if the input is equal to a stored value.
/// @tparam C Type of the value to compare against.
template <typename C>
struct Equal : Pattern
{
    /// @brief Constructs an Equal pattern with the given value.
    /// @param _c The value to compare against during matching.
    Equal(const C& _c) : c(_c) {}

    /// @brief Checks equality when the input type matches the stored type exactly.
    /// Uses System::Equals for precise comparison.
    /// @param e Input value of the same type as stored value.
    /// @return true if values are equal according to System::Equals.
    template <typename E>
    bool check(const E& e) const
    {
        return System::Equals(e, c);
    }

    /// @brief Checks compatibility and equality for inputs of different types.
    /// Uses System::Is for cross-type comparison.
    /// @tparam E Type of the input value.
    /// @param e Input value to match against.
    /// @return true if e is considered equal to the stored value via System::Is.
    bool check(const SharedPtr<Object>& obj) const
    {
        return System::Is(obj, c);
    }

    C c; ///< Stored value for comparison.
};

/// @brief Specialization of Equal for std::nullptr_t.
/// Matches any value that compares equal to nullptr.
template<>
struct Equal<std::nullptr_t> : Pattern
{
    /// @brief Constructs an Equal pattern for nullptr.
    /// @param Value is ignored; pattern always represents nullptr.
    Equal(std::nullptr_t) {};

    /// @brief Checks if the input is null.
    /// @tparam E Type of the input value.
    /// @param e Input value to test.
    /// @return true if e == nullptr.
    template <typename E>
    static bool check(const E& e)
    {
        return e == nullptr;
    }
};

/// @brief Pattern that matches if the input is less than a stored value.
/// @tparam C Type of the value to compare against.
template <typename C>
struct Less : Pattern
{
    /// @brief Constructs a Less pattern with the given value.
    /// @param _c The value to compare against.
    Less(const C& _c) : c(_c) {}

    /// @brief Checks if input is less than the stored value.
    /// @tparam E Type of the input value.
    /// @param e Input value to compare.
    /// @return true if e < c.
    template <typename E>
    bool check(const E& e) const
    {
        return e < c;
    }

    /// @brief Checks if a SharedPtr<Object> is less than the stored value using System::Less.
    /// @param o Input object wrapped in SharedPtr.
    /// @return true if System::Less(o, c) returns true.
    bool check(const SharedPtr<Object>& o) const
    {
        return System::Less(o, c);
    }

    C c; ///< Stored value for comparison.
};

/// @brief Pattern that matches if the input is greater than a stored value.
/// @tparam C Type of the value to compare against.
template <typename C>
struct Greater : Pattern
{
    /// @brief Constructs a Greater pattern with the given value.
    /// @param _c The value to compare against.
    Greater(const C& _c) : c(_c) {}

    /// @brief Checks if input is greater than the stored value.
    /// @tparam E Type of the input value.
    /// @param e Input value to compare.
    /// @return true if e > c.
    template <typename E>
    bool check(const E& e) const
    {
        return e > c;
    }

    /// @brief Checks if a SharedPtr<Object> is greater than the stored value using System::Greater.
    /// @param e Input object wrapped in SharedPtr.
    /// @return true if System::Greater(e, c) returns true.
    bool check(const SharedPtr<Object>& e) const
    {
        return System::Greater(e, c);
    }

    C c; ///< Stored value for comparison.
};

/// @brief Pattern that matches if the input is less than or equal to a stored value.
/// @tparam C Type of the value to compare against.
template <typename C>
struct LEqual : Pattern
{
    /// @brief Constructs an LEqual (<=) pattern with the given value.
    /// @param _c The value to compare against.
    LEqual(const C& _c) : c(_c) {}

    /// @brief Checks if input is less than or equal to the stored value.
    /// @tparam E Type of the input value.
    /// @param e Input value to compare.
    /// @return true if e <= c.
    template <typename E>
    bool check(const E& e) const
    {
        return e <= c;
    }

    /// @brief Checks if a SharedPtr<Object> is less than or equal to the stored value using System::LEqual.
    /// @param obj Input object wrapped in SharedPtr.
    /// @return true if System::LEqual(obj, c) returns true.
    bool check(const SharedPtr<Object>& obj) const
    {
        return System::LEqual(obj, c);
    }

    C c; ///< Stored value for comparison.
};

/// @brief Pattern that matches if the input is greater than or equal to a stored value.
/// @tparam C Type of the value to compare against.
template <typename C>
struct GEqual : Pattern
{
    /// @brief Constructs a GEqual (>=) pattern with the given value.
    /// @param _c The value to compare against.
    GEqual(const C& _c) : c(_c) {}

    /// @brief Checks if input is greater than or equal to the stored value.
    /// @tparam E Type of the input value.
    /// @param e Input value to compare.
    /// @return true if e >= c.
    template <typename E>
    bool check(const E& e) const
    {
        return e >= c;
    }

    /// @brief Checks if a SharedPtr<Object> is greater than or equal to the stored value using System::GEqual.
    /// @param obj Input object wrapped in SharedPtr.
    /// @return true if System::GEqual(obj, c) returns true.
    bool check(const SharedPtr<Object>& obj) const
    {
        return System::GEqual(obj, c);
    }

    C c; ///< Stored value for comparison.
};

/// @brief Pattern that checks if the input is of a specific type T.
/// @tparam T Expected type.
template <typename T>
struct Is : Pattern
{
    /// @brief Checks if the input is of type T using runtime type information.
    /// @tparam E Type of the input value.
    /// @param e Input value to inspect.
    /// @return true if e is of type T according to System::ObjectExt::Is<T>.
    template <typename E>
    bool check(const E& e) const
    {
        return System::ObjectExt::Is<T>(e);
    }
};

/// @brief Pattern that checks type and binds the casted value to a reference.
/// Combines type checking with value extraction.
/// @tparam T Expected type.
/// @tparam V Type of the variable to bind to.
template <typename T, typename V>
struct IsDeclaration : Pattern
{
    /// @brief Constructs an IsDeclaration pattern that binds to a variable.
    /// @param _v Reference to the variable that will receive the casted value.
    IsDeclaration(V& _v) : v(_v) {}

    /// @brief Checks if input is of type T and binds it to the stored reference.
    /// @tparam E Type of the input value.
    /// @param e Input value to inspect and potentially bind.
    /// @return true if e is of type T and binding succeeds via System::Is<T>.
    template <typename E>
    bool check(const E& e) const
    {
        return System::Is<T>(e, v);
    }

    V& v; ///< Reference to bind the matched value to.
};

/// @brief Logical AND combinator for two patterns.
/// Matches only if both sub-patterns match.
/// @tparam A1 Type of the first pattern.
/// @tparam A2 Type of the second pattern.
template <typename A1, typename A2>
struct And : Pattern
{
    /// @brief Constructs an And pattern from two sub-patterns.
    /// @param _a1 First pattern.
    /// @param _a2 Second pattern.
    And(const A1& _a1, const A2& _a2) : a1(_a1), a2(_a2) {}

    /// @brief Checks if both sub-patterns match the input.
    /// @tparam E Type of the input value.
    /// @param e Input value to match.
    /// @return true if both a1 and a2 match e.
    template <typename E>
    bool check(const E& e) const
    {
        return a1.check(e) && a2.check(e);
    }

    A1 a1; ///< First sub-pattern.
    A2 a2; ///< Second sub-pattern.
};

/// @brief Specialized And combinator for Is<T> followed by another pattern.
/// Optimized to avoid redundant type checks and perform explicit casting.
/// @tparam T Expected type from the Is<T> pattern.
/// @tparam A2 Type of the second pattern.
template <typename T, typename A2>
struct And<Is<T>, A2> : Pattern
{
    /// @brief Constructs an optimized And pattern.
    /// The Is<T> argument is unused (stateless), only A2 is stored.
    /// @param Ignored Is<T> instance.
    /// @param _a2 Pattern to apply to the casted value.
    And(const Is<T>&, const A2& _a2) : a2(_a2) {}

    /// @brief Checks if input is of type T and then applies A2 to the casted value.
    /// @tparam E Type of the input value.
    /// @param e Input value to match.
    /// @return true if e is of type T and a2 matches the casted value.
    template <typename E>
    bool check(const E& e) const
    {
        return System::ObjectExt::Is<T>(e) && a2.check(System::ExplicitCast<T>(e));
    }

    A2 a2; ///< Pattern applied after successful cast.
};

/// @brief Logical OR combinator for two patterns.
/// Matches if at least one sub-pattern matches.
/// @tparam A1 Type of the first pattern.
/// @tparam A2 Type of the second pattern.
template <typename A1, typename A2>
struct Or : Pattern
{
    /// @brief Constructs an Or pattern from two sub-patterns.
    /// @param _a1 First pattern.
    /// @param _a2 Second pattern.
    Or(const A1& _a1, const A2& _a2) : a1(_a1), a2(_a2) {}

    /// @brief Checks if either sub-pattern matches the input.
    /// @tparam E Type of the input value.
    /// @param e Input value to match.
    /// @return true if a1 or a2 matches e.
    template <typename E>
    bool check(const E& e) const
    {
        return a1.check(e) || a2.check(e);
    }

    A1 a1; ///< First sub-pattern.
    A2 a2; ///< Second sub-pattern.
};

/// @brief Logical NOT combinator.
/// Matches if the sub-pattern does NOT match.
/// @tparam A Type of the sub-pattern.
template <typename A>
struct Not : Pattern
{
    /// @brief Constructs a Not pattern.
    /// @param _a Sub-pattern to negate.
    Not(const A& _a) : a(_a) {}

    /// @brief Checks that the sub-pattern fails to match.
    /// @tparam E Type of the input value.
    /// @param e Input value to match.
    /// @return true if a does NOT match e.
    template <typename E>
    bool check(const E& e) const
    {
        return !a.check(e);
    }

    A a; ///< Sub-pattern to negate.
};

/// @brief Variable binding pattern.
/// Always matches and assigns the input to a reference.
/// @tparam V Type of the variable to bind to.
template <typename V>
struct Var : Pattern
{
    /// @brief Constructs a Var pattern that binds to a variable.
    /// @param _v Reference to assign the matched value to.
    Var(V& _v) : v(_v) {}

    /// @brief Binds the input to the stored reference and returns true.
    /// @tparam E Type of the input value.
    /// @param e Input value to bind.
    /// @return Always true.
    template <typename E>
    bool check(const E& e) const
    {
        v = e;
        return true;
    }

    V& v; ///< Reference to bind the matched value to.
};

/// @brief Pattern that matches a const member function call on an object and applies a sub-pattern to the result.
/// @tparam Obj Class type that declares the method.
/// @tparam RV Return type of the method.
/// @tparam A Sub-pattern to apply to the method result.
template <typename Obj, typename RV, typename A>
struct ConstMethod : Pattern
{
    /// @brief Constructs a ConstMethod pattern.
    /// @param getter_ Pointer to a const member function.
    /// @param a_ Sub-pattern to apply to the result of the method call.
    ConstMethod(RV (Obj::*getter_)() const, A a_) : getter(getter_), a(a_) {}

    /// @brief Invokes the stored const method on the input and matches the result.
    /// @tparam E Type of the input object (must be dereferenceable to Obj).
    /// @param e Input object.
    /// @return true if the method result matches sub-pattern a.
    template <typename E>
    bool check(const E& e) const
    {
        return a.check(((System::Details::Dereference(e)).*getter)());
    }

    RV (Obj::*getter)() const; ///< Pointer to const member function.
    A a;                       ///< Sub-pattern for the method result.
};

/// @brief Pattern that matches a member function call on an object and applies a sub-pattern to the result.
/// For non-const member functions.
/// @tparam Obj Class type that declares the method.
/// @tparam RV Return type of the method.
/// @tparam A Sub-pattern to apply to the method result.
template <typename Obj, typename RV, typename A>
struct Method : Pattern
{
    /// @brief Constructs a Method pattern.
    /// @param getter_ Pointer to a non-const member function.
    /// @param a_ Sub-pattern to apply to the result of the method call.
    Method(RV (Obj::*getter_)(), A a_) : getter(getter_), a(a_) {}

    /// @brief Invokes the stored method on the input and matches the result.
    /// @tparam E Type of the input object (must be dereferenceable to Obj).
    /// @param e Input object.
    /// @return true if the method result matches sub-pattern a.
    template <typename E>
    bool check(const E& e) const
    {
        return a.check((const_cast<Obj&>(System::Details::Dereference(e)).*getter)());
    }

    RV (Obj::*getter)(); ///< Pointer to non-const member function.
    A a;                 ///< Sub-pattern for the method result.
};

/// @brief Pattern that matches structured data (tuples, deconstructible objects) positionally.
/// @tparam Subs... Types of sub-patterns for each position.
template <typename... Subs>
struct Positional : Pattern
{
    /// @brief Constructs a Positional pattern with sub-patterns for each field.
    /// @param _subs Sub-patterns corresponding to each position in the tuple/object.
    Positional(Subs... _subs) : subs(_subs...) {}

    /// @brief Matches against a ValueTuple by applying sub-patterns to each element.
    /// @tparam Args... Types of elements in the ValueTuple.
    /// @param vt ValueTuple to match.
    /// @return true if all sub-patterns match their respective elements.
    template <typename... Args>
    bool check(const ValueTuple<Args...>& vt) const
    {
        return System::Details::check(subs, StdTupleChecker<decltype(vt.tuple())>{vt.tuple()});
    }

    /// @brief Matches against an ITuple interface (e.g., runtime tuples).
    /// @param object Shared pointer to an object implementing ITuple.
    /// @return true if object is a tuple of matching length and all elements match.
    bool check(const SharedPtr<Object>& object) const
    {
        auto tuple = AsCast<Runtime::CompilerServices::ITuple>(object);
        if (tuple && tuple->get_Length() == sizeof...(Subs))
        {
            return System::Details::check(subs, TupleInterfaceChecker{*tuple});
        }
        return false;
    }

    /// @brief Matches against any object that supports Deconstruct.
    /// Calls Deconstruct to extract fields and applies sub-patterns.
    /// @tparam E Type of the deconstructible object.
    /// @param e Input object.
    /// @return true if all deconstructed fields match their sub-patterns.
    template <typename E>
    bool check(const E& e) const
    {
        Details::DeconstructTuple<E> e_tuple;
        System::Details::apply([&](auto&... args) { const_cast<E&>(e).Deconstruct(args...); }, e_tuple);

        return System::Details::check(subs, StdTupleChecker<decltype(e_tuple)>{e_tuple});
    }

    /// @brief Dereferences and matches a shared pointer to an object.
    /// @tparam E Pointed-to type.
    /// @param e Shared pointer to match.
    /// @return Result of matching *e.
    template <typename E>
    bool check(const SharedPtr<E>& e) const
    {
        return check(*e);
    }

    std::tuple<Subs...> subs; ///< Tuple of sub-patterns for each position.

private:
    /// @brief Helper to apply sub-patterns to an ITuple interface.
    struct TupleInterfaceChecker
    {
        const System::Runtime::CompilerServices::ITuple& tuple;

        /// @brief Checks a single element of the ITuple at compile-time index.
        /// @tparam Index Position in the tuple.
        /// @tparam T Type of the sub-pattern.
        /// @param arg Sub-pattern to apply.
        /// @return Result of arg.check(tuple[Index]).
        template <std::size_t Index, typename A>
        bool check(const A& arg) const
        {
            return arg.check(tuple.idx_get(Index));
        }
    };

    /// @brief Helper to apply sub-patterns to a std::tuple.
    /// @tparam T Type of the std::tuple.
    template <typename T>
    struct StdTupleChecker
    {
        const T& tuple;

        /// @brief Checks a single element of the std::tuple at compile-time index.
        /// @tparam Index Position in the tuple.
        /// @tparam T Type of the sub-pattern.
        /// @param arg Sub-pattern to apply.
        /// @return Result of arg.check(std::get<Index>(tuple)).
        template <std::size_t Index, typename A>
        bool check(const A& arg) const
        {
            return arg.check(std::get<Index>(tuple));
        }
    };
};

/// @brief Wildcard pattern that matches anything.
/// Serves as the entry point for pattern construction via operators.
struct Discard : Pattern
{
    /// @brief Always matches any input.
    /// @tparam E Type of the input.
    /// @param e Input value (ignored).
    /// @return Always true.
    template <typename E>
    static bool check(const E& e)
    {
        return true;
    }

    /// @brief Creates a variable binding pattern.
    /// Syntax: _[var]
    /// @tparam V Type of the variable.
    /// @param v Reference to bind to.
    /// @return Var<V> pattern.
    template <typename V>
    auto operator[](V& v) const
    {
        return Patterns::Var<V>(v);
    }

    /// @brief Creates a positional pattern.
    /// Syntax: _(p1, p2, ...)
    /// @tparam Subs... Types of sub-patterns.
    /// @param subs Sub-patterns for each position.
    /// @return Positional<Subs...> pattern.
    template <typename... Subs>
    auto operator()(Subs... subs) const
    {
        return Patterns::Positional<Subs...>(subs...);
    }

    /// @brief Creates a type-checking pattern.
    /// Syntax: _.Is<T>()
    /// @tparam T Expected type.
    /// @return Is<T> pattern.
    template <typename T>
    static auto Is()
    {
        return Patterns::Is<T>();
    }

    /// @brief Creates a type-checking and binding pattern.
    /// Syntax: _.Is<T>(var)
    /// @tparam T Expected type.
    /// @tparam V Type of the variable to bind to.
    /// @param v Reference to bind the casted value to.
    /// @return IsDeclaration<T, V> pattern.
    template <typename T, typename V>
    static auto Is(V& v)
    {
        return Patterns::IsDeclaration<T, V>(v);
    }
};

/// @brief Global instance of Discard for convenient pattern syntax.
static const Discard _;

/// @brief Equality operator for pattern construction.
/// Syntax: _== value
/// @tparam C Type of the value.
/// @param c Value to compare against.
/// @return Equal<C> pattern.
template <typename C>
auto operator==(const Discard, C c)
{
    return Patterns::Equal<C>(c);
}

/// @brief Less-than operator for pattern construction.
/// Syntax: _< value
/// @tparam C Type of the value.
/// @param c Value to compare against.
/// @return Less<C> pattern.
template <typename C>
auto operator<(const Discard, C c)
{
    return Patterns::Less<C>(c);
}

/// @brief Greater-than operator for pattern construction.
/// Syntax: _> value
/// @tparam C Type of the value.
/// @param c Value to compare against.
/// @return Greater<C> pattern.
template <typename C>
auto operator>(const Discard, C c)
{
    return Patterns::Greater<C>(c);
}

/// @brief Less-than-or-equal operator for pattern construction.
/// Syntax: _<= value
/// @tparam C Type of the value.
/// @param c Value to compare against.
/// @return LEqual<C> pattern.
template <typename C>
auto operator<=(const Discard, C c)
{
    return Patterns::LEqual<C>(c);
}

/// @brief Greater-than-or-equal operator for pattern construction.
/// Syntax: _>= value
/// @tparam C Type of the value.
/// @param c Value to compare against.
/// @return GEqual<C> pattern.
template <typename C>
auto operator>=(const Discard, C c)
{
    return Patterns::GEqual<C>(c);
}

/// @brief Logical AND operator for patterns.
/// Syntax: pattern1 && pattern2
/// @tparam A1 First pattern type.
/// @tparam A2 Second pattern type.
/// @param a1 First pattern.
/// @param a2 Second pattern.
/// @return And<A1, A2> pattern.
template <typename A1, typename A2>
std::enable_if_t<std::is_base_of<Pattern, A1>::value && std::is_base_of<Pattern, A2>::value,
                 typename Patterns::And<A1, A2>>
    operator&&(const A1& a1, const A2& a2)
{
    return Patterns::And<A1, A2>(a1, a2);
}

/// @brief Logical OR operator for patterns.
/// Syntax: pattern1 || pattern2
/// @tparam A1 First pattern type.
/// @tparam A2 Second pattern type.
/// @param a1 First pattern.
/// @param a2 Second pattern.
/// @return Or<A1, A2> pattern.
template <typename A1, typename A2>
std::enable_if_t<std::is_base_of<Pattern, A1>::value && std::is_base_of<Pattern, A2>::value,
                 typename Patterns::Or<A1, A2>>
    operator||(const A1& a1, const A2& a2)
{
    return Patterns::Or<A1, A2>(a1, a2);
}

/// @brief Logical NOT operator for patterns.
/// Syntax: !pattern
/// @tparam A Pattern type.
/// @param a Pattern to negate.
/// @return Not<A> pattern.
template <typename A>
std::enable_if_t<std::is_base_of<Pattern, A>::value, typename Patterns::Not<A>> operator!(const A& a)
{
    return Patterns::Not<A>(a);
}

/// @brief Member function call operator for non-const methods.
/// Syntax: &Class::method% subpattern
/// @tparam Obj Class type.
/// @tparam RV Return type of method.
/// @tparam A Sub-pattern type.
/// @param getter Pointer to non-const member function.
/// @param a Sub-pattern for the result.
/// @return Method<Obj, RV, A> pattern.
template <typename Obj, typename RV, typename A>
auto operator%(RV (Obj::*getter)(), A a)
{
    return Patterns::Method<Obj, RV, A>(getter, a);
}

/// @brief Member function call operator for const methods.
/// Syntax: &Class::method% subpattern
/// @tparam Obj Class type.
/// @tparam RV Return type of method.
/// @tparam A Sub-pattern type.
/// @param getter Pointer to const member function.
/// @param a Sub-pattern for the result.
/// @return ConstMethod<Obj, RV, A> pattern.
template <typename Obj, typename RV, typename A>
auto operator%(RV (Obj::*getter)() const, A a)
{
    return Patterns::ConstMethod<Obj, RV, A>(getter, a);
}

}} // namespace Details::Patterns

/// @brief Top-level matching function.
/// Applies a pattern to a value.
/// @tparam A Pattern type (must inherit from Details::Pattern).
/// @tparam E Type of the value to match.
/// @param e Value to match against.
/// @param a Pattern to apply.
/// @return true if the pattern matches the value.
template <typename A, typename E>
std::enable_if_t<std::is_base_of<Details::Pattern, A>::value, bool>
Is(const E& e, const A& a)
{
    return a.check(e);
}

}

///@brief Uses discard pattern in global scope to shorten pattern declaration code
using System::Details::Patterns::_;
