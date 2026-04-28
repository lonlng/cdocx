//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/LowCode/SignerContext.h
#pragma once

#include <Aspose.Words.Cpp/LowCode/ProcessorContext.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace DigitalSignatures
{
class CertificateHolder;
class SignOptions;
}
}
}

namespace Aspose {

namespace Words {

namespace LowCode {

/// Document signer context
class ASPOSE_WORDS_SHARED_CLASS SignerContext : public Aspose::Words::LowCode::ProcessorContext
{
    typedef SignerContext ThisType;
    typedef Aspose::Words::LowCode::ProcessorContext BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// CertificateHolder object with certificate that used to sign file.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& get_CertificateHolder() const;
    /// CertificateHolder object with certificate that used to sign file.
    ASPOSE_WORDS_SHARED_API void set_CertificateHolder(const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& value);
    /// SignOptions object with various signing options.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::DigitalSignatures::SignOptions>& get_SignOptions() const;
    /// SignOptions object with various signing options.
    ASPOSE_WORDS_SHARED_API void set_SignOptions(const System::SharedPtr<Aspose::Words::DigitalSignatures::SignOptions>& value);

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
