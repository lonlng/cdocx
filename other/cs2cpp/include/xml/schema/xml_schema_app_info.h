/// @file xml/schema/xml_schema_app_info.h

#pragma once

#include <xml/schema/xml_schema_object.h>
#include <system/array.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the World Wide Web Consortium (W3C) @c appinfo element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAppInfo : public XmlSchemaObject
{
    typedef XmlSchemaAppInfo ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAppInfo>;

public:

    /// Returns the source of the application information.
    /// @returns A Uniform Resource Identifier (URI) reference. The default is String::Empty. Optional.
    ASPOSECPP_SHARED_API String get_Source();
    /// Sets the source of the application information.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Source(const String& value);
    /// Returns an array of XmlNode objects that represents the @c appinfo child nodes.
    /// @returns An array of XmlNode objects that represents the @c appinfo child nodes.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlNode>> get_Markup();
    /// Sets an array of XmlNode objects that represents the @c appinfo child nodes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Markup(const ArrayPtr<SharedPtr<XmlNode>>& value);

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
    const char* DBG_class_name() const override { return "XmlSchemaAppInfo"; }
#endif
    /// @endcond

private:

    String _source;
    ArrayPtr<SharedPtr<XmlNode>> _markup;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


