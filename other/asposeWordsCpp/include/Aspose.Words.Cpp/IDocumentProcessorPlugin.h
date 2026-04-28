//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IDocumentProcessorPlugin.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
class ImageWatermarkOptions;
namespace Loading
{
class LoadOptions;
}
namespace Saving
{
class FixedPageSaveOptions;
class SaveOptions;
}
class TextWatermarkOptions;
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

/// \interface IDocumentProcessorPlugin
/// Defines an interface for external document processor plugin.
class ASPOSE_WORDS_SHARED_CLASS IDocumentProcessorPlugin : public virtual System::Object
{
    typedef IDocumentProcessorPlugin ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Load the document using the specified load options.
    /// 
    /// @param inputStream The input stream.
    /// @param loadOptions The document load options. Can be <c>%null</c>, in this case the document is loaded with default load options.
    virtual void Load(System::SharedPtr<System::IO::Stream> inputStream, System::SharedPtr<Aspose::Words::Loading::LoadOptions> loadOptions) = 0;
    /// Append the document loading it with the specified load options.
    /// 
    /// @param inputStream The input stream.
    /// @param loadOptions The document load options. Can be <c>%null</c>, in this case the document is loaded with default load options.
    virtual void Append(System::SharedPtr<System::IO::Stream> inputStream, System::SharedPtr<Aspose::Words::Loading::LoadOptions> loadOptions) = 0;
    /// Save the document loaded by <see cref="Aspose::Words::IDocumentProcessorPlugin::Load(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Loading::LoadOptions>)">Load()</see> method to the output stream using the specified save options.
    /// 
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    virtual void Save(System::SharedPtr<System::IO::Stream> outputStream, System::SharedPtr<Aspose::Words::Saving::SaveOptions> saveOptions) = 0;
    /// Saves each page of the document loaded by <see cref="Aspose::Words::IDocumentProcessorPlugin::Load(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Loading::LoadOptions>)">Load()</see> method using the specified fixed page save options.
    virtual System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ToPages(System::SharedPtr<Aspose::Words::Saving::FixedPageSaveOptions> saveOptions) = 0;
    /// Adds text watermark on each page of the document loaded by <see cref="Aspose::Words::IDocumentProcessorPlugin::Load(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Loading::LoadOptions>)">Load()</see> method.
    /// 
    /// @param textWatermark Text used as a watermark.
    /// @param textWatermarkOptions Text watermark options.
    virtual void SetTextWatermark(System::String textWatermark, System::SharedPtr<Aspose::Words::TextWatermarkOptions> textWatermarkOptions) = 0;
    /// Adds image watermark on each page of the document loaded by <see cref="Aspose::Words::IDocumentProcessorPlugin::Load(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Loading::LoadOptions>)">Load()</see> method.
    /// 
    /// @param imageWatermark Image used as a watermark.
    /// @param imageWatermarkOptions Image watermark options.
    virtual void SetImageWatermark(System::SharedPtr<System::IO::Stream> imageWatermark, System::SharedPtr<Aspose::Words::ImageWatermarkOptions> imageWatermarkOptions) = 0;
    /// Parses the document loaded by <see cref="Aspose::Words::IDocumentProcessorPlugin::Load(System::SharedPtr<System::IO::Stream>, System::SharedPtr<Aspose::Words::Loading::LoadOptions>)">Load()</see> method into <see cref="Aspose::Words::Document">Document</see> object.
    virtual System::SharedPtr<Aspose::Words::Document> ToDocument() = 0;

};

}
}
