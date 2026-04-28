//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WarningSource.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the module that produces a warning during document loading or saving.
enum class ASPOSE_WORDS_SHARED_CLASS WarningSource
{
    /// The warning source is not specified.
    Unknown = 0,
    /// Module that builds a document layout.
    Layout = 1,
    /// Module that renders DrawingML shapes.
    DrawingML = 2,
    /// Module that renders OfficeMath.
    OfficeMath = 3,
    /// Module that renders ordinary shapes.
    Shapes = 4,
    /// Module that renders metafiles.
    Metafile = 5,
    /// Module that renders XPS.
    Xps = 6,
    /// Module that renders PDF.
    Pdf = 7,
    /// Module that renders images.
    Image = 8,
    /// Module that reads/writes DOCX files.
    Docx = 9,
    /// Module that reads/writes binary DOC files.
    Doc = 10,
    /// Module that reads/writes plaintext files.
    Text = 11,
    /// Module that reads/writes RTF files.
    Rtf = 12,
    /// Module that reads/writes WML files.
    WordML = 13,
    /// Common modules that are shared between DOCX/WML reader/writer modules.
    Nrx = 14,
    /// Module that reads/writes ODT files.
    Odt = 15,
    /// Module that reads/writes HTML/MHTML files.
    Html = 16,
    /// Module that verifies model consistency and validity.
    Validator = 17,
    /// Module that reads/writes Xaml files.
    Xaml = 18,
    /// Module that reads Svm files.
    Svm = 19,
    /// Module that reads W3C MathML files.
    MathML = 20,
    /// Module that reads font files.
    Font = 21,
    /// Module that reads SVG files.
    Svg = 22,
    /// Module that reads/writes Markdown files.
    Markdown = 23,
    /// Module that reads CHM files.
    Chm = 24,
    /// Module that reads/writes EPUB files.
    Epub = 25,
    /// Module that reads XML files.
    Xml = 26,
    /// Module that writes XLSX files.
    Xlsx = 27,
    /// Module that writes Docling JSON files.
    Docling = 28
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::WarningSource>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WarningSource, const char_t*>, 29>& values();
};
