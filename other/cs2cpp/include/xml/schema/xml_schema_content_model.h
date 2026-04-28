/// @file xml/schema/xml_schema_content_model.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaContent;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// Specifies the order and structure of the child elements of a type.
class ASPOSECPP_SHARED_CLASS XmlSchemaContentModel : public XmlSchemaAnnotated
{
    typedef XmlSchemaContentModel ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaContentModel>;

public:

    /// Returns the content of the type.
    /// @returns Provides the content of the type.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlSchemaContent> get_Content() = 0;
    /// Sets the content of the type.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_Content(SharedPtr<XmlSchemaContent> value) = 0;

};

} // namespace Schema
} // namespace Xml
} // namespace System


