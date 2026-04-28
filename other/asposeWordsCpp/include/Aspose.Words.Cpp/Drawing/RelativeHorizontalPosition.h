//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/RelativeHorizontalPosition.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies to what the horizontal position of a shape or text frame is relative.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_RelativeHorizontalPosition
enum class ASPOSE_WORDS_SHARED_CLASS RelativeHorizontalPosition
{
    /// Specifies that the horizontal positioning shall be relative to the page margins.
    Margin = 0,
    /// The object is positioned relative to the left edge of the page.
    Page = 1,
    /// The object is positioned relative to the left side of the column.
    Column = 2,
    /// The object is positioned relative to the left side of the paragraph.
    Character = 3,
    /// Specifies that the horizontal positioning shall be relative to the left margin of the page.
    LeftMargin = 4,
    /// Specifies that the horizontal positioning shall be relative to the right margin of the page.
    RightMargin = 5,
    /// Specifies that the horizontal positioning shall be relative to the inside margin of the
    /// current page (the left margin on odd pages, right on even pages).
    InsideMargin = 6,
    /// Specifies that the horizontal positioning shall be relative to the outside margin of the
    /// current page (the right margin on odd pages, left on even pages).
    OutsideMargin = 7,
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeHorizontalPosition::Column">Column</see>.
    Default = static_cast<int32_t>(Column)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::RelativeHorizontalPosition>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::RelativeHorizontalPosition, const char_t*>, 9>& values();
};
