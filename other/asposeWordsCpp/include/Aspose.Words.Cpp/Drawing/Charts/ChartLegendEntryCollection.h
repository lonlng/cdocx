//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartLegendEntryCollection.h
#pragma once

#include <system/object.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <system/collections/icomparer.h>
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

class ChartLegendEntry;

}
}

}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents a collection of chart legend entries.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartLegendEntryCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntry>>
{
    typedef ChartLegendEntryCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntry>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of <see cref="Aspose::Words::Drawing::Charts::ChartLegendEntry">ChartLegendEntry</see> in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntry>>> GetEnumerator() override;

    /// Returns <see cref="Aspose::Words::Drawing::Charts::ChartLegendEntry">ChartLegendEntry</see> for the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartLegendEntry> idx_get(int32_t index);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartLegendEntryCollection();

private:

    System::SharedPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;

};

}
}
}
}
