//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/FontSavingArgs.h
#pragma once

#include <system/string.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;

}
}
namespace System
{
namespace IO
{
class Stream;
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Provides data for the <see cref="Aspose::Words::Saving::IFontSavingCallback::FontSaving(System::SharedPtr<Aspose::Words::Saving::FontSavingArgs>)">FontSaving()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
/// 
/// When %Aspose.Words saves a document to HTML or related formats and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ExportFontResources">ExportFontResources</see>
/// is set to <c>%true</c>, it saves each font subject for export into a separate file.
/// 
/// <see cref="Aspose::Words::Saving::FontSavingArgs">FontSavingArgs</see> controls whether particular font resource should be exported and how.
/// 
/// <see cref="Aspose::Words::Saving::FontSavingArgs">FontSavingArgs</see> also allows to redefine how font file names are generated or to
/// completely circumvent saving of fonts into files by providing your own stream objects.
/// 
/// To decide whether to save a particular font resource, use the <see cref="Aspose::Words::Saving::FontSavingArgs::get_IsExportNeeded">IsExportNeeded</see> property.
/// 
/// To save fonts into streams instead of files, use the <see cref="Aspose::Words::Saving::FontSavingArgs::get_FontStream">FontStream</see> property.
class ASPOSE_WORDS_SHARED_CLASS FontSavingArgs : public System::Object
{
    typedef FontSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the document object that is being saved.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;
    /// Indicates the current font family name.
    ASPOSE_WORDS_SHARED_API System::String get_FontFamilyName() const;
    /// Indicates whether the current font is bold.
    ASPOSE_WORDS_SHARED_API bool get_Bold() const;
    /// Indicates whether the current font is italic.
    ASPOSE_WORDS_SHARED_API bool get_Italic() const;
    /// Gets the original font file name with an extension.
    /// 
    /// This property contains the original file name of the current font if it is known. Otherwise it can be an empty string.
    /// 
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_OriginalFileSize
    ASPOSE_WORDS_SHARED_API System::String get_OriginalFileName() const;
    /// Gets the original font file size.
    /// 
    /// This property contains the original file size of the current font if it is known. Otherwise it can be zero.
    /// 
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_OriginalFileName
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_IsSubsettingNeeded
    ASPOSE_WORDS_SHARED_API int32_t get_OriginalFileSize() const;
    /// Allows to specify whether the current font will be exported as a font resource. Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_IsExportNeeded() const;
    /// Allows to specify whether the current font will be exported as a font resource. Default is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_IsExportNeeded(bool value);
    /// Allows to specify whether the current font will be subsetted before exporting as a font resource.
    /// 
    /// Fonts can be exported as complete original font files or subsetted to include only the characters
    /// that are used in the document. Subsetting allows to reduce the resulting font resource size.
    /// 
    /// By default, %Aspose.Words decides whether to perform subsetting or not by comparing the original font file size
    /// with the one specified in <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontResourcesSubsettingSizeThreshold">FontResourcesSubsettingSizeThreshold</see>.
    /// You can override this behavior for individual fonts by setting the <see cref="Aspose::Words::Saving::FontSavingArgs::get_IsSubsettingNeeded">IsSubsettingNeeded</see> property.
    ASPOSE_WORDS_SHARED_API bool get_IsSubsettingNeeded() const;
    /// Setter for Aspose::Words::Saving::FontSavingArgs::get_IsSubsettingNeeded
    ASPOSE_WORDS_SHARED_API void set_IsSubsettingNeeded(bool value);
    /// Gets or sets the file name (without path) where the font will be saved to.
    /// 
    /// This property allows you to redefine how the font file names are generated
    /// during export to HTML.
    /// 
    /// When the event is fired, this property contains the file name that was generated
    /// by %Aspose.Words. You can change the value of this property to save the font into a
    /// different file. Note that file names must be unique.
    /// 
    /// %Aspose.Words automatically generates a unique file name for every embedded font when
    /// exporting to HTML format. How the font file name is generated
    /// depends on whether you save the document to a file or to a stream.
    /// 
    /// When saving a document to a file, the generated font file name looks like
    /// <i>%\<document base file name\>.\<original file name\>\<optional suffix\>.\<extension\></i>.
    /// 
    /// When saving a document to a stream, the generated font file name looks like
    /// <i>%Aspose.Words.\<document guid\>.\<original file name\>\<optional suffix\>.\<extension\></i>.
    /// 
    /// <see cref="Aspose::Words::Saving::FontSavingArgs::get_FontFileName">FontFileName</see> must contain only the file name without the path.
    /// %Aspose.Words determines the path for saving using the document file name,
    /// the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder">FontsFolder</see> and
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias">FontsFolderAlias</see> properties.
    /// 
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_FontStream
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_FontsFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_FontFileName() const;
    /// Setter for Aspose::Words::Saving::FontSavingArgs::get_FontFileName
    ASPOSE_WORDS_SHARED_API void set_FontFileName(const System::String& value);
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving a font.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::FontSavingArgs::get_FontStream">FontStream</see> property after writing a font into it.
    /// Specify <c>%true</c> to keep the stream open.
    /// 
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_FontStream
    ASPOSE_WORDS_SHARED_API bool get_KeepFontStreamOpen() const;
    /// Setter for Aspose::Words::Saving::FontSavingArgs::get_KeepFontStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepFontStreamOpen(bool value);
    /// Allows to specify the stream where the font will be saved to.
    /// 
    /// This property allows you to save fonts to streams instead of files during HTML export.
    /// 
    /// The default value is <c>%null</c>. When this property is <c>%null</c>, the font
    /// will be saved to a file specified in the <see cref="Aspose::Words::Saving::FontSavingArgs::get_FontFileName">FontFileName</see> property.
    /// 
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_FontFileName
    /// @sa Aspose::Words::Saving::FontSavingArgs::get_KeepFontStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_FontStream() const;
    /// Setter for Aspose::Words::Saving::FontSavingArgs::get_FontStream
    ASPOSE_WORDS_SHARED_API void set_FontStream(const System::SharedPtr<System::IO::Stream>& value);

    template <typename CharType, typename Traits>
    void set_FontStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_FontStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::String mField5;
    __TypeStub<4,4,4,4>::type mField6;
    __TypeStub<1,1,1,1>::type mField7;
    __TypeStub<1,1,1,1>::type mField8;
    System::String mField9;
    __TypeStub<1,1,1,1>::type mField10;

};

}
}
}
