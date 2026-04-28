//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Body.h
#pragma once

#include <Aspose.Words.Cpp/Story.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class DocumentVisitor;
class Node;
class Section;
}
}

namespace Aspose {

namespace Words {

/// Represents a container for the main text of a section.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// <see cref="Aspose::Words::Body">Body</see> can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> child nodes.
/// 
/// <see cref="Aspose::Words::Body">Body</see> is a section-level node and can only be a child of <see cref="Aspose::Words::Section">Section</see>.
/// There can only be one <see cref="Aspose::Words::Body">Body</see> in a <see cref="Aspose::Words::Section">Section</see>.
/// 
/// A minimal valid <see cref="Aspose::Words::Body">Body</see> needs to contain at least one <see cref="Aspose::Words::Paragraph">Paragraph</see>.
class ASPOSE_WORDS_SHARED_CLASS Body : public Aspose::Words::Story
{
    typedef Body ThisType;
    typedef Aspose::Words::Story BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::Body">Body</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the parent section of this story.
    /// 
    /// <see cref="Aspose::Words::Body::get_ParentSection">ParentSection</see> is equivalent to <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> casted to <see cref="Aspose::Words::Section">Section</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_ParentSection();

    /// Initializes a new instance of the <see cref="Aspose::Words::Body">Body</see> class.
    /// 
    /// When <see cref="Aspose::Words::Body">Body</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Body">Body</see> to a <see cref="Aspose::Words::Section">Section</see> use <see cref="Aspose::Words::CompositeNode::AppendChild``1(System::SharedPtr<``0>)">AppendChild</see><see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore</see>
    /// methods.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Body(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

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
    /// Accepts a visitor for visiting the start of the document's body.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the document's body.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// If the last child is not a paragraph, creates and appends one empty paragraph.
    ASPOSE_WORDS_SHARED_API void EnsureMinimum();

protected:

    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Body();

private:

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
