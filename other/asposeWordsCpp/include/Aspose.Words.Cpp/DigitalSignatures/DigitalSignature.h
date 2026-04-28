//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DigitalSignatures/DigitalSignature.h
#pragma once

#include <system/guid.h>
#include <system/date_time.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/DigitalSignatures/DigitalSignatureType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace DigitalSignatures
{
class CertificateHolder;

}

}
}

namespace Aspose {

namespace Words {

namespace DigitalSignatures {

/// Represents a digital signature on a document and the result of its verification.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS DigitalSignature : public System::Object
{
    typedef DigitalSignature ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the type of the digital signature.
    ASPOSE_WORDS_SHARED_API Aspose::Words::DigitalSignatures::DigitalSignatureType get_SignatureType() const;
    /// Gets the time the document was signed.
    ASPOSE_WORDS_SHARED_API System::DateTime get_SignTime() const;
    /// Gets the signing purpose comment.
    ASPOSE_WORDS_SHARED_API System::String get_Comments() const;
    /// Returns the subject distinguished name of the certificate that was used to sign the document.
    ASPOSE_WORDS_SHARED_API System::String get_SubjectName();
    /// Returns the subject distinguished name of the certificate isuuer.
    ASPOSE_WORDS_SHARED_API System::String get_IssuerName();
    /// Returns <c>%true</c> if this digital signature is valid and the document has not been tampered with.
    ASPOSE_WORDS_SHARED_API bool get_IsValid() const;
    /// Returns the certificate holder object that contains the certificate was used to sign the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> get_CertificateHolder() const;
    /// Gets an array of bytes representing a signature value.
    ASPOSE_WORDS_SHARED_API const System::ArrayPtr<uint8_t>& get_SignatureValue() const;

    /// Returns a user-friendly string that displays the value of this object.
    ASPOSE_WORDS_SHARED_API System::String ToString() const override;

protected:

private:

    System::SharedPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;
    System::DateTime mField5;
    System::String mField6;
    __TypeStub<1,1,1,1>::type mField7;
    System::SharedPtr<System::Object> mField8;
    System::SharedPtr<System::Object> mField9;
    System::SharedPtr<System::Object> mField10;
    System::String mField11;
    System::Guid mField12;
    System::Guid mField13;
    __TypeStub<1,1,1,1>::type mField14;

};

}
}
}
