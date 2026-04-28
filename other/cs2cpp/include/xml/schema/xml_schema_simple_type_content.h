/// @file xml/schema/xml_schema_simple_type_content.h

#pragma once

#include <xml/schema/xml_schema_annotated.h>


namespace System {

namespace Xml {

namespace Schema {

/// A base class for simple type content classes.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSchemaSimpleTypeContent : public XmlSchemaAnnotated
{
    typedef XmlSchemaSimpleTypeContent ThisType;
    typedef XmlSchemaAnnotated BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaSimpleTypeContent>;

};

} // namespace Schema
} // namespace Xml
} // namespace System


