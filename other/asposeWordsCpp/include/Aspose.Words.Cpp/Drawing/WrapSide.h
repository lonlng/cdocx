//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/WrapSide.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies what side(s) of the shape or picture the text wraps around.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_WrapSide
enum class ASPOSE_WORDS_SHARED_CLASS WrapSide
{
    /// The document text wraps on both sides of the shape.
    Both = 0,
    /// The document text wraps on the left side of the shape only. There is a text free area on the right of the shape.
    Left = 1,
    /// The document text wraps on the right side of the shape only. There is a text free area on the left side of the shape.
    Right = 2,
    /// The document text wraps on the side of the shape that is farthest from the page margin, leaving text free area on the other side of the shape.
    Largest = 3,
    /// Default value is <see cref="Aspose::Words::Drawing::WrapSide::Both">Both</see>.
    Default = static_cast<int32_t>(Both)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::WrapSide>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::WrapSide, const char_t*>, 5>& values();
};
