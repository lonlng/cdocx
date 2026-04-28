//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldSymbol.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
namespace Fields
{
enum class FieldSwitchType;
}

class NodeRange;
}
}
namespace System
{
class String;
namespace Text
{
class Encoding;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements a SYMBOL field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldSymbol : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldSymbol ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the character's code point value in decimal or hexadecimal.
    ASPOSE_WORDS_SHARED_API System::String get_CharacterCode();
    /// Sets the character's code point value in decimal or hexadecimal.
    ASPOSE_WORDS_SHARED_API void set_CharacterCode(const System::String& value);
    /// Gets the name of the font of the character retrieved by the field.
    ASPOSE_WORDS_SHARED_API System::String get_FontName();
    /// Sets the name of the font of the character retrieved by the field.
    ASPOSE_WORDS_SHARED_API void set_FontName(const System::String& value);
    /// Gets the size in points of the font of the character retrieved by the field.
    ASPOSE_WORDS_SHARED_API System::String get_FontSize();
    /// Sets the size in points of the font of the character retrieved by the field.
    ASPOSE_WORDS_SHARED_API void set_FontSize(const System::String& value);
    /// Gets whether the character code is interpreted as the value of an ANSI character.
    ASPOSE_WORDS_SHARED_API bool get_IsAnsi();
    /// Sets whether the character code is interpreted as the value of an ANSI character.
    ASPOSE_WORDS_SHARED_API void set_IsAnsi(bool value);
    /// Gets whether the character code is interpreted as the value of a Unicode character.
    ASPOSE_WORDS_SHARED_API bool get_IsUnicode();
    /// Sets whether the character code is interpreted as the value of a Unicode character.
    ASPOSE_WORDS_SHARED_API void set_IsUnicode(bool value);
    /// Gets whether the character code is interpreted as the value of a SHIFT-JIS character.
    ASPOSE_WORDS_SHARED_API bool get_IsShiftJis();
    /// Sets whether the character code is interpreted as the value of a SHIFT-JIS character.
    ASPOSE_WORDS_SHARED_API void set_IsShiftJis(bool value);
    /// Gets whether the character retrieved by the field affects the line spacing of the paragraph.
    ASPOSE_WORDS_SHARED_API bool get_DontAffectsLineSpacing();
    /// Sets whether the character retrieved by the field affects the line spacing of the paragraph.
    ASPOSE_WORDS_SHARED_API void set_DontAffectsLineSpacing(bool value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

private:

};

}
}
}
