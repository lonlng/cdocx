//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtCalendarType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies the possible types of calendars which can be used to specify <see cref="Aspose::Words::Markup::StructuredDocumentTag::get_CalendarType">CalendarType</see>
/// in an Office Open XML document.
enum class ASPOSE_WORDS_SHARED_CLASS SdtCalendarType
{
    /// Used as default value in OOXML. Equals <see cref="Aspose::Words::Markup::SdtCalendarType::Gregorian">Gregorian</see>.
    Default,
    /// Specifies that the Gregorian calendar, as defined in ISO  8601, shall be used.
    /// This calendar should be localized into the appropriate language.
    Gregorian = static_cast<int32_t>(Default),
    /// Specifies that the Gregorian calendar, as defined in ISO 8601, shall be used.
    /// The values for this calendar should be presented in Arabic.
    GregorianArabic,
    /// Specifies that the Gregorian calendar, as defined in ISO 8601, shall be used.
    /// The values for this calendar should be presented in Middle East French.
    GregorianMeFrench,
    /// Specifies that the Gregorian calendar, as defined in ISO 8601, shall be used.
    /// The values for this calendar should be presented in English.
    GregorianUs,
    /// Specifies that the Gregorian calendar, as defined in ISO 8601, shall be used.
    /// The values for this calendar should be the representation of the English strings in the corresponding Arabic characters
    /// (the Arabic transliteration of the English for the Gregorian calendar).
    GregorianXlitEnglish,
    /// Specifies that the Gregorian calendar, as defined in ISO 8601, shall be used.
    /// The values for this calendar should be the representation of the French strings in the corresponding Arabic characters
    /// (the Arabic transliteration of the French for the Gregorian calendar).
    GregorianXlitFrench,
    /// Specifies that the Hebrew lunar calendar, as described by the Gauss formula for Passover [CITATION]
    /// and The Complete Restatement of Oral Law (Mishneh Torah),shall be used.
    Hebrew,
    /// Specifies that the Hijri lunar calendar, as described by the Kingdom of Saudi Arabia,
    /// Ministry of Islamic Affairs, Endowments, Da‘wah and Guidance, shall be used.
    Hijri,
    /// Specifies that the Japanese Emperor Era calendar, as described by
    /// Japanese Industrial Standard JIS X 0301, shall be used.
    Japan,
    /// Specifies that the Korean Tangun Era calendar,
    /// as described by Korean Law Enactment No. 4, shall be used.
    Korea,
    /// Specifies that no calendar should be used.
    None,
    /// Specifies that the Saka Era calendar, as described by the Calendar Reform Committee of India,
    /// as part of the Indian Ephemeris and Nautical Almanac, shall be used.
    Saka,
    /// Specifies that the Taiwanese calendar, as defined by the Chinese National Standard CNS 7648, shall be used.
    Taiwan,
    /// Specifies that the Thai calendar, as defined by the Royal Decree of H.M. King Vajiravudh (Rama VI) in
    /// Royal Gazette B. E. 2456 (1913 A.D.) and by the decree of Prime Minister Phibunsongkhram (1941 A.D.) to
    /// start the year on the Gregorian January 1 and to map year zero to Gregorian year 543 B.C., shall be used.
    Thai
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Markup::SdtCalendarType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Markup::SdtCalendarType, const char_t*>, 15>& values();
};
