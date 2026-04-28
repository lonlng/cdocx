//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/CssStyleSheetType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how CSS (Cascading Style Sheet) styles are exported to HTML.
/// 
/// @sa Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetType
enum class ASPOSE_WORDS_SHARED_CLASS CssStyleSheetType
{
    /// CSS styles are written inline (as a value of the <b>%style</b> attribute on every element).
    Inline = 0,
    /// CSS styles are written separately from the content in a style sheet embedded in the HTML file.
    Embedded = 1,
    /// CSS styles are written separately from the content in a style sheet in an external file.
    /// The HTML file links the style sheet.
    External = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::CssStyleSheetType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::CssStyleSheetType, const char_t*>, 3>& values();
};
