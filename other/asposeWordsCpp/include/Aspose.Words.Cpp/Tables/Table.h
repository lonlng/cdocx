//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/Table.h
#pragma once

#include <Aspose.Words.Cpp/Tables/TextWrapping.h>
#include <Aspose.Words.Cpp/Tables/TableStyleOptions.h>
#include <Aspose.Words.Cpp/Tables/TableAlignment.h>
#include <Aspose.Words.Cpp/Tables/AutoFitBehavior.h>
#include <Aspose.Words.Cpp/StyleIdentifier.h>
#include <Aspose.Words.Cpp/NodeType.h>
#include <Aspose.Words.Cpp/CompositeNode.h>
#include <Aspose.Words.Cpp/Drawing/VerticalAlignment.h>
#include <Aspose.Words.Cpp/Drawing/RelativeVerticalPosition.h>
#include <Aspose.Words.Cpp/Drawing/RelativeHorizontalPosition.h>
#include <Aspose.Words.Cpp/Drawing/HorizontalAlignment.h>
#include <Aspose.Words.Cpp/VisitorAction.h>
#include <Aspose.Words.Cpp/TextureIndex.h>
#include <Aspose.Words.Cpp/LineStyle.h>
#include <Aspose.Words.Cpp/BorderType.h>
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

class Style;

namespace Tables
{

class PreferredWidth;
class Row;
class RowCollection;

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

namespace Tables {

/// Represents a table in a Word document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
/// 
/// <see cref="Aspose::Words::Tables::Table">Table</see> is a block-level node and can be a child of classes derived from <see cref="Aspose::Words::Story">Story</see> or
/// <see cref="Aspose::Words::InlineStory">InlineStory</see>.
/// 
/// <see cref="Aspose::Words::Tables::Table">Table</see> can contain one or more <see cref="Aspose::Words::Tables::Row">Row</see> nodes.
/// 
/// A minimal valid table needs to have at least one <see cref="Aspose::Words::Tables::Row">Row</see>.
class ASPOSE_WORDS_SHARED_CLASS Table : public Aspose::Words::CompositeNode
{
    typedef Table ThisType;
    typedef Aspose::Words::CompositeNode BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:
    using Aspose::Words::CompositeNode::Clone;

public:

