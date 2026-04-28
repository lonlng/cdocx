//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartDataPointCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
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
class ChartDataPoint;

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
template <typename> class List;
}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents collection of a <see cref="Aspose::Words::Drawing::Charts::ChartDataPoint">ChartDataPoint</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartDataPointCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataPoint>>
{
    typedef ChartDataPointCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataPoint>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of <see cref="Aspose::Words::Drawing::Charts::ChartDataPoint">ChartDataPoint</see> in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns <see cref="Aspose::Words::Drawing::Charts::ChartDataPoint">ChartDataPoint</see> for the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataPoint> idx_get(int32_t index);

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartDataPoint>>> GetEnumerator() override;
    /// Clears format of all <see cref="Aspose::Words::Drawing::Charts::ChartDataPoint">ChartDataPoint</see> in this collection.
    ASPOSE_WORDS_SHARED_API void ClearFormat();
    /// Gets a flag indicating whether the data point at the specified index has default format.
    ASPOSE_WORDS_SHARED_API bool HasDefaultFormat(int32_t dataPointIndex);
    /// Copies format from the source data point to the destination data point.
    ASPOSE_WORDS_SHARED_API void CopyFormat(int32_t sourceIndex, int32_t destinationIndex);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartDataPointCollection();

private:

    System::WeakPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
}
