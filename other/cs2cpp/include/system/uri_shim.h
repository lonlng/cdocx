/// @file system/uri_shim.h
#pragma once
#include <system/string.h>
#include <system/object.h>
#include <system/array.h>
#include <cstdint>

namespace System {

/// Service class.
class UriShim
{
public:
    /// Converts character to escaped hex form.
    /// @param character Character to convert.
    /// @return Escaped value.
    ASPOSECPP_SHARED_API static String HexEscape(char16_t character);
    /// Converts character from escaped hex form.
    /// @param pattern String to read escaped hex form from.
    /// @param index Offset in the given string.
    /// @return Decoded character.
    ASPOSECPP_SHARED_API static char16_t HexUnescape(const String& pattern, int32_t& index);
    /// Checks if given pattern is an escaped hex form.
    /// @param pattern String to read escaped hex form from.
    /// @param index Offset in the given string.
    /// @return True if there's an escaped hex pattern at given position, false otherwise.
    ASPOSECPP_SHARED_API static bool IsHexEncoding(const String& pattern, int32_t index);
    /// Converts character to escaped hex form.
    /// @param ch Character to convert.
    /// @param to Output buffer.
    /// @param pos Position in output buffer; gets advanced after encoding.
    ASPOSECPP_SHARED_API static void EscapeAsciiChar(char16_t ch, const System::ArrayPtr<char16_t>& to, int32_t& pos);
private:
    static const char16_t c_DummyChar;
    static System::ArrayPtr<char16_t> s_hexUpperChars;
    static char16_t EscapedAscii(char16_t digit, char16_t next);
};

} // namespace System

