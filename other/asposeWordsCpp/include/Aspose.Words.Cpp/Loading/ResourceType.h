//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/ResourceType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Type of loaded resource.
enum class ASPOSE_WORDS_SHARED_CLASS ResourceType
{
    /// Image.
    Image,
    /// Font.
    Font,
    /// CSS style sheet.
    CssStyleSheet,
    /// Document.
    Document
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::ResourceType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::ResourceType, const char_t*>, 4>& values();
};
