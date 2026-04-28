/// @file system/io/compression/details/zlib_base_stream.h
#pragma once

#include <system/io/stream.h>
#include <system/io/seekorigin.h>
#include <array>

#include <system/io/compression/details/zlib_codec.h>
#include <system/io/compression/details/zlib_constants.h>
#include <system/io/compression/details/crc32.h>

namespace Aspose { namespace Zip {

/// The internal class to implement compression and decompression using Zlib library.
class ASPOSECPP_SHARED_CLASS ZlibBaseStream : public System::IO::Stream
{
    /// RTTI information.
    RTTI_INFO(Aspose::Zip::ZlibBaseStream, ::System::BaseTypesInfo<System::IO::Stream>);

public:
    /// Pointer type.
    typedef System::SharedPtr<ZlibBaseStream> Ptr;

    ZlibBaseStream() = delete;
    ZlibBaseStream(const ZlibBaseStream&) = delete;

     /// Constructor.
    /// @param stream The underlying stream
    /// @param mode The compression mode.
    /// @param level The compression level.
    /// @param flavor The zlib stream flavor
    /// @param leaveOpen Whether to close underlying stream on finish.
    /// @param initNow If true is passed the Init method will be called in the constructor.
    ASPOSECPP_SHARED_API ZlibBaseStream(const System::IO::Stream::Ptr& stream, CompressionMode mode,
                                        CompressionLevel level, ZlibStreamFlavor flavor, bool leaveOpen,
                                        bool initNow = true);

    /// Destructor.
    virtual ASPOSECPP_SHARED_API ~ZlibBaseStream();

    /// Gets flush mode.
    /// @return Flush mode set for the stream.
    virtual ASPOSECPP_SHARED_API FlushType get_FlushMode() const;
    /// Sets flush mode.
    /// @param value Flush mode to be set for the stream.
    virtual ASPOSECPP_SHARED_API void set_FlushMode(FlushType value);

    /// Gets buffer size.
    /// @return Buffer size set for the stream.
    virtual ASPOSECPP_SHARED_API int get_BufferSize();
    /// Sets Buffer size.
    /// @param value Buffer size to be set for the stream.
    virtual ASPOSECPP_SHARED_API void set_BufferSize(int value);

    /// Gets compression strategy.
    /// @return Compression strategy set for the stream.
    virtual ASPOSECPP_SHARED_API CompressionStrategy get_Strategy() const;
    /// Sets compression strategy.
    /// @param value Compression strategy to be set for the stream.
    virtual ASPOSECPP_SHARED_API void set_Strategy(CompressionStrategy value);

    /// Gets number of totally written bytes.
    /// @return Number of bytes gone into the stream.
    virtual ASPOSECPP_SHARED_API int64_t get_TotalIn();
    /// Gets number of totally read bytes.
    /// @return Number of bytes gone from the stream.
    virtual ASPOSECPP_SHARED_API int64_t get_TotalOut();

    /// @copydoc System::IO::Stream::get_CanRead
    ASPOSECPP_SHARED_API bool get_CanRead() const override;
    /// @copydoc System::IO::Stream::get_CanSeek
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;
    /// @copydoc System::IO::Stream::get_CanWrite
    ASPOSECPP_SHARED_API bool get_CanWrite() const override;
    /// @copydoc System::IO::Stream::get_Length
    ASPOSECPP_SHARED_API int64_t get_Length() const override;
    /// @copydoc System::IO::Stream::get_Position
    ASPOSECPP_SHARED_API int64_t get_Position() const override;
    /// @copydoc System::IO::Stream::set_Position
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;
    /// @copydoc System::IO::Stream::Close
    ASPOSECPP_SHARED_API void Close() override;
    /// @copydoc System::IO::Stream::Flush
    ASPOSECPP_SHARED_API void Flush() override;
    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const System::ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// @copydoc System::IO::Stream::Seek
    ASPOSECPP_SHARED_API int64_t Seek(int64_t offset, System::IO::SeekOrigin origin) override;
    /// @copydoc System::IO::Stream::SetLength
    ASPOSECPP_SHARED_API void SetLength(int64_t value) override;
    /// @copydoc System::IO::Stream::Write
    ASPOSECPP_SHARED_API void Write(const System::ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// @copydoc System::IO::Stream::Write
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// Converts ZlibStreamFlavor to Windows bitmask.
    /// @param flavor Flavor value.
    /// @return Flavor value converted into 32-bit signed integer.
    static ASPOSECPP_SHARED_API int FlavorToWinBits(ZlibStreamFlavor flavor);

protected:
   
    /// Codec used by stream.
    ZlibCodec::Ptr m_codec;
    /// Underlying stream.
    Stream::Ptr m_stream;
    /// Mode.
    CompressionMode m_mode;
    /// Compression level.
    CompressionLevel m_level;
    /// Zlib stream flavor.
    ZlibStreamFlavor m_flavor;
    /// Whether to close underlying stream on finish.
    bool m_leaveOpen;
    /// Flush type.
    FlushType m_flushType;
    /// Strategy.
    CompressionStrategy m_strategy;
    /// CRC value
    CRC32::Ptr m_crc32;
    /// Buffer size
    int m_bufferSize;
    /// Buffer
    System::ByteArrayPtr m_buffer;

    /// Indicates whether the stream is in compression mode or not.
    /// @return true if the stream in compression stream.
    ASPOSECPP_SHARED_API bool IsCompress() const;
    /// Compresses the string after being compressed to UTF8.
    /// @param str String to compress.
    /// @param flavor Flavor to be used.
    /// @return Compressed string in byte format.
    static ASPOSECPP_SHARED_API System::ByteArrayPtr CompressString(const System::String& str, ZlibStreamFlavor flavor);
    /// Compresses byte sequence.
    /// @param buffer Bytes to compress.
    /// @param flavor Flavor to be used.
    /// @return Compressed data.
    static ASPOSECPP_SHARED_API System::ByteArrayPtr CompressBuffer(const System::ByteArrayPtr& buffer, ZlibStreamFlavor flavor);
    /// Uncompresses the string which is encoded in UTF8 and compressed.
    /// @param compressed Data to uncompress.
    /// @param flavor Flavor to be used.
    /// @return Uncompressed string.
    static ASPOSECPP_SHARED_API System::String UncompressString(const System::ByteArrayPtr& compressed, ZlibStreamFlavor flavor);
    /// Uncompresses byte sequence.
    /// @param compressed Data to uncompress.
    /// @param flavor Flavor to be used.
    /// @return Uncompressed data.
    static ASPOSECPP_SHARED_API System::ByteArrayPtr UncompressBuffer(const System::ByteArrayPtr& compressed, ZlibStreamFlavor flavor);
    /// Handler to be called when codec is updated.
    /// @param current_codec The current codec.
    /// @param new_codec A new codec.
    virtual void OnUpdateCodec(const ZlibCodec::Ptr& current_codec, const ZlibCodec::Ptr& new_codec)
    {
        ASPOSE_UNUSED(current_codec);
        ASPOSE_UNUSED(new_codec);
    }

private:
    /// Internal codec update routine.
    void UpdateCodec();
    /// Internal initialization routine.
    void Init();
    /// Internal finalization routine.
    void SoftFinish() const /*noexcept*/;

};

}} // namespace Aspose::Zip
