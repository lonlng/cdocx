//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PsSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Ps">Ps</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PsSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef PsSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Ps">Ps</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Ps">Ps</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets or sets a boolean value indicating whether the document should be saved using a booklet printing layout,
    /// if it is specified via <see cref="Aspose::Words::PageSetup::get_MultiplePages">MultiplePages</see>.
    /// 
    /// If this option is specified, <see cref="Aspose::Words::Saving::FixedPageSaveOptions::get_PageSet">PageSet</see> is ignored when saving.
    /// This behavior matches MS Word.
    /// If book fold printing settings are not specified in page setup, this option will have no effect.
    ASPOSE_WORDS_SHARED_API bool get_UseBookFoldPrintingSettings() const;
    /// Setter for Aspose::Words::Saving::PsSaveOptions::get_UseBookFoldPrintingSettings
    ASPOSE_WORDS_SHARED_API void set_UseBookFoldPrintingSettings(bool value);

    ASPOSE_WORDS_SHARED_API PsSaveOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;

};

}
}
}
