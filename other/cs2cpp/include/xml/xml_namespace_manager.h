/// @file xml/xml_namespace_manager.h

#pragma once

#include <xml/xml_namespace_scope.h>
#include <xml/ixml_namespace_resolver.h>
#include <system/collections/ienumerable.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename, typename> class IDictionary;
template <typename> class IEnumerator;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class XmlNameTable;
namespace Xsl
{
class XsltContext;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Resolves, adds, and removes namespaces to a collection and provides scope management for these namespaces.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlNamespaceManager : public IXmlNamespaceResolver, public Collections::Generic::IEnumerable<String>
{
    typedef XmlNamespaceManager ThisType;
    typedef IXmlNamespaceResolver BaseType;
    typedef Collections::Generic::IEnumerable<String> BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNamespaceManager>;

private:
    /// @cond
    friend class Xsl::XsltContext;
    /// @endcond

private:

    class NamespaceDeclaration : public System::Object
    {
        typedef NamespaceDeclaration ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        String prefix;
        String uri;
        int32_t scopeId;
        int32_t previousNsIndex;

        void Set(const String& prefix, const String& uri, int32_t scopeId, int32_t previousNsIndex);

        NamespaceDeclaration();

    };


public:

    /// Returns the XmlNameTable associated with this object.
    /// @returns The XmlNameTable used by this object.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();
    /// Returns the namespace URI for the default namespace.
    /// @returns The namespace URI for the default namespace, or an empty string if there is no default namespace.
    virtual ASPOSECPP_SHARED_API String get_DefaultNamespace();

    /// Initializes a new instance of the XmlNamespaceManager class with the specified XmlNameTable.
    /// @param nameTable The XmlNameTable to use.
    /// @throws NullReferenceException @c nullptr is passed to the constructor.
    ASPOSECPP_SHARED_API XmlNamespaceManager(const SharedPtr<XmlNameTable>& nameTable);

    /// Pushes a namespace scope onto the stack.
    virtual ASPOSECPP_SHARED_API void PushScope();
    /// Pops a namespace scope off the stack.
    /// @returns @c true if there are namespace scopes left on the stack; @c false if there are no more namespaces to pop.
    virtual ASPOSECPP_SHARED_API bool PopScope();
    /// Adds the given namespace to the collection.
    /// @param prefix The prefix to associate with the namespace being added. Use String::Empty to add a default namespace.
    /// If the XmlNamespaceManager will be used for resolving namespaces in an XML Path Language (XPath) expression,
    /// a prefix must be specified. If an XPath expression does not include a prefix,
    /// it is assumed that the namespace Uniform Resource Identifier (URI) is the empty namespace.
    /// For more information about XPath expressions and the XmlNamespaceManager,
    /// refer to the XmlNode::SelectNodes(String) and XPathExpression::SetContext(SharedPtr<XmlNamespaceManager>) methods.
    /// @param uri The namespace to add.
    /// @throws ArgumentException The value for @p prefix is "xml" or "xmlns".
    /// @throws ArgumentNullException The value for @p prefix or @p uri is @c nullptr.
    virtual ASPOSECPP_SHARED_API void AddNamespace(String prefix, String uri);
    /// Removes the given namespace for the given prefix.
    /// @param prefix The prefix for the namespace.
    /// @param uri The namespace to remove for the given prefix.
    /// The namespace removed is from the current namespace scope. Namespaces outside the current scope are ignored.
    /// @throws ArgumentNullException The value of @p prefix or @p uri is @c nullptr.
    virtual ASPOSECPP_SHARED_API void RemoveNamespace(String prefix, String uri);
    /// Returns an enumerator to use to iterate through the namespaces in the XmlNamespaceManager.
    /// @returns An IEnumerator containing the prefixes stored by the XmlNamespaceManager.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<String>> GetEnumerator() override;
    /// Returns a collection of namespace names keyed by prefix which can be used to enumerate the namespaces currently in scope.
    /// @param scope An enumeration value that specifies the type of namespace nodes to return.
    /// @returns A collection of namespace and prefix pairs currently in scope.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IDictionary<String, String>> GetNamespacesInScope(XmlNamespaceScope scope) override;
    /// Returns the namespace URI for the specified prefix.
    /// @param prefix The prefix whose namespace URI you want to resolve.
    /// To match the default namespace, pass String::Empty.
    /// @returns The namespace URI for @p prefix or @c nullptr if there is no mapped namespace.
    /// The returned string is atomized.
    /// For more information on atomized strings, see the XmlNameTable class.
    ASPOSECPP_SHARED_API String LookupNamespace(const String& prefix) override;
    /// Finds the prefix declared for the given namespace URI.
    /// @param uri The namespace to resolve for the prefix.
    /// @returns The matching prefix. If there is no mapped prefix, the method returns String::Empty.
    /// If a null value is supplied, then @c nullptr is returned.
    ASPOSECPP_SHARED_API String LookupPrefix(const String& uri) override;
    /// Returns a value indicating whether the supplied prefix has a namespace defined for the current pushed scope.
    /// @param prefix The prefix of the namespace you want to find.
    /// @returns @c true if there is a namespace defined; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool HasNamespace(String prefix);

protected:

    /// @cond
    XmlNamespaceManager();
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlNamespaceManager, CODEPORTING_ARGS());

    bool GetNamespaceDeclaration(int32_t idx, String& prefix, String& uri);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlNamespaceManager();

    /// @cond
    #ifdef ASPOSE_GET_SHARED_MEMBERS
    ASPOSECPP_SHARED_API void GetSharedMembers(System::Object::shared_members_type& result) const override;
    #endif

    #ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to members.
    /// @param visitor Visitor to apply.
    ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "XmlNamespaceManager"; }
    #endif
    /// @endcond

private:

    ArrayPtr<XmlNamespaceManager::NamespaceDeclaration> _nsdecls;
    int32_t _lastDecl;
    SharedPtr<XmlNameTable> _nameTable;
    int32_t _scopeId;
    SharedPtr<Collections::Generic::Dictionary<String, int32_t>> _hashTable;
    bool _useHashtable;
    String _xml;
    String _xmlNs;
    static const int32_t MinDeclsCountForHashtable;

    int32_t LookupNamespaceDecl(const String& prefix);

};

} // namespace Xml
} // namespace System


