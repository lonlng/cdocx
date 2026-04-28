//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/TableAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Tables {

/// Specifies alignment for an inline table.
enum class ASPOSE_WORDS_SHARED_CLASS TableAlignment
{
    /// The table is aligned to the left.
    Left = 0,
    /// The table is centered.
    Center = 1,
    /// The table is aligned to the right.
    Right = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Tables::TableAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Tables::TableAlignment, const char_t*>, 3>& values();
};
