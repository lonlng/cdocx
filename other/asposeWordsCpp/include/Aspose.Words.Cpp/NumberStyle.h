//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/NumberStyle.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the number style for a list, footnotes and endnotes, page numbers.
enum class ASPOSE_WORDS_SHARED_CLASS NumberStyle
{
    /// Arabic numbering (1, 2, 3, ...)
    Arabic = 0,
    /// Upper case Roman (I, II, III, ...)
    UppercaseRoman = 1,
    /// Lower case Roman (i, ii, iii, ...)
    LowercaseRoman = 2,
    /// Upper case Letter (A, B, C, ...)
    UppercaseLetter = 3,
    /// Lower case letter (a, b, c, ...)
    LowercaseLetter = 4,
    /// Ordinal (1st, 2nd, 3rd, ...)
    Ordinal = 5,
    /// Numbered (One, Two, Three, ...)
    Number = 6,
    /// Ordinal (text) (First, Second, Third, ...)
    OrdinalText = 7,
    /// Hexadecimal: 8, 9, A, B, C, D, E, F, 10, 11, 12
    Hex = 8,
    /// Chicago Manual of Style: *, †, †
    ChicagoManual = 9,
    /// Ideograph-digital
    Kanji = 10,
    /// Japanese counting
    KanjiDigit = 11,
    /// Aiueo
    AiueoHalfWidth = 12,
    /// Iroha
    IrohaHalfWidth = 13,
    /// Full-width Arabic: 1, 2, 3, 4
    ArabicFullWidth = 14,
    /// Half-width Arabic: 1, 2, 3, 4
    ArabicHalfWidth = 15,
    /// Japanese legal
    KanjiTraditional = 16,
    /// Japanese digital ten thousand
    KanjiTraditional2 = 17,
    /// Enclosed circles
    NumberInCircle = 18,
    /// Decimal full width: 1, 2, 3, 4
    DecimalFullWidth = 19,
    /// Aiueo full width
    Aiueo = 20,
    /// Iroha full width
    Iroha = 21,
    /// Leading Zero (01, 02,..., 09, 10, 11,..., 99, 100, 101,...)
    LeadingZero = 22,
    /// Bullet (check the character code in the text)
    Bullet = 23,
    /// Korean Ganada
    Ganada = 24,
    /// Korea Chosung
    Chosung = 25,
    /// Enclosed full stop
    GB1 = 26,
    /// Enclosed parenthesis
    GB2 = 27,
    /// Enclosed circle Chinese
    GB3 = 28,
    /// Ideograph enclosed circle
    GB4 = 29,
    /// Ideograph traditional
    Zodiac1 = 30,
    /// Ideograph Zodiac
    Zodiac2 = 31,
    /// Ideograph Zodiac traditional
    Zodiac3 = 32,
    /// Taiwanese counting
    TradChinNum1 = 33,
    /// Ideograph legal traditional
    TradChinNum2 = 34,
    /// Taiwanese counting thousand
    TradChinNum3 = 35,
    /// Taiwanese digital
    TradChinNum4 = 36,
    /// Chinese counting
    SimpChinNum1 = 37,
    /// Chinese legal simplified
    SimpChinNum2 = 38,
    /// Chinese counting thousand
    SimpChinNum3 = 39,
    /// Chinese (not implemented)
    SimpChinNum4 = 40,
    /// Korean digital
    HanjaRead = 41,
    /// Korean counting
    HanjaReadDigit = 42,
    /// Korea legal
    Hangul = 43,
    /// Korea digital2
    Hanja = 44,
    /// Hebrew-1
    Hebrew1 = 45,
    /// Arabic alpha
    Arabic1 = 46,
    /// Hebrew-2
    Hebrew2 = 47,
    /// Arabic abjad
    Arabic2 = 48,
    /// Hindi vowels
    HindiLetter1 = 49,
    /// Hindi consonants
    HindiLetter2 = 50,
    /// Hindi numbers
    HindiArabic = 51,
    /// Hindi descriptive (cardinals)
    HindiCardinalText = 52,
    /// Thai letters
    ThaiLetter = 53,
    /// Thai numbers
    ThaiArabic = 54,
    /// Thai descriptive (cardinals)
    ThaiCardinalText = 55,
    /// Vietnamese descriptive (cardinals)
    VietCardinalText = 56,
    /// Page number format: - 1 -, - 2 -, - 3 -, - 4 -
    NumberInDash = 57,
    /// Lowercase Russian alphabet
    LowercaseRussian = 58,
    /// Uppercase Russian alphabet
    UppercaseRussian = 59,
    /// No bullet or number.
    None = 255,
    /// Custom number format. It is supported by DOCX format only.
    Custom = 0xFF00
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::NumberStyle>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::NumberStyle, const char_t*>, 62>& values();
};
