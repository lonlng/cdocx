//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Themes/ThemeColor.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Themes {

/// Specifies the theme colors for document themes.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-styles-and-themes/">Working with Styles and Themes</a> documentation article.
enum class ASPOSE_WORDS_SHARED_CLASS ThemeColor
{
    /// No color.
    None = -1,
    /// Dark main color 1.
    Dark1,
    /// Light main color 1.
    Light1,
    /// Dark main color 2.
    Dark2,
    /// Light main color 2.
    Light2,
    /// Accent color 1.
    Accent1,
    /// Accent color 2.
    Accent2,
    /// Accent color 3.
    Accent3,
    /// Accent color 4.
    Accent4,
    /// Accent color 5.
    Accent5,
    /// Accent color 6.
    Accent6,
    /// Hyperlink color.
    Hyperlink,
    /// Followed hyperlink color.
    FollowedHyperlink,
    /// Text color 1.
    Text1,
    /// Text color 2.
    Text2,
    /// Background color 1.
    Background1,
    /// Background color 2.
    Background2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Themes::ThemeColor>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Themes::ThemeColor, const char_t*>, 17>& values();
};
