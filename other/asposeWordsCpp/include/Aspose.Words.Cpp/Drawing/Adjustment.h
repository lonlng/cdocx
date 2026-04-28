//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Adjustment.h
#pragma once

#include <system/string.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Represents adjustment values that are applied to the specified shape.
class ASPOSE_WORDS_SHARED_CLASS Adjustment : public System::Object
{
    typedef Adjustment ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the adjustment.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Gets the raw value of the adjustment.
    ASPOSE_WORDS_SHARED_API int32_t get_Value() const;
    /// Sets the raw value of the adjustment.
    ASPOSE_WORDS_SHARED_API void set_Value(int32_t value);

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
