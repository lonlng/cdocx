#pragma once

#include <system/enum.h>

namespace System {

namespace Diagnostics {

/// Identifies the type of event that has caused the trace.
enum class TraceEventType
{
    /// Fatal error or application crash.
    Critical = 1,
    /// Recoverable error.
    Error = 2,
    /// Noncritical problem.
    Warning = 4,
    /// Informational message.
    Information = 8,
    /// Debugging trace.
    Verbose = 16,
    /// Starting of a logical operation.
    Start = 256,
    /// Stopping of a logical operation.
    Stop = 512,
    /// Suspension of a logical operation.
    Suspend = 1024,
    /// Resumption of a logical operation.
    Resume = 2048,
    /// Changing of correlation identity.
    Transfer = 4096
};

} // namespace Diagnostics
} // namespace System

template<>
struct EnumMetaInfo<System::Diagnostics::TraceEventType>
{
    static const std::array<std::pair<System::Diagnostics::TraceEventType, const char_t*>, 10>& values();
};



