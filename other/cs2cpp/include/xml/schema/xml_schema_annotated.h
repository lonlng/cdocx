/// @file xml/schema/xml_schema_annotated.h

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
class Compiler;
class XmlSchemaAnnotation;
} // namespace Schema
class XmlAttribute;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// The base class for any element that can contain annotation elements.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAnnotated : public XmlSchemaObject
{
    typedef XmlSchemaAnnotated ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAnnotated>;

private:
    /// @cond
    friend class Compiler;
    /// @endcond

public:

    /// Returns the string id.
    /// @returns The string id. The default is String::Empty. Optional.
    ASPOSECPP_SHARED_API String get_Id();
    /// Sets the string id.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Id(const String& value);
    /// Returns the @c annotation property.
    /// @returns An XmlSchemaAnnotation representing the @c annotation property.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnnotation> get_Annotation();
    /// Sets the @c annotation property.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Annotation(const SharedPtr<XmlSchemaAnnotation>& value);
    /// Returns the qualified attributes that do not belong to the current schema's target namespace.
    /// @returns An array of qualified XmlAttribute objects that do not belong to the schema's target namespace.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlAttribute>> get_UnhandledAttributes();
    /// Sets the qualified attributes that do not belong to the current schema's target namespace.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_UnhandledAttributes(const ArrayPtr<SharedPtr<XmlAttribute>>& value);

protected:

    /// @cond
    ASPOSECPP_SHARED_API String get_IdAttribute() override;
    ASPOSECPP_SHARED_API void set_IdAttribute(String value) override;

    ASPOSECPP_SHARED_API void SetUnhandledAttributes(ArrayPtr<SharedPtr<XmlAttribute>> moreAttributes) override;
    ASPOSECPP_SHARED_API void AddAnnotation(SharedPtr<XmlSchemaAnnotation> annotation) override;

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
    const char* DBG_class_name() const override { return "XmlSchemaAnnotated"; }
#endif
    /// @endcond

private:

    String _id;
    SharedPtr<XmlSchemaAnnotation> _annotation;
    ArrayPtr<SharedPtr<XmlAttribute>> _moreAttributes;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


