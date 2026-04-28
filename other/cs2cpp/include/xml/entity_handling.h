/// @file xml/entity_handling.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies how the XmlTextReader or XmlValidatingReader handle entities.
enum class EntityHandling
{
    /// Expands all entities and returns the expanded nodes.
    ///
    /// XmlNodeType::EntityReference nodes are not returned. The entity text is expanded in place of the entity references.
    ExpandEntities = 1,
    /// Expands character entities and returns general entities as XmlNodeType::EntityReference nodes.
    ///
    /// You must call XmlReader::ResolveEntity to see what the general entities expand to.
    /// This enables you to optimize entity handling by only expanding the entity the first time it is used.
    ///
    /// When set to EntityHandling::ExpandCharEntities, a reader call to the XmlReader::GetAttribute method
    /// expands all entities (both general and character entities).
    ExpandCharEntities = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::EntityHandling>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::EntityHandling, const char_t*>, 2>& values();
};
/// @endcond


