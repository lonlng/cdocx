//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/AdjustmentCollection.h
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
class Adjustment;

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

/// Represents a read-only collection of <see cref="Aspose::Words::Drawing::Adjustment">Adjustment</see> adjust values that are applied to the specified shape.
class ASPOSE_WORDS_SHARED_CLASS AdjustmentCollection : public System::Object
{
    typedef AdjustmentCollection ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns an adjustment at the specified index.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::Adjustment> idx_get(int32_t index);

protected:

    AdjustmentCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
