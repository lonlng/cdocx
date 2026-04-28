/// @file security/cryptography/dsa_signature_deformatter.h
#pragma once

#include <security/cryptography/asymmetric_signature_deformatter.h>

namespace System { namespace Security { namespace Cryptography {

/// Used for verifying the DSA signatures.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS DSASignatureDeformatter : public AsymmetricSignatureDeformatter
{
public:
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API void SetHashAlgorithm(String strName) override;
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API void SetKey(SharedPtr<AsymmetricAlgorithm> key) override;
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    ASPOSECPP_SHARED_API bool VerifySignature(ArrayPtr<uint8_t> rgbHash, ArrayPtr<uint8_t> rgbSignature) override;
};

}}} // System::Security::Cryptography
