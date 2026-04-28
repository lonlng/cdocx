//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/LayoutFlow.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Determines the flow of the text layout in a textbox.
/// 
/// @sa Aspose::Words::Drawing::TextBox::get_LayoutFlow
enum class ASPOSE_WORDS_SHARED_CLASS LayoutFlow
{
    /// Text is displayed horizontally.
    Horizontal = 0,
    /// Ideographic text is displayed vertically.
    TopToBottomIdeographic = 1,
    /// Text is displayed vertically.
    BottomToTop = 2,
    /// Text is displayed vertically.
    TopToBottom = 3,
    /// Ideographic text is displayed horizontally.
    HorizontalIdeographic = 4,
    /// Text is displayed vertically.
    Vertical = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::LayoutFlow>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::LayoutFlow, const char_t*>, 6>& values();
};
