//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/ResourceSavingArgs.h
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

/// Provides data for the <see cref="Aspose::Words::Saving::IResourceSavingCallback::ResourceSaving(System::SharedPtr<Aspose::Words::Saving::ResourceSavingArgs>)">ResourceSaving()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
/// 
/// By default, when %Aspose.Words saves a document to fixed page HTML, SVG or Markdown, it saves each resource into
/// a separate file. %Aspose.Words uses the document file name and a unique number to generate unique file name
/// for each resource found in the document.
/// 
/// <see cref="Aspose::Words::Saving::ResourceSavingArgs">ResourceSavingArgs</see> allows to redefine how resource file names are generated or to
/// completely circumvent saving of resources into files by providing your own stream objects.
/// 
/// To apply your own logic for generating resource file names use the
/// <see cref="Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileName">ResourceFileName</see> property.
/// 
/// To save resources into streams instead of files, use the <see cref="Aspose::Words::Saving::ResourceSavingArgs::get_ResourceStream">ResourceStream</see> property.
class ASPOSE_WORDS_SHARED_CLASS ResourceSavingArgs : public System::Object
{
    typedef ResourceSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the document object that is currently being saved.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;
    /// Gets or sets the file name (without path) where the resource will be saved to.
    /// 
    /// This property allows you to redefine how the resource file names are generated
    /// during export to fixed page HTML, SVG or Markdown.
    /// 
    /// When the event is fired, this property contains the file name that was generated
    /// by %Aspose.Words. You can change the value of this property to save the resource into a
    /// different file. Note that file names must be unique.
    /// 
    /// %Aspose.Words automatically generates a unique file name for every resource when
    /// exporting to fixed page HTML, SVG or Markdown format. How the resource file name is generated
    /// depends on whether you save the document to a file or to a stream.
    /// 
    /// When saving a document to a file, the generated resource file name looks like
    /// <i>%\<document base file name\>.\<image number\>.\<extension\></i>.
    /// 
    /// When saving a document to a stream, the generated resource file name looks like
    /// <i>%Aspose.Words.\<document guid\>.\<image number\>.\<extension\></i>.
    /// 
    /// <see cref="Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileName">ResourceFileName</see> must contain only the file name without the path.
    /// %Aspose.Words determines the path for saving and the value of the <c>%src</c> attribute for writing
    /// to fixed page HTML, SVG or Markdown using the document file name, the <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolder">ResourcesFolder</see>
    /// or <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolder">ResourcesFolder</see> and <see cref="Aspose::Words::Saving::HtmlFixedSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see>
    /// or <see cref="Aspose::Words::Saving::SvgSaveOptions::get_ResourcesFolderAlias">ResourcesFolderAlias</see> or <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolder">ImagesFolder</see> or
    /// <see cref="Aspose::Words::Saving::MarkdownSaveOptions::get_ImagesFolderAlias">ImagesFolderAlias</see> properties.
    /// 
    /// @sa Aspose::Words::Saving::ResourceSavingArgs::get_ResourceStream
    ASPOSE_WORDS_SHARED_API System::String get_ResourceFileName() const;
    /// Setter for Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileName
    ASPOSE_WORDS_SHARED_API void set_ResourceFileName(const System::String& value);
    /// Gets or sets the uniform resource identifier (URI) used to reference the resource file from the document.
    /// 
    /// This property allows you to change URIs of resource files exported to fixed page HTML,
    /// SVG or Markdown documents.
    /// 
    /// %Aspose.Words automatically generates an URI for every resource file during export to fixed page HTML,
    /// SVG or Markdown format. The generated URIs reference resource files saved by %Aspose.Words. However, the URIs
    /// can be incorrect if resource files are to be moved to other location or if resource files are saved to streams.
    /// This property allows to correct URIs in these cases.
    /// 
    /// When the event is fired, this property contains the URI that was generated
    /// by %Aspose.Words. You can change the value of this property to provide a custom URI for the resource file.
    ASPOSE_WORDS_SHARED_API System::String get_ResourceFileUri() const;
    /// Setter for Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileUri
    ASPOSE_WORDS_SHARED_API void set_ResourceFileUri(const System::String& value);
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving a resource.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::ResourceSavingArgs::get_ResourceStream">ResourceStream</see> property after writing a resource into it.
    /// Specify <c>%true</c> to keep the stream open.
    /// 
    /// @sa Aspose::Words::Saving::ResourceSavingArgs::get_ResourceStream
    ASPOSE_WORDS_SHARED_API bool get_KeepResourceStreamOpen() const;
    /// Setter for Aspose::Words::Saving::ResourceSavingArgs::get_KeepResourceStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepResourceStreamOpen(bool value);
    /// Allows to specify the stream where the resource will be saved to.
    /// 
    /// This property allows you to save resources to streams instead of files.
    /// 
    /// The default value is <c>%null</c>. When this property is <c>%null</c>, the resource
    /// will be saved to a file specified in the <see cref="Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileName">ResourceFileName</see> property.
    /// 
    /// Using <see cref="Aspose::Words::Saving::IResourceSavingCallback">IResourceSavingCallback</see> you cannot substitute one resource with
    /// another. It is intended only for control over location where to save resources.
    /// 
    /// @sa Aspose::Words::Saving::ResourceSavingArgs::get_ResourceFileName
    /// @sa Aspose::Words::Saving::ResourceSavingArgs::get_KeepResourceStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_ResourceStream() const;
    /// Setter for Aspose::Words::Saving::ResourceSavingArgs::get_ResourceStream
    ASPOSE_WORDS_SHARED_API void set_ResourceStream(const System::SharedPtr<System::IO::Stream>& value);

    template <typename CharType, typename Traits>
    void set_ResourceStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_ResourceStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;
    __TypeStub<1,1,1,1>::type mField4;
    System::SharedPtr<System::Object> mField5;

};

}
}
}
