//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/UnsupportedFileFormatException.h
#pragma once

#include <system/exceptions.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace DigitalSignatures
{
class DigitalSignatureUtil;
}
namespace RW
{
namespace Doc
{
namespace Reader
{
class DocReaderCore;
}
}
namespace Factories
{
class ReaderFactory;
}
namespace Mobi
{
namespace Reader
{
class MobiDocumentReaderBase;
}
}
namespace OfficeCrypto
{
class DataSpaces;
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

class Details_UnsupportedFileFormatException;
/// Thrown during document load, when the document format is not recognized or not supported by Aspose.Words.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
using UnsupportedFileFormatException = System::ExceptionWrapper<Details_UnsupportedFileFormatException>;

/// Thrown during document load, when the document format is not recognized or not supported by Aspose.Words.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/programming-with-documents/">Programming with Documents</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS Details_UnsupportedFileFormatException : public System::Details_Exception
{
    typedef Details_UnsupportedFileFormatException ThisType;
    typedef System::Details_Exception BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

    friend class Aspose::Words::RW::Mobi::Reader::MobiDocumentReaderBase;
    friend class Aspose::Words::RW::Factories::ReaderFactory;
    friend class Aspose::Words::DigitalSignatures::DigitalSignatureUtil;
    friend class Aspose::Words::RW::OfficeCrypto::DataSpaces;
    friend class Aspose::Words::RW::Doc::Reader::DocReaderCore;
    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;

protected:

    [[noreturn]] void DoThrow(const System::ExceptionPtr& self) const override;

    Details_UnsupportedFileFormatException(const System::String& message);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedFileFormatException, CODEPORTING_ARGS(const System::String& message));

    Details_UnsupportedFileFormatException(const System::String& message, System::Exception innerException);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedFileFormatException, CODEPORTING_ARGS(const System::String& message, System::Exception innerException));

    Details_UnsupportedFileFormatException(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context);

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedFileFormatException, CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context));

};

}
}
