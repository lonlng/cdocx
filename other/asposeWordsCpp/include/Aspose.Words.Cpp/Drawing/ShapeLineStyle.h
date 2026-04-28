//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ShapeLineStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies the compound line style of a <see cref="Aspose::Words::Drawing::Shape">Shape</see>.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_LineStyle
enum class ASPOSE_WORDS_SHARED_CLASS ShapeLineStyle
{
    /// Single line.
    Single = 0,
    /// Double lines of equal width.
    Double = 1,
    /// Double lines, one thick, one thin.
    ThickThin = 2,
    /// Double lines, one thin, one thick.
    ThinThick = 3,
    /// Three lines, thin, thick, thin.
    Triple = 4,
    /// Default value is <see cref="Aspose::Words::Drawing::ShapeLineStyle::Single">Single</see>.
    Default = static_cast<int32_t>(Single)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ShapeLineStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ShapeLineStyle, const char_t*>, 6>& values();
};
