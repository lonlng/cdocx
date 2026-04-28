/// @file system/web/http_utility.h
#pragma once

#include "fwd.h"
#include <system/array.h>
#include <system/text/encoding.h>
#include <system/exceptions.h>
#include <system/collections/list.h>
#include <system/io/text_writer.h>

namespace System { namespace Web {

/// Service class that encodes and decodes URL parts to and from hex escape fragments.
class ASPOSECPP_SHARED_CLASS HttpUtility : public Object
{
public:
    /// Decodes URI fragment from string.
    /// @param str Encoded URI fragment.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlDecode(String str);
    /// Decodes URI fragment from string.
    /// @param str Encoded URI fragment.
    /// @param e Encoding to use.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlDecode(String str, System::SharedPtr<Text::Encoding> e);
    /// Decodes URI fragment from bytes array.
    /// @param bytes Encoded URI fragment.
    /// @param e Encoding to use.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlDecode(const System::ArrayPtr<uint8_t>& bytes, const System::SharedPtr<Text::Encoding>& e);
    /// Decodes URI fragment from bytes array.
    /// @param bytes Encoded URI fragment.
    /// @param offset Offset in the given byte array.
    /// @param count Number of bytes to read from.
    /// @param e Encoding to use.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlDecode(const System::ArrayPtr<uint8_t>& bytes, int32_t offset, int32_t count, const System::SharedPtr<Text::Encoding>& e);
    /// Decodes URI fragment from bytes array.
    /// @param bytes Encoded URI fragment.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlDecodeToBytes(const System::ArrayPtr<uint8_t>& bytes);
    /// Decodes URI fragment from bytes string.
    /// @param str Encoded URI fragment.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlDecodeToBytes(const String& str);
    /// Decodes URI fragment from string.
    /// @param str Encoded URI fragment.
    /// @param e Encoding to use.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlDecodeToBytes(const String& str, const System::SharedPtr<Text::Encoding>& e);
    /// Decodes URI fragment from bytes array.
    /// @param bytes Encoded URI fragment.
    /// @param offset Offset in the given byte array.
    /// @param count Number of bytes to read from.
    /// @return Decoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlDecodeToBytes(const System::ArrayPtr<uint8_t>& bytes, int32_t offset, int32_t count);
    /// Decodes Html fragment.
    /// @param str Html fragment to decode.
    /// @return Decoded Html fragment.
    static ASPOSECPP_SHARED_API String HtmlDecode(const String& str);
    /// Decodes Html fragment.
    /// @param str Html fragment to decode.
    /// @param output A TextWriter object for output.
    static ASPOSECPP_SHARED_API void HtmlDecode(const String& str, const SharedPtr<IO::TextWriter>& output);
    /// Encodes Html fragment.
    /// @param str Html fragment to encode.
    /// @return Encoded Html fragment.
    static ASPOSECPP_SHARED_API String HtmlEncode(const String& str);
    /// Encodes Html fragment.
    /// @param value Html fragment to encode.
    /// @return Encoded Html fragment.
    static ASPOSECPP_SHARED_API String HtmlEncode(const SharedPtr<Object>& value);
    /// Encodes Html fragment.
    /// @param str Html fragment to encode.
    /// @param output A TextWriter object for output.
    static ASPOSECPP_SHARED_API void HtmlEncode(const String& str, const SharedPtr<IO::TextWriter>& output);
    /// Encodes URI fragment.
    /// @param str URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlEncode(String str);
    /// Encodes URI fragment.
    /// @param str URI fragment to encode.
    /// @param e Encoding to use.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlEncode(String str, const System::SharedPtr<Text::Encoding>& e);
    /// Encodes URI fragment.
    /// @param bytes URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlEncode(const System::ArrayPtr<uint8_t>& bytes);
    /// Encodes URI fragment.
    /// @param bytes URI fragment to encode.
    /// @param offset Offset in the given byte array.
    /// @param count Number of bytes to read from.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlEncode(const System::ArrayPtr<uint8_t>& bytes, int32_t offset, int32_t count);
    /// Encodes URI fragment.
    /// @param str URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlEncodeToBytes(const String& str);
    /// Encodes URI fragment.
    /// @param str URI fragment to encode.
    /// @param e Encoding to use.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlEncodeToBytes(const String& str, const System::SharedPtr<Text::Encoding>& e);
    /// Encodes URI fragment.
    /// @param bytes URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlEncodeToBytes(const System::ArrayPtr<uint8_t>& bytes);
    /// Encodes URI fragment.
    /// @param bytes URI fragment to encode.
    /// @param offset Offset in the given byte array.
    /// @param count Number of bytes to read from.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlEncodeToBytes(const System::ArrayPtr<uint8_t>& bytes, int32_t offset, int32_t count);
    /// Encodes URI fragment usign Unicode.
    /// @param str URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API String UrlEncodeUnicode(const String& str);
    /// Encodes URI fragment usign Unicode.
    /// @param str URI fragment to encode.
    /// @return Encoded URI fragment.
    static ASPOSECPP_SHARED_API System::ArrayPtr<uint8_t> UrlEncodeUnicodeToBytes(const String& str);

private:
    static System::ArrayPtr<char16_t> GetChars(const System::SharedPtr<IO::MemoryStream>& b, const System::SharedPtr<Text::Encoding>& e);
    static void WriteCharBytes(const System::SharedPtr<System::Collections::Generic::List<uint8_t>>& buf, char16_t ch, const System::SharedPtr<Text::Encoding>& e);
    static int32_t GetInt(uint8_t b);
    static int32_t GetChar(const System::ArrayPtr<uint8_t>& bytes, int32_t offset, int32_t length);
    static int32_t GetChar(const String& str, int32_t offset, int32_t length);
};

}} // System::Web
