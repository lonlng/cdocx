/// @file xml/name_table.h

#pragma once

#include <xml/xml_name_table.h>
#include <system/array.h>
#include <cstdint>


namespace System {

namespace Xml {

/// Implements a single-threaded XmlNameTable.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS NameTable : public XmlNameTable
{
    typedef NameTable ThisType;
    typedef XmlNameTable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<NameTable>;

private:

    class Entry : public System::Object
    {
        typedef Entry ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        String str;
        int32_t hashCode;
        SharedPtr<NameTable::Entry> next;

        Entry(const String& str, int32_t hashCode, const SharedPtr<NameTable::Entry>& next);
        /// @endcond

    protected:

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override;
        #endif

        #ifdef __DBG_FOR_EACH_MEMBER
        public:
            /// Applies visitor to members.
            /// @param visitor Visitor to apply.
            ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
            /// Gets class name.
            /// @return String literal pointer.
            const char* DBG_class_name() const override { return "Entry"; }
        #endif


    };


public:

    /// Initializes a new instance of the NameTable class.
    ASPOSECPP_SHARED_API NameTable();

    /// Atomizes the specified string and adds it to the NameTable.
    /// @param key The string to add.
    /// @returns The atomized string or the existing string if it already exists in the NameTable.
    /// @throws ArgumentNullException @p key is @c nullptr.
    ASPOSECPP_SHARED_API const String& Add(const String& key) override;
    /// Atomizes the specified string and adds it to the NameTable.
    /// @param key The character array containing the string to add.
    /// @param start The zero-based index into the array specifying the first character of the string.
    /// @param len The number of characters in the string.
    /// @returns The atomized string or the existing string if one already exists in the NameTable.
    /// If @p len is zero, String::Empty is returned.
    /// @throws IndexOutOfRangeException 0 > @p start
    /// or
    /// @p start >= @p key.Length
    /// or
    /// @p len >= @p key.Length
    /// The above conditions do not cause an exception to be thrown if @p len = 0.
    /// @throws ArgumentOutOfRangeException @p len < 0.
    ASPOSECPP_SHARED_API const String& Add(const ArrayPtr<char16_t>& key, int32_t start, int32_t len) override;
    /// Returns the atomized string with the specified value.
    /// @param value The name to find.
    /// @returns The atomized string object or @c nullptr if the string has not already been atomized.
    /// @throws ArgumentNullException @p value is @c nullptr.
    ASPOSECPP_SHARED_API const String& Get(const String& value) override;
    /// Returns the atomized string containing the same characters as the specified range of characters in the given array.
    /// @param key The character array containing the name to find.
    /// @param start The zero-based index into the array specifying the first character of the name.
    /// @param len The number of characters in the name.
    /// @returns The atomized string or @c nullptr if the string has not already been atomized.
    /// If @p len is zero, String::Empty is returned.
    /// @throws IndexOutOfRangeException 0 > @p start
    /// or
    /// @p start >= @p key.Length
    /// or
    /// @p len >= @p key.Length
    /// The above conditions do not cause an exception to be thrown if @p len = 0.
    /// @throws ArgumentOutOfRangeException @p len < 0.
    ASPOSECPP_SHARED_API const String& Get(const ArrayPtr<char16_t>& key, int32_t start, int32_t len) override;

protected:

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "NameTable"; }
#endif
    /// @endcond

private:

    ArrayPtr<SharedPtr<NameTable::Entry>> _entries;
    int32_t _count;
    int32_t _mask;

    const String& AddEntry(const String& str, int32_t hashCode);
    void Grow();
    static bool TextEquals(const String& str1, const ArrayPtr<char16_t>& str2, int32_t str2Start, int32_t str2Length);
    static int32_t ComputeHash32(const String& key);
    static int32_t ComputeHash32(const ArrayPtr<char16_t>& key, int32_t start, int32_t len);

};

} // namespace Xml
} // namespace System


