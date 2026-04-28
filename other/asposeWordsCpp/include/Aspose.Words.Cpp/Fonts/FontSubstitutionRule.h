//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontSubstitutionRule.h
#pragma once

#include <system/object.h>
#include <system/enum_helpers.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Fonts
{
class ExternalFontCache;
namespace TrueType
{
class TTFont;
}
}
namespace Words
{
namespace Fonts
{

class FontInfo;

}
}
}
namespace System
{
namespace Drawing
{
enum class FontStyle;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// This is an abstract base class for the font substitution rule.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FontSubstitutionRule : public System::Object
{
    typedef FontSubstitutionRule ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Specifies whether the rule is enabled or not.
    virtual ASPOSE_WORDS_SHARED_API bool get_Enabled();
    /// Specifies whether the rule is enabled or not.
    virtual ASPOSE_WORDS_SHARED_API void set_Enabled(bool value);

protected:

    virtual System::SharedPtr<Aspose::Fonts::TrueType::TTFont> PerformSubstitutionCore(System::String , System::Drawing::FontStyle , System::SharedPtr<Aspose::Words::Fonts::FontInfo> , System::SharedPtr<Aspose::Fonts::ExternalFontCache> ) = 0;

private:

    __TypeStub<1,1,1,1>::type mField0;
    System::SharedPtr<System::Object> mField1;

};

}
}
}
