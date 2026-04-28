//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlElementSizeOutputMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words exports element widths and heights to HTML, MHTML and EPUB.
/// 
/// @sa Aspose::Words::Saving::HtmlSaveOptions::get_TableWidthOutputMode
enum class ASPOSE_WORDS_SHARED_CLASS HtmlElementSizeOutputMode
{
    /// All element sizes, both in absolute and relative units, specified in the document are exported.
    All = 0,
    /// Element sizes are exported only if they are specified in relative units in the document.
    /// Fixed sizes are not exported in this mode. Visual agents will calculate missing sizes to make
    /// document layout more natural.
    RelativeOnly = 1,
    /// Element sizes are not exported. Visual agents will build layout automatically according to relationship between elements.
    None = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::HtmlElementSizeOutputMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::HtmlElementSizeOutputMode, const char_t*>, 3>& values();
};
