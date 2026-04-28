//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BuildingBlocks/BuildingBlock.h
#pragma once

#include <system/string.h>
#include <system/guid.h>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/BuildingBlocks/BuildingBlockType.h>
#include <Aspose.Words.Cpp/BuildingBlocks/BuildingBlockGallery.h>
#include <Aspose.Words.Cpp/BuildingBlocks/BuildingBlockBehavior.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace BuildingBlocks
{
class GlossaryDocument;
}
class CompositeNode;
class DocumentVisitor;
class INodeCloningListener;
class Node;

class Section;
class SectionCollection;
}
}

namespace Aspose {

namespace Words {

namespace BuildingBlocks {

/// Represents a glossary document entry such as a Building Block, AutoText or an AutoCorrect entry.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> can contain only <see cref="Aspose::Words::Section">Section</see> nodes.
/// 
/// <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> can only be a child of <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see>.
/// 
/// You can create new building blocks and insert them into a glossary document.
/// You can modify or delete existing building blocks. You can copy or move building blocks
/// between documents. You can insert content of a building block into a document.
/// 
/// Corresponds to the <b>%docPart</b>, <b>%docPartPr</b> and <b>%docPartBody</b> elements in OOXML.
/// 
/// @sa Aspose::Words::BuildingBlocks::GlossaryDocument
class ASPOSE_WORDS_SHARED_CLASS BuildingBlock : public Aspose::Words::CompositeNode
{
    typedef BuildingBlock ThisType;
    typedef Aspose::Words::CompositeNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Returns the <see cref="Aspose::Words::NodeType::BuildingBlock">BuildingBlock</see> value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns a collection that represents all sections in the building block.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::SectionCollection> get_Sections();
    /// Gets the first section in the building block.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_FirstSection();
    /// Gets the last section in the building block.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Section> get_LastSection();
    /// Gets or sets the name of this building block.
    /// 
    /// The name may contain any string content, usually a friendly identifier.
    /// Multiple building blocks can have the same name.
    /// 
    /// Cannot be <c>%null</c> and cannot be an empty string.
    /// 
    /// Corresponds to the <b>%docPartPr.name</b> element in OOXML.
    /// 
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Category
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Name
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Gets or sets an identifier (a 128-bit GUID) that uniquely identifies this building block.
    /// 
    /// Can be used by an application to uniquely reference a building block regardless of
    /// different naming due to localization.
    /// 
    /// Corresponds to the <b>%docPartPr.guid</b> element in OOXML.
    ASPOSE_WORDS_SHARED_API System::Guid get_Guid() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Guid
    ASPOSE_WORDS_SHARED_API void set_Guid(System::Guid value);
    /// Gets or sets the description associated with this building block.
    /// 
    /// The description may contain any string content, usually additional information.
    /// 
    /// Cannot be <c>%null</c>, but can be an empty string.
    /// 
    /// Corresponds to the <b>%docPartPr.description</b> element in OOXML.
    ASPOSE_WORDS_SHARED_API System::String get_Description() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Description
    ASPOSE_WORDS_SHARED_API void set_Description(const System::String& value);
    /// Specifies the first-level categorization for the building block for the purposes of
    /// classification or user interface sorting.
    /// 
    /// Building blocks in %Microsoft Word user interface are arranged
    /// into Galleries. Each <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery">Gallery</see> can have multiple Categories. Each block within
    /// a <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Category">Category</see> has a <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see>.
    /// 
    /// Corresponds to the <b>%docPartPr.category.gallery</b> element in OOXML.
    /// 
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Category
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Name
    ASPOSE_WORDS_SHARED_API Aspose::Words::BuildingBlocks::BuildingBlockGallery get_Gallery() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery
    ASPOSE_WORDS_SHARED_API void set_Gallery(Aspose::Words::BuildingBlocks::BuildingBlockGallery value);
    /// Specifies the second-level categorization for the building block.
    /// 
    /// Building blocks in %Microsoft Word user interface are arranged
    /// into Galleries. Each <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery">Gallery</see> can have multiple Categories. Each block within
    /// a <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Category">Category</see> has a <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see>.
    /// 
    /// Cannot be <c>%null</c> and cannot be an empty string.
    /// 
    /// Corresponds to the <b>%docPartPr.category.name</b> element in OOXML.
    /// 
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Gallery
    /// @sa Aspose::Words::BuildingBlocks::BuildingBlock::get_Name
    ASPOSE_WORDS_SHARED_API System::String get_Category() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Category
    ASPOSE_WORDS_SHARED_API void set_Category(const System::String& value);
    /// Specifies the behavior that shall be applied when the contents of the building block
    /// is inserted into the main document.
    ASPOSE_WORDS_SHARED_API Aspose::Words::BuildingBlocks::BuildingBlockBehavior get_Behavior() const;
    /// Specifies the behavior that shall be applied when the contents of the building block
    /// is inserted into the main document.
    ASPOSE_WORDS_SHARED_API void set_Behavior(Aspose::Words::BuildingBlocks::BuildingBlockBehavior value);
    /// Specifies the building block type.
    /// 
    /// The building block type can influence the visibility and behavior of the
    /// building block in %Microsoft Word.
    /// 
    /// Corresponds to the <b>%docPartPr.types</b> element in OOXML.
    ASPOSE_WORDS_SHARED_API Aspose::Words::BuildingBlocks::BuildingBlockType get_Type() const;
    /// Setter for Aspose::Words::BuildingBlocks::BuildingBlock::get_Type
    ASPOSE_WORDS_SHARED_API void set_Type(Aspose::Words::BuildingBlocks::BuildingBlockType value);

    /// Initializes a new instance of this class.
    /// 
    /// When <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> is created, it belongs to the specified glossary document,
    /// but is not yet part of the glossary document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> to a <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> use
    /// <see cref="Aspose::Words::CompositeNode::AppendChild``1(System::SharedPtr<``0>)">AppendChild``1()</see>.
    /// 
    /// @param glossaryDoc The owner document.
    ASPOSE_WORDS_SHARED_API BuildingBlock(const System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument>& glossaryDoc);

    /// Accepts a visitor.
    /// 
    /// Enumerates over this node and all of its children. Each node calls a corresponding method on <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitBuildingBlockStart(System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock>)">VisitBuildingBlockStart()</see>, then calls
    /// <see cref="Aspose::Words::Node::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see> for all child nodes of this building block, then calls
    /// <see cref="Aspose::Words::DocumentVisitor::VisitBuildingBlockEnd(System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock>)">VisitBuildingBlockEnd()</see>.
    /// 
    /// Note: A building block node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// building block, you need to execute the visitor over <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> or
    /// call <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param visitor The visitor that will visit the nodes.
    /// 
    /// @return True if all nodes were visited; false if <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> stopped the operation before visiting all nodes.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the start of the BuildingBlock.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the BuildingBlock.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~BuildingBlock();

private:

    System::String mField0;
    __TypeStub<1,1,1,1>::type mField1;
    System::Guid mField2;
    System::String mField3;
    __TypeStub<4,4,4,4>::type mField4;
    System::String mField5;
    __TypeStub<4,4,4,4>::type mField6;
    System::String mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::SharedPtr<System::Object> mField9;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
