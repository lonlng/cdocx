//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfDigitalSignatureDetails.h
#pragma once

#include <system/string.h>
#include <system/date_time.h>

#include <Aspose.Words.Cpp/Saving/PdfDigitalSignatureHashAlgorithm.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace DigitalSignatures
{
class CertificateHolder;
}
namespace Saving
{
class PdfDigitalSignatureTimestampSettings;

}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Contains details for signing a PDF document with a digital signature.
/// 
/// At the moment digitally signing PDF documents is only available on .NET 3.5 or higher.
/// 
/// To digitally sign a PDF document when it is created by %Aspose.Words, set the <see cref="Aspose::Words::Saving::PdfSaveOptions::get_DigitalSignatureDetails">DigitalSignatureDetails</see>
/// property to a valid <see cref="Aspose::Words::Saving::PdfDigitalSignatureDetails">PdfDigitalSignatureDetails</see> object and then save the document in the PDF format passing
/// the <see cref="Aspose::Words::Saving::PdfSaveOptions">PdfSaveOptions</see> as a parameter into the <see cref="Aspose::Words::Document::Save(System::String, System::SharedPtr<Aspose::Words::Saving::SaveOptions>)">Save()</see> method.
/// 
/// %Aspose.Words creates a PKCS\#7 signature over the whole PDF document and uses the "Adobe.PPKMS" filter and
/// "adbe.pkcs7.sha1" subfilter when creating a digital signature.
/// 
/// @sa Aspose::Words::Saving::PdfSaveOptions::get_DigitalSignatureDetails
class ASPOSE_WORDS_SHARED_CLASS PdfDigitalSignatureDetails : public System::Object
{
    typedef PdfDigitalSignatureDetails ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the certificate holder object that contains the certificate was used to sign the document.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder> get_CertificateHolder() const;
    /// Returns the certificate holder object that contains the certificate was used to sign the document.
    ASPOSE_WORDS_SHARED_API void set_CertificateHolder(const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& value);
    /// Gets the reason for the signing.
    ASPOSE_WORDS_SHARED_API System::String get_Reason() const;
    /// Sets the reason for the signing.
    ASPOSE_WORDS_SHARED_API void set_Reason(const System::String& value);
    /// Gets the location of the signing.
    ASPOSE_WORDS_SHARED_API System::String get_Location() const;
    /// Sets the location of the signing.
    ASPOSE_WORDS_SHARED_API void set_Location(const System::String& value);
    /// Gets or sets the date of the signing.
    /// 
    /// The default value is the current time.
    /// 
    /// This value will appear in the digital signature as an unverified computer time.
    ASPOSE_WORDS_SHARED_API System::DateTime get_SignatureDate() const;
    /// Setter for Aspose::Words::Saving::PdfDigitalSignatureDetails::get_SignatureDate
    ASPOSE_WORDS_SHARED_API void set_SignatureDate(System::DateTime value);
    /// Gets the hash algorithm.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfDigitalSignatureHashAlgorithm get_HashAlgorithm() const;
    /// Sets the hash algorithm.
    ASPOSE_WORDS_SHARED_API void set_HashAlgorithm(Aspose::Words::Saving::PdfDigitalSignatureHashAlgorithm value);
    /// Gets or sets the digital signature timestamp settings.
    /// 
    /// The default value is <c>%null</c> and the digital signature will not be time-stamped.
    /// When this property is set to a valid <see cref="Aspose::Words::Saving::PdfDigitalSignatureTimestampSettings">PdfDigitalSignatureTimestampSettings</see> object,
    /// then the digital signature in the PDF document will be time-stamped.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::PdfDigitalSignatureTimestampSettings> get_TimestampSettings() const;
    /// Setter for Aspose::Words::Saving::PdfDigitalSignatureDetails::get_TimestampSettings
    ASPOSE_WORDS_SHARED_API void set_TimestampSettings(const System::SharedPtr<Aspose::Words::Saving::PdfDigitalSignatureTimestampSettings>& value);

    /// Initializes an instance of this class.
    ASPOSE_WORDS_SHARED_API PdfDigitalSignatureDetails();
    /// Initializes an instance of this class.
    /// 
    /// @param certificateHolder A certificate holder which contains the certificate itself.
    /// @param reason The reason for signing.
    /// @param location The location of signing.
    /// @param signatureDate The date and time of signing.
    ASPOSE_WORDS_SHARED_API PdfDigitalSignatureDetails(const System::SharedPtr<Aspose::Words::DigitalSignatures::CertificateHolder>& certificateHolder, const System::String& reason, const System::String& location, System::DateTime signatureDate);

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::String mField1;
    System::String mField2;
    System::DateTime mField3;
    System::SharedPtr<System::Object> mField4;
    __TypeStub<4,4,4,4>::type mField5;

};

}
}
}
