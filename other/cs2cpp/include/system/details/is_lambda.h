/// @file system/details/is_lambda.h
#pragma once

#include <type_traits>
#include "defines.h"

namespace System { namespace Details {

/// Checks if type is lambda and follows [](){} semantics.
template<typename T>
using is_lambda_void_void = std::integral_constant<bool, std::is_void<ResultOf<T>>::value>;

/// Checks if type is lambda and follows [](bool&){} semantics.
template<typename T>
using is_lambda_void_boolref = std::integral_constant<bool, std::is_void<ResultOf<T, bool&>>::value>;

/// Checks if type is lambda and follows [](bool&) -> type {} semantics.
template<typename T, typename RV = ResultOf<T, bool&>>
using is_lambda_nonovoid_boolref = std::integral_constant<bool, !std::is_void<RV>::value>;

/// Checks if type is lambda and follows [](const R&) {} semantics.
template<typename T, typename R>
using is_lambda_void_arg = std::integral_constant<bool, std::is_void<ResultOf<T, const R&>>::value>;

/// Checks if type is lambda and follows [](bool&, const R&) {} semantics.
template<typename T, typename R>
using is_lambda_void_bool_arg = std::integral_constant<bool, std::is_void<ResultOf<T, bool&, const R&>>::value>;

/// Checks if type is lambda and follows [](bool&, const R&) -> type {} semantics.
template<typename T, typename R, typename RV = ResultOf<T, bool&, const R&>>
using is_lambda_nonvoid_bool_arg = std::integral_constant<bool, !std::is_void<RV>::value>;

}}
