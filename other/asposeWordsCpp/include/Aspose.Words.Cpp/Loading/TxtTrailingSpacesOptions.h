//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/TxtTrailingSpacesOptions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Specifies available options for trailing spaces handling during import from <see cref="Aspose::Words::LoadFormat::Text">Text</see> file.
enum class ASPOSE_WORDS_SHARED_CLASS TxtTrailingSpacesOptions
{
    /// Trailing spaces are trimmed.
    Trim = 0,
    /// Trailing spaces are preserved.
    Preserve = 1
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::TxtTrailingSpacesOptions>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::TxtTrailingSpacesOptions, const char_t*>, 2>& values();
};
