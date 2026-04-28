/// @file net/http/headers/retry_condition_header_value.h
#pragma once

#include "system/date_time_offset.h"
#include <cstdint>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/timespan.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Retry-After' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS RetryConditionHeaderValue : public System::ICloneable
{
    /// This type.
    typedef RetryConditionHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a date value.
    /// @returns The date value.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_Date();
    /// Returns the delta value.
    /// @returns The delta value.
    ASPOSECPP_SHARED_API Nullable<TimeSpan> get_Delta();

    /// Constructs a new instance.
    /// @param date The date value.
    ASPOSECPP_SHARED_API RetryConditionHeaderValue(DateTimeOffset date);
    /// Constructs a new instance.
    /// @param delta The delta value.
    ASPOSECPP_SHARED_API RetryConditionHeaderValue(TimeSpan delta);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the RetryConditionHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the RangeHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<RetryConditionHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the RetryConditionHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<RetryConditionHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the RetryConditionHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetRetryConditionLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// The date value.
    Nullable<DateTimeOffset> _date;
    /// The delta value.
    Nullable<TimeSpan> _delta;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    RetryConditionHeaderValue(System::SharedPtr<RetryConditionHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(RetryConditionHeaderValue, CODEPORTING_ARGS(System::SharedPtr<RetryConditionHeaderValue> source), CODEPORTING_ARGS(source));

    /// Constructs a new instance.
    RetryConditionHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(RetryConditionHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
