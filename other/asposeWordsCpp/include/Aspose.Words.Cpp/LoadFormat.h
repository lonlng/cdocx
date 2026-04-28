//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LoadFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Indicates the format of the document that is to be loaded.
enum class ASPOSE_WORDS_SHARED_CLASS LoadFormat
{
    /// Instructs %Aspose.Words to recognize the format automatically.
    Auto = 0,
    /// %Microsoft Works 8 Document.
    MsWorks = 8,
    /// %Microsoft Word 95 or Word 97 - 2003 Document.
    Doc = 10,
    /// %Microsoft Word 95 or Word 97 - 2003 Template.
    Dot = 11,
    /// The document is in pre-Word 95 format.
    /// %Aspose.Words does not currently support loading such documents.
    DocPreWord60 = 12,
    /// Office Open XML WordprocessingML Document (macro-free).
    Docx = 20,
    /// Office Open XML WordprocessingML Macro-Enabled Document.
    Docm = 21,
    /// Office Open XML WordprocessingML Template (macro-free).
    Dotx = 22,
    /// Office Open XML WordprocessingML Macro-Enabled Template.
    Dotm = 23,
    /// Office Open XML WordprocessingML stored in a flat XML file instead of a ZIP package.
    FlatOpc = 24,
    /// Office Open XML WordprocessingML Macro-Enabled Document stored in a flat XML file instead of a ZIP package.
    FlatOpcMacroEnabled = 25,
    /// Office Open XML WordprocessingML Template (macro-free) stored in a flat XML file instead of a ZIP package.
    FlatOpcTemplate = 26,
    /// Office Open XML WordprocessingML Macro-Enabled Template stored in a flat XML file instead of a ZIP package.
    FlatOpcTemplateMacroEnabled = 27,
    /// RTF format.
    Rtf = 30,
    /// %Microsoft Word 2003 WordprocessingML format.
    WordML = 31,
    /// HTML format.
    Html = 50,
    /// MHTML (Web archive) format.
    Mhtml = 51,
    /// MOBI format. Used by MobiPocket reader and Amazon Kindle readers.
    Mobi = 52,
    /// CHM (Compiled HTML Help) format.
    Chm = 53,
    /// AZW3 format. Used by Amazon Kindle readers.
    Azw3 = 54,
    /// EPUB format.
    Epub = 55,
    /// ODF Text Document.
    Odt = 60,
    /// ODF Text Document Template.
    Ott = 61,
    /// Plain Text.
    Text = 62,
    /// Markdown text document.
    Markdown = 63,
    /// XML document.
    Xml = 65,
    /// Unrecognized format, cannot be loaded by Aspose.Words.
    Unknown = 255
};

DECLARE_ENUM_OPERATORS(Aspose::Words::LoadFormat);
DECLARE_USING_GLOBAL_OPERATORS

/// LoadFormatTest enumeration.
enum class LoadFormatTest
{
    TestDocxDml = 254
};

DECLARE_ENUM_OPERATORS(Aspose::Words::LoadFormatTest);
DECLARE_USING_GLOBAL_OPERATORS

}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words);
template<>
struct EnumMetaInfo<Aspose::Words::LoadFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LoadFormat, const char_t*>, 28>& values();
};
template<>
struct EnumMetaInfo<Aspose::Words::LoadFormatTest>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::LoadFormatTest, const char_t*>, 1>& values();
};
