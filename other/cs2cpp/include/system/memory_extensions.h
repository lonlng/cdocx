/// @file system/memory_extensions.h
#ifndef _aspose_system_memory_extensions_h_
#define _aspose_system_memory_extensions_h_

#include <type_traits>
#include <array>
#include <system/span.h>
#include <system/object.h>
#include <system/object_ext.h>
#include <system/details/stack_array.h>
#include <system/smart_ptr.h>
#include <system/exceptions.h>
#include <system/comparison.h>

namespace System {

/// @brief Provides extension methods for memory operations on spans and arrays.
namespace MemoryExtensions {
namespace Details {
/// @brief Default whitespace characters used for trimming operations
extern ASPOSECPP_SHARED_API const std::array<char16_t, 22> DefaultWhitespaceChars;

/// @brief Static ReadOnlySpan for default whitespace characters to avoid array creation
extern ASPOSECPP_SHARED_API const ReadOnlySpan<char16_t> DefaultWhitespaceSpan;

/// @brief Compares two smart pointers
/// @tparam T Type of first smart pointer
/// @tparam U Type of second smart pointer
/// @param a First smart pointer
/// @param b Second smart pointer
/// @return Comparison result (0 if equal, -1 if a < b, 1 if a > b)
template <typename T, typename U>
int32_t Compare(const SharedPtr<T>& a, const SharedPtr<U>& b)
{
    if (!a && !b)
    {
        return 0;
    }
    if (!a)
    {
        return -1;
    }
    if (!b)
    {
        return 1;
    }
    // assume T implements IComparable<Ptr<U>>
    return (*a).CompareTo(b);
}

/// @brief Compares two arithmetic values
/// @tparam T Arithmetic type
/// @param a First value
/// @param b Second value
/// @return Comparison result (0 if equal, -1 if a < b, 1 if a > b)
template <typename T>
int32_t // typename std::enable_if<std::is_arithmetic<T>::value, int32_t>::type
    Compare(const T& a, const T& b)
{
    return System::Compare(a, b);
}

/// @brief Compares a smart pointer with a value
/// @tparam T Type pointed to by smart pointer
/// @tparam U Type of value
/// @param a Smart pointer
/// @param b Value
/// @return Comparison result (0 if equal, -1 if a < b, 1 if a > b)
template <typename T, typename U>
int32_t Compare(const SharedPtr<T>& a, const U& b)
{
    // assume T implements IComparable<U>
    return (*a).CompareTo(b);
}

/// @brief Finds the last index of a value in a span
/// @tparam T Type of elements in span
/// @param searchSpace Span to search
/// @param length Length to search within
/// @param value Value to find
/// @return Last index of the value, or -1 if not found
template <typename T>
int32_t LastIndexOfImpl(const ReadOnlySpan<T>& searchSpace, int32_t length, const T& value)
{
    // TODO if value is null find null
    if (length < 0)
        return -1;

    while (length >= 8)
    {
        length -= 8;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 7)))
            return length + 7;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 6)))
            return length + 6;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 5)))
            return length + 5;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 4)))
            return length + 4;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 3)))
            return length + 3;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 2)))
            return length + 2;
        if (System::ObjectExt::Equals(value, searchSpace.get(length + 1)))
            return length + 1;
        if (System::ObjectExt::Equals(value, searchSpace.get(length)))
            return length;
    }

    while (length > 0)
    {
        length--;
        if (System::ObjectExt::Equals(value, searchSpace.get(length)))
        {
            return length;
        }
    }

    return -1;
}

/// @brief Checks if two spans are equal starting from specified positions
/// @tparam T Type of elements in spans
/// @param first First span
/// @param start Starting index in first span
/// @param length Number of elements to compare
/// @param second Second span
/// @return true if the specified ranges are equal, false otherwise
template <typename T>
bool SequenceEqualImpl(const ReadOnlySpan<T>& first, const int32_t start, int32_t length, const ReadOnlySpan<T>& second)
{
    int32_t index = 0;

    // Process 8 elements at a time
    while (length >= 8)
    {
        if (!(System::ObjectExt::Equals(first.get(index + start), second.get(index))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 1), second.get(index + 1))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 2), second.get(index + 2))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 3), second.get(index + 3))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 4), second.get(index + 4))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 5), second.get(index + 5))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 6), second.get(index + 6))) ||
            !(System::ObjectExt::Equals(first.get(index + start + 7), second.get(index + 7))))
        {
            return false;
        }

        index += 8;
        length -= 8;
    }

    // Process remaining elements one by one
    while (length > 0)
    {
        if (!(System::ObjectExt::Equals(first.get(index + start), second.get(index))))
        {
            return false;
        }
        index++;
        length--;
    }
    return true;
}

/// @brief Internal implementation of introsort algorithm for key-value pairs
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to sort
/// @param values The span of values to sort
/// @param depthLimit Maximum recursion depth before switching to heapsort
/// @param comparer Comparison function for keys
template <typename TKey, typename TValue>
void IntroSort(Span<TKey>& keys, Span<TValue>& values, int32_t depthLimit,
               std::function<int32_t(const TKey&, const TKey&)> comparer)
{
    int32_t partitionSize = keys.get_Length();
    while (partitionSize > 1)
    {
        if (partitionSize <= 16)
        { // IntrosortSizeThreshold = 16
            if (partitionSize == 2)
            {
                SwapIfGreaterWithValues(keys, values, comparer, 0, 1);
                return;
            }

            if (partitionSize == 3)
            {
                SwapIfGreaterWithValues(keys, values, comparer, 0, 1);
                SwapIfGreaterWithValues(keys, values, comparer, 0, 2);
                SwapIfGreaterWithValues(keys, values, comparer, 1, 2);
                return;
            }

            InsertionSort(keys, values, comparer);
            return;
        }

        if (depthLimit == 0)
        {
            HeapSort(keys, values, comparer);
            return;
        }
        depthLimit--;

        int32_t p = PickPivotAndPartition(keys, values, comparer);

        // Handle the case where pivot is at the end
        int32_t rightSize = partitionSize - p - 1;
        if (rightSize > 0)
        {
            IntroSort(keys.Slice(p + 1, rightSize), values.Slice(p + 1, rightSize), depthLimit, comparer);
        }

        // Handle the case where pivot is at the beginning
        partitionSize = p;
    }
}

/// @brief Swaps key-value pairs if comparison condition is met
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys
/// @param values The span of values
/// @param comparer Comparison function for keys
/// @param i First index to compare
/// @param j Second index to compare
template <typename TKey, typename TValue>
void SwapIfGreaterWithValues(Span<TKey>& keys, Span<TValue>& values,
                             std::function<int32_t(const TKey&, const TKey&)> comparer, int32_t i, int32_t j)
{
    if (comparer(keys.get(i), keys.get(j)) > 0)
    {
        std::swap(keys.get(i), keys.get(j));
        std::swap(values.get(i), values.get(j));
    }
}

/// @brief Performs insertion sort on key-value pairs
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to sort
/// @param values The span of values to sort
/// @param comparer Comparison function for keys
template <typename TKey, typename TValue>
void InsertionSort(Span<TKey>& keys, Span<TValue>& values, std::function<int32_t(const TKey&, const TKey&)> comparer)
{
    for (int32_t i = 0; i < keys.get_Length() - 1; i++)
    {
        TKey t = keys.get(i + 1);
        TValue tValue = values.get(i + 1);

        int32_t j = i;
        while (j >= 0 && keys.get(j) != t && !comparer(t, keys.get(j)))
        {
            keys.get(j + 1) = keys.get(j);
            values.get(j + 1) = values.get(j);
            j--;
        }

        keys.get(j + 1) = t;
        values.get(j + 1) = tValue;
    }
}

/// @brief Performs heap sort on key-value pairs
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to sort
/// @param values The span of values to sort
/// @param comparer Comparison function for keys
template <typename TKey, typename TValue>
void HeapSort(Span<TKey>& keys, Span<TValue>& values, std::function<int32_t(const TKey&, const TKey&)> comparer)
{
    // Build max heap
    for (int32_t i = keys.get_Length() / 2 - 1; i >= 0; i--)
    {
        Heapify(keys, values, keys.get_Length(), i, comparer);
    }

    // Extract elements from heap one by one
    for (int32_t i = keys.get_Length() - 1; i > 0; i--)
    {
        std::swap(keys.get(0), keys.get(i));
        std::swap(values.get(0), values.get(i));
        Heapify(keys, values, i, 0, comparer);
    }
}

