/// @file system/io/file_mode.h
#pragma once

#include <system/details/enum_meta_info.h>

namespace System { namespace IO {

/// Specifies how a file should be opened.
enum class FileMode
{
    /// Create a new file. If the file already exists, an exception is thrown.
    CreateNew = 1,
    /// Create a new file. If the file already exists, it is overwritten.
    Create = 2,
    /// Open an existing file. If the file does not exist, an exception is thrown. 
    Open = 3,
    /// Open an existing file or create a new one if it does not exist.
    OpenOrCreate = 4,
    /// Open an existing file and truncate it so that it is empty. If the file does not exist, an exception is thrown. 
    Truncate = 5,
    /// Open an existing file and seek to the end of it or create a new one if it does not exist.
    Append = 6
};

}} // namespace System::IO

template<>
struct EnumMetaInfo<System::IO::FileMode>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::IO::FileMode, const char16_t*>, 6>& values();
};
