//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/RtfSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Rtf">Rtf</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS RtfSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef RtfSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Rtf">Rtf</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Rtf">Rtf</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Allows to make output RTF documents smaller in size, but if they contain
    /// RTL (right-to-left) text, it will not be displayed correctly.
    /// Default value is <c>%false</c>.
    /// 
    /// If the document that you want to convert to RTF using %Aspose.Words does not contain
    /// right-to-left text in languages like Arabic, then you can set this option to <c>%true</c>
    /// to reduce the size of the resulting RTF.
    ASPOSE_WORDS_SHARED_API bool get_ExportCompactSize() const;
    /// Setter for Aspose::Words::Saving::RtfSaveOptions::get_ExportCompactSize
    ASPOSE_WORDS_SHARED_API void set_ExportCompactSize(bool value);
    /// Specifies whether the keywords for "old readers" are written to RTF or not.
    /// This can significantly affect the size of the RTF document.
    /// Default value is <c>%true</c>.
    /// 
    /// "Old readers" are pre-Microsoft Word 97 applications and also WordPad.
    /// When this option is <c>%true</c> %Aspose.Words writes additional RTF keywords.
    /// These keywords allow the document to be displayed correctly when opened in an
    /// "old reader" application, but can significantly increase the size of the document.
    /// 
    /// If you set this option to <c>%false</c>, then only images in WMF, EMF and BMP formats
    /// will be displayed in "old readers".
    ASPOSE_WORDS_SHARED_API bool get_ExportImagesForOldReaders() const;
    /// Setter for Aspose::Words::Saving::RtfSaveOptions::get_ExportImagesForOldReaders
    ASPOSE_WORDS_SHARED_API void set_ExportImagesForOldReaders(bool value);
    /// When <c>%true</c> all images will be saved as WMF.
    ASPOSE_WORDS_SHARED_API bool get_SaveImagesAsWmf() const;
    /// When <c>%true</c> all images will be saved as WMF.
    ASPOSE_WORDS_SHARED_API void set_SaveImagesAsWmf(bool value);

    ASPOSE_WORDS_SHARED_API RtfSaveOptions();

protected:

    ASPOSE_WORDS_SHARED_API void SetTestMode() override;

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;

};

}
}
}
