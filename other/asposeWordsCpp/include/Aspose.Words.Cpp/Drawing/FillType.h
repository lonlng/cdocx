//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/FillType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies fill type for a fillable object.
enum class ASPOSE_WORDS_SHARED_CLASS FillType
{
    /// Solid fill.
    Solid = 1,
    /// Patterned fill.
    Patterned = 2,
    /// Gradient fill.
    Gradient = 3,
    /// Textured fill.
    Textured = 4,
    /// Fill is the same as the background.
    Background = 5,
    /// Picture fill.
    Picture = 6
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::FillType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::FillType, const char_t*>, 6>& values();
};
