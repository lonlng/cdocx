/// @file net/http/headers/content_range_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/nullable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Content-Range' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ContentRangeHeaderValue : public System::ICloneable
{
    /// This type.
    typedef ContentRangeHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets units used in the range.
    /// @returns Units used in the range.
    ASPOSECPP_SHARED_API String get_Unit();
    /// Sets units used in the range.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Unit(String value);
    /// Gets a position at which data sending must start.
    /// @returns A position at which data sending must start.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_From();
    /// Gets a position at which data sending must stop.
    /// @returns A position at which data sending must stop.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_To();
    /// Gets the length of an entity body.
    /// @returns The length of an entity body.
    ASPOSECPP_SHARED_API Nullable<int64_t> get_Length();
    /// Gets a value that indicates if the length is specified for the current header.
    /// @returns A value that indicates if the length is specified for the current header.
    ASPOSECPP_SHARED_API bool get_HasLength() const;
    /// Gets a value that indicates if the range is specified for the current header.
    ASPOSECPP_SHARED_API bool get_HasRange() const;

    /// Constructs a new instance.
    /// @param from A position at which data sending must start.
    /// @param to A position at which data sending must stop.
    /// @param length The length of an entity body.
    ASPOSECPP_SHARED_API ContentRangeHeaderValue(int64_t from, int64_t to, int64_t length);
    /// Constructs a new instance.
    /// @param length The length of an entity body.
    ASPOSECPP_SHARED_API ContentRangeHeaderValue(int64_t length);
    /// Constructs a new instance.
    /// @param from A position at which data sending must start.
    /// @param to A position at which data sending must s
    ASPOSECPP_SHARED_API ContentRangeHeaderValue(int64_t from, int64_t to);

    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Converts a passed string to an instance of the ContentRangeHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the ContentRangeHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<ContentRangeHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the ContentRangeHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<ContentRangeHeaderValue>& parsedValue);
    /// Converts a passed string from the specified position to an instance of the ContentRangeHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetContentRangeLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// Units used in the range.
    String _unit;
    /// A position at which data sending must start.
    Nullable<int64_t> _from;
    /// A position at which data sending must stop.
    Nullable<int64_t> _to;
    /// The length of an entity body.
    Nullable<int64_t> _length;

    /// Constructs a new instance.
    ContentRangeHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(ContentRangeHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ContentRangeHeaderValue(System::SharedPtr<ContentRangeHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(ContentRangeHeaderValue, CODEPORTING_ARGS(System::SharedPtr<ContentRangeHeaderValue> source), CODEPORTING_ARGS(source));

    /// Tries to parse the specified string representation of a length and returns a parsing result length.
    /// @param input A string representation of a length.
    /// @param current A start position for parsing.
    /// @param lengthLength The output parameter where a calculated length of the parsed string will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryGetLengthLength(String input, int32_t& current, int32_t& lengthLength);
    /// Tries to parse the specified string representation of a range and returns a parsing result length.
    /// @param input A string representation of a range.
    /// @param current A start position for parsing.
    /// @param fromLength The output parameter where a length of the 'from' directive will be assigned.
    /// @param toStartIndex The output parameter where a start position of the 'to' directive will be assigned.
    /// @param toLength The output parameter where a length of the 'to' directive will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryGetRangeLength(String input, int32_t& current, int32_t& fromLength, int32_t& toStartIndex,
                                  int32_t& toLength);
    /// Tries to parse the specified string representation to an instance of the ContentRangeHeaderValue class.
    /// @param input The string representation to parse.
    /// @param unit The range units.
    /// @param fromStartIndex The start position of the 'from' directive.
    /// @param fromLength The length of the 'from' directive.
    /// @param toStartIndex The start position of the 'to' directive.
    /// @param toLength The length of the 'to' directive.
    /// @param lengthStartIndex The start position of the 'length' directive.
    /// @param lengthLength The length of the 'length' directive.
    /// @param parsedValue The output parameter where the parsed instance will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    static bool TryCreateContentRange(String input, String unit, int32_t fromStartIndex, int32_t fromLength,
                                      int32_t toStartIndex, int32_t toLength, int32_t lengthStartIndex,
                                      int32_t lengthLength, System::SharedPtr<Object>& parsedValue);
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
