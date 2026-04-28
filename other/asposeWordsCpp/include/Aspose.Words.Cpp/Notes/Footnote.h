//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Notes/Footnote.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/InlineStory.h>
#include <Aspose.Words.Cpp/StoryType.h>
#include <Aspose.Words.Cpp/Revisions/ITrackableNode.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Notes/FootnoteType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;

class DocumentVisitor;

namespace Revisions
{
class EditRevision;
class MoveRevision;
}
class RunPr;

}
}

namespace Aspose {

namespace Words {

namespace Notes {

/// Represents a container for text of a footnote or endnote.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-footnote-and-endnote/">Working with Footnote and Endnote</a> documentation article.
/// 
/// The <see cref="Aspose::Words::Notes::Footnote">Footnote</see> class is used to represent both footnotes and endnotes in a Word document.
/// 
/// <see cref="Aspose::Words::Notes::Footnote">Footnote</see> is an inline-level node and can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// <see cref="Aspose::Words::Notes::Footnote">Footnote</see> can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> child nodes.
/// 
/// @sa Aspose::Words::Notes::Footnote::get_FootnoteType
/// @sa Aspose::Words::DocumentBuilder::InsertFootnote(Aspose::Words::Notes::FootnoteType, System::String)
/// @sa Aspose::Words::Notes::FootnoteOptions
/// @sa Aspose::Words::Notes::EndnoteOptions
class ASPOSE_WORDS_SHARED_CLASS Footnote : public Aspose::Words::InlineStory, public Aspose::Words::Revisions::ITrackableNode
{
    typedef Footnote ThisType;
    typedef Aspose::Words::InlineStory BaseType;
    typedef Aspose::Words::Revisions::ITrackableNode BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::Footnote">Footnote</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns <see cref="Aspose::Words::StoryType::Footnotes">Footnotes</see> or <see cref="Aspose::Words::StoryType::Endnotes">Endnotes</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StoryType get_StoryType() override;
    /// Returns a value that specifies whether this is a footnote or endnote.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Notes::FootnoteType get_FootnoteType() const;
    /// Holds a value that specifies whether this is a auto-numbered footnote or
    /// footnote with user defined custom reference mark.
    ASPOSE_WORDS_SHARED_API bool get_IsAuto() const;
    /// Holds a value that specifies whether this is a auto-numbered footnote or
    /// footnote with user defined custom reference mark.
    ASPOSE_WORDS_SHARED_API void set_IsAuto(bool value);
    /// Gets/sets custom reference mark to be used for this footnote.
    /// Default value is <b>%empty string</b>, meaning auto-numbered footnotes are used.
    /// 
    /// If this property is set to <b>%empty string</b> or <c>%null</c>, then <see cref="Aspose::Words::Notes::Footnote::get_IsAuto">IsAuto</see> property will automatically be set to <c>%true</c>,
    /// if set to anything else then <see cref="Aspose::Words::Notes::Footnote::get_IsAuto">IsAuto</see> will be set to <c>%false</c>.
    /// 
    /// RTF-format can only store 1 symbol as custom reference mark, so upon export only the first symbol will be written others will be discard.
    ASPOSE_WORDS_SHARED_API System::String get_ReferenceMark() const;
    /// Setter for Aspose::Words::Notes::Footnote::get_ReferenceMark
    ASPOSE_WORDS_SHARED_API void set_ReferenceMark(const System::String& value);
    /// Gets the actual text of the reference mark displayed in the document for this footnote.
    ASPOSE_WORDS_SHARED_API System::String get_ActualReferenceMark();

    /// Initializes an instance of the <see cref="Aspose::Words::Notes::Footnote">Footnote</see> class.
    /// 
    /// When <see cref="Aspose::Words::Notes::Footnote">Footnote</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Notes::Footnote">Footnote</see> to the document use<see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the paragraph where you want the footnote inserted.
    /// 
    /// @param doc The owner document.
    /// @param footnoteType A <see cref="Aspose::Words::Notes::Footnote::get_FootnoteType">FootnoteType</see> value
    ///     that specifies whether this is a footnote or endnote.
    ASPOSE_WORDS_SHARED_API Footnote(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, Aspose::Words::Notes::FootnoteType footnoteType);

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
    /// Accepts a visitor for visiting the start of the footnote.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the footnote.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Footnote();

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
    __TypeStub<1,1,1,1>::type mField1;
    System::String mField2;
    __TypeStub<4,4,4,4>::type mField3;

    void RemoveMoveRevisions() override;
    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
