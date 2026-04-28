/// @file xml/schema/xml_schema_any.h

#pragma once

#include <xml/schema/xml_schema_particle.h>
#include <xml/schema/xml_schema_content_processing.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class Compiler;
class NamespaceList;
class Preprocessor;
class SchemaCollectionCompiler;
class SchemaCollectionPreprocessor;
class XmlSchemaComplexType;
class XmlSchemaValidator;
class XsdValidator;
} // namespace Schema
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the World Wide Web Consortium (W3C) @c any element.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaAny : public XmlSchemaParticle
{
    typedef XmlSchemaAny ThisType;
    typedef XmlSchemaParticle BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaAny>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionCompiler;
    friend class SchemaCollectionPreprocessor;
    friend class Compiler;
    friend class XmlSchemaComplexType;
    friend class XmlSchemaValidator;
    friend class XsdValidator;
    /// @endcond

public:

    /// Returns the namespaces containing the elements that can be used.
    /// @returns Namespaces for elements that are available for use. The default is @c \#\#any. Optional.
    ASPOSECPP_SHARED_API String get_Namespace();
    /// Sets the namespaces containing the elements that can be used.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Namespace(const String& value);
    /// Returns information about how an application or XML processor should handle the validation of
    /// XML documents for the elements specified by the @c any element.
    /// @returns One of the XmlSchemaContentProcessing values.
    /// If no @c processContents attribute is specified, the default is @c Strict.
    ASPOSECPP_SHARED_API XmlSchemaContentProcessing get_ProcessContents();
    /// Sets information about how an application or XML processor should handle the validation of
    /// XML documents for the elements specified by the @c any element.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_ProcessContents(XmlSchemaContentProcessing value);

    /// Initializes a new instance of the XmlSchemaAny class.
    ASPOSECPP_SHARED_API XmlSchemaAny();

protected:

    /// @cond
    SharedPtr<System::Xml::Schema::NamespaceList> get_NamespaceList();
    String get_ResolvedNamespace();
    XmlSchemaContentProcessing get_ProcessContentsCorrect();
    ASPOSECPP_SHARED_API String get_NameString() override;

    void BuildNamespaceList(const String& targetNamespace);
    void BuildNamespaceListV1Compat(const String& targetNamespace);
    bool Allows(const SharedPtr<XmlQualifiedName>& qname);

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
    const char* DBG_class_name() const override { return "XmlSchemaAny"; }
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


