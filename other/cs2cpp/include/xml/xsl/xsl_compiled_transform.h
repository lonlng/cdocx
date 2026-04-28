/// @file xml/xsl/xsl_compiled_transform.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
namespace IO
{
class Stream;
class TextWriter;
} // namespace IO
class String;
namespace Xml
{
class XmlReader;
class XmlReaderSettings;
class XmlResolver;
class XmlWriter;
class XmlWriterSettings;
namespace XPath
{
class IXPathNavigable;
} // namespace XPath
namespace Xsl
{
class XsltArgumentList;
class XslTransform;
class XsltSettings;
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

/// Transforms XML data using an XSLT style sheet.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XslCompiledTransform final : public System::Object
{
    typedef XslCompiledTransform ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XslCompiledTransform>;

public:

    /// Returns an XmlWriterSettings object that contains the output information derived from
    /// the @c xsl:output element of the style sheet.
    /// @returns A read-only XmlWriterSettings object that contains the output information derived from
    /// the @c xsl:output element of the style sheet.
    /// This value can be @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlWriterSettings> get_OutputSettings();

    /// Initializes a new instance of the XslCompiledTransform class.
    ASPOSECPP_SHARED_API XslCompiledTransform();

    /// Compiles the style sheet contained in the XmlReader.
    /// @param stylesheet An XmlReader containing the style sheet.
    /// @throws ArgumentNullException The @p stylesheet value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<XmlReader>& stylesheet);
    /// Compiles the XSLT style sheet contained in the XmlReader.
    /// The XmlResolver resolves any XSLT @c import or @c include elements and
    /// the XSLT settings determine the permissions for the style sheet.
    /// @param stylesheet The XmlReader containing the style sheet.
    /// @param settings The XsltSettings to apply to the style sheet.
    /// If this is @c nullptr, the XsltSettings::get_Default setting is applied.
    /// @param stylesheetResolver The XmlResolver used to resolve any
    /// style sheets referenced in XSLT @c import and @c include elements.
    /// If this is @c nullptr, external resources are not resolved.
    /// @throws ArgumentNullException The @p stylesheet value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<XmlReader>& stylesheet, const SharedPtr<XsltSettings>& settings, const SharedPtr<XmlResolver>& stylesheetResolver);
    /// Loads and compiles the style sheet located at the specified URI.
    /// @param stylesheetUri The URI of the style sheet.
    /// @throws ArgumentNullException The @p stylesheetUri value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    /// @throws FileNotFoundException The style sheet cannot be found.
    /// @throws DirectoryNotFoundException The @p stylesheetUri value includes a filename or directory that cannot be found.
    /// @throws WebException The @p stylesheetUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p stylesheetUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the style sheet.
    ASPOSECPP_SHARED_API void Load(const String& stylesheetUri);
    /// Loads and compiles the XSLT style sheet specified by the URI.
    /// The XmlResolver resolves any XSLT @c import or @c include elements and
    /// the XSLT settings determine the permissions for the style sheet.
    /// @param stylesheetUri The URI of the style sheet.
    /// @param settings The XsltSettings to apply to the style sheet.
    /// If this is @c nullptr, the XsltSettings::get_Default setting is applied.
    /// @param stylesheetResolver The XmlResolver used to resolve the style sheet URI and
    /// any style sheets referenced in XSLT @c import and @c include elements.
    /// @throws ArgumentNullException The @p stylesheetUri or @p stylesheetResolver value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    /// @throws FileNotFoundException The style sheet cannot be found.
    /// @throws DirectoryNotFoundException The @p stylesheetUri value includes a filename or directory that cannot be found.
    /// @throws WebException The @p stylesheetUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p stylesheetUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the style sheet.
    ASPOSECPP_SHARED_API void Load(const String& stylesheetUri, const SharedPtr<XsltSettings>& settings, const SharedPtr<XmlResolver>& stylesheetResolver);
    /// Compiles the style sheet contained in the IXPathNavigable object.
    /// @param stylesheet An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the style sheet.
    /// @throws ArgumentNullException The @p stylesheet value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::IXPathNavigable>& stylesheet);
    /// Compiles the XSLT style sheet contained in the IXPathNavigable.
    /// The XmlResolver resolves any XSLT @c import or @c include elements and the XSLT settings determine the permissions for the style sheet.
    /// @param stylesheet An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the style sheet.
    /// @param settings The XsltSettings to apply to the style sheet.
    /// If this is @c nullptr, the XsltSettings::get_Default setting is applied.
    /// @param stylesheetResolver The XmlResolver used to resolve any style sheets referenced in XSLT @c import and @c include elements.
    /// If this is @c nullptr, external resources are not resolved.
    /// @throws ArgumentNullException The @p stylesheet value is @c nullptr.
    /// @throws XsltException The style sheet contains an error.
    ASPOSECPP_SHARED_API void Load(const SharedPtr<System::Xml::XPath::IXPathNavigable>& stylesheet, SharedPtr<XsltSettings> settings, SharedPtr<XmlResolver> stylesheetResolver);
    /// Executes the transform using the input document specified by the IXPathNavigable object and outputs the results to an XmlWriter.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the IXPathNavigable object and outputs the results to an XmlWriter.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the IXPathNavigable object and outputs the results to an TextWriter.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The TextWriter to which you want to output.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::TextWriter>& results);
    /// Executes the transform using the input document specified by the IXPathNavigable object and outputs the results to a stream.
    /// The XsltArgumentList provides additional runtime arguments.
    /// @param input An object implementing the IXPathNavigable interface.
    /// It can be either an XmlNode (typically an XmlDocument), or an XPathDocument containing the data to be transformed.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The stream to which you want to output.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::Stream>& results);
    /// Executes the transform using the input document specified by the XmlReader object and outputs the results to an XmlWriter.
    /// @param input The XmlReader containing the input document.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<XmlReader>& input, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the XmlReader object and outputs the results to an XmlWriter.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param input An XmlReader containing the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<XmlReader>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the XmlReader object and outputs the results to a TextWriter.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param input An XmlReader containing the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The TextWriter to which you want to output.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<XmlReader>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::TextWriter>& results);
    /// Executes the transform using the input document specified by the XmlReader object and outputs the results to a stream.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param input An XmlReader containing the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The stream to which you want to output.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<XmlReader>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::Stream>& results);
    /// Executes the transform using the input document specified by the URI and outputs the results to an XmlWriter.
    /// @param inputUri The URI of the input document.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p inputUri or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    /// @throws DirectoryNotFoundException The @p inputUri value includes a filename or directory cannot be found.
    /// @throws WebException The @p inputUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p inputUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the input document.
    ASPOSECPP_SHARED_API void Transform(const String& inputUri, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the URI and outputs the results to an XmlWriter.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param inputUri The URI of the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @throws ArgumentNullException The @p inputUri or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    /// @throws DirectoryNotFoundException The @p inputtUri value includes a filename or directory cannot be found.
    /// @throws WebException The @p inputUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p inputUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the input document.
    ASPOSECPP_SHARED_API void Transform(const String& inputUri, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<XmlWriter>& results);
    /// Executes the transform using the input document specified by the URI and outputs the results to a TextWriter.
    /// @param inputUri The URI of the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The TextWriter to which you want to output.
    /// @throws ArgumentNullException The @p inputUri or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    /// @throws DirectoryNotFoundException The @p inputUri value includes a filename or directory cannot be found.
    /// @throws WebException The @p inputUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p inputUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the input document.
    ASPOSECPP_SHARED_API void Transform(const String& inputUri, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::TextWriter>& results);
    /// Executes the transform using the input document specified by the URI and outputs the results to stream.
    /// The XsltArgumentList provides additional run-time arguments.
    /// @param inputUri The URI of the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The stream to which you want to output.
    /// @throws ArgumentNullException The @p inputUri or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    /// @throws DirectoryNotFoundException The @p inputUri value includes a filename or directory cannot be found.
    /// @throws WebException The @p inputUri value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p inputUri is not a valid URI.
    /// @throws XmlException There was a parsing error loading the input document.
    ASPOSECPP_SHARED_API void Transform(const String& inputUri, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<IO::Stream>& results);
    /// Executes the transform using the input document specified by the URI and outputs the results to a file.
    /// @param inputUri The URI of the input document.
    /// @param resultsFile The URI of the output file.
    /// @throws ArgumentNullException The @p inputUri or @p resultsFile value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    /// @throws FileNotFoundException The input document cannot be found.
    /// @throws DirectoryNotFoundException The @p inputUri or @p resultsFile value includes a filename or directory cannot be found.
    /// @throws WebException The @p inputUri or @p resultsFile value cannot be resolved.
    /// or
    /// An error occurred while processing the request.
    /// @throws UriFormatException @p inputUri or @p resultsFile is not a valid URI.
    /// @throws XmlException There was a parsing error loading the input document.
    ASPOSECPP_SHARED_API void Transform(const String& inputUri, const String& resultsFile);
    /// Executes the transform using the input document specified by the XmlReader object and outputs the results to an XmlWriter.
    /// The XsltArgumentList provides additional run-time arguments and the XmlResolver resolves the XSLT @c document() function.
    /// @param input An XmlReader containing the input document.
    /// @param arguments An XsltArgumentList containing the namespace-qualified arguments used as input to the transform.
    /// This value can be @c nullptr.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter using
    /// the XmlWriterSettings object returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @param documentResolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    /// @throws ArgumentNullException The @p input or @p results value is @c nullptr.
    /// @throws XsltException There was an error executing the XSLT transform.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<XmlReader>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<XmlWriter>& results, const SharedPtr<XmlResolver>& documentResolver);
    /// Executes the transform by using the input document that is specified by the IXPathNavigable object and
    /// outputs the results to an XmlWriter.
    /// The XsltArgumentList provides additional run-time arguments and the XmlResolver resolves the XSLT @c document() function.
    /// @param input The document to transform that is specified by the IXPathNavigable object.
    /// @param arguments Argument list as XsltArgumentList.
    /// @param results The XmlWriter to which you want to output.
    /// If the style sheet contains an @c xsl:output element, you should create the XmlWriter by
    /// using the XmlWriterSettings object that is returned from the XslCompiledTransform::get_OutputSettings value.
    /// This ensures that the XmlWriter has the correct output settings.
    /// @param documentResolver The XmlResolver used to resolve the XSLT @c document() function.
    /// If this is @c nullptr, the @c document() function is not resolved.
    ASPOSECPP_SHARED_API void Transform(const SharedPtr<System::Xml::XPath::IXPathNavigable>& input, const SharedPtr<XsltArgumentList>& arguments, const SharedPtr<XmlWriter>& results, const SharedPtr<XmlResolver>& documentResolver);

protected:

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
        const char* DBG_class_name() const override { return "XslCompiledTransform"; }
    #endif
    /// @endcond

private:

    SharedPtr<XslTransform> _impl;
    SharedPtr<XmlWriterSettings> _outputSettings;
    static SharedPtr<XmlReaderSettings> s_readerSettings;

    static void CheckArguments(const SharedPtr<Object>& input, const SharedPtr<Object>& results);
    static void CheckArguments(const String& inputUri, const SharedPtr<Object>& results);
    static SharedPtr<XmlResolver> CreateDefaultResolver();

};

} // namespace Xsl
} // namespace Xml
} // namespace System


