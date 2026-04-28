//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/UserInformation.h
#pragma once

#include <system/string.h>
#include <mutex>
#include <memory>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies information about the user.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS UserInformation : public System::Object
{
    typedef UserInformation ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the user's name.
    ASPOSE_WORDS_SHARED_API System::String get_Name() const;
    /// Sets the user's name.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Gets the user's initials.
    ASPOSE_WORDS_SHARED_API System::String get_Initials() const;
    /// Sets the user's initials.
    ASPOSE_WORDS_SHARED_API void set_Initials(const System::String& value);
    /// Gets the user's postal address.
    ASPOSE_WORDS_SHARED_API System::String get_Address() const;
    /// Sets the user's postal address.
    ASPOSE_WORDS_SHARED_API void set_Address(const System::String& value);
    /// Default user information.
    static ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::UserInformation> get_DefaultUser();

    ASPOSE_WORDS_SHARED_API UserInformation();

private:

    System::String mField0;
    System::String mField1;
    System::String mField2;

};

}
}
}
