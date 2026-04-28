/// @file system/io/seekorigin.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace IO {

/// Specifies the reference position in the stream relative to which the position
/// to seek to is specified.
enum class SeekOrigin
{
    /// Beginning of the stream.
    Begin = 0,
    /// Current stream position.
    Current,
    /// End of the stream.
    End
};

}} // namespace System::IO

template<>
struct EnumMetaInfo<System::IO::SeekOrigin>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::IO::SeekOrigin, const char16_t*>, 3>& values();
};
