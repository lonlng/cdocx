//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SaveFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Indicates the format in which the document is saved.
/// 
/// @sa Aspose::Words::Document::Save(System::SharedPtr<System::IO::Stream>, Aspose::Words::SaveFormat)
/// @sa Aspose::Words::Saving::SaveOptions
enum class ASPOSE_WORDS_SHARED_CLASS SaveFormat
{
    /// Default, invalid value for file format.
    Unknown = 0,
    /// Saves the document in the %Microsoft Word 97 - 2007 Document format.
    Doc = 10,
    /// Saves the document in the %Microsoft Word 97 - 2007 Template format.
    Dot = 11,
    /// Saves the document as an Office Open XML WordprocessingML Document (macro-free).
    Docx = 20,
    /// Saves the document as an Office Open XML WordprocessingML Macro-Enabled Document.
    Docm = 21,
    /// Saves the document as an Office Open XML WordprocessingML Template (macro-free).
    Dotx = 22,
    /// Saves the document as an Office Open XML WordprocessingML Macro-Enabled Template.
    Dotm = 23,
    /// Saves the document as an Office Open XML WordprocessingML stored in a flat XML file instead of a ZIP package.
    FlatOpc = 24,
    /// Saves the document as an Office Open XML WordprocessingML Macro-Enabled Document stored in a flat XML file instead of a ZIP package.
    FlatOpcMacroEnabled = 25,
    /// Saves the document as an Office Open XML WordprocessingML Template (macro-free) stored in a flat XML file instead of a ZIP package.
    FlatOpcTemplate = 26,
    /// Saves the document as an Office Open XML WordprocessingML Macro-Enabled Template stored in a flat XML file instead of a ZIP package.
    FlatOpcTemplateMacroEnabled = 27,
    /// Saves the document in the RTF format.
    /// All characters above 7-bits are escaped as hexadecimal or Unicode characters.
    Rtf = 30,
    /// Saves the document in the %Microsoft Word 2003 WordprocessingML format.
    WordML = 31,
    /// Saves the document as PDF (Adobe Portable Document) format.
    Pdf = 40,
    /// Saves the document in the XPS (XML Paper Specification) format.
    Xps = 41,
    /// Saves the document in the Extensible Application Markup Language (XAML) format as a fixed document.
    XamlFixed = 42,
    /// Saves the document in the Svg (Scalable Vector Graphics) format.
    Svg = 44,
    /// Saves the document in the HTML format using absolutely positioned elements
    HtmlFixed = 45,
    /// Saves the document in the OpenXPS (Ecma-388) format.
    OpenXps = 46,
    /// Saves the document in the PS (PostScript) format.
    Ps = 47,
    /// Saves the document in the PCL (Printer Control Language) format.
    Pcl = 48,
    /// Saves the document in the HTML format.
    Html = 50,
    /// Saves the document in the MHTML (Web archive) format.
    Mhtml = 51,
    /// Saves the document in the EPUB format.
    Epub = 52,
    /// Saves the document in the AZW3 format.
    Azw3 = 53,
    /// Saves the document in the MOBI format.
    Mobi = 54,
    /// Saves the document as an ODF Text Document.
    Odt = 60,
    /// Saves the document as an ODF Text Document Template.
    Ott = 61,
    /// Saves the document in the plain text format.
    Text = 70,
    /// <b>%Beta.</b> Saves the document in the Extensible Application Markup Language (XAML) format as a flow document.
    XamlFlow = 71,
    /// <b>%Beta.</b> Saves the document in the Extensible Application Markup Language (XAML) package format as a flow document.
    XamlFlowPack = 72,
    /// Saves the document in the Markdown format.
    Markdown = 73,
    /// Saves the document as an Office Open XML SpreadsheetML Document (macro-free).
    Xlsx = 80,
    /// Saves the document in Docling JSON format.
    Docling = 81,
    /// Renders a page or pages of the document and saves them into a single or multipage TIFF file.
    Tiff = 100,
    /// Renders a page of the document and saves it as a PNG file.
    Png = 101,
    /// Renders a page of the document and saves it as a BMP file.
    Bmp = 102,
    /// Renders a page of the document and saves it as a vector EMF (Enhanced Meta File) file.
    Emf = 103,
    /// Renders a page of the document and saves it as a JPEG file.
    Jpeg = 104,
    /// Renders a page of the document and saves it as a GIF file.
    Gif = 105,
    /// Renders a page of the document and saves it as an EPS file.
    Eps = 106
};

DECLARE_ENUM_OPERATORS(Aspose::Words::SaveFormat);
DECLARE_USING_GLOBAL_OPERATORS

}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words);
template<>
struct EnumMetaInfo<Aspose::Words::SaveFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::SaveFormat, const char_t*>, 41>& values();
};
