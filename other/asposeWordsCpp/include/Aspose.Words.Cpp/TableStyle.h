//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/TableStyle.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Tables/TableAlignment.h>
#include <Aspose.Words.Cpp/Tables/CellVerticalAlignment.h>
#include <Aspose.Words.Cpp/Style.h>
#include <Aspose.Words.Cpp/IShadingAttrSource.h>
#include <Aspose.Words.Cpp/IRowAttrSource.h>
#include <Aspose.Words.Cpp/ICellAttrSource.h>
#include <Aspose.Words.Cpp/IBorderAttrSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class BorderCollection;
enum class BorderType;

class ConditionalStyleCollection;

class Shading;
class StyleCollection;

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

/// Represents a table style.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-tables/">Working with Tables</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS TableStyle : public Aspose::Words::Style, public Aspose::Words::ICellAttrSource, public Aspose::Words::IRowAttrSource, public Aspose::Words::IBorderAttrSource, public Aspose::Words::IShadingAttrSource
{
    typedef TableStyle ThisType;
    typedef Aspose::Words::Style BaseType;
    typedef Aspose::Words::ICellAttrSource BaseType1;
    typedef Aspose::Words::IRowAttrSource BaseType2;
    typedef Aspose::Words::IBorderAttrSource BaseType3;
    typedef Aspose::Words::IShadingAttrSource BaseType4;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2, BaseType3, BaseType4> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

protected:

protected:

public:

    /// Gets a flag indicating whether text in a table row is allowed to split across a page break.
    ASPOSE_WORDS_SHARED_API bool get_AllowBreakAcrossPages();
    /// Sets a flag indicating whether text in a table row is allowed to split across a page break.
    ASPOSE_WORDS_SHARED_API void set_AllowBreakAcrossPages(bool value);
    /// Gets the collection of default cell borders for the style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BorderCollection> get_Borders();
    /// Gets the amount of space (in points) to add to the left of the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_LeftPadding();
    /// Sets the amount of space (in points) to add to the left of the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_LeftPadding(double value);
    /// Gets the amount of space (in points) to add to the right of the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_RightPadding();
    /// Sets the amount of space (in points) to add to the right of the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_RightPadding(double value);
    /// Gets the amount of space (in points) to add above the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_TopPadding();
    /// Sets the amount of space (in points) to add above the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_TopPadding(double value);
    /// Gets the amount of space (in points) to add below the contents of table cells.
    ASPOSE_WORDS_SHARED_API double get_BottomPadding();
    /// Sets the amount of space (in points) to add below the contents of table cells.
    ASPOSE_WORDS_SHARED_API void set_BottomPadding(double value);
    /// Specifies the alignment for the table style.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::TableAlignment get_Alignment();
    /// Specifies the alignment for the table style.
    ASPOSE_WORDS_SHARED_API void set_Alignment(Aspose::Words::Tables::TableAlignment value);
    /// Gets the amount of space (in points) between the cells.
    ASPOSE_WORDS_SHARED_API double get_CellSpacing();
    /// Sets the amount of space (in points) between the cells.
    ASPOSE_WORDS_SHARED_API void set_CellSpacing(double value);
    /// Gets or sets whether this is a style for a right-to-left table.
    /// 
    /// When <c>%true</c>, the cells in rows are laid out right to left.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Bidi();
    /// Setter for Aspose::Words::TableStyle::get_Bidi
    ASPOSE_WORDS_SHARED_API void set_Bidi(bool value);
    /// Gets the value that represents the left indent of a table.
    ASPOSE_WORDS_SHARED_API double get_LeftIndent();
    /// Sets the value that represents the left indent of a table.
    ASPOSE_WORDS_SHARED_API void set_LeftIndent(double value);
    /// Gets a <see cref="Aspose::Words::Shading">Shading</see> object that refers to the shading formatting for table cells.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Shading> get_Shading();
    /// Specifies the vertical alignment for the cells.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Tables::CellVerticalAlignment get_VerticalAlignment();
    /// Specifies the vertical alignment for the cells.
    ASPOSE_WORDS_SHARED_API void set_VerticalAlignment(Aspose::Words::Tables::CellVerticalAlignment value);
    /// Gets a number of rows to include in the banding when the style specifies odd/even row banding.
    ASPOSE_WORDS_SHARED_API int32_t get_RowStripe();
    /// Sets a number of rows to include in the banding when the style specifies odd/even row banding.
    ASPOSE_WORDS_SHARED_API void set_RowStripe(int32_t value);
    /// Gets a number of columns to include in the banding when the style specifies odd/even columns banding.
    ASPOSE_WORDS_SHARED_API int32_t get_ColumnStripe();
    /// Sets a number of columns to include in the banding when the style specifies odd/even columns banding.
    ASPOSE_WORDS_SHARED_API void set_ColumnStripe(int32_t value);
    /// Collection of conditional styles that may be defined for this table style.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::ConditionalStyleCollection> get_ConditionalStyles();

protected:

    TableStyle();

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Style> Clone() override;

    ASPOSE_WORDS_SHARED_API bool HasFormatting() override;

    virtual ASPOSE_WORDS_SHARED_API ~TableStyle();

private:

    System::SharedPtr<System::Collections::Generic::SortedList<Aspose::Words::BorderType, int32_t>> get_PossibleBorderKeys() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

    System::SharedPtr<System::Object> GetDirectCellAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchCellAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedCellAttr(int32_t ) override;
    void SetCellAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void ClearCellAttrs() override;
    System::SharedPtr<System::Object> GetDirectRowAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchRowAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedRowAttr(int32_t ) override;
    void SetRowAttr(int32_t , System::SharedPtr<System::Object> ) override;
    void ClearRowAttrs() override;
    void ResetToDefaultAttrs() override;
    System::SharedPtr<System::Object> GetDirectBorderAttr(int32_t ) override;
    System::SharedPtr<System::Object> FetchInheritedBorderAttr(int32_t ) override;
    void SetBorderAttr(int32_t , System::SharedPtr<System::Object> ) override;
    System::SharedPtr<System::Object> FetchInheritedShadingAttr(int32_t ) override;

    ASPOSE_WORDS_SHARED_API ThisType* CppMemberwiseClone() const override;

};

}
}
