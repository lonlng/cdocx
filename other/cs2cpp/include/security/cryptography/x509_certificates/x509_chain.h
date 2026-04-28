/// @file security/cryptography/x509_certificates/x509_chain.h
#pragma once
#include "defines.h"

#include <system/object.h>
#include <security/cryptography/x509_certificates/x509_chain_status.h>

namespace System { namespace Security {namespace Cryptography { namespace X509Certificates {

class X509ChainPolicy;
class X509Certificate2;

/// Represents the X509 certificate chain.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS X509Chain : public System::Object
{
public:
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API SharedPtr<X509ChainPolicy> get_ChainPolicy();
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API ArrayPtr<X509ChainStatus> get_ChainStatus();
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API bool Build(SharedPtr<X509Certificate2> certificate);
};

}}}} // namespace System::Security::Cryptography::X509Certificates
