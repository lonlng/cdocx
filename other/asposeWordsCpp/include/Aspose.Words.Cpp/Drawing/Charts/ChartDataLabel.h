//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataLabel.h
#pragma once

#include <system/shared_ptr.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/Drawing/ShapeTextOrientation.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/INumberFormatProvider.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartItemTextProperties.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelPosition.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelLocationMode.h>
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
class ChartNumberFormat;

enum class ChartShapeType;
namespace Core
{

namespace ComplexTypes
{

class DmlChartNumFormat;

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
class DateTime;
class String;
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents data label on a chart point or trendline.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartDataLabel : public Aspose::Words::Drawing::Charts::Core::INumberFormatProvider, public Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties, public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartDataLabel ThisType;
    typedef Aspose::Words::Drawing::Charts::Core::INumberFormatProvider BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::IChartItemTextProperties BaseType1;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the index of the containing element.
    /// This index shall determine which of the parent's children collection this element applies to.
    /// Default value is 0.
    ASPOSE_WORDS_SHARED_API int32_t get_Index();
    /// Allows to specify if category name is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowCategoryName();
    /// Allows to specify if category name is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowCategoryName(bool value);
    /// Allows to specify if bubble size is to be displayed for the data labels on a chart.
    /// Applies only to Bubble charts.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowBubbleSize();
    /// Allows to specify if bubble size is to be displayed for the data labels on a chart.
    /// Applies only to Bubble charts.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowBubbleSize(bool value);
    /// Allows to specify if legend key is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowLegendKey();
    /// Allows to specify if legend key is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowLegendKey(bool value);
    /// Allows to specify if percentage value is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowPercentage();
    /// Allows to specify if percentage value is to be displayed for the data labels on a chart.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowPercentage(bool value);
    /// Returns a Boolean to indicate the series name display behavior for the data labels on a chart.
    /// <c>%true</c> to show the series name; <c>%false</c> to hide. By default <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowSeriesName();
    /// Sets a Boolean to indicate the series name display behavior for the data labels on a chart.
    /// <c>%true</c> to show the series name; <c>%false</c> to hide. By default <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowSeriesName(bool value);
    /// Allows to specify if values are to be displayed in the data labels.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowValue();
    /// Allows to specify if values are to be displayed in the data labels.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowValue(bool value);
    /// Allows to specify if data label leader lines need be shown.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowLeaderLines();
    /// Allows to specify if data label leader lines need be shown.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowLeaderLines(bool value);
    /// Allows to specify if values from data labels range to be displayed in the data labels.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowDataLabelsRange();
    /// Allows to specify if values from data labels range to be displayed in the data labels.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowDataLabelsRange(bool value);
    /// Gets string separator used for the data labels on a chart.
    /// The default is a comma, except for pie charts showing only category name and percentage, when a line break
    /// shall be used instead.
    ASPOSE_WORDS_SHARED_API System::String get_Separator();
    /// Sets string separator used for the data labels on a chart.
    /// The default is a comma, except for pie charts showing only category name and percentage, when a line break
    /// shall be used instead.
    ASPOSE_WORDS_SHARED_API void set_Separator(const System::String& value);
    /// Gets the orientation of the label text.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ShapeTextOrientation get_Orientation();
    /// Sets the orientation of the label text.
    ASPOSE_WORDS_SHARED_API void set_Orientation(Aspose::Words::Drawing::ShapeTextOrientation value);
    /// Gets or sets the rotation of the label in degrees.
    /// 
    /// The range of acceptable values is from -180 to 180 inclusive. The default value is 0.
    /// 
    /// If the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Orientation">Orientation</see> value is <see cref="Aspose::Words::Drawing::ShapeTextOrientation::Horizontal">Horizontal</see>, the
    /// label shape, if it exists, is rotated along with the label text. Otherwise, only the label text is rotated.
    ASPOSE_WORDS_SHARED_API int32_t get_Rotation();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabel::get_Rotation
    ASPOSE_WORDS_SHARED_API void set_Rotation(int32_t value);
    /// Returns <c>%true</c> if this data label has something to display.
    ASPOSE_WORDS_SHARED_API bool get_IsVisible();
    /// Returns number format of the parent element.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartNumberFormat> get_NumberFormat();
    /// Gets/sets a flag indicating whether this label is hidden.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsHidden();
    /// Gets/sets a flag indicating whether this label is hidden.
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IsHidden(bool value);
    /// Provides access to the font formatting of this data label.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Provides access to fill and line formatting of the data label.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Gets or sets the distance of the data label in points from the left edge of the chart or from the position
    /// specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see> property, depending on the value of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_LeftMode">LeftMode</see>
    /// property.
    /// 
    /// The value of the property changes proportionally if the chart shape is resized.
    /// 
    /// The property cannot be set in a Word 2016 chart.
    ASPOSE_WORDS_SHARED_API double get_Left();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabel::get_Left
    ASPOSE_WORDS_SHARED_API void set_Left(double value);
    /// Gets the interpretation mode of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Left">Left</see> property value: whether it sets the location
    /// of the data label from the left edge of the chart of from the position specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see>
    /// property.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode get_LeftMode();
    /// Sets the interpretation mode of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Left">Left</see> property value: whether it sets the location
    /// of the data label from the left edge of the chart of from the position specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see>
    /// property.
    ASPOSE_WORDS_SHARED_API void set_LeftMode(Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode value);
    /// Gets or sets the distance of the data label in points from the top edge of the chart or from the position
    /// specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see> property, depending on the value of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_TopMode">TopMode</see>
    /// property.
    /// 
    /// The value of the property changes proportionally if the chart shape is resized.
    /// 
    /// The property cannot be set in a Word 2016 chart.
    ASPOSE_WORDS_SHARED_API double get_Top();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabel::get_Top
    ASPOSE_WORDS_SHARED_API void set_Top(double value);
    /// Gets the interpretation mode of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Top">Top</see> property value: whether it sets the location
    /// of the data label from the top edge of the chart of from the position specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see>
    /// property.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode get_TopMode();
    /// Sets the interpretation mode of the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Top">Top</see> property value: whether it sets the location
    /// of the data label from the top edge of the chart of from the position specified by its <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position">Position</see>
    /// property.
    ASPOSE_WORDS_SHARED_API void set_TopMode(Aspose::Words::Drawing::Charts::ChartDataLabelLocationMode value);
    /// Gets or sets the position of the data label.
    /// 
    /// The position can be set for data labels of the following chart series types:
    /// 
    /// - <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Bar">Bar</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Column">Column</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Histogram">Histogram</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Pareto">Pareto</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Waterfall">Waterfall</see>; allowed values: <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Center">Center</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::InsideBase">InsideBase</see>, <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::InsideEnd">InsideEnd</see> and
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::OutsideEnd">OutsideEnd</see>;
    /// 
    /// - <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::BarStacked">BarStacked</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::BarPercentStacked">BarPercentStacked</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::ColumnStacked">ColumnStacked</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::ColumnPercentStacked">ColumnPercentStacked</see>; allowed
    /// values: <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Center">Center</see>, <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::InsideBase">InsideBase</see>
    /// and <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::InsideEnd">InsideEnd</see>;
    /// 
    /// - <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Bubble">Bubble</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Bubble3D">Bubble3D</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Line">Line</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::LineStacked">LineStacked</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::LinePercentStacked">LinePercentStacked</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Scatter">Scatter</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Stock">Stock</see>; allowed values: <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Center">Center</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Left">Left</see>, <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Right">Right</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Above">Above</see> and <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Below">Below</see>;
    /// 
    /// - <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Pie">Pie</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::Pie3D">Pie3D</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::PieOfBar">PieOfBar</see>, <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::PieOfPie">PieOfPie</see>; allowed values:
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Center">Center</see>, <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::InsideEnd">InsideEnd</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::OutsideEnd">OutsideEnd</see> and <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::BestFit">BestFit</see>;
    /// 
    /// - <see cref="Aspose::Words::Drawing::Charts::ChartSeriesType::BoxAndWhisker">BoxAndWhisker</see>; allowed values:
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Left">Left</see>, <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Right">Right</see>,
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Above">Above</see> and <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelPosition::Below">Below</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartDataLabelPosition get_Position();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabel::get_Position
    ASPOSE_WORDS_SHARED_API void set_Position(Aspose::Words::Drawing::Charts::ChartDataLabelPosition value);

