//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/IFieldResultFormatter.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Fields/GeneralFormat.h>
#include <Aspose.Words.Cpp/CalendarType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class DateTime;
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// \interface IFieldResultFormatter
/// Implement this interface if you want to control how the field result is formatted.
class ASPOSE_WORDS_SHARED_CLASS IFieldResultFormatter : public virtual System::Object
{
    typedef IFieldResultFormatter ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Called when %Aspose.Words applies a numeric format switch, i.e. \\\# "#.##".
    virtual System::String FormatNumeric(double value, System::String format) = 0;
    /// Called when %Aspose.Words applies a date/time format switch, i.e. \\\@ "dd.MM.yyyy".
    virtual System::String FormatDateTime(System::DateTime value, System::String format, Aspose::Words::CalendarType calendarType) = 0;
    /// Called when %Aspose.Words applies a capitalization format switch, i.e. \\* Upper.
    virtual System::String Format(System::String value, Aspose::Words::Fields::GeneralFormat format) = 0;
    /// Called when %Aspose.Words applies a number format switch, i.e. \\* Ordinal.
    virtual System::String Format(double value, Aspose::Words::Fields::GeneralFormat format) = 0;

};

}
}
}
