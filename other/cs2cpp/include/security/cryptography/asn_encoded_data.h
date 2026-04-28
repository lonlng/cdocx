/// @file security/cryptography/asn_encoded_data.h
#pragma once

#include <system/string.h>
#include <system/shared_ptr.h>
#include <system/object.h>
#include <system/array.h>
#include <security/cryptography/oid.h>

namespace System { namespace Security { namespace Cryptography {

/// ASN.1-encoded data.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS AsnEncodedData : public System::Object
{
    /// This type.
    typedef AsnEncodedData ThisType;
    /// Parent type.
    typedef System::Object BaseType;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Copy constructor.
    /// @param asn_encoded_data Object to copy data from.
    ASPOSECPP_SHARED_API AsnEncodedData(const SharedPtr<AsnEncodedData>& asn_encoded_data);
    /// Constructor.
    /// @param raw_data Encoded data in raw byte format.
    ASPOSECPP_SHARED_API AsnEncodedData(const ByteArrayPtr& raw_data);
    /// Constructor.
    /// @param oid Object identifier of encoded data.
    /// @param raw_data Encoded data in raw byte format.
    ASPOSECPP_SHARED_API AsnEncodedData(const SharedPtr<Oid>& oid, const ByteArrayPtr& raw_data);
    /// Constructor.
    /// @param oid Object identifier of encoded data.
    /// @param raw_data Encoded data in raw byte format.
    ASPOSECPP_SHARED_API AsnEncodedData(const String& oid, const ByteArrayPtr& raw_data);

    /// Gets object identifier of encoded data.
    /// @return Object identifier object.
    ASPOSECPP_SHARED_API SharedPtr<Oid> get_Oid() const;
    /// Sets object identifier of encoded data.
    /// @param value Object identifier object.
    ASPOSECPP_SHARED_API void set_Oid(const SharedPtr<Oid>& value);
    /// Gets raw encoded data.
    /// @return Encoded data array in byte format.
    ASPOSECPP_SHARED_API ByteArrayPtr get_RawData() const;
    /// Sets raw encoded data.
    /// @param value Encoded data array in byte format.
    ASPOSECPP_SHARED_API void set_RawData(const ByteArrayPtr& value);

    /// Copies data from different object.
    /// @param asn_encoded_data Object to copy data from.
    virtual ASPOSECPP_SHARED_API void CopyFrom(const SharedPtr<AsnEncodedData>& asn_encoded_data);
    /// Formats data in human-readable form.
    /// @param multi_line Whether to use multiline output.
    /// @return Formatted data.
    virtual ASPOSECPP_SHARED_API String Format(bool multi_line) const;

protected:
    /// Default constructor.
    ASPOSECPP_SHARED_API AsnEncodedData();

    ASPOSECPP_SHARED_API ~AsnEncodedData();

    /// Gets a delimiter for the Format method.
    virtual ASPOSECPP_SHARED_API const String& GetFormatDelimiter() const;

private:
    /// Object identifier.
    SharedPtr<Oid> m_oid;
    /// Data in raw form.
    ByteArrayPtr m_raw_data;
};

}}} // namespace System::Security::Cryptography
