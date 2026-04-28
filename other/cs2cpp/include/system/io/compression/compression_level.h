/// @file system/io/compression/compression_level.h
#pragma once

namespace System { namespace IO { namespace Compression {

/// Specifies values that indicate whether a compression operation emphasizes speed or compression size.
enum class CompressionLevel
{
    Optimal = 0,
    Fastest = 1,
    NoCompression = 2
};

}}}
