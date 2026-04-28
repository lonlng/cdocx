//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/IStructuredDocumentTag.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Markup/SdtType.h>
#include <Aspose.Words.Cpp/Markup/SdtAppearance.h>
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
namespace Markup
{
class XmlMapping;
}
class Node;
class NodeCollection;
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

namespace Markup {

/// \interface IStructuredDocumentTag
/// Interface to define a common data for <see cref="Aspose::Words::Markup::StructuredDocumentTag">StructuredDocumentTag</see> and <see cref="Aspose::Words::Markup::StructuredDocumentTagRangeStart">StructuredDocumentTagRangeStart</see>.
class ASPOSE_WORDS_SHARED_CLASS IStructuredDocumentTag : public virtual System::Object
{
    typedef IStructuredDocumentTag ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns true if this instance is a ranged (multi-section) structured document tag.
    virtual bool get_IsMultiSection() = 0;
    /// Returns Node object that implements this interface.
    virtual System::SharedPtr<Aspose::Words::Node> get_Node() = 0;
    /// Specifies a unique read-only persistent numerical Id for this <b>%SDT</b>.
    virtual int32_t get_Id() = 0;
    /// Specifies a tag associated with the current SDT node.
    /// Can not be null.
    virtual System::String get_Tag() const = 0;
    /// Specifies a tag associated with the current SDT node.
    /// Can not be null.
    virtual void set_Tag(System::String value) = 0;
    /// Specifies the friendly name associated with this <b>%SDT</b>.
    /// Can not be null.
    virtual System::String get_Title() const = 0;
    /// Specifies the friendly name associated with this <b>%SDT</b>.
    /// Can not be null.
    virtual void set_Title(System::String value) = 0;
    /// Gets the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text which should be displayed when this SDT run contents are empty,
    /// the associated mapped XML element is empty as specified via the <see cref="Aspose::Words::Markup::IStructuredDocumentTag::get_XmlMapping">XmlMapping</see> element
    /// or the <see cref="Aspose::Words::Markup::IStructuredDocumentTag::get_IsShowingPlaceholderText">IsShowingPlaceholderText</see> element is true.
    virtual System::SharedPtr<Aspose::Words::BuildingBlocks::BuildingBlock> get_Placeholder() = 0;
    /// Gets Name of the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text.
    /// 
    /// @exception System::InvalidOperationException Throw if BuildingBlock with this name <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see> is not present in <see cref="Aspose::Words::Document::get_GlossaryDocument">GlossaryDocument</see>.
    virtual System::String get_PlaceholderName() = 0;
    /// Sets Name of the <see cref="Aspose::Words::BuildingBlocks::BuildingBlock">BuildingBlock</see> containing placeholder text.
    /// 
    /// @exception System::InvalidOperationException Throw if BuildingBlock with this name <see cref="Aspose::Words::BuildingBlocks::BuildingBlock::get_Name">Name</see> is not present in <see cref="Aspose::Words::Document::get_GlossaryDocument">GlossaryDocument</see>.
    virtual void set_PlaceholderName(System::String value) = 0;
    /// Gets the appearance of the structured document tag.
    virtual Aspose::Words::Markup::SdtAppearance get_Appearance() = 0;
    /// Sets the appearance of the structured document tag.
    virtual void set_Appearance(Aspose::Words::Markup::SdtAppearance value) = 0;
    /// Specifies whether the content of this <b>%SDT</b> shall be interpreted to contain placeholder text
    /// (as opposed to regular text contents within the SDT).
    /// if set to true, this state shall be resumed (showing placeholder text) upon opening this document.
    virtual bool get_IsShowingPlaceholderText() = 0;
    /// Specifies whether the content of this <b>%SDT</b> shall be interpreted to contain placeholder text
    /// (as opposed to regular text contents within the SDT).
    /// if set to true, this state shall be resumed (showing placeholder text) upon opening this document.
    virtual void set_IsShowingPlaceholderText(bool value) = 0;
    /// Gets the level at which this <b>%SDT</b> occurs in the document tree.
    virtual Aspose::Words::Markup::MarkupLevel get_Level() const = 0;
    /// Gets type of this <b>%Structured document tag</b>.
    virtual Aspose::Words::Markup::SdtType get_SdtType() = 0;
    /// When set to true, this property will prohibit a user from deleting this <b>%SDT</b>.
    virtual bool get_LockContentControl() = 0;
    /// When set to true, this property will prohibit a user from deleting this <b>%SDT</b>.
    virtual void set_LockContentControl(bool value) = 0;
    /// When set to true, this property will prohibit a user from editing the contents of this <b>%SDT</b>.
    virtual bool get_LockContents() = 0;
    /// When set to true, this property will prohibit a user from editing the contents of this <b>%SDT</b>.
    virtual void set_LockContents(bool value) = 0;
    /// Gets the color of the structured document tag.
    virtual System::Drawing::Color get_Color() = 0;
    /// Sets the color of the structured document tag.
    virtual void set_Color(System::Drawing::Color value) = 0;
    /// Gets an object that represents the mapping of this structured document tag to XML data
    /// in a custom XML part of the current document.
    virtual System::SharedPtr<Aspose::Words::Markup::XmlMapping> get_XmlMapping() = 0;
    /// Gets a string that represents the XML contained within the node in the <see cref="Aspose::Words::SaveFormat::FlatOpc">FlatOpc</see> format.
    virtual System::String get_WordOpenXML() = 0;

    /// Removes just this SDT node itself, but keeps the content of it inside the document tree.
    virtual void RemoveSelfOnly() = 0;
    /// Returns a live collection of child nodes that match the specified types.
    virtual System::SharedPtr<Aspose::Words::NodeCollection> GetChildNodes(Aspose::Words::NodeType nodeType, bool isDeep) = 0;

};

}
}
}
