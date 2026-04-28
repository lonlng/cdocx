//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Lists/ListTrailingCharacter.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Lists {

/// Specifies the character that separates the list label from the text of the paragraph.
/// 
/// Used as a value for the <see cref="Aspose::Words::Lists::ListLevel::get_TrailingCharacter">TrailingCharacter</see> property.
enum class ASPOSE_WORDS_SHARED_CLASS ListTrailingCharacter
{
    /// A tab character is placed between the list label and text of the paragraph.
    Tab = 0,
    /// A space character is placed between the list label and text of the paragraph.
    Space = 1,
    /// There is no separator character between the list label and text of the paragraph.
    Nothing = 2
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Lists::ListTrailingCharacter>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Lists::ListTrailingCharacter, const char_t*>, 3>& values();
};
