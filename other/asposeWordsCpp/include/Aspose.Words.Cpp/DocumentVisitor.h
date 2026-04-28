//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DocumentVisitor.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class AbsolutePositionTab;
class Body;
class BookmarkEnd;
class BookmarkStart;
namespace BuildingBlocks
{
class BuildingBlock;
class GlossaryDocument;
}
class Comment;
class CommentRangeEnd;
class CommentRangeStart;
class Document;
namespace Drawing
{
class GroupShape;
class Shape;
}
class EditableRangeEnd;
class EditableRangeStart;
namespace Fields
{
class FieldEnd;
class FieldSeparator;
class FieldStart;
class FormField;
}
class HeaderFooter;

namespace Markup
{
class SmartTag;
class StructuredDocumentTag;
class StructuredDocumentTagRangeEnd;
class StructuredDocumentTagRangeStart;
}
namespace Math
{
class OfficeMath;
}

class MoveRangeEnd;
class MoveRangeStart;

namespace Notes
{
class Footnote;
}
class Paragraph;
class Run;

class Section;
class SpecialChar;
class SubDocument;
namespace Tables
{
class Cell;
class Row;
class Table;
}
}
}

namespace Aspose {

namespace Words {

/// Base class for custom document visitors.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// With <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> you can define and execute custom operations
/// that require enumeration over the document tree.
/// 
/// For example, %Aspose.Words uses <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> internally for saving <see cref="Aspose::Words::Document">Document</see>
/// in various formats and for other operations like finding fields or bookmarks over
/// a fragment of a document.
/// 
/// To use <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>:
/// 
/// -# Create a class derived from <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
/// -# Override and provide implementations for some or all of the VisitXXX methods
///    to perform some custom operations.
/// -# Call <see cref="Aspose::Words::Node::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Node.Accept</see> on the <see cref="Aspose::Words::Node">Node</see> that
///    you want to start the enumeration from.
/// 
/// <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> provides default implementations for all of the VisitXXX methods
/// to make it easier to create new document visitors as only the methods required for the particular
/// visitor need to be overridden. It is not necessary to override all of the visitor methods.
/// 
/// For more information see the Visitor design pattern.
class ASPOSE_WORDS_SHARED_CLASS DocumentVisitor : public virtual System::Object
{
    typedef DocumentVisitor ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when enumeration of the document has started.
    /// 
    /// @param doc The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitDocumentStart(System::SharedPtr<Aspose::Words::Document> doc);
    /// Called when enumeration of the document has finished.
    /// 
    /// @param doc The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitDocumentEnd(System::SharedPtr<Aspose::Words::Document> doc);
    /// Called when enumeration of a section has started.
    /// 
    /// @param section The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSectionStart(System::SharedPtr<Aspose::Words::Section> section);
    /// Called when enumeration of a section has ended.
    /// 
    /// @param section The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSectionEnd(System::SharedPtr<Aspose::Words::Section> section);
    /// Called when enumeration of the main text story in a section has started.
    /// 
    /// @param body The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBodyStart(System::SharedPtr<Aspose::Words::Body> body);
    /// Called when enumeration of the main text story in a section has ended.
    /// 
    /// @param body The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBodyEnd(System::SharedPtr<Aspose::Words::Body> body);
    /// Called when enumeration of a header or footer in a section has started.
    /// 
    /// @param headerFooter The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitHeaderFooterStart(System::SharedPtr<Aspose::Words::HeaderFooter> headerFooter);
    /// Called when enumeration of a header or footer in a section has ended.
    /// 
    /// @param headerFooter The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitHeaderFooterEnd(System::SharedPtr<Aspose::Words::HeaderFooter> headerFooter);
    /// Called when enumeration of a paragraph has started.
    /// 
    /// @param paragraph The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitParagraphStart(System::SharedPtr<Aspose::Words::Paragraph> paragraph);
    /// Called when enumeration of a paragraph has ended.
    /// 
    /// @param paragraph The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitParagraphEnd(System::SharedPtr<Aspose::Words::Paragraph> paragraph);
    /// Called when enumeration of a table has started.
    /// 
    /// @param table The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitTableStart(System::SharedPtr<Aspose::Words::Tables::Table> table);
    /// Called when enumeration of a table has ended.
    /// 
    /// @param table The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitTableEnd(System::SharedPtr<Aspose::Words::Tables::Table> table);
    /// Called when enumeration of a table row has started.
    /// 
    /// @param row The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitRowStart(System::SharedPtr<Aspose::Words::Tables::Row> row);
    /// Called when enumeration of a table row has ended.
    /// 
    /// @param row The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitRowEnd(System::SharedPtr<Aspose::Words::Tables::Row> row);
    /// Called when enumeration of a table cell has started.
    /// 
    /// @param cell The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCellStart(System::SharedPtr<Aspose::Words::Tables::Cell> cell);
    /// Called when enumeration of a table cell has ended.
    /// 
    /// @param cell The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCellEnd(System::SharedPtr<Aspose::Words::Tables::Cell> cell);
    /// Called when a run of text in the is encountered.
    /// 
    /// @param run The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitRun(System::SharedPtr<Aspose::Words::Run> run);
    /// Called when a field starts in the document.
    /// 
    /// A field in a Word document consists of a field code and field value.
    /// 
    /// For example, a field that displays a page number can be represented as follows:
    /// 
    /// [FieldStart]PAGE[FieldSeparator]98[FieldEnd]
    /// 
    /// The field separator separates field code from field value in the document. Note that some
    /// fields have only field code and do not have field separator and field value.
    /// 
    /// Fields can be nested.
    /// 
    /// @param fieldStart The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFieldStart(System::SharedPtr<Aspose::Words::Fields::FieldStart> fieldStart);
    /// Called when a field separator is encountered in the document.
    /// 
    /// The field separator separates field code from field value in the document. Note that some
    /// fields have only field code and do not have field separator and field value.
    /// 
    /// For more info see <see cref="Aspose::Words::DocumentVisitor::VisitFieldStart(System::SharedPtr<Aspose::Words::Fields::FieldStart>)">VisitFieldStart()</see>
    /// 
    /// @param fieldSeparator The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFieldSeparator(System::SharedPtr<Aspose::Words::Fields::FieldSeparator> fieldSeparator);
    /// Called when a field ends in the document.
    /// 
    /// For more info see <see cref="Aspose::Words::DocumentVisitor::VisitFieldStart(System::SharedPtr<Aspose::Words::Fields::FieldStart>)">VisitFieldStart()</see>
    /// 
    /// @param fieldEnd The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFieldEnd(System::SharedPtr<Aspose::Words::Fields::FieldEnd> fieldEnd);
    /// Called when a form field is encountered in the document.
    /// 
    /// @param formField The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFormField(System::SharedPtr<Aspose::Words::Fields::FormField> formField);
    /// Called when a start of a bookmark is encountered in the document.
    /// 
    /// @param bookmarkStart The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBookmarkStart(System::SharedPtr<Aspose::Words::BookmarkStart> bookmarkStart);
    /// Called when an end of a bookmark is encountered in the document.
    /// 
    /// @param bookmarkEnd The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBookmarkEnd(System::SharedPtr<Aspose::Words::BookmarkEnd> bookmarkEnd);
    /// Called when enumeration of a footnote or endnote text has started.
    /// 
    /// @param footnote The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFootnoteStart(System::SharedPtr<Aspose::Words::Notes::Footnote> footnote);
    /// Called when enumeration of a footnote or endnote text has ended.
    /// 
    /// @param footnote The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitFootnoteEnd(System::SharedPtr<Aspose::Words::Notes::Footnote> footnote);
    /// Called when enumeration of a comment text has started.
    /// 
    /// @param comment The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCommentStart(System::SharedPtr<Aspose::Words::Comment> comment);
    /// Called when enumeration of a comment text has ended.
    /// 
    /// @param comment The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCommentEnd(System::SharedPtr<Aspose::Words::Comment> comment);
    /// Called when a start of an editable range is encountered in the document.
    /// 
    /// @param editableRangeStart The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitEditableRangeStart(System::SharedPtr<Aspose::Words::EditableRangeStart> editableRangeStart);
    /// Called when an end of an editable range is encountered in the document.
    /// 
    /// @param editableRangeEnd The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitEditableRangeEnd(System::SharedPtr<Aspose::Words::EditableRangeEnd> editableRangeEnd);
    /// Called when enumeration of a shape has started.
    /// 
    /// @param shape The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitShapeStart(System::SharedPtr<Aspose::Words::Drawing::Shape> shape);
    /// Called when enumeration of a shape has ended.
    /// 
    /// @param shape The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitShapeEnd(System::SharedPtr<Aspose::Words::Drawing::Shape> shape);
    /// Called when enumeration of a group shape has started.
    /// 
    /// @param groupShape The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitGroupShapeStart(System::SharedPtr<Aspose::Words::Drawing::GroupShape> groupShape);
    /// Called when enumeration of a group shape has ended.
    /// 
    /// @param groupShape The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitGroupShapeEnd(System::SharedPtr<Aspose::Words::Drawing::GroupShape> groupShape);
    /// Called when enumeration of a Office Math object has started.
    /// 
    /// @param officeMath The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitOfficeMathStart(System::SharedPtr<Aspose::Words::Math::OfficeMath> officeMath);
    /// Called when enumeration of a Office Math object has ended.
    /// 
    /// @param officeMath The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitOfficeMathEnd(System::SharedPtr<Aspose::Words::Math::OfficeMath> officeMath);
    /// Called when a <see cref="Aspose::Words::SpecialChar">SpecialChar</see> node is encountered in the document.
    /// 
    /// @param specialChar The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSpecialChar(System::SharedPtr<Aspose::Words::SpecialChar> specialChar);
    /// Called when a <see cref="Aspose::Words::AbsolutePositionTab">AbsolutePositionTab</see> node is encountered in the document.
    /// 
    /// @param tab The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitAbsolutePositionTab(System::SharedPtr<Aspose::Words::AbsolutePositionTab> tab);
    /// Called when enumeration of a smart tag has started.
    /// 
    /// @param smartTag The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSmartTagStart(System::SharedPtr<Aspose::Words::Markup::SmartTag> smartTag);
    /// Called when enumeration of a smart tag has ended.
    /// 
    /// @param smartTag The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSmartTagEnd(System::SharedPtr<Aspose::Words::Markup::SmartTag> smartTag);
    /// Called when enumeration of a structured document tag has started.
    /// 
    /// @param sdt The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitStructuredDocumentTagStart(System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTag> sdt);
    /// Called when enumeration of a structured document tag has ended.
    /// 
    /// @param sdt The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitStructuredDocumentTagEnd(System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTag> sdt);
    /// Called when enumeration of a glossary document has started.
    /// 
    /// Note: A glossary document node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// glossary document, you need to call <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param glossary The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitGlossaryDocumentStart(System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument> glossary);
    /// Called when enumeration of a glossary document has ended.
    /// 
    /// Note: A glossary document node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// glossary document, you need to call <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param glossary The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitGlossaryDocumentEnd(System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument> glossary);
    /// Called when enumeration of a building block has started.
    /// 
    /// Note: A building block node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// building block, you need to execute the visitor over <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> or
    /// call <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param block The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBuildingBlockStart(System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> block);
    /// Called when enumeration of a building block has ended.
    /// 
    /// Note: A building block node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// building block, you need to execute the visitor over <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> or
    /// call <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param block The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitBuildingBlockEnd(System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> block);
    /// Called when the start of a commented range of text is encountered.
    /// 
    /// @param commentRangeStart The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCommentRangeStart(System::SharedPtr<Aspose::Words::CommentRangeStart> commentRangeStart);
    /// Called when the end of a commented range of text is encountered.
    /// 
    /// @param commentRangeEnd The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitCommentRangeEnd(System::SharedPtr<Aspose::Words::CommentRangeEnd> commentRangeEnd);
    /// Called when a sub-document is encountered.
    /// 
    /// @param subDocument The object that is being visited.
    /// 
    /// @return A <see cref="Aspose::Words::VisitorAction">VisitorAction</see> value that specifies how to continue the enumeration.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitSubDocument(System::SharedPtr<Aspose::Words::SubDocument> subDocument);
    /// Called when a StructuredDocumentTagRangeStart is encountered.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitStructuredDocumentTagRangeStart(System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTagRangeStart> sdtRangeStart);
    /// Called when a StructuredDocumentTagRangeEnd is encountered.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitStructuredDocumentTagRangeEnd(System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTagRangeEnd> sdtRangeEnd);

protected:

    virtual ASPOSE_WORDS_SHARED_API bool get_VisitsDeletedNodes();

    ASPOSE_WORDS_SHARED_API DocumentVisitor();

    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitMoveFromRangeStart(System::SharedPtr<Aspose::Words::MoveRangeStart> );
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitMoveFromRangeEnd(System::SharedPtr<Aspose::Words::MoveRangeEnd> );
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitMoveToRangeStart(System::SharedPtr<Aspose::Words::MoveRangeStart> );
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction VisitMoveToRangeEnd(System::SharedPtr<Aspose::Words::MoveRangeEnd> );

private:

    __TypeStub<4,4,4,4>::type mField0;

};

}
}
