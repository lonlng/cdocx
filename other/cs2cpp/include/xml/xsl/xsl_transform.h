/// @file xml/xsl/xsl_transform.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace IO
{
class Stream;
class TextWriter;
} // namespace IO
class String;
namespace Xml
{
class XmlReader;
class XmlResolver;
class XmlWriter;
namespace XPath
{
class IXPathNavigable;
class XPathNavigator;
} // namespace XPath
namespace Xsl
{
class XsltArgumentList;
namespace XsltOld
{
namespace Debugger
{
class IXsltDebugger;
} // namespace Debugger
class RootAction;
class Stylesheet;
class TheQuery;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

/// Transforms XML data using an Extensible Stylesheet Language for Transformations (XSLT) style sheet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XslTransform final : public System::Object
{
    typedef XslTransform ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XslTransform>;

public:

    /// Sets the XmlResolver used to resolve external resources when the XslTransform::Transform method is called.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlResolver(const SharedPtr<System::Xml::XmlResolver>& value);

    /// Initializes a new instance of the XslTransform class.
    ASPOSECPP_SHARED_API XslTransform();

    /// Loads the XSLT style sheet contained in the XmlReader.
    /// @param stylesheet An XmlReader object that contains the XSLT style sheet.
    /// @throws XsltCompileException The current node does not conform to a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<XmlReader>& stylesheet);
    /// Loads the XSLT style sheet contained in the XmlReader.
    /// @param stylesheet An XmlReader object that contains the XSLT style sheet.
    /// @param resolver The XmlResolver used to load any style sheets referenced in @c xsl:import and @c xsl:include elements.
    /// If this is @c nullptr, external resources are not resolved.
    /// The XmlResolver is not cached after this method completes.
    /// @throws XsltCompileException The current node does not conform to a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<XmlReader>& stylesheet, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Loads the XSLT style sheet contained in the IXPathNavigable.
    /// @param stylesheet An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the XSLT style sheet.
    /// @throws XsltCompileException The loaded resource is not a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::IXPathNavigable>& stylesheet);
    /// Loads the XSLT style sheet contained in the IXPathNavigable.
    /// @param stylesheet An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the XSLT style sheet.
    /// @param resolver The XmlResolver used to load any style sheets referenced in @c xsl:import and @c xsl:include elements.
    /// If this is @c nullptr, external resources are not resolved.
    /// The XmlResolver is not cached after this method completes.
    /// @throws XsltCompileException The loaded resource is not a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::IXPathNavigable>& stylesheet, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Loads the XSLT style sheet contained in the XPathNavigator.
    /// @param stylesheet An XPathNavigator object that contains the XSLT style sheet.
    /// @throws XsltCompileException The current node does not conform to a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::XPathNavigator>& stylesheet);
    /// Loads the XSLT style sheet contained in the XPathNavigator.
    /// @param stylesheet An XPathNavigator object that contains the XSLT style sheet.
    /// @param resolver The XmlResolver used to load any style sheets referenced in @c xsl:import and @c xsl:include elements.
    /// If this is @c nullptr, external resources are not resolved.
    /// The XmlResolver is not cached after this method completes.
    /// @throws XsltCompileException The current node does not conform to a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::XPathNavigator>& stylesheet, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Loads the XSLT style sheet specified by a URL.
    /// @param url The URL that specifies the XSLT style sheet to load.
    /// @throws XsltCompileException The loaded resource is not a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const String& url);
    /// Loads the XSLT style sheet specified by a URL.
    /// @param url The URL that specifies the XSLT style sheet to load.
    /// @param resolver The XmlResolver to use to load the style sheet and
    /// any style sheet(s) referenced in @c xsl:import and @c xsl:include elements.
    /// If this is @c nullptr, a default XmlUrlResolver with no user credentials is used to open the style sheet.
    /// The default XmlUrlResolver is not used to resolve any external resources in the style sheet,
    /// so @c xsl:import and @c xsl:include elements are not resolved.
    /// The XmlResolver is not cached after this method completes.
    /// @throws XsltCompileException The loaded resource is not a valid style sheet.
    ASPOSECPP_SHARED_API void Load(const String& url, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to an XmlReader.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @returns An XmlReader containing the results of the transformation.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API SharedPtr<XmlReader> Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to an XmlReader.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @returns An XmlReader containing the results of the transformation.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API SharedPtr<XmlReader> Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args);
    /// Transforms the XML data in the XPathNavigator using the specified args and outputs the result to an XmlWriter.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The XmlWriter to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<XmlWriter>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the XPathNavigator using the specified args and outputs the result to an XmlWriter.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The XmlWriter to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<XmlWriter>& output);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to a Stream.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The stream to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::Stream>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to a Stream.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The stream to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::Stream>& output);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to a TextWriter.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The TextWriter to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::TextWriter>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the XPathNavigator using the specified @p args and outputs the result to a TextWriter.
    /// @param input An XPathNavigator containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The TextWriter to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::XPathNavigator>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::TextWriter>& output);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to an XmlReader.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @returns An XmlReader containing the results of the transformation.
    ASPOSECPP_SHARED_API SharedPtr<XmlReader> Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to an XmlReader.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @returns An XmlReader containing the results of the transformation.
    ASPOSECPP_SHARED_API SharedPtr<XmlReader> Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to a TextWriter.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The TextWriter to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::TextWriter>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to a TextWriter.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The TextWriter to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::TextWriter>& output);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to a Stream.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The stream to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the XslTransform::Transform method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::Stream>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to a Stream.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The stream to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<IO::Stream>& output);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to an XmlWriter.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The XmlWriter to which you want to output.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the this method completes.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<XmlWriter>& output, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the IXPathNavigable using the specified @p args and outputs the result to an XmlWriter.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param args An XsltArgumentList containing the namespace-qualified arguments used as input to the transformation.
    /// @param output The XmlWriter to which you want to output.
    /// @throws InvalidOperationException There was an error processing the XSLT transformation.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& args, const SharedPtr<XmlWriter>& output);
    /// Transforms the XML data in the input file and outputs the result to an output file.
    /// @param inputfile The URL of the source document to be transformed.
    /// @param outputfile The URL of the output file.
    /// @param resolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// The XmlResolver is not cached after the XslTransform::Transform method completes.
    ASPOSECPP_SHARED_API void Transform(const String& inputfile, const String& outputfile, const SharedPtr<System::Xml::XmlResolver>& resolver);
    /// Transforms the XML data in the input file and outputs the result to an output file.
    /// @param inputfile The URL of the source document to be transformed.
    /// @param outputfile The URL of the output file.
    ASPOSECPP_SHARED_API void Transform(const String& inputfile, const String& outputfile);

protected:

    /// @cond
    SharedPtr<XsltOld::Debugger::IXsltDebugger> get_Debugger();

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
    const char* DBG_class_name() const override { return "XslTransform"; }
#endif
    /// @endcond

private:

    SharedPtr<System::Xml::XmlResolver> _documentResolver;
    bool _isDocumentResolverSet;

    SharedPtr<System::Xml::XmlResolver> get__DocumentResolver();

    SharedPtr<XsltOld::Stylesheet> _CompiledStylesheet;
    SharedPtr<Collections::Generic::List<SharedPtr<XsltOld::TheQuery>>> _QueryStore;
    SharedPtr<XsltOld::RootAction> _RootAction;
    SharedPtr<XsltOld::Debugger::IXsltDebugger> _debugger;

    void CheckCommand();
    void Compile(const SharedPtr<System::Xml::XPath::XPathNavigator>& stylesheet, const SharedPtr<System::Xml::XmlResolver>& resolver);
    static SharedPtr<System::Xml::XmlResolver> CreateDefaultResolver();

};

} // namespace Xsl
} // namespace Xml
} // namespace System


