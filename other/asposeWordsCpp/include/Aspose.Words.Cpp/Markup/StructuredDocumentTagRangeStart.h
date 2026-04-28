//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/StructuredDocumentTagRangeStart.h
#pragma once

#include <system/shared_ptr.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NodeMatcher.h>
#include <Aspose.Words.Cpp/NodeFinder.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Node.h>
#include <Aspose.Words.Cpp/Markup/SdtType.h>
#include <Aspose.Words.Cpp/Markup/SdtAppearance.h>
#include <Aspose.Words.Cpp/Markup/IStructuredDocumentTag.h>
#include <Aspose.Words.Cpp/Markup/MarkupLevel.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace BuildingBlocks
{
class BuildingBlock;
}

class DocumentBase;
class DocumentVisitor;
class INodeCloningListener;
namespace Markup
{

class StructuredDocumentTagRangeEnd;
class XmlMapping;
}
class Node;
class NodeCollection;

class NodeRange;
class Range;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
namespace Drawing
{
class Color;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Markup {

/// Represents a start of <b>%ranged</b> structured document tag which accepts multi-sections content.
/// See also <see cref="Aspose::Words::Markup::StructuredDocumentTagRangeEnd">StructuredDocumentTagRangeEnd</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS StructuredDocumentTagRangeStart : public Aspose::Words::Node, public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>>, public Aspose::Words::Markup::IStructuredDocumentTag
{
    typedef StructuredDocumentTagRangeStart ThisType;
    typedef Aspose::Words::Node BaseType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Node>> BaseType1;
    typedef Aspose::Words::Markup::IStructuredDocumentTag BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Node::Clone;

private:

public:

    /// Returns <see cref="Aspose::Words::NodeType::StructuredDocumentTagRangeStart">StructuredDocumentTagRangeStart</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Gets the last child in the stdContent range.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_LastChild();
    /// Gets the level at which this structured document tag range start occurs in the document tree.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Markup::MarkupLevel get_Level() const override;
    /// Gets type of this structured document tag.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Markup::SdtType get_SdtType() override;
    /// Gets the color of the structured document tag.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Color() override;
    /// Sets the color of the structured document tag.
    ASPOSE_WORDS_SHARED_API void set_Color(System::Drawing::Color value) override;
    /// Specifies a unique read-only persistent numerical Id for this structured document tag.
    /// 
    /// Id attribute shall follow these rules:
    /// - The document shall retain structured document tag ids only if the whole document
    /// is cloned <see cref="Aspose::Words::Document::Clone">Clone</see>.
    /// - During <see cref="Aspose::Words::DocumentBase::ImportNode(System::SharedPtr<Aspose::Words::Node>, bool)">ImportNode()</see>
    /// Id shall be retained if import does not cause conflicts with other structured document tag Ids in
    /// the target document.
    /// - If multiple structured document tag nodes specify the same decimal number value for the Id attribute,
    /// then the first structured document tag in the document shall maintain this original Id,
    /// and all subsequent structured document tag nodes shall have new identifiers assigned to them when the document is loaded.
    /// - During standalone structured document tag <see cref="Aspose::Words::Markup::StructuredDocumentTag::Clone(bool, System::SharedPtr<Aspose::Words::INodeCloningListener>)">Clone()</see> operation new unique ID will be
    /// generated for the cloned structured document tag node.
    /// - If Id is not specified in the source document, then the structured document tag node shall have a new unique identifier assigned
    /// to it when the document is loaded.
    ASPOSE_WORDS_SHARED_API int32_t get_Id() override;
    /// When set to <c>%true</c>, this property will prohibit a user from deleting this structured document tag.
    ASPOSE_WORDS_SHARED_API bool get_LockContentControl() override;
    /// When set to <c>%true</c>, this property will prohibit a user from deleting this structured document tag.
    ASPOSE_WORDS_SHARED_API void set_LockContentControl(bool value) override;
    /// When set to <c>%true</c>, this property will prohibit a user from editing the contents of this structured document tag.
    ASPOSE_WORDS_SHARED_API bool get_LockContents() override;
    /// When set to <c>%true</c>, this property will prohibit a user from editing the contents of this structured document tag.
    ASPOSE_WORDS_SHARED_API void set_LockContents(bool value) override;
    /// Specifies whether the content of this structured document tag shall be interpreted to contain
    /// placeholder text (as opposed to regular text contents within the structured document tag).
    /// if set to <c>%true</c>, this state shall be resumed (showing placeholder text) upon opening this document.
    ASPOSE_WORDS_SHARED_API bool get_IsShowingPlaceholderText() override;
    /// Specifies whether the content of this structured document tag shall be interpreted to contain
    /// placeholder text (as opposed to regular text contents within the structured document tag).
    /// if set to <c>%true</c>, this state shall be resumed (showing placeholder text) upon opening this document.
    ASPOSE_WORDS_SHARED_API void set_IsShowingPlaceholderText(bool value) override;
    /// Gets the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text which should be displayed when
    /// this structured document tag run contents are empty, the associated mapped XML element is empty as specified
    /// via the <see cref="Aspose::Words::Markup::StructuredDocumentTagRangeStart::get_XmlMapping">XmlMapping</see> element or the <see cref="Aspose::Words::Markup::StructuredDocumentTagRangeStart::get_IsShowingPlaceholderText">IsShowingPlaceholderText</see> element is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> get_Placeholder() override;
    /// Gets Name of the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text.
    /// 
    /// @exception System::InvalidOperationException Throw if BuildingBlock with this name <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see> is not present in <see cref="Aspose::Words::Document::get_GlossaryDocument">GlossaryDocument</see>.
    ASPOSE_WORDS_SHARED_API System::String get_PlaceholderName() override;
    /// Sets Name of the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text.
    /// 
    /// @exception System::InvalidOperationException Throw if BuildingBlock with this name <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see> is not present in <see cref="Aspose::Words::Document::get_GlossaryDocument">GlossaryDocument</see>.
    ASPOSE_WORDS_SHARED_API void set_PlaceholderName(System::String value) override;
    /// Specifies a tag associated with the current structured document tag node.
    /// Can not be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Tag() const override;
    /// Specifies a tag associated with the current structured document tag node.
    /// Can not be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Tag(System::String value) override;
    /// Specifies the friendly name associated with this structured document tag.
    /// Can not be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::String get_Title() const override;
    /// Specifies the friendly name associated with this structured document tag.
    /// Can not be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_Title(System::String value) override;
    /// Gets a string that represents the XML contained within the node in the <see cref="Aspose::Words::SaveFormat::FlatOpc">FlatOpc</see> format.
    ASPOSE_WORDS_SHARED_API System::String get_WordOpenXML() override;
    /// Gets a string that represents the XML contained within the node in the <see cref="Aspose::Words::SaveFormat::FlatOpc">FlatOpc</see> format.
    /// Unlike the <see cref="Aspose::Words::Markup::StructuredDocumentTagRangeStart::get_WordOpenXML">WordOpenXML</see> property, this method generates a stripped-down document that excludes any non-content-related parts.
    ASPOSE_WORDS_SHARED_API System::String get_WordOpenXMLMinimal();
    /// Gets the appearance of the structured document tag.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Markup::SdtAppearance get_Appearance() override;
    /// Sets the appearance of the structured document tag.
    ASPOSE_WORDS_SHARED_API void set_Appearance(Aspose::Words::Markup::SdtAppearance value) override;
    /// Gets an object that represents the mapping of this structured document tag range to XML data
    /// in a custom XML part of the current document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::XmlMapping> get_XmlMapping() override;
    /// Specifies end of range if the <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see> is a ranged structured document tag.
    /// Otherwise returns <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::StructuredDocumentTagRangeEnd> get_RangeEnd();

    /// Initializes a new instance of the <b>%Structured document tag range start</b> class.
    /// 
    /// The following types of SDT can be created:
    /// 
    /// - <see cref="Aspose::Words::Markup::SdtType::Checkbox">Checkbox</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::DropDownList">DropDownList</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::ComboBox">ComboBox</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::Date">Date</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::BuildingBlockGallery">BuildingBlockGallery</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::Group">Group</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::Picture">Picture</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::RichText">RichText</see>
    /// - <see cref="Aspose::Words::Markup::SdtType::PlainText">PlainText</see>
    /// 
    /// @param doc The owner document.
    /// @param type Type of SDT node.
    ASPOSE_WORDS_SHARED_API StructuredDocumentTagRangeStart(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, Aspose::Words::Markup::SdtType type);

    /// Returns a live collection of child nodes that match the specified types.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeCollection> GetChildNodes(Aspose::Words::NodeType nodeType, bool isDeep) override;
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
    /// Provides support for the for each style iteration over the child nodes of this node.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Node>>> GetEnumerator() override;
    /// Adds the specified node to the end of the stdContent range.
    /// 
    /// @param newChild The node to add.
    /// 
    /// @return The node added.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> AppendChild(const System::SharedPtr<Aspose::Words::Node>& newChild);
    /// Removes all the nodes between this range start node and the range end node.
    ASPOSE_WORDS_SHARED_API void RemoveAllChildren();
    /// Removes this range start and appropriate range end nodes of the structured document tag,
    /// but keeps its content inside the document tree.
    ASPOSE_WORDS_SHARED_API void RemoveSelfOnly() override;
    ASPOSE_WORDS_SHARED_API void SetTemplateWeakPtr(uint32_t argument) override;

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~StructuredDocumentTagRangeStart();

private:

    ASPOSE_WORDS_SHARED_API bool get_IsMultiSection() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> get_Node() override;

    System::SharedPtr<System::Object> mField0;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
