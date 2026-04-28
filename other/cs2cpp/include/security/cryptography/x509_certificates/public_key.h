/// @file security/cryptography/x509_certificates/public_key.h
#pragma once

#include <security/cryptography/oid.h>
#include <security/cryptography/asn_encoded_data.h>
#include <security/cryptography/asymmetric_algorithm.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Represents a X509-certificate's public key information.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS PublicKey final : public Object
{
    RTTI_INFO(System::Security::Cryptography::X509Certificates::PublicKey, ::System::BaseTypesInfo<System::Object>)

public:
    /// Constructor.
    /// @param oid Identifier object that represents the public key.
    /// @param parameters ASN.1-encoded public key parameters.
    /// @param key_value ASN.1-encoded public key value.
    ASPOSECPP_SHARED_API PublicKey(const SharedPtr<Oid>& oid, const SharedPtr<AsnEncodedData>& parameters, const SharedPtr<AsnEncodedData> key_value);

    /// Gets an RSACryptoServiceProvider or DSACryptoServiceProvider.
    /// @return AsymmetricAlgorithm object representing the public key.
    ASPOSECPP_SHARED_API SharedPtr<AsymmetricAlgorithm> get_Key() const;

    /// Gets identifier (OID) of the public key.
    /// @return Object identifier.
    ASPOSECPP_SHARED_API SharedPtr<Oid> get_Oid() const;

    /// Gets ASN.1-encoded public key value.
    /// @return ASN.1-encoded public key value.
    ASPOSECPP_SHARED_API SharedPtr<AsnEncodedData> get_EncodedKeyValue() const;

    /// Gets ASN.1-encoded public key parameters.
    /// @return ASN.1-encoded public key parameters.
    ASPOSECPP_SHARED_API SharedPtr<AsnEncodedData> get_EncodedParameters() const;

private:
    const SharedPtr<Oid> m_oid;
    mutable SharedPtr<AsymmetricAlgorithm> m_key;
    const SharedPtr<AsnEncodedData> m_encoded_key_value;
    const SharedPtr<AsnEncodedData> m_encoded_parameters;

    ASPOSECPP_SHARED_API ~PublicKey();
};

}}}} // namespace System::Security::Cryptography::X509Certificates
