//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelCollection.h
#pragma once

#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/ShapeTextOrientation.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/INumberFormatProvider.h>
#include <Aspose.Words.Cpp/Drawing/Charts/Core/IChartFormatSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartDataLabelPosition.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Drawing
{
namespace Charts
{
class ChartDataLabel;
class ChartFormat;
class ChartNumberFormat;

enum class ChartShapeType;
namespace Core
{

namespace ComplexTypes
{

class DmlChartNumFormat;

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
namespace Collections
{
namespace Generic
{
template <typename> class List;

}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents a collection of <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel">ChartDataLabel</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartDataLabelCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataLabel>>, public Aspose::Words::Drawing::Charts::Core::INumberFormatProvider, public Aspose::Words::Drawing::Charts::Core::IChartFormatSource
{
    typedef ChartDataLabelCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataLabel>> BaseType;
    typedef Aspose::Words::Drawing::Charts::Core::INumberFormatProvider BaseType1;
    typedef Aspose::Words::Drawing::Charts::Core::IChartFormatSource BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel">ChartDataLabel</see> in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Allows to specify whether category name is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowCategoryName();
    /// Allows to specify whether category name is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowCategoryName(bool value);
    /// Allows to specify whether bubble size is to be displayed for the data labels of the entire series.
    /// Applies only to Bubble charts.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowBubbleSize();
    /// Allows to specify whether bubble size is to be displayed for the data labels of the entire series.
    /// Applies only to Bubble charts.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowBubbleSize(bool value);
    /// Allows to specify whether legend key is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowLegendKey();
    /// Allows to specify whether legend key is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowLegendKey(bool value);
    /// Allows to specify whether percentage value is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>. Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API bool get_ShowPercentage();
    /// Allows to specify whether percentage value is to be displayed for the data labels of the entire series.
    /// Default value is <c>%false</c>. Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API void set_ShowPercentage(bool value);
    /// Returns a Boolean to indicate the series name display behavior for the data labels of the entire series.
    /// <c>%true</c> to show the series name; <c>%false</c> to hide. By default <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowSeriesName();
    /// Sets a Boolean to indicate the series name display behavior for the data labels of the entire series.
    /// <c>%true</c> to show the series name; <c>%false</c> to hide. By default <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowSeriesName(bool value);
    /// Allows to specify whether values are to be displayed in the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowValue();
    /// Allows to specify whether values are to be displayed in the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowValue(bool value);
    /// Allows to specify whether data label leader lines need be shown for the data labels of the entire series.
    /// Default value is <c>%false</c>.
    /// 
    /// Applies to Pie charts only.
    /// Leader lines create a visual connection between a data label and its corresponding data point.
    /// 
    /// Value defined for this property can be overridden for an individual data label with using the
    /// <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel::get_ShowLeaderLines">ShowLeaderLines</see> property.
    ASPOSE_WORDS_SHARED_API bool get_ShowLeaderLines();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabelCollection::get_ShowLeaderLines
    ASPOSE_WORDS_SHARED_API void set_ShowLeaderLines(bool value);
    /// Allows to specify whether values from data labels range to be displayed in the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowDataLabelsRange();
    /// Allows to specify whether values from data labels range to be displayed in the data labels of the entire series.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowDataLabelsRange(bool value);
    /// Gets string separator used for the data labels of the entire series.
    /// The default is a comma, except for pie charts showing only category name and percentage, when a line break
    /// shall be used instead.
    ASPOSE_WORDS_SHARED_API System::String get_Separator();
    /// Sets string separator used for the data labels of the entire series.
    /// The default is a comma, except for pie charts showing only category name and percentage, when a line break
    /// shall be used instead.
    ASPOSE_WORDS_SHARED_API void set_Separator(const System::String& value);
    /// Gets the text orientation of the data labels of the entire series.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::ShapeTextOrientation get_Orientation();
    /// Sets the text orientation of the data labels of the entire series.
    ASPOSE_WORDS_SHARED_API void set_Orientation(Aspose::Words::Drawing::ShapeTextOrientation value);
    /// Gets or sets the rotation of the data labels of the entire series in degrees.
    /// 
    /// The range of acceptable values is from -180 to 180 inclusive. The default value is 0.
    /// 
    /// If the <see cref="Aspose::Words::Drawing::Charts::ChartDataLabelCollection::get_Orientation">Orientation</see> value is <see cref="Aspose::Words::Drawing::ShapeTextOrientation::Horizontal">Horizontal</see>, label shapes,
    /// if they exist, are rotated along with the label text. Otherwise, only the label text is rotated.
    ASPOSE_WORDS_SHARED_API int32_t get_Rotation();
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabelCollection::get_Rotation
    ASPOSE_WORDS_SHARED_API void set_Rotation(int32_t value);
    /// Gets an <see cref="Aspose::Words::Drawing::Charts::ChartNumberFormat">ChartNumberFormat</see> instance allowing to set number format for the data labels of the
    /// entire series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartNumberFormat> get_NumberFormat();
    /// Provides access to the font formatting of the data labels of the entire series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Font> get_Font();
    /// Provides access to fill and line formatting of the data labels.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Gets or sets the position of the data labels.
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
    /// Setter for Aspose::Words::Drawing::Charts::ChartDataLabelCollection::get_Position
    ASPOSE_WORDS_SHARED_API void set_Position(Aspose::Words::Drawing::Charts::ChartDataLabelPosition value);

    /// Returns <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel">ChartDataLabel</see> for the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataLabel> idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataLabel>>> GetEnumerator() override;
    /// Clears format of all <see cref="Aspose::Words::Drawing::Charts::ChartDataLabel">ChartDataLabel</see> in this collection.
    ASPOSE_WORDS_SHARED_API void ClearFormat();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartDataLabelCollection();

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
    System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> get_NumFmt_INumberFormatProvider() override;
    void set_NumFmt_INumberFormatProvider(System::SharedPtr<Aspose::Words::Drawing::Charts::Core::ComplexTypes::DmlChartNumFormat> ) override;
    bool get_IsInherited() override;

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::WeakPtr<System::Object> mField2;
    System::WeakPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::SharedPtr<System::Object> mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;

    void MaterializeSpPr() override;

};

}
}
}
}
