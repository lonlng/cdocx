/// @file security/cryptography/ripemd160.h
#pragma once

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// Computes RIPEMD160 hash for input data.
/// In C++ RIPEMD160 is not an abstract class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RIPEMD160 : public HashAlgorithm
{
    /// This type.
    typedef RIPEMD160 ThisType;
    /// Parent type.
    typedef HashAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API RIPEMD160();
    MEMBER_FUNCTION_MAKE_OBJECT(RIPEMD160, CODEPORTING_ARGS(), CODEPORTING_ARGS());

public:
    /// Creates hash algorithm instance.
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<RIPEMD160> Create();
    /// Creates hash algorithm instance.
    /// @param algName Must be "System.Security.Cryptography.RIPEMD160".
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<RIPEMD160> Create(const String& algName);
};

}}} // namespace System::Security::Cryptography
