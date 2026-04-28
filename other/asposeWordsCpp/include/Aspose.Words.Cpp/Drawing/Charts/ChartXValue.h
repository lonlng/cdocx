//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartXValue.h
#pragma once

#include <system/timespan.h>
#include <system/string.h>
#include <system/date_time.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Charts/ChartXValueType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Drawing
{
namespace Charts
{
class ChartMultilevelValue;
}
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents an X value for a chart series.
/// 
/// This class contains a number of static methods for creating an X value of a particular type. The
/// <see cref="Aspose::Words::Drawing::Charts::ChartXValue::get_ValueType">ValueType</see> property allows you to determine the type of an existing X value.
/// 
/// All non-null X values of a chart series must be of the same <see cref="Aspose::Words::Drawing::Charts::ChartXValueType">ChartXValueType</see> type.
class ASPOSE_WORDS_SHARED_CLASS ChartXValue : public System::Object
{
    typedef ChartXValue ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the type of the X value stored in the object.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Charts::ChartXValueType get_ValueType() const;
    /// Gets the stored string value.
    ASPOSE_WORDS_SHARED_API System::String get_StringValue() const;
    /// Gets the stored numeric value.
    ASPOSE_WORDS_SHARED_API double get_DoubleValue() const;
    /// Gets the stored datetime value.
    ASPOSE_WORDS_SHARED_API System::DateTime get_DateTimeValue() const;
    /// Gets the stored time value.
    ASPOSE_WORDS_SHARED_API System::TimeSpan get_TimeValue() const;
    /// Gets the stored multilevel value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMultilevelValue> get_MultilevelValue() const;

    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartXValue">ChartXValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartXValueType::String">String</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue> FromString(const System::String& value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartXValue">ChartXValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartXValueType::Double">Double</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue> FromDouble(double value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartXValue">ChartXValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartXValueType::DateTime">DateTime</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue> FromDateTime(System::DateTime value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartXValue">ChartXValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartXValueType::Time">Time</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue> FromTimeSpan(System::TimeSpan value);
    /// Creates a <see cref="Aspose::Words::Drawing::Charts::ChartXValue">ChartXValue</see> instance of the <see cref="Aspose::Words::Drawing::Charts::ChartXValueType::Multilevel">Multilevel</see> type.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue> FromMultilevelValue(const System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMultilevelValue>& value);
    /// Gets a hash code for the current X value object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Gets a flag indicating whether the specified object is equal to the current X value object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartXValue();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    __TypeStub<8,8,8,8>::type mField2;
    System::DateTime mField3;
    System::TimeSpan mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
}
