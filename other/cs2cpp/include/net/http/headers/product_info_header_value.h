/// @file net/http/headers/product_info_header_value.h
#pragma once

#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>

#include <net/http/headers/product_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a product or a comment in a value of the 'User-Agent' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ProductInfoHeaderValue : public System::ICloneable
{
    /// This type.
    typedef ProductInfoHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Returns a product.
    /// @returns The product.
    ASPOSECPP_SHARED_API System::SharedPtr<ProductHeaderValue> get_Product();
    /// Returns a comment.
    /// @returns The comment.
    ASPOSECPP_SHARED_API String get_Comment();

    /// Constructs a new instance.
    /// @param productName The product token name.
    /// @param productVersion The product token version.
    ASPOSECPP_SHARED_API ProductInfoHeaderValue(String productName, String productVersion);
    /// Constructs a new instance.
    /// @param product The ProductHeaderValue-class instance that is used to initialize the new instance.
    ASPOSECPP_SHARED_API ProductInfoHeaderValue(System::SharedPtr<ProductHeaderValue> product);
    /// Constructs a new instance.
    /// @param comment The comment.
    ASPOSECPP_SHARED_API ProductInfoHeaderValue(String comment);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the ProductInfoHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the ProductInfoHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<ProductInfoHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the ProductInfoHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<ProductInfoHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the ProductInfoHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetProductInfoLength(String input, int32_t startIndex,
                                        System::SharedPtr<ProductInfoHeaderValue>& parsedValue);

private:
    /// The product.
    System::SharedPtr<ProductHeaderValue> _product;
    // The comment.
    String _comment;

    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    ProductInfoHeaderValue(System::SharedPtr<ProductInfoHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(ProductInfoHeaderValue, CODEPORTING_ARGS(System::SharedPtr<ProductInfoHeaderValue> source), CODEPORTING_ARGS(source));

    /// Constructs a new instance.
    ProductInfoHeaderValue();
    MEMBER_FUNCTION_MAKE_OBJECT(ProductInfoHeaderValue, CODEPORTING_ARGS(), CODEPORTING_ARGS());

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
