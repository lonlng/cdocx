/// @file system/comparison.h
/// Contains declaration of System::Comparison class.

#ifndef _aspose_system_comparison_h_
#define _aspose_system_comparison_h_

#include "system/multicast_delegate.h"

namespace System {
/// Represents a pointer to the method that compares two objects of the same type.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
/// @code
/// #include "system/comparison.h"
/// #include "system/console.h"
/// #include "system/exceptions.h"
/// #include "system/string.h"
/// #include <algorithm>
/// #include <initializer_list>
/// #include <vector>
///
/// using namespace System;
///
/// // The template class that represents a dynamic array.
/// template <typename T>
/// class MyArray
/// {
///   // Used to store the array data.
///   std::vector<T> m_data;
///
/// public:
///   // Constructs a new instance of our dynamic array.
///   MyArray(const std::initializer_list<T>& source) : m_data(source) {};
///
///   // Used to sort the array data. This method accepts an instance of the
///   // 'System::Comparison' template class.
///   void Sort(Comparison<T> comparison)
///   {
///     if (comparison.IsNull())
///     {
///       throw ArgumentNullException(u"comparison");
///     }
///     std::sort(m_data.begin(), m_data.end(), comparison);
///   }
///
///   // Returns a number of elements that our dynamic array stores.
///   size_t get_Size()
///   {
///     return m_data.size();
///   }
///
///   // Used to get an element at the specified index.
///   T& operator[](int index)
///   {
///     if (index < 0 || index >= m_data.size())
///     {
///       throw IndexOutOfRangeException(u"index");
///     }
///     return m_data[index];
///   }
/// };
///
/// int main() {
///   // Create an instance of the MyArray class with the specified elements.
///   MyArray<String> arr = {u"a", u"e", u"c", u"b", u"d"};
///
///   // Sort by ascending elements of the dynamic array.
///   arr.Sort([](const String &a, const String &b) -> int
///   {
///     return String::Compare(a, b);
///   });
///
///   // Print elements of the dynamic array.
///   for (auto i = 0; i < arr.get_Size(); ++i)
///   {
///     Console::WriteLine(arr[i]);
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// a
/// b
/// c
/// d
/// e
/// */
/// @endcode
/// @tparam T The type of the objects the method compares
template <typename T>
class Comparison : public System::MulticastDelegate<int(T, T)>
{
public:
    /// Constructs an instance of Comparison delegate that represent the pointer to the specified invokable entity.
    /// @tparam Y The type of the invokable entity to be pointed to by the Comparison object being created
    /// @param arg An invokable entity to be pointed to by the Comparison object being created
    template<typename Y>
    Comparison(Y arg) : System::MulticastDelegate<int(T, T)>(arg) { }
    
    /// Invokes the invokable object pointed to by the current object.
    /// @param a The first comparand
    /// @param b The second comparand
    /// @returns True if @p a is less than @p b, otherwise - true
    bool operator()(T a, T b) { return MulticastDelegate<int(T, T)>::invoke(a, b) < 0; }
};
}

#endif
