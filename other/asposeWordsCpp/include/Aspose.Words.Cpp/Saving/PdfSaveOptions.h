//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/PdfZoomBehavior.h>
#include <Aspose.Words.Cpp/Saving/PdfTextCompression.h>
#include <Aspose.Words.Cpp/Saving/PdfPageMode.h>
#include <Aspose.Words.Cpp/Saving/PdfPageLayout.h>
#include <Aspose.Words.Cpp/Saving/PdfImageCompression.h>
#include <Aspose.Words.Cpp/Saving/PdfImageColorSpaceExportMode.h>
#include <Aspose.Words.Cpp/Saving/PdfFontEmbeddingMode.h>
#include <Aspose.Words.Cpp/Saving/PdfCustomPropertiesExport.h>
#include <Aspose.Words.Cpp/Saving/PdfCompliance.h>
#include <Aspose.Words.Cpp/Saving/PdfAttachmentsEmbeddingMode.h>
#include <Aspose.Words.Cpp/Saving/HeaderFooterBookmarksExportMode.h>
#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
#include <Aspose.Words.Cpp/Saving/DmlEffectsRenderingMode.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{

namespace Saving
{
class DownsampleOptions;
class OutlineOptions;
class PdfDigitalSignatureDetails;
class PdfEncryptionDetails;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Pdf">Pdf</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PdfSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef PdfSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Pdf">Pdf</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Pdf">Pdf</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Allows to specify outline options.
    /// 
    /// Outlines can be created from headings and bookmarks.
    /// 
    /// For headings outline level is determined by the heading level.
    /// 
    /// It is possible to set the max heading level to be included into outlines or disable heading outlines at all.
    /// 
    /// For bookmarks outline level may be set in options as a default value for all bookmarks or as individual values for particular bookmarks.
    /// 
    /// Also, outlines can be exported to XPS format by using the same <see cref="Aspose::Words::Saving::PdfSaveOptions::get_OutlineOptions">OutlineOptions</see> class.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::OutlineOptions> get_OutlineOptions() const;
    /// Specifies compression type to be used for all textual content in the document.
    /// 
    /// Default is <see cref="Aspose::Words::Saving::PdfTextCompression::Flate">Flate</see>.
    /// 
    /// Significantly increases output size when saving a document without compression.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfTextCompression get_TextCompression() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_TextCompression
    ASPOSE_WORDS_SHARED_API void set_TextCompression(Aspose::Words::Saving::PdfTextCompression value);
    /// Gets or sets a value determining the quality of the JPEG images inside PDF document.
    /// 
    /// The default value is 100.
    /// 
    /// This property is used in conjunction with the <see cref="Aspose::Words::Saving::PdfSaveOptions::get_ImageCompression">ImageCompression</see> option.
    /// 
    /// Has effect only when a document contains JPEG images.
    /// 
    /// Use this property to get or set the quality of the images inside a document when saving in PDF format.
    /// The value may vary from 0 to 100 where 0 means worst quality but maximum compression and 100
    /// means best quality but minimum compression.
    /// If quality is 100 and source image is JPEG, it means no compression - original bytes will be saved.
    ASPOSE_WORDS_SHARED_API int32_t get_JpegQuality();
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_JpegQuality
    ASPOSE_WORDS_SHARED_API void set_JpegQuality(int32_t value);
    /// Specifies whether to preserve %Microsoft Word form fields as form fields in PDF or convert them to text.
    /// Default is <c>%false</c>.
    /// 
    /// %Microsoft Word form fields include text input, drop down and check box controls.
    /// 
    /// When set to <c>%false</c>, these fields will be exported as text to PDF. When set to <c>%true</c>,
    /// these fields will be exported as PDF form fields.
    /// 
    /// When exporting form fields to PDF as form fields, some formatting loss might occur because PDF form
    /// fields do not support all features of %Microsoft Word form fields.
    /// 
    /// Also, the output size depends on the content size because editable forms in %Microsoft Word are
    /// inline objects.
    ASPOSE_WORDS_SHARED_API bool get_PreserveFormFields() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_PreserveFormFields
    ASPOSE_WORDS_SHARED_API void set_PreserveFormFields(bool value);
    /// Specifies whether to use SDT control Tag or Id property as a name of form field in PDF.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// When set to <c>%false</c>, SDT control Id property is used as a name of form field in PDF.
    /// 
    /// When set to <c>%true</c>, SDT control Tag property is used as a name of form field in PDF.
    /// 
    /// If set to <c>%true</c> and Tag is empty, Id property will be used as a form field name.
    /// 
    /// If set to <c>%true</c> and Tag values are not unique, duplicate Tag values will be altered to build
    /// unique PDF form field names.
    ASPOSE_WORDS_SHARED_API bool get_UseSdtTagAsFormFieldName() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_UseSdtTagAsFormFieldName
    ASPOSE_WORDS_SHARED_API void set_UseSdtTagAsFormFieldName(bool value);
    /// Specifies whether to render PDF choice form field border.
    /// 
    /// PDF choice form fields are used for export of SDT Combo Box Content Control, SDT Drop-Down List Content
    /// Control and legacy Drop-Down Form Field when <see cref="Aspose::Words::Saving::PdfSaveOptions::get_PreserveFormFields">PreserveFormFields</see> option is enabled.
    /// 
    /// The default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_RenderChoiceFormFieldBorder() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_RenderChoiceFormFieldBorder
    ASPOSE_WORDS_SHARED_API void set_RenderChoiceFormFieldBorder(bool value);
    /// Specifies whether to convert footnote/endnote references in main text story into active hyperlinks.
    /// When clicked the hyperlink will lead to the corresponding footnote/endnote.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_CreateNoteHyperlinks() const;
    /// Specifies whether to convert footnote/endnote references in main text story into active hyperlinks.
    /// When clicked the hyperlink will lead to the corresponding footnote/endnote.
    /// Default is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_CreateNoteHyperlinks(bool value);
    /// Gets or sets the details for encrypting the output PDF document.
    /// 
    /// The default value is <c>%null</c> and the output document will not be encrypted.
    /// When this property is set to a valid <see cref="Aspose::Words::Saving::PdfEncryptionDetails">PdfEncryptionDetails</see> object,
    /// then the output PDF document will be encrypted.
    /// 
    /// AES-128 encryption algorithm is used when saving to PDF 1.7 based compliance (including PDF/UA-1).
    /// AES-256 encryption algorithm is used when saving to PDF 2.0 based compliance.
    /// 
    /// Encryption is prohibited by PDF/A compliance. This option will be ignored when saving to PDF/A.
    /// 
    /// <see cref="Aspose::Words::Saving::PdfPermissions::ContentCopyForAccessibility">ContentCopyForAccessibility</see> permission is required by PDF/UA compliance
    /// if the output document is encrypted. This permission will automatically used when saving to PDF/UA.
    /// 
    /// <see cref="Aspose::Words::Saving::PdfPermissions::ContentCopyForAccessibility">ContentCopyForAccessibility</see> permission is deprecated in PDF 2.0 format.
    /// This permission will be ignored when saving to PDF 2.0.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PdfEncryptionDetails> get_EncryptionDetails() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_EncryptionDetails
    ASPOSE_WORDS_SHARED_API void set_EncryptionDetails(const System::SharedPtr<Aspose::Words::Saving::PdfEncryptionDetails>& value);
    /// Gets or sets the details for signing the output PDF document.
    /// 
    /// The default value is <c>%null</c> and the output document will not be signed.
    /// When this property is set to a valid <see cref="Aspose::Words::Saving::PdfDigitalSignatureDetails">PdfDigitalSignatureDetails</see> object,
    /// then the output PDF document will be digitally signed.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PdfDigitalSignatureDetails> get_DigitalSignatureDetails() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_DigitalSignatureDetails
    ASPOSE_WORDS_SHARED_API void set_DigitalSignatureDetails(const System::SharedPtr<Aspose::Words::Saving::PdfDigitalSignatureDetails>& value);
    /// Controls how fonts are embedded into the resulting PDF documents.
    /// 
    /// The default value is <c>%false</c>, which means the fonts are subsetted before embedding.
    /// Subsetting is useful if you want to keep the output file size smaller. Subsetting removes all
    /// unused glyphs from a font.
    /// 
    /// When this value is set to <c>%true</c>, a complete font file is embedded into PDF without
    /// subsetting. This will result in larger output files, but can be a useful option when you want to
    /// edit the resulting PDF later (e.g. add more text).
    /// 
    /// Some fonts are large (several megabytes) and embedding them without subsetting
    /// will result in large output documents.
    ASPOSE_WORDS_SHARED_API bool get_EmbedFullFonts() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_EmbedFullFonts
    ASPOSE_WORDS_SHARED_API void set_EmbedFullFonts(bool value);
    /// Specifies the font embedding mode.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::PdfFontEmbeddingMode::EmbedAll">EmbedAll</see>.
    /// 
    /// This setting works only for the text in ANSI (Windows-1252) encoding. If the document contains
    /// non-ANSI text then corresponding fonts will be embedded regardless of this setting.
    /// 
    /// PDF/A and PDF/UA compliance requires all fonts to be embedded.
    /// <see cref="Aspose::Words::Saving::PdfFontEmbeddingMode::EmbedAll">EmbedAll</see> value will be used automatically when saving to
    /// PDF/A and PDF/UA.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfFontEmbeddingMode get_FontEmbeddingMode() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_FontEmbeddingMode
    ASPOSE_WORDS_SHARED_API void set_FontEmbeddingMode(Aspose::Words::Saving::PdfFontEmbeddingMode value);
    /// Gets or sets a value determining whether or not to substitute TrueType fonts Arial, Times New Roman,
    /// Courier New and Symbol with core PDF Type 1 fonts.
    /// 
    /// The default value is <c>%false</c>. When this value is set to <c>%true</c> Arial, Times New Roman,
    /// Courier New and Symbol fonts are replaced in PDF document with corresponding core Type 1 font.
    /// 
    /// Core PDF fonts, or their font metrics and suitable substitution fonts, are required to be available to any
    /// PDF viewer application.
    /// 
    /// This setting works only for the text in ANSI (Windows-1252) encoding. Non-ANSI text will be written
    /// with embedded TrueType font regardless of this setting.
    /// 
    /// PDF/A and PDF/UA compliance requires all fonts to be embedded. <c>%false</c> value will be used
    /// automatically when saving to PDF/A and PDF/UA.
    /// 
    /// Core fonts are not supported when saving to PDF 2.0 format. <c>%false</c> value will be used
    /// automatically when saving to PDF 2.0.
    /// 
    /// This option has a higher priority then <see cref="Aspose::Words::Saving::PdfSaveOptions::get_FontEmbeddingMode">FontEmbeddingMode</see> option.
    ASPOSE_WORDS_SHARED_API bool get_UseCoreFonts() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_UseCoreFonts
    ASPOSE_WORDS_SHARED_API void set_UseCoreFonts(bool value);
    /// Gets or sets a value determining the way <see cref="Aspose::Words::Document::get_CustomDocumentProperties">CustomDocumentProperties</see> are exported to PDF file.
    /// 
    /// Default value is <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::None">None</see>.
    /// 
    /// <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::Metadata">Metadata</see> value is not supported when saving to PDF/A.
    /// <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::Standard">Standard</see> will be used instead for PDF/A-1 and PDF/A-2 and
    /// <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::None">None</see> for PDF/A-4.
    /// 
    /// <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::Standard">Standard</see> value is not supported when saving to PDF 2.0.
    /// <see cref="Aspose::Words::Saving::PdfCustomPropertiesExport::Metadata">Metadata</see> will be used instead.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfCustomPropertiesExport get_CustomPropertiesExport() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_CustomPropertiesExport
    ASPOSE_WORDS_SHARED_API void set_CustomPropertiesExport(Aspose::Words::Saving::PdfCustomPropertiesExport value);
    /// Gets a value determining what type of zoom should be applied when a document is opened with a PDF viewer.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfZoomBehavior get_ZoomBehavior() const;
    /// Sets a value determining what type of zoom should be applied when a document is opened with a PDF viewer.
    ASPOSE_WORDS_SHARED_API void set_ZoomBehavior(Aspose::Words::Saving::PdfZoomBehavior value);
    /// Gets a value determining zoom factor (in percentages) for a document.
    ASPOSE_WORDS_SHARED_API int32_t get_ZoomFactor() const;
    /// Sets a value determining zoom factor (in percentages) for a document.
    ASPOSE_WORDS_SHARED_API void set_ZoomFactor(int32_t value);
    /// Specifies compression type to be used for all images in the document.
    /// 
    /// Default is <see cref="Aspose::Words::Saving::PdfImageCompression::Auto">Auto</see>.
    /// 
    /// Using <see cref="Aspose::Words::Saving::PdfImageCompression::Jpeg">Jpeg</see> lets you control the quality of images in the output document through the <see cref="Aspose::Words::Saving::PdfSaveOptions::get_JpegQuality">JpegQuality</see> property.
    /// 
    /// Using <see cref="Aspose::Words::Saving::PdfImageCompression::Jpeg">Jpeg</see> provides the fastest conversion speed when compared to the performance of other compression types,
    /// but in this case, there is lossy JPEG compression.
    /// 
    /// Using <see cref="Aspose::Words::Saving::PdfImageCompression::Auto">Auto</see> lets to control the quality of Jpeg in the output document through the <see cref="Aspose::Words::Saving::PdfSaveOptions::get_JpegQuality">JpegQuality</see> property,
    /// but for other formats, raw pixel data is extracted and saved with Flate compression.
    /// This case is slower than Jpeg conversion but lossless.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfImageCompression get_ImageCompression() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ImageCompression
    ASPOSE_WORDS_SHARED_API void set_ImageCompression(Aspose::Words::Saving::PdfImageCompression value);
    /// Gets or sets a value determining whether hyperlinks in the output Pdf document
    /// are forced to be opened in a new window (or tab) of a browser.
    /// 
    /// The default value is <c>%false</c>. When this value is set to <c>%true</c>
    /// hyperlinks are saved using JavaScript code.
    /// JavaScript code is <c>%app.launchURL("URL", true);</c>,
    /// where <c>%URL</c> is a hyperlink.
    /// 
    /// Note that if this option is set to <c>%true</c> hyperlinks can't work
    /// in some PDF readers e.g. Chrome, Firefox.
    /// 
    /// JavaScript actions are prohibited by PDF/A-1 and PDF/A-2 compliance. <c>%false</c> will be used automatically when
    /// saving to PDF/A-1 and PDF/A-2.
    ASPOSE_WORDS_SHARED_API bool get_OpenHyperlinksInNewWindow() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_OpenHyperlinksInNewWindow
    ASPOSE_WORDS_SHARED_API void set_OpenHyperlinksInNewWindow(bool value);
    /// Gets or sets a value determining whether or not to export document structure.
    /// 
    /// This value is ignored when saving to PDF/A-1a, PDF/A-2a and PDF/UA-1 because document structure is required for this compliance.
    /// 
    /// Note that exporting the document structure significantly increases the memory consumption, especially
    /// for the large documents.
    ASPOSE_WORDS_SHARED_API bool get_ExportDocumentStructure() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ExportDocumentStructure
    ASPOSE_WORDS_SHARED_API void set_ExportDocumentStructure(bool value);
    /// Gets or sets a value determining whether or not to create a "Span" tag in the document structure to export the text language.
    /// 
    /// Default value is <c>%false</c> and "Lang" attribute is attached to a marked-content sequence in a page content stream.
    /// 
    /// When the value is <c>%true</c> "Span" tag is created for the text with non-default language
    /// and "Lang" attribute is attached to this tag.
    /// 
    /// This value is ignored when <see cref="Aspose::Words::Saving::PdfSaveOptions::get_ExportDocumentStructure">ExportDocumentStructure</see> is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportLanguageToSpanTag() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ExportLanguageToSpanTag
    ASPOSE_WORDS_SHARED_API void set_ExportLanguageToSpanTag(bool value);
    /// Gets or sets a value determining whether a paragraph graphic should be marked as an artifact.
    /// 
    /// Default value is <c>%false</c> and paragraph graphics (underlines, text emphasis, etc.)
    /// will be marked as "Span" in the logical structure of the document.
    /// 
    /// When the value is <c>%true</c> the paragraph graphics will be marked as "Artifact".
    /// 
    /// This value is ignored when <see cref="Aspose::Words::Saving::PdfSaveOptions::get_ExportDocumentStructure">ExportDocumentStructure</see> is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportParagraphGraphicsToArtifact() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ExportParagraphGraphicsToArtifact
    ASPOSE_WORDS_SHARED_API void set_ExportParagraphGraphicsToArtifact(bool value);
    /// Gets or sets a value determining whether floating shapes are exported as inline tags in the document structure.
    /// 
    /// Default value is <c>%false</c> and floating shapes will be exported as block-level tags,
    /// placed after the paragraph in which they are anchored.
    /// 
    /// When the value is <c>%true</c> floating shapes will be exported as inline tags,
    /// placed within the paragraph where they are anchored.
    /// 
    /// This value is ignored when <see cref="Aspose::Words::Saving::PdfSaveOptions::get_ExportDocumentStructure">ExportDocumentStructure</see> is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportFloatingShapesAsInlineTag() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ExportFloatingShapesAsInlineTag
    ASPOSE_WORDS_SHARED_API void set_ExportFloatingShapesAsInlineTag(bool value);
    /// Gets or sets a boolean value indicating whether the document should be saved using a booklet printing layout,
    /// if it is specified via <see cref="Aspose::Words::PageSetup::get_MultiplePages">MultiplePages</see>.
    /// 
    /// If this option is specified, <see cref="Aspose::Words::Saving::FixedPageSaveOptions::get_PageSet">PageSet</see> is ignored when saving.
    /// This behavior matches MS Word.
    /// If book fold printing settings are not specified in page setup, this option will have no effect.
    ASPOSE_WORDS_SHARED_API bool get_UseBookFoldPrintingSettings() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_UseBookFoldPrintingSettings
    ASPOSE_WORDS_SHARED_API void set_UseBookFoldPrintingSettings(bool value);
    /// Allows to specify downsample options.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::DownsampleOptions> get_DownsampleOptions() const;
    /// Allows to specify downsample options.
    ASPOSE_WORDS_SHARED_API void set_DownsampleOptions(const System::SharedPtr<Aspose::Words::Saving::DownsampleOptions>& value);
    /// Specifies the page layout to be used when the document is opened in a PDF reader.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfPageLayout get_PageLayout() const;
    /// Specifies the page layout to be used when the document is opened in a PDF reader.
    ASPOSE_WORDS_SHARED_API void set_PageLayout(Aspose::Words::Saving::PdfPageLayout value);
    /// Specifies how the PDF document should be displayed when opened in a PDF reader.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfPageMode get_PageMode() const;
    /// Specifies how the PDF document should be displayed when opened in a PDF reader.
    ASPOSE_WORDS_SHARED_API void set_PageMode(Aspose::Words::Saving::PdfPageMode value);
    /// Specifies how the color space will be selected for the images in PDF document.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::PdfImageColorSpaceExportMode::Auto">Auto</see>.
    /// 
    /// If <see cref="Aspose::Words::Saving::PdfImageColorSpaceExportMode::SimpleCmyk">SimpleCmyk</see> value is specified,
    /// <see cref="Aspose::Words::Saving::PdfSaveOptions::get_ImageCompression">ImageCompression</see> option is ignored and
    /// Flate compression is used for all images in the document.
    /// 
    /// <see cref="Aspose::Words::Saving::PdfImageColorSpaceExportMode::SimpleCmyk">SimpleCmyk</see> value is not supported when saving to PDF/A.
    /// <see cref="Aspose::Words::Saving::PdfImageColorSpaceExportMode::Auto">Auto</see> value will be used instead.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfImageColorSpaceExportMode get_ImageColorSpaceExportMode() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_ImageColorSpaceExportMode
    ASPOSE_WORDS_SHARED_API void set_ImageColorSpaceExportMode(Aspose::Words::Saving::PdfImageColorSpaceExportMode value);
    /// Gets or sets a value determining whether or not to preblend transparent images with black background color.
    /// 
    /// Preblending images may improve PDF document visual appearance in Adobe Reader and remove anti-aliasing artifacts.
    /// 
    /// In order to properly display preblended images, PDF viewer application must support /Matte entry in soft-mask image dictionary.
    /// Also preblending images may decrease PDF rendering performance.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_PreblendImages() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_PreblendImages
    ASPOSE_WORDS_SHARED_API void set_PreblendImages(bool value);
    /// A flag specifying whether the window’s title bar should display the document title taken from
    /// the Title entry of the document information dictionary.
    /// 
    /// If <c>%false</c>, the title bar should instead display the name of the PDF file containing the document.
    /// 
    /// This flag is required by PDF/UA compliance. <c>%true</c> value will be used automatically when saving
    /// to PDF/UA.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_DisplayDocTitle() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_DisplayDocTitle
    ASPOSE_WORDS_SHARED_API void set_DisplayDocTitle(bool value);
    /// Gets or sets a value determining how DrawingML effects are rendered.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::DmlEffectsRenderingMode::Simplified">Simplified</see>.
    /// 
    /// This property is used when the document is exported to fixed page formats.
    /// 
    /// If <see cref="Aspose::Words::Saving::PdfSaveOptions::get_Compliance">Compliance</see> is set to <see cref="Aspose::Words::Saving::PdfCompliance::PdfA1a">PdfA1a</see> or <see cref="Aspose::Words::Saving::PdfCompliance::PdfA1b">PdfA1b</see>,
    /// property always returns <see cref="Aspose::Words::Saving::DmlEffectsRenderingMode::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::DmlEffectsRenderingMode get_DmlEffectsRenderingMode() override;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_DmlEffectsRenderingMode
    ASPOSE_WORDS_SHARED_API void set_DmlEffectsRenderingMode(Aspose::Words::Saving::DmlEffectsRenderingMode value) override;
    /// Determines how bookmarks in headers/footers are exported.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::HeaderFooterBookmarksExportMode::All">All</see>.
    /// 
    /// This property is used in conjunction with the <see cref="Aspose::Words::Saving::PdfSaveOptions::get_OutlineOptions">OutlineOptions</see> option.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::HeaderFooterBookmarksExportMode get_HeaderFooterBookmarksExportMode() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_HeaderFooterBookmarksExportMode
    ASPOSE_WORDS_SHARED_API void set_HeaderFooterBookmarksExportMode(Aspose::Words::Saving::HeaderFooterBookmarksExportMode value);
    /// A flag specifying whether to write additional text positioning operators or not.
    /// 
    /// If <c>%true</c>, additional text positioning operators are written to the output PDF. This may help to overcome
    /// issues with inaccurate text positioning with some printers. The downside is the increased PDF document size.
    /// 
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_AdditionalTextPositioning() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_AdditionalTextPositioning
    ASPOSE_WORDS_SHARED_API void set_AdditionalTextPositioning(bool value);
    /// A flag indicating whether image interpolation shall be performed by a conforming reader.
    /// When <c>%false</c> is specified, the flag is not written to the output document and
    /// the default behaviour of reader is used instead.
    /// 
    /// When the resolution of a source image is significantly lower than that of the output device,
    /// each source sample covers many device pixels. As a result, images can appear jaggy or blocky.
    /// These visual artifacts can be reduced by applying an image interpolation algorithm during rendering.
    /// Instead of painting all pixels covered by a source sample with the same color, image interpolation
    /// attempts to produce a smooth transition between adjacent sample values.
    /// 
    /// A conforming Reader may choose to not implement this feature of PDF,
    /// or may use any specific implementation of interpolation that it wishes.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// Interpolation flag is prohibited by PDF/A compliance. <c>%false</c> value will be used automatically
    /// when saving to PDF/A.
    ASPOSE_WORDS_SHARED_API bool get_InterpolateImages() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_InterpolateImages
    ASPOSE_WORDS_SHARED_API void set_InterpolateImages(bool value);
    /// Specifies the PDF standards compliance level for output documents.
    /// 
    /// Default is <see cref="Aspose::Words::Saving::PdfCompliance::Pdf17">Pdf17</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfCompliance get_Compliance() const;
    /// Specifies the PDF standards compliance level for output documents.
    /// 
    /// Default is <see cref="Aspose::Words::Saving::PdfCompliance::Pdf17">Pdf17</see>.
    ASPOSE_WORDS_SHARED_API void set_Compliance(Aspose::Words::Saving::PdfCompliance value);
    /// Gets or sets a value determining whether or not to cache graphics placed in document's background.
    /// 
    /// Default value is <c>%true</c> and background graphics are written to the PDF document as an xObject.
    /// 
    /// When the value is <c>%false</c> background graphics are not cached.
    /// 
    /// Some shapes are not supported for caching(shapes with fields, bookmarks, HRefs).
    /// 
    /// Document background graphic is various shapes, charts, images placed in the footer or header,
    /// well as background and border of a page.
    ASPOSE_WORDS_SHARED_API bool get_CacheBackgroundGraphics() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_CacheBackgroundGraphics
    ASPOSE_WORDS_SHARED_API void set_CacheBackgroundGraphics(bool value);
    /// Gets or sets a value determining how attachments are embedded to the PDF document.
    /// 
    /// Default value is <see cref="Aspose::Words::Saving::PdfAttachmentsEmbeddingMode::None">None</see> and attachments are not embedded.
    /// 
    /// PDF/A-1, PDF/A-2 and regular PDF/A-4 (not PDF/A-4f) standards do not allow embedded files.
    /// <see cref="Aspose::Words::Saving::PdfAttachmentsEmbeddingMode::None">None</see> value will be used automatically.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfAttachmentsEmbeddingMode get_AttachmentsEmbeddingMode() const;
    /// Setter for Aspose::Words::Saving::PdfSaveOptions::get_AttachmentsEmbeddingMode
    ASPOSE_WORDS_SHARED_API void set_AttachmentsEmbeddingMode(Aspose::Words::Saving::PdfAttachmentsEmbeddingMode value);

