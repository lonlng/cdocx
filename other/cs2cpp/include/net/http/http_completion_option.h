/// @file net/http/http_completion_option.h
#pragma once

namespace System { namespace Net { namespace Http {

/// Indicates when an HttpClient operation should be completed.
enum class HttpCompletionOption
{
    /// The operation should be complete after reading response content.
    ResponseContentRead = 0,
    /// The operation should be complete after reading headers of a response.
    ResponseHeadersRead
};
}}} // namespace System::Net::Http
