/// @file security/cryptography/sha512.h
#pragma once

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// Computes SHA512 hash for input data.
/// In C++ SHA512 is not an abstract class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SHA512 : public HashAlgorithm
{
    /// This type.
    typedef SHA512 ThisType;
    /// Parent type.
    typedef HashAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API SHA512();
    MEMBER_FUNCTION_MAKE_OBJECT(SHA512, CODEPORTING_ARGS(), CODEPORTING_ARGS());

public:
    /// Creates hash algorithm instance.
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<SHA512> Create();
    /// Creates hash algorithm instance.
    /// @param algName Must be "System.Security.Cryptography.SHA512".
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<SHA512> Create(const String& algName);
};

}}} // namespace System::Security::Cryptography
