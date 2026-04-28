//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IDocumentConverterPlugin.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Loading
{
class LoadOptions;
}
namespace Saving
{
class SaveOptions;
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

/// \interface IDocumentConverterPlugin
/// Defines an interface for external converter plugin.
class ASPOSE_WORDS_SHARED_CLASS IDocumentConverterPlugin : public virtual System::Object
{
    typedef IDocumentConverterPlugin ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Converts document using specified input output streams and save options.
    /// 
    /// @param inputStream The input stream.
    /// @param loadOptions The document load options.
    /// @param outputStream The output stream.
    /// @param saveOptions The save options.
    virtual void Convert(System::SharedPtr<System::IO::Stream> inputStream, System::SharedPtr<Aspose::Words::Loading::LoadOptions> loadOptions, System::SharedPtr<System::IO::Stream> outputStream, System::SharedPtr<Aspose::Words::Saving::SaveOptions> saveOptions) = 0;
    /// Converts pages from document from input stream to array of images.
    /// 
    /// @param inputStream The input stream.
    /// @param loadOptions The document load options.
    /// @param saveOptions The save options.
    /// 
    /// @return Array of page images streams.
    virtual System::ArrayPtr<System::SharedPtr<System::IO::Stream>> ConvertToImages(System::SharedPtr<System::IO::Stream> inputStream, System::SharedPtr<Aspose::Words::Loading::LoadOptions> loadOptions, System::SharedPtr<Aspose::Words::Saving::SaveOptions> saveOptions) = 0;

};

}
}
