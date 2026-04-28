//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DocumentBase.h
#pragma once

#include <system/memory_management.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/ImportFormatMode.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class CompositeNode;
class CompositeNodeHelper;

class DocumentRenderingContext;
namespace Drawing
{

class Shape;
class ShapeBase;

}

namespace Fonts
{
class DocumentFontProvider;

class FontInfoCollection;
}

class INodeChangingCallback;
class INodeCloningListener;
class IWarningCallback;

namespace Lists
{
class ListCollection;

}
namespace Loading
{
class IResourceLoadingCallback;

}

class Node;
enum class NodeChangingAction;
class NodeChangingArgs;

class NodeCollection;

namespace Notes
{
class FootnoteSeparatorCollection;
}

namespace Revisions
{
class RevisionTrackingUtil;
}

class StyleCollection;
enum class SuspendedRevisionTypes;

class SuspendTrackRevisionsDocument;

namespace Themes
{
class Theme;

}

}
}
namespace System
{

namespace Drawing
{
class Color;
}
class String;
}

namespace Aspose {

namespace Words {

/// Provides the abstract base class for a main document and a glossary document of a Word document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/aspose-words-document-object-model/">%Aspose.Words Document Object Model (DOM)</a> documentation article.
/// 
/// %Aspose.Words represents a Word document as a tree of nodes. <see cref="Aspose::Words::DocumentBase">DocumentBase</see> is a
/// root node of the tree that contains all other nodes of the document.
/// 
/// <see cref="Aspose::Words::DocumentBase">DocumentBase</see> also stores document-wide information such as <see cref="Aspose::Words::DocumentBase::get_Styles">Styles</see> and
/// <see cref="Aspose::Words::DocumentBase::get_Lists">Lists</see> that the tree nodes might refer to.
/// 
/// @sa Aspose::Words::Document
/// @sa Aspose::Words::DocumentBase
class ASPOSE_WORDS_SHARED_CLASS DocumentBase : public Aspose::Words::CompositeNode
{
    typedef DocumentBase ThisType;
    typedef Aspose::Words::CompositeNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Gets this instance.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DocumentBase> get_Document() const override;
    /// Called when a node is inserted or removed in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::INodeChangingCallback> get_NodeChangingCallback();
    /// Called when a node is inserted or removed in the document.
    ASPOSE_WORDS_SHARED_API void set_NodeChangingCallback(const System::SharedPtr<Aspose::Words::INodeChangingCallback>& value);
    /// Allows to control how external resources are loaded.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::IResourceLoadingCallback> get_ResourceLoadingCallback() const;
    /// Allows to control how external resources are loaded.
    ASPOSE_WORDS_SHARED_API void set_ResourceLoadingCallback(const System::SharedPtr<Aspose::Words::Loading::IResourceLoadingCallback>& value);
    /// Provides access to properties of fonts used in this document.
    /// 
    /// This collection of font definitions is loaded as is from the document.
    /// Font definitions might be optional, missing or incomplete in some documents.
    /// 
    /// Do not rely on this collection to ascertain that a particular font is used in the document.
    /// You should only use this collection to get information about fonts that might be used in the document.
    /// 
    /// @sa Aspose::Words::Fonts::FontInfoCollection
    /// @sa Aspose::Words::Fonts::FontInfo
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fonts::FontInfoCollection> get_FontInfos() const;
    /// Returns a collection of styles defined in the document.
    /// 
    /// For more information see the description of the <see cref="Aspose::Words::StyleCollection">StyleCollection</see> class.
    /// 
    /// @sa Aspose::Words::StyleCollection
    /// @sa Aspose::Words::Style
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::StyleCollection> get_Styles() const;
    /// Provides access to the list formatting used in the document.
    /// 
    /// For more information see the description of the <see cref="Aspose::Words::Lists::ListCollection">ListCollection</see> class.
    /// 
    /// @sa Aspose::Words::Lists::ListCollection
    /// @sa Aspose::Words::Lists::List
    /// @sa Aspose::Words::Lists::ListFormat
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Lists::ListCollection> get_Lists() const;
    /// Called during various document processing procedures when an issue is detected that might result
    /// in data or formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::IWarningCallback> get_WarningCallback() const;
    /// Called during various document processing procedures when an issue is detected that might result
    /// in data or formatting fidelity loss.
    ASPOSE_WORDS_SHARED_API void set_WarningCallback(const System::SharedPtr<Aspose::Words::IWarningCallback>& value);
    /// Provides access to the footnote/endnote separators defined in the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Notes::FootnoteSeparatorCollection> get_FootnoteSeparators() const;
    /// Gets or sets the background shape of the document. Can be <c>%null</c>.
    /// 
    /// %Microsoft Word allows only a shape that has its <see cref="Aspose::Words::Drawing::ShapeBase::get_ShapeType">ShapeType</see> property equal
    /// to <see cref="Aspose::Words::Drawing::ShapeType::Rectangle">Rectangle</see> to be used as a background shape for a document.
    /// 
    /// %Microsoft Word supports only the fill properties of a background shape. All other properties
    /// are ignored.
    /// 
    /// Setting this property to a non-null value will also set the <see cref="Aspose::Words::Settings::ViewOptions::get_DisplayBackgroundShape">DisplayBackgroundShape</see> to <c>%true</c>.
    /// 
    /// @sa Aspose::Words::Settings::ViewOptions::get_DisplayBackgroundShape
    /// @sa Aspose::Words::DocumentBase::get_PageColor
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Shape> get_BackgroundShape() const;
    /// Setter for Aspose::Words::DocumentBase::get_BackgroundShape
    ASPOSE_WORDS_SHARED_API void set_BackgroundShape(const System::SharedPtr<Aspose::Words::Drawing::Shape>& value);
    /// Gets or sets the page color of the document. This property is a simpler version of <see cref="Aspose::Words::DocumentBase::get_BackgroundShape">BackgroundShape</see>.
    /// 
    /// This property provides a simple way to specify a solid page color for the document.
    /// Setting this property creates and sets an appropriate <see cref="Aspose::Words::DocumentBase::get_BackgroundShape">BackgroundShape</see>.
    /// 
    /// If the page color is not set (e.g. there is no background shape in the document) returns
    /// <see cref="System::Drawing::Color::Empty">Empty</see>.
    /// 
    /// @sa Aspose::Words::DocumentBase::get_BackgroundShape
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_PageColor();
    /// Setter for Aspose::Words::DocumentBase::get_PageColor
    ASPOSE_WORDS_SHARED_API void set_PageColor(System::Drawing::Color value);

