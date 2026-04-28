/// @file net/http/http_content.h
#pragma once

#include <cstdint>
#include <system/array.h>
#include <system/exceptions.h>
#include <system/idisposable.h>
#include <system/io/memory_stream.h>
#include <system/io/stream.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/text/encoding.h>

#include <net/http/headers/http_content_headers.h>

namespace System { namespace Net { namespace Http {

/// Represents content of an HTTP entity.
/// Object of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ABSTRACT ASPOSECPP_SHARED_CLASS HttpContent : public System::IDisposable
{
    /// This type.
    typedef HttpContent ThisType;
    /// Parent type.
    typedef System::IDisposable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

private:
    /// Limits the number of bytes of the memory stream.
    class LimitMemoryStream : public System::IO::MemoryStream
    {
        /// This type.
        typedef LimitMemoryStream ThisType;
        /// Parent type.
        typedef System::IO::MemoryStream BaseType;

        /// Base types.
        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        /// RTTI information.
        ASPOSECPP_SHARED_RTTI_INFO_DECL();

    public:
        /// Constructs a new instance.
        /// @param maxSize The maximum number of bytes.
        /// @param capacity The initial size of the internal array.
        LimitMemoryStream(int32_t maxSize, int32_t capacity);

        /// @copydoc System::IO::MemoryStream::Write
        void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
        /// @copydoc System::IO::MemoryStream::Write
        void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
        /// @copydoc System::IO::MemoryStream::WriteByte
        void WriteByte(uint8_t value) override;

    private:
        /// The maximum number of bytes.
        int32_t _maxSize;

        /// Checks if the content size is less than or equal to the maximum size.
        void CheckSize(int32_t countToAdd);
    };

public:
    /// The maximum number of bytes.
    static const int64_t MaxBufferSize;
    /// The default encoding.
    static System::SharedPtr<Text::Encoding> DefaultStringEncoding;

    /// Returns the HTTP content headers.
    /// @returns The HTTP content headers.
    ASPOSECPP_SHARED_API System::SharedPtr<Headers::HttpContentHeaders> get_Headers();
    /// Serializes content and returns a stream.
    /// @returns A stream that represents serialized content.
    ASPOSECPP_SHARED_API System::SharedPtr<IO::Stream> ReadAsStream();
    /// Serializes content and returns a string.
    /// @returns A string that represents serialized content.
    ASPOSECPP_SHARED_API String ReadAsString();
    /// Serializes content and returns a byte array.
    /// @returns A byte array that represents serialized content.
    ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> ReadAsByteArray();
    /// Serializes content to a memory buffer.
    ASPOSECPP_SHARED_API void LoadIntoBuffer();
    /// Serializes content to a memory buffer.
    /// @param maxBufferSize The maximum number of bytes of the buffer to use.
    ASPOSECPP_SHARED_API void LoadIntoBuffer(int64_t maxBufferSize);

    /// Tries to calculate the content size.
    /// @param length The output parameter where the calculated size will be assigned.
    /// @returns True when the size is successfully updated, otherwise false.
    ASPOSECPP_SHARED_API virtual bool TryComputeLength(int64_t& length) = 0;
    /// Disposes the current instance. This method also disposes the stream that is returned by 'ReadAsStream' and the
    /// memory buffer if it is created.
    ASPOSECPP_SHARED_API void Dispose() override;

protected:
    /// Constructs a new instance.
    HttpContent();
    /// Serializes content to a stream.
    /// @param stream The output stream.
    virtual void SerializeToStream(System::SharedPtr<IO::Stream> stream) = 0;
    /// Disposes the current instance. This method also disposes the stream that is returned by 'ReadAsStream' and the
    /// memory buffer if it is created.
    /// @param disposing True when the method is called directly or indirectly by a user's code, otherwise false.
    virtual void Dispose(bool disposing);

private:
    /// The HTTP content headers.
    System::SharedPtr<Headers::HttpContentHeaders> _headers;
    /// The memory stream.
    System::SharedPtr<IO::MemoryStream> _bufferedContent;
    /// Indicates if the current instance is disposed.
    bool _disposed;
    /// The stream that is used in the 'ReadAsStream' method.
    System::SharedPtr<IO::Stream> _contentReadStream;
    /// Indicates that the content length is calculated before.
    bool _canCalculateLength;
    /// The UTF-8 code page.
    static const int32_t UTF8CodePage;
    /// The size of the UTF-8 code page preamble.
    static const int32_t UTF8PreambleLength;
    /// The first byte of the UTF-8 code page preamble.
    static const uint8_t UTF8PreambleByte0;
    /// The second byte of the UTF-8 code page preamble.
    static const uint8_t UTF8PreambleByte1;
    /// The third byte of the UTF-8 code page preamble.
    static const uint8_t UTF8PreambleByte2;
    /// The first two bytes of the UTF-8 code page preamble.
    static const int32_t UTF8PreambleFirst2Bytes;
    /// The UTF-32 code page.
    static const int32_t UTF32CodePage;
    /// The size of the UTF-32 code page preamble.
    static const int32_t UTF32PreambleLength;
    /// The first byte of the UTF-32 code page preamble.
    static const uint8_t UTF32PreambleByte0;
    /// The second byte of the UTF-32 code page preamble.
    static const uint8_t UTF32PreambleByte1;
    /// The third byte of the UTF-32 code page preamble.
    static const uint8_t UTF32PreambleByte2;
    /// The fourth byte of the UTF-32 code page preamble.
    static const uint8_t UTF32PreambleByte3;
    /// The first two bytes of the UTF-32 code page preamble.
    static const int32_t UTF32OrUnicodePreambleFirst2Bytes;
    /// The Unicode code page.
    static const int32_t UnicodeCodePage;
    /// The size of the Unicode code page preamble.
    static const int32_t UnicodePreambleLength;
    /// The first byte of the Unicode code page preamble.
    static const uint8_t UnicodePreambleByte0;
    /// The second byte of the Unicode code page preamble.
    static const uint8_t UnicodePreambleByte1;
    /// The Big-Endian code page.
    static const int32_t BigEndianUnicodeCodePage;
    /// The size of the Big-Endian code page preamble.
    static const int32_t BigEndianUnicodePreambleLength;
    /// The first byte of the Big-Endian code page preamble.
    static const uint8_t BigEndianUnicodePreambleByte0;
    /// The second byte of the Big-Endian code page preamble.
    static const uint8_t BigEndianUnicodePreambleByte1;
    /// The first two bytes of the Big-Endian code page preamble.
    static const int32_t BigEndianUnicodePreambleFirst2Bytes;

    /// Indicates if content is already buffered.
    bool get_IsBuffered();

    /// Returns the content size.
    /// @returns The content size.
    Nullable<int64_t> GetComputedOrBufferLength();
    /// Serializes content and returns a newly created stream.
    virtual System::SharedPtr<IO::Stream> CreateContentReadStream();

    /// Creates a memory stream with the specified limitation of the buffer size.
    /// @param maxBufferSize The maximum number of bytes.
    System::SharedPtr<IO::MemoryStream> CreateMemoryStream(int64_t maxBufferSize);
    /// Returns content of the specified stream as a byte array.
    /// @param stream The stream.
    /// @returns Content of the specified stream as a byte array.
    System::ArrayPtr<uint8_t> GetDataBuffer(System::SharedPtr<IO::MemoryStream> stream);
    /// Checks if the current instance is disposed.
    void CheckDisposed();
    /// Creates a copy of the specified exception.
    /// @param originalException The exception that must be copied.
    /// @returns The copy of the specified exception.
    static Exception GetStreamCopyException(Exception originalException);
    /// Returns the preamble size of the specified data.
    /// @param data A byte array that contains content.
    /// @param dataLength The number of bytes in the specified array that represents the data.
    /// @param encoding The data encoding.
    /// @returns The preamble size.
    static int32_t GetPreambleLength(System::ArrayPtr<uint8_t> data, int32_t dataLength,
                                     System::SharedPtr<Text::Encoding> encoding);
    /// Tries to detect an encoding of the specified data.
    /// @param data A byte array that contains content.
    /// @param dataLength The number of bytes in the specified array that represents the data.
    /// @param encoding The output parameter where a detected encoding will be assigned.
    /// @param preambleLength The output parameter where the preamble size of a detected encoding will be assigned.
    /// @returns True when an encoding is successfully detected, otherwise false.
    static bool TryDetectEncoding(System::ArrayPtr<uint8_t> data, int32_t dataLength,
                                  System::SharedPtr<Text::Encoding>& encoding, int32_t& preambleLength);
    /// Determines if the specified array contains the specified prefix.
    /// @param byteArray The array to check.
    /// @param dataLength The number of bytes in the specified array that represents the data.
    /// @param prefix The prefix.
    /// @returns True when the specified array contains the specified prefix, otherwise false.
    static bool ByteArrayHasPrefix(System::ArrayPtr<uint8_t> byteArray, int32_t dataLength,
                                   System::ArrayPtr<uint8_t> prefix);
};

}}} // namespace System::Net::Http
