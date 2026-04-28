/// @file system/day_of_week.h
#pragma once

#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System {

/// Enumeration that represents a day of week.
enum class DayOfWeek : int
{
    Sunday = 0,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday
};

/// Calculates the number of days between two days of week.
/// @param a The minuend
/// @param b The subtrahend
/// @returns The number of days between weekdays @p a and @p b; the return value is a negative number if @a goes after @b
inline auto operator-(DayOfWeek a, DayOfWeek b)
{
    using underlying_type = std::underlying_type<DayOfWeek>::type;
    return static_cast<underlying_type>(a) - static_cast<underlying_type>(b);
}

/// @cond
/// Declaration of template arithmetic operators for values of the DayOfWeek enum type.
DECLARE_ENUM_OPERATORS(System::DayOfWeek);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
} // namespace System

/// Inserts using declaratios for arithmetic operators declared in namespace System.
DECLARE_USING_ENUM_OPERATORS(System);

/// Specialization for System::DayOfWeek enum.
template<>
struct EnumMetaInfo<System::DayOfWeek>
{
    /// Returns an array of pairs that map System::DayOfWeek enum values to corresponding string names.
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::DayOfWeek, const char16_t*>, 7>& values();
};
