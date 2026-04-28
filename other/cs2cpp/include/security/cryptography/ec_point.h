/// @file security/cryptography/ec_point.h
#pragma once

#include <system/array.h>

namespace System { namespace Security { namespace Cryptography {

/// Point on an elliptic curve.
struct ECPoint
{
    ByteArrayPtr X;
    ByteArrayPtr Y;
};

}}} // namespace System::Security::Cryptography