    /// Imports a node from another document to the current document.
    /// 
    /// This method uses the <see cref="Aspose::Words::ImportFormatMode::UseDestinationStyles">UseDestinationStyles</see> option to resolve formatting.
    /// 
    /// Importing a node creates a copy of the source node belonging to the importing document.
    /// The returned node has no parent. The source node is not altered or removed from the original document.
    /// 
    /// Before a node from another document can be inserted into this document, it must be imported.
    /// During import, document-specific properties such as references to styles and lists are translated
    /// from the original to the importing document. After the node was imported, it can be inserted
    /// into the appropriate place in the document using <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see> or
    /// <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see>.
    /// 
    /// If the source node already belongs to the destination document, then simply a deep clone
    /// of the source node is created.
    /// 
    /// @param srcNode The node being imported.
    /// @param isImportChildren <c>%true</c> to import all child nodes recursively; otherwise, <c>%false</c>.
    /// 
    /// @return The cloned node that belongs to the current document.
    /// 
    /// @sa Aspose::Words::NodeImporter
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> ImportNode(const System::SharedPtr<Aspose::Words::Node>& srcNode, bool isImportChildren);
    /// Imports a node from another document to the current document with an option to control formatting.
    /// 
    /// This overload is useful to control how styles and list formatting are imported.
    /// 
    /// Importing a node creates a copy of the source node belonging to the importing document.
    /// The returned node has no parent. The source node is not altered or removed from the original document.
    /// 
    /// Before a node from another document can be inserted into this document, it must be imported.
    /// During import, document-specific properties such as references to styles and lists are translated
    /// from the original to the importing document. After the node was imported, it can be inserted
    /// into the appropriate place in the document using <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see> or
    /// <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see>.
    /// 
    /// If the source node already belongs to the destination document, then simply a deep clone
    /// of the source node is created.
    /// 
    /// @param srcNode The node to imported.
    /// @param isImportChildren <c>%true</c> to import all child nodes recursively; otherwise, <c>%false</c>.
    /// @param importFormatMode Specifies how to merge style formatting that clashes.
    /// 
    /// @return The cloned, imported node. The node belongs to the destination document, but has no parent.
    /// 
    /// @sa Aspose::Words::ImportFormatMode
    /// @sa Aspose::Words::NodeImporter
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> ImportNode(const System::SharedPtr<Aspose::Words::Node>& srcNode, bool isImportChildren, Aspose::Words::ImportFormatMode importFormatMode);

protected:

    virtual bool get_IsTrackRevisionsEnabled() = 0;
    virtual bool get_IsMoveRevisionsTracked() = 0;

    virtual System::SharedPtr<Aspose::Words::Fonts::DocumentFontProvider> get_FontProvider() = 0;
    virtual System::SharedPtr<Aspose::Words::DocumentRenderingContext> get_RenderingContext() = 0;

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<System::Object> mField1;

    ASPOSE_WORDS_SHARED_API DocumentBase();

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual void SuspendTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) = 0;
    virtual void ResumeTrackRevisions(Aspose::Words::SuspendedRevisionTypes ) = 0;

    virtual ASPOSE_WORDS_SHARED_API int32_t GetNextShapeId(System::SharedPtr<Aspose::Words::Drawing::ShapeBase> );

    virtual ASPOSE_WORDS_SHARED_API int32_t MapShapeToRange(int32_t , int32_t );

    virtual System::SharedPtr<Aspose::Words::Themes::Theme> GetThemeInternal() = 0;

    virtual ASPOSE_WORDS_SHARED_API ~DocumentBase();

private:

    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    __TypeStub<1,1,1,1>::type mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    System::SharedPtr<System::Object> mField14;
    System::SharedPtr<System::Object> mField15;
    System::SharedPtr<System::Object> mField16;
    System::SharedPtr<System::Object> mField17;
    System::SharedPtr<System::Object> mField18;
    System::SharedPtr<System::Object> mField19;
    System::SharedPtr<System::Object> mField20;
    System::SharedPtr<System::Object> mField21;
    System::SharedPtr<System::Object> mField22;
    System::SharedPtr<System::Object> mField23;
    System::SharedPtr<System::Object> mField24;
    __TypeStub<4,4,4,4>::type mField25;

protected:

};

}
}
