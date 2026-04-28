//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/ZoomType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Possible values for how large or small the document appears on the screen in %Microsoft Word.
/// 
/// @sa Aspose::Words::Settings::ViewOptions
/// @sa Aspose::Words::Settings::ViewOptions::get_ZoomType
enum class ASPOSE_WORDS_SHARED_CLASS ZoomType
{
    /// Zoom percentage is set explicitly. It is not recalculated automatically when control size changes.
    Custom = 0,
    /// Indicates to use the explicit zoom percentage. Same as <see cref="Aspose::Words::Settings::ZoomType::Custom">Custom</see>.
    None = static_cast<int32_t>(Custom),
    /// Zoom percentage is automatically recalculated to fit one full page.
    FullPage = 1,
    /// Zoom percentage is automatically recalculated to fit page width.
    PageWidth = 2,
    /// Zoom percentage is automatically recalculated to fit text.
    TextFit = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::ZoomType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::ZoomType, const char_t*>, 5>& values();
};
