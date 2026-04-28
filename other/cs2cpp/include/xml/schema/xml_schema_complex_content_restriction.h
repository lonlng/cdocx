/// @file xml/schema/xml_schema_complex_content_restriction.h

#pragma once

#include <xml/schema/xml_schema_content.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaAnyAttribute;
class XmlSchemaComplexType;
class XmlSchemaObjectCollection;
class XmlSchemaParticle;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c restriction element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class is for complex types with a complex content model derived by restriction.
/// It restricts the contents of the complex type to a subset of the inherited complex type.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaComplexContentRestriction : public XmlSchemaContent
{
    typedef XmlSchemaComplexContentRestriction ThisType;
    typedef XmlSchemaContent BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaComplexContentRestriction>;

private:
    /// @cond
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// Returns the name of a complex type from which this type is derived by restriction.
    /// @returns The name of the complex type from which this type is derived by restriction.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_BaseTypeName();
    /// Sets the name of a complex type from which this type is derived by restriction.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseTypeName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns one of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @returns One of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaParticle> get_Particle();
    /// Sets one of the XmlSchemaGroupRef, XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Particle(const SharedPtr<XmlSchemaParticle>& value);
    /// Returns the collection of attributes for the complex type.
    /// Contains the XmlSchemaAttribute and XmlSchemaAttributeGroupRef elements.
    /// @returns The collection of attributes for the complex type.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Attributes();
    /// Returns the XmlSchemaAnyAttribute component of the complex content model.
    /// @returns The XmlSchemaAnyAttribute component of the complex content model.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaAnyAttribute> get_AnyAttribute();
    /// Sets the XmlSchemaAnyAttribute component of the complex content model.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_AnyAttribute(const SharedPtr<XmlSchemaAnyAttribute>& value);

    /// Initializes a new instance of the XmlSchemaComplexContentRestriction class.
    ASPOSECPP_SHARED_API XmlSchemaComplexContentRestriction();

protected:

    /// @cond
    void SetAttributes(const SharedPtr<XmlSchemaObjectCollection>& newAttributes);

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
    const char* DBG_class_name() const override { return "XmlSchemaComplexContentRestriction"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaParticle> _particle;
    SharedPtr<XmlSchemaObjectCollection> _attributes;
    SharedPtr<XmlSchemaAnyAttribute> _anyAttribute;
    SharedPtr<XmlQualifiedName> _baseTypeName;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


