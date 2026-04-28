//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/Row.h
#pragma once

#include <Aspose.Words.Cpp/Revisions/ITrackableNode.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/IRowAttrSource.h>
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

class Node;

namespace Revisions
{
class EditRevision;
class MoveRevision;

}

namespace Tables
{
class Cell;
class CellCollection;

class RowFormat;

class Table;

}

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Tables {

/// Represents a table row.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
/// 
/// <see cref="Aspose::Words::Tables::Row">Row</see> can only be a child of a <see cref="Aspose::Words::Tables::Table">Table</see>.
/// 
/// <see cref="Aspose::Words::Tables::Row">Row</see> can contain one or more <see cref="Aspose::Words::Tables::Cell">Cell</see> nodes.
/// 
/// A minimal valid row needs to have at least one <see cref="Aspose::Words::Tables::Cell">Cell</see>.
class ASPOSE_WORDS_SHARED_CLASS Row : public Aspose::Words::CompositeNode, public Aspose::Words::IRowAttrSource, public Aspose::Words::Revisions::ITrackableNode
{
    typedef Row ThisType;
    typedef Aspose::Words::CompositeNode BaseType;
    typedef Aspose::Words::IRowAttrSource BaseType1;
    typedef Aspose::Words::Revisions::ITrackableNode BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::Row">Row</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns the immediate parent table of the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Table> get_ParentTable();
    /// True if this is the first row in a table; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsFirstRow();
    /// True if this is the last row in a table; false otherwise.
    ASPOSE_WORDS_SHARED_API bool get_IsLastRow();
    /// Gets the next <see cref="Aspose::Words::Tables::Row">Row</see> node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Row> get_NextRow();
    /// Gets the previous <see cref="Aspose::Words::Tables::Row">Row</see> node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Row> get_PreviousRow();
    /// Returns the first <see cref="Aspose::Words::Tables::Cell">Cell</see> in the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Cell> get_FirstCell();
    /// Returns the last <see cref="Aspose::Words::Tables::Cell">Cell</see> in the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Cell> get_LastCell();
    /// Provides typed access to the <see cref="Aspose::Words::Tables::Cell">Cell</see> child nodes of the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::CellCollection> get_Cells();
    /// Provides access to the formatting properties of the row.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::RowFormat> get_RowFormat();
    /// Gets a flag indicating whether this row is hidden or not.
    ASPOSE_WORDS_SHARED_API bool get_Hidden();
    /// Sets a flag indicating whether this row is hidden or not.
    ASPOSE_WORDS_SHARED_API void set_Hidden(bool value);

    /// Initializes a new instance of the <see cref="Aspose::Words::Tables::Row">Row</see> class.
    /// 
    /// When <see cref="Aspose::Words::Tables::Row">Row</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Tables::Row">Row</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the table where you want the row inserted.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Row(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

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
    /// Accepts a visitor for visiting the start of the row.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the row.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Gets the text of all cells in this row including the end of row character.
    /// 
    /// Returns concatenated text of all child nodes with the end of row character
    /// <see cref="Aspose::Words::ControlChar::Cell">Cell</see> appended at the end.
    /// 
    /// The returned string includes all control and special characters as described in <see cref="Aspose::Words::ControlChar">ControlChar</see>.
    ASPOSE_WORDS_SHARED_API System::String GetText() override;
    /// If the <see cref="Aspose::Words::Tables::Row">Row</see> has no cells, creates and appends one <see cref="Aspose::Words::Tables::Cell">Cell</see>.
    ASPOSE_WORDS_SHARED_API void EnsureMinimum();

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    ASPOSE_WORDS_SHARED_API System::String GetEndText() override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Row();

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

    System::SharedPtr<System::Object> GetDirectRowAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchRowAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedRowAttr(int32_t ) override;
    void SetRowAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void ClearRowAttrs() override;
    void ResetToDefaultAttrs() override;
    void RemoveMoveRevisions() override;
    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
