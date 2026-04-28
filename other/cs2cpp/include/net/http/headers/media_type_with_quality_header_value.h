/// @file net/http/headers/media_type_with_quality_header_value.h
#pragma once

#include <system/nullable.h>

#include <net/http/headers/media_type_header_value.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a MIME type with an additional quality factor in a value of the 'Content-Type' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS MediaTypeWithQualityHeaderValue final
    : public System::Net::Http::Headers::MediaTypeHeaderValue
{
    /// This type.
    typedef MediaTypeWithQualityHeaderValue ThisType;
    /// Parent type.
    typedef System::Net::Http::Headers::MediaTypeHeaderValue BaseType;
    /// Parent type.
    typedef System::ICloneable BaseType1;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a quality value.
    /// @returns A quality value.
    ASPOSECPP_SHARED_API Nullable<double> get_Quality();
    /// Sets a quality value.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_Quality(Nullable<double> value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API MediaTypeWithQualityHeaderValue();
    /// Constructs a new instance.
    /// @param mediaType A string representation of the media-type header value.
    ASPOSECPP_SHARED_API MediaTypeWithQualityHeaderValue(String mediaType);
    /// Constructs a new instance.
    /// @param mediaType A string representation of the media-type header value.
    /// @param quality A quality value.
    ASPOSECPP_SHARED_API MediaTypeWithQualityHeaderValue(String mediaType, double quality);

    /// Converts a passed string to an instance of the MediaTypeWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the MediaTypeWithQualityHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<MediaTypeWithQualityHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the MediaTypeWithQualityHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<MediaTypeWithQualityHeaderValue>& parsedValue);

private:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    MediaTypeWithQualityHeaderValue(System::SharedPtr<MediaTypeWithQualityHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(MediaTypeWithQualityHeaderValue, CODEPORTING_ARGS(System::SharedPtr<MediaTypeWithQualityHeaderValue> source), CODEPORTING_ARGS(source));

    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
