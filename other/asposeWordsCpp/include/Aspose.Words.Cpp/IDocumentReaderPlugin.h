//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/IDocumentReaderPlugin.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Document;
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

/// \interface IDocumentReaderPlugin
/// Defines an interface for external reader plugins that can read a file into a document.
class ASPOSE_WORDS_SHARED_CLASS IDocumentReaderPlugin : public virtual System::Object
{
    typedef IDocumentReaderPlugin ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Reads the data from the specified stream into the <see cref="Aspose::Words::Document">Document</see> instance.
    /// 
    /// @param src The source stream to read the document from.
    /// @param loadOptions An additional load options to load the document.
    /// @param document The instance of the <see cref="Aspose::Words::Document">Document</see> class to read the data to.
    ///     If the instance contains some content, it will be overridden by the data from the source stream
    virtual void Read(System::SharedPtr<System::IO::Stream> src, System::SharedPtr<Aspose::Words::Loading::LoadOptions> loadOptions, System::SharedPtr<Aspose::Words::Document> document) = 0;

};

}
}
