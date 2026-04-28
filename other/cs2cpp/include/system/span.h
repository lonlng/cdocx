/// @file system/span.h
#pragma once

#include <algorithm>
#include <type_traits>

#include <system/array.h>
#include <system/details/stack_array.h>
#include <system/collections/ienumerator.h>
#include <system/convert.h>
#include <system/smart_ptr.h>
#include <system/string.h>
#include <system/exceptions.h>
#include <system/make_const_ref.h>

namespace System {

namespace Details {

/// Common implementation both for System::Span and System::ReadOnlySpan classes.
/// Must not be used directly, only as base of these classes.
template <typename T, typename Span, typename MutableSpan>
class SpanCore
{
protected:
    using MutableT = std::remove_const_t<T>;
    using RefrerenceT = std::conditional_t<std::is_const<T>::value, MakeConstRef_t<MutableT>, T&>;
    using ArrayPtrT = System::ArrayPtr<MutableT>;
    using VoidPtrT = std::conditional_t<std::is_const<std::remove_pointer_t<T>>::value, const void*, void*>;

public:
    ///@brief Enables enumeration of elements of the Span.
    ///@note Objects of this class should only be allocated on stack.
    class Enumerator
    {
        friend SpanCore;

        SpanCore m_span;
        int32_t m_idx = -1;

        ///@brief Constructs an enumerator for the given span.
        ///@param span The span to enumerate.
        explicit Enumerator(const SpanCore& span) : m_span(span)
        {}

    public:
        ///@brief Gets the current element in the enumeration.
        ///@return Reference to the current element or default value of T if enumeration hasn't started or is out of
        /// bounds.
        RefrerenceT get_Current()
        {
            if (m_idx < 0 || m_idx >= m_span.get_Length())
            {
                throw IndexOutOfRangeException(u"index");
            }

            return  m_span.get(m_idx);
        }

        ///@brief Advances the enumerator to the next element.
        ///@return true if the enumerator was successfully advanced; false if end reached.
        bool MoveNext()
        {
            if (m_idx < m_span.get_Length())
            {
                m_idx++;
            }

            return m_idx < m_span.get_Length();
        }

        ///@brief Resets the enumerator to its initial position.
        void Reset()
        {
            m_idx = -1;
        }
    };

public:
    ///@brief Constructs an empty span.
    SpanCore() : SpanCore(nullptr, nullptr, 0)
    {}

    ///@brief Constructs a span from an array.
    ///@param array The array to create a span for.
    SpanCore(const ArrayPtrT& array) : SpanCore(array, array == nullptr ? nullptr : array->data_ptr(), array == nullptr ? 0 : array->get_Length())
    {}

    ///@brief Constructs a span from a stack-allocated array.
    ///@tparam Size Size of the stack array.
    ///@param stack_array The stack array to create a span for.
    template <int32_t Size>
    SpanCore(Details::StackArray<MutableT, Size>& stack_array) : SpanCore(stack_array.data(), Size)
    {}

    ///@brief Constructs a span from a raw pointer and length.
    ///@param pointer Pointer to the beginning of the memory region.
    ///@param length Number of elements in the memory region.
    ///@throws ArgumentOutOfRangeException if length is negative.
    SpanCore(VoidPtrT pointer, int32_t length) : SpanCore(nullptr, (T*)pointer, length)
    {
        if (length < 0)
        {
            throw ArgumentOutOfRangeException(u"length");
        }
    }

    ///@brief Constructs a span representing a portion of an array.
    ///@param array The source array.
    ///@param start The index at which to begin the span.
    ///@param length The number of items to include in the span.
    ///@throws ArgumentOutOfRangeException if parameters are invalid.
    SpanCore(const ArrayPtrT& array, int32_t start, int32_t length) : SpanCore(array, array->data_ptr() + start, length)
    {
        if (array == nullptr)
        {
            if (start != 0)
            {
                throw ArgumentOutOfRangeException(u"start");
            }
            if (length != 0)
            {
                throw ArgumentOutOfRangeException(u"length");
            }
        }
        else
        {
            if (start < 0 || (start > 0 && start >= array->get_Length()))
            {
                throw ArgumentOutOfRangeException(u"start");
            }
            if (start + length > array->get_Length())
            {
                throw ArgumentOutOfRangeException(u"length");
            }
        }
    }

