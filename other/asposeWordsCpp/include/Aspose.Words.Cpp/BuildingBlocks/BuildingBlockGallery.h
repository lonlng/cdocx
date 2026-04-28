//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BuildingBlocks/BuildingBlockGallery.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace BuildingBlocks {

/// Specifies the predefined gallery into which a building block is classified.
/// 
/// Corresponds to the <b>%ST_DocPartGallery</b> type in OOXML.
/// 
/// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery
enum class ASPOSE_WORDS_SHARED_CLASS BuildingBlockGallery
{
    /// Specifies that this glossary document entry shall be associated with all possible gallery classification values.
    All,
    AutoText,
    Bibliography,
    CoverPage,
    CustomAutoText,
    CustomBibliography,
    CustomCoverPage,
    CustomEquations,
    CustomFooters,
    CustomHeaders,
    Custom1,
    Custom2,
    Custom3,
    Custom4,
    Custom5,
    CustomPageNumber,
    CustomPageNumberAtBottom,
    CustomPageNumberAtMargin,
    CustomPageNumberAtTop,
    CustomQuickParts,
    CustomTableOfContents,
    CustomTables,
    CustomTextBox,
    CustomWatermarks,
    NoGallery,
    QuickParts,
    Equations,
    Footers,
    Headers,
    PageNumber,
    PageNumberAtBottom,
    PageNumberAtMargin,
    PageNumberAtTop,
    StructuredDocumentTagPlaceholderText,
    TableOfContents,
    Tables,
    TextBox,
    Watermarks,
    /// Same as <see cref="Aspose::Words::BuildingBlocks::BuildingBlockGallery::All">All</see>.
    Default = static_cast<int32_t>(All)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::BuildingBlocks::BuildingBlockGallery>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::BuildingBlocks::BuildingBlockGallery, const char_t*>, 39>& values();
};
