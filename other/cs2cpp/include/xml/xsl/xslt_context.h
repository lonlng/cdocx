/// @file xml/xsl/xslt_context.h

#pragma once

#include <xml/xpath/xpath_expression.h>
#include <xml/xml_namespace_manager.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Internal
{
namespace Xml
{
namespace XPath
{
class CompiledXpathExpr;
} // namespace XPath
} // namespace Xml
} // namespace Internal
namespace Xml
{
class NameTable;
namespace XPath
{
class XPathNavigator;
} // namespace XPath
namespace Xsl
{
class XsltContext;
namespace XsltOld
{
class XsltCompileContext;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

/// Provides an interface to a given function defined in the Extensible Stylesheet Language for
/// Transformations (XSLT) style sheet during runtime execution.
class ASPOSECPP_SHARED_CLASS IXsltContextFunction : public System::Object
{
    typedef IXsltContextFunction ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns the minimum number of arguments for the function.
    /// This enables the user to differentiate between overloaded functions.
    /// @returns The minimum number of arguments for the function.
    virtual int32_t get_Minargs() = 0;
    /// Returns the maximum number of arguments for the function.
    /// This enables the user to differentiate between overloaded functions.
    /// @returns The maximum number of arguments for the function.
    virtual int32_t get_Maxargs() = 0;
    /// Returns the XPathResultType representing the XPath type returned by the function.
    /// @returns An XPathResultType representing the XPath type returned by the function.
    virtual System::Xml::XPath::XPathResultType get_ReturnType() = 0;
    /// Returns the supplied XML Path Language (XPath) types for the function's argument list.
    /// This information can be used to discover the signature of the function which allows you to
    /// differentiate between overloaded functions.
    /// @returns An array of XPathResultType representing the types for the function's argument list.
    virtual ArrayPtr<System::Xml::XPath::XPathResultType> get_ArgTypes() = 0;

    /// Provides the method to invoke the function with the given arguments in the given context.
    /// @param xsltContext The XSLT context for the function call.
    /// @param args The arguments of the function call. Each argument is an element in the array.
    /// @param docContext The context node for the function call.
    /// @returns An Object representing the return value of the function.
    virtual SharedPtr<Object> Invoke(SharedPtr<XsltContext> xsltContext, ArrayPtr<SharedPtr<Object>> args, SharedPtr<System::Xml::XPath::XPathNavigator> docContext) = 0;

};

/// Provides an interface to a given variable that is defined in the style sheet during runtime execution.
class ASPOSECPP_SHARED_CLASS IXsltContextVariable : public virtual System::Object
{
    typedef IXsltContextVariable ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// Returns a value indicating whether the variable is local.
    /// @returns @c true if the variable is a local variable in the current context; otherwise, @c false.
    virtual bool get_IsLocal() = 0;
    /// Returns a value indicating whether the variable is an Extensible Stylesheet Language Transformations (XSLT) parameter.
    /// This can be a parameter to a style sheet or a template.
    /// @returns @c true if the variable is an XSLT parameter; otherwise, @c false.
    virtual bool get_IsParam() = 0;
    /// Returns the XPathResultType representing the XML Path Language (XPath) type of the variable.
    /// @returns The XPathResultType representing the XPath type of the variable.
    virtual System::Xml::XPath::XPathResultType get_VariableType() = 0;

    /// Evaluates the variable at runtime and returns an object that represents the value of the variable.
    /// @param xsltContext An XsltContext representing the execution context of the variable.
    /// @returns An Object representing the value of the variable.
    /// Possible return types include number, string, Boolean, document fragment, or node set.
    virtual SharedPtr<Object> Evaluate(SharedPtr<XsltContext> xsltContext) = 0;

};

/// Encapsulates the current execution context of the Extensible Stylesheet Language for
/// Transformations (XSLT) processor allowing XML Path Language (XPath) to resolve functions, parameters,
/// and namespaces within XPath expressions.
class ASPOSECPP_SHARED_CLASS XsltContext : public XmlNamespaceManager
{
    typedef XsltContext ThisType;
    typedef XmlNamespaceManager BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltContext>;

private:
    /// @cond
    friend class Internal::Xml::XPath::CompiledXpathExpr;
    friend class XsltOld::XsltCompileContext;
    /// @endcond

public:

    /// When overridden in a derived class, gets a value indicating whether to include white space nodes in the output.
    /// @returns @c true to check white space nodes in the source document for inclusion in the output;
    /// @c false to not evaluate white space nodes. The default is @c true.
    virtual ASPOSECPP_SHARED_API bool get_Whitespace() = 0;

    /// When overridden in a derived class, resolves a variable reference and returns an IXsltContextVariable representing the variable.
    /// @param prefix The prefix of the variable as it appears in the XPath expression.
    /// @param name The name of the variable.
    /// @returns An IXsltContextVariable representing the variable at runtime.
    virtual ASPOSECPP_SHARED_API SharedPtr<IXsltContextVariable> ResolveVariable(String prefix, String name) = 0;
    /// When overridden in a derived class, resolves a function reference and returns an IXsltContextFunction representing the function.
    /// The IXsltContextFunction is used at execution time to get the return value of the function.
    /// @param prefix The prefix of the function as it appears in the XPath expression.
    /// @param name The name of the function.
    /// @param ArgTypes An array of argument types for the function being resolved.
    /// This allows you to select between methods with the same name (for example, overloaded methods).
    /// @returns An IXsltContextFunction representing the function.
    virtual ASPOSECPP_SHARED_API SharedPtr<IXsltContextFunction> ResolveFunction(String prefix, String name, ArrayPtr<System::Xml::XPath::XPathResultType> ArgTypes) = 0;
    /// When overridden in a derived class, evaluates whether to preserve white space nodes or strip them for the given context.
    /// @param node The white space node that is to be preserved or stripped in the current context.
    /// @returns @c true if the white space is to be preserved; @c false if the white space is to be stripped.
    virtual ASPOSECPP_SHARED_API bool PreserveWhitespace(SharedPtr<System::Xml::XPath::XPathNavigator> node) = 0;
    /// When overridden in a derived class, compares the base Uniform Resource Identifiers (URIs) of
    /// two documents based upon the order the documents were loaded by the XSLT processor (that is, the XslTransform class).
    /// @param baseUri The base URI of the first document to compare.
    /// @param nextbaseUri The base URI of the second document to compare.
    /// @returns An integer value describing the relative order of the two base URIs:
    /// -1 if @p baseUri occurs before @p nextbaseUri;
    /// 0 if the two base URIs are identical;
    /// and 1 if @p baseUri occurs after @p nextbaseUri.
    virtual ASPOSECPP_SHARED_API int32_t CompareDocument(String baseUri, String nextbaseUri) = 0;

protected:

    /// Initializes a new instance of the XsltContext class with the specified NameTable.
    /// @param table The NameTable to use.
    ASPOSECPP_SHARED_API XsltContext(const SharedPtr<System::Xml::NameTable>& table);
    /// Initializes a new instance of the XsltContext class.
    ASPOSECPP_SHARED_API XsltContext();

    /// @cond
    XsltContext(bool dummy);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XsltContext();

};

} // namespace Xsl
} // namespace Xml
} // namespace System


