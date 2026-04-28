/// @file xml/schema/xml_schema_content.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>


namespace System {

namespace Xml {

namespace Schema {

/// An abstract class for schema content.
class ASPOSECPP_SHARED_CLASS XmlSchemaContent : public XmlSchemaAnnotated
{
    typedef XmlSchemaContent ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaContent>;

};

} // namespace Schema
} // namespace Xml
} // namespace System


