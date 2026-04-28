//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DocumentPartSavingArgs.h
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

/// Provides data for the <see cref="Aspose::Words::Saving::IDocumentPartSavingCallback::DocumentPartSaving(System::SharedPtr<Aspose::Words::Saving::DocumentPartSavingArgs>)">DocumentPartSaving()</see> callback.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
/// 
/// When %Aspose.Words saves a document to HTML or related formats and <see cref="Aspose::Words::Saving::HtmlSaveOptions::get_DocumentSplitCriteria">DocumentSplitCriteria</see>
/// is specified, the document is split into parts and by default, each document part is saved into a separate file.
/// 
/// Class <see cref="Aspose::Words::Saving::DocumentPartSavingArgs">DocumentPartSavingArgs</see> allows you to control how each document part will be saved.
/// It allows to redefine how file names are generated or to completely circumvent saving of document parts into
/// files by providing your own stream objects.
/// 
/// To save document parts into streams instead of files, use the <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream">DocumentPartStream</see> property.
class ASPOSE_WORDS_SHARED_CLASS DocumentPartSavingArgs : public System::Object
{
    typedef DocumentPartSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the document object that is being saved.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;
    /// Gets or sets the file name (without path) where the document part will be saved to.
    /// 
    /// This property allows you to redefine how the document part file names are generated
    /// during export to HTML or EPUB.
    /// 
    /// When the callback is invoked, this property contains the file name that was generated
    /// by %Aspose.Words. You can change the value of this property to save the document part into a
    /// different file. Note that the file name for each part must be unique.
    /// 
    /// <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartFileName">DocumentPartFileName</see> must contain only the file name without the path.
    /// %Aspose.Words determines the path for saving using the document file name. If output document
    /// file name was not specified, for instance when saving to a stream, this file name is used only
    /// for referencing document parts. The same is true when saving to EPUB format.
    /// 
    /// @sa Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream
    ASPOSE_WORDS_SHARED_API System::String get_DocumentPartFileName() const;
    /// Setter for Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartFileName
    ASPOSE_WORDS_SHARED_API void set_DocumentPartFileName(const System::String& value);
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving a document part.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream">DocumentPartStream</see> property after writing a document part into it.
    /// Specify <c>%true</c> to keep the stream open. Please note that the main output stream
    /// provided in the call to <see cref="Aspose::Words::Document::Save(System::SharedPtr<System::IO::Stream>, Aspose::Words::SaveFormat)">Save()</see> or
    /// <see cref="Aspose::Words::Document::Save(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Saving::SaveOptions>)">Save()</see> will never be closed by %Aspose.Words
    /// even if <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_KeepDocumentPartStreamOpen">KeepDocumentPartStreamOpen</see> is set to <c>%false</c>.
    /// 
    /// @sa Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream
    ASPOSE_WORDS_SHARED_API bool get_KeepDocumentPartStreamOpen() const;
    /// Setter for Aspose::Words::Saving::DocumentPartSavingArgs::get_KeepDocumentPartStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepDocumentPartStreamOpen(bool value);
    /// Allows to specify the stream where the document part will be saved to.
    /// 
    /// This property allows you to save document parts to streams instead of files during HTML export.
    /// 
    /// The default value is <c>%null</c>. When this property is <c>%null</c>, the document part
    /// will be saved to a file specified in the <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartFileName">DocumentPartFileName</see> property.
    /// 
    /// When saving to a stream in HTML format is requested by <see cref="Aspose::Words::Document::Save(System::SharedPtr<System::IO::Stream>, Aspose::Words::SaveFormat)">Save()</see>
    /// or <see cref="Aspose::Words::Document::Save(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Saving::SaveOptions>)">Save()</see> and first document part is about to be saved,
    /// %Aspose.Words suggests here the main output stream initially passed by the caller.
    /// 
    /// When saving to EPUB format that is a container format based on HTML, <see cref="Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream">DocumentPartStream</see> cannot
    /// be specified because all subsidiary parts will be encapsulated into a single output package.
    /// 
    /// @sa Aspose::Words::Saving::DocumentPartSavingArgs::get_KeepDocumentPartStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_DocumentPartStream() const;
    /// Setter for Aspose::Words::Saving::DocumentPartSavingArgs::get_DocumentPartStream
    ASPOSE_WORDS_SHARED_API void set_DocumentPartStream(const System::SharedPtr<System::IO::Stream>& value);

    template <typename CharType, typename Traits>
    void set_DocumentPartStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_DocumentPartStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;

};

}
}
}