/// @brief Maintains heap property for key-value pairs
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys in the heap
/// @param values The span of values in the heap
/// @param n Size of the heap
/// @param i Index to heapify from
/// @param comparer Comparison function for keys
template <typename TKey, typename TValue>
void Heapify(Span<TKey>& keys, Span<TValue>& values, int32_t n, int32_t i,
             std::function<int32_t(const TKey&, const TKey&)> comparer)
{
    int32_t largest = i;
    int32_t left = 2 * i + 1;
    int32_t right = 2 * i + 2;

    if (left < n && comparer(keys.get(left), keys.get(largest)) > 0)
    {
        largest = left;
    }

    if (right < n && comparer(keys.get(right), keys.get(largest)) > 0)
    {
        largest = right;
    }

    if (largest != i)
    {
        std::swap(keys.get(i), keys.get(largest));
        std::swap(values.get(i), values.get(largest));
        Heapify(keys, values, n, largest, comparer);
    }
}

/// @brief Selects pivot and partitions key-value pairs for quicksort
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to partition
/// @param values The span of values to partition
/// @param comparer Comparison function for keys
/// @return The pivot index after partitioning
template <typename TKey, typename TValue>
int32_t PickPivotAndPartition(Span<TKey>& keys, Span<TValue>& values,
                              std::function<int32_t(const TKey&, const TKey&)> comparer)
{
    // Use median-of-three pivot selection
    int32_t middle = keys.get_Length() / 2;
    int32_t last = keys.get_Length() - 1;

    // Sort first, middle, last
    if (comparer(keys.get(0), keys.get(middle)) > 0)
    {
        std::swap(keys.get(0), keys.get(middle));
        std::swap(values.get(0), values.get(middle));
    }
    if (comparer(keys.get(0), keys.get(last)) > 0)
    {
        std::swap(keys.get(0), keys.get(last));
        std::swap(values.get(0), values.get(last));
    }
    if (comparer(keys.get(middle), keys.get(last)) > 0)
    {
        std::swap(keys.get(middle), keys.get(last));
        std::swap(values.get(middle), values.get(last));
    }

    // Place pivot at last position
    std::swap(keys.get(middle), keys.get(last));
    std::swap(values.get(middle), values.get(last));

    TKey pivot = keys.get(last);
    int32_t i = -1;

    for (int32_t j = 0; j < last; j++)
    {
        if (comparer(keys.get(j), pivot) <= 0)
        {
            i++;
            std::swap(keys.get(i), keys.get(j));
            std::swap(values.get(i), values.get(j));
        }
    }

    std::swap(keys.get(i + 1), keys.get(last));
    std::swap(values.get(i + 1), values.get(last));
    return i + 1;
}

/// @brief Common binary search implementation
/// @tparam T Type of elements in span
/// @tparam TValue Type of value to search for
/// @tparam TCompareFunc Function type for comparison
/// @param span The span to search
/// @param value The value to search for
/// @param compareFunc Function that compares value with span element and returns int32_t (-1, 0, 1)
/// @return Index of found element or bitwise complement of insertion point
template <typename T, typename TValue, typename TCompareFunc>
int32_t BinarySearchImpl(const ReadOnlySpan<T>& span, const TValue& value, TCompareFunc compareFunc)
{
    int32_t lo = 0;
    int32_t hi = span.get_Length() - 1;

    while (lo <= hi)
    {
        // Safe unsigned arithmetic to avoid overflow
        int32_t i = static_cast<int32_t>((static_cast<uint32_t>(hi) + static_cast<uint32_t>(lo)) >> 1);
        int32_t c = compareFunc(value, span.get(i));
        if (c == 0)
        {
            return i;
        }
        else if (c > 0)
        {
            lo = i + 1;
        }
        else
        {
            hi = i - 1;
        }
    }

    return ~lo;
}

} // namespace Details

/// @brief Creates a read-only span from a string.
/// @param text The source string.
/// @param start The starting index in the string.
/// @param length The length of the span.
/// @return ReadOnlySpan<char16_t> spanning the specified portion of the string.
ASPOSECPP_SHARED_API ReadOnlySpan<char16_t> AsSpan(const String& text, int32_t start = 0, int32_t length = -1);

/// @brief Creates a span from an array.
/// @tparam T The type of elements in the array.
/// @param array The source array.
/// @param start The starting index in the array.
/// @param length The length of the span.
/// @return Span<T> spanning the specified portion of the array.
template <typename T>
Span<T> AsSpan(const ArrayPtr<T>& array, int32_t start = 0, int32_t length = -1)
{
    if (array == nullptr)
    {
        throw ArgumentNullException(u"array is null");
    }
    if (start < 0 || (length < 0 && length != -1) ||
        (length == -1 ? start > array->get_Length() : start + length > array->get_Length()))
    {
        throw ArgumentOutOfRangeException(u"start or length is out of range");
    }
    if (length == -1)
    {
        length = array->get_Length() - start;
    }
    return Span<T>(array, start, length);
}

/// @brief Performs binary search on a sorted span
/// @tparam T The type of elements in the span
/// @tparam TComparable The type of the comparable value
/// @param span The sorted span to search
/// @param comparable The value to search for
/// @return Index of the found element, or bitwise complement of the insertion point if not found
template <typename T, typename TComparable>
int32_t BinarySearch(const ReadOnlySpan<T>& span, const TComparable& comparable)
{
    return Details::BinarySearchImpl(span, comparable,
                                     [](const TComparable& search_value, const T& container_value) -> int32_t {
                                         return Details::Compare(search_value, container_value);
                                     });
}

/// @brief Performs binary search on a sorted span using a custom comparer
/// @tparam T The type of elements in the span
/// @tparam TComparer The type of the comparer
/// @param span The sorted span to search
/// @param value The value to search for
/// @param comparerPtr The comparer to use for comparisons
/// @return Index of the found element, or bitwise complement of the insertion point if not found
template <typename T, typename TComparer>
int32_t BinarySearch(const ReadOnlySpan<T>& span, const T& value, const SharedPtr<TComparer>& comparerPtr)
{
    return Details::BinarySearchImpl(span, value,
                                     [&comparerPtr](const T& search_value, const T& container_value) -> int32_t {
                                         return comparerPtr->Compare(search_value, container_value);
                                     });
}

/// @brief Performs binary search on a mutable sorted span
/// @tparam T The type of elements in the span
/// @tparam TComparable The type of the comparable value
/// @param span The sorted span to search
/// @param comparable The value to search for
/// @return Index of the found element, or bitwise complement of the insertion point if not found
template <typename T, typename TComparable>
int32_t BinarySearch(const Span<T>& span, const TComparable& comparable)
{
    return BinarySearch(static_cast<ReadOnlySpan<T>>(span), comparable);
}

/// @brief Performs binary search on a mutable sorted span using a custom comparer
/// @tparam T The type of elements in the span
/// @tparam TComparer The type of the comparer
/// @param span The sorted span to search
/// @param value The value to search for
/// @param comparer The comparer to use for comparisons
/// @return Index of the found element, or bitwise complement of the insertion point if not found
template <typename T, typename TComparer>
int32_t BinarySearch(const Span<T>& span, const T& value, const SharedPtr<TComparer>& comparer)
{
    return BinarySearch(static_cast<ReadOnlySpan<T>>(span), value, comparer);
}

/// @brief Finds the length of the common prefix between two spans
/// @tparam T The type of elements in the spans
/// @param span The first span
/// @param other The second span
/// @return The number of matching elements at the beginning of both spans
template <typename T>
int32_t CommonPrefixLength(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other)
{
    int32_t commonLength = 0;
    int32_t minLength = std::min(span.get_Length(), other.get_Length());

    // Compare elements until a mismatch is found
    for (int32_t i = 0; i < minLength; ++i)
    {
        if (System::ObjectExt::Equals(span.get(i), other.get(i)))
        {
            ++commonLength;
        }
        else
        {
            break; // Mismatch found, exit early
        }
    }

    return commonLength;
}

/// @brief Finds the length of the common prefix between a mutable span and a read-only span
/// @tparam T The type of elements in the spans
/// @param span The mutable span
/// @param other The read-only span
/// @return The number of matching elements at the beginning of both spans
template <typename T>
int32_t CommonPrefixLength(const Span<T>& span, const ReadOnlySpan<T>& other)
{
    return CommonPrefixLength(static_cast<ReadOnlySpan<T>>(span), other);
}

/// @brief Finds the length of the common prefix between two mutable spans
/// @tparam T The type of elements in the spans
/// @param span The first mutable span
/// @param other The second mutable span
/// @return The number of matching elements at the beginning of both spans
template <typename T>
int32_t CommonPrefixLength(const Span<T>& span, const Span<T>& other)
{
    return CommonPrefixLength(static_cast<ReadOnlySpan<T>>(span), static_cast<ReadOnlySpan<T>>(other));
}

