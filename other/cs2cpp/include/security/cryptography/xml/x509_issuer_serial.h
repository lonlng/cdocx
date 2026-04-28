#pragma once

#include <system/string.h>
#include <system/object.h>

namespace System { namespace Security { namespace Cryptography { namespace Xml {

/// Represents the 'X509IssuerSerial' element of the XML signature.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509IssuerSerial : public Object
{
    typedef X509IssuerSerial ThisType;
    typedef Object BaseType;

    typedef BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:
    ASPOSECPP_SHARED_API String get_IssuerName();
    ASPOSECPP_SHARED_API void set_IssuerName(String value);
    ASPOSECPP_SHARED_API String get_SerialNumber();
    ASPOSECPP_SHARED_API void set_SerialNumber(String value);

    ASPOSECPP_SHARED_API X509IssuerSerial(String issuerName, String serialNumber);
    ASPOSECPP_SHARED_API X509IssuerSerial();

private:
    String pr_IssuerName;
    String pr_SerialNumber;
};

}}}} // System::Security::Cryptography::Xml
