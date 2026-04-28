/// @file system/uri_parser.h
/// Contains the declaration of System::UriParser class and supporting types.
#pragma once

#include <system/string.h>

namespace System {

/// Used to parse a new URI scheme.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class UriParser
{
public:
    /// Indicates whether the parser for a scheme is registered
    /// @param schemeName The scheme name to check
    /// @returns True if @p schemeName has been registered; otherwise, false
    static ASPOSECPP_SHARED_API bool IsKnownScheme(const String& schemeName);

    UriParser() = delete;
};

} // namespace System
