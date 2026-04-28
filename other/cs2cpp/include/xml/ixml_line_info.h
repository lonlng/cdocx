/// @file xml/ixml_line_info.h

#pragma once

#include <system/object.h>
#include <cstdint>


namespace System {

namespace Xml {

/// Provides an interface to enable a class to return line and position information.
class ASPOSECPP_SHARED_CLASS IXmlLineInfo : public virtual System::Object
{
    typedef IXmlLineInfo ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the current line number.
    /// @returns The current line number or 0 if no line information is available
    /// (for example, IXmlLineInfo::HasLineInfo returns @c false).
    virtual int32_t get_LineNumber() = 0;
    /// Returns the current line position.
    /// @returns The current line position or 0 if no line information is available
    /// (for example, IXmlLineInfo::HasLineInfo returns @c false).
    virtual int32_t get_LinePosition() = 0;

    /// Returns a value indicating whether the class can return line information.
    /// @returns @c true if IXmlLineInfo::get_LineNumber and IXmlLineInfo::get_LinePosition can be provided;
    /// otherwise, @c false.
    virtual bool HasLineInfo() = 0;

};

} // namespace Xml
} // namespace System


