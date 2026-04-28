//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfZoomBehavior.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the type of zoom applied to a PDF document when it is opened in a PDF viewer.
enum class ASPOSE_WORDS_SHARED_CLASS PdfZoomBehavior
{
    /// How the document is displayed is left to the PDF viewer. Usually the viewer displays the document to fit page width.
    None = 0,
    /// Displays the page using the specified zoom factor.
    ZoomFactor = 1,
    /// Displays the page so it visible entirely.
    FitPage = 2,
    /// Fits the width of the page.
    FitWidth = 3,
    /// Fits the height of the page.
    FitHeight = 4,
    /// Fits the bounding box (rectangle containing all visible elements on the page).
    FitBox = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfZoomBehavior>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfZoomBehavior, const char_t*>, 6>& values();
};
