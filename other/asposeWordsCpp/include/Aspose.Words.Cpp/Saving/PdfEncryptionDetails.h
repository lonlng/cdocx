//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfEncryptionDetails.h
#pragma once

#include <system/string.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/Saving/PdfPermissions.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Contains details for encrypting and access permissions for a PDF document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/protect-or-encrypt-a-document/">Protect or Encrypt a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PdfEncryptionDetails : public System::Object
{
    typedef PdfEncryptionDetails ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies the user password required for opening the encrypted PDF document.
    /// 
    /// The user password will be required to open an encrypted PDF document for viewing. The permissions specified in
    /// <see cref="Aspose::Words::Saving::PdfEncryptionDetails::get_Permissions">Permissions</see> will be enforced by the reader software.
    /// 
    /// The user password can be <c>%null</c> or empty string, in this case no password will be required from the user when
    /// opening the PDF document. The user password cannot be the same as the owner password.
    ASPOSE_WORDS_SHARED_API System::String get_UserPassword() const;
    /// Setter for Aspose::Words::Saving::PdfEncryptionDetails::get_UserPassword
    ASPOSE_WORDS_SHARED_API void set_UserPassword(const System::String& value);
    /// Specifies the owner password for the encrypted PDF document.
    /// 
    /// The owner password allows the user to open an encrypted PDF document without any access restrictions
    /// specified in <see cref="Aspose::Words::Saving::PdfEncryptionDetails::get_Permissions">Permissions</see>.
    /// 
    /// The owner password cannot be the same as the user password.
    ASPOSE_WORDS_SHARED_API System::String get_OwnerPassword() const;
    /// Setter for Aspose::Words::Saving::PdfEncryptionDetails::get_OwnerPassword
    ASPOSE_WORDS_SHARED_API void set_OwnerPassword(const System::String& value);
    /// Specifies the operations that are allowed to a user on an encrypted PDF document.
    /// The default value is <see cref="Aspose::Words::Saving::PdfPermissions::DisallowAll">DisallowAll</see>.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Saving::PdfPermissions get_Permissions() const;
    /// Specifies the operations that are allowed to a user on an encrypted PDF document.
    /// The default value is <see cref="Aspose::Words::Saving::PdfPermissions::DisallowAll">DisallowAll</see>.
    ASPOSE_WORDS_SHARED_API void set_Permissions(Aspose::Words::Saving::PdfPermissions value);

    /// Initializes an instance of this class.
    ASPOSE_WORDS_SHARED_API PdfEncryptionDetails(const System::String& userPassword, const System::String& ownerPassword);
    /// Initializes an instance of this class.
    ASPOSE_WORDS_SHARED_API PdfEncryptionDetails(const System::String& userPassword, const System::String& ownerPassword, Aspose::Words::Saving::PdfPermissions permissions);

protected:

private:

    System::String mField0;
    System::String mField1;
    __TypeStub<4,4,4,4>::type mField2;

};

}
}
}
