/// @file system/make_const_ref.h
#pragma once

#include <detail.h>

#include <type_traits>

namespace System {

/// forwards
class String;
template <class T> class SmartPtr;

/// Trait to make generic type "const reference" if it is String or a SmartPtr<> type
template <typename T>
struct MakeConstRef : std::conditional<System::detail::is_a<T, System::SmartPtr>::value || std::is_same<System::String, T>::value, const T&, T> {};

/// Helper type for MakeConstRef modifier
template< class T >
using MakeConstRef_t = typename MakeConstRef<T>::type;

}