//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/LanguagePreferences.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/Loading/EditingLanguage.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to set up language preferences.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS LanguagePreferences : public System::Object
{
    typedef LanguagePreferences ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets default editing language.
    /// The default value is <see cref="Aspose::Words::Loading::EditingLanguage::EnglishUS">EnglishUS</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::EditingLanguage get_DefaultEditingLanguage() const;
    /// Sets default editing language.
    /// The default value is <see cref="Aspose::Words::Loading::EditingLanguage::EnglishUS">EnglishUS</see>.
    ASPOSE_WORDS_SHARED_API void set_DefaultEditingLanguage(Aspose::Words::Loading::EditingLanguage value);

    /// Adds additional editing language.
    ASPOSE_WORDS_SHARED_API void AddEditingLanguage(Aspose::Words::Loading::EditingLanguage language);
    /// Adds additional editing languages.
    ASPOSE_WORDS_SHARED_API void AddEditingLanguages(const System::ArrayPtr<Aspose::Words::Loading::EditingLanguage>& languages);

    ASPOSE_WORDS_SHARED_API LanguagePreferences();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;

};

}
}
}
