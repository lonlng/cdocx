//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldCreateDate.h
#pragma once

#include <Aspose.Words.Cpp/Fields/IFieldInfoResultProvider.h>
#include <Aspose.Words.Cpp/Fields/IFieldWithCalendar.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class Document;
namespace Fields
{
namespace Expressions
{
class Constant;

}

enum class FieldSwitchType;
class FieldUpdateAction;
class IFieldCode;
}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the CREATEDATE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldCreateDate : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IFieldWithCalendar
{
    typedef FieldCreateDate ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IFieldWithCalendar BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets whether to use the Hijri Lunar or Hebrew Lunar calendar.
    ASPOSE_WORDS_SHARED_API bool get_UseLunarCalendar() override;
    /// Sets whether to use the Hijri Lunar or Hebrew Lunar calendar.
    ASPOSE_WORDS_SHARED_API void set_UseLunarCalendar(bool value);
    /// Gets whether to use the Saka Era calendar.
    ASPOSE_WORDS_SHARED_API bool get_UseSakaEraCalendar() override;
    /// Sets whether to use the Saka Era calendar.
    ASPOSE_WORDS_SHARED_API void set_UseSakaEraCalendar(bool value);
    /// Gets whether to use the Um-al-Qura calendar.
    ASPOSE_WORDS_SHARED_API bool get_UseUmAlQuraCalendar() override;
    /// Sets whether to use the Um-al-Qura calendar.
    ASPOSE_WORDS_SHARED_API void set_UseUmAlQuraCalendar(bool value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldCreateDate();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
