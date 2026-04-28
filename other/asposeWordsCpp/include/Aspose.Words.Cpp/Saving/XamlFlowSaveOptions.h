//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/XamlFlowSaveOptions.h
#pragma once

#include <Aspose.Words.Cpp/Saving/SaveOptions.h>
#include <Aspose.Words.Cpp/SaveFormat.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Saving
{
class IImageSavingCallback;
}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the
/// <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see> or <see cref="Aspose::Words::SaveFormat::XamlFlowPack">XamlFlowPack</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS XamlFlowSaveOptions : public Aspose::Words::Saving::SaveOptions
{
    typedef XamlFlowSaveOptions ThisType;
    typedef Aspose::Words::Saving::SaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies the physical folder where images are saved when exporting a document to XAML format.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in XAML format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// images in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the images,
    /// but still needs to save the images somewhere. In this case, you need to specify an accessible folder
    /// in the <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder">ImagesFolder</see> property or provide custom streams via
    /// the <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImageSavingCallback">ImageSavingCallback</see> event handler.
    /// 
    /// @sa Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias
    /// @sa Aspose::Words::Saving::XamlFlowSaveOptions::get_ImageSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolder() const;
    /// Setter for Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder
    ASPOSE_WORDS_SHARED_API void set_ImagesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into an XAML document.
    /// Default is an empty string.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in XAML format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder">ImagesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is not an empty string, then the image URI written
    /// to XAML will be <i>%ImagesFolderAlias + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is an empty string, then the image URI written
    /// to XAML will be <i>%ImagesFolder + \<image file name\></i>.
    /// 
    /// If <see cref="Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> is set to '.' (dot), then the image file name
    /// will be written to XAML without path regardless of other options.
    /// 
    /// @sa Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolder
    /// @sa Aspose::Words::Saving::XamlFlowSaveOptions::get_ImageSavingCallback
    ASPOSE_WORDS_SHARED_API System::String get_ImagesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::XamlFlowSaveOptions::get_ImagesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ImagesFolderAlias(const System::String& value);
    /// Allows to control how images are saved when a document is saved to XAML.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback> get_ImageSavingCallback() const;
    /// Allows to control how images are saved when a document is saved to XAML.
    ASPOSE_WORDS_SHARED_API void set_ImageSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IImageSavingCallback>& value);
    /// Specifies whether backslash characters should be replaced with yen signs.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_ReplaceBackslashWithYenSign() const;
    /// Specifies whether backslash characters should be replaced with yen signs.
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_ReplaceBackslashWithYenSign(bool value);

    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see> format.
    ASPOSE_WORDS_SHARED_API XamlFlowSaveOptions();
    /// Initializes a new instance of this class that can be used to save a document in the <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see>
    /// or <see cref="Aspose::Words::SaveFormat::XamlFlowPack">XamlFlowPack</see> format.
    /// 
    /// @param saveFormat Can be <see cref="Aspose::Words::SaveFormat::XamlFlow">XamlFlow</see> or <see cref="Aspose::Words::SaveFormat::XamlFlowPack">XamlFlowPack</see>.
    ASPOSE_WORDS_SHARED_API XamlFlowSaveOptions(Aspose::Words::SaveFormat saveFormat);

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    System::String mField2;
    System::String mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
