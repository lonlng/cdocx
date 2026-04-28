/// @file system/io/compression/details/deflate_stream.h
#pragma once

#include <system/io/stream.h>

#include <system/io/compression/details/flush_type.h>
#include <system/io/compression/details/zlib_compression_flags.h>
#include <system/io/compression/details/zlib_base_stream.h>

namespace Aspose { namespace Zip {

/// A class for compressing and decompressing streams using the Deflate algorithm.
class ASPOSECPP_SHARED_CLASS DeflateStream : public ZlibBaseStream
{
    /// RTTI information.
    RTTI_INFO(Aspose::Zip::DeflateStream, ::System::BaseTypesInfo<::Aspose::Zip::ZlibBaseStream>);

public:
    /// Pointer type.
    typedef System::SharedPtr<DeflateStream> Ptr;

    /// Constructor. Closes the stream after being processed.
    /// @param stream Stream to be inflated or deflated.
    /// @param mode Direction (compression or decompression).
    ASPOSECPP_SHARED_API DeflateStream(const System::IO::Stream::Ptr& stream, CompressionMode mode);
    /// Constructor.
    /// @param stream Stream to be inflated or deflated.
    /// @param mode Direction (compression or decompression).
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API DeflateStream(const System::IO::Stream::Ptr& stream, CompressionMode mode, bool leaveOpen);
    /// Constructor. Uses 'deflate' mode.
    /// @param stream Stream to be inflated or deflated.
    /// @param level Compression mode to be applied.
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API DeflateStream(const System::IO::Stream::Ptr& stream, CompressionLevel level, bool leaveOpen = false);
    /// Constructor.
    /// @param stream Stream to be inflated or deflated.
    /// @param mode Direction (compression or decompression).
    /// @param level Compression mode to be applied.
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API DeflateStream(const System::IO::Stream::Ptr& stream, CompressionMode mode, CompressionLevel level, bool leaveOpen = false);

    /// Checks whether the stream can seek.
    /// @return Always returns false.
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;
    /// Gets a reference to the underlying stream.
    /// @returns A pointer to the underlying stream.
    ASPOSECPP_SHARED_API System::StreamPtr get_BaseStream() const { return m_stream; };

    /// @copydoc System::IO::Stream::get_Position
    ASPOSECPP_SHARED_API int64_t get_Position() const override;
    /// @copydoc System::IO::Stream::set_Position
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;

    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const System::ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// Compresses the string after being compressed to UTF8.
    /// @param s String to compress.
    /// @return Compressed string in byte format.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> CompressString(const System::String& s);
    /// Compresses byte sequence.
    /// @param b Bytes to compress.
    /// @return Compressed data.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> CompressBuffer(const System::ArrayPtr<uint8_t>& b);
    /// Uncompresses the string which is encoded in UTF8 and compressed.
    /// @param compressed Data to uncompress.
    /// @return Uncompressed string.
    static ASPOSECPP_SHARED_API System::String UncompressString(const System::ArrayPtr<uint8_t>& compressed);
    /// Uncompresses byte sequence.
    /// @param compressed Data to uncompress.
    /// @return Uncompressed data.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UncompressBuffer(const System::ArrayPtr<uint8_t>& compressed);

private:
    int64_t m_position;
};

}} // namespace Aspose::Zip
