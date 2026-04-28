//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontSourceType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies the type of font source.
enum class ASPOSE_WORDS_SHARED_CLASS FontSourceType
{
    /// A <see cref="Aspose::Words::Fonts::FileFontSource">FileFontSource</see> object that represents single font file.
    FontFile = 0,
    /// A <see cref="Aspose::Words::Fonts::FolderFontSource">FolderFontSource</see> object that represents folder with font files.
    FontsFolder = 1,
    /// A <see cref="Aspose::Words::Fonts::MemoryFontSource">MemoryFontSource</see> object that represents single font in memory.
    MemoryFont = 2,
    /// A <see cref="Aspose::Words::Fonts::SystemFontSource">SystemFontSource</see> object that represents all fonts installed to the system.
    SystemFonts = 3,
    /// A <see cref="Aspose::Words::Fonts::StreamFontSource">StreamFontSource</see> object that represents a stream with font data.
    FontStream = 4
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fonts::FontSourceType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::FontSourceType, const char_t*>, 5>& values();
};
