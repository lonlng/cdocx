//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataTable.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartItemTextProperties.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{
namespace Charts
{

class ChartFormat;
enum class ChartShapeType;
namespace Core
{

namespace ComplexTypes
{
class DmlChartSpPr;
class DmlChartTx;
class DmlChartTxPr;
}

}
}
namespace Core
{
namespace Dml
{
namespace Fills
{
class DmlFill;
}
namespace Outlines
{
class DmlOutline;
}
namespace Themes
{
class IThemeProvider;
}
}
}
}
class Font;

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Allows to specify properties of a chart data table.
class ASPOSE_WORDS_SHARED_CLASS ChartDataTable : public Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties, public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartDataTable ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a flag indicating whether the data table will be shown for the chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_Show() const;
    /// Sets a flag indicating whether the data table will be shown for the chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_Show(bool value);
    /// Gets a flag indicating whether legend keys are displayed in the data table.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_HasLegendKeys() const;
    /// Sets a flag indicating whether legend keys are displayed in the data table.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_HasLegendKeys(bool value);
    /// Gets a flag indicating whether a horizontal border of the data table is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_HasHorizontalBorder() const;
    /// Sets a flag indicating whether a horizontal border of the data table is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_HasHorizontalBorder(bool value);
    /// Gets a flag indicating whether a vertical border of the data table is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_HasVerticalBorder() const;
    /// Sets a flag indicating whether a vertical border of the data table is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_HasVerticalBorder(bool value);
    /// Gets a flag indicating whether an outline border, that is, a border around series and category names,
    /// is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_HasOutlineBorder() const;
    /// Sets a flag indicating whether an outline border, that is, a border around series and category names,
    /// is displayed.
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_HasOutlineBorder(bool value);
    /// Provides access to font formatting of the data table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Provides access to fill of text background and border formatting of the data table.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartDataTable();

private:

    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> get_ItemTx() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_ItemTxPr() override;
    void set_ItemTxPr(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartSpPr> get_ItemSpPr() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_CollectionTxPr() override;
    bool get_IsFillSupported() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_Fill() override;
    void set_Fill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> get_Outline() override;
    void set_Outline(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> ) override;
    Aspose::Words::Drawing::Charts::ChartShapeType get_ShapeType() override;
    void set_ShapeType(Aspose::Words::Drawing::Charts::ChartShapeType ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_ThemeProvider() override;
    bool get_IsFormatDefined() override;

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;

    System::String GenerateItemText() override;
    System::SharedPtr<System::Object> FetchSpecialDefaultRunPropertyValue(int32_t ) override;
    System::SharedPtr<System::Object> GetRelativePropertyValue(int32_t , System::SharedPtr<System::Object> ) override;
    void MaterializeSpPr() override;

};

}
}
}
}
