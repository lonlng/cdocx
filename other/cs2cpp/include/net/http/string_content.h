/// @file net/http/string_content.h
#pragma once

#include <net/http/byte_array_content.h>

namespace System { namespace Net { namespace Http {

/// Represents HTTP content as a string.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS StringContent : public System::Net::Http::ByteArrayContent
{
    /// This type.
    typedef StringContent ThisType;
    /// Parent type.
    typedef System::Net::Http::ByteArrayContent BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    /// @param content HTTP content.
    ASPOSECPP_SHARED_API StringContent(String content);
    /// Constructs a new instance.
    /// @param content HTTP content.
    /// @param encoding The encoding of HTTP content.
    ASPOSECPP_SHARED_API StringContent(String content, System::SharedPtr<Text::Encoding> encoding);
    /// Constructs a new instance.
    /// @param content HTTP content.
    /// @param encoding The encoding of HTTP content.
    /// @param mediaType The MIME type.
    ASPOSECPP_SHARED_API StringContent(String content, System::SharedPtr<Text::Encoding> encoding, String mediaType);

private:
    /// The default MIME type.
    static const String defaultMediaType;

    /// Converts the specified string to the byte array.
    /// @param content HTTP content.
    /// @param encoding The encoding of HTTP content.
    /// @returns The byte array.
    static System::ArrayPtr<uint8_t> GetContentByteArray(String content, System::SharedPtr<Text::Encoding> encoding);
};

}}} // namespace System::Net::Http
