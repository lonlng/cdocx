/// @file xml/schema/xml_schema_group_ref.h

#pragma once

#include <xml/schema/xml_schema_particle.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class XmlSchemaGroup;
class XmlSchemaGroupBase;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c group element with @c ref attribute from the XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class is used within complex types that reference a @c group defined at the @c schema level.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaGroupRef : public XmlSchemaParticle
{
    typedef XmlSchemaGroupRef ThisType;
    typedef XmlSchemaParticle BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaGroupRef>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class Compiler;
    /// @endcond

public:

    /// Returns the name of a group defined in this schema (or another schema indicated by the specified namespace).
    /// @returns The name of a group defined in this schema.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_RefName();
    /// Sets the name of a group defined in this schema (or another schema indicated by the specified namespace).
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_RefName(const SharedPtr<XmlQualifiedName>& value);
    /// Returns one of the XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes,
    /// which holds the post-compilation interpretation of the @c Particle value.
    /// @returns The post-compilation interpretation of the @c Particle value,
    /// which is one of the XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaGroupBase> get_Particle();

    /// Initializes a new instance of the XmlSchemaGroupRef class.
    ASPOSECPP_SHARED_API XmlSchemaGroupRef();

protected:

    /// @cond
    SharedPtr<XmlSchemaGroup> get_Redefined();
    void set_Redefined(const SharedPtr<XmlSchemaGroup>& value);

    void SetParticle(const SharedPtr<XmlSchemaGroupBase>& value);

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
    const char* DBG_class_name() const override { return "XmlSchemaGroupRef"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _refName;
    SharedPtr<XmlSchemaGroupBase> _particle;
    SharedPtr<XmlSchemaGroup> _refined;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


