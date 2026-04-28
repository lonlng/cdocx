//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/HorizontalAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies horizontal alignment of a floating shape, text frame or floating table.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_HorizontalAlignment
enum class ASPOSE_WORDS_SHARED_CLASS HorizontalAlignment
{
    /// The object is explicitly positioned, usually using its <b>%Left</b> property.
    None = 0,
    /// Same as <see cref="Aspose::Words::Drawing::HorizontalAlignment::None">None</see>.
    Default = static_cast<int32_t>(None),
    /// Specifies that the object shall be left aligned to the horizontal alignment base.
    Left = 1,
    /// Specifies that the object shall be centered with respect to the horizontal alignment base.
    Center = 2,
    /// Specifies that the object shall be right aligned to the horizontal alignment base.
    Right = 3,
    /// Specifies that the object shall be inside of the horizontal alignment base.
    Inside = 4,
    /// Specifies that the object shall be outside of the horizontal alignment base.
    Outside = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::HorizontalAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::HorizontalAlignment, const char_t*>, 7>& values();
};
