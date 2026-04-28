/// @file security/cryptography/x509_certificates/x509_certificate.h
#pragma once

#include <defines.h>
#include <system/object.h>
#include <system/array.h>
#include <system/idisposable.h>
#include <system/date_time.h>
#include <system/security/secure_string.h>
#include <security/cryptography/x509_certificates/x509_content_type.h>
#include <security/cryptography/x509_certificates/x509_key_storage_flags.h>
#include <security/cryptography/hash_algorithm_name.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

class X500DistinguishedName;
namespace Details { struct X509CertificateImpl; }

/// X.509 v.3 certificate.
/// Encrypted certificates are not supported.
/// Only X509KeyStorageFlags::DefaultKeySet flag is supported.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509Certificate
    : public virtual Object
    , public IDisposable
    // public IDeserializationCallback, public ISerializable
{
    RTTI_INFO(System::Security::Cryptography::X509Certificates::X509Certificate, ::System::BaseTypesInfo<System::Object>)

public:
    /// Pointer type.
    typedef SharedPtr<X509Certificate> Ptr;

    X509Certificate(const X509Certificate&) = delete;
    X509Certificate& operator=(const X509Certificate&) = delete;

    /// Constructor.
    ASPOSECPP_SHARED_API X509Certificate();
    /// Constructor.
    /// @param data Sequence of bytes that represents encoded certificate.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& data);
    /// Constructor.
    /// @param filename File to load certificate from.
    ASPOSECPP_SHARED_API X509Certificate(const String& filename);
    
    /// Constructor.
    /// @param cert A certificate used to initialize this object.
    ASPOSECPP_SHARED_API X509Certificate(const SharedPtr<X509Certificate>& cert);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Password used to access the certificate data.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& raw_data, const String& password);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Password used to access the certificate data.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& raw_data, const SecureStringPtr& password);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Password used to access the certificate data.
    ASPOSECPP_SHARED_API X509Certificate(const String& filename, const String& password);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Password used to access the certificate data.
    ASPOSECPP_SHARED_API X509Certificate(const String& filename, const SecureStringPtr& password);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Password used to access the certificate data.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& raw_data, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Password used to access the certificate data.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& raw_data, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Password used to access the certificate data.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate(const String& filename, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Password used to access the certificate data.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate(const String& filename, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate (public part).
    /// @param private_key Sequence of bytes that represents private key.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate(const ByteArrayPtr& raw_data, const ByteArrayPtr& private_key, X509KeyStorageFlags key_storage_flags);

    ASPOSECPP_SHARED_API void Dispose() override;

    /// Gets a handle to Microsoft Cryptographic API certificate context.
    /// @return Always returns 0.
    ASPOSECPP_SHARED_API IntPtr get_Handle() const;
    /// Gets subject distinguished name from certificate.
    /// @return Subject name of certificate.
    ASPOSECPP_SHARED_API String get_Subject() const;
    /// Gets name of the certificate authority that issued the X.509v3 certificate.
    /// @return Issuer name.
    ASPOSECPP_SHARED_API String get_Issuer() const;

    /// Gets hash for the current object as an array of bytes.
    /// @return The hash value.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetCertHash() const;
    /// Gets hash for the current object as an array of bytes.
    /// @param hash_algorithm Hash algorithm name.
    /// @return The hash value.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetCertHash(const HashAlgorithmName& hash_algorithm) const;
    /// Gets SHA1 hash for the current object as a hexadecimal string.
    /// @return The hexadecimal string.
    virtual ASPOSECPP_SHARED_API String GetCertHashString() const;
    /// Gets SHA1 hash for the current object as a hexadecimal string.
    /// @param hash_algorithm Hash algorithm name.
    /// @return The hexadecimal string.
    virtual ASPOSECPP_SHARED_API String GetCertHashString(const HashAlgorithmName& hash_algorithm) const;
    /// Gets effective date of the current sertificate.
    /// @return The effective date of the current certificate.
    virtual ASPOSECPP_SHARED_API String GetEffectiveDateString() const;
    /// Gets expiration date of the current sertificate.
    /// @return The expiration date of the current certificate.
    virtual ASPOSECPP_SHARED_API String GetExpirationDateString() const;
    /// Gets name of the certificate format.
    /// @return The format name.
    virtual ASPOSECPP_SHARED_API String GetFormat() const;
    /// Gets name of the certification authority that issued the current certificate.
    /// @return The name of the certification authority.
    virtual ASPOSECPP_SHARED_API String GetIssuerName() const;
    /// Gets key information for the current certificate as a string.
    /// @return The key information.
    virtual ASPOSECPP_SHARED_API String GetKeyAlgorithm() const;
    /// Gets key information for the current certificate as an array of bytes.
    /// @return The key information.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetKeyAlgorithmParameters() const;
    /// Gets key information for the current certificate as a hexadecimal string.
    /// @return The key information.
    virtual ASPOSECPP_SHARED_API String GetKeyAlgorithmParametersString() const;
    /// Gets name of the principal to witch the current sertificate was issued.
    /// @return The name of the principal.
    virtual ASPOSECPP_SHARED_API String GetName() const;
    /// Gets public key from certificate as array of bytes.
    /// @return Byte representation of public key.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetPublicKey() const;
    /// Gets public key from certificate as a hexadecimal string.
    /// @return The public key as a hexadecimal string.
    virtual ASPOSECPP_SHARED_API String GetPublicKeyString() const;
    /// Gets raw data from certificate as array of bytes.
    /// @return Byte representation of certificate data.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetRawCertData() const;
    /// Gets raw data from certificate as a hexadecimal string.
    /// @return The certificate data as a hexadecimal string.
    virtual ASPOSECPP_SHARED_API String GetRawCertDataString() const;
    /// Gets serial number from certificate as array of bytes.
    /// @return Byte representation of certificate serial number.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr GetSerialNumber() const;
    /// Gets serial number from certificate as a hexadecimal string.
    /// @return The certificate serial number a hexadecimal string.
    virtual ASPOSECPP_SHARED_API String GetSerialNumberString() const;

    /// Exports the current object to a byte array using the specified format. NOT IMPLEMENTED.
    /// @param content_type Specifies how to format the output data.
    /// @return An array of bytes that represents the current object.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr Export(X509ContentType content_type) const;
    /// Exports the current object to a byte array using the specified format. NOT IMPLEMENTED.
    /// @param content_type Specifies how to format the output data.
    /// @param password The password required to access certificate data.
    /// @return An array of bytes that represents the current object.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr Export(X509ContentType content_type, const SecureStringPtr& password) const;
    /// Exports the current object to a byte array using the specified format. NOT IMPLEMENTED.
    /// @param content_type Specifies how to format the output data.
    /// @param password The password required to access certificate data.
    /// @return An array of bytes that represents the current object.
    virtual ASPOSECPP_SHARED_API ByteArrayPtr Export(X509ContentType content_type, const String& password) const;

    /// Imports information from the specified certificate file. NOT IMPLEMENTED.
    /// @param filename The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    virtual ASPOSECPP_SHARED_API void Import(const String& filename, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Imports information from the specified certificate file. NOT IMPLEMENTED.
    /// @param filename The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    virtual ASPOSECPP_SHARED_API void Import(const String& filename, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Imports information from the specified certificate data. NOT IMPLEMENTED.
    /// @param data The X.509 certificate data.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    virtual ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Imports information from the specified certificate data. NOT IMPLEMENTED.
    /// @param data The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    virtual ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Imports information from the specified certificate file. NOT IMPLEMENTED.
    /// @param filename The certificate file name.
    virtual ASPOSECPP_SHARED_API void Import(const String& filename);
    /// Imports information from the specified certificate data. NOT IMPLEMENTED.
    /// @param data The certificate file name.
    virtual ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data);

    /// Resets the certificate state.
    virtual ASPOSECPP_SHARED_API void Reset();

    /// Compares two certificates.
    /// @param obj Certificate to compare with current object.
    /// @return true if the current certificate is equal to the specified certificate.
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<Object> obj) override;

    /// Returns the certificate information in text format.
    /// @param verbose true to display additional certificate information.
    /// @return The certificate information.
    virtual ASPOSECPP_SHARED_API String ToString(bool verbose) const;
    /// Returns the certificate information in text format.
    /// @return The certificate information.
    ASPOSECPP_SHARED_API String ToString() const override;

    /// Gets certificate hash code.
    /// @return Hash code as a integer.
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;

    /// Creates sertificate from the specified PKCS7 file.
    /// @param filename Certificate file name.
    /// @return The newly created certificate.
    static ASPOSECPP_SHARED_API SharedPtr<X509Certificate> CreateFromCertFile(const String& filename);
    /// Creates sertificate from the specified signed file.
    /// @param filename Certificate file name.
    /// @return The newly created certificate.
    static ASPOSECPP_SHARED_API SharedPtr<X509Certificate> CreateFromSignedFile(const String& filename);

protected:
    /// Certificate implementation.
    const std::unique_ptr<Details::X509CertificateImpl> m_pimpl;

    ASPOSECPP_SHARED_API ~X509Certificate();

    void VerifyCertificateCreated() const;
    ByteArrayPtr GetRawCertHash() const;
    ByteArrayPtr GetRawKeyAlgorithmParameters() const;
    ByteArrayPtr GetRawPublicKey() const;
    ByteArrayPtr GetRawSerialNumber() const;
    DateTime GetNotBefore() const;
    DateTime GetNotAfter() const;
    SharedPtr<X500DistinguishedName> GetIssuerNameInternal() const;
    SharedPtr<X500DistinguishedName> GetSubjectNameInternal() const;

    static String FormatDate(DateTime dt);
};

}}}} // namespace System::Security::Cryptography::X509Certificates
