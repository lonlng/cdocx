/// @file net/secure_protocols/ssl_stream.h
#pragma once

#include <cstdint>
#include <security/cryptography/x509_certificates/x509_certificate.h>
#include <security/cryptography/x509_certificates/x509_certificate_collection.h>
#include <security/cryptography/x509_certificates/x509_chain.h>
#include <system/array.h>
#include <system/async_callback.h>
#include <system/enum_helpers.h>
#include <system/iasyncresult.h>
#include <system/io/seekorigin.h>
#include <system/multicast_delegate.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/secure_protocols/authentificated_stream.h>
#include <net/secure_protocols/ssl_enum_types.h>
#include <net/secure_protocols/ssl_policy_errors.h>

namespace System { namespace Net { namespace Details {
class TlsStreamImplStream;
class TlsStreamImplSocket;
}}} // namespace System::Net::Details

namespace System { namespace Net { namespace Security {

/// Enumerates the encryption policies.
enum class EncryptionPolicy
{
    /// Require encryption and never allow a 'Null' cipher.
    RequireEncryption = 0,
    /// Prefer using full encryption but a 'Null' cipher can be used if the server agrees.
    AllowNoEncryption,
    /// Allow no encryption and request that a 'Null' cipher be used if the other endpoint can handle a 'Null' cipher.
    NoEncryption
};

/// A user delegate used to verify remote SSL certificate
using RemoteCertificateValidationCallback = System::MulticastDelegate<bool(
    System::SharedPtr<Object>, System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>,
    System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Chain>, SslPolicyErrors)>;

/// A user delegate used to select local SSL certificate
using LocalCertificateSelectionCallback =
    System::MulticastDelegate<System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>(
        System::SharedPtr<Object>, String,
        System::SharedPtr<System::Security::Cryptography::X509Certificates::X509CertificateCollection>,
        System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>,
        System::ArrayPtr<String>)>;

class TlsStreamAsyncResult;

/// A stream that uses the SSL protocol to authenticate the server and optionally the client.
class ASPOSECPP_SHARED_CLASS SslStream : public System::Net::Security::AuthenticatedStream
{
    friend class TlsStreamAsyncResult;

    /// This type.
    typedef SslStream ThisType;
    /// Parent type.
    typedef System::Net::Security::AuthenticatedStream BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();
public:
    /// Type of AsyncResultType
    typedef TlsStreamAsyncResult AsyncResultType;
    /// Type of pointer to the implementation
    typedef std::shared_ptr<System::Net::Details::TlsStreamImplSocket> StreamImplementationPtr;


