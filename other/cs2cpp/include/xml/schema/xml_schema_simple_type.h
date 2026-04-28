/// @file xml/schema/xml_schema_simple_type.h

#pragma once

#include <xml/schema/xml_schema_type.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class DatatypeImplementation;
class XmlSchemaObject;
class XmlSchemaSimpleTypeContent;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c simpleType element for simple content from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class defines a simple type. Simple types can specify information and constraints for the value of attributes or elements with text-only content.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleType : public XmlSchemaType
{
    typedef XmlSchemaSimpleType ThisType;
    typedef XmlSchemaType BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleType>;

private:
    /// @cond
    friend class DatatypeImplementation;
    /// @endcond

public:

    /// Returns one of XmlSchemaSimpleTypeUnion, XmlSchemaSimpleTypeList, or XmlSchemaSimpleTypeRestriction.
    /// @returns One of XmlSchemaSimpleTypeUnion, XmlSchemaSimpleTypeList, or XmlSchemaSimpleTypeRestriction.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaSimpleTypeContent> get_Content();
    /// Sets one of XmlSchemaSimpleTypeUnion, XmlSchemaSimpleTypeList, or XmlSchemaSimpleTypeRestriction.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Content(const SharedPtr<XmlSchemaSimpleTypeContent>& value);

    /// Initializes a new instance of the XmlSchemaSimpleType class.
    ASPOSECPP_SHARED_API XmlSchemaSimpleType();

protected:

    /// @cond
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_DerivedFrom() override;

    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;

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
    const char* DBG_class_name() const override { return "XmlSchemaSimpleType"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaSimpleTypeContent> _content;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


