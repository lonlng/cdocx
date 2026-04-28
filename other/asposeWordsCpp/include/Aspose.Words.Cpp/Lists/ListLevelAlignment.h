//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListLevelAlignment.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Lists {

/// Specifies alignment for the list number or bullet.
/// 
/// Used as a value for the <see cref="Aspose::Words::Lists::ListLevel::get_Alignment">Alignment</see> property.
enum class ASPOSE_WORDS_SHARED_CLASS ListLevelAlignment
{
    /// The list label is aligned to the left of the number position.
    Left = 0,
    /// The list label is centered at the number position.
    Center = 1,
    /// This list label is aligned to the right of the number position.
    Right = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Lists::ListLevelAlignment>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Lists::ListLevelAlignment, const char_t*>, 3>& values();
};
