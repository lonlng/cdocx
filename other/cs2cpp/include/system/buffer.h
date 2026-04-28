/// @file system/buffer.h
/// Contains declaration of System::Buffer class.
#ifndef _aspose_system_buffer_h_
#define _aspose_system_buffer_h_

#include <algorithm>

#include "fwd.h"
#include "system/array.h"
#include "system/exceptions.h"
#include "system/details/array_view.h"
#include "system/details/stack_array.h"

namespace System {

    /// Contains methods that manipulate raw byte arrays.
    /// This is a static type with no instance services.
    /// You should never create instances of it by any means.
    /// @code
    /// #include <system/buffer.h>
    ///
    /// using namespace System;
    ///
    /// void Print(const SmartPtr<Array<uint8_t>> &source, int size)
    /// {
    ///   for (auto i = 0; i < size; i++)
    ///   {
    ///     std::cout << static_cast<int>(source[i]) << ' ';
    ///   }
    ///   std::cout << std::endl;
    /// }
    ///
    /// int main()
    /// {
    ///   // Create and fill the array.
    ///   const int SIZE = 16;
    ///   auto first = MakeObject<Array<uint8_t>>(SIZE);
    ///   for (auto i = 0; i < SIZE; ++i)
    ///   {
    ///     first[i] = static_cast<uint8_t>(i * 2);
    ///   }
    ///
    ///   // Print the array items.
    ///   Print(first, SIZE);
    ///
    ///   // Create an array that contains a part of the first one.
    ///   auto second = MakeObject<Array<uint8_t>>(SIZE / 2);
    ///   Buffer::BlockCopy(first, SIZE / 2, second, 0, SIZE / 2);
    ///
    ///   // Print the items of the second array.
    ///   Print(second, SIZE / 2);
    ///
    ///   // Set the value of the item at index 0 and print the array items.
    ///   Buffer::SetByte(second, 0, 128);
    ///   Print(second, SIZE / 2);
    ///
    ///   return 0;
    /// }
    /// /*
    /// This code example produces the following output:
    /// 0 2 4 6 8 10 12 14 16 18 20 22 24 26 28 30
    /// 16 18 20 22 24 26 28 30
    /// 128 18 20 22 24 26 28 30
    /// */
    /// @endcode
    class Buffer
    {
    public:

