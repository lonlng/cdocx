/// @file xml/xpath/xpath_document.h

#pragma once

#include <xml/xpath/ixpath_navigable.h>
#include <xml/xml_space.h>
#include <system/shared_ptr.h>
#include <system/enum_helpers.h>


/// @cond
namespace System
{
namespace Internal
{
namespace Xml
{
namespace Cache
{
class XPathDocumentBuilder;
class XPathDocumentNavigator;
class XPathNode;
class XPathNodeHelper;
} // namespace Cache
} // namespace Xml
} // namespace Internal
namespace IO
{
class Stream;
class TextReader;
} // namespace IO
class String;
namespace Xml
{
class XmlNameTable;
class XmlRawWriter;
class XmlReader;
class XmlTextReaderImpl;
namespace XPath
{
class XPathDocumentImpl;
class XPathNavigator;
} // namespace XPath
namespace Xsl
{
namespace XsltOld
{
class NavigatorOutput;
} // namespace XsltOld
} // namespace Xsl
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Provides a fast, read-only, in-memory representation of an XML document by using the XPath data model.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XPathDocument : public IXPathNavigable
{
    typedef XPathDocument ThisType;
    typedef IXPathNavigable BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathDocument>;

private:
    /// @cond
    friend class Internal::Xml::Cache::XPathDocumentBuilder;
    friend class Internal::Xml::Cache::XPathDocumentNavigator;
    friend class Internal::Xml::Cache::XPathNode;
    friend class Internal::Xml::Cache::XPathNodeHelper;
    friend class XPathDocumentImpl;
    friend class Xsl::XsltOld::NavigatorOutput;
    /// @endcond

protected:

    /// @cond
    enum class LoadFlags
    {
        None = 0,
        AtomizeNames = 1,
        Fragment = 2
    };

    DECLARE_FRIEND_ENUM_OPERATORS(System::Xml::XPath::XPathDocument::LoadFlags);
    /// @endcond

public:

    /// Initializes a new instance of the XPathDocument class from the XML data that is contained in
    /// the specified XmlReader object.
    /// @param reader The XmlReader object that contains the XML data.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The XmlReader object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const SharedPtr<XmlReader>& reader);
    /// Initializes a new instance of the XPathDocument class from the XML data that is contained in
    /// the specified XmlReader object with the specified white space handling.
    /// @param reader The XmlReader object that contains the XML data.
    /// @param space An XmlSpace object.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The XmlReader object parameter or XmlSpace object parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const SharedPtr<XmlReader>& reader, XmlSpace space);
    /// Initializes a new instance of the XPathDocument class from the XML data that is contained in
    /// the specified TextReader object.
    /// @param textReader The TextReader object that contains the XML data.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The TextReader object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const SharedPtr<IO::TextReader>& textReader);
    /// Initializes a new instance of the XPathDocument class from the XML data in the specified Stream object.
    /// @param stream The Stream object that contains the XML data.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The Stream object passed as a parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const SharedPtr<IO::Stream>& stream);
    /// Initializes a new instance of the XPathDocument class from the XML data in the specified file.
    /// @param uri The path of the file that contains the XML data.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The file path parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const String& uri);
    /// Initializes a new instance of the XPathDocument class from the XML data in the file specified with
    /// the white space handling specified.
    /// @param uri The path of the file that contains the XML data.
    /// @param space An XmlSpace object.
    /// @throws XmlException An error was encountered in the XML data.
    /// The XPathDocument remains empty.
    /// @throws ArgumentNullException The file path parameter or XmlSpace object parameter is @c nullptr.
    ASPOSECPP_SHARED_API XPathDocument(const String& uri, XmlSpace space);

    /// Initializes a read-only XPathNavigator object for navigating through nodes in this XPathDocument.
    /// @returns A read-only XPathNavigator object.
    ASPOSECPP_SHARED_API SharedPtr<XPathNavigator> CreateNavigator() override;

protected:

    /// @cond
    SharedPtr<XPathDocumentImpl> get_Impl();
    SharedPtr<XmlNameTable> get_NameTable();
    bool get_HasLineInfo();

    XPathDocument();
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XPathDocument, CODEPORTING_ARGS());

    XPathDocument(const SharedPtr<XmlNameTable>& nameTable);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XPathDocument, CODEPORTING_ARGS(SharedPtr<XmlNameTable> nameTable));

    SharedPtr<XmlRawWriter> LoadFromWriter(XPathDocument::LoadFlags flags, const String& baseUri);
    void LoadFromReader(const SharedPtr<XmlReader>& reader, XmlSpace space);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XPathDocument();

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
    const char* DBG_class_name() const override { return "XPathDocument"; }
#endif
    /// @endcond

private:

    SharedPtr<XPathDocumentImpl> _impl;

    SharedPtr<XmlTextReaderImpl> SetupReader(const SharedPtr<XmlTextReaderImpl>& reader);

};

/// @cond
DECLARE_ENUM_OPERATORS(System::Xml::XPath::XPathDocument::LoadFlags);
DECLARE_USING_GLOBAL_OPERATORS
/// @endcond

} // namespace XPath
} // namespace Xml
} // namespace System

/// @cond
DECLARE_USING_ENUM_OPERATORS(System::Xml::XPath);
/// @endcond


