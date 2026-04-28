//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Shape.h
#pragma once

#include <Aspose.Words.Cpp/StoryType.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/Drawing/ShapeType.h>
#include <Aspose.Words.Cpp/Drawing/ShapeBase.h>
#include <Aspose.Words.Cpp/Drawing/Core/ITextBox.h>
#include <Aspose.Words.Cpp/Drawing/Core/IStrokable.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Drawing
{
class DrColor;
}

namespace Words
{

class DocumentBase;

class DocumentVisitor;
namespace Drawing
{
class AdjustmentCollection;
enum class ArrowLength;
enum class ArrowType;
enum class ArrowWidth;
namespace Charts
{
class Chart;
}
namespace Core
{

namespace Dml
{

namespace Fills
{
class DmlFill;
}

namespace Themes
{
class IThemeProvider;
}
}

enum class LineFillType;

}
enum class DashStyle;
enum class EndCap;
class HorizontalRuleFormat;
class ImageData;
enum class JoinStyle;
enum class LayoutFlow;
class OleFormat;
enum class ShapeLineStyle;
enum class ShapeMarkupLanguage : uint8_t;
class SignatureLine;
class Stroke;
class TextBox;
enum class TextBoxWrapMode;
class TextPath;
}
class INodeCloningListener;

class Node;
class Paragraph;

namespace Themes
{
enum class ThemeColor;
}

}
}
namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents an object in the drawing layer, such as an AutoShape, textbox, freeform, OLE object, ActiveX control, or picture.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-shapes/">Working with Shapes</a> documentation article.
/// 
/// Using the <see cref="Aspose::Words::Drawing::Shape">Shape</see> class you can create or modify shapes in a %Microsoft Word document.
/// 
/// An important property of a shape is its <see cref="Aspose::Words::Drawing::ShapeBase::get_ShapeType">ShapeType</see>. Shapes of different
/// types can have different capabilities in a Word document. For example, only image and OLE shapes
/// can have images inside them. Most of the shapes can have text, but not all.
/// 
/// Shapes that can have text, can contain <see cref="Aspose::Words::Paragraph">Paragraph</see> and
/// <see cref="Aspose::Words::Tables::Table">Table</see> nodes as children.
/// 
/// @sa Aspose::Words::Drawing::ShapeBase
/// @sa Aspose::Words::Drawing::GroupShape
class ASPOSE_WORDS_SHARED_CLASS Shape final : public Aspose::Words::Drawing::ShapeBase, public Aspose::Words::Drawing::Core::ITextBox, public Aspose::Words::Drawing::Core::IStrokable
{
    typedef Shape ThisType;
    typedef Aspose::Words::Drawing::ShapeBase BaseType;
    typedef Aspose::Words::Drawing::Core::ITextBox BaseType1;
    typedef Aspose::Words::Drawing::Core::IStrokable BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::Drawing::ShapeBase::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::Shape">Shape</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns <see cref="Aspose::Words::StoryType::Textbox">Textbox</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StoryType get_StoryType();
    /// Returns <c>%true</c> if an extrusion effect is enabled.
    ASPOSE_WORDS_SHARED_API bool get_ExtrusionEnabled();
    /// Returns <c>%true</c> if a shadow effect is enabled.
    ASPOSE_WORDS_SHARED_API bool get_ShadowEnabled();
    /// Defines a stroke for a shape.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Stroke> get_Stroke();
    /// Defines whether the path will be stroked.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Stroke::get_On">On</see> property.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_Stroked();
    /// Setter for Aspose::Words::Drawing::Shape::get_Stroked
    ASPOSE_WORDS_SHARED_API void set_Stroked(bool value);
    /// Defines the brush thickness that strokes the path of a shape in points.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Stroke::get_Weight">Weight</see> property.
    /// 
    /// The default value is 0.75.
    ASPOSE_WORDS_SHARED_API double get_StrokeWeight();
    /// Setter for Aspose::Words::Drawing::Shape::get_StrokeWeight
    ASPOSE_WORDS_SHARED_API void set_StrokeWeight(double value);
    /// Defines the color of a stroke.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Stroke::get_Color">Color</see> property.
    /// 
    /// The default value is
    /// <see cref="System::Drawing::Color::get_Black">Black</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_StrokeColor();
    /// Setter for Aspose::Words::Drawing::Shape::get_StrokeColor
    ASPOSE_WORDS_SHARED_API void set_StrokeColor(System::Drawing::Color value);
    /// Determines whether the closed path of the shape will be filled.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Fill::get_Visible">Visible</see> property.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_Filled();
    /// Setter for Aspose::Words::Drawing::Shape::get_Filled
    ASPOSE_WORDS_SHARED_API void set_Filled(bool value);
    /// Defines the brush color that fills the closed path of the shape.
    /// 
    /// This is a shortcut to the <see cref="Aspose::Words::Drawing::Fill::get_Color">Color</see> property.
    /// 
    /// The default value is
    /// <see cref="System::Drawing::Color::get_White">White</see>.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_FillColor();
    /// Setter for Aspose::Words::Drawing::Shape::get_FillColor
    ASPOSE_WORDS_SHARED_API void set_FillColor(System::Drawing::Color value);
    /// Returns <c>%true</c> if the shape has image bytes or links an image.
    ASPOSE_WORDS_SHARED_API bool get_HasImage();
    /// Provides access to the image of the shape.
    /// Returns <c>%null</c> if the shape cannot have an image.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::ImageData> get_ImageData();
    /// Provides access to the OLE data of a shape. For a shape that is not an OLE object or ActiveX control, returns <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::OleFormat> get_OleFormat();
    /// Defines attributes that specify how text is displayed in a shape.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::TextBox> get_TextBox();
    /// Defines the text of the text path (of a WordArt object).
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::TextPath> get_TextPath();
    /// Gets the first paragraph in the shape.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> get_FirstParagraph();
    /// Gets the last paragraph in the shape.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Paragraph> get_LastParagraph();
    /// Provides access to the properties of the horizontal rule shape.
    /// For a shape that is not a horizontal rule, returns <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::HorizontalRuleFormat> get_HorizontalRuleFormat();
    /// Provides access to the adjustment raw values of a shape.
    /// For a shape that does not contain any adjustment raw values, it returns an empty collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::AdjustmentCollection> get_Adjustments();
    /// Gets <see cref="Aspose::Words::Drawing::SignatureLine">SignatureLine</see> object if the shape is a signature line. Returns <c>%null</c> otherwise.
    /// 
    /// @sa Aspose::Words::DocumentBuilder::InsertSignatureLine(System::SharedPtr<Aspose::Words::SignatureLineOptions>, Aspose::Words::Drawing::RelativeHorizontalPosition, double, Aspose::Words::Drawing::RelativeVerticalPosition, double, Aspose::Words::Drawing::WrapType)
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::SignatureLine> get_SignatureLine();
    /// Returns <c>%true</c> if this <see cref="Aspose::Words::Drawing::Shape">Shape</see> has a <see cref="Aspose::Words::Drawing::Charts::Chart">Chart</see>.
    ASPOSE_WORDS_SHARED_API bool get_HasChart();
    /// Returns <c>%true</c> if this <see cref="Aspose::Words::Drawing::Shape">Shape</see> has a SmartArt object.
    ASPOSE_WORDS_SHARED_API bool get_HasSmartArt();
    /// Provides access to the chart properties if this shape has a <see cref="Aspose::Words::Drawing::Charts::Chart">Chart</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::Chart> get_Chart();

