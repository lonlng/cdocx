/// @file system/details/is_forwarding_of.h
#pragma once

#include <type_traits>

namespace System { namespace Details {

/// Template that checks passed template argument if it is the forwarded instance of class T
/// False by default for all arguments except the template specialization below
/// @tparam T Check @p U that it is the forwarded instance of class T
/// @tparam U Passed argument types to be checked
template <typename T, typename ...U>
struct IsForwardingOf : public std::false_type {};

/// Template specialization that checks passed template argument if it is the forwarded instance of class T
/// @tparam T Check @p U that it is the forwarded instance of class T
/// @tparam U Passed argument type to be checked
template <typename T, typename U>
struct IsForwardingOf<T, U> : public std::integral_constant<bool, std::is_same<typename std::remove_cv<typename std::remove_reference<U>::type>::type, T>::value> {};

}}