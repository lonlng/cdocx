//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartAxisCollection.h
#pragma once

#include <system/shared_ptr.h>
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

class ChartAxis;

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

}
}
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents a collection of chart axes.
class ASPOSE_WORDS_SHARED_CLASS ChartAxisCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis>>
{
    typedef ChartAxisCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of axes in this collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis>>> GetEnumerator() override;

    /// Gets the axis at the specified index.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Charts::ChartAxis> idx_get(int32_t index);

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartAxisCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
}
