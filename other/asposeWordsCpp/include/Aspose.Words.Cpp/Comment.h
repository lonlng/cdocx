//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Comment.h
#pragma once

#include <system/string.h>
#include <system/date_time.h>

#include <Aspose.Words.Cpp/Model/Text/INodeWithCommentId.h>
#include <Aspose.Words.Cpp/InlineStory.h>
#include <Aspose.Words.Cpp/StoryType.h>
#include <Aspose.Words.Cpp/Revisions/IMoveTrackableNode.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CommentCollection;

class DocumentBase;
class DocumentVisitor;

namespace Revisions
{
class MoveRevision;
}
class RunPr;

}
}

namespace Aspose {

namespace Words {

/// Represents a container for text of a comment.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-comments/">Working with Comments</a> documentation article.
/// 
/// A comment is an annotation which is anchored to a region of text or to a position in text.
/// A comment can contain an arbitrary amount of block-level content.
/// 
/// If a <see cref="Aspose::Words::Comment">Comment</see> object occurs on its own, the comment is anchored to
/// the position of the <see cref="Aspose::Words::Comment">Comment</see> object.
/// 
/// To anchor a comment to a region of text three objects are required: <see cref="Aspose::Words::Comment">Comment</see>,
/// <see cref="Aspose::Words::CommentRangeStart">CommentRangeStart</see> and <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see>. All three objects need to share the same
/// <see cref="Aspose::Words::Comment::get_Id">Id</see> value.
/// 
/// <see cref="Aspose::Words::Comment">Comment</see> is an inline-level node and can only be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
/// 
/// <see cref="Aspose::Words::Comment">Comment</see> can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and <see cref="Aspose::Words::Tables::Table">Table</see> child nodes.
/// 
/// @sa Aspose::Words::CommentRangeStart
/// @sa Aspose::Words::CommentRangeEnd
class ASPOSE_WORDS_SHARED_CLASS Comment final : public Aspose::Words::InlineStory, public Aspose::Words::INodeWithAnnotationId, public Aspose::Words::Revisions::IMoveTrackableNode
{
    typedef Comment ThisType;
    typedef Aspose::Words::InlineStory BaseType;
    typedef Aspose::Words::INodeWithAnnotationId BaseType1;
    typedef Aspose::Words::Revisions::IMoveTrackableNode BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::Comment">Comment</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns <see cref="Aspose::Words::StoryType::Comments">Comments</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StoryType get_StoryType() override;
    /// Gets or sets the comment identifier.
    /// 
    /// The comment identifier allows to anchor a comment to a region of text in the document.
    /// The region must be demarcated using the <see cref="Aspose::Words::CommentRangeStart">CommentRangeStart</see> and <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see>
    /// object sharing the same identifier value as the <see cref="Aspose::Words::Comment">Comment</see> object.
    /// 
    /// You would use this value when looking for the <see cref="Aspose::Words::CommentRangeStart">CommentRangeStart</see> and
    /// <see cref="Aspose::Words::CommentRangeEnd">CommentRangeEnd</see> nodes that are linked to this comment.
    /// 
    /// Comment identifiers are supposed to be unique across a document and %Aspose.Words automatically
    /// maintains comment identifiers when loading, saving and combining documents.
    ASPOSE_WORDS_SHARED_API int32_t get_Id() const;
    /// Setter for Aspose::Words::Comment::get_Id
    ASPOSE_WORDS_SHARED_API void set_Id(int32_t value);
    /// Returns or sets the initials of the user associated with a specific comment.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Initial() const;
    /// Setter for Aspose::Words::Comment::get_Initial
    ASPOSE_WORDS_SHARED_API void set_Initial(const System::String& value);
    /// Gets the date and time that the comment was made.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTime() const;
    /// Gets the date and time that the comment was made.
    ASPOSE_WORDS_SHARED_API void set_DateTime(System::DateTime value);
    /// Gets the UTC date and time that the comment was made.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTimeUtc();
    /// Returns or sets the author name for a comment.
    /// 
    /// Cannot be <c>%null</c>.
    /// 
    /// Default is empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Author() const;
    /// Setter for Aspose::Words::Comment::get_Author
    ASPOSE_WORDS_SHARED_API void set_Author(const System::String& value);
    /// Returns the parent <see cref="Aspose::Words::Comment">Comment</see> object. Returns <c>%null</c> for top-level comments.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Comment> get_Ancestor();
    /// Returns a collection of <see cref="Aspose::Words::Comment">Comment</see> objects that are immediate children of the specified comment.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::CommentCollection> get_Replies();
    /// Gets flag indicating that the comment has been marked done.
    ASPOSE_WORDS_SHARED_API bool get_Done() const;
    /// Sets flag indicating that the comment has been marked done.
    ASPOSE_WORDS_SHARED_API void set_Done(bool value);
    /// Gets the parent comment ID. A value of <c>%-1</c> means the comment has no parent.
    ASPOSE_WORDS_SHARED_API int32_t get_ParentId() const;
    /// Sets the parent comment ID. A value of <c>%-1</c> means the comment has no parent.
    ASPOSE_WORDS_SHARED_API void set_ParentId(int32_t value);

