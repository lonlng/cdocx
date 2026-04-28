/// @file net/http/headers/range_header_value.h
#pragma once

#include <system/collections/icollection.h>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/http/headers/object_collection.h>
#include <net/http/headers/range_item_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Range' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RangeHeaderValue : public System::ICloneable
{
    /// This type.
    typedef RangeHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a unit.
    /// @returns The unit.
    ASPOSECPP_SHARED_API String get_Unit();
    /// Sets a unit.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Unit(String value);
    /// Returns the collection of the ranges.
    /// @returns The collection of the ranges.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<RangeItemHeaderValue>>>
        get_Ranges();

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API RangeHeaderValue();
    /// Constructs a new instance.
    /// @param from The position at which data sending must start.
    /// @param to The position at which data sending must stop.
    ASPOSECPP_SHARED_API RangeHeaderValue(Nullable<int64_t> from, Nullable<int64_t> to);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the RangeHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the RangeHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<RangeHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the RangeHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<RangeHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the RangeHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetRangeLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// The unit value.
    String _unit;
    /// The collection of the ranges.
    System::SharedPtr<ObjectCollection<System::SharedPtr<RangeItemHeaderValue>>> _ranges;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    RangeHeaderValue(System::SharedPtr<RangeHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(RangeHeaderValue, CODEPORTING_ARGS(System::SharedPtr<RangeHeaderValue> source), CODEPORTING_ARGS(source));

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