/// @brief Finds the length of the common prefix between two spans using a custom equality comparer
/// @tparam T The type of elements in the spans
/// @tparam TEqualityComparer The type of the equality comparer
/// @param span The first span
/// @param other The second span
/// @param comparer The equality comparer to use for element comparison
/// @return The number of matching elements at the beginning of both spans
template <typename T, typename TEqualityComparer>
int32_t CommonPrefixLength(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other,
                           const SharedPtr<TEqualityComparer>& comparer)
{
    int32_t commonLength = 0;
    int32_t minLength = std::min(span.get_Length(), other.get_Length());

    // Compare elements until a mismatch is found
    for (int32_t i = 0; i < minLength; ++i)
    {
        if ((comparer == nullptr && System::ObjectExt::Equals(span.get(i), other.get(i))) ||
            (comparer != nullptr && comparer->Equals(span.get(i), other.get(i))))
        {
            ++commonLength;
        }
        else
        {
            break; // Mismatch found, exit early
        }
    }

    return commonLength;
}

/// @brief Finds the length of the common prefix between a mutable span and a read-only span using a custom equality
/// comparer
/// @tparam T The type of elements in the spans
/// @tparam TEqualityComparer The type of the equality comparer
/// @param span The mutable span
/// @param other The read-only span
/// @param comparer The equality comparer to use for element comparison
/// @return The number of matching elements at the beginning of both spans
template <typename T, typename TEqualityComparer>
int32_t CommonPrefixLength(const Span<T>& span, const ReadOnlySpan<T>& other,
                           const SharedPtr<TEqualityComparer>& comparer)
{
    return CommonPrefixLength(static_cast<ReadOnlySpan<T>>(span), other, comparer);
}

/// @brief Finds the length of the common prefix between two mutable spans using a custom equality comparer
/// @tparam T The type of elements in the spans
/// @tparam TEqualityComparer The type of the equality comparer
/// @param span The first mutable span
/// @param other The second mutable span
/// @param comparer The equality comparer to use for element comparison
/// @return The number of matching elements at the beginning of both spans
template <typename T, typename TEqualityComparer>
int32_t CommonPrefixLength(const Span<T>& span, const Span<T>& other, const SharedPtr<TEqualityComparer>& comparer)
{
    return CommonPrefixLength(static_cast<ReadOnlySpan<T>>(span), static_cast<ReadOnlySpan<T>>(other), comparer);
}

/// @brief Compares two character spans with specified string comparison rules
/// @param span The first character span
/// @param other The second character span
/// @param comparisonType The type of string comparison to perform
/// @return Negative value if span < other, zero if equal, positive if span > other
ASPOSECPP_SHARED_API int32_t CompareTo(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& other,
                                       StringComparison comparisonType);

/// @brief Checks if a character span contains another character span with specified comparison rules
/// @param span The span to search in
/// @param value The span to search for
/// @param comparisonType The type of string comparison to perform
/// @return true if value is found in span, false otherwise
ASPOSECPP_SHARED_API bool Contains(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& value,
                                   StringComparison comparisonType);

/**/

/// @brief Checks if a read-only span contains a specific value
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to search for
/// @return true if value is found in span, false otherwise
template <typename T>
bool Contains(const ReadOnlySpan<T>& span, const T& value)
{
    return std::find_if(span.begin(), span.end(), [&value](const T& item) { return System::ObjectExt::Equals(value, item); }) !=
           span.end();
}

/// @brief Checks if a mutable span contains a specific value
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value The value to search for
/// @return true if value is found in span, false otherwise
template <typename T>
bool Contains(const Span<T>& span, const T& value)
{
    return std::find(span.begin(), span.end(), value) != span.end();
}

/// @brief Checks if a read-only span contains any of two values
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return true if any of the values is found in span, false otherwise
template <typename T>
bool ContainsAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    return Contains(span, value0) || Contains(span, value1);
}

/// @brief Checks if a read-only span contains any of three values
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return true if any of the values is found in span, false otherwise
template <typename T>
bool ContainsAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    return Contains(span, value0) || Contains(span, value1) || Contains(span, value2);
}

/// @brief Checks if a mutable span contains any of two values
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return true if any of the values is found in span, false otherwise
template <typename T>
bool ContainsAny(const Span<T>& span, const T& value0, const T& value1)
{
    return ContainsAny(static_cast<const ReadOnlySpan<T>&>(span), value0, value1);
}

/// @brief Checks if a mutable span contains any of three values
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return true if any of the values is found in span, false otherwise
template <typename T>
bool ContainsAny(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return ContainsAny(static_cast<const ReadOnlySpan<T>&>(span), value0, value1, value2);
}

/// @brief Checks if a read-only span contains any value from another span
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span of values to search for
/// @return true if any value from values is found in span, false otherwise
template <typename T>
bool ContainsAny(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    for (const auto& value : values)
    {
        if (Contains(span, value))
        {
            return true; // Found at least one value
        }
    }
    return false; // Not found
}

/// @brief Checks if a mutable span contains any value from a read-only span
/// @tparam T The type of elements in the spans
/// @param span The mutable span to search in
/// @param values The read-only span of values to search for
/// @return true if any value from values is found in span, false otherwise
template <typename T>
bool ContainsAny(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return ContainsAny(static_cast<const ReadOnlySpan<T>&>(span), values);
}

/// @brief Checks if a read-only span contains any element except three specified values
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @param value2 The third value to exclude
/// @return true if any element different from the specified values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    for (auto& member : span)
    {
        if (!System::ObjectExt::Equals(member, value0) && !System::ObjectExt::Equals(member, value1) &&
            !System::ObjectExt::Equals(member, value2))
        {
            return true;
        }
    }
    return false;
}

/// @brief Checks if a mutable span contains any element except three specified values
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @param value2 The third value to exclude
/// @return true if any element different from the specified values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return ContainsAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value0, value1, value2);
}

/// @brief Checks if a read-only span contains any element except two specified values
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @return true if any element different from the specified values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    for (auto& member : span)
    {
        if (!System::ObjectExt::Equals(member, value0) && !System::ObjectExt::Equals(member, value1))
        {
            return true;
        }
    }
    return false;
}

/// @brief Checks if a mutable span contains any element except two specified values
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @return true if any element different from the specified values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const Span<T>& span, const T& value0, const T& value1)
{
    return ContainsAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value0, value1);
}

/// @brief Checks if a read-only span contains any element except a specified value
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to exclude
/// @return true if any element different from the specified value is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const ReadOnlySpan<T>& span, const T& value)
{
    for (auto& member : span)
    {
        if (!System::ObjectExt::Equals(member, value))
        {
            return true;
        }
    }
    return false;
}

/// @brief Checks if a mutable span contains any element except a specified value
/// @tparam T The type of elements in the span
/// @param span The mutable span to search in
/// @param value The value to exclude
/// @return true if any element different from the specified value is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const Span<T>& span, const T& value)
{
    return ContainsAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value);
}

/// @brief Checks if a read-only span contains any element except those in another span
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span of values to exclude
/// @return true if any element not in values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    switch (values.get_Length())
    {
    case 0:
        return span.get_IsEmpty() ? false : true;

    case 1:
        return ContainsAnyExcept(span, values.get(0));

    case 2:
        return ContainsAnyExcept(span, values.get(0), values.get(1));

    case 3:
        return ContainsAnyExcept(span, values.get(0), values.get(1), values.get(2));

    default:
        for (auto& member : span)
        {
            if (!Contains(values, member))
            {
                return true;
            }
        }
        return false;
    }
}

/// @brief Checks if a mutable span contains any element except those in a read-only span
/// @tparam T The type of elements in the spans
/// @param span The mutable span to search in
/// @param values The read-only span of values to exclude
/// @return true if any element not in values is found, false otherwise
template <typename T>
bool ContainsAnyExcept(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return ContainsAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), values);
}

/// @brief Checks if a read-only span contains any element outside the specified range
/// @tparam T The type of elements in the span (must be comparable)
/// @param span The span to search in
/// @param lowInclusive The lower bound (inclusive)
/// @param highInclusive The upper bound (inclusive)
/// @return true if any element outside the range is found, false otherwise
template <typename T>
bool ContainsAnyExceptInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (const auto& value : span)
    {
        if (value < lowInclusive || value > highInclusive)
        {
            return true; // Found a value outside the range
        }
    }
    return false; // All values are within the range
}

/// @brief Checks if a mutable span contains any element outside the specified range
/// @tparam T The type of elements in the span (must be comparable)
/// @param span The mutable span to search in
/// @param lowInclusive The lower bound (inclusive)
/// @param highInclusive The upper bound (inclusive)
/// @return true if any element outside the range is found, false otherwise
template <typename T>
bool ContainsAnyExceptInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (const auto& value : span)
    {
        if (value < lowInclusive || value > highInclusive)
        {
            return true; // Found a value outside the range
        }
    }
    return false; // All values are within the range
}

/// @brief Checks if a read-only span contains any element within the specified range
/// @tparam T The type of elements in the span (must be comparable)
/// @param span The span to search in
/// @param lowInclusive The lower bound (inclusive)
/// @param highInclusive The upper bound (inclusive)
/// @return true if any element within the range is found, false otherwise
template <typename T>
bool ContainsAnyInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (const auto& value : span)
    {
        if (value >= lowInclusive && value <= highInclusive)
        {
            return true; // Found a value within the range
        }
    }
    return false; // No values found within the range
}

