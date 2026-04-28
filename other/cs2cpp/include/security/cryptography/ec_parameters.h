/// @file security/cryptography/ec_parameters.h
#pragma once

#include <security/cryptography/ec_point.h>
#include <security/cryptography/ec_curve.h>

namespace System { namespace Security { namespace Cryptography {

/// Public and private key parameters of an elliptic curve.
struct ECParameters
{
    /// Public point.
    ECPoint Q;

    /// Private Key.
    ByteArrayPtr D;

    /// The Curve.
    ECCurve Curve;

    /// Validate current parameters.
    ASPOSECPP_SHARED_API void Validate() const;
};

}}} // namespace System::Security::Cryptography
