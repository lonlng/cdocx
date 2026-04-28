//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/EmbeddedFontFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies format of particular embedded font inside <see cref="Aspose::Words::Fonts::FontInfo">FontInfo</see> object.
/// When saving a document to a file, only embedded fonts of corresponding format are written down.
enum class ASPOSE_WORDS_SHARED_CLASS EmbeddedFontFormat
{
    /// Specifies Embedded OpenType (EOT) File Format.
    /// This format of embedded fonts used in DOC files.
    /// 
    /// See http://www.w3.org/Submission/EOT for description of the format.
    EmbeddedOpenType,
    /// Specifies font, embedded as plain copy of OpenType (TrueType) font file.
    /// This format of embedded fonts used in Open Office XML format, including DOCX files.
    OpenType
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fonts::EmbeddedFontFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::EmbeddedFontFormat, const char_t*>, 2>& values();
};
