/// @file net/http/headers/authentication_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents values of the 'Authorization', 'ProxyAuthorization', 'WWW-Authenticate', and 'Proxy-Authenticate' headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS AuthenticationHeaderValue : public System::ICloneable
{
    /// This type.
    typedef AuthenticationHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the scheme that can be used for authorization.
    /// @returns The scheme that can be used for authorization.
    ASPOSECPP_SHARED_API String get_Scheme();
    /// Gets the credentials containing the authentication information.
    /// @returns The credentials containing the authentication information.
    ASPOSECPP_SHARED_API String get_Parameter();

    /// Constructor.
    /// @param scheme The scheme that can be used for authorization.
    ASPOSECPP_SHARED_API AuthenticationHeaderValue(String scheme);
    /// Constructor.
    /// @param scheme The scheme that can be used for authorization.
    /// @param parameter The credentials containing the authentication information.
    ASPOSECPP_SHARED_API AuthenticationHeaderValue(String scheme, String parameter);

    /// @copydoc System::Object::ToString()
    ASPOSECPP_SHARED_API virtual String ToString() const override;
    /// @copydoc System::Object::Equals()
    ASPOSECPP_SHARED_API virtual bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode()
    ASPOSECPP_SHARED_API virtual int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the AuthenticationHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the AuthenticationHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<AuthenticationHeaderValue> Parse(String input);
    /// Trying to convert a passed string to an instance of the AuthenticationHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<AuthenticationHeaderValue>& parsedValue);
    /// Parses the specified string and returns the last index of the string representation.
    /// @param input The string that must be parsed.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue The output parameter where a parsed value will be assigned.
    /// @returns The length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetAuthenticationLength(String input, int32_t startIndex, System::SharedPtr<Object>& parsedValue);
    /// @copydoc System::ICloneable::Clone()
    System::SharedPtr<Object> Clone() override;

private:
    /// The scheme that can be used for authorization.
    String _scheme;
    /// The credentials containing the authentication information.
    String _parameter;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    AuthenticationHeaderValue(System::SharedPtr<AuthenticationHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(AuthenticationHeaderValue, CODEPORTING_ARGS(System::SharedPtr<AuthenticationHeaderValue> source), CODEPORTING_ARGS(source));

    /// Constructs a new instance.
    AuthenticationHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(AuthenticationHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// Tries to skip the first 'blob' part in the specified scheme.
    /// @param input The scheme.
    /// @param current The start index.
    /// @param parameterEndIndex The end index.
    /// @returns False if the specified string is invalid-quoted, otherwise true.
    static bool TrySkipFirstBlob(String input, int32_t& current, int32_t& parameterEndIndex);
    /// Tries to get an end index of a parameter in the specified scheme.
    /// @param input The scheme.
    /// @param parseEndIndex The index where the parsing must be stopped.
    /// @param parameterEndIndex The output parameter where the last index of a parameter will be assigned.
    /// @returns True when the last index of a parameter is found, otherwise false.
    static bool TryGetParametersEndIndex(String input, int32_t& parseEndIndex, int32_t& parameterEndIndex);
};

}}}} // namespace System::Net::Http::Headers
