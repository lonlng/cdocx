/// @file security/cryptography/x509_certificates/x509_key_usage_extension.h
#pragma once

#include <security/cryptography/x509_certificates/x509_extension.h>
#include <security/cryptography/x509_certificates/x509_key_usage_flags.h>
#include <system/nullable.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Extension object to keep extra information about the usage of a key.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509KeyUsageExtension : public X509Extension
{
    /// This type.
    typedef X509KeyUsageExtension ThisType;
    /// Parent type.
    typedef System::Security::Cryptography::X509Certificates::X509Extension BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Default constructor.
    ASPOSECPP_SHARED_API X509KeyUsageExtension();

    /// Constructor.
    /// @param encoded_key_usage Encoded data of key usages.
    /// @param critical Criticality sign.
    ASPOSECPP_SHARED_API X509KeyUsageExtension(const SharedPtr<AsnEncodedData>& encoded_key_usage,
        bool critical);

    /// Constructor.
    /// @param key_usages Key usages.
    /// @param critical Criticality sign.
    ASPOSECPP_SHARED_API X509KeyUsageExtension(X509KeyUsageFlags key_usages, bool critical); 

    /// Gets key usages.
    ASPOSECPP_SHARED_API X509KeyUsageFlags get_KeyUsages();

    /// Copies extension data from other object.
    /// @param asn_encoded_data Object to copy data from.
    ASPOSECPP_SHARED_API void CopyFrom(const SharedPtr<AsnEncodedData>& asn_encoded_data) override;

protected:
    /// @see AsnEncodedData::GetFormatDelimiter
    ASPOSECPP_SHARED_API const String& GetFormatDelimiter() const override;

private:
    Nullable<X509KeyUsageFlags> m_usage_flags;
};

}}}} // namespace System::Security::Cryptography::X509Certificates
