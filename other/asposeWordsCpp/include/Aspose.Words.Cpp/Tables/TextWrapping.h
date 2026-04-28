//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/TextWrapping.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies how text is wrapped around the table.
enum class ASPOSE_WORDS_SHARED_CLASS TextWrapping
{
    /// Text and table is displayed in the order of their appearance in the document.
    None,
    /// Text is wrapped around the table occupying available side space.
    Around,
    /// Default value.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::TextWrapping>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::TextWrapping, const char_t*>, 3>& values();
};
