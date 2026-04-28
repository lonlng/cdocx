//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartSeriesCollection.h
#pragma once

#include <system/collections/ienumerable.h>
#include <system/array.h>
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

class ChartMultilevelValue;
class ChartSeries;

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
template <typename> class IEnumerator;
template <typename> class IList;
}
}
class DateTime;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents collection of a <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartSeriesCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries>>
{
    typedef ChartSeriesCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the number of <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns a <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> at the specified index.
    /// 
    /// The index is zero-based.
    /// 
    /// Negative indexes are allowed and indicate access from the back of the collection.
    /// For example -1 means the last item, -2 means the second before last and so on.
    /// 
    /// If index is greater than or equal to the number of items in the list, this returns a null reference.
    /// 
    /// If index is negative and its absolute value is greater than the number of items in the list, this returns a null reference.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries>>> GetEnumerator() override;
    /// Removes a <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> at the specified index.
    /// 
    /// @param index The zero-based index of the <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to remove.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> from this collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series to any type of Bar, Column, Line and Surface charts.
    /// 
    /// @return Recently added <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<System::String>& categories, const System::ArrayPtr<double>& values);
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series to any type of Scatter charts.
    /// 
    /// @return Recently added <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<double>& xValues, const System::ArrayPtr<double>& yValues);
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series to any type of Area, Radar and Stock charts.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<System::DateTime>& dates, const System::ArrayPtr<double>& values);
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series to any type of Bubble charts.
    /// 
    /// @return Recently added <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<double>& xValues, const System::ArrayPtr<double>& yValues, const System::ArrayPtr<double>& bubbleSizes);
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series that have multi-level data categories.
    /// 
    /// @return Recently added <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartMultilevelValue>>& categories, const System::ArrayPtr<double>& values);
    /// Adds new <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> to this collection.
    /// Use this method to add series to Histogram charts.
    /// 
    /// @return Recently added <see cref="Aspose::Words::Drawing::Charts::ChartSeries">ChartSeries</see> object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<double>& xValues);
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartSeries> Add(const System::String& seriesName, const System::ArrayPtr<System::String>& categories, const System::ArrayPtr<double>& values, const System::ArrayPtr<bool>& isSubtotal);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartSeriesCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
}
