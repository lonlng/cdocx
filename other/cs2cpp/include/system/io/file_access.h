/// @file system/io/file_access.h
#pragma once

#include <system/enum_helpers.h>
#include <system/details/enum_meta_info.h>

namespace System { namespace IO {

/// Specifies the type of access when opening the file.
enum class FileAccess
{
    /// Read-only access.
    Read = 0x00000001,
    /// Write-only access.
    Write = 0x00000002,
    /// Read and write access.
    ReadWrite = Read | Write
};

/// @cond
/// Declaration of template arithmetic operators for values of the FileAccess enum type.
DECLARE_ENUM_OPERATORS(System::IO::FileAccess);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace System::IO

/// Inserts using declaratios for arithmetic operators declared in namespace System::IO.
DECLARE_USING_ENUM_OPERATORS(System::IO);

template<>
struct EnumMetaInfo<System::IO::FileAccess>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::IO::FileAccess, const char16_t*>, 3>& values();
};
