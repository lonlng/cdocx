//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/SaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/ImlRenderingMode.h>
#include <Aspose.Words.Cpp/Saving/DmlRenderingMode.h>
#include <Aspose.Words.Cpp/Saving/DmlEffectsRenderingMode.h>
#include <Aspose.Words.Cpp/Saving/Dml3DEffectsRenderingMode.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{

class IDocumentSavingCallback;

}

}
}
namespace System
{
class TimeZoneInfo;
}

namespace Aspose {

namespace Words {

namespace Saving {

/// This is an abstract base class for classes that allow the user to specify additional
/// options when saving a document into a particular format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SaveOptions : public System::Object
{
    typedef SaveOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() = 0;
    /// Specifies the format in which the document will be saved if this save options object is used.
    virtual ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) = 0;
    /// When <c>%true</c>, causes the name and version of %Aspose.Words to be embedded into produced files.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ExportGeneratorName() const;
    /// When <c>%true</c>, causes the name and version of %Aspose.Words to be embedded into produced files.
    /// Default value is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ExportGeneratorName(bool value);
    /// Specifies the folder for temporary files used when saving to a DOC or DOCX file.
    /// By default, this property is <c>%null</c> and no temporary files are used.
    /// 
    /// When %Aspose.Words saves a document, it needs to create temporary internal structures. By default,
    /// these internal structures are created in memory and the memory usage spikes for a short period while
    /// the document is being saved. When saving is complete, the memory is freed and reclaimed by the garbage collector.
    /// 
    /// Specifying a temporary folder using <see cref="Aspose::Words::Saving::SaveOptions::get_TempFolder">TempFolder</see> will cause %Aspose.Words to keep the internal structures in
    /// temporary files instead of memory. It reduces the memory usage during saving, but will decrease the save performance.
    /// 
    /// The folder must exist and be writable, otherwise an exception will be thrown.
    /// 
    /// %Aspose.Words automatically deletes all temporary files when saving is complete.
    /// 
    /// @exception System::OutOfMemoryException Throw if you are saving a very large document (thousands of pages) and/or processing many documents at the same time.
    ///     The memory spike during saving can be significant enough to cause the exception.
    ASPOSE_WORDS_SHARED_API System::String get_TempFolder() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_TempFolder
    ASPOSE_WORDS_SHARED_API void set_TempFolder(const System::String& value);
    /// Gets a value determining whether OLE controls presentation image will be updated.
    ASPOSE_WORDS_SHARED_API bool get_UpdateOleControlImages() const;
    /// Sets a value determining whether OLE controls presentation image will be updated.
    ASPOSE_WORDS_SHARED_API void set_UpdateOleControlImages(bool value);
    /// When <c>%true</c>, pretty formats output where applicable.
    /// Default value is <c>%false</c>.
    /// 
    /// Set to <c>%true</c> to make HTML, MHTML, EPUB, WordML, RTF, DOCX and ODT output human readable.
    /// Useful for testing or debugging.
    ASPOSE_WORDS_SHARED_API bool get_PrettyFormat() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_PrettyFormat
    ASPOSE_WORDS_SHARED_API void set_PrettyFormat(bool value);
    /// Gets or sets a value determining whether or not to use anti-aliasing for rendering.
    /// 
    /// The default value is <c>%false</c>. When this value is set to <c>%true</c> anti-aliasing is
    /// used for rendering.
    /// 
    /// This property is used when the document is exported to the following formats:
    /// <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>, <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>,
    /// <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see>, <see cref="Aspose::Words::SaveFormat::Emf">Emf</see>. When the document is exported to the
    /// <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>,
    /// <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>, <see cref="Aspose::Words::SaveFormat::Azw3">Azw3</see>
    /// or <see cref="Aspose::Words::SaveFormat::Mobi">Mobi</see> formats this option is used for raster images.
    ASPOSE_WORDS_SHARED_API bool get_UseAntiAliasing() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_UseAntiAliasing
    ASPOSE_WORDS_SHARED_API void set_UseAntiAliasing(bool value);
    /// Gets or sets a value determining whether or not to use high quality (i.e. slow) rendering algorithms.
    /// 
    /// The default value is <c>%false</c>.
    /// 
    /// This property is used when the document is exported to image formats:
    /// <see cref="Aspose::Words::SaveFormat::Tiff">Tiff</see>, <see cref="Aspose::Words::SaveFormat::Png">Png</see>, <see cref="Aspose::Words::SaveFormat::Bmp">Bmp</see>,
    /// <see cref="Aspose::Words::SaveFormat::Jpeg">Jpeg</see>, <see cref="Aspose::Words::SaveFormat::Emf">Emf</see>.
    ASPOSE_WORDS_SHARED_API bool get_UseHighQualityRendering() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_UseHighQualityRendering
    ASPOSE_WORDS_SHARED_API void set_UseHighQualityRendering(bool value);
    /// Gets or sets a value determining how DrawingML shapes are rendered.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::DmlRenderingMode::Fallback">Fallback</see>.
    /// 
    /// This property is used when the document is exported to fixed page formats.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::DmlRenderingMode get_DmlRenderingMode() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_DmlRenderingMode
    ASPOSE_WORDS_SHARED_API void set_DmlRenderingMode(Aspose::Words::Saving::DmlRenderingMode value);
    /// Gets or sets a value determining how DrawingML effects are rendered.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::DmlEffectsRenderingMode::Simplified">Simplified</see>.
    /// 
    /// This property is used when the document is exported to fixed page formats.
    virtual ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::DmlEffectsRenderingMode get_DmlEffectsRenderingMode();
    /// Setter for Aspose::Words::Saving::SaveOptions::get_DmlEffectsRenderingMode
    virtual ASPOSE_WORDS_SHARED_API void set_DmlEffectsRenderingMode(Aspose::Words::Saving::DmlEffectsRenderingMode value);
    /// Gets or sets a value determining how ink (InkML) objects are rendered.
    /// 
    /// The default value is <see cref="Aspose::Words::Saving::ImlRenderingMode::InkML">InkML</see>.
    /// 
    /// This property is used when the document is exported to fixed page formats.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::ImlRenderingMode get_ImlRenderingMode() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_ImlRenderingMode
    ASPOSE_WORDS_SHARED_API void set_ImlRenderingMode(Aspose::Words::Saving::ImlRenderingMode value);
    /// Gets path to default template (including filename).
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_DefaultTemplate() const;
    /// Sets path to default template (including filename).
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_DefaultTemplate(const System::String& value);
    /// Gets a value determining if fields of certain types should be updated before saving the document to a fixed page format.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_UpdateFields() const;
    /// Sets a value determining if fields of certain types should be updated before saving the document to a fixed page format.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_UpdateFields(bool value);
    /// Gets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_LastSavedTime">LastSavedTime</see> property is updated before saving.
    ASPOSE_WORDS_SHARED_API bool get_UpdateLastSavedTimeProperty() const;
    /// Sets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_LastSavedTime">LastSavedTime</see> property is updated before saving.
    ASPOSE_WORDS_SHARED_API void set_UpdateLastSavedTimeProperty(bool value);
    /// Gets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_LastPrinted">LastPrinted</see> property is updated before saving.
    ASPOSE_WORDS_SHARED_API bool get_UpdateLastPrintedProperty() const;
    /// Sets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_LastPrinted">LastPrinted</see> property is updated before saving.
    ASPOSE_WORDS_SHARED_API void set_UpdateLastPrintedProperty(bool value);
    /// Gets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_CreatedTime">CreatedTime</see> property is updated before saving.
    /// Default value is <c>%false</c>;
    ASPOSE_WORDS_SHARED_API bool get_UpdateCreatedTimeProperty() const;
    /// Sets a value determining whether the <see cref="Aspose::Words::Properties::BuiltInDocumentProperties::get_CreatedTime">CreatedTime</see> property is updated before saving.
    /// Default value is <c>%false</c>;
    ASPOSE_WORDS_SHARED_API void set_UpdateCreatedTimeProperty(bool value);
    /// Gets value determining if memory optimization should be performed before saving the document.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_MemoryOptimization() const;
    /// Sets value determining if memory optimization should be performed before saving the document.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_MemoryOptimization(bool value);
    /// Determines whether the font attributes will be changed according to the character code being used.
    ASPOSE_WORDS_SHARED_API bool get_UpdateAmbiguousTextFont() const;
    /// Determines whether the font attributes will be changed according to the character code being used.
    ASPOSE_WORDS_SHARED_API void set_UpdateAmbiguousTextFont(bool value);
    /// Gets a value determining how 3D effects are rendered.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::Dml3DEffectsRenderingMode get_Dml3DEffectsRenderingMode() const;
    /// Sets a value determining how 3D effects are rendered.
    ASPOSE_WORDS_SHARED_API void set_Dml3DEffectsRenderingMode(Aspose::Words::Saving::Dml3DEffectsRenderingMode value);
    /// Called during saving a document and accepts data about saving progress.
    /// 
    /// Progress is reported when saving to <see cref="Aspose::Words::SaveFormat::Docx">Docx</see>, <see cref="Aspose::Words::SaveFormat::FlatOpc">FlatOpc</see>,
    /// <see cref="Aspose::Words::SaveFormat::Docm">Docm</see>, <see cref="Aspose::Words::SaveFormat::Dotm">Dotm</see>, <see cref="Aspose::Words::SaveFormat::Dotx">Dotx</see>,
    /// <see cref="Aspose::Words::SaveFormat::Doc">Doc</see>, <see cref="Aspose::Words::SaveFormat::Dot">Dot</see>,
    /// <see cref="Aspose::Words::SaveFormat::Html">Html</see>, <see cref="Aspose::Words::SaveFormat::Mhtml">Mhtml</see>, <see cref="Aspose::Words::SaveFormat::Epub">Epub</see>,
    /// <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see>, or <see cref="Aspose::Words::SaveFormat::XamlFlowPack">XamlFlowPack</see>.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Saving::IDocumentSavingCallback>& get_ProgressCallback() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_ProgressCallback
    ASPOSE_WORDS_SHARED_API void set_ProgressCallback(const System::SharedPtr<Aspose::Words::Saving::IDocumentSavingCallback>& value);
    /// Gets or sets a boolean value indicating whether to allow embedding fonts with PostScript outlines
    /// when embedding TrueType fonts in a document upon it is saved.
    /// The default value is <c>%false</c>.
    /// 
    /// Note, Word does not embed PostScript fonts, but can open documents with embedded fonts of this type.
    /// 
    /// This option only works when <see cref="Aspose::Words::Fonts::FontInfoCollection::get_EmbedTrueTypeFonts">EmbedTrueTypeFonts</see> of the
    /// <see cref="Aspose::Words::DocumentBase::get_FontInfos">FontInfos</see> property is set to <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_AllowEmbeddingPostScriptFonts() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_AllowEmbeddingPostScriptFonts
    ASPOSE_WORDS_SHARED_API void set_AllowEmbeddingPostScriptFonts(bool value);
    /// Gets or sets custom local time zone used for date/time fields.
    /// 
    /// This option is available in either .Net framework starting from 3.5 version or .Net Standard.
    /// 
    /// By default, %Aspose.Words uses system local time zone when writes date/time fields, this option allows to set custom value.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::TimeZoneInfo> get_CustomTimeZoneInfo() const;
    /// Setter for Aspose::Words::Saving::SaveOptions::get_CustomTimeZoneInfo
    ASPOSE_WORDS_SHARED_API void set_CustomTimeZoneInfo(const System::SharedPtr<System::TimeZoneInfo>& value);

