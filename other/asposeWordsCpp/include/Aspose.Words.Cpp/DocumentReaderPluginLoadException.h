//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DocumentReaderPluginLoadException.h
#pragma once

#include <system/exceptions.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace RW
{
namespace Pdf
{
namespace Reader
{
class PdfReader;
}
}
}
}
}
namespace System
{
namespace Runtime
{
namespace Serialization
{
class SerializationInfo;
class StreamingContext;
}
}
class String;
}

namespace Aspose {

namespace Words {

class Details_DocumentReaderPluginLoadException;
/// Thrown during document load, when the plugin required for reading the document format cannot be loaded.
using DocumentReaderPluginLoadException = System::ExceptionWrapper<Details_DocumentReaderPluginLoadException>;

/// Thrown during document load, when the plugin required for reading the document format cannot be loaded.
class ASPOSE_WORDS_SHARED_CLASS Details_DocumentReaderPluginLoadException : public System::Details_Exception
{
    typedef Details_DocumentReaderPluginLoadException ThisType;
    typedef System::Details_Exception BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;

protected:

    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    Details_DocumentReaderPluginLoadException(const System::String& message);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_DocumentReaderPluginLoadException, CODEPORTING_ARGS(const System::String& message));

    Details_DocumentReaderPluginLoadException(const System::String& message, System::Exception innerException);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_DocumentReaderPluginLoadException, CODEPORTING_ARGS(const System::String& message, System::Exception innerException));

    ASPOSE_WORDS_SHARED_API Details_DocumentReaderPluginLoadException(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context);

    ASPOSE_WORDS_SHARED_API MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_DocumentReaderPluginLoadException, CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context));

};

}
}
