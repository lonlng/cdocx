//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/JoinStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Line join style.
/// 
/// @sa Aspose::Words::Drawing::Stroke::get_JoinStyle
enum class ASPOSE_WORDS_SHARED_CLASS JoinStyle
{
    /// Join edges by a straight line.
    Bevel = 0,
    /// Extend edges until they join.
    Miter = 1,
    /// Draw an arc between the two edges.
    Round = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::JoinStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::JoinStyle, const char_t*>, 3>& values();
};
