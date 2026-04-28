//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/HtmlControlType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Type of document nodes that represent \<input\> and \<select\> elements imported from HTML.
enum class ASPOSE_WORDS_SHARED_CLASS HtmlControlType
{
    /// A form field.
    FormField = 0,
    /// A structured document tag
    StructuredDocumentTag = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::HtmlControlType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::HtmlControlType, const char_t*>, 2>& values();
};
