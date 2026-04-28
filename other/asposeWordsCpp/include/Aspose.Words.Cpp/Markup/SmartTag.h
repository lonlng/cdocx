//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SmartTag.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/Markup/IMarkupNode.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class CompositeNode;
class DocumentBase;
class DocumentVisitor;
class INodeCloningListener;
namespace Markup
{
class CustomXmlPropertyCollection;
enum class MarkupLevel;
}
class Node;

}
}

namespace Aspose {

namespace Words {

namespace Markup {

/// This element specifies the presence of a smart tag around one or more inline structures
/// (runs, images, fields,etc.) within a paragraph.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
/// 
/// Smart tags is a kind of custom XML markup. Smart tags provide a facility for embedding
/// customer-defined semantics into the document via the ability to provide a basic namespace/name
/// for a run or set of runs within a document.
/// 
/// <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see> can be a child of a <see cref="Aspose::Words::Paragraph">Paragraph</see> or
/// another <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see> node.
/// 
/// The complete list of child nodes that can occur inside a smart tag consists of
/// <see cref="Aspose::Words::BookmarkStart">BookmarkStart</see>, <see cref="Aspose::Words::BookmarkEnd">BookmarkEnd</see>,
/// <see cref="Aspose::Words::Fields::FieldStart">FieldStart</see>, <see cref="Aspose::Words::Fields::FieldSeparator">FieldSeparator</see>, <see cref="Aspose::Words::Fields::FieldEnd">FieldEnd</see>, <see cref="Aspose::Words::Fields::FormField">FormField</see>,
/// <see cref="Aspose::Words::Comment">Comment</see>, <see cref="Aspose::Words::Notes::Footnote">Footnote</see>,
/// <see cref="Aspose::Words::Run">Run</see>, <see cref="Aspose::Words::SpecialChar">SpecialChar</see>,
/// <see cref="Aspose::Words::Drawing::Shape">Shape</see>, <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see>,
/// <see cref="Aspose::Words::CommentRangeStart">CommentRangeStart</see>,
/// <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see>,
/// <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see>.
class ASPOSE_WORDS_SHARED_CLASS SmartTag : public Aspose::Words::CompositeNode, public Aspose::Words::Markup::IMarkupNode
{
    typedef SmartTag ThisType;
    typedef Aspose::Words::CompositeNode BaseType;
    typedef Aspose::Words::Markup::IMarkupNode BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::SmartTag">SmartTag</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Specifies the name of the smart tag within the document.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Element() const;
    /// Setter for Aspose::Words::Markup::SmartTag::get_Element
    ASPOSE_WORDS_SHARED_API void set_Element(const System::String& value);
    /// Specifies the namespace URI of the smart tag.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Uri() const;
    /// Setter for Aspose::Words::Markup::SmartTag::get_Uri
    ASPOSE_WORDS_SHARED_API void set_Uri(const System::String& value);
    /// A collection of the smart tag properties.
    /// 
    /// Cannot be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::CustomXmlPropertyCollection> get_Properties() const;

    /// Initializes a new instance of the <see cref="Aspose::Words::Markup::SmartTag">SmartTag</see> class.
    /// 
    /// When you create a new node, you need to specify a document to which the node belongs.
    /// A node cannot exist without a document because it depends on the document-wide structures
    /// such as lists and styles. Although a node always belongs to a document, a node might or might
    /// not be a part of the document tree.
    /// 
    /// When a node is created, it belongs to a document, but is not yet part of the document tree
    /// and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is null. To insert a node into the document, use the
    /// <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// methods on the parent node.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API SmartTag(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

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
    /// Accepts a visitor for visiting the start of the SmartTag.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the SmartTag.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~SmartTag();

private:

    Aspose::Words::Markup::MarkupLevel get_Level_IMarkupNode() override;

    System::String mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