        /// Copies a specified number of bytes from source buffer to destination buffer.
        /// @param src Pointer to the source buffer
        /// @param srcOffset A byte offset in source buffer at which copying starts
        /// @param dst Pointer to the destination buffer
        /// @param dstOffset A byte offset in the destination buffer at which to start inserting data
        /// @param count The number of bytes to copy
        static ASPOSECPP_SHARED_API void BlockCopy(const uint8_t* src, int srcOffset, uint8_t* dst, int dstOffset, int count);

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source array
        /// @param srcOffset A byte offset in the tho source array at which copying starts
        /// @param dst The destination array
        /// @param dstOffset A byte offset in the destination array at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array
        /// @tparam TDst The type of elements of the destination array
        template<typename TSrc, typename TDst>
        static void BlockCopy(const SharedPtr<Array<TSrc>>& src, int srcOffset, const SharedPtr<Array<TDst>>& dst, int dstOffset, int count)
        {
            BlockCopy(static_cast<System::Details::ArrayView<TSrc>>(src), srcOffset, static_cast<System::Details::ArrayView<TDst>>(dst), dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source array view
        /// @param srcOffset A byte offset in the tho source array view at which copying starts
        /// @param dst The destination array view
        /// @param dstOffset A byte offset in the destination array view at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array view
        /// @tparam TDst The type of elements of the destination array view
        template<typename TSrc, typename TDst>
        static void BlockCopy(const System::Details::ArrayView<TSrc>& src, int srcOffset, const System::Details::ArrayView<TDst>& dst, int dstOffset, int count)
        {
            static_assert(Details::IsPod<TSrc>::value, "BlockCopy template argument must be a POD type.");
            static_assert(Details::IsPod<TDst>::value, "BlockCopy template argument must be a POD type.");

            if (!src)
                throw ArgumentNullException(u"src");

            if (!dst)
                throw ArgumentNullException(u"dst");

            if (0 > srcOffset || 0 > dstOffset || 0 > count)
                throw ArgumentOutOfRangeException();

            if (_ByteLength(src) < srcOffset || _ByteLength(src) < srcOffset + count)
                throw ArgumentOutOfRangeException(u"src->Count() < srcOffset |+count|");

            if (_ByteLength(dst) < dstOffset || _ByteLength(dst) < dstOffset + count)
                throw ArgumentOutOfRangeException(u"dst->Count() < dstOffset |+count|");

            if (0 == count)
                return;

            _BlockCopy(src, srcOffset, dst, dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source array
        /// @param srcOffset A byte offset in the tho source array at which copying starts
        /// @param dst The destination array view
        /// @param dstOffset A byte offset in the destination array view at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array
        /// @tparam TDst The type of elements of the destination array view
        template<typename TSrc, typename TDst>
        static void BlockCopy(const SharedPtr<Array<TSrc>>& src, int srcOffset, const System::Details::ArrayView<TDst>& dst, int dstOffset, int count)
        {
            BlockCopy(static_cast<System::Details::ArrayView<TSrc>>(src), srcOffset, dst, dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source array view
        /// @param srcOffset A byte offset in the tho source array view at which copying starts
        /// @param dst The destination array
        /// @param dstOffset A byte offset in the destination array at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array view
        /// @tparam TDst The type of elements of the destination array
        template<typename TSrc, typename TDst>
        static void BlockCopy(const System::Details::ArrayView<TSrc>& src, int srcOffset, const SharedPtr<Array<TDst>>& dst, int dstOffset, int count)
        {
            BlockCopy(src, srcOffset, static_cast<System::Details::ArrayView<TDst>>(dst), dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source stack array
        /// @param srcOffset A byte offset in the tho source stack array at which copying starts
        /// @param dst The destination stack array
        /// @param dstOffset A byte offset in the destination stack array at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source stack array
        /// @tparam NS The size of the source stack array
        /// @tparam TDst The type of elements of the destination stack array
        /// @tparam ND The size of the destination stack array
        template<typename TSrc, std::size_t NS, typename TDst, std::size_t ND>
        static void BlockCopy(const System::Details::StackArray<TSrc, NS>& src, int srcOffset, const System::Details::StackArray<TDst, ND>& dst, int dstOffset, int count)
        {
            BlockCopy(static_cast<System::Details::ArrayView<TSrc>>(src), srcOffset, static_cast<System::Details::ArrayView<TDst>>(dst), dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source array
        /// @param srcOffset A byte offset in the tho source array at which copying starts
        /// @param dst The destination stack array
        /// @param dstOffset A byte offset in the destination stack array at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array
        /// @tparam TDst The type of elements of the destination stack array
        /// @tparam ND The size of the destination stack array
        template<typename TSrc, typename TDst, std::size_t ND>
        static void BlockCopy(const SharedPtr<Array<TSrc>>& src, int srcOffset, const System::Details::StackArray<TDst, ND>& dst, int dstOffset, int count)
        {
            BlockCopy(static_cast<System::Details::ArrayView<TSrc>>(src), srcOffset, static_cast<System::Details::ArrayView<TDst>>(dst), dstOffset, count);
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another.
        /// @param src The source stack array
        /// @param srcOffset A byte offset in the tho source stack array at which copying starts
        /// @param dst The destination array
        /// @param dstOffset A byte offset in the destination array at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source stack array
        /// @tparam NS The size of the source stack array
        /// @tparam TDst The type of elements of the destination array
        template<typename TSrc, std::size_t NS, typename TDst>
        static void BlockCopy(const System::Details::StackArray<TSrc, NS>& src, int srcOffset, const SharedPtr<Array<TDst>>& dst, int dstOffset, int count)
        {
            BlockCopy(static_cast<System::Details::ArrayView<TSrc>>(src), srcOffset, static_cast<System::Details::ArrayView<TDst>>(dst), dstOffset, count);
        }

        /// Determines the number of bytes occupied by all elements of the specified array.
        /// @param array An array 
        /// @returns The number of bytes occupied by all elements of the specified array
        /// @tparam T The type of elements of the array
        template<class T>
        static int ByteLength(const SharedPtr<Array<T>>& array)
        {
            return ByteLength(static_cast<System::Details::ArrayView<T>>(array));
        }

        /// Determines the number of bytes occupied by all elements of the specified array.
        /// @param array An array view
        /// @returns The number of bytes occupied by all elements of the specified array view
        /// @tparam T The type of elements of the array view
        template<class T>
        static int ByteLength(const System::Details::ArrayView<T>& array)
        {
            static_assert(Details::IsPod<T>::value, "ByteLength template argument must be a POD type.");

            if (!array)
                throw ArgumentNullException(u"array");

            return _ByteLength(array);
        }

        /// Determines the number of bytes occupied by all elements of the specified array.
        /// @param array An stack array
        /// @returns The number of bytes occupied by all elements of the specified stack array
        /// @tparam T The type of elements of the stack array
        /// @tparam N The size of the stack array
        template<class T, std::size_t N>
        static int ByteLength(const System::Details::StackArray<T, N>& array)
        {
            return ByteLength(static_cast<System::Details::ArrayView<T>>(array));
        }

        /// Interprets the specified typed array as a raw byte array and retrieves the byte value at specified byte offset.
        /// @param array The target array
        /// @param index Zero-based offset of the byte to retrieve
        /// @returns The byte value at the specified index
        /// @tparam T The type of elements of the array
        template<typename T>
        static uint8_t GetByte(const SharedPtr<Array<T>>& array, int index)
        {
            return GetByte(static_cast<System::Details::ArrayView<T>>(array), index);
        }

        /// Interprets the specified typed array as a raw byte array and retrieves the byte value at specified byte offset.
        /// @param array The target array view
        /// @param index Zero-based offset of the byte to retrieve
        /// @returns The byte value at the specified index
        /// @tparam T The type of elements of the array view
        template<typename T>
        static uint8_t GetByte(const System::Details::ArrayView<T>& array, int index)
        {
            static_assert(Details::IsPod<T>::value, "GetByte template argument must be a POD type.");

            if (!array)
                throw ArgumentNullException(u"array");

            if (index < 0 || index >= _ByteLength(array))
                throw ArgumentOutOfRangeException(u"index");

            return _GetByte<T>(array, index);
        }

        /// Interprets the specified typed array as a raw byte array and retrieves the byte value at specified byte offset.
        /// @param array The target stack array
        /// @param index Zero-based offset of the byte to retrieve
        /// @returns The byte value at the specified index
        /// @tparam T The type of elements of the stack array
        /// @tparam N The size of the stack array
        template<typename T, std::size_t N>
        static uint8_t GetByte(const System::Details::StackArray<T, N>& array, int index)
        {
            return GetByte(static_cast<System::Details::ArrayView<T>>(array), index);
        }

        /// Interprets the specified typed array as a raw byte array and sets the specified byte value at specified byte offset.
        /// @param array The target array
        /// @param index Zero-based offset of the byte to set
        /// @param value The byte value to set
        /// @tparam T The type of elements of the array
        template<typename T>
        static void SetByte(const SharedPtr<Array<T>>& array, int index, uint8_t value)
        {
            SetByte(static_cast<System::Details::ArrayView<T>>(array), index, value);
        }

        /// Interprets the specified typed array as a raw byte array and sets the specified byte value at specified byte offset.
        /// @param array The target array view
        /// @param index Zero-based offset of the byte to set
        /// @param value The byte value to set
        /// @tparam T The type of elements of the array
        template<typename T>
        static void SetByte(const System::Details::ArrayView<T>& array, int index, uint8_t value)
        {
            static_assert(Details::IsPod<T>::value, "SetByte template argument must be a POD type.");

            if (!array)
                throw ArgumentNullException(u"array");

            if (index < 0 || index >= _ByteLength(array))
                throw ArgumentOutOfRangeException(u"index");

            return _SetByte<T>(array, index, value);
        }

        /// Interprets the specified typed array as a raw byte array and sets the specified byte value at specified byte offset.
        /// @param array The target stack array
        /// @param index Zero-based offset of the byte to set
        /// @param value The byte value to set
        /// @tparam T The type of elements of the array
        /// @tparam N The size of the stack array
        template<typename T, std::size_t N>
        static void SetByte(const System::Details::StackArray<T, N>& array, int index, uint8_t value)
        {
            SetByte(static_cast<System::Details::ArrayView<T>>(array), index, value);
        }

    private:

        /// Determines the number of bytes occupied by all elements of the specified array.
        /// @param array An array view
        /// @returns The number of bytes occupied by all elements of the specified array
        /// @tparam T The type of elements of the array view
        template<typename T>
        static int _ByteLength(const System::Details::ArrayView<T>& array)
        {
            return (int)(array.Count()*sizeof(T));
        }

        /// Interprets the specified typed array as a raw byte array and retrieves the byte value at specified byte offset.
        /// @param array The target array view
        /// @param index Zero-based offset of the byte to retrieve
        /// @returns The byte value at the specified index
        /// @tparam T The type of elements of the array view
        template<typename T>
        static uint8_t _GetByte(const System::Details::ArrayView<T>& array, int index)
        {
            return reinterpret_cast<const uint8_t*>(array.data())[index];
        }

        /// Interprets the specified typed array as a raw byte array and sets the specified byte value at specified byte offset.
        /// @param array The target array view
        /// @param index Zero-based offset of the byte to set
        /// @param value The byte value to set
        /// @tparam T The type of elements of the array view
        template<typename T>
        static void _SetByte(const System::Details::ArrayView<T>& array, int index, uint8_t value)
        {
            reinterpret_cast<uint8_t*>(array.data())[index] = value;
        }

        /// Interprets two specified typed arrays as raw arrays of bytes and copies data from one of them to another. 
        /// @param src The source array view
        /// @param srcOffset A byte offset in the tho source array view at which copying starts
        /// @param dst The destination array view
        /// @param dstOffset A byte offset in the destination array view at which to start inserting data
        /// @param count The number of bytes to copy
        /// @tparam TSrc The type of elements of the source array view
        /// @tparam TDst The type of elements of the destination array view
        template<typename TSrc, typename TDst>
        static void _BlockCopy(const System::Details::ArrayView<TSrc>& src, int srcOffset, const System::Details::ArrayView<TDst>& dst, int dstOffset, int count)
        {
            std::copy(reinterpret_cast<const uint8_t*>(src.data()) + static_cast<size_t>(srcOffset)
                , reinterpret_cast<const uint8_t*>(src.data()) + static_cast<size_t>(srcOffset) + static_cast<size_t>(count)
                , reinterpret_cast<uint8_t*>(dst.data()) + static_cast<size_t>(dstOffset));
        }
    };
}

#endif // _aspose_system_buffer_h_
