//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PageSavingArgs.h
#pragma once

#include <system/string.h>
#include <system/io/std_stream_wrappers.h>
#include <iostream>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

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

/// Provides data for the <see cref="Aspose::Words::Saving::IPageSavingCallback::PageSaving(System::SharedPtr<Aspose::Words::Saving::PageSavingArgs>)">PageSaving()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PageSavingArgs : public System::Object
{
    typedef PageSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Allows to specify the stream where the document page will be saved to.
    /// 
    /// This property allows you to save document pages to streams instead of files.
    /// 
    /// The default value is <c>%null</c>. When this property is <c>%null</c>, the document page
    /// will be saved to a file specified in the <see cref="Aspose::Words::Saving::PageSavingArgs::get_PageFileName">PageFileName</see> property.
    /// 
    /// If both <see cref="Aspose::Words::Saving::PageSavingArgs::get_PageStream">PageStream</see> and <see cref="Aspose::Words::Saving::PageSavingArgs::get_PageFileName">PageFileName</see> are set, then PageStream will be used.
    /// 
    /// @sa Aspose::Words::Saving::PageSavingArgs::get_PageFileName
    /// @sa Aspose::Words::Saving::PageSavingArgs::get_KeepPageStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_PageStream() const;
    /// Setter for Aspose::Words::Saving::PageSavingArgs::get_PageStream
    ASPOSE_WORDS_SHARED_API void set_PageStream(const System::SharedPtr<System::IO::Stream>& value);
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving a document page.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::PageSavingArgs::get_PageStream">PageStream</see> property after writing a document page into it.
    /// Specify <c>%true</c> to keep the stream open.
    /// 
    /// @sa Aspose::Words::Saving::PageSavingArgs::get_PageStream
    ASPOSE_WORDS_SHARED_API bool get_KeepPageStreamOpen() const;
    /// Setter for Aspose::Words::Saving::PageSavingArgs::get_KeepPageStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepPageStreamOpen(bool value);
    /// Gets the file name where the document page will be saved to.
    ASPOSE_WORDS_SHARED_API System::String get_PageFileName() const;
    /// Sets the file name where the document page will be saved to.
    ASPOSE_WORDS_SHARED_API void set_PageFileName(const System::String& value);
    /// Current page index.
    ASPOSE_WORDS_SHARED_API int32_t get_PageIndex() const;

    ASPOSE_WORDS_SHARED_API PageSavingArgs();

    template <typename CharType, typename Traits>
    void set_PageStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_PageStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    __TypeStub<4,4,4,4>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;

};

}
}
}
