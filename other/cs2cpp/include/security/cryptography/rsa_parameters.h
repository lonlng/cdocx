/// @file security/cryptography/rsa_parameters.h
#pragma once

#include <system/object.h>
#include <system/array.h>

namespace System { namespace Security { namespace Cryptography {

/// Data structure of RSA algorithm parameters.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
struct ASPOSECPP_SHARED_CLASS RSAParameters : public System::Object
{
private:
    /// This type.
    typedef RSAParameters ThisType;
    /// Parent type.
    typedef System::Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// D parameter of RSA algorithm.
    ByteArrayPtr D;
    /// DP parameter of RSA algorithm.
    ByteArrayPtr DP;
    /// DQ parameter of RSA algorithm.
    ByteArrayPtr DQ;
    /// Exponent parameter of RSA algorithm.
    ByteArrayPtr Exponent;
    /// InverseQ parameter of RSA algorithm.
    ByteArrayPtr InverseQ;
    /// Modulus parameter of RSA algorithm.
    ByteArrayPtr Modulus;
    /// P parameter of RSA algorithm.
    ByteArrayPtr P;
    /// Q parameter of RSA algorithm.
    ByteArrayPtr Q;

    /// Constructor.
    ASPOSECPP_SHARED_API RSAParameters();
};

}}} // namespace System::Security::Cryptography