    /// Clears format of this data label. The properties are set to the default values defined in the parent data
    /// label collection.
    ASPOSE_WORDS_SHARED_API void ClearFormat();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartDataLabel();

private:

    bool get_IsFillSupported() override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> get_Fill() override;
    void set_Fill(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Fills::DmlFill> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> get_Outline() override;
    void set_Outline(System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Outlines::DmlOutline> ) override;
    Aspose::Words::Drawing::Charts::ChartShapeType get_ShapeType() override;
    void set_ShapeType(Aspose::Words::Drawing::Charts::ChartShapeType ) override;
    System::SharedPtr<Aspose::Words::Drawing::Core::Dml::Themes::IThemeProvider> get_ThemeProvider() override;
    bool get_IsFormatDefined() override;

    __TypeStub<4,4,4,4>::type mField0;

    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> get_NumFmt_INumberFormatProvider() override;
    void set_NumFmt_INumberFormatProvider(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> ) override;
    bool get_IsInherited() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTx> get_ItemTx() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_ItemTxPr() override;
    void set_ItemTxPr(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> ) override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartSpPr> get_ItemSpPr() override;
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartTxPr> get_CollectionTxPr() override;

    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::WeakPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;

    void MaterializeSpPr() override;
    System::String GenerateItemText() override;
    System::SharedPtr<System::Object> FetchSpecialDefaultRunPropertyValue(int32_t ) override;
    System::SharedPtr<System::Object> GetRelativePropertyValue(int32_t , System::SharedPtr<System::Object> ) override;

};

}
}
}
}
