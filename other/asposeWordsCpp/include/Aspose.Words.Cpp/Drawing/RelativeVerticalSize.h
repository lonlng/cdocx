//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/RelativeVerticalSize.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies relatively to what the height of a shape or a text frame is calculated vertically.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_RelativeVerticalSize
enum class ASPOSE_WORDS_SHARED_CLASS RelativeVerticalSize
{
    /// Specifies that the height is calculated relatively to the space between the top and the bottom margins.
    Margin = 0,
    /// Specifies that the height is calculated relatively to the page height.
    Page = 1,
    /// Specifies that the height is calculated relatively to the top margin area size.
    TopMargin = 2,
    /// Specifies that the height is calculated relatively to the bottom margin area size.
    BottomMargin = 3,
    /// Specifies that the height is calculated relatively to the inside margin area size,
    /// to the top margin area size for odd pages and to the bottom margin area size for even pages.
    InnerMargin = 4,
    /// Specifies that the height is calculated relatively to the outside margin area size,
    /// to the bottom margin area size for odd pages and to the top margin area size for even pages.
    OuterMargin = 5,
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeVerticalSize::Margin">Margin</see>.
    Default = static_cast<int32_t>(Page)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::RelativeVerticalSize>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::RelativeVerticalSize, const char_t*>, 7>& values();
};
