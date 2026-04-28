/// @file xml/xml_name_table.h

#pragma once

#include <system/array.h>
#include <cstdint>


namespace System {

namespace Xml {

/// Table of atomized string objects.
class ASPOSECPP_SHARED_CLASS XmlNameTable : public System::Object
{
    typedef XmlNameTable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNameTable>;

public:

    /// When overridden in a derived class, gets the atomized string containing the same characters as
    /// the specified range of characters in the given array.
    /// @param array The character array containing the name to look up.
    /// @param offset The zero-based index into the array specifying the first character of the name.
    /// @param length The number of characters in the name.
    /// @returns The atomized string or @c nullptr if the string has not already been atomized.
    /// If @p length is zero, String::Empty is returned.
    /// @throws IndexOutOfRangeException 0 > @p offset
    /// or
    /// @p offset >= @p array.Length
    /// or
    /// @p length > @p array.Length
    /// The above conditions do not cause an exception to be thrown if @p length = 0.
    /// @throws ArgumentOutOfRangeException @p length < 0.
    virtual ASPOSECPP_SHARED_API const String& Get(const ArrayPtr<char16_t>& array, int32_t offset, int32_t length) = 0;
    /// When overridden in a derived class, gets the atomized string containing the same value as the specified string.
    /// @param array The name to look up.
    /// @returns The atomized string or @c nullptr if the string has not already been atomized.
    /// @throws ArgumentNullException @p array is @c nullptr.
    virtual ASPOSECPP_SHARED_API const String& Get(const String& array) = 0;
    /// When overridden in a derived class, atomizes the specified string and adds it to the XmlNameTable.
    /// @param array The character array containing the name to add.
    /// @param offset Zero-based index into the array specifying the first character of the name.
    /// @param length The number of characters in the name.
    /// @returns The new atomized string or the existing one if it already exists.
    /// If length is zero, String::Empty is returned.
    /// @throws IndexOutOfRangeException 0 > @p offset
    /// or
    /// @p offset >= @p array.Length
    /// or
    /// @p length > @p array.Length
    /// The above conditions do not cause an exception to be thrown if @p length = 0.
    /// @throws ArgumentOutOfRangeException @p length < 0.
    virtual ASPOSECPP_SHARED_API const String& Add(const ArrayPtr<char16_t>& array, int32_t offset, int32_t length) = 0;
    /// When overridden in a derived class, atomizes the specified string and adds it to the XmlNameTable.
    /// @param array The name to add.
    /// @returns The new atomized string or the existing one if it already exists.
    /// @throws ArgumentNullException @p array is @c nullptr.
    virtual ASPOSECPP_SHARED_API const String& Add(const String& array) = 0;

};

} // namespace Xml
} // namespace System


