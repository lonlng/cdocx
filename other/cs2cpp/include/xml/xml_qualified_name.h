/// @file xml/xml_qualified_name.h

#pragma once

#include <system/string.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Xml
{
class IXmlNamespaceResolver;
class QueryOutputWriter;
class QueryOutputWriterV1;
namespace Schema
{
class Datatype_NOTATION;
class Datatype_QName;
class Datatype_QNameXdr;
class DtdValidator;
class Preprocessor;
class SchemaCollectionPreprocessor;
class XdrBuilder;
class XdrValidator;
class XmlSchemaAttribute;
class XmlSchemaComplexType;
class XmlSchemaElement;
class XmlSchemaSimpleTypeList;
class XmlSchemaSimpleTypeRestriction;
class XmlSchemaSimpleTypeUnion;
class XmlSchemaValidator;
class XsdBuilder;
class XsdValidator;
} // namespace Schema
class XmlNameTable;
namespace Xsl
{
class XsltArgumentList;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents an XML qualified name.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlQualifiedName : public System::Object
{
    typedef XmlQualifiedName ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlQualifiedName>;

private:
    /// @cond
    friend class QueryOutputWriter;
    friend class QueryOutputWriterV1;
    friend class Schema::Datatype_QName;
    friend class Schema::Datatype_NOTATION;
    friend class Schema::Datatype_QNameXdr;
    friend class Schema::DtdValidator;
    friend class Schema::Preprocessor;
    friend class Schema::SchemaCollectionPreprocessor;
    friend class Schema::XdrBuilder;
    friend class Schema::XdrValidator;
    friend class Schema::XmlSchemaAttribute;
    friend class Schema::XmlSchemaComplexType;
    friend class Schema::XmlSchemaElement;
    friend class Schema::XmlSchemaSimpleTypeList;
    friend class Schema::XmlSchemaSimpleTypeRestriction;
    friend class Schema::XmlSchemaSimpleTypeUnion;
    friend class Schema::XmlSchemaValidator;
    friend class Schema::XsdBuilder;
    friend class Schema::XsdValidator;
    friend class Xsl::XsltArgumentList;
    friend ASPOSECPP_SHARED_API bool operator ==(const SharedPtr<XmlQualifiedName>& a, const SharedPtr<XmlQualifiedName>& b);
    friend ASPOSECPP_SHARED_API bool operator !=(const SharedPtr<XmlQualifiedName>& a, const SharedPtr<XmlQualifiedName>& b);
    /// @endcond

public:

    /// Provides an empty XmlQualifiedName.
    static ASPOSECPP_SHARED_API SharedPtr<XmlQualifiedName> Empty;

    /// Returns a string representation of the namespace of the XmlQualifiedName.
    /// @returns A string representation of the namespace or String::Empty if a namespace is not defined for the object.
    ASPOSECPP_SHARED_API String get_Namespace() const;
    /// Returns a string representation of the qualified name of the XmlQualifiedName.
    /// @returns A string representation of the qualified name or String::Empty if a name is not defined for the object.
    ASPOSECPP_SHARED_API String get_Name() const;
    /// Returns a value indicating whether the XmlQualifiedName is empty.
    /// @returns @c true if name and namespace are empty strings; otherwise, @c false.
    ASPOSECPP_SHARED_API bool get_IsEmpty() const;

    /// Initializes a new instance of the XmlQualifiedName class.
    ASPOSECPP_SHARED_API XmlQualifiedName();
    /// Initializes a new instance of the XmlQualifiedName class with the specified name.
    /// @param name The local name to use as the name of the XmlQualifiedName object.
    ASPOSECPP_SHARED_API XmlQualifiedName(const String& name);
    /// Initializes a new instance of the XmlQualifiedName class with the specified name and namespace.
    /// @param name The local name to use as the name of the XmlQualifiedName object.
    /// @param ns The namespace for the XmlQualifiedName object.
    ASPOSECPP_SHARED_API XmlQualifiedName(const String& name, const String& ns);

    /// Returns the hash code for the XmlQualifiedName.
    /// @returns A hash code for this object.
    ASPOSECPP_SHARED_API int32_t GetHashCode() const override;
    /// Determines whether the specified XmlQualifiedName object is equal to the current XmlQualifiedName object.
    /// @param other The XmlQualifiedName to compare.
    /// @returns @c true if the two are the same instance object; otherwise, @c false.
    ASPOSECPP_SHARED_API bool Equals(SharedPtr<Object> other) override;
    /// Returns the string value of the XmlQualifiedName.
    /// @param name The name of the object.
    /// @param ns The namespace of the object.
    /// @returns The string value of the XmlQualifiedName in the format of @c namespace:localname.
    /// If the object does not have a namespace defined, this method returns just the local name.
    static ASPOSECPP_SHARED_API String ToString(const String& name, const String& ns);
    /// Returns the string value of the XmlQualifiedName.
    /// @returns The string value of the XmlQualifiedName in the format of @c namespace:localname.
    /// If the object does not have a namespace defined, this method returns just the local name.
    ASPOSECPP_SHARED_API String ToString() const override;

protected:

    /// @cond
    void Init(const String& name, const String& ns);
    void SetNamespace(const String& ns);
    void Verify();
    void Atomize(const SharedPtr<XmlNameTable>& nameTable);
    static SharedPtr<XmlQualifiedName> Parse(const String& s, const SharedPtr<IXmlNamespaceResolver>& nsmgr, String& prefix);
    SharedPtr<XmlQualifiedName> Clone();
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
    const char* DBG_class_name() const override { return "XmlQualifiedName"; }
    #endif
    /// @endcond

private:

    String _name;
    String _ns;
    mutable int32_t _hash;

    String ToString_NonConst();
    virtual ThisType* CppMemberwiseClone() const { return new ThisType(*this); }

};

/// Compares two XmlQualifiedName objects.
/// @param a An XmlQualifiedName to compare.
/// @param b An XmlQualifiedName to compare.
/// @returns @c true if the two objects have the same name and namespace values; otherwise, @c false.
ASPOSECPP_SHARED_API bool operator ==(const SharedPtr<XmlQualifiedName>& a, const SharedPtr<XmlQualifiedName>& b);
/// Compares two XmlQualifiedName objects.
/// @param a An XmlQualifiedName to compare.
/// @param b An XmlQualifiedName to compare.
/// @returns @c true if the name and namespace values for the two objects differ; otherwise, @c false.
ASPOSECPP_SHARED_API bool operator !=(const SharedPtr<XmlQualifiedName>& a, const SharedPtr<XmlQualifiedName>& b);

} // namespace Xml
} // namespace System


