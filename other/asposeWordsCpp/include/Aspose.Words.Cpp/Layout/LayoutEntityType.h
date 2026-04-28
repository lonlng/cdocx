//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Layout/LayoutEntityType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum_helpers.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Layout/Core/PartType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Layout {

/// Types of the layout entities.
enum class ASPOSE_WORDS_SHARED_CLASS LayoutEntityType
{
    /// Default value.
    None = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::None),
    /// Represents page of a document.
    /// Page may have <see cref="Aspose::Words::Layout::LayoutEntityType::Column">Column</see>, <see cref="Aspose::Words::Layout::LayoutEntityType::HeaderFooter">HeaderFooter</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Comment">Comment</see> child entities.
    Page = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Page),
    /// Represents a column of text on a page.
    /// Column may have the same child entities as <see cref="Aspose::Words::Layout::LayoutEntityType::Cell">Cell</see>, plus <see cref="Aspose::Words::Layout::LayoutEntityType::Footnote">Footnote</see>, <see cref="Aspose::Words::Layout::LayoutEntityType::Endnote">Endnote</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::NoteSeparator">NoteSeparator</see> entities.
    Column = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Column),
    /// Represents a table row.
    /// Row may have <see cref="Aspose::Words::Layout::LayoutEntityType::Cell">Cell</see> as child entities.
    Row = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Row),
    /// Represents a table cell.
    /// Cell may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    Cell = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Cell),
    /// Represents line of characters of text and inline objects.
    /// Line may have <see cref="Aspose::Words::Layout::LayoutEntityType::Span">Span</see> child entities.
    Line = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Line),
    /// Represents one or more characters in a line.
    /// This include special characters like field start/end markers, bookmarks and comments.
    /// Span may not have child entities.
    Span = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Span),
    /// Represents placeholder for footnote content.
    /// Footnote may have <see cref="Aspose::Words::Layout::LayoutEntityType::Note">Note</see> child entities.
    Footnote = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Footnote),
    /// Represents placeholder for endnote content.
    /// Endnote may have <see cref="Aspose::Words::Layout::LayoutEntityType::Note">Note</see> child entities.
    Endnote = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Endnote),
    /// Represents placeholder for note content.
    /// Note may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    Note = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Note),
    /// Represents placeholder for header/footer content on a page.
    /// HeaderFooter may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    HeaderFooter = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::HeaderFooter),
    /// Represents text area inside of a shape.
    /// Textbox may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    TextBox = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::TextBox),
    /// Represents placeholder for comment content.
    /// Comment may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    Comment = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::Comment),
    /// Represents footnote/endnote separator.
    /// NoteSeparator may have <see cref="Aspose::Words::Layout::LayoutEntityType::Line">Line</see> and <see cref="Aspose::Words::Layout::LayoutEntityType::Row">Row</see> child entities.
    NoteSeparator = static_cast<int32_t>(Aspose::Words::Layout::Core::PartType::NoteSeparator)
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Layout::LayoutEntityType);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Layout);
template<>
struct EnumMetaInfo<Aspose::Words::Layout::LayoutEntityType>
{
    typedef void Flags;
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Layout::LayoutEntityType, const char_t*>, 14>& values();
};
