//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontSubstitutionSettings.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fonts
{
class DefaultFontSubstitutionRule;
class FontConfigSubstitutionRule;
class FontInfoSubstitutionRule;
class FontNameSubstitutionRule;

class TableSubstitutionRule;
}
}
}

namespace Aspose {

namespace Words {

namespace Fonts {

/// Specifies font substitution mechanism settings.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fonts/">Working with Fonts</a> documentation article.
/// 
/// Font substitution process consists of several rules which are checked one by one in specific order.
/// If the first rule can't resolve the font then second rule is checked and so on.
/// 
/// The order of the rules is following:
/// 1. Font name substitution rule (enabled by default)
/// 2. Font config substitution rule (disabled by default)
/// 3. Table substitution rule (enabled by default)
/// 4. Font info substitution rule (enabled by default)
/// 5. Default font rule (enabled by default)
/// 
/// Note that font info substitution rule will always resolve the font if <see cref="Aspose::Words::Fonts::FontInfo">FontInfo</see> is available
/// and will override the default font rule. If you want to use the default font rule then you should disable the
/// font info substitution rule.
/// 
/// Note that font config substitution rule will resolve the font in most cases and thus overrides all other rules.
class ASPOSE_WORDS_SHARED_CLASS FontSubstitutionSettings : public System::Object
{
    typedef FontSubstitutionSettings ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Settings related to table substitution rule.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::TableSubstitutionRule>& get_TableSubstitution() const;
    /// Settings related to font info substitution rule.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::FontInfoSubstitutionRule>& get_FontInfoSubstitution() const;
    /// Settings related to default font substitution rule.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::DefaultFontSubstitutionRule>& get_DefaultFontSubstitution() const;
    /// Settings related to font config substitution rule.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::FontConfigSubstitutionRule>& get_FontConfigSubstitution() const;
    /// Settings related to font name substitution rule.
    ASPOSE_WORDS_SHARED_API const System::SharedPtr<Aspose::Words::Fonts::FontNameSubstitutionRule>& get_FontNameSubstitution() const;

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;
    System::SharedPtr<System::Object> mField2;
    System::SharedPtr<System::Object> mField3;
    System::SharedPtr<System::Object> mField4;

};

}
}
}
