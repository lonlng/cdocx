//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/PhoneticGuide.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// Represents Phonetic Guide.
class ASPOSE_WORDS_SHARED_CLASS PhoneticGuide : public System::Object
{
    typedef PhoneticGuide ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets base text of the phonetic guide.
    ASPOSE_WORDS_SHARED_API System::String get_BaseText();
    /// Gets ruby text of the phonetic guide.
    ASPOSE_WORDS_SHARED_API System::String get_RubyText();

protected:

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
