/// @file system/predicate.h
/// Contains the declaration of System::Predicate class.
#ifndef _aspose_system_predicate_h_
#define _aspose_system_predicate_h_

#include "system/multicast_delegate.h"

namespace System
{

/// Represents a pointer to a predicate - an invokable entity that accepts a single argument and returns a bool value.
/// @code
/// #include "system/array.h"
/// #include "system/predicate.h"
/// #include <iostream>
///
/// int main()
/// {
///   // Fill the array.
///   auto arr = System::MakeArray<int>({-1, -123, 5, 3, 7});
///
///   // Create the predicate that returns an array element that is greater than 3.
///   const auto predicate = static_cast<System::Predicate<int>>([](int a) -> bool
///   {
///       return a > 3;
///   });
///
///   // Find the first element of the array using the created predicate and print it.
///   int firstItem = System::Array<int>::Find(arr, predicate);
///   std::cout << firstItem << std::endl;
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 5
/// */
/// @endcode
/// @tparam T The type of the argument accepted by the invokable entity pointed to by the Predicate delegate type.
template<class T>
using Predicate = MulticastDelegate<bool(T)>;

}

#endif
