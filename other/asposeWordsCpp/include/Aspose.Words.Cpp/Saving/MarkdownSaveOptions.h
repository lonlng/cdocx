//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/MarkdownSaveOptions.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Saving/TxtSaveOptionsBase.h>
#include <Aspose.Words.Cpp/Saving/TableContentAlignment.h>
#include <Aspose.Words.Cpp/Saving/MarkdownOfficeMathExportMode.h>
#include <Aspose.Words.Cpp/Saving/MarkdownListExportMode.h>
#include <Aspose.Words.Cpp/Saving/MarkdownLinkExportMode.h>
#include <Aspose.Words.Cpp/Saving/MarkdownExportAsHtml.h>
#include <Aspose.Words.Cpp/Saving/MarkdownEmptyParagraphExportMode.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{
class IImageSavingCallback;
class IResourceSavingCallback;

}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Class to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS MarkdownSaveOptions : public Aspose::Words::Saving::TxtSaveOptionsBase
{
    typedef MarkdownSaveOptions ThisType;
    typedef Aspose::Words::Saving::TxtSaveOptionsBase BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Gets a value that specifies how to align contents in tables
    /// when exporting into the <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    /// The default value is <see cref="Aspose::Words::Saving::TableContentAlignment::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::TableContentAlignment get_TableContentAlignment() const;
    /// Sets a value that specifies how to align contents in tables
    /// when exporting into the <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    /// The default value is <see cref="Aspose::Words::Saving::TableContentAlignment::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API void set_TableContentAlignment(Aspose::Words::Saving::TableContentAlignment value);
    /// Specifies the physical folder where images are saved when exporting a document to
    /// the <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format. Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format,
    /// %Aspose.Words needs to save all images embedded in the document as standalone files.
    /// <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> allows you to specify where the images will be saved.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the images in
    /// the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder
    /// where to save the images, but still needs to save the images somewhere. In this case,
    /// you need to specify an accessible folder in the <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> property.
    /// 
    /// If the folder specified by <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> doesn't exist, it will be created automatically.
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolder() const;
    /// Setter for Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder
    ASPOSE_WORDS_SHARED_API void set_ImagesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into a document.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format,
    /// %Aspose.Words needs to save all images embedded in the document as standalone files.
    /// <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> allows you to specify where the images will be saved and
    /// <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> allows to specify how the image URIs will be constructed.
    /// 
    /// If <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is not an empty string, then the image URI written
    /// to Markdown will be <i>%ImagesFolderAlias + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is an empty string, then the image URI written
    /// to Markdown will be <i>%ImagesFolder + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is set to '.' (dot), then the image file name
    /// will be written to Markdown without path regardless of other options.
    /// 
    /// @sa Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder
    /// @sa Aspose::Words::Saving::MarkdownSaveOptions::get_ImageSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ImagesFolderAlias(const System::String& value);
    /// Allows to control how images are saved when a document is saved to
    /// <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback> get_ImageSavingCallback() const;
    /// Allows to control how images are saved when a document is saved to
    /// <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    ASPOSE_WORDS_SHARED_API void set_ImageSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback>& value);
    /// Allows to control how resources are saved when a document is exported to
    /// <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback>& get_ResourceSavingCallback() const;
    /// Allows to control how resources are saved when a document is exported to
    /// <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    ASPOSE_WORDS_SHARED_API void set_ResourceSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback>& value);
    /// Specifies whether images are saved in Base64 format to the output file.
    /// Default value is <c>%false</c>.
    /// 
    /// When this property is set to <c>%true</c> images data are exported
    /// directly into the <b>%img</b> elements and separate files are not created.
    ASPOSE_WORDS_SHARED_API bool get_ExportImagesAsBase64() const;
    /// Setter for Aspose::Words::Saving::MarkdownSaveOptions::get_ExportImagesAsBase64
    ASPOSE_WORDS_SHARED_API void set_ExportImagesAsBase64(bool value);
    /// Specifies how list items will be written to the output file.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownListExportMode::MarkdownSyntax">MarkdownSyntax</see>.
    /// 
    /// When this property is set to <see cref="Aspose::Words::Saving::MarkdownListExportMode::PlainText">PlainText</see> all list labels are
    /// updated using <see cref="Aspose::Words::Document::UpdateListLabels">UpdateListLabels</see> and exported with their actual values. Such lists
    /// can be non-compatible with Markdown format and will be recognized as plain text upon importing in this case.
    /// 
    /// When this property is set to <see cref="Aspose::Words::Saving::MarkdownListExportMode::MarkdownSyntax">MarkdownSyntax</see>, writer tries to export
    /// list items in manner that allows to numerate list items in automatic mode by Markdown.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MarkdownListExportMode get_ListExportMode() const;
    /// Setter for Aspose::Words::Saving::MarkdownSaveOptions::get_ListExportMode
    ASPOSE_WORDS_SHARED_API void set_ListExportMode(Aspose::Words::Saving::MarkdownListExportMode value);
    /// Gets a boolean value indicating either to export underline
    /// text formatting as sequence of two plus characters "++".
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportUnderlineFormatting() const;
    /// Sets a boolean value indicating either to export underline
    /// text formatting as sequence of two plus characters "++".
    /// The default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportUnderlineFormatting(bool value);
    /// Specifies how links will be written to the output file.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownLinkExportMode::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MarkdownLinkExportMode get_LinkExportMode() const;
    /// Specifies how links will be written to the output file.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownLinkExportMode::Auto">Auto</see>.
    ASPOSE_WORDS_SHARED_API void set_LinkExportMode(Aspose::Words::Saving::MarkdownLinkExportMode value);
    /// Specifies how OfficeMath will be written to the output file.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownOfficeMathExportMode::Text">Text</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MarkdownOfficeMathExportMode get_OfficeMathExportMode() const;
    /// Specifies how OfficeMath will be written to the output file.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownOfficeMathExportMode::Text">Text</see>.
    ASPOSE_WORDS_SHARED_API void set_OfficeMathExportMode(Aspose::Words::Saving::MarkdownOfficeMathExportMode value);
    /// Allows to specify the elements to be exported to Markdown as raw HTML.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownExportAsHtml::None">None</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MarkdownExportAsHtml get_ExportAsHtml() const;
    /// Allows to specify the elements to be exported to Markdown as raw HTML.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownExportAsHtml::None">None</see>.
    ASPOSE_WORDS_SHARED_API void set_ExportAsHtml(Aspose::Words::Saving::MarkdownExportAsHtml value);
    /// Specifies the output resolution for images when exporting to Markdown.
    /// Default is <c>%96 dpi</c>.
    ASPOSE_WORDS_SHARED_API int32_t get_ImageResolution() const;
    /// Specifies the output resolution for images when exporting to Markdown.
    /// Default is <c>%96 dpi</c>.
    ASPOSE_WORDS_SHARED_API void set_ImageResolution(int32_t value);
    /// Specifies how to export empty paragraphs to Markdown.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownEmptyParagraphExportMode::EmptyLine">EmptyLine</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::MarkdownEmptyParagraphExportMode get_EmptyParagraphExportMode() const;
    /// Specifies how to export empty paragraphs to Markdown.
    /// Default value is <see cref="Aspose::Words::Saving::MarkdownEmptyParagraphExportMode::EmptyLine">EmptyLine</see>.
    ASPOSE_WORDS_SHARED_API void set_EmptyParagraphExportMode(Aspose::Words::Saving::MarkdownEmptyParagraphExportMode value);

    /// Initializes a new instance of this class that can be used to save a document
    /// in the <see cref="Aspose::Words::SaveFormat::Markdown">Markdown</see> format.
    ASPOSE_WORDS_SHARED_API MarkdownSaveOptions();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<4,4,4,4>::type mField4;
    __TypeStub<4,4,4,4>::type mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    System::SharedPtr<System::Object> mField9;
    System::String mField10;
    System::String mField11;

};

}
}
}
