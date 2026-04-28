//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/ChartNumberFormat.h
#pragma once

#include <system/object.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Represents number formatting of the parent element.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-charts/">Working with Charts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ChartNumberFormat : public System::Object
{
    typedef ChartNumberFormat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets or sets the format code applied to a data label.
    /// 
    /// Number formatting is used to change the way a value appears in data label and can be used in some very creative ways.
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
    /// Text - "@"
    /// 
    /// Accounting - "_-\"\$\\"* #,##0.00_-;-\"\$\\"* #,##0.00_-;_-\"\$\\"* \"-\\"??_-;_-@_-"
    /// 
    /// Custom with color - "[Red]-#,##0.0"
    ASPOSE_WORDS_SHARED_API System::String get_FormatCode();
    /// Setter for Aspose::Words::Drawing::Charts::ChartNumberFormat::get_FormatCode
    ASPOSE_WORDS_SHARED_API void set_FormatCode(const System::String& value);
    /// Specifies whether the format code is linked to a source cell.
    /// Default is true.
    ASPOSE_WORDS_SHARED_API bool get_IsLinkedToSource();
    /// Specifies whether the format code is linked to a source cell.
    /// Default is true.
    ASPOSE_WORDS_SHARED_API void set_IsLinkedToSource(bool value);

protected:

private:

    System::WeakPtr<System::Object> mField0;
    System::WeakPtr<System::Object> mField1;

};

}
}
}
}