    ///@brief Gets an empty span.
    ///@return An empty span.
    static Span get_Empty()
    {
        return Span(nullptr, nullptr, 0);
    }

    ///@brief Gets an enumerator for this span.
    ///@return An enumerator for the span.
    Enumerator GetEnumerator() const
    {
        return Enumerator(*this);
    }

    ///@brief Gets the hash code for this span (not supported).
    ///@throws NotSupportedException always.
    int32_t GetHashCode() const
    {
        throw NotSupportedException();
    }

    ///@brief Checks if the span is empty.
    ///@return true if the span is empty; otherwise false.
    bool get_IsEmpty() const
    {
        return m_length == 0;
    }

    ///@brief Gets the length of the span.
    ///@return The number of elements in the span.
    int32_t get_Length() const
    {
        return m_length;
    }

    ///@brief Forms a slice out of the current span starting at specified index.
    ///@param start The index at which to begin the slice.
    ///@return A span consisting of all elements from start to the end of current span.
    ///@throws ArgumentOutOfRangeException if start is out of range.
    Span Slice(int32_t start) const
    {
        return Slice(start, m_length - start);
    }

    ///@brief Forms a slice out of the current span.
    ///@param start The index at which to begin the slice.
    ///@param length The desired length of the slice.
    ///@return A span consisting of length elements from start.
    ///@throws ArgumentOutOfRangeException if parameters are invalid.
    Span Slice(int32_t start, int32_t length) const
    {
        if (start < 0)
        {
            throw ArgumentOutOfRangeException(u"start");
        }
        else if (length < 0 || start + length > m_length)
        {
            throw ArgumentOutOfRangeException(u"length");
        }

        return Span(m_array, m_pointer + start, length);
    }

    ///@brief Copies the contents of this span into destination span.
    ///@param destination The destination span.
    ///@throws ArgumentException if destination is shorter than source span.
    void CopyTo(MutableSpan destination) const
    {
        if (m_length > destination.get_Length())
        {
            throw ArgumentException(u"destination");
        }

        std::copy(cbegin(), cend(), destination.begin());
    }

    ///@brief Attempts to copy the current span to destination span.
    ///@param destination The destination span.
    ///@return true if the copy succeeded; false if destination was too small.
    bool TryCopyTo(MutableSpan destination) const
    {
        if (m_length > destination.get_Length())
        {
            return false;
        }

        std::copy(cbegin(), cend(), destination.begin());

        return true;
    }

    ///@brief Copies the contents of this span into a new array.
    ///@return A new array containing the data from the span.
    ArrayPtrT ToArray() const
    {
        auto result = System::MakeArray<MutableT>(m_length);

        std::copy(cbegin(), cend(), result->begin());

        return result;
    }

    ///@brief Converts the span to a string (specialization for char16_t).
    ///@return A string containing the characters in the span.
    ///@tparam T1 Used for SFINAE, should be char16_t.
    template <typename T1 = MutableT>
    typename std::enable_if<std::is_same<T1, char16_t>::value, String>::type ToString() const
    {
        return System::String(ToArray());
    }

    ///@brief Converts the span to a string (general case).
    ///@return A string representation of the span.
    ///@tparam T1 Used for SFINAE, should not be char16_t.
    template <typename T1 = MutableT>
    typename std::enable_if<!std::is_same<T1, char16_t>::value, String>::type ToString() const
    {
        return u"System::Span<T>[" + System::Convert::ToString(m_length) + u"]";
    }

public:
    // Iterator support
    T* begin() const noexcept
    {
        return m_pointer;
    }

    T* end() const noexcept
    {
        return m_pointer + m_length;
    }

    const T* cbegin() const noexcept
    {
        return m_pointer;
    }

    const T* cend() const noexcept
    {
        return m_pointer + m_length;
    }

    T* rbegin() const noexcept
    {
        return m_pointer + m_length;
    }

    T* rend() const noexcept
    {
        return m_pointer;
    }

    const T* crbegin() const noexcept
    {
        return m_pointer + m_length;
    }

    const T* crend() const noexcept
    {
        return m_pointer;
    }

