/// @file xml/schema/xml_schema_any_attribute.h

#pragma once

#include <xml/schema/xml_schema_content_processing.h>
#include <xml/schema/xml_schema_annotated.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
class DocumentSchemaValidator;
namespace Schema
{
class Compiler;
class NamespaceList;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class SchemaInfo;
class XmlSchemaComplexType;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the World Wide Web Consortium (W3C) @c anyAttribute element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAnyAttribute : public XmlSchemaAnnotated
{
    typedef XmlSchemaAnyAttribute ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAnyAttribute>;

private:
    /// @cond
    friend class System::Xml::DocumentSchemaValidator;
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class SchemaInfo;
    friend class Compiler;
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// Returns the namespaces containing the attributes that can be used.
    /// @returns Namespaces for attributes that are available for use. The default is @c \#\#any. Optional.
    ASPOSECPP_SHARED_API String get_Namespace();
    /// Sets the namespaces containing the attributes that can be used.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Namespace(const String& value);
    /// Returns information about how an application or XML processor should handle the validation of XML documents
    /// for the attributes specified by the @c anyAttribute element.
    /// @returns One of the XmlSchemaContentProcessing values.
    /// If no @c processContents attribute is specified, the default is @c Strict.
    ASPOSECPP_SHARED_API XmlSchemaContentProcessing get_ProcessContents();
    /// Sets information about how an application or XML processor should handle the validation of XML documents
    /// for the attributes specified by the @c anyAttribute element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ProcessContents(XmlSchemaContentProcessing value);

    /// Initializes a new instance of the XmlSchemaAnyAttribute class.
    ASPOSECPP_SHARED_API XmlSchemaAnyAttribute();

protected:

    /// @cond
    SharedPtr<System::Xml::Schema::NamespaceList> get_NamespaceList();
    XmlSchemaContentProcessing get_ProcessContentsCorrect();

    void BuildNamespaceList(const String& targetNamespace);
    void BuildNamespaceListV1Compat(const String& targetNamespace);
    bool Allows(const SharedPtr<XmlQualifiedName>& qname);
    static bool IsSubset(const SharedPtr<XmlSchemaAnyAttribute>& sub, const SharedPtr<XmlSchemaAnyAttribute>& super);
    static SharedPtr<XmlSchemaAnyAttribute> Intersection(const SharedPtr<XmlSchemaAnyAttribute>& o1, const SharedPtr<XmlSchemaAnyAttribute>& o2, bool v1Compat);
    static SharedPtr<XmlSchemaAnyAttribute> Union(const SharedPtr<XmlSchemaAnyAttribute>& o1, const SharedPtr<XmlSchemaAnyAttribute>& o2, bool v1Compat);

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
    const char* DBG_class_name() const override { return "XmlSchemaAnyAttribute"; }
#endif
    /// @endcond

private:

    String _ns;
    XmlSchemaContentProcessing _processContents;
    SharedPtr<System::Xml::Schema::NamespaceList> _namespaceList;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