    /// @copydoc System::Net::Security::AuthenticatedStream::get_IsAuthenticated
    ASPOSECPP_SHARED_API bool get_IsAuthenticated() const override;
    /// @copydoc System::Net::Security::AuthenticatedStream::get_IsMutuallyAuthenticated
    ASPOSECPP_SHARED_API bool get_IsMutuallyAuthenticated() const override;
    /// @copydoc System::Net::Security::AuthenticatedStream::get_IsEncrypted
    ASPOSECPP_SHARED_API bool get_IsEncrypted() const override;
    /// @copydoc System::Net::Security::AuthenticatedStream::get_IsSigned
    ASPOSECPP_SHARED_API bool get_IsSigned() const override;
    /// @copydoc System::Net::Security::AuthenticatedStream::get_IsServer
    ASPOSECPP_SHARED_API bool get_IsServer() const override;
    /// Returns the SSL protocol.
    /// @returns The SSL protocol.
    virtual ASPOSECPP_SHARED_API System::Security::Authentication::SslProtocols get_SslProtocol();
    /// Returns a value that indicates if the certificate revocation list is checked during the certificate validation
    /// process.
    /// @returns A value that indicates if the certificate revocation list is checked during the certificate validation
    // process.
    virtual ASPOSECPP_SHARED_API bool get_CheckCertRevocationStatus();
    /// Returns the certificate that is used to authenticate the local endpoint.
    /// @returns The certificate that is used to authenticate the local endpoint.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>
        get_LocalCertificate();
    /// Returns the certificate that is used to authenticate the remote endpoint.
    /// @returns The certificate that is used to authenticate the remote endpoint.
    virtual ASPOSECPP_SHARED_API System::SharedPtr<System::Security::Cryptography::X509Certificates::X509Certificate>
        get_RemoteCertificate();
    /// Returns the encryption algorithm.
    /// @returns The encryption algorithm.
    virtual ASPOSECPP_SHARED_API System::Security::Authentication::CipherAlgorithmType get_CipherAlgorithm();
    /// Returns the strength of the used encryption algorithm.
    /// @returns The strength of the used encryption algorithm.
    virtual ASPOSECPP_SHARED_API int32_t get_CipherStrength();
    /// Returns the hash algorithm.
    /// @returns The hash algorithm.
    virtual ASPOSECPP_SHARED_API System::Security::Authentication::HashAlgorithmType get_HashAlgorithm();
    /// Returns the strength of the used hash algorithm.
    /// @returns The strength of the used hash algorithm.
    virtual ASPOSECPP_SHARED_API int32_t get_HashStrength();
    /// Returns the strength of the used key exchange algorithm.
    /// @returns The strength of the used key exchange algorithm.
    virtual ASPOSECPP_SHARED_API int32_t get_KeyExchangeStrength();
    /// @copydoc System::IO::Stream::get_CanSeek
    ASPOSECPP_SHARED_API bool get_CanSeek() const override;
    /// @copydoc System::IO::Stream::get_CanRead
    ASPOSECPP_SHARED_API bool get_CanRead() const override;
    /// @copydoc System::IO::Stream::get_CanTimeout
    ASPOSECPP_SHARED_API bool get_CanTimeout() const override;
    /// @copydoc System::IO::Stream::get_CanWrite
    ASPOSECPP_SHARED_API bool get_CanWrite() const override;
    /// @copydoc System::IO::Stream::get_ReadTimeout
    ASPOSECPP_SHARED_API int32_t get_ReadTimeout() const override;
    /// @copydoc System::IO::Stream::set_ReadTimeout
    ASPOSECPP_SHARED_API void set_ReadTimeout(int32_t value) override;
    /// @copydoc System::IO::Stream::get_WriteTimeout
    ASPOSECPP_SHARED_API int32_t get_WriteTimeout() const override;
    /// @copydoc System::IO::Stream::set_WriteTimeout
    ASPOSECPP_SHARED_API void set_WriteTimeout(int32_t value) override;
    /// @copydoc System::IO::Stream::get_Length
    ASPOSECPP_SHARED_API int64_t get_Length() const override;
    /// @copydoc System::IO::Stream::get_Position
    ASPOSECPP_SHARED_API int64_t get_Position() const override;
    /// @copydoc System::IO::Stream::set_Position
    ASPOSECPP_SHARED_API void set_Position(int64_t value) override;

    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    ASPOSECPP_SHARED_API SslStream(System::SharedPtr<IO::Stream> innerStream);
    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    /// @param leaveInnerStreamOpen If true, closing the current instance has no effect on 'InnerStream'.
    ASPOSECPP_SHARED_API SslStream(System::SharedPtr<IO::Stream> innerStream, bool leaveInnerStreamOpen);
    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    /// @param leaveInnerStreamOpen If true, closing the current instance has no effect on 'InnerStream'.
    /// @param userCertificateValidationCallback The delegate that is used for validating the certificate supplied by
    /// the remote party.
    ASPOSECPP_SHARED_API SslStream(System::SharedPtr<IO::Stream> innerStream, bool leaveInnerStreamOpen,
                                   RemoteCertificateValidationCallback userCertificateValidationCallback);
    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    /// @param leaveInnerStreamOpen If true, closing the current instance has no effect on 'InnerStream'.
    /// @param userCertificateValidationCallback The delegate that is used for validating the certificate supplied by
    /// the remote party.
    /// @param userCertificateSelectionCallback The delegate that is used for selecting the certificate used for
    /// authentication.
    ASPOSECPP_SHARED_API SslStream(System::SharedPtr<IO::Stream> innerStream, bool leaveInnerStreamOpen,
                                   RemoteCertificateValidationCallback userCertificateValidationCallback,
                                   LocalCertificateSelectionCallback userCertificateSelectionCallback);
    /// Constructs a new instance.
    /// @param innerStream The stream that is used for sending and receiving data.
    /// @param leaveInnerStreamOpen If true, closing the current instance has no effect on 'InnerStream'.
    /// @param userCertificateValidationCallback The delegate that is used for validating the certificate supplied by
    /// the remote party.
    /// @param userCertificateSelectionCallback The delegate that is used for selecting the certificate used for
    /// authentication.
    /// @param encryptionPolicy The encryption policy.
    ASPOSECPP_SHARED_API SslStream(System::SharedPtr<IO::Stream> innerStream, bool leaveInnerStreamOpen,
                                   RemoteCertificateValidationCallback userCertificateValidationCallback,
                                   LocalCertificateSelectionCallback userCertificateSelectionCallback,
                                   EncryptionPolicy encryptionPolicy);

