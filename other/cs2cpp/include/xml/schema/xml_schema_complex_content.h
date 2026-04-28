/// @file xml/schema/xml_schema_complex_content.h

#pragma once

#include <xml/schema/xml_schema_content_model.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class Preprocessor;
class SchemaCollectionPreprocessor;
class XmlSchemaContent;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Represents the @c complexContent element from XML Schema as specified by the World Wide Web Consortium (W3C).
/// This class represents the complex content model for complex types.
/// It contains extensions or restrictions on a complex type that has either only elements or mixed content.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaComplexContent : public XmlSchemaContentModel
{
    typedef XmlSchemaComplexContent ThisType;
    typedef XmlSchemaContentModel BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaComplexContent>;

private:
    /// @cond
    friend class Preprocessor;
    friend class SchemaCollectionPreprocessor;
    /// @endcond

public:

    /// Returns information that determines if the type has a mixed content model.
    /// @returns If this value is @c true, character data is allowed to appear
    /// between the child elements of the complex type (mixed content model).
    /// The default is @c false. Optional.
    ASPOSECPP_SHARED_API bool get_IsMixed();
    /// Sets information that determines if the type has a mixed content model.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_IsMixed(bool value);
    /// Returns the content.
    /// @returns One of either the XmlSchemaComplexContentRestriction or XmlSchemaComplexContentExtension classes.
    ASPOSECPP_SHARED_API SharedPtr<XmlSchemaContent> get_Content() override;
    /// Sets the content.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Content(SharedPtr<XmlSchemaContent> value) override;

    /// Initializes a new instance of the XmlSchemaComplexContent class.
    ASPOSECPP_SHARED_API XmlSchemaComplexContent();

protected:

    /// @cond
    bool get_HasMixedAttribute();

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
    const char* DBG_class_name() const override { return "XmlSchemaComplexContent"; }
#endif
    /// @endcond

private:

    SharedPtr<XmlSchemaContent> _content;
    bool _isMixed;
    bool _hasMixedAttribute;

    ThisType* CppMemberwiseClone() const override { return new ThisType(*this); } 

};

} // namespace Schema
} // namespace Xml
} // namespace System


