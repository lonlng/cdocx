//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TxtExportHeadersFootersMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies the way headers and footers are exported to plain text format.
enum class ASPOSE_WORDS_SHARED_CLASS TxtExportHeadersFootersMode
{
    /// No headers and footers are exported.
    None = 0,
    /// Only primary headers and footers are exported at the beginning and end of each section.
    /// 
    /// It is hard to meaningfully output headers and footers to plain text because it is not paginated.
    /// 
    /// When this mode is used, only primary headers and footers are exported at the beginning and end of each section.
    PrimaryOnly = 1,
    /// All headers and footers are placed after all section bodies at the very end of a document.
    AllAtEnd = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::TxtExportHeadersFootersMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::TxtExportHeadersFootersMode, const char_t*>, 3>& values();
};
