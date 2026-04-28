/// @file net/http/byte_array_content.h
#pragma once

#include <cstdint>
#include <system/array.h>
#include <system/io/stream.h>
#include <system/shared_ptr.h>
#include <net/http/http_content.h>

namespace System { namespace Net { namespace Http {

/// Represents HTTP content as a byte array.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS ByteArrayContent : public System::Net::Http::HttpContent
{
    /// This type.
    typedef ByteArrayContent ThisType;
    /// Parent type.
    typedef System::Net::Http::HttpContent BaseType;

    /// Base types.
    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    /// RTTI information.
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:
    /// Constructs a new instance.
    /// @param content Content that is used to initialize a new instance.
    ASPOSECPP_SHARED_API ByteArrayContent(System::ArrayPtr<uint8_t> content);
    /// Constructs a new instance.
    /// @param content Content that is used to initialize a new instance.
    /// @param offset The offset in bytes in the specified array.
    /// @param count The number of bytes in the specified array starting from the 'offset' parameter.
    ASPOSECPP_SHARED_API ByteArrayContent(System::ArrayPtr<uint8_t> content, int32_t offset, int32_t count);

    /// Tries to calculate the byte array length.
    /// @param length The output parameter where the calculated length will be assigned.
    /// @returns True when the length is successfully calculated, otherwise false.
    ASPOSECPP_SHARED_API bool TryComputeLength(int64_t& length) override;

protected:
    /// Creates a stream that is used to read content.
    /// @returns A stream that is used to read content.
    System::SharedPtr<IO::Stream> CreateContentReadStream() override;
    /// Writes content to the specified stream.
    /// @param stream A stream where the content will be written.
    void SerializeToStream(System::SharedPtr<IO::Stream> stream) override;

private:
    /// Content.
    System::ArrayPtr<uint8_t> _content;
    /// The offset in the array.
    int32_t _offset;
    /// The number of bytes in the array starting from the 'offset' parameter.
    int32_t _count;
};

}}} // namespace System::Net::Http
