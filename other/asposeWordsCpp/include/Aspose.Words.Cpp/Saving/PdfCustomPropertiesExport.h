//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfCustomPropertiesExport.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the way <see cref="Aspose::Words::Document::get_CustomDocumentProperties">CustomDocumentProperties</see> are exported to PDF file.
enum class ASPOSE_WORDS_SHARED_CLASS PdfCustomPropertiesExport
{
    /// No custom properties are exported.
    None = 0,
    /// Custom properties are exported as entries in /Info dictionary.
    /// Custom properties with the following names are not exported:
    /// "Title", "Author", "Subject", "Keywords", "Creator", "Producer", "CreationDate", "ModDate", "Trapped".
    Standard = 1,
    /// Custom properties are Metadata.
    /// 
    /// The namespace of exported properties in XMP packet is "custprops".
    /// Every property has an associated xml-element "custprops:Property1", "custprops:Property2" and so on.
    /// There is "rdf:Description" element inside property element.
    /// The description element has two elements "custprops:Name", containing custom property's name
    /// as a value of this xml-element, and "custprops:Value", containing custom property's value as value of this xml-element.
    Metadata = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::PdfCustomPropertiesExport>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::PdfCustomPropertiesExport, const char_t*>, 3>& values();
};
