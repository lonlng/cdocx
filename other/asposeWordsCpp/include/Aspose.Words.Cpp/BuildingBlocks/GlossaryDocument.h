//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BuildingBlocks/GlossaryDocument.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/DocumentBase.h>
#include <Aspose.Words.Cpp/BuildingBlocks/BuildingBlockGallery.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace BuildingBlocks
{
class BuildingBlock;
class BuildingBlockCollection;
}

class DocumentBase;
class DocumentRenderingContext;
class DocumentVisitor;
namespace Fonts
{
class DocumentFontProvider;
}
class INodeCloningListener;
class Node;

class StyleCollection;
enum class SuspendedRevisionTypes;
namespace Themes
{
class Theme;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace BuildingBlocks {

/// Represents the root element for a glossary document within a Word document.
/// A glossary document is a storage for AutoText, AutoCorrect entries and Building Blocks.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// Some documents, usually templates, can contain AutoText, AutoCorrect entries
/// and/or Building Blocks (also known as <i>%glossary document entries</i>, <i>%document parts</i>
/// or <i>%building blocks</i>).
/// 
/// To access building blocks, you need to load a document into a <see cref="Aspose::Words::Document">Document</see>
/// object. Building blocks will be available via the <see cref="Aspose::Words::Document::get_GlossaryDocument">GlossaryDocument</see> property.
/// 
/// <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument">GlossaryDocument</see> can contain any number of <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> objects.
/// Each <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> represents one document part.
/// 
/// Corresponds to the <b>%glossaryDocument</b> and <b>%docParts</b> elements in OOXML.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::Document::get_GlossaryDocument
/// @sa Aspose::Words::BuildingBlocks::BuildingBlock
class ASPOSE_WORDS_SHARED_CLASS GlossaryDocument : public Aspose::Words::DocumentBase
{
    typedef GlossaryDocument ThisType;
    typedef Aspose::Words::DocumentBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::DocumentBase::Clone;

public:

    /// Returns the <see cref="Aspose::Words::NodeType::GlossaryDocument">GlossaryDocument</see> value.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns a typed collection that represents all building blocks in the glossary document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlockCollection> get_BuildingBlocks();
    /// Gets the first building block in the glossary document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> get_FirstBuildingBlock();
    /// Gets the last building block in the glossary document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> get_LastBuildingBlock();

    /// Accepts a visitor.
    /// 
    /// Enumerates over this node and all of its children. Each node calls a corresponding method on <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see>.
    /// 
    /// For more info see the Visitor design pattern.
    /// 
    /// Calls <see cref="Aspose::Words::DocumentVisitor::VisitGlossaryDocumentStart(System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument>)">VisitGlossaryDocumentStart()</see>, then calls <see cref="Aspose::Words::Node::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>
    /// for all child nodes of this node and then calls <see cref="Aspose::Words::DocumentVisitor::VisitGlossaryDocumentEnd(System::SharedPtr<Aspose::Words::BuildingBlocks::GlossaryDocument>)">VisitGlossaryDocumentEnd()</see>
    /// at the end.
    /// 
    /// Note: A glossary document node and its children are not visited when you execute a
    /// Visitor over a <see cref="Aspose::Words::Document">Document</see>. If you want to execute a Visitor over a
    /// glossary document, you need to call <see cref="Aspose::Words::BuildingBlocks::GlossaryDocument::Accept(System::SharedPtr<Aspose::Words::DocumentVisitor>)">Accept()</see>.
    /// 
    /// @param visitor The visitor that will visit the nodes.
    /// 
    /// @return True if all nodes were visited; false if <see cref="Aspose::Words::DocumentVisitor">DocumentVisitor</see> stopped the operation before visiting all nodes.
    ASPOSE_WORDS_SHARED_API bool Accept(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the start of the Glossary document.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the Glossary document.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Finds a building block using the specified gallery, category and name.
    /// 
    /// This is a convenience method that iterates over all building blocks
    /// in this collection and returns the first building block that matches
    /// the specified gallery, category and name.
    /// 
    /// %Microsoft Word organizes building blocks into galleries. The galleries
    /// are predefined using the <see cref="Aspose::Words::BuildingBlocks::BuildingBlockGallery">BuildingBlockGallery</see> enum.
    /// Within each gallery, building blocks can be organized into one or more categories.
    /// The category name is a string. Each building block has a name. A building block
    /// name is not guaranteed to be unique.
    /// 
    /// @param gallery The gallery criteria.
    /// @param category The category criteria. Can be <c>%null</c>, in which case it will not be used for comparison.
    /// @param name The building block name criteria.
    /// 
    /// @return The matching building block or <c>%null</c> if a match was not found.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> GetBuildingBlock(Aspose::Words::BuildingBlocks::BuildingBlockGallery gallery, const System::String& category, const System::String& name);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::DocumentFontProvider> get_FontProvider() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentRenderingContext> get_RenderingContext() override;
    ASPOSE_WORDS_SHARED_API bool get_IsTrackRevisionsEnabled() override;
    ASPOSE_WORDS_SHARED_API bool get_IsMoveRevisionsTracked() override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Themes::Theme> GetThemeInternal() override;
    ASPOSE_WORDS_SHARED_API void SuspendTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) override;
    ASPOSE_WORDS_SHARED_API void ResumeTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~GlossaryDocument();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
