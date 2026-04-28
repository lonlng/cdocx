//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/MergeFieldImageDimension.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Fields/MergeFieldImageDimensionUnit.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Represents an image dimension (i.e. the width or the height) used across a mail merge process.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// @sa Aspose::Words::Fields::MergeFieldImageDimensionUnit
class ASPOSE_WORDS_SHARED_CLASS MergeFieldImageDimension : public System::Object
{
    typedef MergeFieldImageDimension ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// The value.
    ASPOSE_WORDS_SHARED_API double get_Value() const;
    /// The value.
    ASPOSE_WORDS_SHARED_API void set_Value(double value);
    /// The unit.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::MergeFieldImageDimensionUnit get_Unit() const;
    /// The unit.
    ASPOSE_WORDS_SHARED_API void set_Unit(Aspose::Words::Fields::MergeFieldImageDimensionUnit value);

    /// Creates an image dimension instance with the given value in points.
    /// 
    /// @param value The value.
    ASPOSE_WORDS_SHARED_API MergeFieldImageDimension(double value);
    /// Creates an image dimension instance with the given value and the given unit.
    /// 
    /// @param value The value.
    /// @param unit The unit.
    ASPOSE_WORDS_SHARED_API MergeFieldImageDimension(double value, Aspose::Words::Fields::MergeFieldImageDimensionUnit unit);

protected:

    MergeFieldImageDimension();

private:

    __TypeStub<8,8,8,8>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;

};

}
}
}
