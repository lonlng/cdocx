//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/DashStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Dashed line style.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_DashStyle
enum class ASPOSE_WORDS_SHARED_CLASS DashStyle
{
    /// Solid (continuous) pen.
    Solid = 0,
    /// System dash style.
    ShortDash = 1,
    /// System dash style.
    ShortDot = 2,
    /// System dash style.
    ShortDashDot = 3,
    /// System dash style.
    ShortDashDotDot = 4,
    /// Square dot style.
    Dot = 5,
    /// Dash style.
    Dash = 6,
    /// Long dash style.
    LongDash = 7,
    /// Dash short dash.
    DashDot = 8,
    /// Long dash short dash.
    LongDashDot = 9,
    /// Long dash short dash short dash.
    LongDashDotDot = 10,
    /// Same as <see cref="Aspose::Words::Drawing::DashStyle::Solid">Solid</see>.
    Default = static_cast<int32_t>(Solid)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::DashStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::DashStyle, const char_t*>, 12>& values();
};
