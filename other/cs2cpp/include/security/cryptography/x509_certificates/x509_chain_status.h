/// @file security/cryptography/x509_certificates/x509_chain_status.h
#pragma once

#include <system/string.h>
#include <system/object.h>
#include <system/enum_helpers.h>

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates { enum class X509ChainStatusFlags; } } } }

namespace System { namespace Security { namespace Cryptography { namespace X509Certificates {

/// Stores the X509 chain status and error information.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class X509ChainStatus : public Object
{
    typedef X509ChainStatus ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    X509ChainStatusFlags get_Status();
    void set_Status(X509ChainStatusFlags value);
    String get_StatusInformation();
    void set_StatusInformation(String value);

    X509ChainStatus();

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    void GetSharedMembers(System::Object::shared_members_type& result) const override;
#endif

private:
    X509ChainStatusFlags pr_Status;
    String _statusInformation;

};

}}}} // System::Security::Cryptography::X509Certificates
