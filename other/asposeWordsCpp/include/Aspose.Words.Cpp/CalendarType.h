//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/CalendarType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the type of a calendar.
enum class ASPOSE_WORDS_SHARED_CLASS CalendarType
{
    /// The Gregorian calendar.
    Gregorian,
    /// The Hijri Lunar calendar.
    Hijri,
    /// The Hebrew Lunar calendar.
    Hebrew,
    /// The Saka Era calendar.
    SakaEra,
    /// The Um-al-Qura calendar.
    UmAlQura
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::CalendarType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::CalendarType, const char_t*>, 5>& values();
};
