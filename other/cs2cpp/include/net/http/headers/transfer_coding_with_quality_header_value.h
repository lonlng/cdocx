/// @file net/http/headers/transfer_coding_with_quality_header_value.h
#pragma once

#include <system/nullable.h>
#include <net/http/headers/transfer_coding_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a value with an additional quality of the 'Accept-Encoding' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS TransferCodingWithQualityHeaderValue final
    : public System::Net::Http::Headers::TransferCodingHeaderValue
{
    /// This type.
    typedef TransferCodingWithQualityHeaderValue ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::TransferCodingHeaderValue BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets the quality value of the 'Accept-Encoding' header.
    /// @returns The quality value of the 'Accept-Encoding' header.
    ASPOSECPP_SHARED_API Nullable<double> get_Quality();
    /// Sets the quality value of the 'Accept-Encoding' header.
    /// @param value The quality value that must be set.
    ASPOSECPP_SHARED_API void set_Quality(Nullable<double> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API TransferCodingWithQualityHeaderValue();
    /// Constructs a new instance.
    /// @param value The header value.
    ASPOSECPP_SHARED_API TransferCodingWithQualityHeaderValue(String value);
    /// Constructs a new instance.
    /// @param value The header value.
    /// @param quality The quality value of the 'Accept-Encoding' header.
    ASPOSECPP_SHARED_API TransferCodingWithQualityHeaderValue(String value, double quality);

    /// Converts a passed string to an instance of the TransferCodingWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the TransferCodingWithQualityHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<TransferCodingWithQualityHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the TransferCodingWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<TransferCodingWithQualityHeaderValue>& parsedValue);

private:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    TransferCodingWithQualityHeaderValue(System::SharedPtr<TransferCodingWithQualityHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(TransferCodingWithQualityHeaderValue, CODEPORTING_ARGS(System::SharedPtr<TransferCodingWithQualityHeaderValue> source), CODEPORTING_ARGS(source));

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
