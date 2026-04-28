/// @file system/byte.h
#pragma once

#include <system/string.h>
#include <system/iformatprovider.h>
#include <system/globalization/number_styles.h>
#include <limits>

namespace System {

namespace Globalization {
    class CultureInfo;
    class NumberFormatInfo;
}

/// Contains methods to work with the unsigned 8-bit integer.
/// @code
/// #include <system/byte.h>
///
/// using namespace System;
///
/// int main()
/// {
///   auto b1 = Byte::Parse(u"123");
///   std::cout << static_cast<uint32_t>(b1) << std::endl;
///
///   try
///   {
///     auto b2 = Byte::Parse(u"345");
///     std::cout << static_cast<uint32_t>(b2) << std::endl;
///   }
///   catch (const OverflowException &ex)
///   {
///     std::cerr << ex.what() << std::endl;
///   }
///
///   uint8_t b3 = 0;
///   if (Byte::TryParse(u"10", b3))
///   {
///     std::cout << static_cast<uint32_t>(b3) << std::endl;
///   }
///   else
///   {
///     std::cerr << "Something went wrong." << std::endl;
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 123
/// System::OverflowException: Value was either too large or too small for an UInt8
/// 10
/// */
/// @endcode
class Byte
{
    RTTI_INFO_VALUE_TYPE(Byte)
public:
    /// Smallest possible value.
    static ASPOSECPP_SHARED_API constexpr uint8_t MinValue = 0;
    /// Largest possible value.
    static ASPOSECPP_SHARED_API constexpr uint8_t MaxValue = (std::numeric_limits<uint8_t>::max)();

    /// Converts the specified string containing the string representation of a number to the equivalent 8-bit unsigned integer.
    /// @param value The string to convert.
    /// @returns The 8-bit unsigned integer equal to the number represented by the specified string.
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value);

    /// Converts the specified string containing the string representation of a number to the equivalent 8-bit unsigned integer using the provided formatting information.
    /// @param value The string to convert.
    /// @param provider A pointer to an object that contains the string format information.
    /// @returns The 8-bit unsigned integer equal to the number represented by the specified string.
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, const SharedPtr<IFormatProvider>& provider);
    // Optimized function overloads
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, const SharedPtr<Globalization::CultureInfo>& culture);
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, const SharedPtr<Globalization::NumberFormatInfo>& nfi);
    static uint8_t Parse(const String& value, std::nullptr_t) { return Parse(value); }

    /// Converts the specified string containing the string representation of a number to the equivalent 8-bit unsigned integer using the provided formatting information and number style.
    /// @param value The string to convert.
    /// @param styles A bitwise combination of values of NumberStyles enum that specifies the permitted style of the string representation of a number.
    /// @param provider A pointer to an object that contains the string format information.
    /// @returns The 8-bit unsigned integer equal to the number represented by the specified string.
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, Globalization::NumberStyles styles, const SharedPtr<IFormatProvider>& provider);
    // Optimized function overloads
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, Globalization::NumberStyles styles, const SharedPtr<Globalization::CultureInfo>& culture);
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, Globalization::NumberStyles styles, const SharedPtr<Globalization::NumberFormatInfo>& nfi);
    static ASPOSECPP_SHARED_API uint8_t Parse(const String& value, Globalization::NumberStyles styles, std::nullptr_t = nullptr);

    /// Converts the specified string containing the string representation of a number to the equivalent 8-bit unsigned integer.
    /// @param value The string to convert.
    /// @param result The reference to a 8-bit unsigned integer variable where the result of the conversion is put.
    /// @returns True if the conversion succeeded, otherwise - false.
    static ASPOSECPP_SHARED_API bool TryParse(const String& value, uint8_t& result);

    /// Converts the specified string containing the string representation of a number to the equivalent 8-bit unsigned integer using the provided formatting information and number style.
    /// @param value The string to convert.
    /// @param styles A bitwise combination of values of NumberStyles enum that specifies the permitted style of the string representation of a number.
    /// @param provider A pointer to an object that contains the string format information.
    /// @param result The reference to a 8-bit unsigned integer variable where the result of the conversion is put.
    /// @returns True if the conversion succeeded, otherwise - false.
    static ASPOSECPP_SHARED_API bool TryParse(const String& value, Globalization::NumberStyles styles, const SharedPtr<IFormatProvider>& provider, uint8_t& result);
    // Optimized function overloads
    static ASPOSECPP_SHARED_API bool TryParse(const String& value, Globalization::NumberStyles styles, const SharedPtr<Globalization::CultureInfo>& culture, uint8_t& result);
    static ASPOSECPP_SHARED_API bool TryParse(const String& value, Globalization::NumberStyles styles, const SharedPtr<Globalization::NumberFormatInfo>& nfi, uint8_t& result);
    static ASPOSECPP_SHARED_API bool TryParse(const String& value, Globalization::NumberStyles styles, std::nullptr_t, uint8_t& result);
};

} // namespace System
