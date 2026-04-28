//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Tables/CellFormat.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/TextOrientation.h>
#include <Aspose.Words.Cpp/Tables/CellVerticalAlignment.h>
#include <Aspose.Words.Cpp/Tables/CellMerge.h>
#include <Aspose.Words.Cpp/IShadingAttrSource.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class BorderCollection;
enum class BorderType;

class Shading;
namespace Tables
{

class PreferredWidth;
}
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class SortedList;
}
}
}

namespace Aspose {

namespace Words {

namespace Tables {

/// Represents all formatting for a table cell.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS CellFormat : public Aspose::Words::IBorderAttrSource, public Aspose::Words::IShadingAttrSource
{
    typedef CellFormat ThisType;
    typedef Aspose::Words::IBorderAttrSource BaseType;
    typedef Aspose::Words::IShadingAttrSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the amount of space (in points) to add to the left of the contents of cell.
    ASPOSE_WORDS_SHARED_API double get_LeftPadding();
    /// Sets the amount of space (in points) to add to the left of the contents of cell.
    ASPOSE_WORDS_SHARED_API void set_LeftPadding(double value);
    /// Returns the amount of space (in points) to add to the right of the contents of cell.
    ASPOSE_WORDS_SHARED_API double get_RightPadding();
    /// Sets the amount of space (in points) to add to the right of the contents of cell.
    ASPOSE_WORDS_SHARED_API void set_RightPadding(double value);
    /// Returns the amount of space (in points) to add above the contents of cell.
    ASPOSE_WORDS_SHARED_API double get_TopPadding();
    /// Sets the amount of space (in points) to add above the contents of cell.
    ASPOSE_WORDS_SHARED_API void set_TopPadding(double value);
    /// Returns the amount of space (in points) to add below the contents of cell.
    ASPOSE_WORDS_SHARED_API double get_BottomPadding();
    /// Sets the amount of space (in points) to add below the contents of cell.
    ASPOSE_WORDS_SHARED_API void set_BottomPadding(double value);
    /// Gets collection of borders of the cell.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Returns a <see cref="Aspose::Words::Shading">Shading</see> object that refers to the shading formatting for the cell.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shading> get_Shading();
    /// Returns the vertical alignment of text in the cell.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::CellVerticalAlignment get_VerticalAlignment();
    /// Sets the vertical alignment of text in the cell.
    ASPOSE_WORDS_SHARED_API void set_VerticalAlignment(Aspose::Words::Tables::CellVerticalAlignment value);
    /// Returns visibility of cell mark.
    ASPOSE_WORDS_SHARED_API bool get_HideMark();
    /// Sets visibility of cell mark.
    ASPOSE_WORDS_SHARED_API void set_HideMark(bool value);
    /// Gets the width of the cell in points.
    /// 
    /// The width is calculated by %Aspose.Words on document loading and saving.
    /// Currently, not every combination of table, cell and document properties is supported.
    /// The returned value may not be accurate for some documents.
    /// It may not exactly match the cell width as calculated by MS Word when the document is opened in MS Word.
    /// 
    /// Setting this property is not recommended.
    /// There is no guarantee that the cell will actually have the set width.
    /// The width may be adjusted to accommodate cell contents in an auto-fit table layout.
    /// Cells in other rows may have conflicting width settings.
    /// The table may be resized to fit into the container or to meet table width settings.
    /// Consider using <see cref="Aspose::Words::Tables::CellFormat::get_PreferredWidth">PreferredWidth</see> for setting the cell width.
    /// Setting this property sets <see cref="Aspose::Words::Tables::CellFormat::get_PreferredWidth">PreferredWidth</see> implicitly since version 15.8.
    /// 
    /// @sa Aspose::Words::Tables::CellFormat::get_PreferredWidth
    ASPOSE_WORDS_SHARED_API double get_Width();
    /// Setter for Aspose::Words::Tables::CellFormat::get_Width
    ASPOSE_WORDS_SHARED_API void set_Width(double value);
    /// Returns or sets the preferred width of the cell.
    /// 
    /// The preferred width (along with the table's Auto Fit option) determines how the actual
    /// width of the cell is calculated by the table layout algorithm. Table layout can be performed by
    /// %Aspose.Words when it saves the document or by %Microsoft Word when it displays the document.
    /// 
    /// The preferred width can be specified in points or in percent. The preferred width
    /// can also be specified as "auto", which means no preferred width is specified.
    /// 
    /// The default value is <see cref="Aspose::Words::Tables::PreferredWidth::Auto">Auto</see>.
    /// 
    /// @sa Aspose::Words::Tables::CellFormat::get_Width
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Tables::PreferredWidth> get_PreferredWidth();
    /// Setter for Aspose::Words::Tables::CellFormat::get_PreferredWidth
    ASPOSE_WORDS_SHARED_API void set_PreferredWidth(const System::SharedPtr<Aspose::Words::Tables::PreferredWidth>& value);
    /// Specifies how the cell is merged with other cells vertically.
    /// 
    /// Cells can only be merged vertically if their left and right boundaries are identical.
    /// 
    /// When cells are vertically merged, the display areas of the merged cells are consolidated.
    /// The consolidated area is used to display the contents of the first vertically merged cell
    /// and all other vertically merged cells must be empty.
    /// 
    /// @sa Aspose::Words::Tables::CellFormat::get_HorizontalMerge
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::CellMerge get_VerticalMerge();
    /// Setter for Aspose::Words::Tables::CellFormat::get_VerticalMerge
    ASPOSE_WORDS_SHARED_API void set_VerticalMerge(Aspose::Words::Tables::CellMerge value);
    /// Specifies how the cell is merged horizontally with other cells in the row.
    /// 
    /// @sa Aspose::Words::Tables::CellFormat::get_VerticalMerge
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::CellMerge get_HorizontalMerge();
    /// Specifies how the cell is merged horizontally with other cells in the row.
    /// 
    /// @sa Aspose::Words::Tables::CellFormat::get_VerticalMerge
    ASPOSE_WORDS_SHARED_API void set_HorizontalMerge(Aspose::Words::Tables::CellMerge value);
    /// Returns the orientation of text in a table cell.
    ASPOSE_WORDS_SHARED_API Aspose::Words::TextOrientation get_Orientation();
    /// Sets the orientation of text in a table cell.
    ASPOSE_WORDS_SHARED_API void set_Orientation(Aspose::Words::TextOrientation value);
    /// If <c>%true</c>, fits text in the cell, compressing each paragraph to the width of the cell.
    ASPOSE_WORDS_SHARED_API bool get_FitText();
    /// If <c>%true</c>, fits text in the cell, compressing each paragraph to the width of the cell.
    ASPOSE_WORDS_SHARED_API void set_FitText(bool value);
    /// If <c>%true</c>, wrap text for the cell.
    ASPOSE_WORDS_SHARED_API bool get_WrapText();
    /// If <c>%true</c>, wrap text for the cell.
    ASPOSE_WORDS_SHARED_API void set_WrapText(bool value);

    /// Resets to default cell formatting. Does not change the width of the cell.
    ASPOSE_WORDS_SHARED_API void ClearFormatting();
    /// Sets the amount of space (in points) to add to the left/top/right/bottom of the contents of cell.
    ASPOSE_WORDS_SHARED_API void SetPaddings(double leftPadding, double topPadding, double rightPadding, double bottomPadding);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~CellFormat();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;
    System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t ) override;

};

}
}
}