    /// Returns <see cref="Aspose::Words::NodeType::Table">Table</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::NodeType get_NodeType() const override;
    /// Returns the first <see cref="Aspose::Words::Tables::Row">Row</see> node in the table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Row> get_FirstRow();
    /// Returns the last <see cref="Aspose::Words::Tables::Row">Row</see> node in the table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::Row> get_LastRow();
    /// Provides typed access to the rows of the table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::RowCollection> get_Rows();
    /// Specifies how an inline table is aligned in the document.
    /// 
    /// The default value is <see cref="Aspose::Words::Tables::TableAlignment::Left">Left</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::TableAlignment get_Alignment();
    /// Specifies how an inline table is aligned in the document.
    /// 
    /// The default value is <see cref="Aspose::Words::Tables::TableAlignment::Left">Left</see>.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::Tables::TableAlignment value);
    /// Allows %Microsoft Word and %Aspose.Words to automatically resize cells in a table to fit their contents.
    /// 
    /// The default value is <c>%true</c>.
    /// 
    /// @sa Aspose::Words::Tables::Table::AutoFit(Aspose::Words::Tables::AutoFitBehavior)
    ASPOSE_WORDS_SHARED_API bool get_AllowAutoFit();
    /// Setter for Aspose::Words::Tables::Table::get_AllowAutoFit
    ASPOSE_WORDS_SHARED_API void set_AllowAutoFit(bool value);
    /// Gets the table preferred width.
    /// 
    /// The default value is <see cref="Aspose::Words::Tables::PreferredWidth::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::PreferredWidth> get_PreferredWidth();
    /// Sets the table preferred width.
    /// 
    /// The default value is <see cref="Aspose::Words::Tables::PreferredWidth::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API void set_PreferredWidth(const System::SharedPtr<Aspose::Words::Tables::PreferredWidth>& value);
    /// Gets or sets whether this is a right-to-left table.
    /// 
    /// When <c>%true</c>, the cells in this row are laid out right to left.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Bidi();
    /// Setter for Aspose::Words::Tables::Table::get_Bidi
    ASPOSE_WORDS_SHARED_API void set_Bidi(bool value);
    /// Gets the amount of space (in points) to add to the left of the contents of cells.
    ASPOSE_WORDS_SHARED_API double get_LeftPadding();
    /// Sets the amount of space (in points) to add to the left of the contents of cells.
    ASPOSE_WORDS_SHARED_API void set_LeftPadding(double value);
    /// Gets the amount of space (in points) to add to the right of the contents of cells.
    ASPOSE_WORDS_SHARED_API double get_RightPadding();
    /// Sets the amount of space (in points) to add to the right of the contents of cells.
    ASPOSE_WORDS_SHARED_API void set_RightPadding(double value);
    /// Gets the amount of space (in points) to add above the contents of cells.
    ASPOSE_WORDS_SHARED_API double get_TopPadding();
    /// Sets the amount of space (in points) to add above the contents of cells.
    ASPOSE_WORDS_SHARED_API void set_TopPadding(double value);
    /// Gets the amount of space (in points) to add below the contents of cells.
    ASPOSE_WORDS_SHARED_API double get_BottomPadding();
    /// Sets the amount of space (in points) to add below the contents of cells.
    ASPOSE_WORDS_SHARED_API void set_BottomPadding(double value);
    /// Gets the amount of space (in points) between the cells.
    ASPOSE_WORDS_SHARED_API double get_CellSpacing();
    /// Sets the amount of space (in points) between the cells.
    ASPOSE_WORDS_SHARED_API void set_CellSpacing(double value);
    /// Gets the "Allow spacing between cells" option.
    ASPOSE_WORDS_SHARED_API bool get_AllowCellSpacing();
    /// Sets the "Allow spacing between cells" option.
    ASPOSE_WORDS_SHARED_API void set_AllowCellSpacing(bool value);
    /// Gets the value that represents the left indent of the table.
    ASPOSE_WORDS_SHARED_API double get_LeftIndent();
    /// Sets the value that represents the left indent of the table.
    ASPOSE_WORDS_SHARED_API void set_LeftIndent(double value);
    /// Gets bit flags that specify how a table style is applied to this table.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::TableStyleOptions get_StyleOptions();
    /// Sets bit flags that specify how a table style is applied to this table.
    ASPOSE_WORDS_SHARED_API void set_StyleOptions(Aspose::Words::Tables::TableStyleOptions value);
    /// Gets the table style applied to this table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> get_Style();
    /// Sets the table style applied to this table.
    ASPOSE_WORDS_SHARED_API void set_Style(const System::SharedPtr<Aspose::Words::Style>& value);
    /// Gets the name of the table style applied to this table.
    ASPOSE_WORDS_SHARED_API System::String get_StyleName();
    /// Sets the name of the table style applied to this table.
    ASPOSE_WORDS_SHARED_API void set_StyleName(const System::String& value);
    /// Gets the locale independent style identifier of the table style applied to this table.
    ASPOSE_WORDS_SHARED_API Aspose::Words::StyleIdentifier get_StyleIdentifier();
    /// Sets the locale independent style identifier of the table style applied to this table.
    ASPOSE_WORDS_SHARED_API void set_StyleIdentifier(Aspose::Words::StyleIdentifier value);
    /// Gets <see cref="Aspose::Words::Tables::Table::get_TextWrapping">TextWrapping</see> for table.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::TextWrapping get_TextWrapping();
    /// Sets <see cref="Aspose::Words::Tables::Table::get_TextWrapping">TextWrapping</see> for table.
    ASPOSE_WORDS_SHARED_API void set_TextWrapping(Aspose::Words::Tables::TextWrapping value);
    /// Gets or sets title of this table.
    /// It provides an alternative text representation of the information contained in the table.
    /// 
    /// The default value is an empty string.
    /// 
    /// This property is meaningful for ISO/IEC 29500 compliant DOCX documents
    /// (<see cref="Aspose::Words::Saving::OoxmlCompliance">OoxmlCompliance</see>).
    /// When saved to pre-ISO/IEC 29500 formats, the property is ignored.
    ASPOSE_WORDS_SHARED_API System::String get_Title();
    /// Setter for Aspose::Words::Tables::Table::get_Title
    ASPOSE_WORDS_SHARED_API void set_Title(const System::String& value);
    /// Gets or sets description of this table.
    /// It provides an alternative text representation of the information contained in the table.
    /// 
    /// The default value is an empty string.
    /// 
    /// This property is meaningful for ISO/IEC 29500 compliant DOCX documents
    /// (<see cref="Aspose::Words::Saving::OoxmlCompliance">OoxmlCompliance</see>).
    /// When saved to pre-ISO/IEC 29500 formats, the property is ignored.
    ASPOSE_WORDS_SHARED_API System::String get_Description();
    /// Setter for Aspose::Words::Tables::Table::get_Description
    ASPOSE_WORDS_SHARED_API void set_Description(const System::String& value);
    /// Gets distance between table left and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API double get_DistanceLeft();
    /// Sets distance between table left and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API void set_DistanceLeft(double value);
    /// Gets distance between table right and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API double get_DistanceRight();
    /// Sets distance between table right and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API void set_DistanceRight(double value);
    /// Gets distance between table top and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API double get_DistanceTop();
    /// Sets distance between table top and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API void set_DistanceTop(double value);
    /// Gets distance between table bottom and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API double get_DistanceBottom();
    /// Sets distance between table bottom and the surrounding text, in points.
    ASPOSE_WORDS_SHARED_API void set_DistanceBottom(double value);
    /// Gets floating table relative horizontal alignment.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::HorizontalAlignment get_RelativeHorizontalAlignment();
    /// Sets floating table relative horizontal alignment.
    ASPOSE_WORDS_SHARED_API void set_RelativeHorizontalAlignment(Aspose::Words::Drawing::HorizontalAlignment value);
    /// Gets floating table relative vertical alignment.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::VerticalAlignment get_RelativeVerticalAlignment();
    /// Sets floating table relative vertical alignment.
    ASPOSE_WORDS_SHARED_API void set_RelativeVerticalAlignment(Aspose::Words::Drawing::VerticalAlignment value);
    /// Gets the base object from which the horizontal positioning of floating table should be calculated.
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeHorizontalPosition::Column">Column</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::RelativeHorizontalPosition get_HorizontalAnchor();
    /// Gets the base object from which the horizontal positioning of floating table should be calculated.
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeHorizontalPosition::Column">Column</see>.
    ASPOSE_WORDS_SHARED_API void set_HorizontalAnchor(Aspose::Words::Drawing::RelativeHorizontalPosition value);
    /// Gets the base object from which the vertical positioning of floating table should be calculated.
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeVerticalPosition::Margin">Margin</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::RelativeVerticalPosition get_VerticalAnchor();
    /// Gets the base object from which the vertical positioning of floating table should be calculated.
    /// Default value is <see cref="Aspose::Words::Drawing::RelativeVerticalPosition::Margin">Margin</see>.
    ASPOSE_WORDS_SHARED_API void set_VerticalAnchor(Aspose::Words::Drawing::RelativeVerticalPosition value);
    /// Gets absolute horizontal floating table position specified by the table properties, in points.
    /// Default value is 0.
    ASPOSE_WORDS_SHARED_API double get_AbsoluteHorizontalDistance();
    /// Sets absolute horizontal floating table position specified by the table properties, in points.
    /// Default value is 0.
    ASPOSE_WORDS_SHARED_API void set_AbsoluteHorizontalDistance(double value);
    /// Gets absolute vertical floating table position specified by the table properties, in points.
    /// Default value is 0.
    ASPOSE_WORDS_SHARED_API double get_AbsoluteVerticalDistance();
    /// Sets absolute vertical floating table position specified by the table properties, in points.
    /// Default value is 0.
    ASPOSE_WORDS_SHARED_API void set_AbsoluteVerticalDistance(double value);
    /// Gets whether a floating table shall allow other floating objects in the document
    /// to overlap its extents when displayed.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_AllowOverlap();

