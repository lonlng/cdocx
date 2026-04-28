/// @file xml/schema/xml_schema_attribute_groupref.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c attributeGroup element with the @c ref attribute from the XML Schema as specified by
/// the [World Wide Web Consortium (W3C)](https://go.microsoft.com/fwlink/?LinkId=49454).
/// AttributesGroupRef is the reference for an attributeGroup, name property contains the attribute group being referenced.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAttributeGroupRef : public XmlSchemaAnnotated
{
    typedef XmlSchemaAttributeGroupRef ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAttributeGroupRef>;

public:

    /// Returns the name of the referenced @c attributeGroup element.
    /// @returns The name of the referenced attribute group. The value must be a QName.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_RefName();
    /// Sets the name of the referenced @c attributeGroup element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_RefName(const SharedPtr<XmlQualifiedName>& value);

    /// Initializes a new instance of the XmlSchemaAttributeGroupRef class.
    ASPOSECPP_SHARED_API XmlSchemaAttributeGroupRef();

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
    const char* DBG_class_name() const override { return "XmlSchemaAttributeGroupRef"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _refName;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


