/// @file net/http/headers/warning_header_value.h
#pragma once

#include "system/date_time_offset.h"
#include <cstdint>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Warning' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS WarningHeaderValue : public System::ICloneable
{
    /// This type.
    typedef WarningHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a warning code.
    /// @returns The warning code.
    ASPOSECPP_SHARED_API int32_t get_Code();
    /// Returns the host attached to the warning.
    /// @returns The host attached to the warning.
    ASPOSECPP_SHARED_API String get_Agent();
    /// Returns the warning text.
    /// @returns The warning text.
    ASPOSECPP_SHARED_API String get_Text();
    /// Returns the datetime of the warning.
    /// @returns The datetime of the warning.
    ASPOSECPP_SHARED_API Nullable<DateTimeOffset> get_Date();

    /// Constructs a new instance.
    /// @param code The warning code.
    /// @param agent The host information.
    /// @param text The warning text.
    ASPOSECPP_SHARED_API WarningHeaderValue(int32_t code, String agent, String text);
    /// Constructs a new instance.
    /// @param code The warning code.
    /// @param agent The host information.
    /// @param text The warning text.
    /// @param date The datetime of the warning.
    ASPOSECPP_SHARED_API WarningHeaderValue(int32_t code, String agent, String text, DateTimeOffset date);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the WarningHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the WarningHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<WarningHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the WarningHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<WarningHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the WarningHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetWarningLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// The warning code.
    int32_t _code;
    /// The host attached to the warning.
    String _agent;
    /// The warning text.
    String _text;
    /// The datetime of the warning.
    Nullable<DateTimeOffset> _date;

    /// Constructs a new instance.
    WarningHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(WarningHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    WarningHeaderValue(System::SharedPtr<WarningHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(WarningHeaderValue, CODEPORTING_ARGS(System::SharedPtr<WarningHeaderValue> source), CODEPORTING_ARGS(source));

    /// Tries to extract the host information from the specified string.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param current The output parameter where the last index of the host information will be assigned.
    /// @param agent A string where the host information will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryReadAgent(String input, int32_t startIndex, int32_t& current, String& agent);
    /// Tries to extract the warning code from the specified string.
    /// @param input A string to parse.
    /// @param current The output parameter where the last index of the warning code will be assigned.
    /// @param code A variable where the warning code will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryReadCode(String input, int32_t& current, int32_t& code);
    /// Tries to extract the datetime of the warning from the specified string.
    /// @param input A string to parse.
    /// @param current The output parameter where the last index of the warning datetime will be assigned.
    /// @param date A variable where the warning datetime will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryReadDate(String input, int32_t& current, Nullable<DateTimeOffset>& date);
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
    /// Checks if the specified code is valid.
    static void CheckCode(int32_t code);
    /// Checks if the specified host information is valid.
    static void CheckAgent(String agent);
};

}}}} // namespace System::Net::Http::Headers
