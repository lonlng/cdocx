//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Replacing/ReplacementFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Replacing {

/// Specifies the replacement format.
enum class ASPOSE_WORDS_SHARED_CLASS ReplacementFormat
{
    /// Replacement is treated as simple text.
    Text,
    /// Replacement is interpreted as Markdown text.
    Markdown,
    /// Replacement is interpreted as Html formatted string.
    Html
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Replacing::ReplacementFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Replacing::ReplacementFormat, const char_t*>, 3>& values();
};