    /// Initializes a new instance of the <see cref="Aspose::Words::Tables::Table">Table</see> class.
    /// 
    /// When <see cref="Aspose::Words::Tables::Table">Table</see> is created, it belongs to the specified document, but is not
    /// yet part of the document and <see cref="Aspose::Words::Node::get_ParentNode">ParentNode</see> is <c>%null</c>.
    /// 
    /// To append <see cref="Aspose::Words::Tables::Table">Table</see> to the document use <see cref="Aspose::Words::CompositeNode::InsertAfter``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertAfter``1()</see> or <see cref="Aspose::Words::CompositeNode::InsertBefore``1(System::SharedPtr<``0>, System::SharedPtr<Aspose::Words::Node>)">InsertBefore``1()</see>
    /// on the story where you want the table inserted.
    /// 
    /// @param doc The owner document.
    ASPOSE_WORDS_SHARED_API Table(const System::SharedPtr<Aspose::Words::DocumentBase>& doc);

    /// Converts cells horizontally merged by width to cells merged by <see cref="Aspose::Words::Tables::CellFormat::get_HorizontalMerge">HorizontalMerge</see>.
    /// 
    /// Table cells can be horizontally merged either using merge flags <see cref="Aspose::Words::Tables::CellFormat::get_HorizontalMerge">HorizontalMerge</see> or using cell width <see cref="Aspose::Words::Tables::CellFormat::get_Width">Width</see>.
    /// 
    /// When table cell is merged by width property <see cref="Aspose::Words::Tables::CellFormat::get_HorizontalMerge">HorizontalMerge</see> is meaningless but sometimes having merge flags is more convenient way.
    /// 
    /// Use this method to transforms table cells horizontally merged by width to cells merged by merge flags.
    ASPOSE_WORDS_SHARED_API void ConvertToHorizontallyMergedCells();
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
    /// Accepts a visitor for visiting the start of the table.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptStart(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// Accepts a visitor for visiting the end of the table.
    /// 
    /// @param visitor The document visitor.
    /// 
    /// @return The action to be taken by the visitor.
    ASPOSE_WORDS_SHARED_API Aspose::Words::VisitorAction AcceptEnd(System::SharedPtr<Aspose::Words::DocumentVisitor> visitor) override;
    /// If the table has no rows, creates and appends one <see cref="Aspose::Words::Tables::Row">Row</see>.
    ASPOSE_WORDS_SHARED_API void EnsureMinimum();
    /// Sets all table borders to the specified line style, width and color.
    /// 
    /// @param lineStyle The line style to apply.
    /// @param lineWidth The line width to set (in points).
    /// @param color The color to use for the border.
    ASPOSE_WORDS_SHARED_API void SetBorders(Aspose::Words::LineStyle lineStyle, double lineWidth, System::Drawing::Color color);
    /// Sets the specified table border to the specified line style, width and color.
    /// 
    /// @param borderType The table border to change.
    /// @param lineStyle The line style to apply.
    /// @param lineWidth The line width to set (in points).
    /// @param color The color to use for the border.
    /// @param isOverrideCellBorders When <c>%true</c>, causes all existing explicit cell borders to be removed.
    ASPOSE_WORDS_SHARED_API void SetBorder(Aspose::Words::BorderType borderType, Aspose::Words::LineStyle lineStyle, double lineWidth, System::Drawing::Color color, bool isOverrideCellBorders);
    /// Removes all table and cell borders on this table.
    ASPOSE_WORDS_SHARED_API void ClearBorders();
    /// Sets shading to the specified values on whole table.
    /// 
    /// @param texture The texture to apply.
    /// @param foregroundColor The color of the texture.
    /// @param backgroundColor The color of the background fill.
    ASPOSE_WORDS_SHARED_API void SetShading(Aspose::Words::TextureIndex texture, System::Drawing::Color foregroundColor, System::Drawing::Color backgroundColor);
    /// Removes all shading on the table.
    ASPOSE_WORDS_SHARED_API void ClearShading();
    /// Resizes the table and cells according to the specified auto fit behavior.
    /// 
    /// This method mimics the commands available in the Auto Fit menu for a table in %Microsoft Word.
    /// The commands available are "Auto Fit to Contents", "Auto Fit to Window" and "Fixed Column Width". In %Microsoft Word
    /// these commands set relevant table properties and then update the table layout and %Aspose.Words does the same for you.
    /// 
    /// @param behavior Specifies how to auto fit the table.
    ASPOSE_WORDS_SHARED_API void AutoFit(Aspose::Words::Tables::AutoFitBehavior behavior);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Node> Clone(bool , System::SharedPtr<Aspose::Words::INodeCloningListener> ) override;

    ASPOSE_WORDS_SHARED_API bool CanInsert(System::SharedPtr<Aspose::Words::Node> ) override;

    virtual ASPOSE_WORDS_SHARED_API ~Table();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

protected:

};

}
}
}
