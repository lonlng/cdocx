//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BuildingBlocks/BuildingBlockType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace BuildingBlocks {

/// Specifies a building block type. The type might affect the visibility and behavior of the building block
/// in %Microsoft Word.
/// 
/// Corresponds to the <b>%ST_DocPartType</b> type in OOXML.
/// 
/// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Type
enum class ASPOSE_WORDS_SHARED_CLASS BuildingBlockType
{
    /// No type information is specified for the building block.
    None,
    /// Allows the building block to be automatically inserted into the document whenever
    /// its name is entered into an application.
    AutomaticallyReplaceNameWithContent,
    /// The building block is a structured document tag placeholder text.
    StructuredDocumentTagPlaceholderText,
    /// The building block is a form field help text.
    FormFieldHelpText,
    /// The building block is a normal (i.e. regular) glossary document entry.
    Normal,
    /// The building block is associated with the spelling and grammar tools.
    AutoCorrect,
    /// The building block is an AutoText entry.
    AutoText,
    /// The building block is associated with all types.
    All,
    /// Save as <see cref="Aspose::Words::BuildingBlocks::BuildingBlockType::None">None</see>.
    Default = static_cast<int32_t>(None)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::BuildingBlocks::BuildingBlockType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BuildingBlocks::BuildingBlockType, const char_t*>, 9>& values();
};
