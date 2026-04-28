//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Themes/ThemeColors.h
#pragma once

#include <system/array.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace Drawing
{
class Color;
}
}

namespace Aspose {

namespace Words {

namespace Themes {

/// Represents the color scheme of the document theme which contains twelve colors.
/// <see cref="Aspose::Words::Themes::ThemeColors">ThemeColors</see> object contains six accent colors, two dark colors, two light colors
/// and a color for each of a hyperlink and followed hyperlink.
class ASPOSE_WORDS_SHARED_CLASS ThemeColors : public System::Object
{
    typedef ThemeColors ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies color Accent 1.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent1();
    /// Specifies color Accent 1.
    ASPOSE_WORDS_SHARED_API void set_Accent1(System::Drawing::Color value);
    /// Specifies color Accent 2.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent2();
    /// Specifies color Accent 2.
    ASPOSE_WORDS_SHARED_API void set_Accent2(System::Drawing::Color value);
    /// Specifies color Accent 3.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent3();
    /// Specifies color Accent 3.
    ASPOSE_WORDS_SHARED_API void set_Accent3(System::Drawing::Color value);
    /// Specifies color Accent 4.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent4();
    /// Specifies color Accent 4.
    ASPOSE_WORDS_SHARED_API void set_Accent4(System::Drawing::Color value);
    /// Specifies color Accent 5.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent5();
    /// Specifies color Accent 5.
    ASPOSE_WORDS_SHARED_API void set_Accent5(System::Drawing::Color value);
    /// Specifies color Accent 6.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Accent6();
    /// Specifies color Accent 6.
    ASPOSE_WORDS_SHARED_API void set_Accent6(System::Drawing::Color value);
    /// Specifies color Dark 1.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Dark1();
    /// Specifies color Dark 1.
    ASPOSE_WORDS_SHARED_API void set_Dark1(System::Drawing::Color value);
    /// Specifies color Dark 2.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Dark2();
    /// Specifies color Dark 2.
    ASPOSE_WORDS_SHARED_API void set_Dark2(System::Drawing::Color value);
    /// Specifies color for a clicked hyperlink.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_FollowedHyperlink();
    /// Specifies color for a clicked hyperlink.
    ASPOSE_WORDS_SHARED_API void set_FollowedHyperlink(System::Drawing::Color value);
    /// Specifies color for a hyperlink.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Hyperlink();
    /// Specifies color for a hyperlink.
    ASPOSE_WORDS_SHARED_API void set_Hyperlink(System::Drawing::Color value);
    /// Specifies color Light 1.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Light1();
    /// Specifies color Light 1.
    ASPOSE_WORDS_SHARED_API void set_Light1(System::Drawing::Color value);
    /// Specifies color Light 2.
    ASPOSE_WORDS_SHARED_API System::Drawing::Color get_Light2();
    /// Specifies color Light 2.
    ASPOSE_WORDS_SHARED_API void set_Light2(System::Drawing::Color value);

protected:

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    System::WeakPtr<System::Object> mField3;

};

}
}
}
