/// @file xml/xml_node_order.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Describes the document order of a node compared to a second node.
enum class XmlNodeOrder
{
    /// The current node of this navigator is before the current node of the supplied navigator.
    Before,
    /// The current node of this navigator is after the current node of the supplied navigator.
    After,
    /// The two navigators are positioned on the same node.
    Same,
    /// The node positions cannot be determined in document order, relative to each other.
    /// This could occur if the two nodes reside in different trees.
    Unknown
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlNodeOrder>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlNodeOrder, const char_t*>, 4>& values();
};
/// @endcond


