/// @file net/http/headers/range_item_header_value.h
#pragma once

#include <cstdint>
#include <system/collections/icollection.h>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a range of bytes in a value of the 'Range' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RangeItemHeaderValue : public System::ICloneable
{
    /// This type.
    typedef RangeItemHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a position at which data sending must start.
    /// @returns The position at which data sending must start.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_From();
    /// Returns a position at which data sending must stop.
    /// @returns The position at which data sending must stop.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_To();

    /// Constructs a new instance.
    /// @param from The position at which data sending must start.
    /// @param to The position at which data sending must stop.
    ASPOSECPP_SHARED_API RangeItemHeaderValue(Nullable<int64_t> from, Nullable<int64_t> to);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string from the specified position to the collection of the RangeItemHeaderValue-class
    /// instances.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param rangeCollection An instance where a parsed collection will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetRangeItemListLength(
        String input, int32_t startIndex,
        System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<RangeItemHeaderValue>>> rangeCollection);
    /// Converts a passed string from the specified index to an instance of the RangeItemHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetRangeItemLength(String input, int32_t startIndex,
                                      System::SharedPtr<RangeItemHeaderValue>& parsedValue);

private:
    /// The position at which data sending must start.
    Nullable<int64_t> _from;
    /// The position at which data sending must stop.
    Nullable<int64_t> _to;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    RangeItemHeaderValue(System::SharedPtr<RangeItemHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(RangeItemHeaderValue, CODEPORTING_ARGS(System::SharedPtr<RangeItemHeaderValue> source), CODEPORTING_ARGS(source));

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
