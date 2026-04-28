//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NodeType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of a Word document node.
enum class ASPOSE_WORDS_SHARED_CLASS NodeType
{
    /// Indicates all node types. Allows to select all children.
    Any,
    /// A <see cref="Aspose::Words::Document">Document</see> object that, as the root of the document tree,
    /// provides access to the entire Word document.
    /// A <see cref="Aspose::Words::Document">Document</see> node can have <see cref="Aspose::Words::Section">Section</see> nodes.
    Document,
    /// A <see cref="Aspose::Words::Section">Section</see> object that corresponds to one section in a Word document.
    /// A <see cref="Aspose::Words::Section">Section</see> node can have <see cref="Aspose::Words::Body">Body</see> and <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> nodes.
    Section,
    /// A <see cref="Aspose::Words::Body">Body</see> object that contains the main text of a section (main text story).
    /// A <see cref="Aspose::Words::Body">Body</see> node can have <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    Body,
    /// A <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> object that contains text of a particular header or footer inside a section.
    /// A <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> node can have <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    HeaderFooter,
    /// A <see cref="Aspose::Words::Tables::Table">Table</see> object that represents a table in a Word document.
    /// A <see cref="Aspose::Words::Tables::Table">Table</see> node can have <see cref="Aspose::Words::Tables::Row">Row</see> nodes.
    Table,
    /// A row of a table.
    /// A <see cref="Aspose::Words::Tables::Row">Row</see> node can have <see cref="Aspose::Words::Tables::Cell">Cell</see> nodes.
    Row,
    /// A cell of a table row.
    /// A <see cref="Aspose::Words::Tables::Cell">Cell</see> node can have <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    Cell,
    /// A paragraph of text.
    /// A <see cref="Aspose::Words::Paragraph">Paragraph</see> node is a container for inline level elements
    /// <see cref="Aspose::Words::Run">Run</see>,
    /// <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see>,
    /// <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see>,
    /// <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see>,
    /// <see cref="Aspose::Words::Fields::FormField">FormField</see>,
    /// <see cref="Aspose::Words::Drawing::Shape">Shape</see>,
    /// <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see>,
    /// <see cref="Aspose::Words::Notes::Footnote">Footnote</see>,
    /// <see cref="Aspose::Words::Comment">Comment</see>,
    /// <see cref="Aspose::Words::SpecialChar">SpecialChar</see>,
    /// as well as <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see> and <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see>.
    Paragraph,
    /// A beginning of a bookmark marker.
    BookmarkStart,
    /// An end of a bookmark marker.
    BookmarkEnd,
    /// A beginning of an editable range.
    EditableRangeStart,
    /// An end of an editable range.
    EditableRangeEnd,
    /// A beginning of an MoveFrom range.
    MoveFromRangeStart,
    /// An end of an MoveFrom range.
    MoveFromRangeEnd,
    /// A beginning of an MoveTo range.
    MoveToRangeStart,
    /// An end of an MoveTo range.
    MoveToRangeEnd,
    /// A group of shapes, images, OLE objects or other group shapes.
    /// A <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see> node can contain other
    /// <see cref="Aspose::Words::Drawing::Shape">Shape</see> and <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see> nodes.
    GroupShape,
    /// A drawing object, such as an OfficeArt shape, image or an OLE object.
    /// A <see cref="Aspose::Words::Drawing::Shape">Shape</see> node can contain <see cref="Aspose::Words::Paragraph">Paragraph</see>
    /// and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    Shape,
    /// A comment in a Word document.
    /// A <see cref="Aspose::Words::Comment">Comment</see> node can have <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    Comment,
    /// A footnote or endnote in a Word document.
    /// A <see cref="Aspose::Words::Notes::Footnote">Footnote</see> node can have <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> nodes.
    Footnote,
    /// A run of text.
    Run,
    /// A special character that designates the start of a Word field.
    FieldStart,
    /// A special character that separates the field code from the field result.
    FieldSeparator,
    /// A special character that designates the end of a Word field.
    FieldEnd,
    /// A form field.
    FormField,
    /// A special character that is not one of the more specific special character types.
    SpecialChar,
    /// A smart tag around one or more inline structures (runs, images, fields,etc.) within a paragraph
    SmartTag,
    /// Allows to define customer-specific information and its means of presentation.
    StructuredDocumentTag,
    /// A start of <b>%ranged</b> structured document tag which accepts multi-sections content.
    StructuredDocumentTagRangeStart,
    /// A end of <b>%ranged</b> structured document tag which accepts multi-sections content.
    StructuredDocumentTagRangeEnd,
    /// A glossary document within the main document.
    GlossaryDocument,
    /// A building block within a glossary document (e.g. glossary document entry).
    BuildingBlock,
    /// A marker node that represents the start of a commented range.
    CommentRangeStart,
    /// A marker node that represents the end of a commented range.
    CommentRangeEnd,
    /// An Office Math object. Can be equation, function, matrix or one of other mathematical objects.
    /// Can be a collection of mathematical object and also can contain some non-mathematical objects such as runs of text.
    OfficeMath,
    /// A subdocument node which is a link to another document.
    SubDocument,
    /// Reserved for internal use by Aspose.Words.
    System,
    /// Reserved for internal use by Aspose.Words.
    Null
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::NodeType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::NodeType, const char_t*>, 39>& values();
};
