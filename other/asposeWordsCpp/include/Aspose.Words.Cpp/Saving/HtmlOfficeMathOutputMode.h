//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlOfficeMathOutputMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words exports OfficeMath to HTML, MHTML and EPUB.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlOfficeMathOutputMode
{
    /// OfficeMath is converted to HTML as image specified by \<img\> tag.
    Image = 0,
    /// OfficeMath is converted to HTML using MathML.
    MathML = 1,
    /// OfficeMath is converted to HTML as sequence of runs specified by \<span\> tags.
    Text = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::HtmlOfficeMathOutputMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::HtmlOfficeMathOutputMode, const char_t*>, 3>& values();
};
