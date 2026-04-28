//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/TextPathAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// WordArt alignment.
/// 
/// @sa Aspose::Words::Drawing::TextPath::get_TextPathAlignment
enum class ASPOSE_WORDS_SHARED_CLASS TextPathAlignment
{
    /// Stretch each line of text to fit width.
    Stretch = 0,
    /// Center text on width.
    Center = 1,
    /// Left justify.
    Left = 2,
    /// Right justify.
    Right = 3,
    /// Spread letters out to fit width.
    LetterJustify = 4,
    /// Spread words out to fit width.
    WordJustify = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::TextPathAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::TextPathAlignment, const char_t*>, 6>& values();
};
