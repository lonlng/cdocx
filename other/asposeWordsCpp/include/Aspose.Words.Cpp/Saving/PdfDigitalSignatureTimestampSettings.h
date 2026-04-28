//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/PdfDigitalSignatureTimestampSettings.h
#pragma once

#include <system/timespan.h>
#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Saving {

/// Contains settings of the digital signature timestamp.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-digital-signatures/">Work with Digital Signatures</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS PdfDigitalSignatureTimestampSettings : public System::Object
{
    typedef PdfDigitalSignatureTimestampSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Timestamp server URL.
    ASPOSE_WORDS_SHARED_API System::String get_ServerUrl() const;
    /// Timestamp server URL.
    ASPOSE_WORDS_SHARED_API void set_ServerUrl(const System::String& value);
    /// Timestamp server user name.
    ASPOSE_WORDS_SHARED_API System::String get_UserName() const;
    /// Timestamp server user name.
    ASPOSE_WORDS_SHARED_API void set_UserName(const System::String& value);
    /// Timestamp server password.
    ASPOSE_WORDS_SHARED_API System::String get_Password() const;
    /// Timestamp server password.
    ASPOSE_WORDS_SHARED_API void set_Password(const System::String& value);
    /// Time-out value for accessing timestamp server.
    ASPOSE_WORDS_SHARED_API System::TimeSpan get_Timeout() const;
    /// Time-out value for accessing timestamp server.
    ASPOSE_WORDS_SHARED_API void set_Timeout(System::TimeSpan value);

    /// Initializes an instance of this class.
    ASPOSE_WORDS_SHARED_API PdfDigitalSignatureTimestampSettings();
    /// Initializes an instance of this class.
    /// 
    /// @param serverUrl Timestamp server URL.
    /// @param userName Timestamp server user name.
    /// @param password Timestamp server password.
    ASPOSE_WORDS_SHARED_API PdfDigitalSignatureTimestampSettings(const System::String& serverUrl, const System::String& userName, const System::String& password);
    /// Initializes an instance of this class.
    /// 
    /// @param serverUrl Timestamp server URL.
    /// @param userName Timestamp server user name.
    /// @param password Timestamp server password.
    /// @param timeout Time-out value for accessing timestamp server.
    ASPOSE_WORDS_SHARED_API PdfDigitalSignatureTimestampSettings(const System::String& serverUrl, const System::String& userName, const System::String& password, System::TimeSpan timeout);

protected:

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;
    System::TimeSpan mField3;

};

}
}
}
