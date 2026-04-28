/// @file xml/schema/xml_schema_particle.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/shared_ptr.h>
#include <system/enum_helpers.h>
#include <system/decimal.h>


/// @cond
namespace System
{
class String;
namespace Xml
{
namespace Schema
{
class Compiler;
class DfaContentValidator;
class NfaContentValidator;
class RangeContentValidator;
class SchemaCollectionCompiler;
class XmlSchemaAll;
class XmlSchemaChoice;
class XmlSchemaComplexType;
class XmlSchemaGroup;
class XmlSchemaSequence;
class XmlSchemaValidator;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// A base class for that is the base class for all particle types (e.g. XmlSchemaAny).
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaParticle : public XmlSchemaAnnotated
{
    typedef XmlSchemaParticle ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaParticle>;

private:
    /// @cond
    friend class DfaContentValidator;
    friend class NfaContentValidator;
    friend class RangeContentValidator;
    friend class SchemaCollectionCompiler;
    friend class Compiler;
    friend class XmlSchemaAll;
    friend class XmlSchemaChoice;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaGroup;
    friend class XmlSchemaSequence;
    friend class XmlSchemaValidator;
    /// @endcond

private:

    enum class Occurs
    {
        None,
        Min,
        Max
    };
    DECLARE_FRIEND_ENUM_OPERATORS(System::Xml::Schema::XmlSchemaParticle::Occurs);



public:

    /// Returns the number as a string value.
    /// The minimum number of times the particle can occur.
    /// @returns The number as a string value.
    /// String::Empty indicates that @c MinOccurs is equal to the default value.
    /// The default is @c nullptr.
    ASPOSECPP_SHARED_API String get_MinOccursString();
    /// Sets the number as a string value.
    /// The minimum number of times the particle can occur.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MinOccursString(const String& value);
    /// Returns the number as a string value. Maximum number of times the particle can occur.
    /// @returns The number as a string value.
    /// String::Empty indicates that @c MaxOccurs is equal to the default value.
    /// The default is @c nullptr.
    ASPOSECPP_SHARED_API String get_MaxOccursString();
    /// Sets the number as a string value. Maximum number of times the particle can occur.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MaxOccursString(const String& value);
    /// Returns the minimum number of times the particle can occur.
    /// @returns The minimum number of times the particle can occur. The default is 1.
    ASPOSECPP_SHARED_API Decimal get_MinOccurs();
    /// Sets the minimum number of times the particle can occur.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MinOccurs(Decimal value);
    /// Returns the maximum number of times the particle can occur.
    /// @returns The maximum number of times the particle can occur. The default is 1.
    ASPOSECPP_SHARED_API Decimal get_MaxOccurs();
    /// Sets the maximum number of times the particle can occur.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_MaxOccurs(Decimal value);

    /// Initializes a new instance of the XmlSchemaParticle class.
    ASPOSECPP_SHARED_API XmlSchemaParticle();

protected:

    /// @cond
    virtual ASPOSECPP_SHARED_API bool get_IsEmpty();
    bool get_IsMultipleOccurrence();
    virtual ASPOSECPP_SHARED_API String get_NameString();

    static SharedPtr<XmlSchemaParticle> Empty;

    SharedPtr<XmlQualifiedName> GetQualifiedName();
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlSchemaParticle();

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
    const char* DBG_class_name() const override { return "XmlSchemaParticle"; }
#endif
    /// @endcond

private:

    Decimal _minOccurs;
    Decimal _maxOccurs;
    XmlSchemaParticle::Occurs _flags;

};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::Schema::XmlSchemaParticle::Occurs);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace Schema
} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml::Schema);
/// @endcond


