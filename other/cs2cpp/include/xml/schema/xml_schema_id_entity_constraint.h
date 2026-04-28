/// @file xml/schema/xml_schema_id_entity_constraint.h

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
class CompiledIdentityConstraint;
class Compiler;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchemaObjectCollection;
class XmlSchemaXPath;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Class for the identity constraints: @c key, @c keyref, and @c unique elements.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaIdentityConstraint : public XmlSchemaAnnotated
{
    typedef XmlSchemaIdentityConstraint ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaIdentityConstraint>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    /// @endcond

public:

    /// Returns the name of the identity constraint.
    /// @returns The name of the identity constraint.
    ASPOSECPP_SHARED_API String get_Name();
    /// Sets the name of the identity constraint.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Name(const String& value);
    /// Returns the XPath expression @c selector element.
    /// @returns The XPath expression @c selector element.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaXPath> get_Selector();
    /// Sets the XPath expression @c selector element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Selector(const SharedPtr<XmlSchemaXPath>& value);
    /// Returns the collection of fields that apply as children for the XML Path Language (XPath) expression selector.
    /// @returns The collection of fields.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Fields();
    /// Returns the qualified name of the identity constraint,
    /// which holds the post-compilation interpretation of the @c QualifiedName value.
    /// @returns The post-compilation interpretation of the @c QualifiedName value.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_QualifiedName();

    /// Initializes a new instance of the XmlSchemaIdentityConstraint class.
    ASPOSECPP_SHARED_API XmlSchemaIdentityConstraint();

protected:

    /// @cond
    SharedPtr<CompiledIdentityConstraint> get_CompiledConstraint();
    void set_CompiledConstraint(const SharedPtr<CompiledIdentityConstraint>& value);
    ASPOSECPP_SHARED_API String get_NameAttribute() override;
    ASPOSECPP_SHARED_API void set_NameAttribute(String value) override;

    void SetQualifiedName(const SharedPtr<XmlQualifiedName>& value);

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
    const char* DBG_class_name() const override { return "XmlSchemaIdentityConstraint"; }
#endif
    /// @endcond

private:

    String _name;
    SharedPtr<XmlSchemaXPath> _selector;
    SharedPtr<XmlSchemaObjectCollection> _fields;
    SharedPtr<XmlQualifiedName> _qualifiedName;
    SharedPtr<CompiledIdentityConstraint> _compiledConstraint;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the World Wide Web Consortium (W3C) @c selector element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaXPath : public XmlSchemaAnnotated
{
    typedef XmlSchemaXPath ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaXPath>;

public:

    /// Returns the attribute for the XPath expression.
    /// @returns The string attribute value for the XPath expression.
    ASPOSECPP_SHARED_API String get_XPath();
    /// Sets the attribute for the XPath expression.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XPath(const String& value);

private:

    String _xpath;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// Represents the @c unique element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class can be used to identify a unique constraint among a set of elements.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaUnique : public XmlSchemaIdentityConstraint
{
    typedef XmlSchemaUnique ThisType;
    typedef XmlSchemaIdentityConstraint BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaUnique>;

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// This class represents the @c key element from XMLSchema as specified by the World Wide Web Consortium (W3C).
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaKey : public XmlSchemaIdentityConstraint
{
    typedef XmlSchemaKey ThisType;
    typedef XmlSchemaIdentityConstraint BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaKey>;

private:

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

/// This class represents the @c keyref element from XMLSchema as specified by the World Wide Web Consortium (W3C).
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaKeyref : public XmlSchemaIdentityConstraint
{
    typedef XmlSchemaKeyref ThisType;
    typedef XmlSchemaIdentityConstraint BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaKeyref>;

public:

    /// Returns the name of the key that this constraint refers to in another simple or complex type.
    /// @returns The QName of the key that this constraint refers to.
    ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> get_Refer();
    /// Sets the name of the key that this constraint refers to in another simple or complex type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Refer(const SharedPtr<XmlQualifiedName>& value);

    /// Initializes a new instance of the XmlSchemaKeyref class.
    ASPOSECPP_SHARED_API XmlSchemaKeyref();

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
    const char* DBG_class_name() const override { return "XmlSchemaKeyref"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlQualifiedName> _refer;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


