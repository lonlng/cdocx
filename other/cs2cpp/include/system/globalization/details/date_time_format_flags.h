/// @file system/globalization/details/date_time_format_flags.h
#pragma once

#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Globalization { namespace Details {

/// Bit flags, used in parsing/formatting.
enum class DateTimeFormatFlags : unsigned
{
    None = 0,
    UseGenitiveMonth = 1,
    UseLeapYearMonth = 2,
    UseSpacesInMonthNames = 4,
    UseHebrewRule = 8,
    UseSpacesInDayNames = 16,
    UseDigitPrefixInTokens = 32,
};

/// @cond
/// Declaration of template arithmetic operators for values of the DateTimeFormatFlags enum type.
DECLARE_ENUM_OPERATORS(System::Globalization::Details::DateTimeFormatFlags);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}}} // namespace System::Globalization::Details

/// Inserts using declaratios for arithmetic operators declared in namespace System::Globalization::Details.
DECLARE_USING_ENUM_OPERATORS(System::Globalization::Details);

template<>
struct EnumMetaInfo<System::Globalization::Details::DateTimeFormatFlags>
{
    typedef void Flags;
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Globalization::Details::DateTimeFormatFlags, const char16_t*>, 7>& values();
};
