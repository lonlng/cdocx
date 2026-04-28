//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/TxtLeadingSpacesOptions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Specifies available options for leading space handling during import from <see cref="Aspose::Words::LoadFormat::Text">Text</see> file.
enum class ASPOSE_WORDS_SHARED_CLASS TxtLeadingSpacesOptions
{
    /// Leading spaces are removed and converted to left indent.
    ConvertToIndent = 0,
    /// Leading spaces are trimmed
    Trim = 1,
    /// Leading spaces are preserved.
    Preserve = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Loading::TxtLeadingSpacesOptions>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Loading::TxtLeadingSpacesOptions, const char_t*>, 3>& values();
};
