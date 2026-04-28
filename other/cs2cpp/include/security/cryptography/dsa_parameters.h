/// @file security/cryptography/dsa_parameters.h
#pragma once

#include <system/object.h>
#include <system/array.h>

namespace System { namespace Security { namespace Cryptography {

/// Data structure of DSA algorithm parameters.
/// This type should be allocated on stack and passed to functions by value or by reference.
/// Never use System::SmartPtr class to manage objects of this type.
struct ASPOSECPP_SHARED_CLASS DSAParameters : public System::Object
{
private:
    /// This type.
    typedef DSAParameters ThisType;
    /// Parent type.
    typedef System::Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// P parameter of the DSA algorithm.
    ByteArrayPtr P;
    /// Q parameter of the DSA algorithm.
    ByteArrayPtr Q;
    /// G parameter of the DSA algorithm.
    ByteArrayPtr G;
    /// Y parameter of the DSA algorithm.
    ByteArrayPtr Y;
    /// J parameter of the DSA algorithm.
    ByteArrayPtr J;
    /// X parameter of the DSA algorithm.
    ByteArrayPtr X;
    /// Seed of the DSA algorithm.
    ByteArrayPtr Seed;
    /// Counter of the DSA algorithm.
    int32_t Counter = 0;

    /// Constructor.
    ASPOSECPP_SHARED_API DSAParameters();
};

}}} // namespace System::Security::Cryptography
