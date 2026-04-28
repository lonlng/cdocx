/// @file xml/schema/xml_schema_group_base.h

#pragma once

#include <xml/schema/xml_schema_particle.h>


/// @cond
namespace System
{
namespace Xml
{
namespace Schema
{
class XmlSchemaComplexType;
class XmlSchemaObjectCollection;
} // namespace Schema
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Schema {

/// An abstract class for XmlSchemaAll, XmlSchemaChoice, or XmlSchemaSequence.
class ASPOSECPP_SHARED_CLASS XmlSchemaGroupBase : public XmlSchemaParticle
{
    typedef XmlSchemaGroupBase ThisType;
    typedef XmlSchemaParticle BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSchemaGroupBase>;

private:
    /// @cond
    friend class XmlSchemaComplexType;
    /// @endcond

public:

    /// This collection is used to add new elements to the compositor.
    /// @returns An XmlSchemaObjectCollection.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlSchemaObjectCollection> get_Items() = 0;

protected:

    /// @cond
    virtual void SetItems(SharedPtr<XmlSchemaObjectCollection> newItems) = 0;
    /// @endcond

};

} // namespace Schema
} // namespace Xml
} // namespace System