/// @brief Checks if a mutable span contains any element within the specified range
/// @tparam T The type of elements in the span (must be comparable)
/// @param span The mutable span to search in
/// @param lowInclusive The lower bound (inclusive)
/// @param highInclusive The upper bound (inclusive)
/// @return true if any element within the range is found, false otherwise
template <typename T>
bool ContainsAnyInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (const auto& value : span)
    {
        if (value >= lowInclusive && value <= highInclusive)
        {
            return true; // Found a value within the range
        }
    }
    return false; // No values found within the range
}

/// @brief Copies elements from an array to a span
/// @tparam T The type of elements in the array and span
/// @param source The source array
/// @param destination The destination span
template <typename T>
void CopyTo(const ArrayPtr<T>& source, Span<T>& destination)
{
    return ReadOnlySpan<T>(source).CopyTo(destination);
}

/// @brief Counts occurrences of a value in a read-only span
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to count
/// @return The number of times value appears in span
template <typename T>
int32_t Count(const ReadOnlySpan<T>& span, const T& value)
{
    int32_t count = 0;
    for (const auto& item : span)
    {
        if (System::ObjectExt::Equals(item, value))
        {
            ++count;
        }
    }
    return count;
}

/// @brief Counts occurrences of a span within another read-only span
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param value The span to count occurrences of
/// @return The number of times value appears in span
template <typename T>
int32_t Count(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& value)
{
    switch (value.get_Length())
    {
    case 0:
        return 0;

    case 1:
        return Count(span, value.get(0));

    default:
        int32_t count = 0;
        int32_t pos = 0;
        ReadOnlySpan<T> currentSpan = span;
        while ((pos = IndexOf(currentSpan, value)) >= 0)
        {
            count++;
            currentSpan = currentSpan.Slice(pos + value.get_Length());
        }
        return count;
    }
}

/// @brief Counts occurrences of a single value in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to count occurrences of
/// @return The number of occurrences of the value in the span
template <typename T>
int32_t Count(const Span<T>& span, const T& value)
{
    return Count(ReadOnlySpan<T>(span), value); // Delegate to ReadOnlySpan<T> method
}

/// @brief Counts occurrences of a ReadOnlySpan<T> in a Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param value The span containing values to count occurrences of
/// @return The number of occurrences of the value span in the target span
template <typename T>
int32_t Count(const Span<T>& span, const ReadOnlySpan<T>& value)
{
    return Count(ReadOnlySpan<T>(span), value); // Delegate to ReadOnlySpan<T> method
}

/// @brief Determines if a ReadOnlySpan<char16_t> ends with the specified value using StringComparison
/// @param span The span to check
/// @param value The value to check for at the end of the span
/// @param comparisonType The string comparison type to use
/// @return true if the span ends with the value, false otherwise
ASPOSECPP_SHARED_API bool EndsWith(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& value,
                                   StringComparison comparisonType);

/// @brief Determines if a ReadOnlySpan<T> ends with a single value
/// @tparam T The type of elements in the span
/// @param span The span to check
/// @param value The value to check for at the end of the span
/// @return true if the span ends with the value, false otherwise
template <typename T>
bool EndsWith(const ReadOnlySpan<T>& span, const T& value)
{
    if (span.get_Length() == 0)
    {
        return false; // Empty span does not end with any value
    }
    return System::ObjectExt::Equals(span.get(span.get_Length() - 1), value);
}

/// @brief Determines if a ReadOnlySpan<T> ends with another ReadOnlySpan<T>
/// @tparam T The type of elements in the spans
/// @param span The span to check
/// @param value The span to check for at the end of the target span
/// @return true if the span ends with the value span, false otherwise
template <typename T>
bool EndsWith(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& value)
{
    int32_t spanLength = span.get_Length();
    int32_t valueLength = value.get_Length();

    if (valueLength > spanLength)
    {
        return false;
    }

    if (valueLength == spanLength)
    {
        return SequenceEqual(span, value);
    }

    return SequenceEqual(span.Slice(spanLength - valueLength), value);
}

/// @brief Determines if a Span<T> ends with a ReadOnlySpan<T>
/// @tparam T The type of elements in the spans
/// @param span The span to check
/// @param value The span to check for at the end of the target span
/// @return true if the span ends with the value span, false otherwise
template <typename T>
bool EndsWith(const Span<T>& span, const ReadOnlySpan<T>& value)
{
    return EndsWith(ReadOnlySpan<T>(span), value);
}

/// @brief Determines if a ReadOnlySpan<T> ends with a Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to check
/// @param value The span to check for at the end of the target span
/// @return true if the span ends with the value span, false otherwise
template <typename T>
bool EndsWith(const ReadOnlySpan<T>& span, const Span<T>& value)
{
    return EndsWith(span, ReadOnlySpan<T>(value));
}

/// @brief Determines if a Span<T> ends with another Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to check
/// @param value The span to check for at the end of the target span
/// @return true if the span ends with the value span, false otherwise
template <typename T>
bool EndsWith(const Span<T>& span, const Span<T>& value)
{
    return EndsWith(ReadOnlySpan<T>(span), ReadOnlySpan<T>(value));
}

/// @brief Compares two ReadOnlySpan<char16_t> for equality using StringComparison
/// @param span The first span to compare
/// @param other The second span to compare
/// @param comparisonType The string comparison type to use
/// @return true if the spans are equal, false otherwise
ASPOSECPP_SHARED_API bool Equals(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& other,
                                 StringComparison comparisonType);

/// @brief Finds the index of a ReadOnlySpan<char16_t> value in a ReadOnlySpan<char16_t> with StringComparison
/// @param span The span to search in
/// @param value The value to search for
/// @param comparisonType The string comparison type to use
/// @return The zero-based index of the first occurrence, or -1 if not found
ASPOSECPP_SHARED_API int32_t IndexOf(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& value,
                                     StringComparison comparisonType);

/// @brief Finds the index of a ReadOnlySpan<T> value in another ReadOnlySpan<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param value The span to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOf(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& value)
{
    if (value.get_Length() == 0)
    {
        return 0; // A zero-length sequence is always treated as "found" at the start of the search space.
    }

    const T& valueHead = value.get(0);
    int32_t valueTailLength = value.get_Length() - 1;

    int32_t index = 0;
    while (true)
    {
        if (index + valueTailLength > span.get_Length())
        {
            break; // The unsearched portion is now shorter than the sequence we're looking for.
        }

        // Search for the first element of "value".
        int32_t remainingSearchSpaceLength = span.get_Length() - index - valueTailLength;
        int32_t relativeIndex = -1; // Default to not found

        for (int32_t i = 0; i < remainingSearchSpaceLength; ++i)
        {
            if (System::ObjectExt::Equals(span.get(index + i), valueHead))
            {
                relativeIndex = i;
                break;
            }
        }

        if (relativeIndex == -1)
        {
            break; // First element not found.
        }

        index += relativeIndex;

        // Found the first element of "value". Check if the tail matches.
        bool tailMatches = true;
        for (int32_t i = 0; i < valueTailLength; ++i)
        {
            if (span.get(index + 1 + i) != value.get(1 + i))
            {
                tailMatches = false;
                break;
            }
        }

        if (tailMatches)
        {
            return index; // The tail matched. Return a successful find.
        }

        ++index; // Move to the next position in the search space.
    }

    return -1; // Not found.
}

/// @brief Finds the index of a single value in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOf(const ReadOnlySpan<T>& span, const T& value)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (System::ObjectExt::Equals(span.get(i), value))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of a ReadOnlySpan<T> value in a Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param value The span to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOf(const Span<T>& span, const ReadOnlySpan<T>& value)
{
    return IndexOf(static_cast<ReadOnlySpan<T>>(span), value);
}

/// @brief Finds the index of a single value in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOf(const Span<T>& span, const T& value)
{
    return IndexOf(static_cast<ReadOnlySpan<T>>(span), value);
}

/// @brief Finds the index of the first occurrence of any of two specified values in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (System::ObjectExt::Equals(span.get(i), value0) || System::ObjectExt::Equals(span.get(i), value1))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first occurrence of any of three specified values in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (System::ObjectExt::Equals(span.get(i), value0) || System::ObjectExt::Equals(span.get(i), value1) ||
            System::ObjectExt::Equals(span.get(i), value2))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first occurrence of any of two specified values in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const Span<T>& span, const T& value0, const T& value1)
{
    return IndexOfAny(static_cast<ReadOnlySpan<T>>(span), value0, value1);
}

/// @brief Finds the index of the first occurrence of any of three specified values in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return IndexOfAny(static_cast<ReadOnlySpan<T>>(span), value0, value1, value2);
}

