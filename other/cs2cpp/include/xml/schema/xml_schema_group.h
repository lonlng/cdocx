/// @file xml/schema/xml_schema_group.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/string.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class BaseProcessor;
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchema;
class XmlSchemaGroupBase;
class XmlSchemaObject;
class XmlSchemaParticle;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c group element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class defines groups at the @c schema level that are referenced from the complex types.
/// It groups a set of element declarations so that they can be incorporated as a group into complex type definitions.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaGroup : public XmlSchemaAnnotated
{
    typedef XmlSchemaGroup ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaGroup>;

private:
    /// @cond
    friend class BaseProcessor;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchema;
    /// @endcond

public:

    /// Returns the name of the schema group.
    /// @returns The name of the schema group.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the schema group.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns one of the XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @returns One of the XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaGroupBase> get_Particle();
    /// Sets one of the XmlSchemaChoice, XmlSchemaAll, or XmlSchemaSequence classes.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Particle(const SharedPtr<XmlSchemaGroupBase>& value);
    /// Returns the qualified name of the schema group.
    /// @returns An XmlQualifiedName object representing the qualified name of the schema group.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();

    /// Initializes a new instance of the XmlSchemaGroup class.
    ASPOSECPP_SHARED_API XmlSchemaGroup();

protected:

    /// @cond
    SharedPtr<XmlSchemaParticle> get_CanonicalParticle();
    void set_CanonicalParticle(const SharedPtr<XmlSchemaParticle>& value);
    SharedPtr<XmlSchemaGroup> get_Redefined();
    void set_Redefined(const SharedPtr<XmlSchemaGroup>& value);
    int32_t get_SelfReferenceCount();
    void set_SelfReferenceCount(int32_t value);
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObject> Clone() override;
    SharedPtr<XmlSchemaObject> Clone(const SharedPtr<XmlSchema>& parentSchema);

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
    const char* DBG_class_name() const override { return "XmlSchemaGroup"; }
#endif
    /// @endcond

private:

    String _name;
    SharedPtr<XmlSchemaGroupBase> _particle;
    SharedPtr<XmlSchemaParticle> _canonicalParticle;
    SharedPtr<XmlQualifiedName> _qname;
    SharedPtr<XmlSchemaGroup> _redefined;
    int32_t _selfReferenceCount;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


