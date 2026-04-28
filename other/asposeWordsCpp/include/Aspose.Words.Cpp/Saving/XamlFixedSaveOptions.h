//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/XamlFixedSaveOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/Saving/FixedPageSaveOptions.h>
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

namespace Aspose {

namespace Words {

namespace Saving {

/// Can be used to specify additional options when saving a document into the <see cref="Aspose::Words::SaveFormat::XamlFixed">XamlFixed</see> format.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/specify-save-options/">Specify Save Options</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS XamlFixedSaveOptions : public Aspose::Words::Saving::FixedPageSaveOptions
{
    typedef XamlFixedSaveOptions ThisType;
    typedef Aspose::Words::Saving::FixedPageSaveOptions BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::XamlFixed">XamlFixed</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::SaveFormat get_SaveFormat() override;
    /// Specifies the format in which the document will be saved if this save options object is used.
    /// Can only be <see cref="Aspose::Words::SaveFormat::XamlFixed">XamlFixed</see>.
    ASPOSE_WORDS_SHARED_API void set_SaveFormat(Aspose::Words::SaveFormat value) override;
    /// Specifies the physical folder where resources (images and fonts) are saved when exporting a document to fixed page Xaml format.
    /// Default is <c>%null</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in fixed page Xaml format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// If you save a document into a file and provide a file name, %Aspose.Words, by default, saves the
    /// images in the same folder where the document file is saved. Use <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// to override this behavior.
    /// 
    /// If you save a document into a stream, %Aspose.Words does not have a folder where to save the images,
    /// but still needs to save the images somewhere. In this case, you need to specify an accessible folder
    /// by using the <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see> property
    /// 
    /// @sa Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolder() const;
    /// Setter for Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolder(const System::String& value);
    /// Specifies the name of the folder used to construct image URIs written into an fixed page Xaml document.
    /// Default is <c>%null</c>.
    /// 
    /// When you save a <see cref="Aspose::Words::Document">Document</see> in fixed page Xaml format, %Aspose.Words needs to save all
    /// images embedded in the document as standalone files. <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// allows you to specify where the images will be saved and <see cref="Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// allows to specify how the image URIs will be constructed.
    /// 
    /// @sa Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolder
    ASPOSE_WORDS_SHARED_API System::String get_ResourcesFolderAlias() const;
    /// Setter for Aspose::Words::Saving::XamlFixedSaveOptions::get_ResourcesFolderAlias
    ASPOSE_WORDS_SHARED_API void set_ResourcesFolderAlias(const System::String& value);
    /// Allows to control how resources (images and fonts) are saved when a document is exported to fixed page Xaml format.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback> get_ResourceSavingCallback() const;
    /// Allows to control how resources (images and fonts) are saved when a document is exported to fixed page Xaml format.
    ASPOSE_WORDS_SHARED_API void set_ResourceSavingCallback(const System::SharedPtr<Aspose::Words::Saving::IResourceSavingCallback>& value);

protected:

private:

    System::String mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
