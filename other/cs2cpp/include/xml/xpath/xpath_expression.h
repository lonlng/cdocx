/// @file xml/xpath/xpath_expression.h

#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IComparer;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class IXmlNamespaceResolver;
class XmlNamespaceManager;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Specifies the sort order.
enum class XmlSortOrder
{
    /// Nodes are sorted in ascending order.
    /// For example, if the numbers 1,2,3, and 4 are sorted in ascending order, they appear as 1,2,3,4.
    Ascending = 1,
    /// Nodes are sorted in descending order.
    /// For example, if the numbers 1,2,3, and 4 are sorted in descending order, they appear as, 4,3,2,1.
    Descending = 2
};

/// Specifies the sort order for uppercase and lowercase letters.
enum class XmlCaseOrder
{
    /// Ignore the case.
    None = 0,
    /// Uppercase letters are sorted before lowercase letters.
    UpperFirst = 1,
    /// Lowercase letters are sorted before uppercase letters.
    LowerFirst = 2
};

/// Specifies the data type used to determine sort order.
enum class XmlDataType
{
    /// Values are sorted alphabetically.
    Text = 1,
    /// Values are sorted numerically.
    Number = 2
};

/// Specifies the return type of the XPath expression.
enum class XPathResultType
{
    /// A numeric value.
    Number = 0,
    /// A String value.
    String = 1,
    /// A Boolean @c true or @c false value.
    Boolean = 2,
    /// A node collection.
    NodeSet = 3,
    /// A tree fragment.
    Navigator = static_cast<int32_t>(XPathResultType::String),
    /// Any of the XPath node types.
    Any = 5,
    /// The expression does not evaluate to the correct XPath type.
    Error
};

/// Provides a typed class that represents a compiled XPath expression.
class ASPOSECPP_SHARED_CLASS XPathExpression : public System::Object
{
    typedef XPathExpression ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathExpression>;

public:

    /// When overridden in a derived class, gets a @c string representation of the XPathExpression.
    /// @returns A @c string representation of the XPathExpression.
    virtual ASPOSECPP_SHARED_API String get_Expression() = 0;
    /// When overridden in a derived class, gets the result type of the XPath expression.
    /// @returns An XPathResultType value representing the result type of the XPath expression.
    virtual ASPOSECPP_SHARED_API XPathResultType get_ReturnType() = 0;

    /// When overridden in a derived class, sorts the nodes selected by the XPath expression according to the specified IComparer object.
    /// @param expr An object representing the sort key. This can be the @c string value of the node or
    /// an XPathExpression object with a compiled XPath expression.
    /// @param comparer An IComparer object that provides the specific data type comparisons for comparing two objects for equivalence.
    /// @throws XPathException The XPathExpression or sort key includes a prefix and either an XmlNamespaceManager is not provided,
    /// or the prefix cannot be found in the supplied XmlNamespaceManager.
    virtual ASPOSECPP_SHARED_API void AddSort(SharedPtr<Object> expr, SharedPtr<Collections::Generic::IComparer<SharedPtr<Object>>> comparer) = 0;
    /// When overridden in a derived class, sorts the nodes selected by the XPath expression according to the supplied parameters.
    /// @param expr An object representing the sort key. This can be the @c string value of the node or
    /// an XPathExpression object with a compiled XPath expression.
    /// @param order An XmlSortOrder value indicating the sort order.
    /// @param caseOrder An XmlCaseOrder value indicating how to sort uppercase and lowercase letters.
    /// @param lang The language to use for comparison.
    /// Uses the Globalization::CultureInfo class that can be passed to the String::Compare method for the language types,
    /// for example, "us-en" for U.S. English.
    /// If an empty string is specified, the system environment is used to determine the Globalization::CultureInfo.
    /// @param dataType An XmlDataType value indicating the sort order for the data type.
    /// @throws XPathException The XPathExpression or sort key includes a prefix and either an XmlNamespaceManager is not provided,
    /// or the prefix cannot be found in the supplied XmlNamespaceManager.
    virtual ASPOSECPP_SHARED_API void AddSort(SharedPtr<Object> expr, XmlSortOrder order, XmlCaseOrder caseOrder, String lang, XmlDataType dataType) = 0;
    /// When overridden in a derived class, returns a clone of this XPathExpression.
    /// @returns A new XPathExpression object.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathExpression> Clone() = 0;
    /// When overridden in a derived class, specifies the XmlNamespaceManager object to use for namespace resolution.
    /// @param nsManager An XmlNamespaceManager object to use for namespace resolution.
    /// @throws XPathException The XmlNamespaceManager object parameter is not derived from the XmlNamespaceManager class.
    virtual ASPOSECPP_SHARED_API void SetContext(SharedPtr<XmlNamespaceManager> nsManager) = 0;
    /// When overridden in a derived class, specifies the IXmlNamespaceResolver object to use for namespace resolution.
    /// @param nsResolver An object that implements the IXmlNamespaceResolver interface to use for namespace resolution.
    /// @throws XPathException The IXmlNamespaceResolver object parameter is not derived from IXmlNamespaceResolver.
    virtual ASPOSECPP_SHARED_API void SetContext(SharedPtr<IXmlNamespaceResolver> nsResolver) = 0;
    /// Compiles the XPath expression specified and returns an XPathExpression object representing the XPath expression.
    /// @param xpath An XPath expression.
    /// @returns An XPathExpression object.
    /// @throws ArgumentException The XPath expression parameter is not a valid XPath expression.
    /// @throws XPathException The XPath expression is not valid.
    static ASPOSECPP_SHARED_API SharedPtr<XPathExpression> Compile(const String& xpath);
    /// Compiles the specified XPath expression, with the IXmlNamespaceResolver object specified for namespace resolution,
    /// and returns an XPathExpression object that represents the XPath expression.
    /// @param xpath An XPath expression.
    /// @param nsResolver An object that implements the IXmlNamespaceResolver interface for namespace resolution.
    /// @returns An XPathExpression object.
    /// @throws ArgumentException The XPath expression parameter is not a valid XPath expression.
    /// @throws XPathException The XPath expression is not valid.
    static ASPOSECPP_SHARED_API SharedPtr<XPathExpression> Compile(const String& xpath, const SharedPtr<IXmlNamespaceResolver>& nsResolver);

protected:

    /// @cond
    XPathExpression();
    /// @endcond

};

} // namespace XPath
} // namespace Xml
} // namespace System

/// @cond
template<>
struct EnumMetaInfo<System::Xml::XPath::XmlSortOrder>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XmlSortOrder, const char_t*>, 2>& values();
};

template<>
struct EnumMetaInfo<System::Xml::XPath::XmlCaseOrder>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XmlCaseOrder, const char_t*>, 3>& values();
};

template<>
struct EnumMetaInfo<System::Xml::XPath::XmlDataType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XmlDataType, const char_t*>, 2>& values();
};

template<>
struct EnumMetaInfo<System::Xml::XPath::XPathResultType>
{
    static const ASPOSECPP_SHARED_API std::array<std::pair<System::Xml::XPath::XPathResultType, const char_t*>, 7>& values();
};
/// @endcond


