//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartMultilevelValue.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents a value for charts that display multilevel data.
class ASPOSE_WORDS_SHARED_CLASS ChartMultilevelValue : public System::Object
{
    typedef ChartMultilevelValue ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the chart top level that this value refers to.
    ASPOSE_WORDS_SHARED_API System::String get_Level1() const;
    /// Gets the name of the chart intermediate level that this value refers to.
    ASPOSE_WORDS_SHARED_API System::String get_Level2() const;
    /// Gets the name of the chart bottom level that this value refers to.
    ASPOSE_WORDS_SHARED_API System::String get_Level3() const;

    /// Initializes a new instance of this class that represents a three-level value.
    ASPOSE_WORDS_SHARED_API ChartMultilevelValue(const System::String& level1, const System::String& level2, const System::String& level3);
    /// Initializes a new instance of this class that represents a two-level value.
    ASPOSE_WORDS_SHARED_API ChartMultilevelValue(const System::String& level1, const System::String& level2);
    /// Initializes a new instance of this class that represents a single-level value.
    ASPOSE_WORDS_SHARED_API ChartMultilevelValue(const System::String& level1);

    /// Gets a hash code for the current multilevel data object.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Gets a flag indicating whether the specified object is equal to the current multilevel data object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~ChartMultilevelValue();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;

};

}
}
}
}
