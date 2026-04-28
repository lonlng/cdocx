//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldGreetingLine.h
#pragma once

#include <system/array.h>
#include <mutex>
#include <memory>

#include <Aspose.Words.Cpp/Fields/IFormattableMergeField.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Collections
{
template <typename> class StringToObjDictionary;
}
namespace Words
{
class Document;
namespace Fields
{
enum class FieldSwitchType;
class FieldUpdateAction;
class IMergeFormatContext;
class MergeFormatPlaceholder;
}
}
}
namespace System
{
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the GREETINGLINE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldGreetingLine : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IFormattableMergeField
{
    typedef FieldGreetingLine ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IFormattableMergeField BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text to include in the field if the name is blank.
    ASPOSE_WORDS_SHARED_API System::String get_AlternateText();
    /// Sets the text to include in the field if the name is blank.
    ASPOSE_WORDS_SHARED_API void set_AlternateText(const System::String& value);
    /// Gets the format of the name included in the field.
    ASPOSE_WORDS_SHARED_API System::String get_NameFormat();
    /// Sets the format of the name included in the field.
    ASPOSE_WORDS_SHARED_API void set_NameFormat(const System::String& value);
    /// Gets the language id used to format the name.
    ASPOSE_WORDS_SHARED_API System::String get_LanguageId();
    /// Sets the language id used to format the name.
    ASPOSE_WORDS_SHARED_API void set_LanguageId(const System::String& value);

    /// Returns a collection of mail merge field names used by the field.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<System::String> GetFieldNames() override;

    ASPOSE_WORDS_SHARED_API FieldGreetingLine();

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldGreetingLine();

private:

    System::String get_MergeFormat() override;
    System::SharedPtr<Aspose::Collections::StringToObjDictionary<System::String>> get_PlaceholdersToFieldsMap() override;

    System::String mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;
    System::SharedPtr<Aspose::Words::Document> IFormattableMergeField_FetchDocument() override;
    System::String GetPlaceholderValue(System::SharedPtr<Aspose::Words::Fields::IMergeFormatContext> , System::SharedPtr<Aspose::Words::Fields::MergeFormatPlaceholder> ) override;

};

}
}
}
