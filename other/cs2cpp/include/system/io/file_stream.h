/// @file system/io/file_stream.h
#pragma once

#include <system/io/stream.h>
#include <system/io/file_mode.h>
#include <system/io/file_access.h>
#include <system/io/file_share.h>
#include <system/io/file_options.h>
#include <system/io/seekorigin.h>
#include <system/reflection.h>
#include <system/nullable.h>
#include <memory>
#include <vector>

namespace System { namespace IO {

namespace Details { class FileWrapper; }

/// Represents a file stream supporting synchronous and asynchronous read and write operations.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS FileStream : public Stream
{
    RTTI_INFO(System::IO::FileStream, ::System::BaseTypesInfo<System::IO::Stream>);
public:
    /// Default value of the number of bytes bufferred during read and write operations.
    static constexpr int32_t DefaultBufferSize = 4096;

    /// Constructs a new instance of FileStream class and initializes it with the 
    /// specified parameters.
    /// @param path The path of the file to open.
    /// @param mode Specifies the mode in which to open the file.
    ASPOSECPP_SHARED_API FileStream(const String& path, FileMode mode);

    /// Constructs a new instance of FileStream class and initializes it with the 
    /// specified parameters.
    /// @param path The path of the file to open.
    /// @param mode Specifies the mode in which to open the file.
    /// @param access The requested access type.
    /// @param share The type of access that other FileStream objects have to the opened file.
    /// @param buffer_size The number of bytes bufferred during read and write operations.
    /// @param options Additional options.
    ASPOSECPP_SHARED_API FileStream(const String& path, FileMode mode, FileAccess access,
               FileShare share = FileShare::Read,
               int32_t buffer_size = DefaultBufferSize,
               FileOptions options = FileOptions::SequentialScan);

    /// Constructs a new instance of FileStream class and initializes it with the
    /// specified parameters.
    /// @param path The path of the file to open.
    /// @param mode Specifies the mode in which to open the file.
    /// @param access The requested access type.
    /// @param share The type of access that other FileStream objects have to the opened file.
    /// @param buffer_size The number of bytes bufferred during read and write operations.
    /// @param useAsync Specifies whether to use asynchronous I/O or synchronous I/O.
    /// @note The underlying operating system might not support asynchronous I/O.
    ASPOSECPP_SHARED_API FileStream(const String& path, FileMode mode, FileAccess access, FileShare share,
                                    int32_t buffer_size, bool useAsync);

    /// Destructor.
    ASPOSECPP_SHARED_API ~FileStream();

    FileStream(const FileStream&) = delete;
    FileStream& operator=(const FileStream&) = delete;

    /// Determines if the stream is readable.
    /// @returns True if the stream is readable; otherwise - false.
    ASPOSECPP_SHARED_API bool get_CanRead() const override;

    /// Determines if the stream supports seeking.
    /// @returns True if the stream supports seeking; otherwise - false.
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;

    /// Determines if the stream is writable.
    /// @returns True if the stream is writable; otherwise - false.
    ASPOSECPP_SHARED_API bool get_CanWrite() const override;

    /// Returns the length of the stream in bytes.
    ASPOSECPP_SHARED_API int64_t get_Length() const override;

    /// Returns the name of the file encapsulated by the current FileStream object.
    ASPOSECPP_SHARED_API String get_Name() const;

    /// Flushes the stream and then sets the stream's position.
    /// @param value The byte offset to set the stream's position to.
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;

    /// Returns the current position of the stream.
    ASPOSECPP_SHARED_API int64_t get_Position() const override;

    /// Closes the current FileStream object.
    ASPOSECPP_SHARED_API void Close() override;

    /// Clears this stream's buffers and writes all buffered data to the underlying file.
    ASPOSECPP_SHARED_API void Flush() override;

    /// Asynchronously clears all buffers for this stream, causes any buffered data to
    /// be written to the underlying device, and monitors cancellation requests.
    /// @param cancellationToken The token to monitor for cancellation requests.
    /// @returns A task that represents the asynchronous flush operation.
    ASPOSECPP_SHARED_API TaskPtr FlushAsync(const Threading::CancellationToken& cancellationToken) override;

    /// Clears this stream's buffers and writes all buffered data to the underlying file.
    /// Synonym for method Flush().
    /// @param flush_to_disk True to flush all intermediate buffers, otherwise - false.
    ASPOSECPP_SHARED_API void Flush(bool flush_to_disk);

    /// Reads a single byte from the stream and returns a 32-bit integer value
    /// equivalent to the value of the read byte.
    ASPOSECPP_SHARED_API int32_t ReadByte() override;

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array to write the read bytes to.
    /// @param offset A 0-based position in @p buffer to start writing at.
    /// @param count The number of bytes to read.
    /// @returns The number of bytes read.
    ASPOSECPP_SHARED_API int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// Asynchronously reads a sequence of bytes from the current stream, advances the
    /// position within the stream by the number of bytes read, and monitors cancellation
    /// requests.
    /// @param buffer The byte array to write the read bytes to.
    /// @param offset A 0-based position in @p buffer to start writing at.
    /// @param count The number of bytes to read.
    /// @param cancellationToken The token to monitor for cancellation requests.
    /// @returns A task that represents the asynchronous read operation. The value of the TResult
    /// parameter contains the total number of bytes read into the buffer. The result
    /// value can be less than the number of bytes requested if the number of bytes currently
    /// available is less than the requested number, or it can be 0 (zero) if the end
    /// of the stream has been reached.
    ASPOSECPP_SHARED_API RTaskPtr<int32_t> ReadAsync(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count,
                                                     const Threading::CancellationToken& cancellationToken) override;

    /// Sets the position of the stream represented by the current object.
    /// @param offset The byte offset relative to a position specified by @p origin.
    /// @param origin Specifies the position from which and the direction toward which the offset is calculated.
    /// @returns The new position of the stream.
    ASPOSECPP_SHARED_API int64_t Seek(int64_t offset, SeekOrigin origin) override;

    /// Sets the length of the stream represented by the current object.
    /// @param value The length in bytes to set.
    ASPOSECPP_SHARED_API void SetLength(int64_t value) override;

    /// Writes the specified unsigned 8-bit integer value to the stream.
    /// @param value The value to write.
    ASPOSECPP_SHARED_API void WriteByte(uint8_t value) override;

    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array containing the bytes to write.
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins.
    /// @param count The number of elements in the subrange to write.
    ASPOSECPP_SHARED_API void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// Asynchronously writes a sequence of bytes to the current stream, advances the
    /// current position within this stream by the number of bytes written, and monitors
    /// cancellation requests.
    /// @param buffer The array containing the bytes to write.
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins.
    /// @param count The number of elements in the subrange to write.
    /// @param cancellationToken The token to monitor for cancellation requests.
    /// @returns A task that represents the asynchronous write operation.
    ASPOSECPP_SHARED_API TaskPtr WriteAsync(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count,
                                            const Threading::CancellationToken& cancellationToken) override;

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array view to write the read bytes to.
    /// @param offset A 0-based position in @p buffer to start writing at.
    /// @param count The number of bytes to read.
    /// @returns The number of bytes read.
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;

    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array view containing the bytes to write.
    /// @param offset A 0-based index of the elemnet in @p buffer at which the subrange to write begins.
    /// @param count The number of elements in the subrange to write.
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;

private:
    /// Low-level file wrapper.
    std::unique_ptr<Details::FileWrapper> m_file;

    /// File full path.
    String m_path;

    /// File open mode.
    const FileMode m_mode; // Used only for debugging

    /// File access type.
    const FileAccess m_access;

    /// File share mode.
    const FileShare m_share; // Used only for debugging

    /// Advanced options used to create FileStream object.
    const FileOptions m_options; // Used only for debugging

    /// Internal buffer.
    std::vector<uint8_t> m_buffer;

    /// Internal buffer size.
    const int32_t m_buffer_size;

    /// Next byte position in internal buffer to write a byte.
    int32_t m_write_pos = 0;

    /// Next byte position to be read from internal buffer;
    int32_t m_read_pos = 0;

    /// Number of valid bytes in internal buffer.
    int32_t m_read_length = 0;

    /// Current cached position of the file pointer.
    int64_t m_file_pos = 0;

    /// Start position of the file pointer (may not be zero in Append mode).
    int64_t m_file_start_pos = 0;

    void VerifyIntegrity() const;
    void VerifyOpen() const;
    void VerifyReadable() const;
    void VerifyWriteable() const;
    void VerifySeekable() const;

    /// Flushes the read buffer.
    void FlushReadBuffer();

    /// Flushes the write buffer.
    void FlushWriteBuffer();

    /// Flushes all internal buffers (read and write).
    void FlushInternalBuffers();

    /// Read data from file to internal buffer.
    void FillReadBuffer();

    /// Close file.
    void CloseInternal();
};

}} // namespace System::IO
