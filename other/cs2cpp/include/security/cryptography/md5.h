/// @file security/cryptography/md5.h
#pragma once

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// MD5 hashing algorithm.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS MD5 : public HashAlgorithm
{
    /// This type.
    typedef MD5 ThisType;
    /// Parent type.
    typedef HashAlgorithm BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Pointer type.
    typedef SharedPtr<MD5> ptr;

    /// Creates MD5 algorithm.
    /// @return Newly created algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<MD5> Create();
    /// Creates MD5 algorithm.
    /// @param algName Should be "System.Security.Cryptography.MD5".
    /// @return Newly created algorithm object.
    static ASPOSECPP_SHARED_API SharedPtr<MD5> Create(const String& algName);

protected:
    /// Constructor.
    ASPOSECPP_SHARED_API MD5();
    MEMBER_FUNCTION_MAKE_OBJECT(MD5, CODEPORTING_ARGS(), CODEPORTING_ARGS());
};

}}} // namespace System::Security::Cryptography
