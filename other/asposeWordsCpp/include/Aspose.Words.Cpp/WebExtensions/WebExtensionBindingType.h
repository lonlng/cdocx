//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/WebExtensionBindingType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Enumerates available types of binding between a web extension and the data in the document.
enum class ASPOSE_WORDS_SHARED_CLASS WebExtensionBindingType
{
    /// Tabular data without a header row.
    Matrix,
    /// Tabular data with a header row.
    Table,
    /// Plain text.
    Text,
    /// Matrix used by default.
    Default = static_cast<int32_t>(Matrix)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::WebExtensions::WebExtensionBindingType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WebExtensions::WebExtensionBindingType, const char_t*>, 4>& values();
};
