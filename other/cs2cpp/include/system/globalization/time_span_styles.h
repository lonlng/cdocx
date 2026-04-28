/// @file system/globalization/time_span_styles.h
#pragma once

#include <cstdint>
#include <system/details/enum_meta_info.h>
#include <system/enum_helpers.h>

namespace System { namespace Globalization {

/// Specifies the formatting options that customize string parsing for methods that convert a string representation of a time interval into Timespan object.
enum class TimeSpanStyles : int32_t
{
    /// The time interval represented by the inptut string is interpreted as a negative time interval only if a negative sign is present.
    None = 0,
    /// The time interval represented by the inptut string is interpreted as a negative time interval always.
    AssumeNegative = 1
};

/// @cond
/// Declaration of template arithmetic operators for values of the TimeSpanStyles enum type.
DECLARE_ENUM_OPERATORS(System::Globalization::TimeSpanStyles);
/// Import of global operators into current namespace.
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond
}} // namespace System::Globalization

/// Inserts using declaratios for arithmetic operators declared in namespace System::Globalization.
DECLARE_USING_ENUM_OPERATORS(System::Globalization);

template<>
struct EnumMetaInfo<System::Globalization::TimeSpanStyles>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Globalization::TimeSpanStyles, const char16_t*>, 2>& values();
};
