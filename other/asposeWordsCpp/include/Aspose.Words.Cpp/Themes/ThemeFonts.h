//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Themes/ThemeFonts.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Themes {

/// Represents a collection of fonts in the font scheme, allowing to specify different fonts for different languages <see cref="Aspose::Words::Themes::ThemeFonts::get_Latin">Latin</see>, <see cref="Aspose::Words::Themes::ThemeFonts::get_EastAsian">EastAsian</see> and <see cref="Aspose::Words::Themes::ThemeFonts::get_ComplexScript">ComplexScript</see>.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-styles-and-themes/">Working with Styles and Themes</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS ThemeFonts : public System::Object
{
    typedef ThemeFonts ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies font name for Latin characters.
    ASPOSE_WORDS_SHARED_API System::String get_Latin();
    /// Specifies font name for Latin characters.
    ASPOSE_WORDS_SHARED_API void set_Latin(const System::String& value);
    /// Specifies font name for EastAsian characters.
    ASPOSE_WORDS_SHARED_API System::String get_EastAsian();
    /// Specifies font name for EastAsian characters.
    ASPOSE_WORDS_SHARED_API void set_EastAsian(const System::String& value);
    /// Specifies font name for ComplexScript characters.
    ASPOSE_WORDS_SHARED_API System::String get_ComplexScript();
    /// Specifies font name for ComplexScript characters.
    ASPOSE_WORDS_SHARED_API void set_ComplexScript(const System::String& value);

protected:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;

    ThemeFonts();

private:

    __TypeStub<1,1,1,1>::type mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
