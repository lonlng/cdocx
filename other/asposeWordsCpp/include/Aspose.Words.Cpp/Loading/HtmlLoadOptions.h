//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Loading/HtmlLoadOptions.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Loading/LoadOptions.h>
#include <Aspose.Words.Cpp/Loading/HtmlControlType.h>
#include <Aspose.Words.Cpp/Loading/BlockImportMode.h>
#include <Aspose.Words.Cpp/LoadFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Loading {

/// Allows to specify additional options when loading HTML document into a <see cref="Aspose::Words::Document">Document</see> object.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-load-options/">Specify Load Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS HtmlLoadOptions : public Aspose::Words::Loading::LoadOptions
{
    typedef HtmlLoadOptions ThisType;
    typedef Aspose::Words::Loading::LoadOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a value indicating whether to support VML images.
    ASPOSE_WORDS_SHARED_API bool get_SupportVml() const;
    /// Sets a value indicating whether to support VML images.
    ASPOSE_WORDS_SHARED_API void set_SupportVml(bool value);
    /// The number of milliseconds to wait before the web request times out. The default value is 100000 milliseconds
    /// (100 seconds).
    ASPOSE_WORDS_SHARED_API int32_t get_WebRequestTimeout() const;
    /// The number of milliseconds to wait before the web request times out. The default value is 100000 milliseconds
    /// (100 seconds).
    ASPOSE_WORDS_SHARED_API void set_WebRequestTimeout(int32_t value);
    /// Gets preferred type of document nodes that will represent imported \<input\> and \<select\> elements.
    /// Default value is <see cref="Aspose::Words::Loading::HtmlControlType::FormField">FormField</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::HtmlControlType get_PreferredControlType() const;
    /// Sets preferred type of document nodes that will represent imported \<input\> and \<select\> elements.
    /// Default value is <see cref="Aspose::Words::Loading::HtmlControlType::FormField">FormField</see>.
    ASPOSE_WORDS_SHARED_API void set_PreferredControlType(Aspose::Words::Loading::HtmlControlType value);
    /// Gets a value indicating whether to ignore \<noscript\> HTML elements.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_IgnoreNoscriptElements() const;
    /// Sets a value indicating whether to ignore \<noscript\> HTML elements.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_IgnoreNoscriptElements(bool value);
    /// Gets or sets a value indicating whether to convert loaded SVG images to the EMF format.
    /// Default value is <c>%false</c> and, if possible, loaded SVG images are stored as is without conversion.
    /// 
    /// Newer versions of MS Word support SVG images natively. If the MS Word version specified in load options supports
    /// SVG, %Aspose.Words will store SVG images as is without conversion. If SVG is not supported, loaded SVG images will be
    /// converted to the EMF format.
    /// 
    /// If, however, this option is set to <c>%true</c>, %Aspose.Words will convert loaded SVG images to EMF even if SVG
    /// images are supported by the specified version of MS Word.
    ASPOSE_WORDS_SHARED_API bool get_ConvertSvgToEmf() const;
    /// Setter for Aspose::Words::Loading::HtmlLoadOptions::get_ConvertSvgToEmf
    ASPOSE_WORDS_SHARED_API void set_ConvertSvgToEmf(bool value);
    /// Gets a value that specifies how properties of block-level elements are imported.
    /// Default value is <see cref="Aspose::Words::Loading::BlockImportMode::Merge">Merge</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Loading::BlockImportMode get_BlockImportMode() const;
    /// Sets a value that specifies how properties of block-level elements are imported.
    /// Default value is <see cref="Aspose::Words::Loading::BlockImportMode::Merge">Merge</see>.
    ASPOSE_WORDS_SHARED_API void set_BlockImportMode(Aspose::Words::Loading::BlockImportMode value);
    /// Gets or sets a value indicating whether to support \@font-face rules and whether to load declared fonts.
    /// Default value is <c>%false</c>.
    /// 
    /// If this option is enabled, fonts declared in \@font-face rules are loaded and embedded into the resulting document's
    /// font definitions (see <see cref="Aspose::Words::DocumentBase::get_FontInfos">FontInfos</see>). This makes the loaded fonts available for rendering but
    /// doesn't automatically enable embedding of the fonts upon saving. In order to save the document with loaded fonts,
    /// the <see cref="Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts">EmbedTrueTypeFonts</see> property of the <see cref="Aspose::Words::DocumentBase::get_FontInfos">FontInfos</see>
    /// collection should be set to <c>%true</c>.
    /// 
    /// Supported font formats are TTF, EOT, and WOFF.
    /// 
    /// \@font-face rules are not supported when loading SVG images.
    ASPOSE_WORDS_SHARED_API bool get_SupportFontFaceRules() const;
    /// Setter for Aspose::Words::Loading::HtmlLoadOptions::get_SupportFontFaceRules
    ASPOSE_WORDS_SHARED_API void set_SupportFontFaceRules(bool value);

    /// Initializes a new instance of this class with default values.
    ASPOSE_WORDS_SHARED_API HtmlLoadOptions();
    /// A shortcut to initialize a new instance of this class with the specified password to load an encrypted document.
    /// 
    /// @param password The password to open an encrypted document. Can be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API HtmlLoadOptions(const System::String& password);
    /// A shortcut to initialize a new instance of this class with properties set to the specified values.
    /// 
    /// @param loadFormat The format of the document to be loaded.
    /// @param password The password to open an encrypted document. Can be <c>%null</c> or empty string.
    /// @param baseUri The string that will be used to resolve relative URIs to absolute. Can be <c>%null</c> or empty string.
    ASPOSE_WORDS_SHARED_API HtmlLoadOptions(Aspose::Words::LoadFormat loadFormat, const System::String& password, const System::String& baseUri);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Loading::LoadOptions> Clone() override;

    virtual ASPOSE_WORDS_SHARED_API ~HtmlLoadOptions();

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;

};

}
}
}
