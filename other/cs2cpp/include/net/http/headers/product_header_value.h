/// @file net/http/headers/product_header_value.h
#pragma once

#include <cstdint>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a product token in a value of the 'User-Agent' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ProductHeaderValue : public System::ICloneable
{
    /// This type.
    typedef ProductHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns the product token name.
    /// @returns The product token name.
    ASPOSECPP_SHARED_API String get_Name();
    /// Returns the product token version.
    /// @returns The product token version
    ASPOSECPP_SHARED_API String get_Version();

    /// Constructs a new instance.
    /// @param name The product token name.
    ASPOSECPP_SHARED_API ProductHeaderValue(String name);
    /// Constructs a new instance.
    /// @param name The product token name.
    /// @param version The product token version.
    ASPOSECPP_SHARED_API ProductHeaderValue(String name, String version);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the ProductHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the ProductHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<ProductHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the ProductHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<ProductHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the ProductHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetProductLength(String input, int32_t startIndex,
                                    System::SharedPtr<ProductHeaderValue>& parsedValue);

private:
    /// The product token name.
    String _name;
    /// The product token version.
    String _version;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ProductHeaderValue(System::SharedPtr<ProductHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(ProductHeaderValue, CODEPORTING_ARGS(System::SharedPtr<ProductHeaderValue> source), CODEPORTING_ARGS(source));

    /// Constructs a new instance.
    ProductHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(ProductHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
