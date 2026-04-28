/// @file xml/schema/xml_schema_notation.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>
#include <system/string.h>


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
class SchemaCollectionPreprocessor;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c notation element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// An XML Schema @c notation declaration is a reconstruction of @c XML 1.0 NOTATION declarations.
/// The purpose of notations is to describe the format of non-XML data within an XML document.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaNotation : public XmlSchemaAnnotated
{
    typedef XmlSchemaNotation ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaNotation>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    /// @endcond

public:

    /// Returns the name of the notation.
    /// @returns The name of the notation.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the notation.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns the @c public identifier.
    /// @returns The @c public identifier. The value must be a valid Uniform Resource Identifier (URI).
    ASPOSECPP_SHARED_API String get_Public();
    /// Sets the @c public identifier.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Public(const String& value);
    /// Returns the @c system identifier.
    /// @returns The @c system identifier. The value must be a valid URI.
    ASPOSECPP_SHARED_API String get_System();
    /// Sets the @c system identifier.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_System(const String& value);

    /// Initializes a new instance of the XmlSchemaNotation class.
    ASPOSECPP_SHARED_API XmlSchemaNotation();

protected:

    /// @cond
    SharedPtr<XmlQualifiedName> get_QualifiedName();
    void set_QualifiedName(const SharedPtr<XmlQualifiedName>& value);
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

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
    const char* DBG_class_name() const override { return "XmlSchemaNotation"; }
#endif
    /// @endcond

private:

    String _name;
    String _publicId;
    String _systemId;
    SharedPtr<XmlQualifiedName> _qname;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


