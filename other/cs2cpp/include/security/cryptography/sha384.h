/// @file security/cryptography/sha384.h
#pragma once

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// Computes SHA384 hash for input data.
/// In C++ SHA384 is not an abstract class.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS SHA384 : public HashAlgorithm
{
    /// This type.
    typedef SHA384 ThisType;
    /// Parent type.
    typedef HashAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API SHA384();
    MEMBER_FUNCTION_MAKE_OBJECT(SHA384, CODEPORTING_ARGS(), CODEPORTING_ARGS());

public:
    /// Creates hash algorithm instance.
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<SHA384> Create();
    /// Creates hash algorithm instance.
    /// @param algName Must be "System.Security.Cryptography.SHA384".
    /// @return Newly created hasher instance.
    static ASPOSECPP_SHARED_API SharedPtr<SHA384> Create(const String& algName);
};

}}} // namespace System::Security::Cryptography
