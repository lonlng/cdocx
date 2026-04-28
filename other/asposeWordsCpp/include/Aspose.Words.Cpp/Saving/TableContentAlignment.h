//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/TableContentAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify the alignment of the content of the table to be used when exporting into Markdown format.
enum class ASPOSE_WORDS_SHARED_CLASS TableContentAlignment
{
    /// The alignment will be taken from the first paragraph in corresponding table column.
    Auto = 0,
    /// The content of tables will be aligned to the Left.
    Left = 1,
    /// The content of tables will be aligned to the Center.
    Center = 2,
    /// The content of tables will be aligned to the Right.
    Right = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Saving::TableContentAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::TableContentAlignment, const char_t*>, 4>& values();
};
