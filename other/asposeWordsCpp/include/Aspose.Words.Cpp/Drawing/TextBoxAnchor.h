//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/TextBoxAnchor.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies values used for shape text vertical alignment.
enum class ASPOSE_WORDS_SHARED_CLASS TextBoxAnchor
{
    /// Text is aligned to the top of the textbox.
    Top = 0,
    /// Text is aligned to the middle of the textbox.
    Middle = 1,
    /// Text is aligned to the bottom of the textbox.
    Bottom = 2,
    /// Text is aligned to the top centered of the textbox.
    TopCentered = 3,
    /// Text is aligned to the middle centered of the textbox.
    MiddleCentered = 4,
    /// Text is aligned to the bottom centered of the textbox.
    BottomCentered = 5,
    /// Text is aligned to the top baseline of the textbox.
    TopBaseline = 6,
    /// Text is aligned to the bottom baseline of the textbox.
    BottomBaseline = 7,
    /// Text is aligned to the top centered baseline of the textbox.
    TopCenteredBaseline = 8,
    /// Text is aligned to the bottom centered baseline of the textbox.
    BottomCenteredBaseline = 9
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::TextBoxAnchor>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::TextBoxAnchor, const char_t*>, 10>& values();
};
