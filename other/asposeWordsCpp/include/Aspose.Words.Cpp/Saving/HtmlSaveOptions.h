//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/HtmlSaveOptions.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/Saving/HtmlVersion.h>
#include <Aspose.Words.Cpp/Saving/HtmlOfficeMathOutputMode.h>
#include <Aspose.Words.Cpp/Saving/HtmlMetafileFormat.h>
#include <Aspose.Words.Cpp/Saving/HtmlElementSizeOutputMode.h>
#include <Aspose.Words.Cpp/Saving/ExportListLabels.h>
#include <Aspose.Words.Cpp/Saving/ExportHeadersFootersMode.h>
#include <Aspose.Words.Cpp/Saving/DocumentSplitCriteria.h>
#include <Aspose.Words.Cpp/Saving/CssStyleSheetType.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{
class ICssSavingCallback;
class IDocumentPartSavingCallback;
class IFontSavingCallback;
class IImageSavingCallback;

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

/// Can be used to specify additional options when saving a document into the
/// <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
/// <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS HtmlSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef HtmlSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
    /// <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can be <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
    /// <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies whether negative left and right indents of paragraphs are normalized
    /// when saving to HTML, MHTML or EPUB. Default value is <c>%false</c>.
    /// 
    /// When negative indent is not allowed, it is exported as zero margin to HTML.
    /// When negative indent is allowed, a paragraph might appear partially outside of the
    /// browser window.
    ASPOSE_WORDS_SHARED_API bool get_AllowNegativeIndent() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_AllowNegativeIndent
    ASPOSE_WORDS_SHARED_API void set_AllowNegativeIndent(bool value);
    /// Specifies the path and the name of the Cascading Style Sheet (CSS) file written when a document
    /// is exported to HTML.
    /// Default is an empty string.
    /// 
    /// This property has effect only when saving a document to HTML format
    /// and external CSS style sheet is requested using <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetType">CssStyleSheetType</see>.
    /// 
    /// If this property is empty, the CSS file will be saved into the same folder and with the same name as the HTML
    /// document but with the ".css" extension.
    /// 
    /// If only path but no file name is specified in this property, the CSS file will be saved into the specified
    /// folder and will have the same name as the HTML document but with the ".css" extension.
    /// 
    /// If the folder specified by this property doesn't exist, it will be created automatically before the CSS file
    /// is saved.
    /// 
    /// Another way to specify a folder where external CSS file is saved is to use <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see>.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetType
    ASPOSE_WORDS_SHARED_API System::String get_CssStyleSheetFileName() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetFileName
    ASPOSE_WORDS_SHARED_API void set_CssStyleSheetFileName(const System::String& value);
    /// Specifies how CSS (Cascading Style Sheet) styles are exported to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::CssStyleSheetType::Inline">Inline</see> for HTML/MHTML and
    /// <see cref="Aspose::Words::Saving::CssStyleSheetType::External">External</see> for EPUB.
    /// 
    /// Saving CSS style sheet into an external file is only supported when saving to HTML.
    /// When you are exporting to one of the container formats (EPUB or MHTML) and specifying
    /// <see cref="Aspose::Words::Saving::CssStyleSheetType::External">External</see>, CSS file will be encapsulated
    /// into the output package.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetFileName
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::CssStyleSheetType get_CssStyleSheetType() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetType
    ASPOSE_WORDS_SHARED_API void set_CssStyleSheetType(Aspose::Words::Saving::CssStyleSheetType value);
    /// Specifies a prefix which is added to all CSS class names.
    /// Default value is an empty string and generated CSS class names have no common prefix.
    /// 
    /// If this value is not empty, all CSS classes generated by %Aspose.Words will start with the specified prefix.
    /// This might be useful, for example, if you add custom CSS to generated documents and want to prevent class
    /// name conflicts.
    /// 
    /// If the value is not <c>%null</c> or empty, it must be a valid CSS identifier.
    /// 
    /// @exception System::ArgumentException The value is not empty and is not a valid CSS identifier.
    ASPOSE_WORDS_SHARED_API System::String get_CssClassNamePrefix() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_CssClassNamePrefix
    ASPOSE_WORDS_SHARED_API void set_CssClassNamePrefix(const System::String& value);
    /// Allows to control how document parts are saved when a document is saved to HTML or EPUB.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IDocumentPartSavingCallback> get_DocumentPartSavingCallback() const;
    /// Allows to control how document parts are saved when a document is saved to HTML or EPUB.
    ASPOSE_WORDS_SHARED_API void set_DocumentPartSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IDocumentPartSavingCallback>& value);
    /// Allows to control how CSS styles are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::ICssSavingCallback> get_CssSavingCallback() const;
    /// Allows to control how CSS styles are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API void set_CssSavingCallback(const System::SharedPtr<Aspose::Words::Saving::ICssSavingCallback>& value);
    /// Specifies how the document should be split when saving to <see cref="Aspose::Words::SaveFormat::Html">Html</see>,
    /// <see cref="Aspose::Words::SaveFormat::Epub">Epub</see> or <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> format.
    /// Default is <see cref="Aspose::Words::Saving::DocumentSplitCriteria::None">None</see> for HTML and
    /// <see cref="Aspose::Words::Saving::DocumentSplitCriteria::HeadingParagraph">HeadingParagraph</see> for EPUB and AZW3.
    /// 
    /// Normally you would want a document saved to HTML as a single file.
    /// But in some cases it is preferable to split the output into several smaller HTML pages.
    /// When saving to HTML format these pages will be output to individual files or streams.
    /// When saving to EPUB format they will be incorporated into corresponding packages.
    /// 
    /// A document cannot be split when saving in the MHTML format.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitHeadingLevel
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_DocumentPartSavingCallback
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::DocumentSplitCriteria get_DocumentSplitCriteria() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitCriteria
    ASPOSE_WORDS_SHARED_API void set_DocumentSplitCriteria(Aspose::Words::Saving::DocumentSplitCriteria value);
    /// Specifies the maximum level of headings at which to split the document.
    /// Default value is <c>%2</c>.
    /// 
    /// When <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitCriteria">DocumentSplitCriteria</see> includes <see cref="Aspose::Words::Saving::DocumentSplitCriteria::HeadingParagraph">HeadingParagraph</see>
    /// and this property is set to a value from 1 to 9, the document will be split at paragraphs formatted using
    /// <b>%Heading 1</b>, <b>%Heading 2</b> , <b>%Heading 3</b> etc. styles up to the specified heading level.
    /// 
    /// By default, only <b>%Heading 1</b> and <b>%Heading 2</b> paragraphs cause the document to be split.
    /// Setting this property to zero will cause the document not to be split at heading paragraphs at all.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitCriteria
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_DocumentPartSavingCallback
    ASPOSE_WORDS_SHARED_API int32_t get_DocumentSplitHeadingLevel() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitHeadingLevel
    ASPOSE_WORDS_SHARED_API void set_DocumentSplitHeadingLevel(int32_t value);
    /// Specifies the encoding to use when exporting to HTML, MHTML or EPUB.
    /// Default value is <c>%new UTF8Encoding(false)</c> (UTF-8 without BOM).
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Text::Encoding> get_Encoding() const;
    /// Specifies the encoding to use when exporting to HTML, MHTML or EPUB.
    /// Default value is <c>%new UTF8Encoding(false)</c> (UTF-8 without BOM).
    ASPOSE_WORDS_SHARED_API void set_Encoding(const System::SharedPtr<System::Text::Encoding>& value);
    /// Specifies the maximum level of headings populated to the navigation map when exporting to EPUB, MOBI, or AZW3
    /// formats. Default value is <c>%3</c>.
    /// 
    /// The navigation map allows user agents to provide an easy way of navigation through the document structure.
    /// Usually navigation points correspond to headings in the document. In order to populate headings up to level <b>%N</b>
    /// assign this value to <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_NavigationMapLevel">NavigationMapLevel</see>.
    /// 
    /// By default, three levels of headings are populated: paragraphs of styles <b>%Heading 1</b>, <b>%Heading 2</b>
    /// and <b>%Heading 3</b>.
    /// You can set this property to a value from 1 to 9 in order to request the corresponding maximum level.
    /// Setting it to zero will reduce the navigation map to only the document root or roots of document parts.
    ASPOSE_WORDS_SHARED_API int32_t get_NavigationMapLevel() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_NavigationMapLevel
    ASPOSE_WORDS_SHARED_API void set_NavigationMapLevel(int32_t value);
    /// Specifies whether to export built-in and custom document properties to HTML, MHTML or EPUB.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportDocumentProperties() const;
    /// Specifies whether to export built-in and custom document properties to HTML, MHTML or EPUB.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportDocumentProperties(bool value);
    /// Specifies whether font resources should be exported to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    /// 
    /// Exporting font resources allows for consistent document rendering independent of the fonts available
    /// in a given user's environment.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources">ExportFontResources</see> is set to <c>%true</c>, main HTML document will refer to every font via
    /// the CSS 3 <b>%\@font-face</b> at-rule and fonts will be output as separate files. When exporting to IDPF EPUB or MHTML
    /// formats, fonts will be embedded into the corresponding package along with other subsidiary files.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontsAsBase64">ExportFontsAsBase64</see> is set to <c>%true</c>, fonts will not be saved to separate files.
    /// Instead, they will be embedded into <b>%\@font-face</b> at-rules in Base64 encoding.
    /// 
    /// <b>%Important!</b> When exporting font resources, font licensing issues should be considered. Authors who want to use specific fonts via a downloadable
    /// font mechanism must always carefully verify that their intended use is within the scope of the font license. Many commercial fonts presently do not
    /// allow web downloading of their fonts in any form. License agreements that cover some fonts specifically note that usage via <b>%\@font-face</b> rules
    /// in CSS style sheets is not allowed. Font subsetting can also violate license terms.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontResourcesSubsettingSizeThreshold
    ASPOSE_WORDS_SHARED_API bool get_ExportFontResources() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources
    ASPOSE_WORDS_SHARED_API void set_ExportFontResources(bool value);
    /// Specifies whether fonts resources should be embedded to HTML in Base64 encoding.
    /// Default is <c>%false</c>.
    /// 
    /// By default, fonts are written to separate files. If this option is set to <c>%true</c>, fonts will be embedded
    /// into the document's CSS in Base64 encoding.
    ASPOSE_WORDS_SHARED_API bool get_ExportFontsAsBase64() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontsAsBase64
    ASPOSE_WORDS_SHARED_API void set_ExportFontsAsBase64(bool value);
    /// Specifies how headers and footers are output to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::ExportHeadersFootersMode::PerSection">PerSection</see> for HTML/MHTML
    /// and <see cref="Aspose::Words::Saving::ExportHeadersFootersMode::None">None</see> for EPUB.
    /// 
    /// It is hard to meaningfully output headers and footers to HTML because HTML is not paginated.
    /// 
    /// When this property is <see cref="Aspose::Words::Saving::ExportHeadersFootersMode::PerSection">PerSection</see>, %Aspose.Words exports
    /// only primary headers and footers at the beginning and the end of each section.
    /// 
    /// When it is <see cref="Aspose::Words::Saving::ExportHeadersFootersMode::FirstSectionHeaderLastSectionFooter">FirstSectionHeaderLastSectionFooter</see>
    /// only first primary header and the last primary footer (including linked to previous) are exported.
    /// 
    /// You can disable export of headers and footers altogether by setting this property
    /// to <see cref="Aspose::Words::Saving::ExportHeadersFootersMode::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ExportHeadersFootersMode get_ExportHeadersFootersMode() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportHeadersFootersMode
    ASPOSE_WORDS_SHARED_API void set_ExportHeadersFootersMode(Aspose::Words::Saving::ExportHeadersFootersMode value);
    /// Specifies whether images are saved in Base64 format to the output HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    /// 
    /// When this property is set to <c>%true</c> images data are exported
    /// directly into the <b>%img</b> elements and separate files are not created.
    ASPOSE_WORDS_SHARED_API bool get_ExportImagesAsBase64() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportImagesAsBase64
    ASPOSE_WORDS_SHARED_API void set_ExportImagesAsBase64(bool value);
    /// Specifies whether language information is exported to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    /// 
    /// When this property is set to <c>%true</c> %Aspose.Words outputs <b>%lang</b> HTML attribute on the document
    /// elements that specify language. This can be needed to preserve language related semantics.
    ASPOSE_WORDS_SHARED_API bool get_ExportLanguageInformation() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportLanguageInformation
    ASPOSE_WORDS_SHARED_API void set_ExportLanguageInformation(bool value);
    /// Controls how list labels are output to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::ExportListLabels::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ExportListLabels get_ExportListLabels() const;
    /// Controls how list labels are output to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::ExportListLabels::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API void set_ExportListLabels(Aspose::Words::Saving::ExportListLabels value);
    /// Specifies in what format metafiles are saved when exporting to HTML, MHTML, or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlMetafileFormat::Png">Png</see>, meaning that metafiles are rendered to raster PNG images.
    /// 
    /// Metafiles are not natively displayed by HTML browsers. By default, %Aspose.Words converts WMF and EMF
    /// images into PNG files when exporting to HTML. Other options are to convert metafiles to SVG images or to export
    /// them as is without conversion.
    /// 
    /// Some image transforms, in particular image cropping, will not be applied to metafile images if they
    /// are exported to HTML without conversion.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImageResolution
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HtmlMetafileFormat get_MetafileFormat() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_MetafileFormat
    ASPOSE_WORDS_SHARED_API void set_MetafileFormat(Aspose::Words::Saving::HtmlMetafileFormat value);
    /// Specifies whether page setup is exported to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    /// 
    /// Each <see cref="Aspose::Words::Section">Section</see> in %Aspose.Words document model provides page setup information
    /// via <see cref="Aspose::Words::PageSetup">PageSetup</see> class. When you export a document to HTML format you might need to keep this information
    /// for further usage. In particular, page setup might be important for rendering to paged media (printing)
    /// or subsequent conversion to the native %Microsoft Word file formats (DOCX, DOC, RTF, WML).
    /// 
    /// In most cases HTML is intended for viewing in browsers where pagination is not performed. So this feature
    /// is inactive by default.
    ASPOSE_WORDS_SHARED_API bool get_ExportPageSetup() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportPageSetup
    ASPOSE_WORDS_SHARED_API void set_ExportPageSetup(bool value);
    /// Specifies whether page margins is exported to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportPageMargins() const;
    /// Specifies whether page margins is exported to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportPageMargins(bool value);
    /// Specifies whether font sizes should be output in relative units when saving to HTML, MHTML or EPUB.
    /// Default is <c>%false</c>.
    /// 
    /// In many existing documents (HTML, IDPF EPUB) font sizes are specified in relative units. This allows
    /// applications to adjust text size when viewing/processing documents. For instance, %Microsoft Internet Explorer
    /// has "View->Text Size" submenu, Adobe Digital Editions has two buttons: Increase/Decrease Text Size.
    /// If you expect this functionality to work then set <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportRelativeFontSize">ExportRelativeFontSize</see> property to <c>%true</c>.
    /// 
    /// Aspose Words document model contains and operates only with absolute font size units. Relative units need
    /// additional logic to be recalculated from some initial (standard) size. Font size of <b>%Normal</b> document style
    /// is taken as standard. For instance, if <b>%Normal</b> has 12pt font and some text is 18pt then it will be output
    /// as <b>%1.5em.</b> to the HTML.
    /// 
    /// When this option is enabled, document elements other than text will still have absolute sizes. Also some
    /// text-related attributes might be expressed absolutely. In particular, line spacing specified with "exactly" rule
    /// might produce unwanted results when scaling text. So the source documents should be properly designed and tested
    /// when exporting with <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportRelativeFontSize">ExportRelativeFontSize</see> set to <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportRelativeFontSize() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportRelativeFontSize
    ASPOSE_WORDS_SHARED_API void set_ExportRelativeFontSize(bool value);
    /// Controls how text input form fields are saved to HTML or MHTML.
    /// Default value is <c>%false</c>.
    /// 
    /// When set to <c>%true</c>, exports text input form fields as normal text.
    /// When <c>%false</c>, exports Word text input form fields as INPUT elements in HTML.
    /// 
    /// When exporting to EPUB, text input form fields are always saved as text due
    /// to requirements of this format.
    ASPOSE_WORDS_SHARED_API bool get_ExportTextInputFormFieldAsText() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportTextInputFormFieldAsText
    ASPOSE_WORDS_SHARED_API void set_ExportTextInputFormFieldAsText(bool value);
    /// Controls whether <see cref="Aspose::Words::Drawing::Shape">Shape</see> nodes are converted to SVG images when saving
    /// to HTML, MHTML, EPUB or AZW3.
    /// Default value is <c>%false</c>.
    /// 
    /// If this option is set to <c>%true</c>, <see cref="Aspose::Words::Drawing::Shape">Shape</see> nodes are exported as \<svg\> elements.
    /// Otherwise, they are rendered to bitmaps and are exported as \<img\> elements.
    ASPOSE_WORDS_SHARED_API bool get_ExportShapesAsSvg() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportShapesAsSvg
    ASPOSE_WORDS_SHARED_API void set_ExportShapesAsSvg(bool value);
    /// Controls how drop-down form fields are saved to HTML or MHTML.
    /// Default value is <c>%false</c>.
    /// 
    /// When set to <c>%true</c>, exports drop-down form fields as normal text.
    /// When <c>%false</c>, exports drop-down form fields as SELECT element in HTML.
    /// 
    /// When exporting to EPUB, text drop-down form fields are always saved as text due
    /// to requirements of this format.
    ASPOSE_WORDS_SHARED_API bool get_ExportDropDownFormFieldAsText() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportDropDownFormFieldAsText
    ASPOSE_WORDS_SHARED_API void set_ExportDropDownFormFieldAsText(bool value);
    /// Specifies whether to write page numbers to table of contents when saving HTML, MHTML and EPUB.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportTocPageNumbers() const;
    /// Specifies whether to write page numbers to table of contents when saving HTML, MHTML and EPUB.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportTocPageNumbers(bool value);
    /// Specifies whether to write the DOCTYPE declaration when saving to HTML or MHTML.
    /// When <c>%true</c>, writes a DOCTYPE declaration in the document prior to the root element.
    /// Default value is <c>%false</c>.
    /// When saving to EPUB or HTML5 (<see cref="Aspose::Words::Saving::HtmlVersion::Html5">Html5</see>) the DOCTYPE
    /// declaration is always written.
    /// 
    /// %Aspose.Words always writes well formed HTML regardless of this setting.
    /// 
    /// When <c>%true</c>, the beginning of the HTML output document will look like this:
    /// 
    /// @code
    /// <?xml version="1.0" encoding="utf-8" standalone="no" ?>
    ///              <!DOCTYPE html
    ///                    PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
    ///              "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
    ///              <html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en" lang="en">
    /// @endcode
    /// 
    /// %Aspose.Words aims to output XHTML according to the XHTML 1.0 Transitional specification,
    /// but the output will not always validate against the DTD. Some structures inside a %Microsoft Word
    /// document are hard or impossible to map to a document that will validate against the XHTML schema.
    /// For example, XHTML does not allow nested lists (UL cannot be nested inside another UL element),
    /// but in %Microsoft Word document multilevel lists occur quite often.
    ASPOSE_WORDS_SHARED_API bool get_ExportXhtmlTransitional() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportXhtmlTransitional
    ASPOSE_WORDS_SHARED_API void set_ExportXhtmlTransitional(bool value);
    /// Specifies version of HTML standard that should be used when saving the document to HTML or MHTML.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlVersion::Xhtml">Xhtml</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HtmlVersion get_HtmlVersion() const;
    /// Specifies version of HTML standard that should be used when saving the document to HTML or MHTML.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlVersion::Xhtml">Xhtml</see>.
    ASPOSE_WORDS_SHARED_API void set_HtmlVersion(Aspose::Words::Saving::HtmlVersion value);
    /// Specifies whether to write the roundtrip information when saving to HTML, MHTML or EPUB.
    /// Default value is <c>%true</c> for HTML and <c>%false</c> for MHTML and EPUB.
    /// 
    /// Saving of the roundtrip information allows to restore document properties such as tab stops,
    /// comments, headers and footers during the HTML documents loading back into a <see cref="Aspose::Words::Document">Document</see> object.
    /// 
    /// When <c>%true</c>, the roundtrip information is exported as -aw-* CSS properties
    /// of the corresponding HTML elements.
    /// 
    /// When <c>%false</c>, causes no roundtrip information to be output into produced files.
    ASPOSE_WORDS_SHARED_API bool get_ExportRoundtripInformation() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportRoundtripInformation
    ASPOSE_WORDS_SHARED_API void set_ExportRoundtripInformation(bool value);
    /// Specifies a physical folder where all resources like images, fonts, and external CSS are saved when a document
    /// is exported to HTML. Default is an empty string.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> is the simplest way to specify a folder where all resources should be written.
    /// Another way is to use individual properties <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see>, <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>,
    /// and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetFileName">CssStyleSheetFileName</see>.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> has a lower priority than folders specified via <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see>,
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>, and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetFileName">CssStyleSheetFileName</see>. For example, if both
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> are specified, fonts will be saved
    /// to <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see>, while images and CSS will be saved to <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see>.
    /// 
    /// If the folder specified by <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> doesn't exist, it will be created automatically.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_CssStyleSheetFileName
    ASPOSE_WORDS_SHARED_API System::String get_ResourceFolder() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder
    ASPOSE_WORDS_SHARED_API void set_ResourceFolder(const System::String& value);
    /// Specifies the name of the folder used to construct URIs of all resources written into an HTML document.
    /// Default is an empty string.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see> is the simplest way to specify how URIs for all resource files should be
    /// constructed. Same information can be specified for images and fonts separately via <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>
    /// and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> properties, respectively. However, there is no individual property for CSS.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see> has lower priority than <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see>
    /// and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>. For example, if both <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see>
    /// and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> are specified, fonts' URIs will be constructed using
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see>, while URIs of images and CSS will be constructed using
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see>.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see> is empty, the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> property value will be used
    /// to construct resource URIs.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see> is set to '.' (dot), resource URIs will contain file names only, without
    /// any path.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_ResourceFolderAlias() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ResourceFolderAlias(const System::String& value);
    /// Specifies the physical folder where fonts are saved when exporting a document to HTML.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in HTML format and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources">ExportFontResources</see>
    /// is set to <c>%true</c>, %Aspose.Words needs to save fonts used in the document as standalone files.
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> allows you to specify where the fonts will be saved and
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> allows to specify how the font URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// fonts in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the fonts,
    /// but still needs to save the fonts somewhere. In this case, you need to specify an accessible folder
    /// in the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> property or provide custom streams via
    /// the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontSavingCallback">FontSavingCallback</see> event handler.
    /// 
    /// If the folder specified by <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> doesn't exist, it will be created automatically.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> is another way to specify a folder where fonts should be saved.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_FontsFolder() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder
    ASPOSE_WORDS_SHARED_API void set_FontsFolder(const System::String& value);
    /// Specifies the name of the folder used to construct font URIs written into an HTML document.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in HTML format and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources">ExportFontResources</see>
    /// is set to <c>%true</c>, %Aspose.Words needs to save fonts used in the document as standalone files.
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> allows you to specify where the fonts will be saved and
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> allows to specify how the font URIs will be constructed.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> is not an empty string, then the font URI written
    /// to HTML will be <i>%FontsFolderAlias + \<font file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> is an empty string, then the font URI written
    /// to HTML will be <i>%FontsFolder + \<font file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> is set to '.' (dot), then the font file name
    /// will be written to HTML without path regardless of other options.
    /// 
    /// Alternative way to specify the name of the folder to construct font URIs
    /// is to use <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see>.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_FontsFolderAlias() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias
    ASPOSE_WORDS_SHARED_API void set_FontsFolderAlias(const System::String& value);
    /// Controls which font resources need subsetting when saving to HTML, MHTML or EPUB.
    /// Default is <c>%0</c>.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources">ExportFontResources</see> allows exporting fonts as subsidiary files or as parts of the output
    /// package. If the document uses many fonts, especially with large number of glyphs, then output size can grow
    /// significantly. Font subsetting reduces the size of the exported font resource by filtering out glyphs that
    /// are not used by the current document.
    /// 
    /// Font subsetting works as follows:
    /// 
    /// - By default, all exported fonts are subsetted.
    /// - Setting <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontResourcesSubsettingSizeThreshold">FontResourcesSubsettingSizeThreshold</see> to a positive value
    ///   instructs %Aspose.Words to subset fonts which file size is larger than the specified value.
    /// - Setting the property to <see cref="System::Int32::MaxValue">MaxValue</see>
    ///   suppresses font subsetting.
    /// 
    /// <b>%Important!</b> When exporting font resources, font licensing issues should be considered. Authors who want to use specific fonts via a downloadable
    /// font mechanism must always carefully verify that their intended use is within the scope of the font license. Many commercial fonts presently do not
    /// allow web downloading of their fonts in any form. License agreements that cover some fonts specifically note that usage via <b>%\@font-face</b> rules
    /// in CSS style sheets is not allowed. Font subsetting can also violate license terms.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources
    ASPOSE_WORDS_SHARED_API int32_t get_FontResourcesSubsettingSizeThreshold() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_FontResourcesSubsettingSizeThreshold
    ASPOSE_WORDS_SHARED_API void set_FontResourcesSubsettingSizeThreshold(int32_t value);
    /// Allows to control how fonts are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IFontSavingCallback> get_FontSavingCallback() const;
    /// Allows to control how fonts are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API void set_FontSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IFontSavingCallback>& value);
    /// Specifies the physical folder where images are saved when exporting a document to HTML format.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in HTML format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// images in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the images,
    /// but still needs to save the images somewhere. In this case, you need to specify an accessible folder
    /// in the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see> property or provide custom streams via
    /// the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImageSavingCallback">ImageSavingCallback</see> event handler.
    /// 
    /// If the folder specified by <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see> doesn't exist, it will be created automatically.
    /// 
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder">ResourceFolder</see> is another way to specify a folder where images should be saved.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImageSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolder() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder
    ASPOSE_WORDS_SHARED_API void set_ImagesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into an HTML document.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in HTML format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is not an empty string, then the image URI written
    /// to HTML will be <i>%ImagesFolderAlias + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is an empty string, then the image URI written
    /// to HTML will be <i>%ImagesFolder + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is set to '.' (dot), then the image file name
    /// will be written to HTML without path regardless of other options.
    /// 
    /// Alternative way to specify the name of the folder to construct image URIs
    /// is to use <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias">ResourceFolderAlias</see>.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ResourceFolderAlias
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImageSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ImagesFolderAlias(const System::String& value);
    /// Specifies the output resolution for images when exporting to HTML, MHTML or EPUB.
    /// Default is <c>%96 dpi</c>.
    /// 
    /// This property effects raster images when <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see>
    /// is <c>%true</c> and effects metafiles exported as raster images. Some image properties such as cropping
    /// or rotation require saving transformed images and in this case transformed images are created in the given
    /// resolution.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize
    ASPOSE_WORDS_SHARED_API int32_t get_ImageResolution() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ImageResolution
    ASPOSE_WORDS_SHARED_API void set_ImageResolution(int32_t value);
    /// Allows to control how images are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback> get_ImageSavingCallback() const;
    /// Allows to control how images are saved when a document is saved to HTML, MHTML or EPUB.
    ASPOSE_WORDS_SHARED_API void set_ImageSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback>& value);
    /// Specifies whether images are scaled by %Aspose.Words to the bounding shape size when exporting to HTML, MHTML
    /// or EPUB.
    /// Default value is <c>%true</c>.
    /// 
    /// An image in a %Microsoft Word document is a shape. The shape has a size and the image
    /// has its own size. The sizes are not directly linked. For example, the image can be 1024x786 pixels,
    /// but shape that displays this image can be 400x300 points.
    /// 
    /// In order to display an image in the browser, it must be scaled to the shape size.
    /// The <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see> property controls where the scaling of the image
    /// takes place: in %Aspose.Words during export to HTML or in the browser when displaying the document.
    /// 
    /// When <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see> is <c>%true</c>, the image is scaled by Aspose.Words
    /// using high quality scaling during export to HTML. When <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see>
    /// is <c>%false</c>, the image is output with its original size and the browser has to scale it.
    /// 
    /// In general, browsers do quick and poor quality scaling. As a result, you will normally get better
    /// display quality in the browser and smaller file size when <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see> is <c>%true</c>,
    /// but better printing quality and faster conversion when <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see> is <c>%false</c>.
    /// 
    /// In addition to shapes containing individual raster images, this option also affects group shapes consisting
    /// of raster images. If <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize">ScaleImageToShapeSize</see> is <c>%false</c> and a group shape contains raster images
    /// whose intrinsic resolution is higher than the value specified in <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImageResolution">ImageResolution</see>, %Aspose.Words will
    /// increase rendering resolution for that group. This allows to better preserve quality of grouped high resolution
    /// images when saving to HTML.
    /// 
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImageResolution
    ASPOSE_WORDS_SHARED_API bool get_ScaleImageToShapeSize() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ScaleImageToShapeSize
    ASPOSE_WORDS_SHARED_API void set_ScaleImageToShapeSize(bool value);
    /// Controls how table, row and cell widths are exported to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlElementSizeOutputMode::All">All</see>.
    /// 
    /// In the HTML format, table, row and cell elements
    /// (<b>%\<table\></b>, <b>%\<tr\></b>, <b>%\<th\></b>, <b>%\<td\></b>)
    /// can have their widths specified either in relative (percentage) or in absolute units.
    /// In a document in %Aspose.Words, tables, rows and cells can have their widths specified
    /// using either relative or absolute units too.
    /// 
    /// When you convert a document to HTML using %Aspose.Words, you might want to control how
    /// table, row and cell widths are exported to affect how the resulting document is displayed
    /// in the visual agent (e.g. a browser or viewer).
    /// 
    /// Use this property as a filter to specify what table widths values are exported into the destination document.
    /// For example, if you are converting a document to EPUB and intend to view the document on a mobile reading device,
    /// then you probably want to avoid exporting absolute width values. To do this you need to specify
    /// the output mode <see cref="Aspose::Words::Saving::HtmlElementSizeOutputMode::RelativeOnly">RelativeOnly</see> or <see cref="Aspose::Words::Saving::HtmlElementSizeOutputMode::None">None</see>
    /// so the viewer on the mobile device can layout the table to fit the width of the screen as best as it can.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HtmlElementSizeOutputMode get_TableWidthOutputMode() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_TableWidthOutputMode
    ASPOSE_WORDS_SHARED_API void set_TableWidthOutputMode(Aspose::Words::Saving::HtmlElementSizeOutputMode value);
    /// Controls how OfficeMath objects are exported to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlOfficeMathOutputMode::Image">Image</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HtmlOfficeMathOutputMode get_OfficeMathOutputMode() const;
    /// Controls how OfficeMath objects are exported to HTML, MHTML or EPUB.
    /// Default value is <see cref="Aspose::Words::Saving::HtmlOfficeMathOutputMode::Image">Image</see>.
    ASPOSE_WORDS_SHARED_API void set_OfficeMathOutputMode(Aspose::Words::Saving::HtmlOfficeMathOutputMode value);
    /// Specifies whether original URL should be used as the URL of the linked images.
    /// Default value is <c>%false</c>.
    /// 
    /// If value is set to <c>%true</c><see cref="Aspose::Words::Drawing::ImageData::get_SourceFullName">SourceFullName</see> value is used
    /// as the URL of linked images and linked images are not loaded into document's folder
    /// or <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>.
    /// 
    /// If value is set to <c>%false</c> linked images are loaded into document's folder
    /// or <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see> and URL of each linked image is constructed depending
    /// on document's folder, <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> properties.
    ASPOSE_WORDS_SHARED_API bool get_ExportOriginalUrlForLinkedImages() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportOriginalUrlForLinkedImages
    ASPOSE_WORDS_SHARED_API void set_ExportOriginalUrlForLinkedImages(bool value);
    /// Specifies whether to use CID (Content-ID) URLs to reference resources (images, fonts, CSS) included in MHTML
    /// documents. Default value is <c>%false</c>.
    /// 
    /// This option affects only documents being saved to MHTML.
    /// 
    /// By default, resources in MHTML documents are referenced by file name (for example, "image.png"), which
    /// are matched against "Content-Location" headers of MIME parts.
    /// 
    /// This option enables an alternative method, where references to resource files are written as CID (Content-ID)
    /// URLs (for example, "cid:image.png") and are matched against "Content-ID" headers.
    /// 
    /// In theory, there should be no difference between the two referencing methods and either of them should work
    /// fine in any browser or mail agent. In practice, however, some agents fail to fetch resources by file name. If your
    /// browser or mail agent refuses to load resources included in an MTHML document (doesn't show images or doesn't load
    /// CSS styles), try exporting the document with CID URLs.
    ASPOSE_WORDS_SHARED_API bool get_ExportCidUrlsForMhtmlResources() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ExportCidUrlsForMhtmlResources
    ASPOSE_WORDS_SHARED_API void set_ExportCidUrlsForMhtmlResources(bool value);
    /// Specifies whether font family names used in the document are resolved and substituted according to
    /// <see cref="Aspose::Words::Document::get_FontSettings">FontSettings</see> when being written into HTML-based formats.
    /// 
    /// By default, this option is set to <c>%false</c> and font family names are written to HTML as specified
    /// in source documents. That is, <see cref="Aspose::Words::Document::get_FontSettings">FontSettings</see> are ignored and no resolution or substitution
    /// of font family names is performed.
    /// 
    /// If this option is set to <c>%true</c>, %Aspose.Words uses <see cref="Aspose::Words::Document::get_FontSettings">FontSettings</see> to resolve
    /// each font family name specified in a source document into the name of an available font family, performing
    /// font substitution as required.
    ASPOSE_WORDS_SHARED_API bool get_ResolveFontNames() const;
    /// Setter for Aspose::Words::Saving::HtmlSaveOptions::get_ResolveFontNames
    ASPOSE_WORDS_SHARED_API void set_ResolveFontNames(bool value);
    /// Specifies whether backslash characters should be replaced with yen signs.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ReplaceBackslashWithYenSign() const;
    /// Specifies whether backslash characters should be replaced with yen signs.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ReplaceBackslashWithYenSign(bool value);
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_RemoveJavaScriptFromLinks() const;
    /// Specifies whether JavaScript will be removed from links.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_RemoveJavaScriptFromLinks(bool value);

    /// Initializes a new instance of this class that can be used to save a document
    /// in the <see cref="Aspose::Words::SaveFormat::Html">Html</see> format.
    ASPOSE_WORDS_SHARED_API HtmlSaveOptions();
    /// Initializes a new instance of this class that can be used to save a document
    /// in the <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
    /// <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see> format.
    /// 
    /// @param saveFormat Can be <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
    ///     <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see> or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see>.
    ASPOSE_WORDS_SHARED_API HtmlSaveOptions(Aspose::Words::SaveFormat saveFormat);