/// @brief Finds the index of the first occurrence of any value from a span in another ReadOnlySpan<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span containing values to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        for (int32_t j = 0; j < values.get_Length(); ++j)
        {
            if (System::ObjectExt::Equals(span.get(i), values.get(j)))
            {
                return i; // Found
            }
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first occurrence of any value from a span in a Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span containing values to search for
/// @return The zero-based index of the first occurrence, or -1 if not found
template <typename T>
int32_t IndexOfAny(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return IndexOfAny(static_cast<ReadOnlySpan<T>>(span), values);
}

/// @brief Finds the index of the first element that is not equal to the specified value in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (!System::ObjectExt::Equals(span.get(i), value))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is not equal to either of two specified values in a
/// ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude from the search
/// @param value1 The second value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (!System::ObjectExt::Equals(span.get(i), value0) && !System::ObjectExt::Equals(span.get(i), value1))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is not equal to any of three specified values in a
/// ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude from the search
/// @param value1 The second value to exclude from the search
/// @param value2 The third value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (!System::ObjectExt::Equals(span.get(i), value0) && !System::ObjectExt::Equals(span.get(i), value1) &&
            !System::ObjectExt::Equals(span.get(i), value2))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is not equal to the specified value in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value The value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const Span<T>& span, const T& value)
{
    return IndexOfAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value);
}

/// @brief Finds the index of the first element that is not equal to either of two specified values in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude from the search
/// @param value1 The second value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const Span<T>& span, const T& value0, const T& value1)
{
    return IndexOfAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value0, value1);
}

/// @brief Finds the index of the first element that is not equal to any of three specified values in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param value0 The first value to exclude from the search
/// @param value1 The second value to exclude from the search
/// @param value2 The third value to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return IndexOfAnyExcept(static_cast<const ReadOnlySpan<T>&>(span), value0, value1, value2);
}

/// @brief Finds the index of the first element that is not equal to any value in a span of values
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span containing values to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        bool found = false;
        for (int32_t j = 0; j < values.get_Length(); ++j)
        {
            if (System::ObjectExt::Equals(span.get(i), values.get(j)))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is not equal to any value in a span of values in a Span<T>
/// @tparam T The type of elements in the spans
/// @param span The span to search in
/// @param values The span containing values to exclude from the search
/// @return The zero-based index of the first non-matching element, or -1 if not found
template <typename T>
int32_t IndexOfAnyExcept(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return IndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), values);
}

/// @brief Finds the index of the first element that is outside the specified range in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the first element outside the range, or -1 if not found
template <typename T>
int32_t IndexOfAnyExceptInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (Details::Compare(span.get(i), lowInclusive) < 0 || Details::Compare(span.get(i), highInclusive) > 0)
        {
            return i; // Found an element outside the range
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is outside the specified range in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the first element outside the range, or -1 if not found
template <typename T>
int32_t IndexOfAnyExceptInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    return IndexOfAnyExceptInRange(static_cast<const ReadOnlySpan<T>&>(span), lowInclusive, highInclusive);
}

/// @brief Finds the index of the first element that is within the specified range in a ReadOnlySpan<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the first element within the range, or -1 if not found
template <typename T>
int32_t IndexOfAnyInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        // if (span.get(i).CompareTo(lowInclusive) >= 0 && span.get(i).CompareTo(highInclusive) <= 0) {
        if (Details::Compare(span.get(i), lowInclusive) >= 0 && Details::Compare(span.get(i), highInclusive) <= 0)
        {
            return i; // Found an element within the range
        }
    }
    return -1; // Not found
}

/// @brief Finds the index of the first element that is within the specified range in a Span<T>
/// @tparam T The type of elements in the span
/// @param span The span to search in
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the first element within the range, or -1 if not found
template <typename T>
int32_t IndexOfAnyInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    return IndexOfAnyInRange(static_cast<const ReadOnlySpan<T>&>(span), lowInclusive, highInclusive);
}

/// @brief Checks if the entire span consists only of whitespace characters
/// @param span The span to check for whitespace
/// @return true if all characters in the span are whitespace, false otherwise
ASPOSECPP_SHARED_API bool IsWhiteSpace(const ReadOnlySpan<char16_t>& span);

/// @brief Finds the last occurrence of a value within a span using specified string comparison
/// @param span The span to search within
/// @param value The value to search for
/// @param comparisonType The type of string comparison to perform
/// @return The zero-based index of the last occurrence, or -1 if not found
ASPOSECPP_SHARED_API int32_t LastIndexOf(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& value,
                                         StringComparison comparisonType);

/// @brief Finds the last occurrence of a sequence within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The sequence to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOf(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& value)
{
    if (value.get_Length() == 0)
        return span.get_Length(); // A zero-length sequence is always treated as "found" at the end of the search space.

    int32_t valueTailLength = value.get_Length() - 1;
    if (valueTailLength == 0)
    {
        return LastIndexOf<T>(span, value.get(0));
    }

    int32_t index = 0;

    T valueHead = value.get(0);
    ReadOnlySpan<T> valueTail = value.Slice(1);

    while (true)
    {
        int32_t remainingSearchSpaceLength = span.get_Length() - index - valueTail.get_Length(); // отступ
        if (remainingSearchSpaceLength <= 0)
            break;

        // Do a quick search for the first element of "value".
        int32_t relativeIndex = Details::LastIndexOfImpl<T>(span, remainingSearchSpaceLength, valueHead);
        if (relativeIndex < 0)
            break;

        // Found the first element of "value". See if the tail matches.
        if (Details::SequenceEqualImpl<T>(span, relativeIndex + 1, valueTail.get_Length(), valueTail))
            return relativeIndex;

        index += remainingSearchSpaceLength - relativeIndex;
    }
    return -1;
}

/// @brief Finds the last occurrence of a single value within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOf(const ReadOnlySpan<T>& span, const T& value)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        if (System::ObjectExt::Equals(span.get(i), value))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of a sequence within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The sequence to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOf(const Span<T>& span, const ReadOnlySpan<T>& value)
{
    return LastIndexOf(static_cast<const ReadOnlySpan<T>&>(span), value); // Cast for use with ReadOnlySpan
}

/// @brief Finds the last occurrence of a single value within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOf(const Span<T>& span, const T& value)
{
    return LastIndexOf(static_cast<const ReadOnlySpan<T>&>(span), value); // Cast for use with ReadOnlySpan
}

/// @brief Finds the last occurrence of any of three specified values within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        if (System::ObjectExt::Equals(span.get(i), value0) || System::ObjectExt::Equals(span.get(i), value1) ||
            System::ObjectExt::Equals(span.get(i), value2))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any of three specified values within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @param value2 The third value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return LastIndexOfAny(static_cast<const ReadOnlySpan<T>&>(span), value0, value1, value2);
}

/// @brief Finds the last occurrence of any of two specified values within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        if (System::ObjectExt::Equals(span.get(i), value0) || System::ObjectExt::Equals(span.get(i), value1))
        {
            return i; // Found
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any of two specified values within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to search for
/// @param value1 The second value to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const Span<T>& span, const T& value0, const T& value1)
{
    return LastIndexOfAny(static_cast<const ReadOnlySpan<T>&>(span), value0, value1);
}

/// @brief Finds the last occurrence of any value from a sequence within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        for (int32_t j = 0; j < values.get_Length(); ++j)
        {
            if (System::ObjectExt::Equals(span.get(i), values.get(j)))
            {
                return i; // Found
            }
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any value from a sequence within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return LastIndexOfAny(static_cast<const ReadOnlySpan<T>&>(span), values);
}

/// @brief Finds the last occurrence of any value from a mutable sequence within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to search for
/// @return The zero-based index of the last occurrence, or -1 if not found
template <typename T>
int32_t LastIndexOfAny(const Span<T>& span, const Span<T>& values)
{
    return LastIndexOfAny(static_cast<const ReadOnlySpan<T>&>(span), static_cast<const ReadOnlySpan<T>&>(values));
}

/// @brief Finds the last occurrence of any element except three specified values within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @param value2 The third value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1, const T& value2)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        const T& current = span.get(i);
        if (!(System::ObjectExt::Equals(current, value0) || System::ObjectExt::Equals(current, value1) ||
              System::ObjectExt::Equals(current, value2)))
        {
            return i;
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element except three specified values within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @param value2 The third value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const Span<T>& span, const T& value0, const T& value1, const T& value2)
{
    return LastIndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), value0, value1, value2);
}

/// @brief Finds the last occurrence of any element except two specified values within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value0, const T& value1)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        const T& current = span.get(i);
        if (!(System::ObjectExt::Equals(current, value0) || System::ObjectExt::Equals(current, value1)))
        {
            return i;
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element except two specified values within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value0 The first value to exclude
/// @param value1 The second value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const Span<T>& span, const T& value0, const T& value1)
{
    return LastIndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), value0, value1);
}

/// @brief Finds the last occurrence of any element except a specified value within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const ReadOnlySpan<T>& span, const T& value)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        T current = span.get(i);
        if (!(System::ObjectExt::Equals(current, value)))
        {
            return i;
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element except a specified value within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param value The value to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const Span<T>& span, const T& value)
{
    return LastIndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), value);
}

