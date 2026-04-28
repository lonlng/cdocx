//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/SignatureLine.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class Guid;
}

namespace Aspose {

namespace Words {

namespace Drawing {

/// Provides access to signature line properties.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SignatureLine : public System::Object
{
    typedef SignatureLine ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets suggested signer of the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Signer();
    /// Sets suggested signer of the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Signer(const System::String& value);
    /// Gets suggested signer's title (for example, Manager).
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_SignerTitle();
    /// Sets suggested signer's title (for example, Manager).
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_SignerTitle(const System::String& value);
    /// Gets suggested signer's e-mail address.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Email();
    /// Sets suggested signer's e-mail address.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Email(const System::String& value);
    /// Gets a value indicating that default instructions is shown in the Sign dialog.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_DefaultInstructions();
    /// Sets a value indicating that default instructions is shown in the Sign dialog.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_DefaultInstructions(bool value);
    /// Gets instructions to the signer that are displayed on signing the signature line.
    /// This property is ignored if <see cref="Aspose::Words::Drawing::SignatureLine::get_DefaultInstructions">DefaultInstructions</see> is set.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Instructions();
    /// Sets instructions to the signer that are displayed on signing the signature line.
    /// This property is ignored if <see cref="Aspose::Words::Drawing::SignatureLine::get_DefaultInstructions">DefaultInstructions</see> is set.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Instructions(const System::String& value);
    /// Gets a value indicating that the signer can add comments in the Sign dialog.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_AllowComments();
    /// Sets a value indicating that the signer can add comments in the Sign dialog.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_AllowComments(bool value);
    /// Gets a value indicating that sign date is shown in the signature line.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowDate();
    /// Sets a value indicating that sign date is shown in the signature line.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowDate(bool value);
    /// Gets or sets identifier for this signature line.
    /// This identifier can be associated with a digital signature, when signing document using <see cref="Aspose::Words::DigitalSignatures::DigitalSignatureUtil">DigitalSignatureUtil</see>.
    /// This value must be unique and by default it is randomly generated new Guid
    /// (<see cref="System::Guid::NewGuid">NewGuid</see>).
    ASPOSE_WORDS_SHARED_API System::Guid get_Id();
    /// Setter for Aspose::Words::Drawing::SignatureLine::get_Id
    ASPOSE_WORDS_SHARED_API void set_Id(System::Guid value);
    /// Gets or sets signature provider identifier for this signature line.
    /// Default value is "{00000000-0000-0000-0000-000000000000}".
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
    ASPOSE_WORDS_SHARED_API System::Guid get_ProviderId();
    /// Setter for Aspose::Words::Drawing::SignatureLine::get_ProviderId
    ASPOSE_WORDS_SHARED_API void set_ProviderId(System::Guid value);
    /// Indicates that signature line is signed by digital signature.
    ASPOSE_WORDS_SHARED_API bool get_IsSigned();
    /// Indicates that signature line is signed by digital signature and this digital signature is valid.
    ASPOSE_WORDS_SHARED_API bool get_IsValid();

protected:

    virtual ASPOSE_WORDS_SHARED_API ~SignatureLine();

private:

    System::WeakPtr<System::Object> mField0;
    __TypeStub<4,4,4,4>::type mField1;

};

}
}
}
