/// @file security/cryptography/x509_certificates/x509_certificate_2.h
#pragma once

#include <system/string.h>
#include <system/date_time.h>
#include <system/exceptions.h>
#include <system/security/secure_string.h>
#include <security/cryptography/asymmetric_algorithm.h>
#include <security/cryptography/oid.h>
#include <security/cryptography/x509_certificates/public_key.h>
#include <security/cryptography/x509_certificates/x509_certificate.h>
#include <security/cryptography/x509_certificates/x509_name_type.h>
#include <security/cryptography/x509_certificates/x509_key_storage_flags.h>
#include <security/cryptography/x509_certificates/x509_extension_collection.h>
#include <security/cryptography/x509_certificates/x500_distinguished_name.h>

namespace System { namespace Security { namespace Cryptography {

class RSA;
class DSA;
class ECDsa;

}}} // namespace System::Security::Cryptography

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Represents X509 certificate.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509Certificate2 : public X509Certificate
{
    RTTI_INFO(System::Security::Cryptography::X509Certificates::X509Certificate2, ::System::BaseTypesInfo<System::Security::Cryptography::X509Certificates::X509Certificate>)

public:
    /// Constructs empty X509Certificate2.
    ASPOSECPP_SHARED_API X509Certificate2();
    /// Constructor.
    /// @param filename File to load certificate from.
    ASPOSECPP_SHARED_API X509Certificate2(const String& filename);
    /// Constructor.
    /// @param cert An X509Certificate object.
    ASPOSECPP_SHARED_API X509Certificate2(const SharedPtr<X509Certificate>& cert);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Certificate password.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data, const String& password);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Certificate password.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data, const SecureStringPtr& password);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Certificate password.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate.
    /// @param password Certificate password.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Certificate password.
    ASPOSECPP_SHARED_API X509Certificate2(const String& filename, const String& password);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Certificate password.
    ASPOSECPP_SHARED_API X509Certificate2(const String& filename, const SecureStringPtr& password);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Certificate password.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate2(const String& filename, const String& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param filename File to load certificate from.
    /// @param password Certificate password.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate2(const String& filename, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags);
    /// Constructor.
    /// @param raw_data Sequence of bytes that represents encoded certificate (public part).
    /// @param private_key Sequence of bytes that represents private key.
    /// @param key_storage_flags Flags indicating how to store key.
    ASPOSECPP_SHARED_API X509Certificate2(const ByteArrayPtr& raw_data, const ByteArrayPtr& private_key, X509KeyStorageFlags key_storage_flags);

    /// Gets algorithm used to create signature of a certificate.
    /// @return Algorithm identifier.
    ASPOSECPP_SHARED_API SharedPtr<Oid> get_SignatureAlgorithm() const;
    /// Gets a sertificate PublicKey object.
    /// @return A PublicKey object.
    ASPOSECPP_SHARED_API SharedPtr<PublicKey> get_PublicKey() const;
    /// Checks whether the certificate has private key.
    /// @return True if private key existst, false otherwise.
    ASPOSECPP_SHARED_API bool get_HasPrivateKey() const;
    /// Gets private key associated with certificate.
    /// @return Private key object (or nullptr if unset).
    ASPOSECPP_SHARED_API SharedPtr<AsymmetricAlgorithm> get_PrivateKey() const;
    /// Sets or clears private key associated with certificate.
    /// @param value Private key object (or nullptr to unset).
    ASPOSECPP_SHARED_API void set_PrivateKey(const SharedPtr<AsymmetricAlgorithm>& value);
    /// Gets collection of extension objects associated with certificate.
    /// @return Collection of extensions.
    ASPOSECPP_SHARED_API X509ExtensionCollectionPtr get_Extensions() const;
    /// Gets certificate raw data.
    /// @return Raw byte data of the certificate.
    ASPOSECPP_SHARED_API ByteArrayPtr get_RawData() const;
    /// Gets the name of party that issued a certificate.
    /// @return Issuer name object.
    ASPOSECPP_SHARED_API SharedPtr<X500DistinguishedName> get_IssuerName() const;
    /// Gets the subject name from a certificate.
    /// @return Subject name object.
    ASPOSECPP_SHARED_API SharedPtr<X500DistinguishedName> get_SubjectName() const;
    /// Gets the serial number of a certificate.
    /// @return Serial number.
    ASPOSECPP_SHARED_API String get_SerialNumber() const;
    /// Gets the local date and time on which a certificate becomes valid.
    /// @return Date and time.
    ASPOSECPP_SHARED_API DateTime get_NotBefore() const;
    /// Gets the local date and time after which a certificate is no longer valid.
    /// @return Date and time.
    ASPOSECPP_SHARED_API DateTime get_NotAfter() const;
    /// Gets the certificate's friendly name.
    /// @return The certificate's friendly name.
    ASPOSECPP_SHARED_API String get_FriendlyName() const;
    /// Sets the certificate's friendly name.
    /// @param value The certificate's friendly name.
    ASPOSECPP_SHARED_API void set_FriendlyName(const String& value);
    /// Gets a value indicating that certificate is archived.
    /// @return true if the certificate is archived, otherwise - false.
    ASPOSECPP_SHARED_API bool get_Archived() const;
    /// Sets a value indicating that certificate is archived.
    /// @param value true if the certificate is archived, otherwise - false.
    ASPOSECPP_SHARED_API void set_Archived(bool value) const;
    /// Gets certificate format version.
    /// @return Certificate version.
    ASPOSECPP_SHARED_API int32_t get_Version() const;
    /// Gets the certificate thumbprint.
    /// @return The certificate thumbprint.
    ASPOSECPP_SHARED_API String get_Thumbprint() const;

    /// Gets subject or issuer name from certificate.
    /// @param name_type Name formatting options.
    /// @param for_issuer If true, returns issuer name, else returns subject name.
    /// @return Formatted issuer or subject name.
    ASPOSECPP_SHARED_API String GetNameInfo(X509NameType name_type, bool for_issuer) const;
    /// Verifies certificate chain.
    /// @return True if the certificate is valid, false otherwise.
    ASPOSECPP_SHARED_API bool Verify() const;
    /// Resets the certificate state.
    ASPOSECPP_SHARED_API void Reset() override;
    /// Returns the certificate information in text format.
    /// @param verbose true to display additional certificate information.
    /// @return The certificate information.
    ASPOSECPP_SHARED_API String ToString(bool verbose) const override;
    /// Returns the certificate information in text format.
    /// @return The certificate information.
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Imports information from the specified certificate file.
    /// @param filename The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    ASPOSECPP_SHARED_API void Import(const String& filename, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags) override;
    /// Imports information from the specified certificate file.
    /// @param filename The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    ASPOSECPP_SHARED_API void Import(const String& filename, const String& password, X509KeyStorageFlags key_storage_flags) override;
    /// Imports information from the specified certificate data.
    /// @param data The X.509 certificate data.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data, const SecureStringPtr& password, X509KeyStorageFlags key_storage_flags) override;
    /// Imports information from the specified certificate data.
    /// @param data The certificate file name.
    /// @param password The password required to access the certificate data.
    /// @param key_storage_flags 
    ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data, const String& password, X509KeyStorageFlags key_storage_flags) override;
    /// Imports information from the specified certificate file.
    /// @param filename The certificate file name.
    ASPOSECPP_SHARED_API void Import(const String& filename) override;
    /// Imports information from the specified certificate data.
    /// @param data The certificate file name.
    ASPOSECPP_SHARED_API void Import(const ByteArrayPtr& data) override;

    /// Gets the type of certificate contained in the specified byte array.
    /// @param raw_data Certificate data.
    /// @return Type of X.509 certificate.
    static ASPOSECPP_SHARED_API X509ContentType GetCertContentType(const ByteArrayPtr& raw_data);
    /// Gets the type of certificate contained in the specified file.
    /// @param filename Certificate file name.
    /// @return Type of X.509 certificate.
    static ASPOSECPP_SHARED_API X509ContentType GetCertContentType(const String& filename);

    // Extension methods

    /// Gets RSA public key.
    ASPOSECPP_SHARED_API SharedPtr<RSA> GetRSAPublicKey() const;
    /// Gets RSA private key;
    ASPOSECPP_SHARED_API SharedPtr<RSA> GetRSAPrivateKey() const;
    /// Gets RSA public key.
    ASPOSECPP_SHARED_API SharedPtr<DSA> GetDSAPublicKey() const;
    /// Gets RSA private key;
    ASPOSECPP_SHARED_API SharedPtr<DSA> GetDSAPrivateKey() const;
    /// Gets RSA public key.
    ASPOSECPP_SHARED_API SharedPtr<ECDsa> GetECDsaPublicKey() const;
    /// Gets RSA private key;
    ASPOSECPP_SHARED_API SharedPtr<ECDsa> GetECDsaPrivateKey() const;

protected:
    ASPOSECPP_SHARED_API ~X509Certificate2();
};

}}}} // namespace System::Security::Cryptography::X509Certificates
