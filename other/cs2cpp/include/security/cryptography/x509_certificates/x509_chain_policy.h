#pragma once

#include <system/timespan.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/enum_helpers.h>
#include <system/date_time.h>
#include <security/cryptography/x509_certificates/x509_verification_flags.h>
#include <security/cryptography/x509_certificates/x509_revocation_flag.h>
#include <security/cryptography/x509_certificates/x509_certificate_2_collection.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// The chain policy that will be applied when building an X509 certificate chain.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class X509ChainPolicy final : public Object
{
    typedef X509ChainPolicy ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    SharedPtr<X509Certificate2Collection> get_ExtraStore();
    SharedPtr<X509Certificate2Collection> get_CustomTrustStore();
    X509RevocationFlag get_RevocationFlag();
    void set_RevocationFlag(X509RevocationFlag value);
    X509VerificationFlags get_VerificationFlags();
    void set_VerificationFlags(X509VerificationFlags value);
    DateTime get_VerificationTime();
    void set_VerificationTime(DateTime value);
    TimeSpan get_UrlRetrievalTimeout();
    void set_UrlRetrievalTimeout(TimeSpan value);

    X509ChainPolicy();

    void Reset();

protected:
    SharedPtr<X509Certificate2Collection> _extraStore;
    SharedPtr<X509Certificate2Collection> _customTrustStore;

#ifdef ASPOSE_GET_SHARED_MEMBERS
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    X509RevocationFlag _revocationFlag;
    X509VerificationFlags _verificationFlags;
    DateTime pr_VerificationTime;
    TimeSpan pr_UrlRetrievalTimeout;

};

}}}} // System::Security::Cryptography::X509Certificates
