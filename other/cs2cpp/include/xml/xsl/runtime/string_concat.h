/// @file xml/xsl/runtime/string_concat.h

#pragma once

#include <system/string.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class XmlEventCache;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

namespace Runtime {

/// Concatenates strings when the number of strings is not known beforehand.
class ASPOSECPP_SHARED_CLASS StringConcat : public System::Object
{
    typedef StringConcat ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

    /// @cond
    friend class System::Xml::XmlEventCache;
    /// @endcond

public:

    /// Returns the string that delimits concatenated strings.
    /// @returns The string delimiter.
    ASPOSECPP_SHARED_API String get_Delimiter();
    /// Sets the string that delimits concatenated strings.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Delimiter(const String& value);

    /// Clears the result string.
    ASPOSECPP_SHARED_API void Clear();
    /// Concatenates a new string to the result.
    /// @param value A @c string value to be concatenated to the result.
    ASPOSECPP_SHARED_API void Concat(const String& value);
    /// Returns the result string.
    /// @returns A @c string value that contains the result.
    ASPOSECPP_SHARED_API String GetResult();

    /// Default constructor.
    ASPOSECPP_SHARED_API StringConcat();

protected:

    /// @cond
    int32_t get_Count();

    void ConcatNoDelimiter(const String& s);

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
    const char* DBG_class_name() const override { return "StringConcat"; }
#endif
    /// @endcond

private:

    String _s1, _s2, _s3, _s4;
    String _delimiter;
    SharedPtr<Collections::Generic::List<String>> _strList;
    int32_t _idxStr;

};

} // namespace Runtime
} // namespace Xsl
} // namespace Xml
} // namespace System


