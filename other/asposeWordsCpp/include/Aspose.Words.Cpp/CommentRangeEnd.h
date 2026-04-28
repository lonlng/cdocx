//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CommentRangeEnd.h
#pragma once

#include <Aspose.Words.Cpp/Model/Text/INodeWithCommentId.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/IDisplaceableByCustomXml.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class DocumentBase;
class DocumentVisitor;
class Node;
namespace Revisions
{
enum class DisplacedByType;
}

}
}

namespace Aspose {

namespace Words {

/// Denotes the end of a region of text that has a comment associated with it.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-comments/">Working with Comments</a> documentation article.
/// 
/// To create a comment anchored to a region of text, you need to create a <see cref="Aspose::Words::Comment">Comment</see> and
/// then create <see cref="Aspose::Words::CommentRangeStart">CommentRangeStart</see> and <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see> and set their identifiers
/// to the same <see cref="Aspose::Words::Comment::get_Id">Id</see> value.
/// 
/// <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see> is an inline-level node and can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// @sa Aspose::Words::Comment
/// @sa Aspose::Words::CommentRangeStart
class ASPOSE_WORDS_SHARED_CLASS CommentRangeEnd final : public Aspose::Words::Node, public Aspose::Words::IDisplaceableByCustomXml, public Aspose::Words::INodeWithAnnotationId
{
    typedef CommentRangeEnd ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef Aspose::Words::IDisplaceableByCustomXml BaseType1;
    typedef Aspose::Words::INodeWithAnnotationId BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the identifier of the comment to which this region is linked to.
    ASPOSE_WORDS_SHARED_API int32_t get_Id() const;
    /// Specifies the identifier of the comment to which this region is linked to.
    ASPOSE_WORDS_SHARED_API void set_Id(int32_t value);
    /// Returns <see cref="Aspose::Words::NodeType::CommentRangeEnd">CommentRangeEnd</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Initializes a new instance of this class.
    /// 
    /// When <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append a <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see> to the document use InsertAfter or InsertBefore
    /// on the paragraph where you want the comment inserted.
    /// 
    /// @param doc The owner document.
    /// @param id The comment identifier to which this object is linked.
    ASPOSE_WORDS_SHARED_API CommentRangeEnd(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, int32_t id);

    /// Accepts a visitor.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitCommentRangeEnd(System::SharedPtr<Aspose::Words::CommentRangeEnd>)">VisitCommentRangeEnd()</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// @param visitor The visitor that will visit the node.
    /// 
    /// @return <c>%false</c> if the visitor requested the enumeration to stop.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~CommentRangeEnd();

private:

    Aspose::Words::Revisions::DisplacedByType get_DisplacedByCustomXml() override;
    void set_DisplacedByCustomXml(Aspose::Words::Revisions::DisplacedByType ) override;
    int32_t get_IdInternal() override;
    void set_IdInternal(int32_t ) override;
    int32_t get_ParentIdInternal() override;
    void set_ParentIdInternal(int32_t ) override;

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