/// @brief Finds the last occurrence of any element except values from a sequence within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& values)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        const T& current = span.get(i);
        bool found = false;
        for (auto& value : values)
        {
            if (System::ObjectExt::Equals(current, value))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            return i;
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element except values from a sequence within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const Span<T>& span, const ReadOnlySpan<T>& values)
{
    return LastIndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), values);
}

/// @brief Finds the last occurrence of any element except values from a mutable sequence within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param values The sequence of values to exclude
/// @return The zero-based index of the last non-excluded element, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExcept(const Span<T>& span, const Span<T>& values)
{
    return LastIndexOfAnyExcept(static_cast<ReadOnlySpan<T>>(span), static_cast<ReadOnlySpan<T>>(values));
}

/// @brief Finds the last occurrence of any element outside the specified range within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the last element outside the range, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExceptInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        if (Details::Compare(span.get(i), lowInclusive) < 0 || Details::Compare(span.get(i), highInclusive) > 0)
        {
            return i; // Found an element outside the range
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element outside the specified range within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the last element outside the range, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyExceptInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    return LastIndexOfAnyExceptInRange(static_cast<ReadOnlySpan<T>>(span), lowInclusive, highInclusive);
}

/// @brief Finds the last occurrence of any element within the specified range within a span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the last element within the range, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyInRange(const ReadOnlySpan<T>& span, const T& lowInclusive, const T& highInclusive)
{
    for (int32_t i = span.get_Length() - 1; i >= 0; --i)
    {
        if (Details::Compare(span.get(i), lowInclusive) >= 0 && Details::Compare(span.get(i), highInclusive) <= 0)
        {
            return i; // Found an element outside the range
        }
    }
    return -1; // Not found
}

/// @brief Finds the last occurrence of any element within the specified range within a mutable span
/// @tparam T The type of elements in the span
/// @param span The span to search within
/// @param lowInclusive The lower bound of the range (inclusive)
/// @param highInclusive The upper bound of the range (inclusive)
/// @return The zero-based index of the last element within the range, or -1 if not found
template <typename T>
int32_t LastIndexOfAnyInRange(const Span<T>& span, const T& lowInclusive, const T& highInclusive)
{
    return LastIndexOfAnyInRange(static_cast<ReadOnlySpan<T>>(span), lowInclusive, highInclusive);
}

/// @brief Determines if two ReadOnlySpans overlap in memory without calculating offset
/// @tparam T The type of elements in the spans
/// @param span The first span to check for overlap
/// @param other The second span to check for overlap
/// @return true if the spans share any common memory locations, false otherwise
template <typename T>
bool Overlaps(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other)
{
    int32_t offset;
    return Overlaps(span, other, offset);
}

/// @brief Determines if a Span and ReadOnlySpan overlap in memory without calculating offset
/// @tparam T The type of elements in the spans
/// @param span The Span to check for overlap
/// @param other The ReadOnlySpan to check for overlap
/// @return true if the spans share any common memory locations, false otherwise
template <typename T>
bool Overlaps(const Span<T>& span, const ReadOnlySpan<T>& other)
{
    return Overlaps(static_cast<ReadOnlySpan<T>>(span), other);
}

/// @brief Determines if two ReadOnlySpans overlap in memory and calculates the offset
/// @tparam T The type of elements in the spans
/// @param span The first span to check for overlap
/// @param other The second span to check for overlap
/// @param elementOffset Output parameter that receives the offset between spans if they overlap
/// @return true if the spans share any common memory locations, false otherwise
template <typename T>
bool Overlaps(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other, int32_t& elementOffset)
{
    if (span.get_IsEmpty() || other.get_IsEmpty())
    {
        elementOffset = 0;
        return false;
    }
    ptrdiff_t Offset = other.begin() - span.begin();
    bool isOverlap = (Offset >= 0 && Offset < span.get_Length()) || (Offset < 0 && -Offset < other.get_Length());

    if (isOverlap)
    {
        elementOffset = static_cast<int32_t>(Offset);
    }
    else
    {
        elementOffset = 0;
    }
    return isOverlap;
}

/// @brief Determines if a Span and ReadOnlySpan overlap in memory and calculates the offset
/// @tparam T The type of elements in the spans
/// @param span The Span to check for overlap
/// @param other The ReadOnlySpan to check for overlap
/// @param elementOffset Output parameter that receives the offset between spans if they overlap
/// @return true if the spans share any common memory locations, false otherwise
template <typename T>
bool Overlaps(const Span<T>& span, const ReadOnlySpan<T>& other, int32_t& elementOffset)
{
    return Overlaps(static_cast<ReadOnlySpan<T>>(span), other, elementOffset);
}

/// @brief Replaces all occurrences of a value with a new value in a Span
/// @tparam T The type of elements in the span
/// @param span The span to modify in-place
/// @param oldValue The value to search for and replace
/// @param newValue The new value to replace oldValue with
template <typename T>
void Replace(Span<T>& span, const T& oldValue, const T& newValue)
{
    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (System::ObjectExt::Equals(span.get(i), oldValue))
        {
            span.get(i) = newValue; // Replace oldValue with newValue
        }
    }
}

/// @brief Copies elements from source to destination, replacing specified values during copy
/// @tparam T The type of elements in the spans
/// @param source The source ReadOnlySpan to copy from
/// @param destination The destination Span to copy to
/// @param oldValue The value to search for and replace during copying
/// @param newValue The new value to replace oldValue with
/// @throws ArgumentException if destination is smaller than source
template <typename T>
void Replace(const ReadOnlySpan<T>& source, Span<T>& destination, const T& oldValue, const T& newValue)
{
    if (destination.get_Length() < source.get_Length())
    {
        throw ArgumentException(u"Destination span is smaller than source span.");
    }

    for (int32_t i = 0; i < source.get_Length(); ++i)
    {
        if (System::ObjectExt::Equals(source.get(i), oldValue))
        {
            destination.get(i) = newValue; // Replace oldValue with newValue
        }
        else
        {
            destination.get(i) = source.get(i); // Copy the original value
        }
    }
}

/// @brief Reverses the order of elements in a Span in-place
/// @tparam T The type of elements in the span
/// @param span The span to reverse
template <typename T>
void Reverse(Span<T>& span)
{
    int32_t left = 0;
    int32_t right = span.get_Length() - 1;
    while (left < right)
    {
        std::swap(span.get(left), span.get(right));
        ++left;
        --right;
    }
}

/// @brief Compares two ReadOnlySpans lexicographically
/// @tparam T The type of elements in the spans
/// @param span The first span to compare
/// @param other The second span to compare
/// @return -1 if span < other, 0 if span == other, 1 if span > other
template <typename T>
int32_t SequenceCompareTo(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other)//span.begin() ++
{
    auto spanIt = span.begin();
    auto otherIt = other.begin();
    auto spanEnd = span.end();
    auto otherEnd = other.end();

    while (spanIt != spanEnd && otherIt != otherEnd)
    {
        if (*spanIt < *otherIt)
        {
            return -1; // span is less than other
        }
        if (*spanIt > *otherIt)
        {
            return 1; // span is greater than other
        }

        ++spanIt;
        ++otherIt;
    }

    // If all elements are equal up to the length of the shorter span
    if (span.get_Length() < other.get_Length())
    {
        return -1; // span is shorter
    }
    if (span.get_Length() > other.get_Length())
    {
        return 1; // span is longer
    }

    return 0; // spans are equal
}

/// @brief Compares a Span and ReadOnlySpan lexicographically
/// @tparam T The type of elements in the spans
/// @param span The Span to compare
/// @param other The ReadOnlySpan to compare
/// @return -1 if span < other, 0 if span == other, 1 if span > other
template <typename T>
int32_t SequenceCompareTo(const Span<T>& span, const ReadOnlySpan<T>& other)
{
    return SequenceCompareTo(static_cast<ReadOnlySpan<T>>(span), other);
}

/// @brief Compares a ReadOnlySpan and Span lexicographically
/// @tparam T The type of elements in the spans
/// @param span The ReadOnlySpan to compare
/// @param other The Span to compare
/// @return -1 if span < other, 0 if span == other, 1 if span > other
template <typename T>
int32_t SequenceCompareTo(const ReadOnlySpan<T>& span, const Span<T>& other)
{
    return SequenceCompareTo(span, static_cast<ReadOnlySpan<T>>(other));
}

/// @brief Determines if two ReadOnlySpans contain identical elements in the same order
/// @tparam T The type of elements in the spans
/// @param first The first span to compare
/// @param second The second span to compare
/// @return true if spans have same length and all elements are equal, false otherwise
template <typename T>
bool SequenceEqual(const ReadOnlySpan<T>& first, const ReadOnlySpan<T>& second)
{
    if (first == second)
        return true;

    if (first.get_Length() != second.get_Length())
    {
        return false;
    }

    int32_t length = second.get_Length();

    return Details::SequenceEqualImpl(first, 0, first.get_Length(), second);
}

