//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/FlipOrientation.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Possible values for the orientation of a shape.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase::get_FlipOrientation
enum class ASPOSE_WORDS_SHARED_CLASS FlipOrientation
{
    /// Coordinates are not flipped.
    None = 0x00,
    /// Flip along the y-axis, reversing the x-coordinates.
    Horizontal = 0x01,
    /// Flip along the x-axis, reversing the y-coordinates.
    Vertical = 0x02,
    /// Flip along both the y- and x-axis.
    Both = 0x03
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Drawing::FlipOrientation);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Drawing);
template<>
struct EnumMetaInfo<Aspose::Words::Drawing::FlipOrientation>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::FlipOrientation, const char_t*>, 4>& values();
};
