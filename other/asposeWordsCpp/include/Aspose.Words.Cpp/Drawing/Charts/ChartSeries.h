//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartSeries.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/Drawing/Core/Dml/IDmlExtensionListSource.h>
#include <Aspose.Words.Cpp/Drawing/Charts/IChartDataPoint.h>
#include <Aspose.Words.Cpp/Drawing/Charts/ChartSeriesType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{

namespace Drawing
{
namespace Charts
{
class BubbleSizeCollection;

class ChartDataLabelCollection;

class ChartDataPointCollection;
class ChartFormat;
class ChartLegendEntry;

class ChartMarker;

class ChartXValue;
class ChartXValueCollection;
class ChartYValue;
class ChartYValueCollection;

}
namespace Core
{
namespace Dml
{
class DmlExtension;
}
}
}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents chart series properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartSeries : public Aspose::Words::Drawing::Charts::IChartDataPoint, public Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource
{
    typedef ChartSeries ThisType;
    typedef Aspose::Words::Drawing::Charts::IChartDataPoint BaseType;
    typedef Aspose::Words::Drawing::Core::Dml::IDmlExtensionListSource BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API int32_t get_Explosion() override;
    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    ASPOSE_WORDS_SHARED_API void set_Explosion(int32_t value) override;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    ASPOSE_WORDS_SHARED_API bool get_InvertIfNegative() override;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    ASPOSE_WORDS_SHARED_API void set_InvertIfNegative(bool value) override;
    /// Specifies a data marker. Marker is automatically created when requested.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMarker> get_Marker() override;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    ASPOSE_WORDS_SHARED_API bool get_Bubble3D() override;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    ASPOSE_WORDS_SHARED_API void set_Bubble3D(bool value) override;
    /// Returns a collection of formatting objects for all data points in this series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataPointCollection> get_DataPoints() const;
    /// Gets the name of the series, if name is not set explicitly it is generated using index.
    /// By default returns Series plus one based index.
    ASPOSE_WORDS_SHARED_API System::String get_Name();
    /// Sets the name of the series, if name is not set explicitly it is generated using index.
    /// By default returns Series plus one based index.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Allows to specify whether the line connecting the points on the chart shall be smoothed using Catmull-Rom splines.
    ASPOSE_WORDS_SHARED_API bool get_Smooth() const;
    /// Allows to specify whether the line connecting the points on the chart shall be smoothed using Catmull-Rom splines.
    ASPOSE_WORDS_SHARED_API void set_Smooth(bool value);
    /// Gets a flag indicating whether data labels are displayed for the series.
    ASPOSE_WORDS_SHARED_API bool get_HasDataLabels() const;
    /// Sets a flag indicating whether data labels are displayed for the series.
    ASPOSE_WORDS_SHARED_API void set_HasDataLabels(bool value);
    /// Specifies the settings for the data labels for the entire series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataLabelCollection> get_DataLabels();
    /// Provides access to fill and line formatting of the series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartFormat> get_Format();
    /// Gets a legend entry for this chart series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntry> get_LegendEntry();
    /// Gets the type of this chart series.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartSeriesType get_SeriesType();
    /// Gets a collection of X values for this chart series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValueCollection> get_XValues();
    /// Gets a collection of Y values for this chart series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValueCollection> get_YValues();
    /// Gets a collection of bubble sizes for this chart series.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::BubbleSizeCollection> get_BubbleSizes();

    /// Adds the specified X value to the chart series. If the series supports Y values and bubble sizes, they will
    /// be empty for the X value.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue);
    /// Adds the specified X and Y values to the chart series.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>& yValue);
    /// Adds the specified X value, Y value and bubble size to the chart series.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>& yValue, double bubbleSize);
    /// Inserts the specified X value into the chart series at the specified index. If the series supports Y values
    /// and bubble sizes, they will be empty for the X value.
    ASPOSE_WORDS_SHARED_API void Insert(int32_t index, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue);
    /// Inserts the specified X and Y values into the chart series at the specified index.
    ASPOSE_WORDS_SHARED_API void Insert(int32_t index, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>& yValue);
    /// Inserts the specified X value, Y value and bubble size into the chart series at the specified index.
    ASPOSE_WORDS_SHARED_API void Insert(int32_t index, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>& xValue, const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>& yValue, double bubbleSize);
    /// Removes the X value, Y value, and bubble size, if supported, from the chart series at the specified index.
    /// The corresponding data point and data label are also removed.
    ASPOSE_WORDS_SHARED_API void Remove(int32_t index);
    /// Removes all data values from the chart series. Format of all individual data points and data labels is cleared.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Removes all data values from the chart series with preserving the format of the data points and data labels.
    ASPOSE_WORDS_SHARED_API void ClearValues();
    /// Copies default data point format from the data point with the specified index.
    ASPOSE_WORDS_SHARED_API void CopyFormatFrom(int32_t dataPointIndex);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartSeries();

private:

    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> get_Extensions() override;
    void set_Extensions(System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::SharedPtr<Aspose::Words::Drawing::Core::Dml::DmlExtension>>> ) override;

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    System::SharedPtr<System::Object> mField6;
    System::SharedPtr<System::Object> mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::SharedPtr<System::Object> mField11;
    System::SharedPtr<System::Object> mField12;
    System::SharedPtr<System::Object> mField13;
    System::SharedPtr<System::Object> mField14;
    System::SharedPtr<System::Object> mField15;
    System::SharedPtr<System::Object> mField16;
    System::SharedPtr<System::Object> mField17;
    System::SharedPtr<System::Object> mField18;
    System::SharedPtr<System::Object> mField19;
    System::SharedPtr<System::Object> mField20;
    System::SharedPtr<System::Object> mField21;
    System::SharedPtr<System::Object> mField22;
    System::SharedPtr<System::Object> mField23;
    __TypeStub<4,4,4,4>::type mField24;
    __TypeStub<1,1,1,1>::type mField25;
    System::SharedPtr<System::Object> mField26;
    System::String mField27;
    __TypeStub<4,4,4,4>::type mField28;
    __TypeStub<4,4,4,4>::type mField29;
    __TypeStub<4,4,4,4>::type mField30;
    System::SharedPtr<System::Object> mField31;
    System::SharedPtr<System::Object> mField32;
    System::SharedPtr<System::Object> mField33;
    __TypeStub<1,1,1,1>::type mField34;

};

}
}
}
}
