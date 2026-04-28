/// @file xml/schema/xml_schema_documentation.h

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
class XmlSchemaSimpleType;
} // namespace Schema
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c documentation element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class specifies information to be read or used by humans within an @c annotation.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaDocumentation : public XmlSchemaObject
{
    typedef XmlSchemaDocumentation ThisType;
    typedef XmlSchemaObject BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaDocumentation>;

public:

    /// Returns the Uniform Resource Identifier (URI) source of the information.
    /// @returns A URI reference. The default is String::Empty. Optional.
    ASPOSECPP_SHARED_API String get_Source();
    /// Sets the Uniform Resource Identifier (URI) source of the information.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Source(const String& value);
    /// Returns the @c xml:lang attribute. This serves as an indicator of the language used in the contents.
    /// @returns The @c xml:lang attribute. Optional.
    ASPOSECPP_SHARED_API String get_Language();
    /// Sets the @c xml:lang attribute. This serves as an indicator of the language used in the contents.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Language(const String& value);
    /// Returns an array of XmlNode objects that represents the documentation child nodes.
    /// @returns The array that represents the documentation child nodes.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlNode>> get_Markup();
    /// Sets an array of XmlNode objects that represents the documentation child nodes.
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
    const char* DBG_class_name() const override { return "XmlSchemaDocumentation"; }
#endif
    /// @endcond

private:

    String _source;
    String _language;
    ArrayPtr<SharedPtr<XmlNode>> _markup;
    static SharedPtr<XmlSchemaSimpleType> s_languageType;

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


