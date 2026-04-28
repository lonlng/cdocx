//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DocumentSplitCriteria.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Specifies how the document is split into parts when saving to <see cref="Aspose::Words::SaveFormat::Html">Html</see>,
/// <see cref="Aspose::Words::SaveFormat::Epub">Epub</see> or <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> format.
/// 
/// <see cref="Aspose::Words::Saving::DocumentSplitCriteria">DocumentSplitCriteria</see> is a set of flags which can be combined. For instance you can split the document
/// at page breaks and heading paragraphs in the same export operation.
/// 
/// Different criteria can partially overlap. For instance, <b>%Heading 1</b> style is frequently given
/// <see cref="Aspose::Words::ParagraphFormat::get_PageBreakBefore">PageBreakBefore</see> property so it falls under two criteria: <see cref="Aspose::Words::Saving::DocumentSplitCriteria::PageBreak">PageBreak</see> and
/// <see cref="Aspose::Words::Saving::DocumentSplitCriteria::HeadingParagraph">HeadingParagraph</see>. Some section breaks can cause page breaks and so on.
/// In typical cases specifying only one flag is the most practical option.
/// 
/// @sa Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitCriteria
enum class ASPOSE_WORDS_SHARED_CLASS DocumentSplitCriteria
{
    /// The document is not split.
    None = 0x0000,
    /// The document is split into parts at explicit page breaks.
    /// A page break can be specified by a <see cref="Aspose::Words::ControlChar::PageBreak">PageBreak</see> character,
    /// a section break specifying start of new section on a new page,
    /// or a paragraph that has its <see cref="Aspose::Words::ParagraphFormat::get_PageBreakBefore">PageBreakBefore</see> property set to <c>%true</c>.
    PageBreak = 0x0001,
    /// The document is split into parts at column breaks.
    /// A column break can be specified by a <see cref="Aspose::Words::ControlChar::ColumnBreak">ColumnBreak</see> character or
    /// a section break specifying start of new section in a new column.
    ColumnBreak = 0x0002,
    /// The document is split into parts at a section break of any type.
    SectionBreak = 0x0004,
    /// The document is split into parts at a paragraph formatted using a heading style <b>%Heading 1</b>, <b>%Heading 2</b> etc.
    /// Use together with <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitHeadingLevel">DocumentSplitHeadingLevel</see> to specify the heading levels
    /// (from 1 to the specified level) at which to split.
    HeadingParagraph = 0x0008
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Saving::DocumentSplitCriteria);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Saving);
template<>
struct EnumMetaInfo<Aspose::Words::Saving::DocumentSplitCriteria>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Saving::DocumentSplitCriteria, const char_t*>, 5>& values();
};
