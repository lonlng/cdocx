/// @file xml/schema/xml_schema_annotation.h

#pragma once

#include <xml/schema/xml_schema_object.h>
#include <system/array.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaObjectCollection;
} // namespace Schema
class XmlAttribute;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the World Wide Web Consortium (W3C) @c annotation element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAnnotation : public XmlSchemaObject
{
    typedef XmlSchemaAnnotation ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAnnotation>;

public:

    /// Returns the string id.
    /// @returns The string id. The default is String::Empty. Optional.
    ASPOSECPP_SHARED_API String get_Id();
    /// Sets the string id.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Id(const String& value);
    /// Returns the @c Items collection that is used to store the @c appinfo and @c documentation child elements.
    /// @returns An XmlSchemaObjectCollection of @c appinfo and @c documentation child elements.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Items();
    /// Returns the qualified attributes that do not belong to the schema's target namespace.
    /// @returns An array of XmlAttribute objects that do not belong to the schema's target namespace.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlAttribute>> get_UnhandledAttributes();
    /// Sets the qualified attributes that do not belong to the schema's target namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_UnhandledAttributes(const ArrayPtr<SharedPtr<XmlAttribute>>& value);

    /// Initializes a new instance of the XmlSchemaAnnotation class.
    ASPOSECPP_SHARED_API XmlSchemaAnnotation();

protected:

    /// @cond
    ASPOSECPP_SHARED_API String get_IdAttribute() override;
    ASPOSECPP_SHARED_API void set_IdAttribute(String value) override;

    ASPOSECPP_SHARED_API void SetUnhandledAttributes(ArrayPtr<SharedPtr<XmlAttribute>> moreAttributes) override;

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
    const char* DBG_class_name() const override { return "XmlSchemaAnnotation"; }
#endif
    /// @endcond

private:

    String _id;
    SharedPtr<XmlSchemaObjectCollection> _items;
    ArrayPtr<SharedPtr<XmlAttribute>> _moreAttributes;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


