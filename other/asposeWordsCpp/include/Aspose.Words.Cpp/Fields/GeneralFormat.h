//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/GeneralFormat.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fields {

/// Specifies a general format that is applied to a numeric, text, or any field result.
/// A field may have a combination of general formats.
enum class ASPOSE_WORDS_SHARED_CLASS GeneralFormat
{
    /// Used to specify a missing general format.
    None,
    /// Numeric formatting. Formats a numeric result using hiragana characters in the traditional a-i-u-e-o order.
    Aiueo = 1,
    /// Numeric formatting. Formats a numeric result as one or more occurrences of an uppercase alphabetic Latin character.
    UppercaseAlphabetic,
    /// Numeric formatting. Formats a numeric result as one or more occurrences of an lowercase alphabetic Latin character.
    LowercaseAlphabetic,
    /// Numeric formatting. Formats a numeric result using Arabic cardinal numerals.
    Arabic,
    /// Numeric formatting. Formats a numeric result using ascending Abjad numerals.
    ArabicAbjad,
    /// Numeric formatting. Formats a numeric result using characters in the Arabic alphabet.
    ArabicAlpha,
    /// Numeric formatting. Formats a numeric result using Arabic cardinal numerals, with a prefix of "- " and a suffix of " -".
    ArabicDash,
    /// Numeric formatting. Formats a numeric result in the Thai counting system.
    BahtText,
    /// Numeric formatting. Cardinal text (One, Two, Three, ...).
    CardText,
    /// Numeric formatting. Formats a numeric result using ascending numbers from the appropriate counting system.
    ChineseNum1,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the appropriate legal format.
    ChineseNum2,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the appropriate counting thousand system.
    ChineseNum3,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the Korean Chosung format.
    Chosung,
    /// Numeric formatting. Formats a numeric result using decimal numbering enclosed in a circle, using the
    /// enclosed alphanumeric glyph character for numbers in the range 1–20.
    CircleNum,
    /// Numeric formatting. Formats a numeric result using double-byte Arabic numbering.
    DBChar,
    /// Numeric formatting. Formats a numeric result using sequential digital ideographs, using the appropriate character.
    DBNum1,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the appropriate counting system.
    DBNum2,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the appropriate legal counting system.
    DBNum3,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the appropriate digital counting system.
    DBNum4,
    /// Numeric formatting. Dollar text (One, Two, Three, ... + AND 55/100).
    DollarText,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the Korean Ganada format.
    Ganada,
    /// Numeric formatting. Formats a numeric result using decimal numbering followed by a period, using
    /// the enclosed alphanumeric glyph character.
    GB1,
    /// Numeric formatting. Formats a numeric result using decimal numbering enclosed in parenthesis,
    /// using the enclosed alphanumeric glyph character.
    GB2,
    /// Numeric formatting. Formats a numeric result using decimal numbering enclosed in a circle, using the
    /// enclosed alphanumeric glyph character.
    GB3,
    /// Numeric formatting. Formats a numeric result using decimal numbering enclosed in a circle, using the
    /// enclosed alphanumeric glyph character.
    GB4,
    /// Numeric formatting. Formats a numeric result using Hebrew numerals.
    Hebrew1,
    /// Numeric formatting. Formats a numeric result using the Hebrew alphabet.
    Hebrew2,
    /// Numeric formatting. Formats the numeric result using uppercase hexadecimal digits.
    Hex,
    /// Numeric formatting. Formats a numeric result using Hindi numbers.
    HindiArabic,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the Hindi counting system.
    HindiCardText,
    /// Numeric formatting. Formats a numeric result using Hindi vowels.
    HindiLetter1,
    /// Numeric formatting. Formats a numeric result using Hindi consonants.
    HindiLetter2,
    /// Numeric formatting. Formats a numeric result using the Japanese iroha.
    Iroha,
    /// Numeric formatting. Formats a numeric result using a Japanese style using the appropriate counting system.
    KanjiNum1,
    /// Numeric formatting. Formats a numeric result using the appropriate counting system.
    KanjiNum2,
    /// Numeric formatting. Formats a numeric result using the appropriate counting system.
    KanjiNum3,
    /// Numeric formatting. Ordinal (1st, 2nd, 3rd, ...).
    Ordinal,
    /// Numeric formatting. Ordinal text (First, Second, Third, ...).
    OrdText,
    /// Numeric formatting. Uppercase Roman (I, II, III, ...).
    UppercaseRoman,
    /// Numeric formatting. Lowercase Roman (i, ii, iii, ...).
    LowercaseRoman,
    /// Numeric formatting. Formats a numeric result using single-byte Arabic numbering.
    SBChar,
    /// Numeric formatting. Formats a numeric result using Thai numbers.
    ThaiArabic,
    /// Numeric formatting. Formats a numeric result using sequential numbers from the Thai counting system.
    ThaiCardText,
    /// Numeric formatting. Formats a numeric result using Thai letters.
    ThaiLetter,
    /// Numeric formatting. Formats a numeric result using Vietnamese numerals.
    VietCardText,
    /// Numeric formatting. Formats a numeric result using sequential numerical traditional ideographs.
    Zodiac1,
    /// Numeric formatting. Formats a numeric result using sequential zodiac ideographs.
    Zodiac2,
    /// Numeric formatting. Formats a numeric result using sequential traditional zodiac ideographs.
    Zodiac3,
    /// Text formatting. Capitalizes the first letter of each word.
    Caps,
    /// Text formatting. Capitalizes the first letter of the first word.
    FirstCap,
    /// Text formatting. All letters are lowercase.
    Lower,
    /// Text formatting. All letters are uppercase.
    Upper,
    /// Field result formatting. The CHARFORMAT instruction.
    CharFormat,
    /// Field result formatting. The MERGEFORMAT instruction.
    MergeFormat,
    /// Field result formatting. The MERGEFORMATINET instruction.
    MergeFormatInet
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fields::GeneralFormat>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fields::GeneralFormat, const char_t*>, 56>& values();
};