    /// Creates a new shape object.
    /// 
    /// You should specify desired shape properties after you created a shape.
    /// 
    /// @param doc The owner document.
    /// @param shapeType The type of the shape to create.
    ASPOSE_WORDS_SHARED_API Shape(const System::SharedPtr<Aspose::Words::DocumentBase>& doc, Aspose::Words::Drawing::ShapeType shapeType);

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
    /// Accepts a visitor for visiting the start of the shape.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the shape.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Updates SmartArt pre-rendered drawing by using Aspose.Words's SmartArt cold rendering engine.
    ASPOSE_WORDS_SHARED_API void UpdateSmartArtDrawing();

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsPercentWidthInapplicable() override;

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;
    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Shape();

private:

    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeForeColor() override;
    void set_StrokeForeColor(System::SharedPtr<Aspose::Drawing::DrColor> ) override;
    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBaseForeColor() override;
    System::SharedPtr<Aspose::Drawing::DrColor> get_StrokeBackColor() override;
    void set_StrokeBackColor(System::SharedPtr<Aspose::Drawing::DrColor> ) override;
    Aspose::Words::Themes::ThemeColor get_StrokeForeThemeColor() override;
    void set_StrokeForeThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    Aspose::Words::Themes::ThemeColor get_StrokeBackThemeColor() override;
    void set_StrokeBackThemeColor(Aspose::Words::Themes::ThemeColor ) override;
    double get_StrokeForeTintAndShade() override;
    void set_StrokeForeTintAndShade(double ) override;
    double get_StrokeBackTintAndShade() override;
    void set_StrokeBackTintAndShade(double ) override;
    bool get_StrokeVisible() override;
    void set_StrokeVisible(bool ) override;
    double get_StrokeTransparency() override;
    void set_StrokeTransparency(double ) override;
    double get_Weight() override;
    void set_Weight(double ) override;
    Aspose::Words::Drawing::DashStyle get_DashStyle() override;
    void set_DashStyle(Aspose::Words::Drawing::DashStyle ) override;
    Aspose::Words::Drawing::JoinStyle get_JoinStyle() override;
    void set_JoinStyle(Aspose::Words::Drawing::JoinStyle ) override;
    Aspose::Words::Drawing::EndCap get_EndCap() override;
    void set_EndCap(Aspose::Words::Drawing::EndCap ) override;
    Aspose::Words::Drawing::ShapeLineStyle get_LineStyle() override;
    void set_LineStyle(Aspose::Words::Drawing::ShapeLineStyle ) override;
    Aspose::Words::Drawing::ArrowType get_StartArrowType() override;
    void set_StartArrowType(Aspose::Words::Drawing::ArrowType ) override;
    Aspose::Words::Drawing::ArrowType get_EndArrowType() override;
    void set_EndArrowType(Aspose::Words::Drawing::ArrowType ) override;
    Aspose::Words::Drawing::ArrowWidth get_StartArrowWidth() override;
    void set_StartArrowWidth(Aspose::Words::Drawing::ArrowWidth ) override;
    Aspose::Words::Drawing::ArrowLength get_StartArrowLength() override;
    void set_StartArrowLength(Aspose::Words::Drawing::ArrowLength ) override;
    Aspose::Words::Drawing::ArrowWidth get_EndArrowWidth() override;
    void set_EndArrowWidth(Aspose::Words::Drawing::ArrowWidth ) override;
    Aspose::Words::Drawing::ArrowLength get_EndArrowLength() override;
    void set_EndArrowLength(Aspose::Words::Drawing::ArrowLength ) override;
    Aspose::Words::Drawing::Core::LineFillType get_LineFillType() override;
    void set_LineFillType(Aspose::Words::Drawing::Core::LineFillType ) override;
    System::ArrayPtr<uint8_t> get_StrokeImageBytes() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_StrokeThemeProvider() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_StrokeFill() override;
    ASPOSE_WORDS_SHARED_API void set_StrokeFill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;
    Aspose::Words::Drawing::TextBoxWrapMode get_TextBoxWrapMode_ITextBox() override;
    Aspose::Words::Drawing::LayoutFlow get_TextboxLayoutFlow_ITextBox() override;
    bool get_HasVerticalTextFlow_ITextBox() override;
    Aspose::Words::Drawing::ShapeMarkupLanguage get_MarkupLanguage_ITextBox() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;

    float GetHorizontalMargins_ITextBox() override;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
}
