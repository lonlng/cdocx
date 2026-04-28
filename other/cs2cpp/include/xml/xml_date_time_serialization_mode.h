/// @file xml/xml_date_time_serialization_mode.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies how to treat the time value when converting between string and DateTime.
enum class XmlDateTimeSerializationMode
{
    /// Treat as local time.
    /// If the DateTime object represents a Coordinated Universal Time (UTC), it is converted to the local time.
    Local,
    /// Treat as a UTC.
    /// If the DateTime object represents a local time, it is converted to a UTC.
    Utc,
    /// Treat as a local time if a DateTime is being converted to a string.
    /// If a string is being converted to DateTime, convert to a local time if a time zone is specified.
    Unspecified,
    /// Time zone information should be preserved when converting.
    RoundtripKind
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlDateTimeSerializationMode>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlDateTimeSerializationMode, const char_t*>, 4>& values();
};
/// @endcond


