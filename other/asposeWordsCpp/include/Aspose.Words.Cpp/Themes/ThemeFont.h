//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Themes/ThemeFont.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Themes {

/// Specifies the types of theme font names for document themes.
enum class ASPOSE_WORDS_SHARED_CLASS ThemeFont
{
    /// No theme font.
    None,
    /// Major theme font.
    Major,
    /// Minor theme font.
    Minor
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Themes::ThemeFont>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Themes::ThemeFont, const char_t*>, 3>& values();
};