    /// Initializes a new instance of the <see cref="Aspose::Words::Comment">Comment</see> class.
    /// 
    /// When <see cref="Aspose::Words::Comment">Comment</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Comment">Comment</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the paragraph where you want the comment inserted.
    /// 
    /// After creating a comment, don't forget to set its <see cref="Aspose::Words::Comment::get_Author">Author</see>,
    /// <see cref="Aspose::Words::Comment::get_Initial">Initial</see> and <see cref="Aspose::Words::Comment::get_DateTime">DateTime</see> properties.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Comment(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);
    /// Initializes a new instance of the <see cref="Aspose::Words::Comment">Comment</see> class.
    /// 
    /// @param doc The owner document.
    /// @param author The author name for the comment. Cannot be <c>%null</c>.
    /// @param initial The author initials for the comment. Cannot be <c>%null</c>.
    /// @param dateTime The date and time for the comment.
    ASPOSE_WORDS_SHARED_API Comment(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, const System::String& author, const System::String& initial, System::DateTime dateTime);

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
    /// Adds a reply to this comment.
    /// 
    /// Due to the existing MS Office limitations only 1 level of replies is allowed in the document.
    /// 
    /// @param author The author name for the reply.
    /// @param initial The author initials for the reply.
    /// @param dateTime The date and time for the reply.
    /// @param text The reply text.
    /// 
    /// @return The created <see cref="Aspose::Words::Comment">Comment</see> node for the reply.
    /// 
    /// @exception System::InvalidOperationException Throws if this method is called on the existing Reply comment.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Comment> AddReply(const System::String& author, const System::String& initial, System::DateTime dateTime, const System::String& text);
    /// Removes the specified reply to this comment.
    /// 
    /// @param reply The comment node of the deleting reply.
    ASPOSE_WORDS_SHARED_API void RemoveReply(const System::SharedPtr<Aspose::Words::Comment>& reply);
    /// Removes all replies to this comment.
    ASPOSE_WORDS_SHARED_API void RemoveAllReplies();
    /// Accepts a visitor for visiting the start of the comment.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the comment.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// This is a convenience method that allows to easily set text of the comment.
    /// 
    /// This method allows to quickly set text of a comment from a string. The string can contain
    /// paragraph breaks, this will create paragraphs of text in the comment accordingly.
    /// If you want to insert more complex elements into the comment, for example bookmarks
    /// or tables or apply rich formatting, then you need to use the appropriate node classes to
    /// build up the comment text.
    /// 
    /// @param text The new text of the comment.
    ASPOSE_WORDS_SHARED_API void SetText(const System::String& text);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~Comment();

private:

    int32_t get_IdInternal() override;
    void set_IdInternal(int32_t ) override;
    int32_t get_ParentIdInternal() override;
    void set_ParentIdInternal(int32_t ) override;

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveFromRevision() override;
    void set_MoveFromRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveToRevision() override;
    void set_MoveToRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;

    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::String mField6;
    System::String mField7;
    System::DateTime mField8;
    System::DateTime mField9;
    System::SharedPtr<System::Object> mField10;

    void RemoveMoveRevisions() override;
    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

protected:

};

}
}
