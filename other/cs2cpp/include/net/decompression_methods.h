/// @file net/decompression_methods.h
#pragma once
#include <system/enum_helpers.h>

namespace System { namespace Net {

/// Enumerates the compression-decompression algorithm.
enum class DecompressionMethods
{
    /// The compression-decompression algorithm is not used.
    None = 0,
    /// The gZip compression-decompression algorithm.
    GZip = 1,
    /// The deflate compression-decompression algorithm.
    Deflate = 2
};

/// @cond
/// Declaration of template arithmetic operators for values of DecompressionMethods enum type.
DECLARE_ENUM_OPERATORS(System::Net::DecompressionMethods);
/// Declaration for argument-dependent lookup to work.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace System::Net

/// Inserts using declarations for arithmetic operators declared in namespace System::Net.
DECLARE_USING_ENUM_OPERATORS(System::Net);
