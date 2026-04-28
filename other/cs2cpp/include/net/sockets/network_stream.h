/// @file net/sockets/network_stream.h
#pragma once

#include <cstdint>
#include <system/array.h>
#include <system/async_callback.h>
#include <system/iasyncresult.h>
#include <system/io/file_access.h>
#include <system/io/seekorigin.h>
#include <system/io/stream.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/sockets/socket.h>

namespace System { namespace Net { namespace Sockets {

/// Provides the underlying stream of the data for the network access.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS NetworkStream : public System::IO::Stream
{
    /// This type.
    typedef NetworkStream ThisType;
    /// Parent type.
    typedef System::IO::Stream BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// @copydoc System::IO::Stream::get_CanRead
    ASPOSECPP_SHARED_API bool get_CanRead() const override;
    /// @copydoc System::IO::Stream::get_CanSeek
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;
    /// @copydoc System::IO::Stream::get_CanWrite
    ASPOSECPP_SHARED_API bool get_CanWrite() const override;
    /// @copydoc System::IO::Stream::get_CanTimeout
    ASPOSECPP_SHARED_API bool get_CanTimeout() const override;
    /// @copydoc System::IO::Stream::get_ReadTimeout
    ASPOSECPP_SHARED_API int32_t get_ReadTimeout() const override;
    /// @copydoc System::IO::Stream::set_ReadTimeout
    ASPOSECPP_SHARED_API void set_ReadTimeout(int32_t value) override;
    /// @copydoc System::IO::Stream::get_WriteTimeout
    ASPOSECPP_SHARED_API int32_t get_WriteTimeout() const override;
    /// @copydoc System::IO::Stream::set_WriteTimeout
    ASPOSECPP_SHARED_API void set_WriteTimeout(int32_t value) override;
    /// Returns a value that indicates if the there is available data to read.
    /// @returns A value that indicates if the there is available data to read.
    ASPOSECPP_SHARED_API bool get_DataAvailable() const;
    /// @copydoc System::IO::Stream::get_Length
    ASPOSECPP_SHARED_API int64_t get_Length() const override;
    /// @copydoc System::IO::Stream::get_Position
    ASPOSECPP_SHARED_API int64_t get_Position() const override;
    /// @copydoc System::IO::Stream::set_Position
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;

    /// Gets the underlying Socket.
    /// @returns A Socket object that represents the underlying network connection.
    ASPOSECPP_SHARED_API System::SharedPtr<System::Net::Sockets::Socket> get_Socket();

    /// Constructs a new instance.
    /// @param socket The socket that is used for sending and receiving data.
    ASPOSECPP_SHARED_API NetworkStream(System::SharedPtr<System::Net::Sockets::Socket> socket);
    /// Constructs a new instance.
    /// @param socket The socket that is used for sending and receiving data.
    /// @param access Specifies the access type given to the instance over the specified socket.
    /// @param ownsSocket A value that indicates if the current instance takes ownership of the specified socket when
    /// the value is true.
    ASPOSECPP_SHARED_API NetworkStream(System::SharedPtr<System::Net::Sockets::Socket> socket,
                                       System::IO::FileAccess access, bool ownsSocket);
    /// Constructs a new instance.
    /// @param socket The socket that is used for sending and receiving data.
    /// @param ownsSocket A value that indicates if the current instance takes ownership of the specified socket when
    /// the value is true.
    ASPOSECPP_SHARED_API NetworkStream(System::SharedPtr<System::Net::Sockets::Socket> socket, bool ownsSocket);

    /// @copydoc System::IO::Stream::Seek
    ASPOSECPP_SHARED_API int64_t Seek(int64_t offset, IO::SeekOrigin origin) override;
    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array where the read bytes will be written.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to read.
    /// @returns The number of read bytes.
    ASPOSECPP_SHARED_API int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t size) override;
    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array containing the bytes to write.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of elements in the subrange to write.
    ASPOSECPP_SHARED_API void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t size) override;

    /// Reads the specified number of bytes from the stream and writes them to the specified byte array.
    /// @param buffer The byte array view to write the read bytes to
    /// @param offset A 0-based position in @p buffer to start writing at
    /// @param size The number of bytes to read
    /// @returns The number of bytes read
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t size) override;
    /// Writes the specified subrange of bytes from the specified byte array to the stream.
    /// @param buffer The array view containing the bytes to write
    /// @param offset A 0-based index of the element in @p buffer at which the subrange to write begins
    /// @param size The number of elements in the subrange to write
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t size) override;

    /// Closes the current instance after the specified time expires.
    /// @param timeout A number of milliseconds to wait.
    ASPOSECPP_SHARED_API void Close(int timeout);

    /// Destructs the current instance.
    virtual ASPOSECPP_SHARED_API ~NetworkStream();

    /// Initiates an asynchronous read operation.
    /// @param buffer The byte array where the read bytes will be written.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to read.
    /// @param callback A callback to be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous read operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous read operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginRead(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                   int32_t size, AsyncCallback callback,
                                                                   System::SharedPtr<Object> state) override;
    /// @copydoc System::IO::Stream::EndRead
    ASPOSECPP_SHARED_API int32_t EndRead(System::SharedPtr<IAsyncResult> asyncResult) override;
    /// Initiates an asynchronous write operation.
    /// @param buffer A buffer containing data to be written.
    /// @param offset The offset in bytes in the specified array.
    /// @param size The number of bytes to write.
    /// @param callback A callback to be called when the operation completes.
    /// @param state User-provided data used to uniquely identify each asynchronous write operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous write operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginWrite(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                    int32_t size, AsyncCallback callback,
                                                                    System::SharedPtr<Object> state) override;
    /// @copydoc System::IO::Stream::EndWrite
    ASPOSECPP_SHARED_API void EndWrite(System::SharedPtr<IAsyncResult> asyncResult) override;
    /// @copydoc System::IO::Stream::Flush
    ASPOSECPP_SHARED_API void Flush() override;
    /// @copydoc System::IO::Stream::SetLength
    ASPOSECPP_SHARED_API void SetLength(int64_t value) override;

private:
    /// Initializes the current instance using the specified parameters.
    /// @param socket The socket that is used for sending and receiving data.
    /// @param Access Specifies the access type given to the instance over the specified socket.
    void InitNetworkStream(System::SharedPtr<System::Net::Sockets::Socket> socket, System::IO::FileAccess Access);

    /// The socket that is used for sending and receiving data.
    System::SharedPtr<System::Net::Sockets::Socket> m_StreamSocket;

    /// A value that indicates if the current stream is readable.
    bool m_Readable;
    /// A value that indicates if the current stream is writeable.
    bool m_Writeable;
    /// A value that indicates if the instance takes ownership of the specified socket when the value is true.
    bool m_OwnsSocket;
};
}}} // namespace System::Net::Sockets
