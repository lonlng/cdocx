/// @file net/http/headers/media_type_header_value.h
#pragma once

#include <cstdint>
#include <system/collections/icollection.h>
#include <system/icloneable.h>
#include <system/object.h>
#include <system/shared_ptr.h>
#include <system/string.h>

#include <net/http/headers/name_value_header_value.h>
#include <net/http/headers/object_collection.h>

namespace System { namespace Net { namespace Http { namespace Headers {

/// Represents a MIME type in a value of the 'Content-Type' header.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS MediaTypeHeaderValue : public virtual System::ICloneable
{
    /// This type.
    typedef MediaTypeHeaderValue ThisType;
    /// Parent type.
    typedef System::ICloneable BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Gets a character set.
    /// @returns A character set.
    ASPOSECPP_SHARED_API String get_CharSet();
    /// Sets a character set.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_CharSet(String value);
    /// Returns the value parameters of the media-type header.
    /// @returns The value parameters of the media-type header.
    ASPOSECPP_SHARED_API System::SharedPtr<Collections::Generic::ICollection<System::SharedPtr<NameValueHeaderValue>>>
        get_Parameters();
    /// Gets a value of the media-type header.
    /// @returns A value of the media-type header.
    ASPOSECPP_SHARED_API String get_MediaType();
    /// Sets a value of the media-type header.
    /// @param value The value that must be set.
    ASPOSECPP_SHARED_API void set_MediaType(String value);

    /// Constructs a new instance.
    ASPOSECPP_SHARED_API MediaTypeHeaderValue();
    /// Constructs a new instance.
    /// @param mediaType A string representation of the media-type header value.
    ASPOSECPP_SHARED_API MediaTypeHeaderValue(String mediaType);

    /// @copydoc System::Object::ToString
    ASPOSECPP_SHARED_API String ToString() const override;
    /// @copydoc System::Object::Equals
    ASPOSECPP_SHARED_API bool Equals(System::SharedPtr<Object> obj) override;
    /// @copydoc System::Object::GetHashCode
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Converts a passed string to an instance of the MediaTypeHeaderValue class.
    /// @param input A string to parse.
    /// @returns An instance of the MediaTypeHeaderValue class.
    ASPOSECPP_SHARED_API static System::SharedPtr<MediaTypeHeaderValue> Parse(String input);
    /// Tries to convert a passed string to an instance of the MediaTypeHeaderValue class.
    /// @param input A string to parse.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns True when the parsing is successfully done, otherwise false.
    ASPOSECPP_SHARED_API static bool TryParse(String input, System::SharedPtr<MediaTypeHeaderValue>& parsedValue);
    /// Converts a passed string from the specified index to an instance of the MediaTypeHeaderValue class.
    /// @param input A string to parse.
    /// @param startIndex A start position for parsing.
    /// @param mediaTypeCreator The delegate that is used to create instances of the MediaTypeHeaderValue class.
    /// @param parsedValue An instance where a parsed object will be assigned.
    /// @returns Returns the length of a parsed substring, otherwise 0.
    ASPOSECPP_SHARED_API static int32_t GetMediaTypeLength(String input, int32_t startIndex,
                                      HeaderFunc<System::SharedPtr<MediaTypeHeaderValue>> mediaTypeCreator,
                                      System::SharedPtr<MediaTypeHeaderValue>& parsedValue);

protected:
    /// The copy constructor.
    /// @param source An instance that must be copied to the current one.
    MediaTypeHeaderValue(System::SharedPtr<MediaTypeHeaderValue> source);
    MEMBER_FUNCTION_MAKE_OBJECT(MediaTypeHeaderValue, CODEPORTING_ARGS(System::SharedPtr<MediaTypeHeaderValue> source), CODEPORTING_ARGS(source));

private:
    /// A string representation of the optional 'charset' parameter name.
    static const String charSet;
    /// The collection of the MIME type parameters.
    System::SharedPtr<ObjectCollection<System::SharedPtr<NameValueHeaderValue>>> _parameters;
    /// A MIME type string representation.
    String _mediaType;

    /// Calculates the length of the MIME type from the specified index.
    static int32_t GetMediaTypeExpressionLength(String input, int32_t startIndex, String& mediaType);
    /// Checks if the specified MIME type has a valid format.
    static void CheckMediaTypeFormat(String mediaType, String parameterName);
    /// @copydoc System::ICloneable::Clone
    System::SharedPtr<Object> Clone() override;
};

}}}} // namespace System::Net::Http::Headers