protected:

    ASPOSE_WORDS_SHARED_API bool get_IsMultipleMainPartsAllowed() override;

    ASPOSE_WORDS_SHARED_API void SetTestMode() override;

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    System::String mField7;
    System::String mField8;
    System::String mField9;
    System::String mField10;
    System::String mField11;
    System::SharedPtr<System::Object> mField12;
    __TypeStub<1,1,1,1>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    __TypeStub<4,4,4,4>::type mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    __TypeStub<1,1,1,1>::type mField18;
    __TypeStub<1,1,1,1>::type mField19;
    __TypeStub<1,1,1,1>::type mField20;
    __TypeStub<4,4,4,4>::type mField21;
    __TypeStub<4,4,4,4>::type mField22;
    __TypeStub<4,4,4,4>::type mField23;
    __TypeStub<1,1,1,1>::type mField24;
    System::SharedPtr<System::Object> mField25;
    __TypeStub<1,1,1,1>::type mField26;
    __TypeStub<4,4,4,4>::type mField27;
    __TypeStub<1,1,1,1>::type mField28;
    __TypeStub<1,1,1,1>::type mField29;
    __TypeStub<4,4,4,4>::type mField30;
    System::String mField31;
    System::String mField32;
    __TypeStub<4,4,4,4>::type mField33;
    __TypeStub<4,4,4,4>::type mField34;
    __TypeStub<4,4,4,4>::type mField35;
    System::SharedPtr<System::Object> mField36;
    System::SharedPtr<System::Object> mField37;
    __TypeStub<1,1,1,1>::type mField38;
    __TypeStub<1,1,1,1>::type mField39;
    __TypeStub<4,4,4,4>::type mField40;
    System::String mField41;
    __TypeStub<1,1,1,1>::type mField42;
    __TypeStub<1,1,1,1>::type mField43;
    __TypeStub<1,1,1,1>::type mField44;
    __TypeStub<1,1,1,1>::type mField45;
    System::String mField46;

};

}
}
}
