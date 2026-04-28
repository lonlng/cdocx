/// @file xml/ixml_namespace_resolver.h

#pragma once

#include <xml/xml_namespace_scope.h>
#include <system/object.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class IDictionary;
} // namespace Generic
} // namespace Collections
class String;
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Provides read-only access to a set of prefix and namespace mappings.
class ASPOSECPP_SHARED_CLASS IXmlNamespaceResolver : public virtual System::Object
{
    typedef IXmlNamespaceResolver ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a collection of defined prefix-namespace mappings that are currently in scope.
    /// @param scope An XmlNamespaceScope value that specifies the type of namespace nodes to return.
    /// @returns An IDictionary collection that contains the current in-scope namespaces.
    virtual SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) = 0;
    /// Returns the namespace URI mapped to the specified prefix.
    /// @param prefix The prefix whose namespace URI you wish to find.
    /// @returns The namespace URI that is mapped to the prefix; @c nullptr if the prefix is not mapped to a namespace URI.
    virtual String LookupNamespace(const String& prefix) = 0;
    /// Returns the prefix that is mapped to the specified namespace URI.
    /// @param namespaceName The namespace URI whose prefix you wish to find.
    /// @returns The prefix that is mapped to the namespace URI; @c nullptr if the namespace URI is not mapped to a prefix.
    virtual String LookupPrefix(const String& namespaceName) = 0;

};

} // namespace Xml
} // namespace System


