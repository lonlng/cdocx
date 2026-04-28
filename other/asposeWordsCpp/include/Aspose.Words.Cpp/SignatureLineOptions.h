//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/SignatureLineOptions.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Allows to specify options for signature line being inserted. Used in <see cref="Aspose::Words::DocumentBuilder">DocumentBuilder</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SignatureLineOptions : public System::Object
{
    typedef SignatureLineOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets suggested signer of the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Signer() const;
    /// Sets suggested signer of the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Signer(const System::String& value);
    /// Gets suggested signer's title.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_SignerTitle() const;
    /// Sets suggested signer's title.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_SignerTitle(const System::String& value);
    /// Gets suggested signer's e-mail address.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Email() const;
    /// Sets suggested signer's e-mail address.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Email(const System::String& value);
    /// Gets a value indicating that default instructions is shown in the Sign dialog.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_DefaultInstructions() const;
    /// Sets a value indicating that default instructions is shown in the Sign dialog.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_DefaultInstructions(bool value);
    /// Gets instructions to the signer that are displayed on signing the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API System::String get_Instructions() const;
    /// Sets instructions to the signer that are displayed on signing the signature line.
    /// Default value for this property is <b>%empty string</b>.
    ASPOSE_WORDS_SHARED_API void set_Instructions(const System::String& value);
    /// Gets a value indicating that the signer can add comments in the Sign dialog.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_AllowComments() const;
    /// Sets a value indicating that the signer can add comments in the Sign dialog.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_AllowComments(bool value);
    /// Gets a value indicating that sign date is shown in the signature line.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API bool get_ShowDate() const;
    /// Sets a value indicating that sign date is shown in the signature line.
    /// Default value for this property is <c>%true</c>.
    ASPOSE_WORDS_SHARED_API void set_ShowDate(bool value);

    ASPOSE_WORDS_SHARED_API SignatureLineOptions();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    __TypeStub<1,1,1,1>::type mField3;
    System::String mField4;
    __TypeStub<1,1,1,1>::type mField5;
    __TypeStub<1,1,1,1>::type mField6;

};

}
}
