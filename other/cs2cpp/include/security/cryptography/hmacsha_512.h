/// @file security/cryptography/hmacsha_512.h
#ifndef _aspose_security_cryptography_hmacsha_512_h_
#define _aspose_security_cryptography_hmacsha_512_h_

#include <system/array.h>
#include <system/exceptions.h>

#include <security/cryptography/hash_algorithm.h>

namespace System { namespace Security { namespace Cryptography {

/// Hash-based Message Authentication Code that uses the SHA512 hash function. Partialy implemented.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS HMACSHA512 : public HashAlgorithm
{
    System::ArrayPtr<uint8_t> m_key;
public:
    /// Constructor.
    ASPOSECPP_SHARED_API HMACSHA512();
    /// Constructor.
    /// @param key Hasher key.
    ASPOSECPP_SHARED_API HMACSHA512(const System::ArrayPtr<uint8_t>& key);
    /// Calculates HMAC.
    /// @param buffer Source buffer.
    /// @return Calculated HMAC value.
    ASPOSECPP_SHARED_API ArrayPtr<uint8_t> ComputeHash(const ArrayPtr<uint8_t>& buffer);

protected:
    MEMBER_FUNCTION_MAKE_OBJECT(HMACSHA512, CODEPORTING_ARGS(), CODEPORTING_ARGS());
};

}}}
#endif
