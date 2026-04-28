//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BuildingBlocks/BuildingBlockBehavior.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace BuildingBlocks {

/// Specifies the behavior that shall be applied to the contents of the building block
/// when it is inserted into the main document.
/// 
/// Corresponds to the <b>%ST_DocPartBehavior</b> type in OOXML.
/// 
/// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Behavior
enum class ASPOSE_WORDS_SHARED_CLASS BuildingBlockBehavior
{
    /// Specifies that the building block shall be inserted as inline content.
    Content,
    /// Specifies that the building block shall be inserted into its own paragraph.
    Paragraph,
    /// Specifies that the building block shall be added into its own page.
    Page,
    /// Same as <see cref="Aspose::Words::BuildingBlocks::BuildingBlockBehavior::Content">Content</see>.
    Default = static_cast<int32_t>(Content)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::BuildingBlocks::BuildingBlockBehavior>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BuildingBlocks::BuildingBlockBehavior, const char_t*>, 4>& values();
};
