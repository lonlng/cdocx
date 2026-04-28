//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/AxisBound.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class DateTime;
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents minimum or maximum bound of axis values.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
/// 
/// Bound can be specified as a numeric, datetime or a special "auto" value.
/// 
/// The instances of this class are immutable.
/// 
/// @sa Aspose::Words::Drawing::Charts::AxisScaling::get_Minimum
/// @sa Aspose::Words::Drawing::Charts::AxisScaling::get_Maximum
class ASPOSE_WORDS_SHARED_CLASS AxisBound final : public System::Object
{
    typedef AxisBound ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a flag indicating that axis bound should be determined automatically.
    ASPOSE_WORDS_SHARED_API bool get_IsAuto() const;
    /// Returns numeric value of axis bound.
    ASPOSE_WORDS_SHARED_API double get_Value() const;
    /// Returns value of axis bound represented as datetime.
    ASPOSE_WORDS_SHARED_API System::DateTime get_ValueAsDate();

    /// Creates a new instance indicating that axis bound should be determined automatically by a word-processing
    /// application.
    ASPOSE_WORDS_SHARED_API AxisBound();
    /// Creates an axis bound represented as a number.
    ASPOSE_WORDS_SHARED_API AxisBound(double value);
    /// Creates an axis bound represented as datetime value.
    ASPOSE_WORDS_SHARED_API AxisBound(System::DateTime datetime);

    /// Determines whether the specified object is equal in value to the current object.
    ASPOSE_WORDS_SHARED_API bool Equals(System::SharedPtr<System::Object> obj) override;
    /// Serves as a hash function for this type.
    ASPOSE_WORDS_SHARED_API int32_t GetHashCode() const override;
    /// Returns a user-friendly string that displays the value of this object.
    ASPOSE_WORDS_SHARED_API System::String ToString() const override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~AxisBound();

private:

    __TypeStub<8,8,8,8>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;

};

}
}
}
}