    /// Initializes a new instance of this class that can be used to save a document in the
    /// <see cref="Aspose::Words::SaveFormat::Pdf">Pdf</see> format.
    ASPOSE_WORDS_SHARED_API PdfSaveOptions();

    /// Creates a deep clone of this object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PdfSaveOptions> Clone();

protected:

    ASPOSE_WORDS_SHARED_API bool get_CreateOutlinesForHeadingsInTables() override;

    ASPOSE_WORDS_SHARED_API bool get_IsShapingSupported() override;

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<1,1,1,1>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<4,4,4,4>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    System::SharedPtr<System::Object> mField7;
    __TypeStub<4,4,4,4>::type mField8;
    __TypeStub<1,1,1,1>::type mField9;
    __TypeStub<4,4,4,4>::type mField10;
    __TypeStub<4,4,4,4>::type mField11;
    __TypeStub<4,4,4,4>::type mField12;
    __TypeStub<4,4,4,4>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    System::SharedPtr<System::Object> mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<1,1,1,1>::type mField17;
    __TypeStub<1,1,1,1>::type mField18;
    __TypeStub<1,1,1,1>::type mField19;
    System::SharedPtr<System::Object> mField20;
    __TypeStub<4,4,4,4>::type mField21;
    __TypeStub<4,4,4,4>::type mField22;
    __TypeStub<4,4,4,4>::type mField23;
    __TypeStub<1,1,1,1>::type mField24;
    __TypeStub<1,1,1,1>::type mField25;
    __TypeStub<4,4,4,4>::type mField26;
    __TypeStub<1,1,1,1>::type mField27;
    __TypeStub<1,1,1,1>::type mField28;
    __TypeStub<1,1,1,1>::type mField29;
    __TypeStub<1,1,1,1>::type mField30;
    __TypeStub<1,1,1,1>::type mField31;
    __TypeStub<4,4,4,4>::type mField32;

};

}
}
}
