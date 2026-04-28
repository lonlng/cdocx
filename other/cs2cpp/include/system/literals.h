/// @file system/literals.h
/// User literals are defined in the global namespace. To minimize the risk of collisions with other user code,
/// we will place them in a separate file and include them as needed.
#pragma once

#include <system/string.h>
#include <system/decimal.h>

/// @brief User-defined literal for converting string literals to System::String
/// @param str Pointer to the beginning of the character sequence
/// @param length Length of the character sequence
/// @return System::String object containing the converted string
/// @note This literal allows easy conversion from UTF-16 string literals to System::String
inline System::String operator"" _s(const char16_t* str, std::size_t length)
{
    return System::String(str, (int32_t)length);
}

/// @brief User-defined literal for converting string literals to System::Decimal
/// @param str Pointer to the beginning of the character sequence
/// @param length Length of the character sequence
/// @return System::Decimal object parsed from the string representation
/// @note The string must represent a valid decimal number format
inline System::Decimal operator"" _d(const char* str, std::size_t length)
{
    return System::Decimal(std::string(str, length));
}

/// @brief User-defined literal for converting integer litrals to System::Decimal
/// @param value Unsigned long integer value
/// @return System::Decimal object costructed from the given number
/// @note The translator doesn't use this literal bacuse of possible performance issues.
inline System::Decimal operator"" _d(unsigned long long value)
{
    return System::Decimal(static_cast<uint64_t>(value));
}
