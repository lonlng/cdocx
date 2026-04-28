//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Inline.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/IInline.h>
#include <Aspose.Words.Cpp/Revisions/ITrackableNode.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;

class DocumentVisitor;

class Font;

class INodeCloningListener;

class Node;

class Paragraph;

namespace Revisions
{
class EditRevision;
class MoveRevision;

}
enum class RevisionsView;

class RunPr;
enum class RunPrExpandFlags;

}
}

namespace Aspose {

namespace Words {

/// Base class for inline-level nodes that can have character formatting associated with them, but cannot have child nodes of their own.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/logical-levels-of-nodes-in-a-document/">Logical Levels of Nodes in a Document</a> documentation article.
/// 
/// A class derived from <see cref="Aspose::Words::Inline">Inline</see> can be a child of <see cref="Aspose::Words::Paragraph">Paragraph</see>.
class ASPOSE_WORDS_SHARED_CLASS Inline : public Aspose::Words::Node, public Aspose::Words::IInline, public Aspose::Words::Revisions::ITrackableNode
{
    typedef Inline ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef Aspose::Words::IInline BaseType1;
    typedef Aspose::Words::Revisions::ITrackableNode BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Node::Clone;

public:

    /// Retrieves the parent <see cref="Aspose::Words::Paragraph">Paragraph</see> of this node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> get_ParentParagraph();
    /// Provides access to the font formatting of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
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

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Inline();

private:

    System::SharedPtr<Aspose::Words::RunPr> get_RunPr_IInline() override;
    void set_RunPr_IInline(System::SharedPtr<Aspose::Words::RunPr> ) override;
    System::SharedPtr<Aspose::Words::Paragraph> get_ParentParagraph_IInline() override;
    System::SharedPtr<Aspose::Words::DocumentBase> get_Document_IInline() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_InsertRevision() override;
    void set_InsertRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::EditRevision> get_DeleteRevision() override;
    void set_DeleteRevision(System::SharedPtr<Aspose::Words::Revisions::EditRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveFromRevision() override;
    void set_MoveFromRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;
    System::SharedPtr<Aspose::Words::Revisions::MoveRevision> get_MoveToRevision() override;
    void set_MoveToRevision(System::SharedPtr<Aspose::Words::Revisions::MoveRevision> ) override;

    System::SharedPtr<Aspose::Words::RunPr> GetExpandedRunPr_IInline(Aspose::Words::RunPrExpandFlags ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t ) override;
    System::SharedPtr<System::Object> GetDirectRunAttr(int32_t , Aspose::Words::RevisionsView ) override;
    System::SharedPtr<System::Object> FetchInheritedRunAttr(int32_t ) override;
    void SetRunAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void RemoveRunAttr(int32_t ) override;
    void ClearRunAttrs() override;
    void RemoveMoveRevisions() override;

};

}
}
