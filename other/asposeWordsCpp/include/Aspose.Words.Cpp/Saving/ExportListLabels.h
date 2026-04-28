//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ExportListLabels.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how list labels are exported to HTML, MHTML and EPUB.
/// 
/// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ExportListLabels
enum class ASPOSE_WORDS_SHARED_CLASS ExportListLabels
{
    /// Outputs list labels in auto mode. Uses HTML native elements when possible.
    Auto = 0,
    /// Outputs all list labels as inline text.
    AsInlineText = 1,
    /// Outputs all list labels as HTML native elements.
    ByHtmlTags = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ExportListLabels>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ExportListLabels, const char_t*>, 3>& values();
};
