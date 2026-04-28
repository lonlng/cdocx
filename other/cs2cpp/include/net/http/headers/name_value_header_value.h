/// @file net/http/headers/name_value_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>
#include <system/text/string_builder.h>

#include <net/http/headers/http_headers.h>
#include <net/http/headers/object_collection.h>

namespace System {
class ObjectExt;
}

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a key/value pair to use in headers.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS NameValueHeaderValue : public virtual System::ICloneable
{
    /// This type.
    typedef NameValueHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    friend class System::ObjectExt;

public:
    /// Returns a name of the current instance.
    /// @returns The name of the current instance.
    ASPOSECPP_SHARED_API String get_Name();
    /// Gets a value of the current instance.
    /// @returns The value of the current instance.
    ASPOSECPP_SHARED_API String get_Value();
    /// Sets a value of the current instance.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Value(String value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API NameValueHeaderValue();
    /// Constructs a new instance.
    /// @param name The header name.
    ASPOSECPP_SHARED_API NameValueHeaderValue(String name);
    /// Constructs a new instance.
    /// @param name The header name.
    /// @param value The header value.
    ASPOSECPP_SHARED_API NameValueHeaderValue(String name, String value);

    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// Converts a passed string to an instance of the NameValueHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the NameValueHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<NameValueHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the NameValueHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<NameValueHeaderValue>& parsedValue);
    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// Returns a string representation of the collection of the NameValueHeaderValue-class instances.
    /// @param values The collection of the NameValueHeaderValue-class instances.
    /// @param separator A string separator.
    /// @param leadingSeparator The value that indicates if the string separator must be added before the first 
    /// collection item.
    /// @param destination An instance where a string representation will be assigned.
    ASPOSECPP_SHARED_API static void ToString(System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> values,
                         char16_t separator, bool leadingSeparator, System::SharedPtr<Text::StringBuilder> destination);
    /// Returns a string representation of the collection of the NameValueHeaderValue-class instances.
    /// @param values The collection of the NameValueHeaderValue-class instances.
    /// @param separator A string separator.
    /// @param leadingSeparator The value that indicates if the string separator must be added before the first 
    /// collection item.
    /// @returns A string representation of the collection of the NameValueHeaderValue-class instances.
    ASPOSECPP_SHARED_API static String ToString(System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> values,
                           char16_t separator, bool leadingSeparator);
    /// Returns a hash code of all the collection items.
    /// @param values The collection of the NameValueHeaderValue-class instances.
    /// @returns A hash code of all the collection items.
    ASPOSECPP_SHARED_API static int32_t GetHashCode(System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> values);
    /// Converts a passed string from the specified index to an instance of the NameValueHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetNameValueLength(String input, int32_t startIndex,
                                      System::SharedPtr<NameValueHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the NameValueHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param nameValueCreator A function that is used to create new instances of the NameValueHeaderValue class.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetNameValueLength(String input, int32_t startIndex,
                                      HeaderFunc<System::SharedPtr<NameValueHeaderValue>> nameValueCreator,
                                      System::SharedPtr<NameValueHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to the collection of the NameValueHeaderValue-class instances
    /// and returns the length of a parsed substring.
    /// @param input A string to analyze.
    /// @param startIndex A start position for analyzing.
    /// @param delimiter A string that is used to delimit items in the specified string.
    /// @param nameValueCollection The output parameter where a parsed collection will be assigned.
    /// @returns The length of a parsed substring.
    ASPOSECPP_SHARED_API static int32_t GetNameValueListLength(
        String input, int32_t startIndex, char16_t delimiter,
        System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> nameValueCollection);
    /// Finds the NameValueHeaderValue-class instance in a collection by the specified name.
    /// @param values The collection of the NameValueHeaderValue-class instances.
    /// @param name The name to look for.
    /// @returns The NameValueHeaderValue-class instance when it is found, otherwise nullptr.
    ASPOSECPP_SHARED_API static System::SharedPtr<NameValueHeaderValue>
        Find(System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> values, String name);
    /// Returns the length of a value from the specified index.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @returns The length of a value from the specified index.
    ASPOSECPP_SHARED_API static int32_t GetValueLength(String input, int32_t startIndex);

protected:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ASPOSECPP_SHARED_API NameValueHeaderValue(System::SharedPtr<NameValueHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(NameValueHeaderValue, CODEPORTING_ARGS(System::SharedPtr<NameValueHeaderValue> source), CODEPORTING_ARGS(source));

private:
    /// The delegate that is used to create instances of the NameValueHeaderValue class.
    static HeaderFunc<System::SharedPtr<NameValueHeaderValue>> s_defaultNameValueCreator;
    /// The header name.
    String _name;
    /// The header value.
    String _value;

    /// Checks if the specified name and value are valid.
    static void CheckNameValueFormat(String name, String value);
    /// Throws an exception when the specified value is empty/nullptr or has an invalid format.
    static void CheckValueFormat(String value);
    /// Creates an instance of the NameValueHeaderValue class.
    static System::SharedPtr<NameValueHeaderValue> CreateNameValue();
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
