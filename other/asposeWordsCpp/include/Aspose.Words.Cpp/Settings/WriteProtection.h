//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/WriteProtection.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Specifies write protection settings for a document.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/protect-or-encrypt-a-document/">Protect or Encrypt a Document</a> documentation article.
/// 
/// Write protection specifies whether the author has recommended that
/// the document is to be opened as read-only and/or require a password to modify a document.
/// 
/// Write protection is different from document protection. Write protection is specified in
/// %Microsoft Word in the options of the Save As dialog box.
/// 
/// You do not create instances of this class directly. You access document protection settings
/// via the <see cref="Aspose::Words::Document::get_WriteProtection">WriteProtection</see> property.
class ASPOSE_WORDS_SHARED_CLASS WriteProtection : public System::Object
{
    typedef WriteProtection ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether the document author has recommended that the document be opened as read-only.
    ASPOSE_WORDS_SHARED_API bool get_ReadOnlyRecommended() const;
    /// Specifies whether the document author has recommended that the document be opened as read-only.
    ASPOSE_WORDS_SHARED_API void set_ReadOnlyRecommended(bool value);
    /// Returns <c>%true</c> when a write protection password is set.
    ASPOSE_WORDS_SHARED_API bool get_IsWriteProtected();

    /// Sets the write protection password for the document.
    /// 
    /// If a password is set, %Microsoft Word will require the user to enter it or open
    /// the document as read-only.
    /// 
    /// @param password The password to set. Cannot be <c>%null</c>, but can be an empty string.
    ASPOSE_WORDS_SHARED_API void SetPassword(const System::String& password);
    /// Returns <c>%true</c> if the specified password is the same as the write-protection password the document was protected with.
    /// If document is not write-protected with password then returns <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool ValidatePassword(const System::String& password);

protected:

    WriteProtection();

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::String mField1;
    System::SharedPtr<System::Object> mField2;

};

}
}
}
