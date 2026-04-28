/// @file drawing/imaging/encoder_value.h
#ifndef _encoder_value_h_
#define _encoder_value_h_

#include "system/enum.h"
#include "system/enum_helpers.h"

namespace System {  namespace Drawing { namespace Imaging {
    /// Specifies the parameter value passed to a JPEG or TIFF image encoder.
    enum class EncoderValue {
    /// The CMYK color space.
    ColorTypeCMYK,
    /// The YCCK color space.
    ColorTypeYCCK,
    /// The LZW compression method.
    CompressionLZW,
    /// Specifies the CCITT3 compression method for a TIFF image.
    CompressionCCITT3,
    /// Specifies the CCITT4 compression method for a TIFF image.
    CompressionCCITT4,
    /// Specifies he RLE compression method for a TIFF image.
    CompressionRle,
    /// Specifies no compression for a TIFF image.
    CompressionNone,
    /// Interlaced mode.
    ScanMethodInterlaced,
    /// Non-interlaced mode.
    ScanMethodNonInterlaced,
    /// Specifies version 87 for a TIFF image.
    VersionGif87,
    /// Specifies version 89a for a GIF image.
    VersionGif89,
    /// Progressive mode.
    RenderProgressive,
    /// Non-progressive mode.
    RenderNonProgressive,
    /// Specifies lossless 90-degree clockwise rotation for a JPEG image.
    TransformRotate90,
    /// Specifies lossless 180-degree rotation for a JPEG image.
    TransformRotate180,
    /// Specifies lossless 270-degree clockwise rotation for a JPEG image.
    TransformRotate270,
    /// Specifies a lossless horizontal flip for a JPEG image.
    TransformFlipHorizontal,
    /// Specifies a lossless vertical flip for a JPEG image.
    TransformFlipVertical,
    /// Multiframe encoding.
    MultiFrame,
    /// The last frame of a multiframe image.
    LastFrame,
    /// The encoder object is to be closed.
    Flush,
    /// Specifies the time frame dimension for a GIF image.
    FrameDimensionTime,
    /// The resolution frame dimension.
    FrameDimensionResolution,
    /// Specifies the page frame dimension for a TIFF image.
    FrameDimensionPage
    };
}}}

/// Specialization for System::Drawing::Imaging::EncoderValue; contains mapping of enum constants
/// to their string representations.
template<>
struct EnumMetaInfo<System::Drawing::Imaging::EncoderValue>
{
    /// This typedef marks this enum as flags one using SFINAE.
    typedef void Flags;
    /// Returns a array of pairs that associate System::Drawing::Imaging::EncoderValue enum's constants with their
    /// string representations.
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Drawing::Imaging::EncoderValue, const char_t*>, 24>& values();
};

#endif
