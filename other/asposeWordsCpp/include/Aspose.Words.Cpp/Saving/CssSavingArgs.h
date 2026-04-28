//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/CssSavingArgs.h
#pragma once

#include <system/object.h>
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

/// Provides data for the <see cref="Aspose::Words::Saving::ICssSavingCallback::CssSaving(System::SharedPtr<Aspose::Words::Saving::CssSavingArgs>)">CssSaving()</see> event.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
/// 
/// By default, when %Aspose.Words saves a document to HTML, it saves CSS information inline
/// (as a value of the <b>%style</b> attribute on every element).
/// 
/// <see cref="Aspose::Words::Saving::CssSavingArgs">CssSavingArgs</see> allows to save CSS information into file by providing your own stream object.
/// 
/// To save CSS into stream, use the <see cref="Aspose::Words::Saving::CssSavingArgs::get_CssStream">CssStream</see> property.
/// 
/// To suppress saving CSS into a file and embedding to HTML document use the <see cref="Aspose::Words::Saving::CssSavingArgs::get_IsExportNeeded">IsExportNeeded</see> property.
class ASPOSE_WORDS_SHARED_CLASS CssSavingArgs : public System::Object
{
    typedef CssSavingArgs ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the document object that is currently being saved.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Document> get_Document() const;
    /// Specifies whether %Aspose.Words should keep the stream open or close it after saving an CSS information.
    /// 
    /// Default is <c>%false</c> and %Aspose.Words will close the stream you provided
    /// in the <see cref="Aspose::Words::Saving::CssSavingArgs::get_CssStream">CssStream</see> property after writing an CSS information into it.
    /// Specify <c>%true</c> to keep the stream open.
    /// 
    /// @sa Aspose::Words::Saving::CssSavingArgs::get_CssStream
    ASPOSE_WORDS_SHARED_API bool get_KeepCssStreamOpen() const;
    /// Setter for Aspose::Words::Saving::CssSavingArgs::get_KeepCssStreamOpen
    ASPOSE_WORDS_SHARED_API void set_KeepCssStreamOpen(bool value);
    /// Allows to specify the stream where the CSS information will be saved to.
    /// 
    /// This property allows you to save CSS information to a stream.
    /// 
    /// The default value is <c>%null</c>. This property doesn't suppress saving CSS information to a file or
    /// embedding to HTML document. To suppress exporting CSS use the <see cref="Aspose::Words::Saving::CssSavingArgs::get_IsExportNeeded">IsExportNeeded</see> property.
    /// 
    /// Using <see cref="Aspose::Words::Saving::ICssSavingCallback">ICssSavingCallback</see> you cannot substitute CSS with
    /// another. It is intended only for saving CSS to a stream.
    /// 
    /// @sa Aspose::Words::Saving::CssSavingArgs::get_KeepCssStreamOpen
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::IO::Stream> get_CssStream() const;
    /// Setter for Aspose::Words::Saving::CssSavingArgs::get_CssStream
    ASPOSE_WORDS_SHARED_API void set_CssStream(const System::SharedPtr<System::IO::Stream>& value);
    /// Allows to specify whether the CSS will be exported to file and embedded to HTML document. Default is <c>%true</c>.
    /// When this property is <c>%false</c>, the CSS information will not be saved to a CSS file and will not be embedded to HTML document.
    ASPOSE_WORDS_SHARED_API bool get_IsExportNeeded() const;
    /// Allows to specify whether the CSS will be exported to file and embedded to HTML document. Default is <c>%true</c>.
    /// When this property is <c>%false</c>, the CSS information will not be saved to a CSS file and will not be embedded to HTML document.
    ASPOSE_WORDS_SHARED_API void set_IsExportNeeded(bool value);

    template <typename CharType, typename Traits>
    void set_CssStream(std::basic_ostream<CharType, Traits>& value)
    {
        auto valueWrapper = System::IO::WrapSTDIOStream(value);
        set_CssStream(valueWrapper);
    }

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    __TypeStub<1,1,1,1>::type mField2;
    __TypeStub<1,1,1,1>::type mField3;

};

}
}
}
