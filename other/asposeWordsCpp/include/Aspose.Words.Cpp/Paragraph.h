//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Paragraph.h
#pragma once

#include <Aspose.Words.Cpp/Revisions/ITrackableNode.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/IRunAttrSource.h>
#include <Aspose.Words.Cpp/IParaAttrSource.h>
#include <Aspose.Words.Cpp/Fields/FieldType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CompositeNode;

class DocumentBase;

class DocumentVisitor;

namespace Fields
{

class Field;

}
class Font;

class FrameFormat;

class INodeCloningListener;

namespace Lists
{

class ListFormat;
class ListLabel;

}

class Node;

class NodeUtil;

class ParagraphFormat;

namespace Revisions
{
class EditRevision;
class MoveRevision;

}
enum class RevisionsView;

class RunCollection;

class Section;
class Story;

class TabStop;

}
}
namespace System
{
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

/// Represents a paragraph of text.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-paragraphs/">Working with Paragraphs</a> documentation article.
/// 
/// <see cref="Aspose::Words::Paragraph">Paragraph</see> is a block-level node and can be a child of classes derived from
/// <see cref="Aspose::Words::Story">Story</see> or <see cref="Aspose::Words::InlineStory">InlineStory</see>.
/// 
/// <see cref="Aspose::Words::Paragraph">Paragraph</see> can contain any number of inline-level nodes and bookmarks.
/// 
/// The complete list of child nodes that can occur inside a paragraph consists of
/// <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see>, <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see>,
/// <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see>, <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see>,
/// <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see>, <see cref="Aspose::Words::Fields::FormField">FormField</see>,
/// <see cref="Aspose::Words::Comment">Comment</see>, <see cref="Aspose::Words::Notes::Footnote">Footnote</see>,
/// <see cref="Aspose::Words::Run">Run</see>, <see cref="Aspose::Words::SpecialChar">SpecialChar</see>,
/// <see cref="Aspose::Words::Drawing::Shape">Shape</see>, <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see>,
/// <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see>.
/// 
/// A valid paragraph in %Microsoft Word always ends with a paragraph break character and
/// a minimal valid paragraph consists just of a paragraph break. The <see cref="Aspose::Words::Paragraph">Paragraph</see>
/// class automatically appends the appropriate paragraph break character at the end
/// and this character is not part of the child nodes of the <see cref="Aspose::Words::Paragraph">Paragraph</see>, therefore
/// a <see cref="Aspose::Words::Paragraph">Paragraph</see> can be empty.
/// 
/// Do not include the end of paragraph <see cref="Aspose::Words::ControlChar::ParagraphBreak">ParagraphBreak</see>
/// or end of cell <see cref="Aspose::Words::ControlChar::Cell">Cell</see> characters inside the text of
/// the paragraph as it might make the paragraph invalid when the document is opened in %Microsoft Word.
class ASPOSE_WORDS_SHARED_CLASS Paragraph : public Aspose::Words::CompositeNode, public Aspose::Words::IParaAttrSource, public Aspose::Words::IRunAttrSource, public Aspose::Words::Revisions::ITrackableNode
{
    typedef Paragraph ThisType;
    typedef Aspose::Words::CompositeNode BaseType;
    typedef Aspose::Words::IParaAttrSource BaseType1;
    typedef Aspose::Words::IRunAttrSource BaseType2;
    typedef Aspose::Words::Revisions::ITrackableNode BaseType3;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2, BaseType3> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::Paragraph">Paragraph</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Retrieves the parent section-level story that can be <see cref="Aspose::Words::Body">Body</see> or <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Story> get_ParentStory();
    /// Retrieves the parent <see cref="Aspose::Words::Section">Section</see> of the paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_ParentSection();
    /// True if this paragraph is an immediate child of <see cref="Aspose::Words::Tables::Cell">Cell</see>; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsInCell();
    /// True if this paragraph is the last paragraph in a <see cref="Aspose::Words::Tables::Cell">Cell</see>; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsEndOfCell();
    /// True if this paragraph break is a Style Separator. A style separator allows one
    /// paragraph to consist of parts that have different paragraph styles.
    ASPOSE_WORDS_SHARED_API bool get_BreakIsStyleSeparator();
    /// True if this paragraph is the last paragraph in the <see cref="Aspose::Words::Body">Body</see> (main text story) of a <see cref="Aspose::Words::Section">Section</see>; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsEndOfSection();
    /// True if this paragraph is the last paragraph in the <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> (main text story) of a <see cref="Aspose::Words::Section">Section</see>; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsEndOfHeaderFooter();
    /// True if this paragraph is the last paragraph in the last section of the document.
    ASPOSE_WORDS_SHARED_API bool get_IsEndOfDocument();
    /// Provides access to the paragraph formatting properties.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ParagraphFormat> get_ParagraphFormat();
    /// Provides access to the list formatting properties of the paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::ListFormat> get_ListFormat();
    /// Provides access to the frame formatting properties.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::FrameFormat> get_FrameFormat();
    /// Gets a <see cref="Aspose::Words::Paragraph::get_ListLabel">ListLabel</see> object that provides access to list numbering value and formatting
    /// for this paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::ListLabel> get_ListLabel();
    /// Provides access to the typed collection of pieces of text inside the paragraph.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::RunCollection> get_Runs();
    /// Provides access to the font formatting of the paragraph break character.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_ParagraphBreakFont();
    /// Returns true if this object was inserted in %Microsoft Word while change tracking was enabled.
    ASPOSE_WORDS_SHARED_API bool get_IsInsertRevision();
    /// Returns true if this object was deleted in %Microsoft Word while change tracking was enabled.
    ASPOSE_WORDS_SHARED_API bool get_IsDeleteRevision();
    /// Returns <c>%true</c> if this object was moved (deleted) in %Microsoft Word while change tracking was enabled.
    ASPOSE_WORDS_SHARED_API bool get_IsMoveFromRevision();
    /// Returns <c>%true</c> if this object was moved (inserted) in %Microsoft Word while change tracking was enabled.
    ASPOSE_WORDS_SHARED_API bool get_IsMoveToRevision();
    /// Returns true if formatting of the object was changed in %Microsoft Word while change tracking was enabled.
    ASPOSE_WORDS_SHARED_API bool get_IsFormatRevision();
    /// True when the paragraph is an item in a bulleted or numbered list in original revision.
    ASPOSE_WORDS_SHARED_API bool get_IsListItem();

