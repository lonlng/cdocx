//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TxtOfficeMathExportMode.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how %Aspose.Words exports OfficeMath to <see cref="Aspose::Words::SaveFormat::Text">Text</see>.
enum class ASPOSE_WORDS_SHARED_CLASS TxtOfficeMathExportMode
{
    /// Export OfficeMath as plain text.
    Text = 0,
    /// Export OfficeMath as LaTeX.
    Latex = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::TxtOfficeMathExportMode>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::TxtOfficeMathExportMode, const char_t*>, 2>& values();
};
