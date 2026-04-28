//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PclSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Pcl">Pcl</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PclSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef PclSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Pcl">Pcl</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Pcl">Pcl</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets a value determining whether or not complex transformed elements
    /// should be rasterized before saving to PCL document.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_RasterizeTransformedElements() const;
    /// Sets a value determining whether or not complex transformed elements
    /// should be rasterized before saving to PCL document.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_RasterizeTransformedElements(bool value);
    /// Name of the font that will be used
    /// if no expected font is found in printer and built-in fonts collections.
    ASPOSE_WORDS_SHARED_API System::String get_FallbackFontName() const;
    /// Name of the font that will be used
    /// if no expected font is found in printer and built-in fonts collections.
    ASPOSE_WORDS_SHARED_API void set_FallbackFontName(const System::String& value);

    /// Adds information about font that is uploaded to the printer by manufacturer.
    /// 
    /// @param fontFullName Full name of the font (e.g. "Times New Roman Bold Italic").
    /// @param fontPclName Name of the font that is used in Pcl document.
    ASPOSE_WORDS_SHARED_API void AddPrinterFont(const System::String& fontFullName, const System::String& fontPclName);

    ASPOSE_WORDS_SHARED_API PclSaveOptions();

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;

};

}
}
}
