//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/DigitalSignatures/SignOptions.h
#pragma once

#include <system/guid.h>
#include <system/date_time.h>
#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/DigitalSignatures/XmlDsigLevel.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Licensing
{
void Venture(const System::SharedPtr<System::Object>&, bool, const uint8_t*, const size_t);

}

}
}

namespace Aspose {

namespace Words {

namespace DigitalSignatures {

/// Allows to specify options for document signing.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SignOptions : public System::Object
{
    typedef SignOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies comments on the digital signature.
    /// Default value is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Comments() const;
    /// Specifies comments on the digital signature.
    /// Default value is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Comments(const System::String& value);
    /// The date of signing.
    /// Default value is <b>%current time</b> (<see cref="System::DateTime::get_Now">Now</see>)
    ASPOSE_WORDS_SHARED_API System::DateTime get_SignTime() const;
    /// The date of signing.
    /// Default value is <b>%current time</b> (<see cref="System::DateTime::get_Now">Now</see>)
    ASPOSE_WORDS_SHARED_API void set_SignTime(System::DateTime value);
    /// Signature line identifier.
    /// Default value is <b>%Empty (all zeroes) Guid</b>.
    ASPOSE_WORDS_SHARED_API System::Guid get_SignatureLineId() const;
    /// Signature line identifier.
    /// Default value is <b>%Empty (all zeroes) Guid</b>.
    ASPOSE_WORDS_SHARED_API void set_SignatureLineId(System::Guid value);
    /// The image that will be shown in associated <see cref="Aspose::Words::Drawing::SignatureLine">SignatureLine</see>.
    /// Default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::ArrayPtr<uint8_t> get_SignatureLineImage() const;
    /// The image that will be shown in associated <see cref="Aspose::Words::Drawing::SignatureLine">SignatureLine</see>.
    /// Default value is <c>%null</c>.
    ASPOSE_WORDS_SHARED_API void set_SignatureLineImage(const System::ArrayPtr<uint8_t>& value);
    /// The password to decrypt source document.
    /// Default value is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_DecryptionPassword() const;
    /// The password to decrypt source document.
    /// Default value is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_DecryptionPassword(const System::String& value);
    /// Specifies the class ID of the signature provider.
    /// Default value is <b>%Empty (all zeroes) Guid</b>.
    /// 
    /// The cryptographic service provider (CSP) is an independent software module that actually performs
    /// cryptography algorithms for authentication, encoding, and encryption. MS Office reserves the value
    /// of {00000000-0000-0000-0000-000000000000} for its default signature provider.
    /// 
    /// The GUID of the additionally installed provider should be obtained from the documentation shipped with the provider.
    /// 
    /// In addition, all the installed cryptographic providers are enumerated in windows registry.
    /// It can be found in the following path: HKLM\\SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider.
    /// There is a key name "CP Service UUID" which corresponds to a GUID of signature provider.
    ASPOSE_WORDS_SHARED_API System::Guid get_ProviderId() const;
    /// Setter for Aspose::Words::DigitalSignatures::SignOptions::get_ProviderId
    ASPOSE_WORDS_SHARED_API void set_ProviderId(System::Guid value);
    /// Specifies the level of a digital signature based on XML-DSig standard.
    /// The default value is <see cref="Aspose::Words::DigitalSignatures::XmlDsigLevel::XmlDSig">XmlDSig</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::DigitalSignatures::XmlDsigLevel get_XmlDsigLevel() const;
    /// Specifies the level of a digital signature based on XML-DSig standard.
    /// The default value is <see cref="Aspose::Words::DigitalSignatures::XmlDsigLevel::XmlDSig">XmlDSig</see>.
    ASPOSE_WORDS_SHARED_API void set_XmlDsigLevel(Aspose::Words::DigitalSignatures::XmlDsigLevel value);

    ASPOSE_WORDS_SHARED_API SignOptions();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::String mField1;
    System::DateTime mField2;
    System::Guid mField3;
    System::Guid mField4;
    System::SharedPtr<System::Object> mField5;
    System::String mField6;
    System::SharedPtr<System::Object> mField7;

};

}
}
}
