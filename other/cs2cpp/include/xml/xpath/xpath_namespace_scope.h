/// @file xml/xpath/xpath_namespace_scope.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>


namespace System {

namespace Xml {

namespace XPath {

/// Defines the namespace scope.
enum class XPathNamespaceScope
{
    /// Returns all namespaces defined in the scope of the current node.
    /// This includes the @c xmlns:xml namespace which is always declared implicitly.
    /// The order of the namespaces returned is not defined.
    All,
    /// Returns all namespaces defined in the scope of the current node, excluding the @c xmlns:xml namespace.
    /// The @c xmlns:xml namespace is always declared implicitly.
    /// The order of the namespaces returned is not defined.
    ExcludeXml,
    /// Returns all namespaces that are defined locally at the current node.
    Local
};

} // namespace XPath
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XPath::XPathNamespaceScope>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XPathNamespaceScope, const char_t*>, 3>& values();
};
/// @endcond


