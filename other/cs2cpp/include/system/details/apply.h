/// @file system/details/apply.h
#pragma once

// C++14 std::apply implementation - http://en.cppreference.com/w/cpp/utility/apply
// Very simple implementation, without taking into account all possible types of callable

#include <utility>
#include <tuple>

namespace System { namespace Details
{

/// Invokes lambda with given argments.
/// @tparam F Lambda type.
/// @tparam Args Arguments type.
/// @param f Function to invoke.
/// @param args Arguments to pass to @p f.
/// @return @p f invocation result.
template<typename F, typename... Args>
decltype(auto) invoke_lambda(F&& f, Args&&... args)
{
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

/// Invokes lambda with arguments provided as tuple.
/// @tparam F Lambda type.
/// @tparam Tuple Tuple type containing function arguments.
/// @tparam I Order of indexes to pass to @p f.
/// @param f Function to invoke.
/// @param t Tuple of @p f arguments.
/// @return @p f invocation result.
template <class F, class Tuple, std::size_t... I>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
{
    return invoke_lambda(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
}

/// Invokes lambda with arguments provided as tuple.
/// @tparam F Lambda type.
/// @tparam Tuple Tuple type containing function arguments.
/// @param f Function to invoke.
/// @param t Tuple of @p f arguments.
/// @return @p f invocation result.
template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return apply_impl(
        std::forward<F>(f), std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>::value>{});
}

/// @brief Recursive helper function to check all elements of a tuple against a predicate.
/// Base case: when the index I reaches the size of the tuple, matching succeeds.
/// @tparam I Current index in the tuple (default: 0).
/// @tparam Tuple Type of the tuple being checked.
/// @tparam Pred Type of the predicate providing the check<I>(element) method.
/// @param t Reference to the tuple (unused in base case).
/// @param pred Reference to the predicate (unused in base case).
/// @return Always true, indicating successful match of all elements.
template <std::size_t I = 0, typename Tuple, typename Pred>
typename std::enable_if<I == std::tuple_size<Tuple>::value, bool>::type check_impl(const Tuple&, const Pred&)
{
    return true;
}

/// @brief Recursive helper function to check all elements of a tuple against a predicate.
/// Recursive case: checks the I-th element and proceeds to the next.
/// @tparam I Current index in the tuple (default: 0).
/// @tparam Tuple Type of the tuple being checked.
/// @tparam Pred Type of the predicate providing the check<I>(element) method.
/// @param t Reference to the tuple to inspect.
/// @param pred Reference to the predicate that validates each element.
/// @return true if the I-th element matches and all subsequent elements match recursively; false otherwise.
template <std::size_t I = 0, typename Tuple, typename Pred>
    typename std::enable_if < I<std::tuple_size<Tuple>::value, bool>::type check_impl(const Tuple& t, const Pred& pred)
{
    if (!pred.template check<I>(std::get<I>(t)))
        return false;

    return check_impl<I + 1>(t, pred);
}

/// @brief Entry-point function to validate all elements of a tuple using a predicate with indexed checks.
/// Iterates over the tuple at compile time and applies pred.check<I>(element) to each position.
/// @tparam Tuple Type of the tuple to check (must be a std::tuple or tuple-like with std::get support).
/// @tparam Pred Type of the predicate; must provide a template method check<I>(const Element&) const.
/// @param t The tuple whose elements are to be validated.
/// @param pred The predicate object that defines matching logic per index.
/// @return true if all elements satisfy their respective indexed checks; false otherwise.
template <typename Tuple, typename Pred>
bool check(const Tuple& t, const Pred& pred)
{
    return check_impl(t, pred);
}

}}
