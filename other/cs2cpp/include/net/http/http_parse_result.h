/// @file net/http/http_parse_result.h
#pragma once

namespace System { namespace Net { namespace Http {

/// Indicates the parsing result.
enum class HttpParseResult
{
    /// The parsing is successfully done.
    Parsed,
    /// The string to parse starts with an invalid character.
    NotParsed,
    /// The string to parse has an invalid format.
    InvalidFormat
};
}}} // namespace System::Net::Http
