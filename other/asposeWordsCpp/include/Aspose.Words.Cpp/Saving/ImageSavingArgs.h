//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ImageSavingArgs.h
#pragma once

#include <system/string.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
namespace Drawing
{
class ShapeBase;
}

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

/// Provides data for the <see cref="Aspose::Words::Saving::IImageSavingCallback::ImageSaving(System::SharedPtr<Aspose::Words::Saving::ImageSavingArgs>)">ImageSaving()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
/// 
/// By default, when %Aspose.Words saves a document to HTML, it saves each image into
/// a separate file. %Aspose.Words uses the document file name and a unique number to generate unique file name
/// for each image found in the document.
/// 
/// <see cref="Aspose::Words::Saving::ImageSavingArgs">ImageSavingArgs</see> allows to redefine how image file names are generated or to
/// completely circumvent saving of images into files by providing your own stream objects.
/// 
/// To apply your own logic for generating image file names use the
/// <see cref="Aspose::Words::Saving::ImageSavingArgs::get_ImageFileName">ImageFileName</see>, <see cref="Aspose::Words::Saving::ImageSavingArgs::get_CurrentShape">CurrentShape</see> and <see cref="Aspose::Words::Saving::ImageSavingArgs::get_IsImageAvailable">IsImageAvailable</see>
/// properties.
/// 
/// To save images into streams instead of files, use the <see cref="Aspose::Words::Saving::ImageSavingArgs::get_ImageStream">ImageStream</see> property.
class ASPOSE_WORDS_SHARED_CLASS ImageSavingArgs : public System::Object
{
    typedef ImageSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the document object that is currently being saved.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document();
    /// Gets the <see cref="Aspose::Words::Drawing::ShapeBase">ShapeBase</see> object corresponding to the shape or group shape
    /// that is about to be saved.
    /// 
    /// <see cref="Aspose::Words::Saving::IImageSavingCallback">IImageSavingCallback</see> can be fired while saving either a shape or a group shape.
    /// That's why the property has <see cref="Aspose::Words::Drawing::ShapeBase">ShapeBase</see> type. You can check whether it's a group shape comparing
    /// <see cref="Aspose::Words::Drawing::ShapeBase::get_ShapeType">ShapeType</see> with <see cref="Aspose::Words::Drawing::ShapeType::Group">Group</see> or by casting it to one of derived classes:
    /// <see cref="Aspose::Words::Drawing::Shape">Shape</see> or <see cref="Aspose::Words::Drawing::GroupShape">GroupShape</see>.
    /// 
    /// %Aspose.Words uses the document file name and a unique number to generate unique file name
    /// for each image found in the document. You can use the <see cref="Aspose::Words::Saving::ImageSavingArgs::get_CurrentShape">CurrentShape</see> property to generate
    /// a "better" file name by examining shape properties such as <see cref="Aspose::Words::Drawing::ImageData::get_Title">Title</see>
    /// (Shape only), <see cref="Aspose::Words::Drawing::ImageData::get_SourceFullName">SourceFullName</see> (Shape only)
    /// and <see cref="Aspose::Words::Drawing::ShapeBase::get_Name">Name</see>. Of course you can build file names using any other properties or criteria
    /// but note that subsidiary file names must be unique within the export operation.
    /// 
    /// Some images in the document can be unavailable. To check image availability
    /// use the <see cref="Aspose::Words::Saving::ImageSavingArgs::get_IsImageAvailable">IsImageAvailable</see> property.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Drawing::ShapeBase> get_CurrentShape() const;
    /// Returns <c>%true</c> if the current image is available for export.
    /// 
    /// Some images in the document can be unavailable, for example, because the image
    /// is linked and the link is inaccessible or does not point to a valid image.
    /// In this case %Aspose.Words exports an icon with a red cross. This property returns
    /// <c>%true</c> if the original image is available; returns <c>%false</c> if the original
    /// image is not available and a "no image" icon will be offered for save.
    /// 
    /// When saving a group shape or a shape that doesn't require any image this property
    /// is always <c>%true</c>.
    /// 
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_CurrentShape
    ASPOSE_WORDS_SHARED_API bool get_IsImageAvailable() const;
    /// Gets or sets the file name (without path) where the image will be saved to.
    /// 
    /// This property allows you to redefine how the image file names are generated
    /// during export to HTML.
    /// 
    /// When the event is fired, this property contains the file name that was generated
    /// by %Aspose.Words. You can change the value of this property to save the image into a
    /// different file. Note that file names must be unique.
    /// 
    /// %Aspose.Words automatically generates a unique file name for every embedded image when
    /// exporting to HTML format. How the image file name is generated
    /// depends on whether you save the document to a file or to a stream.
    /// 
    /// When saving a document to a file, the generated image file name looks like
    /// <i>%\<document base file name\>.\<image number\>.\<extension\></i>.
    /// 
    /// When saving a document to a stream, the generated image file name looks like
    /// <i>%Aspose.Words.\<document guid\>.\<image number\>.\<extension\></i>.
    /// 
    /// <see cref="Aspose::Words::Saving::ImageSavingArgs::get_ImageFileName">ImageFileName</see> must contain only the file name without the path.
    /// %Aspose.Words determines the path for saving and the value of the <c>%src</c> attribute for writing
    /// to HTML using the document file name, the <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder">ImagesFolder</see> and
    /// <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> properties.
    /// 
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_CurrentShape
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_IsImageAvailable
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_ImageStream
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolder
    /// @sa Aspose::Words::Saving::HtmlSaveOptions::get_ImagesFolderAlias
    ASPOSE_WORDS_SHARED_API System::String get_ImageFileName() const;
    /// Setter for Aspose::Words::Saving::ImageSavingArgs::get_ImageFileName
    ASPOSE_WORDS_SHARED_API void set_ImageFileName(const System::String& value);
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving an image.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::ImageSavingArgs::get_ImageStream">ImageStream</see> property after writing an image into it.
    /// Specify <c>%true</c> to keep the stream open.
    /// 
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_ImageStream
    ASPOSE_WORDS_SHARED_API bool get_KeepImageStreamOpen() const;
    /// Setter for Aspose::Words::Saving::ImageSavingArgs::get_KeepImageStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepImageStreamOpen(bool value);
    /// Allows to specify the stream where the image will be saved to.
    /// 
    /// This property allows you to save images to streams instead of files during HTML.
    /// 
    /// The default value is <c>%null</c>. When this property is <c>%null</c>, the image
    /// will be saved to a file specified in the <see cref="Aspose::Words::Saving::ImageSavingArgs::get_ImageFileName">ImageFileName</see> property.
    /// 
    /// Using <see cref="Aspose::Words::Saving::IImageSavingCallback">IImageSavingCallback</see> you cannot substitute one image with
    /// another. It is intended only for control over location where to save images.
    /// 
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_ImageFileName
    /// @sa Aspose::Words::Saving::ImageSavingArgs::get_KeepImageStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_ImageStream() const;
    /// Setter for Aspose::Words::Saving::ImageSavingArgs::get_ImageStream
    ASPOSE_WORDS_SHARED_API void set_ImageStream(const System::SharedPtr<System::IO::Stream>& value);

    template <typename CharType, typename Traits>
    void set_ImageStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_ImageStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    System::String mField3;
    __TypeStub<1,1,1,1>::type mField4;

};

}
}
}