/// @brief Determines if a Span and ReadOnlySpan contain identical elements in the same order
/// @tparam T The type of elements in the spans
/// @param span The Span to compare
/// @param other The ReadOnlySpan to compare
/// @return true if spans have same length and all elements are equal, false otherwise
template <typename T>
bool SequenceEqual(const Span<T>& span, const ReadOnlySpan<T>& other)
{
    return SequenceEqual(static_cast<ReadOnlySpan<T>>(span), other);
}

/// @brief Determines if two ReadOnlySpans contain equal elements using a custom comparer
/// @tparam T The type of elements in the spans
/// @tparam TComparer The type of the comparer object
/// @param span The first span to compare
/// @param other The second span to compare
/// @param comparer Smart pointer to comparer object for element comparison
/// @return true if spans have same length and comparer considers all elements equal, false otherwise
template <typename T, typename TComparer>
bool SequenceEqual(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& other, SharedPtr<TComparer>& comparer)
{
    if (comparer == nullptr)
    {
        return SequenceEqual(span, other);
    }

    if (span.get_Length() != other.get_Length())
    {
        return false; // Lengths are not equal
    }

    for (int32_t i = 0; i < span.get_Length(); ++i)
    {
        if (!comparer->Equals(span.get(i), other.get(i)))
        {
            return false; // Elements are not equal
        }
    }
    return true; // All elements are equal
}

/// @brief Determines if a Span and ReadOnlySpan contain equal elements using a custom comparer
/// @tparam T The type of elements in the spans
/// @tparam TComparer The type of the comparer object
/// @param span The Span to compare
/// @param other The ReadOnlySpan to compare
/// @param comparer Smart pointer to comparer object for element comparison
/// @return true if spans have same length and comparer considers all elements equal, false otherwise
template <typename T, typename TComparer>
bool SequenceEqual(const Span<T>& span, const ReadOnlySpan<T>& other, SharedPtr<TComparer>& comparer)
{
    return SequenceEqual(static_cast<ReadOnlySpan<T>>(span), other, comparer);
}

/// @brief Sorts a Span using a custom comparer
/// @tparam T The type of elements in the span
/// @tparam TComparer The type of the comparer object
/// @param span The span to sort
/// @param comparer Smart pointer to comparer object for element comparison
template <typename T, typename TComparer>
void Sort(const Span<T>& span, const SharedPtr<TComparer>& comparer)
{
    std::sort(span.begin(), span.end(), [&comparer](const T& a, const T& b) -> bool { return comparer->Compare(a, b) < 0; });
}

/// @brief Sorts a Span using default comparison
/// @tparam T The type of elements in the span
/// @param span The span to sort
template <typename T>
void Sort(Span<T>& span)
{
    std::sort(span.begin(), span.end());
}

/// @brief Sorts key-value pairs using a custom comparer (keys and values sorted together)
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @tparam TComparer The type of the comparer object
/// @param keys The span of keys to sort
/// @param values The span of values to sort (maintaining correspondence with keys)
/// @param comparer Smart pointer to comparer object for key comparison
/// @throws ArgumentException if keys and values have different lengths
template <typename TKey, typename TValue, typename TComparer>
void Sort(Span<TKey>& keys, Span<TValue>& values, const SharedPtr<TComparer>& comparer)
{
    if (keys.get_Length() != values.get_Length())
    {
        throw ArgumentException(u"Keys and items must have the same length.");
    }
    if (keys.get_Length() > 1)
    {
        int32_t depthLimit = 2 * (static_cast<int32_t>(std::log2(keys.get_Length())) + 1);
        Details::IntroSort<TKey, TValue>(keys, values, depthLimit,
                                         [&comparer](TKey a, TKey b) -> bool { return comparer->Compare(a, b) > 0; });
    }
}

/// @brief Sorts key-value pairs using a comparison delegate
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to sort
/// @param values The span of values to sort
/// @param comparer Comparison delegate for key comparison
/// @throws ArgumentException if keys and values have different lengths
template <typename TKey, typename TValue>
void Sort(Span<TKey>& keys, Span<TValue>& values, System::Comparison<TKey> comparer)
{
    if (keys.get_Length() != values.get_Length())
    {
        throw ArgumentException(u"Keys and items must have the same length.");
    }
    if (keys.get_Length() > 1)
    {
        int32_t depthLimit = 2 * (static_cast<int32_t>(std::log2(keys.get_Length())) + 1);
        Details::IntroSort<TKey, TValue>(keys, values, depthLimit,
                                         [&](const TKey& a, const TKey& b) { return !comparer(a, b); });
    }
}

/// @brief Sorts key-value pairs using default comparison
/// @tparam TKey The type of keys
/// @tparam TValue The type of values
/// @param keys The span of keys to sort
/// @param values The span of values to sort
/// @throws ArgumentException if keys and values have different lengths
template <typename TKey, typename TValue>
void Sort(Span<TKey>& keys, Span<TValue>& values)
{
    if (keys.get_Length() != values.get_Length())
    {
        throw ArgumentException(u"Keys and items must have the same length.");
    }
    if (keys.get_Length() > 1)
    {
        int32_t depthLimit = 2 * (static_cast<int32_t>(std::log2(keys.get_Length())) + 1);
        Details::IntroSort<TKey, TValue>(keys, values, depthLimit, [&](const TKey& a, const TKey& b) { return a > b; });
    }
}

/// @brief Checks if the span starts with the specified value
/// @tparam T The type of elements in the span
/// @param span The span to check
/// @param value The value to check for at the beginning of the span
/// @return true if the span starts with the value, false otherwise
template <typename T>
bool StartsWith(const ReadOnlySpan<T>& span, const T& value)
{
    if (span.get_Length() == 0)
    {
        return false; // Empty span cannot start with a value
    }
    return System::ObjectExt::Equals<T>(span.get(0), value);
}

/// @brief Checks if a string span starts with the specified character array
/// @param span The string span to check
/// @param val The character array to check for at the beginning
/// @return true if the span starts with the character array, false otherwise
inline bool StartsWith(const ReadOnlySpan<String>& span, const char16_t* val)
{
    if (span.get_Length() == 0)
    {
        return false;
    }
    String value = String(val);
    return (span.get(0)).Equals(value);
}

/// @brief Checks if the span starts with the specified value span
/// @tparam T The type of elements in the spans
/// @param span The span to check
/// @param value The span containing values to check for at the beginning
/// @return true if the span starts with the value span, false otherwise
template <typename T>
bool StartsWith(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& value)
{
    if (value.get_Length() > span.get_Length())
    {
        return false;
    }

    for (int32_t i = 0; i < value.get_Length(); ++i)
    {
        if (!System::ObjectExt::Equals(span.get(i), value.get(i)))
        {
            return false;
        }
    }

    return true;
}

/// @brief Checks if the mutable span starts with the specified read-only value span
/// @tparam T The type of elements in the spans
/// @param span The mutable span to check
/// @param value The read-only span containing values to check for
/// @return true if the span starts with the value span, false otherwise
template <typename T>
bool StartsWith(const Span<T>& span, const ReadOnlySpan<T>& value)
{
    return StartsWith(static_cast<ReadOnlySpan<T>>(span), value);
}

/// @brief Checks if the read-only span starts with the specified mutable value span
/// @tparam T The type of elements in the spans
/// @param span The read-only span to check
/// @param value The mutable span containing values to check for
/// @return true if the span starts with the value span, false otherwise
template <typename T>
bool StartsWith(const ReadOnlySpan<T>& span, const Span<T>& value)
{
    return StartsWith(span, static_cast<ReadOnlySpan<T>>(value));
}

/// @brief Checks if the character span starts with the specified value span using string comparison
/// @param span The character span to check
/// @param value The character span containing values to check for
/// @param comparisonType The type of string comparison to perform
/// @return true if the span starts with the value span, false otherwise
ASPOSECPP_SHARED_API bool StartsWith(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& value,
                                     StringComparison comparisonType);

/// @brief Converts characters to lowercase using specified culture
/// @param source The source character span to convert
/// @param destination The destination span to store converted characters
/// @param culture The culture to use for conversion (nullptr for current culture)
/// @return Number of characters converted, or -1 if destination is too small
ASPOSECPP_SHARED_API int32_t ToLower(const ReadOnlySpan<char16_t>& source, Span<char16_t>& destination,
                                     const SharedPtr<Globalization::CultureInfo>& culture);

/// @brief Converts characters to lowercase using invariant culture
/// @param source The source character span to convert
/// @param destination The destination span to store converted characters
/// @return Number of characters converted, or -1 if destination is too small
ASPOSECPP_SHARED_API int32_t ToLowerInvariant(const ReadOnlySpan<char16_t>& source, Span<char16_t>& destination);

