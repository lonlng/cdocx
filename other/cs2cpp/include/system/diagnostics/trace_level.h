#pragma once

#include "system/enum.h"

namespace System { namespace Diagnostics {
    /// Specifies what messages to output for the System.Diagnostics.Debug, System.Diagnostics.Trace
    /// and System.Diagnostics.TraceSwitch classes.
    enum class TraceLevel
    {
        ///     Output no tracing and debugging messages.
        Off = 0,
        ///     Output error-handling messages.
        Error = 1,
        ///     Output warnings and error-handling messages.
        Warning = 2,
        ///     Output informational messages, warnings, and error-handling messages.
        Info = 3,
        ///     Output all debugging and tracing messages.
        Verbose = 4
    };

}}

template<>
struct EnumMetaInfo<System::Diagnostics::TraceLevel>
{
    static ASPOSECPP_SHARED_API const std::array<std::pair<System::Diagnostics::TraceLevel, const char_t*>, 5>& values();
};


