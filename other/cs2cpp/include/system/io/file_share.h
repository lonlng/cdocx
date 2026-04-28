/// @file system/io/file_share.h
#pragma once

#include <system/enum_helpers.h>
#include <system/details/enum_meta_info.h>

namespace System { namespace IO {

/// Specifies what kind of access other FileStream objects can have to a file being opened.
enum class FileShare
{
    /// No access.
    None = 0,
    /// Read-only access.
    Read = 1,
    /// Write-only access.
    Write = 2,
    /// Read and Write access.
    ReadWrite = 3,
    /// The file can be deleted.
    Delete = 4,
    /// Makes file handle inheritable by child processes.
    Inheritable = 16
};

/// @cond
/// Declaration of template arithmetic operators for values of the FileShare enum type.
DECLARE_ENUM_OPERATORS(System::IO::FileShare);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace System::IO

/// Inserts using declaratios for arithmetic operators declared in namespace System::IO.
DECLARE_USING_ENUM_OPERATORS(System::IO);

template<>
struct EnumMetaInfo<System::IO::FileShare>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::IO::FileShare, const char16_t*>, 6>& values();
};
