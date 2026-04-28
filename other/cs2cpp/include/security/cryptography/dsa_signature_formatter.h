/// @file security/cryptography/dsa_signature_formatter.h
#pragma once

#include <security/cryptography/asymmetric_signature_formatter.h>

namespace System { namespace Security { namespace Cryptography {

/// Used to create a DSA signature.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DSASignatureFormatter : public AsymmetricSignatureFormatter
{
public:
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ArrayPtr<uint8_t> CreateSignature(ArrayPtr<uint8_t> rgbHash) override;
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    void SetHashAlgorithm(String strName) override;
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    void SetKey(SharedPtr<AsymmetricAlgorithm> key) override;

};

}}} // System::Security::Cryptography
