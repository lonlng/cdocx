/// @file xml/xml_node_changed_action.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Specifies the type of node change.
enum class XmlNodeChangedAction
{
    /// A node is being inserted in the tree.
    Insert = 0,
    /// A node is being removed from the tree.
    Remove = 1,
    /// A node value is being changed.
    Change = 2
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlNodeChangedAction>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlNodeChangedAction, const char_t*>, 3>& values();
};
/// @endcond


