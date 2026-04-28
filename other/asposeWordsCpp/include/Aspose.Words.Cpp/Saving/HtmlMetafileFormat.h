//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlMetafileFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Indicates the format in which metafiles are saved to HTML documents.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlMetafileFormat
{
    /// Metafiles are rendered to raster PNG images.
    Png = 0,
    /// Metafiles are converted to vector SVG images.
    Svg = 1,
    /// Metafiles are saved as is, without conversion.
    EmfOrWmf = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::HtmlMetafileFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::HtmlMetafileFormat, const char_t*>, 3>& values();
};
