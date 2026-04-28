//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ExportFontFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Indicates the format that is used to export fonts while rendering to HTML fixed format.
/// 
/// @sa Aspose::Words::Saving::HtmlFixedSaveOptions::get_FontFormat
enum class ASPOSE_WORDS_SHARED_CLASS ExportFontFormat
{
    /// WOFF (Web Open Font Format).
    Woff = 0,
    /// TTF (TrueType Font format).
    Ttf = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::ExportFontFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::ExportFontFormat, const char_t*>, 2>& values();
};
