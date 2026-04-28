//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/VerticalAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies vertical alignment of a floating shape, text frame or a floating table.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_VerticalAlignment
enum class ASPOSE_WORDS_SHARED_CLASS VerticalAlignment
{
    /// The object is explicitly positioned, usually using its <b>%Top</b> property.
    None = 0,
    /// Specifies that the object shall be at the top of the vertical alignment base.
    Top = 1,
    /// Specifies that the object shall be centered with respect to the vertical alignment base.
    Center = 2,
    /// Specifies that the object shall be at the bottom of the vertical alignment base.
    Bottom = 3,
    /// Specifies that the object shall be inside of the horizontal alignment base.
    Inside = 4,
    /// Specifies that the object shall be outside of the vertical alignment base.
    Outside = 5,
    /// Not documented. Seems to be a possible value for floating paragraphs and tables.
    Inline = -1,
    /// Same as <see cref="Aspose::Words::Drawing::VerticalAlignment::None">None</see>.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::VerticalAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::VerticalAlignment, const char_t*>, 8>& values();
};
