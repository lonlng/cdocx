//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ExportHeadersFootersMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how headers and footers are exported to HTML, MHTML or EPUB.
/// 
/// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ExportHeadersFootersMode
enum class ASPOSE_WORDS_SHARED_CLASS ExportHeadersFootersMode
{
    /// Headers and footers are not exported.
    None = 0,
    /// Primary headers and footers are exported at the beginning and the end of each section.
    PerSection = 1,
    /// Primary header of the first section is exported at the beginning of the document and primary footer is at the end.
    FirstSectionHeaderLastSectionFooter = 2,
    /// First page header and footer are exported at the beginning and the end of each section.
    FirstPageHeaderFooterPerSection = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ExportHeadersFootersMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ExportHeadersFootersMode, const char_t*>, 4>& values();
};
