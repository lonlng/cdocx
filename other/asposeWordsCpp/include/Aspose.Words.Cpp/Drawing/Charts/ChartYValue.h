//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartYValue.h
#pragma once

#include <system/timespan.h>
#include <system/object.h>
#include <system/date_time.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Charts/ChartYValueType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents an Y value for a chart series.
/// 
/// This class contains a number of static methods for creating an Y value of a particular type. The
/// <see cref="Aspose::Words::Drawing::Charts::ChartYValue::get_ValueType">ValueType</see> property allows you to determine the type of an existing Y value.
/// 
/// All non-null Y values of a chart series must be of the same <see cref="Aspose::Words::Drawing::Charts::ChartYValueType">ChartYValueType</see> type.
class ASPOSE_WORDS_SHARED_CLASS ChartYValue : public System::Object
{
    typedef ChartYValue ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the type of the Y value stored in the object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartYValueType get_ValueType() const;
    /// Gets the stored numeric value.
    ASPOSE_WORDS_SHARED_API double get_DoubleValue() const;
    /// Gets the stored datetime value.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTimeValue() const;
    /// Gets the stored time value.
    ASPOSE_WORDS_SHARED_API System::TimeSpan get_TimeValue() const;

    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartYValue">ChartYValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartYValueType::Double">Double</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue> FromDouble(double value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartYValue">ChartYValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartYValueType::DateTime">DateTime</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue> FromDateTime(System::DateTime value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartYValue">ChartYValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartYValueType::Time">Time</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue> FromTimeSpan(System::TimeSpan value);
    /// Gets a hash code for the current Y value object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Gets a flag indicating whether the specified object is equal to the current Y value object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartYValue();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<8,8,8,8>::type mField1;
    System::DateTime mField2;
    System::TimeSpan mField3;

};

}
}
}
}
