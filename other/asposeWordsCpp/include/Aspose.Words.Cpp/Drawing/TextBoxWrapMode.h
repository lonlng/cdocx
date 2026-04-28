//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/TextBoxWrapMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies how text wraps inside a shape.
enum class ASPOSE_WORDS_SHARED_CLASS TextBoxWrapMode
{
    /// Text wraps inside a shape.
    Square = 0,
    /// Text does not wrap inside a shape.
    None = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::TextBoxWrapMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::TextBoxWrapMode, const char_t*>, 2>& values();
};