/// @brief Converts characters to uppercase using specified culture
/// @param source The source character span to convert
/// @param destination The destination span to store converted characters
/// @param culture The culture to use for conversion (nullptr for current culture)
/// @return Number of characters converted, or -1 if destination is too small
ASPOSECPP_SHARED_API int32_t ToUpper(const ReadOnlySpan<char16_t>& source, Span<char16_t>& destination,
                                     const SharedPtr<Globalization::CultureInfo>& culture);

/// @brief Converts characters to uppercase using invariant culture
/// @param source The source character span to convert
/// @param destination The destination span to store converted characters
/// @return Number of characters converted, or -1 if destination is too small
ASPOSECPP_SHARED_API int32_t ToUpperInvariant(const ReadOnlySpan<char16_t>& source, Span<char16_t>& destination);

/// @brief Trims specified element from both ends of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from both ends
template <typename T>
ReadOnlySpan<T> Trim(const ReadOnlySpan<T>& span, T trimElement)
{
    return Trim(span, ReadOnlySpan<T>(&trimElement, 1));
}

/// @brief Trims specified element from both ends of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from both ends
template <typename T>
Span<T> Trim(Span<T>& span, T trimElement)
{
    return Trim(span, ReadOnlySpan<T>(&trimElement, 1));
}

/// @brief Trims specified elements from both ends of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from both ends
template <typename T>
ReadOnlySpan<T> Trim(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& trimElements)
{
    if (span.get_IsEmpty())
    {
        return span;
    }

    int32_t start = 0;
    int32_t end = span.get_Length() - 1;

    // Trim from the start
    while (start <= end && Contains(trimElements, span.get(start)))
    {
        start++;
    }

    // Trim from the end
    while (end >= start && Contains(trimElements, span.get(end)))
    {
        end--;
    }

    return span.Slice(start, end - start + 1);
}

/// @brief Trims specified elements from both ends of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from both ends
template <typename T>
Span<T> Trim(Span<T>& span, const ReadOnlySpan<T>& trimElements)
{
    if (span.get_IsEmpty())
    {
        return span;
    }

    int32_t start = 0;
    int32_t end = span.get_Length() - 1;

    // Trim from the start
    while (start <= end && Contains(trimElements, span.get(start)))
    {
        start++;
    }

    // Trim from the end
    while (end >= start && Contains(trimElements, span.get(end)))
    {
        end--;
    }

    return span.Slice(start, end - start + 1);
}

/// @brief Trims whitespace characters from both ends of a character span
/// @param span The character span to trim
/// @return A new span with whitespace trimmed from both ends
inline ReadOnlySpan<char16_t> Trim(const ReadOnlySpan<char16_t>& span)
{
    return Trim(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims whitespace characters from both ends of a mutable character span
/// @param span The mutable character span to trim
/// @return A new span with whitespace trimmed from both ends
inline Span<char16_t> Trim(Span<char16_t>& span)
{
    return Trim(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims specified element from the end of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from the end
template <typename T>
ReadOnlySpan<T> TrimEnd(const ReadOnlySpan<T>& span, const T& trimElement)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && System::ObjectExt::Equals(span.get(endIndex), trimElement))
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified element from the end of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from the end
template <typename T>
Span<T> TrimEnd(Span<T>& span, const T& trimElement)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && System::ObjectExt::Equals(span.get(endIndex), trimElement)) // equals
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified elements from the end of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from the end
template <typename T>
ReadOnlySpan<T> TrimEnd(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& trimElements)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && Contains(trimElements, span.get(endIndex)))
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified elements from the end of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from the end
template <typename T>
Span<T> TrimEnd(Span<T>& span, const ReadOnlySpan<T>& trimElements)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && Contains(trimElements, span.get(endIndex)))
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims whitespace characters from the end of a character span
/// @param span The character span to trim
/// @return A new span with whitespace trimmed from the end
inline ReadOnlySpan<char16_t> TrimEnd(const ReadOnlySpan<char16_t>& span)
{
    return TrimEnd(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims whitespace characters from the end of a mutable character span
/// @param span The mutable character span to trim
/// @return A new span with whitespace trimmed from the end
inline Span<char16_t> TrimEnd(Span<char16_t>& span)
{
    return TrimEnd<char16_t>(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims specified character from the end of a character span
/// @param span The character span to trim
/// @param trimchar The character to trim
/// @return A new span with the specified character trimmed from the end
inline ReadOnlySpan<char16_t> TrimEnd(const ReadOnlySpan<char16_t>& span, char16_t trimchar)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && span.get(endIndex) == trimchar)
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified character from the end of a mutable character span
/// @param span The mutable character span to trim
/// @param trimchar The character to trim
/// @return A new span with the specified character trimmed from the end
inline Span<char16_t> TrimEnd(Span<char16_t>& span, char16_t trimchar)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && span.get(endIndex) == trimchar)
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified characters from the end of a character span
/// @param span The character span to trim
/// @param trimChars The characters to trim
/// @return A new span with the specified characters trimmed from the end
inline ReadOnlySpan<char16_t> TrimEnd(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& trimChars)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && Contains(trimChars, span.get(endIndex)))
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified characters from the end of a mutable character span
/// @param span The mutable character span to trim
/// @param trimchars The characters to trim
/// @return A new span with the specified characters trimmed from the end
inline Span<char16_t> TrimEnd(Span<char16_t>& span, const ReadOnlySpan<char16_t>& trimchars)
{
    int32_t endIndex = span.get_Length() - 1;
    while (endIndex >= 0 && Contains(trimchars, span.get(endIndex)))
    {
        --endIndex;
    }
    return span.Slice(0, endIndex + 1);
}

/// @brief Trims specified element from the start of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from the start
template <typename T>
ReadOnlySpan<T> TrimStart(const ReadOnlySpan<T>& span, const T& trimElement)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && System::ObjectExt::Equals(span.get(startIndex), trimElement))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified element from the start of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElement The element to trim
/// @return A new span with the specified element trimmed from the start
template <typename T>
Span<T> TrimStart(Span<T>& span, const T& trimElement)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && System::ObjectExt::Equals(span.get(startIndex), trimElement))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified elements from the start of a typed span
/// @tparam T The type of elements in the span
/// @param span The span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from the start
template <typename T>
ReadOnlySpan<T> TrimStart(const ReadOnlySpan<T>& span, const ReadOnlySpan<T>& trimElements)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && Contains(trimElements, span.get(startIndex)))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified elements from the start of a mutable typed span
/// @tparam T The type of elements in the span
/// @param span The mutable span to trim
/// @param trimElements The elements to trim
/// @return A new span with the specified elements trimmed from the start
template <typename T>
Span<T> TrimStart(Span<T>& span, const ReadOnlySpan<T>& trimElements)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && Contains(trimElements, span.get(startIndex)))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims whitespace characters from the start of a character span
/// @param span The character span to trim
/// @return A new span with whitespace trimmed from the start
inline ReadOnlySpan<char16_t> TrimStart(const ReadOnlySpan<char16_t>& span)
{
    return TrimStart(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims whitespace characters from the start of a mutable character span
/// @param span The mutable character span to trim
/// @return A new span with whitespace trimmed from the start
inline Span<char16_t> TrimStart(Span<char16_t>& span)
{
    return TrimStart(span, Details::DefaultWhitespaceSpan);
}

/// @brief Trims specified character from the start of a character span
/// @param span The character span to trim
/// @param trimchar The character to trim
/// @return A new span with the specified character trimmed from the start
inline ReadOnlySpan<char16_t> TrimStart(const ReadOnlySpan<char16_t>& span, char16_t trimchar)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && span.get(startIndex) == trimchar)
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified character from the start of a mutable character span
/// @param span The mutable character span to trim
/// @param trimchar The character to trim
/// @return A new span with the specified character trimmed from the start
inline Span<char16_t> TrimStart(Span<char16_t>& span, char16_t trimchar)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && span.get(startIndex) == trimchar)
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified characters from the start of a character span
/// @param span The character span to trim
/// @param trimchars The characters to trim
/// @return A new span with the specified characters trimmed from the start
inline ReadOnlySpan<char16_t> TrimStart(const ReadOnlySpan<char16_t>& span, const ReadOnlySpan<char16_t>& trimchars)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && Contains(trimchars, span.get(startIndex)))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

/// @brief Trims specified characters from the start of a mutable character span
/// @param span The mutable character span to trim
/// @param trimchars The characters to trim
/// @return A new span with the specified characters trimmed from the start
inline Span<char16_t> TrimStart(Span<char16_t>& span, const ReadOnlySpan<char16_t>& trimchars)
{
    int32_t startIndex = 0;
    while (startIndex < span.get_Length() && Contains(trimchars, span.get(startIndex)))
    {
        ++startIndex;
    }
    return span.Slice(startIndex);
}

} // namespace MemoryExtensions
} // namespace System
#endif // _aspose_system_memory_extensions_

