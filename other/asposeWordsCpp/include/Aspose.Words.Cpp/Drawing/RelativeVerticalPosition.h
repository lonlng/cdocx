//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/RelativeVerticalPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies to what the vertical position of a shape or text frame is relative.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_RelativeVerticalPosition
enum class ASPOSE_WORDS_SHARED_CLASS RelativeVerticalPosition
{
    /// Specifies that the vertical positioning shall be relative to the page margins.
    Margin = 0,
    /// The object is positioned relative to the top edge of the page.
    Page = 1,
    /// The object is positioned relative to the top of the paragraph that contains the anchor.
    Paragraph = 2,
    /// Undocumented.
    Line = 3,
    /// Specifies that the vertical positioning shall be relative to the top margin of the current page.
    TopMargin = 4,
    /// Specifies that the vertical positioning shall be relative to the bottom margin of the current page.
    BottomMargin = 5,
    /// Specifies that the vertical positioning shall be relative to the inside margin of the current page.
    InsideMargin = 6,
    /// Specifies that the vertical positioning shall be relative to the outside margin of the current page.
    OutsideMargin = 7,
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeVerticalPosition::Margin">Margin</see>.
    TableDefault = static_cast<int32_t>(Margin),
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeVerticalPosition::Paragraph">Paragraph</see>.
    TextFrameDefault = static_cast<int32_t>(Paragraph)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::RelativeVerticalPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::RelativeVerticalPosition, const char_t*>, 10>& values();
};
