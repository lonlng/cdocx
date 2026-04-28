/// @file net/http/headers/name_value_with_parameters_header_value.h
#pragma once

#include <system/collections/icollection.h>

#include <net/http/headers/name_value_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a key/value pair with parameters to use in headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS NameValueWithParametersHeaderValue
    : public System::Net::Http::Headers::NameValueHeaderValue
{
    /// This type.
    typedef NameValueWithParametersHeaderValue ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::NameValueHeaderValue BaseType;
    /// Parent type.
    typedef System::ICloneable BaseType1;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns parameters from the current instance.
    /// @returns Parameters from the current instance.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<NameValueHeaderValue>>>
        get_Parameters();

    /// Constructs a new instance.
    /// @param name The header name.
    ASPOSECPP_SHARED_API NameValueWithParametersHeaderValue(String name);
    /// Constructs a new instance.
    /// @param name The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API NameValueWithParametersHeaderValue(String name, String value);
    /// Constructs a new instance.
    ASPOSECPP_SHARED_API NameValueWithParametersHeaderValue();

    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;

    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Converts a passed string to an instance of the NameValueWithParametersHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the NameValueWithParametersHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<NameValueWithParametersHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the NameValueWithParametersHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<NameValueWithParametersHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the NameValueWithParametersHeaderValue
    /// class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetNameValueWithParametersLength(String input, int32_t startIndex,
                                                    System::SharedPtr<Object>& parsedValue);

protected:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ASPOSECPP_SHARED_API NameValueWithParametersHeaderValue(System::SharedPtr<NameValueWithParametersHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(NameValueWithParametersHeaderValue, CODEPORTING_ARGS(System::SharedPtr<NameValueWithParametersHeaderValue> source), CODEPORTING_ARGS(source));

private:
    /// The delegate that is used to create instances of the NameValueHeaderValue class.
    static HeaderFunc<System::SharedPtr<NameValueHeaderValue>> s_nameValueCreator;
    /// The collection of the header parameters.
    System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> _parameters;

    /// Creates an instance of the NameValueHeaderValue class.
    static System::SharedPtr<NameValueHeaderValue> CreateNameValue();
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
