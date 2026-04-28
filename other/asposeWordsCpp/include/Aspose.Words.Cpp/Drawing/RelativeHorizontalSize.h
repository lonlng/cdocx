//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/RelativeHorizontalSize.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies relatively to what the width of a shape or a text frame is calculated horizontally.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_RelativeHorizontalSize
enum class ASPOSE_WORDS_SHARED_CLASS RelativeHorizontalSize
{
    /// Specifies that the width is calculated relatively to the space between the left and the right margins.
    Margin = 0,
    /// Specifies that the width is calculated relatively to the page width.
    Page = 1,
    /// Specifies that the width is calculated relatively to the left margin area size.
    LeftMargin = 2,
    /// Specifies that the width is calculated relatively to the right margin area size.
    RightMargin = 3,
    /// Specifies that the width is calculated relatively to the inside margin area size,
    /// to the left margin area size for odd pages and to the right margin area size for even pages.
    InnerMargin = 4,
    /// Specifies that the width is calculated relatively to the outside margin area size,
    /// to the right margin area size for odd pages and to the left margin area size for even pages.
    OuterMargin = 5,
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeHorizontalSize::Margin">Margin</see>.
    Default = static_cast<int32_t>(Page)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::RelativeHorizontalSize>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::RelativeHorizontalSize, const char_t*>, 7>& values();
};
