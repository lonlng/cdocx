/// @file net/http/headers/via_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value of the 'Via' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ViaHeaderValue : public System::ICloneable
{
    /// This type.
    typedef ViaHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the protocol name from the 'Via' header value.
    /// @returns The protocol name from the 'Via' header value.
    ASPOSECPP_SHARED_API String get_ProtocolName();
    /// Returns the protocol version from the 'Via' header value.
    /// @returns The protocol version from the 'Via' header value.
    ASPOSECPP_SHARED_API String get_ProtocolVersion();
    /// Returns the host and port that the request or response was received by.
    /// @returns The host and port that the request or response was received by.
    ASPOSECPP_SHARED_API String get_ReceivedBy();
    /// Returns the comment from the 'Via' header value.
    /// @returns The comment from the 'Via' header value.
    ASPOSECPP_SHARED_API String get_Comment();

    /// Constructs a new instance.
    /// @param protocolVersion The protocol version.
    /// @param receivedBy The host and port that the request or response was received by.
    ASPOSECPP_SHARED_API ViaHeaderValue(String protocolVersion, String receivedBy);
    /// Constructs a new instance.
    /// @param protocolVersion The protocol version.
    /// @param receivedBy The host and port that the request or response was received by.
    /// @param protocolName The protocol name.
    ASPOSECPP_SHARED_API ViaHeaderValue(String protocolVersion, String receivedBy, String protocolName);
    /// Constructs a new instance.
    /// @param protocolVersion The protocol version.
    /// @param receivedBy The host and port that the request or response was received by.
    /// @param protocolName The protocol name.
    /// @param comment The comment.
    ASPOSECPP_SHARED_API ViaHeaderValue(String protocolVersion, String receivedBy, String protocolName, String comment);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the ViaHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the ViaHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<ViaHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the ViaHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<ViaHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the ViaHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetViaLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);

private:
    /// The protocol name.
    String _protocolName;
    /// The protocol version.
    String _protocolVersion;
    /// The host and port that the request or response was received by.
    String _receivedBy;
    /// The comment.
    String _comment;

    /// Constructs a new instance.
    ViaHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(ViaHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ViaHeaderValue(System::SharedPtr<ViaHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(ViaHeaderValue, CODEPORTING_ARGS(System::SharedPtr<ViaHeaderValue> source), CODEPORTING_ARGS(source));

    /// Parses the specified string and returns the last index of the string representation.
    /// @param input The string that must be parsed.
    /// @param startIndex A start position for parsing.
    /// @param protocolName The output parameter where the 'protocol-name' directive value will be assigned.
    /// @param protocolVersion The output parameter where the 'protocol-version' directive value will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    static int32_t GetProtocolEndIndex(String input, int32_t startIndex, String& protocolName, String& protocolVersion);
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
    /// Checks if the specified string is valid.
    /// @param receivedBy The string that contains the host and port that the request or response was received by.
    /// @throws System::ArgumentException The exception is thrown when the specified string is empty.
    /// @throws System::FormatException The exception is thrown when the specified string contains invalid values.
    static void CheckReceivedBy(String receivedBy);
};

}}}} // namespace System::Net::Http::Headers
