/// @file security/cryptography/hmac.h
#pragma once

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// All implementations of Hash-based Message Authentication Code (HMAC) must inherit this abstract class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HMAC : public HashAlgorithm
{
public:
    /// NOT IMPLEMENTED
    /// @throws NotImplementedException
    static ASPOSECPP_SHARED_API SharedPtr<HMAC> Create();
};

}}} // System::Security::Cryptography
