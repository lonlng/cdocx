//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/WrapType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies how text is wrapped around a shape or picture.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_WrapType
enum class ASPOSE_WORDS_SHARED_CLASS WrapType
{
    /// No text wrapping around the shape. The shape is placed behind or in front of text.
    None = 3,
    /// The shape remains on the same layer as text and treated as a character.
    Inline = 0,
    /// The text stops at the top of the shape and restarts on the line below the shape.
    TopBottom = 1,
    /// Wraps text around all sides of the square bounding box of the shape.
    Square = 2,
    /// Wraps tightly around the edges of the shape, instead of wrapping around the bounding box.
    Tight = 4,
    /// Same as Tight, but wraps inside any parts of the shape that are open.
    Through = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::WrapType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::WrapType, const char_t*>, 6>& values();
};
