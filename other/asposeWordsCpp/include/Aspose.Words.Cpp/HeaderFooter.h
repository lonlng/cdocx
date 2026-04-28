//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/HeaderFooter.h
#pragma once

#include <Aspose.Words.Cpp/Story.h>
#include <Aspose.Words.Cpp/HeaderFooterType.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class DocumentVisitor;
class Section;
}
}

namespace Aspose {

namespace Words {

/// Represents a container for the header or footer text of a section.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-headers-and-footers/">Working with Headers and Footers</a> documentation article.
/// 
/// <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> child nodes.
/// 
/// <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> is a section-level node and can only be a child of <see cref="Aspose::Words::Section">Section</see>.
/// There can only be one <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> of each <see cref="Aspose::Words::HeaderFooter::get_HeaderFooterType">HeaderFooterType</see> in a <see cref="Aspose::Words::Section">Section</see>.
/// 
/// If <see cref="Aspose::Words::Section">Section</see> does not have a <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> of a specific type or
/// the <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> has no child nodes, this header/footer is considered linked to
/// the header/footer of the same type of the previous section in %Microsoft Word.
/// 
/// When <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> contains at least one <see cref="Aspose::Words::Paragraph">Paragraph</see>, it is no longer
/// considered linked to previous in %Microsoft Word.
class ASPOSE_WORDS_SHARED_CLASS HeaderFooter : public Aspose::Words::Story
{
    typedef HeaderFooter ThisType;
    typedef Aspose::Words::Story BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::HeaderFooter">HeaderFooter</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the parent section of this story.
    /// 
    /// <see cref="Aspose::Words::HeaderFooter::get_ParentSection">ParentSection</see> is equivalent to <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> casted to <see cref="Aspose::Words::Section">Section</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_ParentSection();
    /// Gets the type of this header/footer.
    ASPOSE_WORDS_SHARED_API Aspose::Words::HeaderFooterType get_HeaderFooterType();
    /// True if this <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> object is a header.
    ASPOSE_WORDS_SHARED_API bool get_IsHeader();
    /// True if this header or footer is linked to the corresponding header or footer
    /// in the previous section.
    /// 
    /// Default is <c>%true</c>.
    /// 
    /// Note, when your link a header or footer, its contents is cleared.
    ASPOSE_WORDS_SHARED_API bool get_IsLinkedToPrevious();
    /// Setter for Aspose::Words::HeaderFooter::get_IsLinkedToPrevious
    ASPOSE_WORDS_SHARED_API void set_IsLinkedToPrevious(bool value);

    /// Creates a new header or footer of the specified type.
    /// 
    /// When <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see> to a <see cref="Aspose::Words::Section">Section</see> use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see>, <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>,
    /// or <see cref="Aspose::Words::Section::get_HeadersFooters">HeadersFooters</see> property and methods <see cref="Aspose::Words::NodeCollection::Add(System::SharedPtr<Aspose::Words::Node>)">Add()</see>, <see cref="Aspose::Words::NodeCollection::Insert(int32_t, System::SharedPtr<Aspose::Words::Node>)">Insert()</see>.
    /// 
    /// @param doc The owner document.
    /// @param headerFooterType A <see cref="Aspose::Words::HeaderFooter::get_HeaderFooterType">HeaderFooterType</see> value
    ///     that specifies the type of the header or footer.
    ASPOSE_WORDS_SHARED_API HeaderFooter(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, Aspose::Words::HeaderFooterType headerFooterType);

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
    /// Accepts a visitor for visiting the start of the header.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the header.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~HeaderFooter();

private:

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
