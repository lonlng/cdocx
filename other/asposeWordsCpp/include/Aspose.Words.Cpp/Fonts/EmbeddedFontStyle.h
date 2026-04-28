//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/EmbeddedFontStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies the style of an embedded font inside a <see cref="Aspose::Words::Fonts::FontInfo">FontInfo</see> object.
enum class ASPOSE_WORDS_SHARED_CLASS EmbeddedFontStyle
{
    /// Specifies the Regular embedded font.
    Regular = 0,
    /// Specifies the Bold embedded font.
    Bold = 1,
    /// Specifies the Italic embedded font.
    Italic = 2,
    /// Specifies the Bold-Italic embedded font.
    BoldItalic = 3
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Fonts::EmbeddedFontStyle);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Fonts);
template<>
struct EnumMetaInfo<Aspose::Words::Fonts::EmbeddedFontStyle>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::EmbeddedFontStyle, const char_t*>, 4>& values();
};
