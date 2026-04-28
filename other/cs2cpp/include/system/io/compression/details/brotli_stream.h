/// @file system/io/compression/details/brotli_stream.h
#pragma once

#include <system/exceptions.h>
#include <system/io/stream.h>
#include <system/io/compression/compression_level.h>
#include <system/io/compression/compression_mode.h>

//#include <system/io/compression/details/flush_type.h>

namespace Aspose { namespace Brotli {

/// A class for compressing and decompressing streams using the Brotli algorithm.
class ASPOSECPP_SHARED_CLASS BrotliStream final : public System::IO::Stream
{
    /// RTTI information.
    RTTI_INFO(Aspose::Brotli::BrotliStream, ::System::BaseTypesInfo<System::IO::Stream>);

public:
    /// Pointer type.
    typedef System::SharedPtr<BrotliStream> Ptr;

    /// Compresses byte sequence.
    /// @param b Bytes to compress.
    /// @return Compressed data.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> CompressBuffer(const System::ArrayPtr<uint8_t>& b);
    /// Uncompresses byte sequence.
    /// @param compressed Data to uncompress.
    /// @return Uncompressed data.
    static ASPOSECPP_SHARED_API size_t UncompressBuffer(const System::ArrayPtr<uint8_t>& compressed,
                                                        System::ArrayPtr<uint8_t>& destination);
    BrotliStream() = delete;
    BrotliStream(const BrotliStream&) = delete;

    /// Constructor. Closes the stream after being processed.
    /// @param stream Stream to be compressed or uncompressed.
    /// @param mode Direction (compression or decompression).
    ASPOSECPP_SHARED_API BrotliStream(const System::IO::Stream::Ptr& stream,
                                      System::IO::Compression::CompressionMode mode);
    /// Constructor.
    /// @param stream Stream to be compressed or uncompressed.
    /// @param mode Direction (compression or decompression).
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API BrotliStream(const System::IO::Stream::Ptr& stream,
                                      System::IO::Compression::CompressionMode mode, bool leaveOpen);
    /// Constructor. Uses 'Compress' mode.
    /// @param stream Stream to be compressed or uncompressed.
    /// @param level Compression mode to be applied.
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API BrotliStream(const System::IO::Stream::Ptr& stream,
                                      System::IO::Compression::CompressionLevel level, bool leaveOpen = false);
    /// Constructor.
    /// @param stream Stream to be compressed or uncompressed.
    /// @param mode Direction (compression or decompression).
    /// @param level Compression mode to be applied.
    /// @param leaveOpen Whether to close stream (false) or not (true) after processing.
    ASPOSECPP_SHARED_API BrotliStream(const System::IO::Stream::Ptr& stream,
                                      System::IO::Compression::CompressionMode mode,
                                      System::IO::Compression::CompressionLevel level, bool leaveOpen = false);

    /// Destructor.
    ASPOSECPP_SHARED_API ~BrotliStream();

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns The number of bytes read
    ASPOSECPP_SHARED_API int32_t Read(const System::ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Reads the specified number of bytes from the stream and writes them to the specified byte array view.
    /// @param buffer The byte array view to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param count The number of bytes to read
    /// @returns The number of bytes read
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    ASPOSECPP_SHARED_API void Write(const System::ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Writes the specified subrange of bytes from the specified byte array view to the stream.
    /// @param buffer The array view containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param count The number of elements in the subrange to write
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Sets the position of the stream represented by the current object.
    /// @param offset The byte offset relative to a position specified by @p origin
    /// @param origin Specifies the position from which and the direction toward which the offset is calculated
    /// @returns The new position of the stream
    ASPOSECPP_SHARED_API int64_t Seek(int64_t offset, System::IO::SeekOrigin origin) override;
    /// Sets the length of the stream represented by the current object.
    /// @param value The length in bytes to set
    ASPOSECPP_SHARED_API void SetLength(int64_t value) override;
    /// Clears this stream's buffers and writes all buffered data to the underlying storage.
    ASPOSECPP_SHARED_API void Flush() override;

    /// Gets a reference to the underlying stream.
    /// @returns A pointer to the underlying stream.
    ASPOSECPP_SHARED_API System::StreamPtr get_BaseStream() const;
    /// Checks whether the stream can seek.
    /// @return Always returns false.
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;
    /// Determines if the stream is readable.
    /// @returns True if the stream is readable; otherwise - false
    ASPOSECPP_SHARED_API bool get_CanRead() const override;
    /// Determines if the stream is writable.
    /// @returns True if the stream is writable; otherwise - false
    ASPOSECPP_SHARED_API bool get_CanWrite() const override;
    /// Sets the stream's position.
    /// @param value The byte offset to set the stream's position to
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;
    /// Returns the current position of the stream.
    /// @returns The current position of the stream.
    ASPOSECPP_SHARED_API int64_t get_Position() const override;
    /// Returns the length of the stream in bytes.
    /// @returns The length of the stream in bytes.
    ASPOSECPP_SHARED_API int64_t get_Length() const override;
    /// Set compress level for stream.
    /// @param quality Compress level.
    ASPOSECPP_SHARED_API void SetQuality(int quality);
    /// Tune encoder for specific input.
    /// @param mode Compress mode.
    ASPOSECPP_SHARED_API void SetMode(int mode);
    /// Sets the window size for the encoder.
    /// @param windowSize The window size in bits (a value from 10-24).
    ASPOSECPP_SHARED_API void SetWindow(int windowSize);
    /// Closes the stream.
    ASPOSECPP_SHARED_API void Close() override;

private:
    Stream::Ptr m_stream;
    System::IO::Compression::CompressionMode m_mode;
    System::IO::Compression::CompressionLevel m_level;
    System::ByteArrayPtr m_buffer = nullptr;
    int m_bufferOffset = 0;
    int m_bufferCount = 0;
    bool m_leaveOpen;
    bool m_disposed;
    int m_lastDecoderState;
    std::unique_ptr<void, std::function<const void(void*)>> m_encoderState;
    std::unique_ptr<void, std::function<const void(void*)>> m_decoderState;

    void Dispose(bool disposing) override;
    void EnsureNotDisposed();
    void ValidateParameters(System::Details::ArrayView<uint8_t> buffer, int offset, int count);
    void FlushCompress(bool finish);
    void WriteCore(const System::ArrayPtr<uint8_t>& buffer, int offset, int count, int operation);
    void WriteCore(System::Details::ArrayView<uint8_t> buffer, int offset, int count, int operation);
    int QualityFromCompressionLevel(System::IO::Compression::CompressionLevel level);
};

}} // namespace Aspose::Brotli
