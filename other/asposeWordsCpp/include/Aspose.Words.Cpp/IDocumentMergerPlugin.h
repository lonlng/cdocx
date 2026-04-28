//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IDocumentMergerPlugin.h
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

/// \interface IDocumentMergerPlugin
/// Defines an interface for external merger plugin that can merge Pdf documents.
class ASPOSE_WORDS_SHARED_CLASS IDocumentMergerPlugin : public virtual System::Object
{
    typedef IDocumentMergerPlugin ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Merges the given input PDF documents into a single output PDF document using specified input and output streams.
    /// 
    /// @param outputStream The output stream.
    /// @param inputStreams The input streams.
    /// @param loadOptions Load options for the input files.
    virtual void Merge(System::SharedPtr<System::IO::Stream> outputStream, System::ArrayPtr<System::SharedPtr<System::IO::Stream>> inputStreams, System::ArrayPtr<System::SharedPtr<Aspose::Words::Loading::LoadOptions>> loadOptions) = 0;

};

}
}
