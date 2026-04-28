#pragma once

#include <system/string.h>
#include <system/collections/ilist.h>
#include <security/cryptography/x509_certificates/x509_certificate.h>
#include <security/cryptography/xml/key_info_clause.h>
#include <security/cryptography/xml/x509_issuer_serial.h>
#include <cstdint>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents an 'X509Data' element.
/// Contains X.509v3 certificate information related to the validation or encryption key.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS KeyInfoX509Data : public KeyInfoClause
{
    typedef KeyInfoX509Data ThisType;
    typedef KeyInfoClause BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IList<SharedPtr<X509Certificates::X509Certificate>>> get_Certificates();
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IList<ArrayPtr<uint8_t>>> get_SubjectKeyIds();
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IList<String>> get_SubjectNames();
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IList<X509IssuerSerial>> get_IssuerSerials();

    ASPOSECPP_SHARED_API KeyInfoX509Data();

    ASPOSECPP_SHARED_API void AddCertificate(SharedPtr<X509Certificates::X509Certificate> certificate);
    ASPOSECPP_SHARED_API void AddSubjectKeyId(ArrayPtr<uint8_t> subjectKeyId);
    ASPOSECPP_SHARED_API void AddSubjectName(String subjectName);
    ASPOSECPP_SHARED_API void AddIssuerSerial(String issuerName, String serialNumber);
    ASPOSECPP_SHARED_API void InternalAddIssuerSerial(String issuerName, String serialNumber);
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml() override;
    ASPOSECPP_SHARED_API SharedPtr<System::Xml::XmlElement> GetXml(SharedPtr<System::Xml::XmlDocument> xmlDocument) override;
    ASPOSECPP_SHARED_API void LoadXml(SharedPtr<System::Xml::XmlElement> element) override;

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:

    SharedPtr<Collections::Generic::IList<SharedPtr<X509Certificates::X509Certificate>>> _certificates;
    SharedPtr<Collections::Generic::IList<X509IssuerSerial>> _issuerSerials;
    SharedPtr<Collections::Generic::IList<ArrayPtr<uint8_t>>> _subjectKeyIds;
    SharedPtr<Collections::Generic::IList<String>> _subjectNames;
    ArrayPtr<uint8_t> _CRL;

    void Clear();

};

}}}} // System::Security::Cryptography::Xml
