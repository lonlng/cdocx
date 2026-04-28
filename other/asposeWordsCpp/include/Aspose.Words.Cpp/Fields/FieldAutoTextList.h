//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldAutoTextList.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
enum class FieldSwitchType;
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

/// Implements the AUTOTEXTLIST field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldAutoTextList : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldAutoTextList ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the AutoText entry.
    ASPOSE_WORDS_SHARED_API System::String get_EntryName();
    /// Sets the name of the AutoText entry.
    ASPOSE_WORDS_SHARED_API void set_EntryName(const System::String& value);
    /// Gets the name of the style on which the list to contain entries is based.
    ASPOSE_WORDS_SHARED_API System::String get_ListStyle();
    /// Sets the name of the style on which the list to contain entries is based.
    ASPOSE_WORDS_SHARED_API void set_ListStyle(const System::String& value);
    /// Gets the text of the ScreenTip to show.
    ASPOSE_WORDS_SHARED_API System::String get_ScreenTip();
    /// Sets the text of the ScreenTip to show.
    ASPOSE_WORDS_SHARED_API void set_ScreenTip(const System::String& value);

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
