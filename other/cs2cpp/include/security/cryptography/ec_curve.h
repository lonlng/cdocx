/// @file security/cryptography/ec_curve.h
#pragma once

#include <security/cryptography/ec_point.h>
#include <security/cryptography/hash_algorithm_name.h>
#include <security/cryptography/oid.h>
#include <system/nullable.h>

namespace System { namespace Security { namespace Cryptography {

/// An elliptic curve.
struct ECCurve
{
    /// Type of elliptic curve.
    enum class ECCurveType : int32_t
    {
        Implicit = 0,
        PrimeShortWeierstrass = 1,
        PrimeTwistedEdwards = 2,
        PrimeMontgomery = 3,
        Characteristic2 = 4,
        Named = 5,
    };


    /// Coefficient A.
    ByteArrayPtr A;

    /// Coefficient B.
    ByteArrayPtr B;

    /// Base Point.
    ECPoint G;

    /// Order of the group.
    ByteArrayPtr Order;

    /// Cofactor.
    ByteArrayPtr Cofactor;

    /// Seed.
    ByteArrayPtr Seed;

    /// Curve Type.
    ECCurveType CurveType = ECCurveType::Implicit;

    /// Hash algorithm.
    Nullable<HashAlgorithmName> Hash;

    /// Binary polynomial.
    ByteArrayPtr Polynomial;

    /// Prime.
    ByteArrayPtr Prime;

    /// Gets Oid representing the named curve.
    ASPOSECPP_SHARED_API SharedPtr<Oid> get_Oid() const;

    ASPOSECPP_SHARED_API bool get_IsPrime() const;
    ASPOSECPP_SHARED_API bool get_IsCharacteristic2() const;
    ASPOSECPP_SHARED_API bool get_IsExplicit() const;
    ASPOSECPP_SHARED_API bool get_IsNamed() const;

    /// Validate the current curve.
    ASPOSECPP_SHARED_API void Validate() const;

    /// Create a curve from the specified oid.
    static ASPOSECPP_SHARED_API ECCurve CreateFromOid(const SharedPtr<Oid>& oid);

    /// Create a curve from the specified OID firendly name.
    static ASPOSECPP_SHARED_API ECCurve CreateFromFriendlyName(const String& oid_friendly_name);

    /// Create a curve from the specified OID value.
    static ASPOSECPP_SHARED_API ECCurve CreateFromValue(const String& oid_value);
private:
    SharedPtr<Oid> m_oid;

    void set_Oid(const SharedPtr<Oid>& oid);
    bool HasExplicitParameters() const;

    static ECCurve Create(const SharedPtr<Oid>& oid);
};

}}} // namespace System::Security::Cryptography
