//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlFixedSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/HtmlFixedPageHorizontalAlignment.h>
#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/Saving/ExportFontFormat.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Saving
{
class IResourceSavingCallback;
}
}
}
namespace System
{
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::HtmlFixed">HtmlFixed</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS HtmlFixedSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef HtmlFixedSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::HtmlFixed">HtmlFixed</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::HtmlFixed">HtmlFixed</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies whether border around pages should be shown.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowPageBorder() const;
    /// Specifies whether border around pages should be shown.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowPageBorder(bool value);
    /// Specifies the horizontal alignment of pages in an HTML document.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment get_PageHorizontalAlignment() const;
    /// Specifies the horizontal alignment of pages in an HTML document.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API void set_PageHorizontalAlignment(Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment value);
    /// Specifies the margins around pages in an HTML document.
    /// The margins value is measured in points and should be equal to or greater than 0.
    /// Default value is 10 points.
    /// 
    /// Depends on the value of <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_PageHorizontalAlignment">PageHorizontalAlignment</see> property:
    /// 
    /// - Defines top, bottom and left page margins if the value is <see cref="Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment::Left">Left</see>.
    /// - Defines top, bottom and right page margins if the value is <see cref="Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment::Right">Right</see>.
    /// - Defines top and bottom page margins if the value is <see cref="Aspose::Words::Saving::HtmlFixedPageHorizontalAlignment::Center">Center</see>.
    ASPOSE_WORDS_SHARED_API double get_PageMargins() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_PageMargins
    ASPOSE_WORDS_SHARED_API void set_PageMargins(double value);
    /// Specifies the physical folder where resources (images, fonts, css) are saved when exporting a document to Html format.
    /// Default is <c>%null</c>.
    /// 
    /// Has effect only if <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ExportEmbeddedImages">ExportEmbeddedImages</see> property is <c>%false</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in Html format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// images in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the images,
    /// but still needs to save the images somewhere. In this case, you need to specify an accessible folder
    /// by using the <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see> property
    /// 
    /// @sa Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolder() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into an Html document.
    /// Default is <c>%null</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in Html format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// @sa Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolderAlias(const System::String& value);
    /// Specifies whether images should be embedded into Html document in Base64 format.
    /// Note setting this flag can significantly increase size of output Html file.
    ASPOSE_WORDS_SHARED_API bool get_ExportEmbeddedImages() const;
    /// Specifies whether images should be embedded into Html document in Base64 format.
    /// Note setting this flag can significantly increase size of output Html file.
    ASPOSE_WORDS_SHARED_API void set_ExportEmbeddedImages(bool value);
    /// Specifies whether fonts should be embedded into Html document in Base64 format.
    /// Note setting this flag can significantly increase size of output Html file.
    ASPOSE_WORDS_SHARED_API bool get_ExportEmbeddedFonts() const;
    /// Specifies whether fonts should be embedded into Html document in Base64 format.
    /// Note setting this flag can significantly increase size of output Html file.
    ASPOSE_WORDS_SHARED_API void set_ExportEmbeddedFonts(bool value);
    /// Specifies whether the CSS (Cascading Style Sheet) should be embedded into Html document.
    ASPOSE_WORDS_SHARED_API bool get_ExportEmbeddedCss() const;
    /// Specifies whether the CSS (Cascading Style Sheet) should be embedded into Html document.
    ASPOSE_WORDS_SHARED_API void set_ExportEmbeddedCss(bool value);
    /// Specifies whether SVG resources should be embedded into Html document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportEmbeddedSvg() const;
    /// Specifies whether SVG resources should be embedded into Html document.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportEmbeddedSvg(bool value);
    /// Gets <see cref="Aspose::Words::Saving::ExportFontFormat">ExportFontFormat</see> used for font exporting.
    /// Default value is <see cref="Aspose::Words::Saving::ExportFontFormat::Woff">Woff</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ExportFontFormat get_FontFormat() const;
    /// Sets <see cref="Aspose::Words::Saving::ExportFontFormat">ExportFontFormat</see> used for font exporting.
    /// Default value is <see cref="Aspose::Words::Saving::ExportFontFormat::Woff">Woff</see>.
    ASPOSE_WORDS_SHARED_API void set_FontFormat(Aspose::Words::Saving::ExportFontFormat value);
    /// Specifies prefix which is added to all class names in style.css file.
    /// Default value is <c>%"aw"</c>.
    ASPOSE_WORDS_SHARED_API System::String get_CssClassNamesPrefix() const;
    /// Specifies prefix which is added to all class names in style.css file.
    /// Default value is <c>%"aw"</c>.
    ASPOSE_WORDS_SHARED_API void set_CssClassNamesPrefix(const System::String& value);
    /// Allows to control how resources (images, fonts and css) are saved when a document is exported to fixed page Html format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback> get_ResourceSavingCallback() const;
    /// Allows to control how resources (images, fonts and css) are saved when a document is exported to fixed page Html format.
    ASPOSE_WORDS_SHARED_API void set_ResourceSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback>& value);
    /// Specifies the encoding to use when exporting to HTML.
    /// Default value is <c>%new UTF8Encoding(true)</c> (UTF-8 with BOM).
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::Encoding> get_Encoding() const;
    /// Specifies the encoding to use when exporting to HTML.
    /// Default value is <c>%new UTF8Encoding(true)</c> (UTF-8 with BOM).
    ASPOSE_WORDS_SHARED_API void set_Encoding(const System::SharedPtr<System::Text::Encoding>& value);
    /// Gets indication of whether form fields are exported as interactive
    /// items (as 'input' tag) rather than converted to text or graphics.
    ASPOSE_WORDS_SHARED_API bool get_ExportFormFields() const;
    /// Sets indication of whether form fields are exported as interactive
    /// items (as 'input' tag) rather than converted to text or graphics.
    ASPOSE_WORDS_SHARED_API void set_ExportFormFields(bool value);
    /// Flag indicates whether it is required to optimize output.
    /// If this flag is set redundant nested canvases and empty canvases are removed,
    /// also neighbor glyphs with the same formating are concatenated.
    /// Note: The accuracy of the content display may be affected if this property is set to <c>%true</c>.
    /// Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_OptimizeOutput() override;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_OptimizeOutput
    ASPOSE_WORDS_SHARED_API void set_OptimizeOutput(bool value) override;
    /// Flag indicates whether fonts from target machine must be used to display the document.
    /// If this flag is set to <c>%true</c>, <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_FontFormat">FontFormat</see> and <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ExportEmbeddedFonts">ExportEmbeddedFonts</see> properties do not have effect,
    /// also <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourceSavingCallback">ResourceSavingCallback</see> is not fired for fonts.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_UseTargetMachineFonts() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_UseTargetMachineFonts
    ASPOSE_WORDS_SHARED_API void set_UseTargetMachineFonts(bool value);
    /// Flag indicates whether "@font-face" CSS rules should be placed into a separate file "fontFaces.css"
    /// when a document is being saved with external stylesheet (that is, when <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ExportEmbeddedCss">ExportEmbeddedCss</see>
    /// is <c>%false</c>).
    /// Default value is <c>%false</c>, all CSS rules are written into single file "styles.css".
    ASPOSE_WORDS_SHARED_API bool get_SaveFontFaceCssSeparately() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_SaveFontFaceCssSeparately
    ASPOSE_WORDS_SHARED_API void set_SaveFontFaceCssSeparately(bool value);
    /// Specifies a prefix that is prepended to all generated element IDs in the output document.
    /// Default value is null and no prefix is prepended.
    /// 
    /// @exception System::ArgumentException The value does not meet the requirements specified above.
    ASPOSE_WORDS_SHARED_API System::String get_IdPrefix() const;
    /// Setter for Aspose::Words::Saving::HtmlFixedSaveOptions::get_IdPrefix
    ASPOSE_WORDS_SHARED_API void set_IdPrefix(const System::String& value);
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_RemoveJavaScriptFromLinks() const;
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_RemoveJavaScriptFromLinks(bool value);

    ASPOSE_WORDS_SHARED_API HtmlFixedSaveOptions();

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsShapingSupported() override;

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<8,8,8,8>::type mField4;
    System::String mField5;
    System::String mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<1,1,1,1>::type mField10;
    __TypeStub<4,4,4,4>::type mField11;
    System::String mField12;
    __TypeStub<1,1,1,1>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    System::SharedPtr<System::Object> mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    System::String mField18;

};

}
}
}
