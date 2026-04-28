/// @file security/cryptography/oid.h
#pragma once

#include <system/object.h>
#include <system/exceptions.h>
#include <security/cryptography/oid_group.h>

namespace System { namespace Security { namespace Cryptography {

/// Cryptographic object identifier.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS Oid final : public System::Object
{
    /// This type.
    typedef Oid ThisType;
    /// Parent type.
    typedef System::Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Default constructor.
    ASPOSECPP_SHARED_API Oid();
    /// Copy constructor.
    /// @param oid Identifier to copy data from.
    ASPOSECPP_SHARED_API Oid(const SharedPtr<Oid>& oid);
    /// Constructor.
    /// @param oid String value of object identifier.
    ASPOSECPP_SHARED_API Oid(const String& oid);
    /// Constructor.
    /// @param value String value of object identifier.
    /// @param friendly_name User-friendly object name.
    ASPOSECPP_SHARED_API Oid(const String& value, const String& friendly_name);

    /// Gets user-friendly name of object.
    /// @return User-friendly object name.
    ASPOSECPP_SHARED_API String get_FriendlyName() const;
    /// Sets user-friendly name of object.
    /// @param value User-friendly object name.
    ASPOSECPP_SHARED_API void set_FriendlyName(const String& value);
    /// Gets object identifier string.
    /// @return Object identifier.
    ASPOSECPP_SHARED_API String get_Value() const;
    /// Sets object identifier string.
    /// @param value Object identifier.
    ASPOSECPP_SHARED_API void set_Value(const String& value);

    /// Create OID object from the specified OID friendly name.
    /// @param friendly_name User-friendly object name.
    /// @param group OID group to search in.
    static ASPOSECPP_SHARED_API SharedPtr<Oid> FromFriendlyName(const String& friendly_name, OidGroup group);

    /// Create OID object from the specified OID value.
    /// @param oid_value OID value.
    /// @param group OID group to search in.
    static ASPOSECPP_SHARED_API SharedPtr<Oid> FromOidValue(const String& oid_value, OidGroup group);

private:
    /// Object identifier.
    String m_value;
    /// User-friendly object name.
    mutable String m_friendly_name;
};

}}} // namespace System::Security::Cryptography
