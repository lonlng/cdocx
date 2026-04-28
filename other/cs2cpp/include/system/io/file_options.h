/// @file system/io/file_options.h
#pragma once

#include <cstdint>
#include <system/enum_helpers.h>
#include <system/details/enum_meta_info.h>
#include <limits>

namespace System { namespace IO {

/// Represents advanced options for creating FileStream object.
enum class FileOptions {
    /// No additional options.
    None = 0,
    /// The file is encrypted. NOT IMPLEMENTED.
    Encrypted = 0x4000,
    /// The file should be automatically deleted when it is not in use anymore.
    DeleteOnClose = 0x4000000,
    /// The file shoud be accesses sequentially.
    SequentialScan = 0x8000000,
    /// The file is accessed randomly.
    RandomAccess = 0x10000000,
    /// The file can be used for asynchronous I/O operations.
    Asynchronous = 0x40000000,
    /// All writes should go directly to the disk bypassing any intermediate cache.
    WriteThrough = (std::numeric_limits<int32_t>::min)(),  // 0x80000000
};

/// @cond
/// Declaration of template arithmetic operators for values of the FileOptions enum type.
DECLARE_ENUM_OPERATORS(System::IO::FileOptions);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace System::IO

/// Inserts using declaratios for arithmetic operators declared in namespace System::IO.
DECLARE_USING_ENUM_OPERATORS(System::IO);

template<>
struct EnumMetaInfo<System::IO::FileOptions>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::IO::FileOptions, const char16_t*>, 7>& values();
};
