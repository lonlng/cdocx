//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/IChartDataPoint.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Charts
{
class ChartMarker;
}
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// \interface IChartDataPoint
/// Contains properties of a single data point on the chart.
class ASPOSE_WORDS_SHARED_CLASS IChartDataPoint : public virtual System::Object
{
    typedef IChartDataPoint ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    virtual int32_t get_Explosion() = 0;
    /// Specifies the amount the data point shall be moved from the center of the pie.
    /// Can be negative, negative means that property is not set and no explosion should be applied.
    /// Applies only to Pie charts.
    virtual void set_Explosion(int32_t value) = 0;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    virtual bool get_InvertIfNegative() = 0;
    /// Specifies whether the parent element shall inverts its colors if the value is negative.
    virtual void set_InvertIfNegative(bool value) = 0;
    /// Specifies a data marker. Marker is automatically created when requested.
    virtual System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMarker> get_Marker() = 0;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    virtual bool get_Bubble3D() = 0;
    /// Specifies whether the bubbles in Bubble chart should have a 3-D effect applied to them.
    virtual void set_Bubble3D(bool value) = 0;

};

}
}
}
}
