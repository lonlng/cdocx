//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/CompressionLevel.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Compression level for OOXML files.
/// (DOCX and DOTX files are internally a ZIP-archive, this property controls the compression level of the archive.
/// Note, that FlatOpc file is not a ZIP-archive, therefore, this property does not affect the FlatOpc files.)
enum class ASPOSE_WORDS_SHARED_CLASS CompressionLevel
{
    /// Normal compression level. Default compression level used by Aspose.Words.
    Normal = 0,
    /// Maximum compression level.
    Maximum = 1,
    /// Fast compression level.
    Fast = 2,
    /// Super Fast compression level. %Microsoft Word uses this compression level.
    SuperFast = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::CompressionLevel>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::CompressionLevel, const char_t*>, 4>& values();
};