    /// Initializes a new instance of the <see cref="Aspose::Words::Paragraph">Paragraph</see> class.
    /// 
    /// When <see cref="Aspose::Words::Paragraph">Paragraph</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Paragraph">Paragraph</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the story where you want the paragraph inserted.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Paragraph(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

    /// Accepts a visitor.
    /// 
    /// Enumerates over this node and all of its children. Each node calls a corresponding method on <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the nodes.
    /// 
    /// @return True if all nodes were visited; false if <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> stopped the operation before visiting all nodes.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the start of the document's paragraph.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the document's paragraph.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Gets the text of this paragraph including the end of paragraph character.
    /// 
    /// The text of all child nodes is concatenated and the end of paragraph character is appended as follows:
    /// 
    /// - If the paragraph is the last paragraph of <see cref="Aspose::Words::Body">Body</see>, then
    ///   <see cref="Aspose::Words::ControlChar::SectionBreak">SectionBreak</see> (\\x000c) is appended.
    /// - If the paragraph is the last paragraph of <see cref="Aspose::Words::Tables::Cell">Cell</see>, then
    ///   <see cref="Aspose::Words::ControlChar::Cell">Cell</see> (\\x0007) is appended.
    /// - For all other paragraphs
    ///   <see cref="Aspose::Words::ControlChar::ParagraphBreak">ParagraphBreak</see> (\\r) is appended.
    /// 
    /// The returned string includes all control and special characters as described in <see cref="Aspose::Words::ControlChar">ControlChar</see>.
    ASPOSE_WORDS_SHARED_API System::String GetText() override;
    /// Returns array of all tab stops applied to this paragraph, including applied indirectly by styles or lists.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::SharedPtr<Aspose::Words::TabStop>> GetEffectiveTabStops();
    /// Joins runs with the same formatting in the paragraph.
    /// 
    /// @return Number of joins performed. When <b>%N</b> adjacent runs are being joined they count as <b>%N - 1</b> joins.
    ASPOSE_WORDS_SHARED_API int32_t JoinRunsWithSameFormatting();
    /// Appends a field to this paragraph.
    /// 
    /// @param fieldType The type of the field to append.
    /// @param updateField Specifies whether to update the field immediately.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the appended field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> AppendField(Aspose::Words::Fields::FieldType fieldType, bool updateField);
    /// Appends a field to this paragraph.
    /// 
    /// @param fieldCode The field code to append (without curly braces).
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the appended field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> AppendField(const System::String& fieldCode);
    /// Appends a field to this paragraph.
    /// 
    /// @param fieldCode The field code to append (without curly braces).
    /// @param fieldValue The field value to append. Pass <c>%null</c> for fields that do not have a value.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the appended field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> AppendField(const System::String& fieldCode, const System::String& fieldValue);
    /// Inserts a field into this paragraph.
    /// 
    /// @param fieldType The type of the field to insert.
    /// @param updateField Specifies whether to update the field immediately.
    /// @param refNode Reference node inside this paragraph (if @a refNode is <c>%null</c>, then appends to the end of the paragraph).
    /// @param isAfter Whether to insert the field after or before reference node.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the inserted field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> InsertField(Aspose::Words::Fields::FieldType fieldType, bool updateField, const System::SharedPtr<Aspose::Words::Node>& refNode, bool isAfter);
    /// Inserts a field into this paragraph.
    /// 
    /// @param fieldCode The field code to insert (without curly braces).
    /// @param refNode Reference node inside this paragraph (if @a refNode is <c>%null</c>, then appends to the end of the paragraph).
    /// @param isAfter Whether to insert the field after or before reference node.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the inserted field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> InsertField(const System::String& fieldCode, const System::SharedPtr<Aspose::Words::Node>& refNode, bool isAfter);
    /// Inserts a field into this paragraph.
    /// 
    /// @param fieldCode The field code to insert (without curly braces).
    /// @param fieldValue The field value to insert. Pass <c>%null</c> for fields that do not have a value.
    /// @param refNode Reference node inside this paragraph (if @a refNode is <c>%null</c>, then appends to the end of the paragraph).
    /// @param isAfter Whether to insert the field after or before reference node.
    /// 
    /// @return A <see cref="Aspose::Words::Fields::Field">Field</see> object that represents the inserted field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::Field> InsertField(const System::String& fieldCode, const System::String& fieldValue, const System::SharedPtr<Aspose::Words::Node>& refNode, bool isAfter);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    ASPOSE_WORDS_SHARED_API System::String GetEndText() override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Paragraph();

private:

    System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_InsertRevision() override;
    void set_InsertRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_DeleteRevision() override;
    void set_DeleteRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveFromRevision() override;
    void set_MoveFromRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveToRevision() override;
    void set_MoveToRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;

    System::SharedPtr<System::Object> GetDirectParaAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectParaAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedParaAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchParaAttr(int32_t ) override;
    void SetParaAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveParaAttr(int32_t ) override;
    void ClearParaAttrs() override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t ) override;
    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveRunAttr(int32_t ) override;
    void ClearRunAttrs() override;
    void RemoveMoveRevisions() override;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