    /// Authenticates the client-side of the connection.
    /// @param targetHost The name of the server that shares the current instance.
    virtual ASPOSECPP_SHARED_API void AuthenticateAsClient(String targetHost);
    /// Authenticates the client-side of the connection.
    /// @param targetHost The name of the server that shares the current instance.
    /// @param clientCertificates The client certificates.
    /// @param enabledSslProtocols The SSL protocols that are used for authentication.
    /// @param checkCertificateRevocation A value that indicates if the certificate revocation list must be checked
    /// during authentication.
    virtual ASPOSECPP_SHARED_API void AuthenticateAsClient(
        String targetHost,
        System::SharedPtr<System::Security::Cryptography::X509Certificates::X509CertificateCollection>
            clientCertificates,
        System::Security::Authentication::SslProtocols enabledSslProtocols, bool checkCertificateRevocation);

    /// @copydoc System::IO::Stream::SetLength
    ASPOSECPP_SHARED_API void SetLength(int64_t value) override;
    /// @copydoc System::IO::Stream::Seek
    ASPOSECPP_SHARED_API int64_t Seek(int64_t offset, IO::SeekOrigin origin) override;
    /// @copydoc System::IO::Stream::Flush
    ASPOSECPP_SHARED_API void Flush() override;
    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Writes the specified byte array to the stream.
    /// @param buffer The byte array to write.
    ASPOSECPP_SHARED_API void Write(const ArrayPtr<uint8_t>& buffer);
    /// @copydoc System::IO::Stream::Write
    ASPOSECPP_SHARED_API void Write(const ArrayPtr<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// @copydoc System::IO::Stream::Read
    ASPOSECPP_SHARED_API int32_t Read(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Writes the specified byte array to the stream.
    /// @param buffer The byte array to write.
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer);
    /// @copydoc System::IO::Stream::Write
    ASPOSECPP_SHARED_API void Write(const System::Details::ArrayView<uint8_t>& buffer, int32_t offset, int32_t count) override;
    /// Initiates an asynchronous read operation.
    /// @param buffer The byte array to read data from.
    /// @param offset The offset in bytes in the specified array.
    /// @param count The number of bytes to read.
    /// @param asyncCallback A callback to be called when the operation completes.
    /// @param asyncState User-provided data used to uniquely identify each asynchronous read operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous read operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginRead(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                   int32_t count, AsyncCallback asyncCallback,
                                                                   System::SharedPtr<Object> asyncState) override;
    /// @copydoc System::IO::Stream::EndRead
    ASPOSECPP_SHARED_API int32_t EndRead(System::SharedPtr<IAsyncResult> asyncResult) override;
    /// Initiates an asynchronous write operation.
    /// @param buffer The byte array to write data to.
    /// @param offset The offset in bytes in the specified array.
    /// @param count The number of bytes to write.
    /// @param asyncCallback A callback to be called when the operation completes.
    /// @param asyncState User-provided data used to uniquely identify each asynchronous write operation.
    /// @returns An IAsyncResult object representing the initiated asynchronous write operation.
    ASPOSECPP_SHARED_API System::SharedPtr<IAsyncResult> BeginWrite(System::ArrayPtr<uint8_t> buffer, int32_t offset,
                                                                    int32_t count, AsyncCallback asyncCallback,
                                                                    System::SharedPtr<Object> asyncState) override;
    /// @copydoc System::IO::Stream::EndWrite
    ASPOSECPP_SHARED_API void EndWrite(System::SharedPtr<IAsyncResult> asyncResult) override;

    /// @copydoc System::IO::Stream::Dispose
    ASPOSECPP_SHARED_API void Dispose(bool disposing) override;
    /// @copydoc System::IO::Stream::Close
    ASPOSECPP_SHARED_API void Close() override;

private:
    /// Reads the specified number of bytes from the inner stream and copies them to the specified byte array.
    /// @param buffer The output parameter where the data will be copied.
    /// @param size The number of bytes to read from the inner stream.
    /// @returns The number of bytes that are read from the inner stream.
    size_t read(uint8_t buffer[], size_t size);
    /// Writes the specified number of bytes from the specified byte array to the inner stream.
    /// @param buffer The byte array from which data will copied to the inner stream.
    /// @param size The number of bytes that must be copied.
    void write(const uint8_t buffer[], size_t size);

    /// The stream implementation.
    StreamImplementationPtr stream_impl;
};
}}} // namespace System::Net::Security

DECLARE_USING_ENUM_OPERATORS(System::Net::Security);
