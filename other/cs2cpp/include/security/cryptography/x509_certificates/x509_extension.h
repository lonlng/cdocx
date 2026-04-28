/// @file security/cryptography/x509_certificates/x509_extension.h
#pragma once

#include <security/cryptography/asn_encoded_data.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Extension object to keep extra information associated with X.509 certificate.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509Extension : public AsnEncodedData
{
    /// This type.
    typedef X509Extension ThisType;
    /// Parent type.
    typedef System::Security::Cryptography::AsnEncodedData BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructor.
    /// @param encoded_extension Encoded data associated with certificate.
    /// @param critical Criticality sign.
    ASPOSECPP_SHARED_API X509Extension(const SharedPtr<AsnEncodedData>& encoded_extension, bool critical);
    /// Constructor.
    /// @param oid Object identifier associated with extension.
    /// @param raw_data Raw data associated with certificate.
    /// @param critical Criticality sign.
    ASPOSECPP_SHARED_API X509Extension(const SharedPtr<Oid>& oid, const ByteArrayPtr& raw_data, bool critical);
    /// Constructor.
    /// @param oid Object identifier associated with extension.
    /// @param raw_data Raw data associated with certificate.
    /// @param critical Criticality sign.
    ASPOSECPP_SHARED_API X509Extension(const String& oid, const ByteArrayPtr& raw_data, bool critical);

    /// Checks whether extension is critical.
    /// @return True if extension is critical, false otherwise.
    ASPOSECPP_SHARED_API bool get_Critical() const;
    /// Defines whether extension is critical.
    /// @param value True to make extension critical, false otherwise.
    ASPOSECPP_SHARED_API void set_Critical(bool value);

    /// Copies extension data from other object.
    /// @param asn_encoded_data Object to copy data from.
    virtual ASPOSECPP_SHARED_API void CopyFrom(const SharedPtr<AsnEncodedData>& asn_encoded_data) override;

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API X509Extension();
    /// Constructor.
    /// @param oid_value Object identifier value.
    ASPOSECPP_SHARED_API X509Extension(const String& oid_value);

private:
    /// Criticality sign.
    bool m_critical = false;
};

}}}} // namespace System::Security::Cryptography::X509Certificates