    /// Creates a save options object of a class suitable for the specified save format.
    /// 
    /// @param saveFormat The save format for which to create a save options object.
    /// 
    /// @return An object of a class that derives from <see cref="Aspose::Words::Saving::SaveOptions">SaveOptions</see>.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOptions> CreateSaveOptions(Aspose::Words::SaveFormat saveFormat);
    /// Creates a save options object of a class suitable for the file extension specified in the given file name.
    /// 
    /// @param fileName The extension of this file name determines the class of the save options object to create.
    /// 
    /// @return An object of a class that derives from <see cref="Aspose::Words::Saving::SaveOptions">SaveOptions</see>.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::SaveOptions> CreateSaveOptions(const System::String& fileName);

protected:

    virtual ASPOSE_WORDS_SHARED_API bool get_IsMultipleMainPartsAllowed();
    virtual ASPOSE_WORDS_SHARED_API bool get_IsFlowFormat();

    ASPOSE_WORDS_SHARED_API SaveOptions();

    virtual ASPOSE_WORDS_SHARED_API void SetTestMode();

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<1,1,1,1>::type mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;
    __TypeStub<4,4,4,4>::type mField7;
    __TypeStub<4,4,4,4>::type mField8;
    __TypeStub<4,4,4,4>::type mField9;
    System::String mField10;
    __TypeStub<1,1,1,1>::type mField11;
    __TypeStub<1,1,1,1>::type mField12;
    __TypeStub<1,1,1,1>::type mField13;
    __TypeStub<1,1,1,1>::type mField14;
    __TypeStub<1,1,1,1>::type mField15;
    __TypeStub<1,1,1,1>::type mField16;
    __TypeStub<4,4,4,4>::type mField17;
    System::SharedPtr<System::Object> mField18;
    __TypeStub<1,1,1,1>::type mField19;
    System::SharedPtr<System::Object> mField20;
    __TypeStub<1,1,1,1>::type mField21;
    __TypeStub<1,1,1,1>::type mField22;
    __TypeStub<1,1,1,1>::type mField23;
    __TypeStub<1,1,1,1>::type mField24;

};

}
}
}
