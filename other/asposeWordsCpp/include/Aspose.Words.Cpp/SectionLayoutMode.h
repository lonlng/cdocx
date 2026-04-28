//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SectionLayoutMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the layout mode for a section allowing to define the document grid behavior.
enum class ASPOSE_WORDS_SHARED_CLASS SectionLayoutMode
{
    /// Specifies that no document grid shall be applied to the contents of the corresponding section in the document.
    Default = 0,
    /// Specifies that the corresponding section shall have both the additional line pitch and character pitch
    /// added to each line and character within it in order to maintain a specific number
    /// of lines per page and characters per line.
    /// Characters will not be automatically aligned with gridlines on typing.
    Grid = 1,
    /// Specifies that the corresponding section shall have additional line pitch added to each line within it
    /// in order to maintain the specified number of lines per page.
    LineGrid = 2,
    /// Specifies that the corresponding section shall have both the additional line pitch and character pitch
    /// added to each line and character within it in order to maintain a specific number
    /// of lines per page and characters per line.
    /// Characters will be automatically aligned with gridlines on typing.
    SnapToChars = 3
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::SectionLayoutMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::SectionLayoutMode, const char_t*>, 4>& values();
};
