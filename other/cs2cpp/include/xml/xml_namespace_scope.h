/// @file xml/xml_namespace_scope.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

/// Defines the namespace scope.
enum class XmlNamespaceScope
{
    /// All namespaces defined in the scope of the current node.
    /// This includes the xmlns:xml namespace which is always declared implicitly.
    /// The order of the namespaces returned is not defined.
    All,
    /// All namespaces defined in the scope of the current node, excluding the xmlns:xml namespace,
    /// which is always declared implicitly.
    /// The order of the namespaces returned is not defined.
    ExcludeXml,
    /// All namespaces that are defined locally at the current node.
    Local
};

} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XmlNamespaceScope>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XmlNamespaceScope, const char_t*>, 3>& values();
};
/// @endcond


