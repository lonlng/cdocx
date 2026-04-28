//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/DigitalSignatureDetails.h
#pragma once

#include <system/object.h>

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

namespace Saving {

/// Contains details for signing a document with a digital signature.
class ASPOSE_WORDS_SHARED_CLASS DigitalSignatureDetails : public System::Object
{
    typedef DigitalSignatureDetails ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a <see cref="Aspose::Words::Saving::DigitalSignatureDetails::get_CertificateHolder">CertificateHolder</see> object that contains the certificate used to sign a document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& get_CertificateHolder() const;
    /// Sets a <see cref="Aspose::Words::Saving::DigitalSignatureDetails::get_CertificateHolder">CertificateHolder</see> object that contains the certificate used to sign a document.
    ASPOSE_WORDS_SHARED_API void set_CertificateHolder(const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& value);
    /// Gets a <see cref="Aspose::Words::Saving::DigitalSignatureDetails::get_SignOptions">SignOptions</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::DigitalSignatures::SignOptions>& get_SignOptions() const;
    /// Sets a <see cref="Aspose::Words::Saving::DigitalSignatureDetails::get_SignOptions">SignOptions</see> object used to sign a document.
    ASPOSE_WORDS_SHARED_API void set_SignOptions(const System::SharedPtr<Aspose::Words::DigitalSignatures::SignOptions>& value);

    /// Initializes a new instance of <see cref="Aspose::Words::Saving::DigitalSignatureDetails">DigitalSignatureDetails</see> class.
    /// 
    /// @param certificateHolder A certificate holder which contains the certificate itself.
    /// @param signOptions Signature options to use for signing a document.
    ASPOSE_WORDS_SHARED_API DigitalSignatureDetails(const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& certificateHolder, const System::SharedPtr<Aspose::Words::DigitalSignatures::SignOptions>& signOptions);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
