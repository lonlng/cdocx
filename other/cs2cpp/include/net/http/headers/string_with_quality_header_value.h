/// @file net/http/headers/string_with_quality_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value with an additional quality of a string header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS StringWithQualityHeaderValue : public System::ICloneable
{
    /// This type.
    typedef StringWithQualityHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a value.
    /// @returns The value.
    ASPOSECPP_SHARED_API String get_Value();
    /// Returns a quality.
    /// @returns The quality.
    ASPOSECPP_SHARED_API Nullable<double> get_Quality();

    /// Constructs a new instance.
    /// @param value The value.
    ASPOSECPP_SHARED_API StringWithQualityHeaderValue(String value);
    /// Constructs a new instance.
    /// @param value The value.
    /// @param quality The quality.
    ASPOSECPP_SHARED_API StringWithQualityHeaderValue(String value, double quality);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the StringWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the RangeHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<StringWithQualityHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the StringWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<StringWithQualityHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the StringWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetStringWithQualityLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// The value.
    String _value;
    /// The quality.
    Nullable<double> _quality;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    StringWithQualityHeaderValue(System::SharedPtr<StringWithQualityHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(StringWithQualityHeaderValue, CODEPORTING_ARGS(System::SharedPtr<StringWithQualityHeaderValue> source), CODEPORTING_ARGS(source));
    /// Constructs a new instance.
    StringWithQualityHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(StringWithQualityHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Tries to parse the specified string representation to an instance of the StringWithQualityHeaderValue class.
    /// @param input A string representation of a StringWithQualityHeaderValue-class instance.
    /// @param result The output parameter where a calculated length of the parsed string will be assigned.
    /// @param index A start position for parsing.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryReadQuality(String input, System::SharedPtr<StringWithQualityHeaderValue> result, int32_t& index);

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
