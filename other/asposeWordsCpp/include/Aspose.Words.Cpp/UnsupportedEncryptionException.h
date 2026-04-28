//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/UnsupportedEncryptionException.h
#pragma once

#include <system/exceptions.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

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

class Details_UnsupportedEncryptionException;
/// Thrown during document load, when the document is encrypted with an unsupported method.
using UnsupportedEncryptionException = System::ExceptionWrapper<Details_UnsupportedEncryptionException>;

/// Thrown during document load, when the document is encrypted with an unsupported method.
class ASPOSE_WORDS_SHARED_CLASS Details_UnsupportedEncryptionException : public System::Details_Exception
{
    typedef Details_UnsupportedEncryptionException ThisType;
    typedef System::Details_Exception BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

    friend class System::ExceptionWrapperHelper;
    template <typename T> friend class System::ExceptionWrapper;

protected:

    [[noreturn]] void DoThrow(const System::ExceptionPtr& ) const override;

    Details_UnsupportedEncryptionException(const System::String& );

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedEncryptionException, CODEPORTING_ARGS(const System::String& message));

    Details_UnsupportedEncryptionException(const System::String& , System::Exception );

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedEncryptionException, CODEPORTING_ARGS(const System::String& message, System::Exception innerException));

    Details_UnsupportedEncryptionException(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& , System::Runtime::Serialization::StreamingContext );

    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(Details_UnsupportedEncryptionException, CODEPORTING_ARGS(const System::SharedPtr<System::Runtime::Serialization::SerializationInfo>& info, System::Runtime::Serialization::StreamingContext context));

};

}
}
