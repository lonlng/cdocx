//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/GroupShape.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Drawing/ShapeBase.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class DocumentBase;

class DocumentVisitor;
namespace Drawing
{

enum class ShapeMarkupLanguage : uint8_t;
}
class Node;

}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents a group of shapes in a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/how-to-add-group-shape-into-a-word-document/">How to Add Group Shape into a Word Document</a> documentation article.
/// 
/// A <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see> is a composite node and can have <see cref="Aspose::Words::Drawing::Shape">Shape</see> and
/// <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see> nodes as children.
/// 
/// Each <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see> defines a new coordinate system for its child shapes.
/// The coordinate system is defined using the <see cref="Aspose::Words::Drawing::ShapeBase::get_CoordSize">CoordSize</see> and
/// <see cref="Aspose::Words::Drawing::ShapeBase::get_CoordOrigin">CoordOrigin</see> properties.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase
/// @sa Aspose::Words::Drawing::Shape
class ASPOSE_WORDS_SHARED_CLASS GroupShape : public Aspose::Words::Drawing::ShapeBase
{
    typedef GroupShape ThisType;
    typedef Aspose::Words::Drawing::ShapeBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns <see cref="Aspose::Words::NodeType::GroupShape">GroupShape</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;

    /// Creates a new group shape.
    /// 
    /// By default, the shape is floating and has default location and size.
    /// 
    /// You should specify desired shape properties after you created a shape.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API GroupShape(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

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
    /// Accepts a visitor for visiting the start of the GroupShape.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the GroupShape.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsPercentWidthInapplicable() override;

    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~GroupShape();

private:

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