    ///@brief Accesses the element at specified index with bounds checking.
    ///@param index The zero-based index of the element.
    ///@return Reference to the element at specified index.
    ///@throws IndexOutOfRangeException if index is out of range.
    RefrerenceT operator[](int32_t index) const
    {
        if (index < 0 || index >= m_length)
        {
            throw IndexOutOfRangeException(u"index");
        }

        return *(m_pointer + index);
    }

    ///@brief Accesses the element at specified index without bounds checking.
    ///@param index The zero-based index of the element.
    RefrerenceT get(int32_t index) const
    {
        return *(m_pointer + index);
    }

    ///@brief Compares two spans for equality.
    ///@param right The span to compare with.
    ///@return true if spans point to same memory and have same length; otherwise false.
    bool operator==(const SpanCore& right) const
    {
        return m_pointer == right.m_pointer && m_length == right.m_length;
    }

protected:
    ///@brief Internal constructor used by other constructors.
    ///@param array Smart pointer to array (controls lifetime).
    ///@param pointer Raw pointer to data.
    ///@param length Length of the span.
    SpanCore(const ArrayPtrT& array, T* pointer, int32_t length)
        : m_array(array), m_pointer(pointer), m_length(length)
    {}

    T*        m_pointer; ///< Pointer to first data element
    int32_t   m_length;  ///< Number of elements in the span
    ArrayPtrT m_array;   ///< Smart pointer to array (only controls lifetime)
};

} // namespace Details

/// Forward to use within Span class
template <typename T>
class ReadOnlySpan;

///@brief Represents a contiguous region of arbitrary memory similar to C++20's std::span.
///@tparam T The type of elements in the span.
/// This class provides a type-safe way to work with contiguous sequences of objects.
/// It can be used to wrap arrays, stack arrays, or raw pointers while maintaining bounds checking.
/// The Span doesn't own the memory it points to - it's just a view into existing memory.
template <typename T>
class Span : public Details::SpanCore<T, Span<T>, Span<T>>
{
    typedef Span<T> ThisType;
    typedef typename Details::SpanCore<T, Span<T>, Span<T>> BaseType;

    friend BaseType;
    friend ReadOnlySpan<T>;

public:
    using Details::SpanCore<T, Span<T>, Span<T>>::SpanCore;

    ///@brief Clears the contents of the span by setting all elements to default value.
    void Clear() const
    {
        std::fill(this->begin(), this->end(), System::Default<T>());
    }

    ///@brief Fills the span with the specified value.
    ///@param value The value to assign to each element of the span.
    void Fill(const T& value) const
    {
        std::fill(this->begin(), this->end(), value);
    }

    ///@brief Converts an array to a Span.
    ///@param array The array to convert.
    ///@return A span representing the array.
    static ThisType to_Span(const typename BaseType::ArrayPtrT& array)
    {
        return ThisType(array);
    }
};

///@brief Represents a read-only contiguous region of arbitrary memory.
///@tparam T The type of elements in the span.
/// This class provides a type-safe way to work with contiguous sequences of objects in a read-only manner.
/// It can be used to wrap arrays, stack arrays, or raw pointers while maintaining bounds checking.
/// The ReadOnlySpan doesn't own the memory it points to - it's just a view into existing memory.
template <typename T>
class ReadOnlySpan : public Details::SpanCore<const T, ReadOnlySpan<T>, Span<T>>
{
    typedef ReadOnlySpan<T> ThisType;
    typedef typename Details::SpanCore<const T, ReadOnlySpan<T>, Span<T>> BaseType;

    friend BaseType;

public:
    using Details::SpanCore<const T, ReadOnlySpan<T>, Span<T>>::SpanCore;

    ///@brief Constructs a read-only span from a regular span.
    ///@param span The span to create a read-only view of.
    ReadOnlySpan(const Span<T>& span) : BaseType(span.m_array, span.m_pointer, span.m_length)
    {}

    ///@brief Converts an array to a ReadOnlySpan.
    ///@param array The array to convert.
    ///@return A read only span representing the array.
    static ThisType to_ReadOnlySpan(const typename BaseType::ArrayPtrT& array)
    {
        return ThisType(array);
    }
};

} // namespace System
