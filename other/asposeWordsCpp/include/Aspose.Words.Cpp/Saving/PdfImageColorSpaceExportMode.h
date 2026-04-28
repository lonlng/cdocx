//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfImageColorSpaceExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how the color space will be selected for the images in PDF document.
enum class ASPOSE_WORDS_SHARED_CLASS PdfImageColorSpaceExportMode
{
    /// %Aspose.Words automatically selects the most appropriate color space for each image.
    /// 
    /// Most of the images are saved in RGB color space. Also Indexed and Grayscale color spaces may be used. CMYK color space is never used.
    /// 
    /// For some images the color space may be different on different platforms.
    Auto = 0,
    /// %Aspose.Words coverts RGB images to CMYK color space using simple formula.
    /// 
    /// Images in RGB color space are converted to CMYK using formula:
    /// Black   = minimum(1-Red,1-Green,1-Blue).
    /// Cyan    = (1-Red-Black)/(1-Black).
    /// Magenta = (1-Green-Black)/(1-Black).
    /// Yellow  = (1-Blue-Black)/(1-Black).
    /// RGB values are normalized - they are between 0 and 1.0.
    SimpleCmyk = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfImageColorSpaceExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfImageColorSpaceExportMode, const char_t*>, 2>& values();
};
