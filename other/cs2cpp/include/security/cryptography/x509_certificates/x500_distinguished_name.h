/// @file security/cryptography/x509_certificates/x500_distinguished_name.h
#pragma once

#include <security/cryptography/x509_certificates/x500_distinguished_name_flags.h>
#include <security/cryptography/asn_encoded_data.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Represents distinguished name of X509 certificate.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X500DistinguishedName final : public AsnEncodedData
{
    /// This type.
    typedef X500DistinguishedName ThisType;
    /// Parent type.
    typedef AsnEncodedData BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructor.
    /// @param encoded_distinguished_name Object representing distinguished name.
    ASPOSECPP_SHARED_API X500DistinguishedName(const SharedPtr<AsnEncodedData>& encoded_distinguished_name);
    /// Constructor.
    /// @param encoded_distinguished_name Encoded distinguished name.
    ASPOSECPP_SHARED_API X500DistinguishedName(const ByteArrayPtr& encoded_distinguished_name);
    /// Constructor.
    /// @param distinguished_name Distinguished name.
    ASPOSECPP_SHARED_API X500DistinguishedName(const String& distinguished_name);
    /// Copy constructor.
    /// @param distinguishedName Distinguished name to copy data from.
    ASPOSECPP_SHARED_API X500DistinguishedName(const SharedPtr<X500DistinguishedName>& distinguishedName);
    /// Constructor.
    /// @param distinguished_name Distinguished name.
    /// @param flags Bitwise-combined flags specifying name building properties.
    ASPOSECPP_SHARED_API X500DistinguishedName(const String& distinguished_name, X500DistinguishedNameFlags flags);

    /// Gets certificate distinguished name.
    /// @return Name as stored internally.
    ASPOSECPP_SHARED_API String get_Name() const;

    /// Decodes name using parameters specified by flags.
    /// @param flags Bitwise junction of flags to use.
    /// @return Decoded name.
    ASPOSECPP_SHARED_API String Decode(X500DistinguishedNameFlags flags) const;
    /// Formats name for printing.
    /// @param multi_line Whether to use multiline output.
    /// @return X509 distinguished name in a readable form.
    ASPOSECPP_SHARED_API virtual String Format(bool multi_line) const override;

private:
    /// Name value.
    mutable String m_name;
};

}}}} // namespace System::Security::Cryptography::X509Certificates
