//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/BubbleSizeCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents a collection of bubble sizes for a chart series.
/// 
/// The collection allows only changing bubble sizes. To add or insert new values to a chart series, or remove
/// values, the appropriate methods of the <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> class can be used.
/// 
/// Empty bubble size values are represented as <see cref="System::Double::NaN">NaN</see>.
/// 
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Add(System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Add(System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Add(System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>, double)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Insert(int32_t, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Insert(int32_t, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Insert(int32_t, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartXValue>, System::SharedPtr<Aspose::Words::Drawing::Charts::ChartYValue>, double)
/// @sa Aspose::Words::Drawing::Charts::ChartSeries::Remove(int32_t)
class ASPOSE_WORDS_SHARED_CLASS BubbleSizeCollection : public System::Collections::Generic::IEnumerable<double>
{
    typedef BubbleSizeCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<double> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the number of items in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();
    /// Gets or sets the format code applied to the bubble sizes.
    /// 
    /// Number formatting is used to change the way values appears in the chart.
    /// The examples of number formats:
    /// 
    /// Number - "#,##0.00"
    /// 
    /// Currency - "\"\$\\"#,##0.00"
    /// 
    /// Time - "[$-x-systime]h:mm:ss AM/PM"
    /// 
    /// Date - "d/mm/yyyy"
    /// 
    /// Percentage - "0.00%"
    /// 
    /// Fraction - "# ?/?"
    /// 
    /// Scientific - "0.00E+00"
    /// 
    /// Accounting - "_-\"\$\\"* #,##0.00_-;-\"\$\\"* #,##0.00_-;_-\"\$\\"* \"-\\"??_-;_-@_-"
    /// 
    /// Custom with color - "[Red]-#,##0.0"
    ASPOSE_WORDS_SHARED_API System::String get_FormatCode();
    /// Setter for Aspose::Words::Drawing::Charts::BubbleSizeCollection::get_FormatCode
    ASPOSE_WORDS_SHARED_API void set_FormatCode(const System::String& value);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<double>> GetEnumerator() override;

    /// Gets or sets the bubble size value at the specified index.
    ASPOSE_WORDS_SHARED_API double idx_get(int32_t index);
    /// Gets or sets the bubble size value at the specified index.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, double value);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~BubbleSizeCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
}
