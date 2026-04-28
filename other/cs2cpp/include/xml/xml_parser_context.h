/// @file xml/xml_parser_context.h

#pragma once

#include <xml/xml_space.h>
#include <system/string.h>


/// @cond
namespace System
{
namespace Text
{
class Encoding;
} // namespace Text
namespace Xml
{
class XmlNamespaceManager;
class XmlNameTable;
class XmlTextReaderImpl;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Provides all the context information required by the XmlReader to parse an XML fragment.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlParserContext : public System::Object
{
    typedef XmlParserContext ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlParserContext>;

private:
    /// @cond
    friend class XmlTextReaderImpl;
    /// @endcond

public:

    /// Returns the XmlNameTable used to atomize strings. For more information on atomized strings, see XmlNameTable.
    /// @returns The XmlNameTable.
    ASPOSECPP_SHARED_API SharedPtr<XmlNameTable> get_NameTable();
    /// Sets the XmlNameTable used to atomize strings. For more information on atomized strings, see XmlNameTable.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NameTable(const SharedPtr<XmlNameTable>& value);
    /// Returns the XmlNamespaceManager.
    /// @returns The XmlNamespaceManager.
    ASPOSECPP_SHARED_API SharedPtr<XmlNamespaceManager> get_NamespaceManager();
    /// Sets the XmlNamespaceManager.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_NamespaceManager(const SharedPtr<XmlNamespaceManager>& value);
    /// Returns the name of the document type declaration.
    /// @returns The name of the document type declaration.
    ASPOSECPP_SHARED_API String get_DocTypeName();
    /// Sets the name of the document type declaration.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_DocTypeName(const String& value);
    /// Returns the public identifier.
    /// @returns The public identifier.
    ASPOSECPP_SHARED_API String get_PublicId();
    /// Sets the public identifier.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_PublicId(const String& value);
    /// Returns the system identifier.
    /// @returns The system identifier.
    ASPOSECPP_SHARED_API String get_SystemId();
    /// Sets the system identifier.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_SystemId(const String& value);
    /// Returns the base URI.
    /// @returns The base URI to use to resolve the DTD file.
    ASPOSECPP_SHARED_API String get_BaseURI();
    /// Sets the base URI.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_BaseURI(const String& value);
    /// Returns the internal DTD subset.
    /// @returns The internal DTD subset.
    /// For example, this method returns everything between the square brackets <tt><!DOCTYPE doc [...]></tt>.
    ASPOSECPP_SHARED_API String get_InternalSubset();
    /// Sets the internal DTD subset.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_InternalSubset(const String& value);
    /// Returns the current @c xml:lang scope.
    /// @returns The current @c xml:lang scope. If there is no @c xml:lang in scope, String::Empty is returned.
    ASPOSECPP_SHARED_API String get_XmlLang();
    /// Sets the current @c xml:lang scope.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlLang(const String& value);
    /// Returns the current @c xml:space scope.
    /// @returns An XmlSpace value indicating the @c xml:space scope.
    ASPOSECPP_SHARED_API System::Xml::XmlSpace get_XmlSpace();
    /// Sets the current @c xml:space scope.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_XmlSpace(System::Xml::XmlSpace value);
    /// Returns the encoding type.
    /// @returns An Encoding object indicating the encoding type.
    ASPOSECPP_SHARED_API SharedPtr<System::Text::Encoding> get_Encoding();
    /// Sets the encoding type.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Encoding(const SharedPtr<System::Text::Encoding>& value);

    /// Initializes a new instance of the XmlParserContext class with the specified XmlNameTable, XmlNamespaceManager,
    /// @c xml:lang, and @c xml:space values.
    /// @param nt The XmlNameTable to use to atomize strings.
    /// If this is @c nullptr, the name table used to construct the @p nsMgr is used instead.
    /// For more information about atomized strings, see XmlNameTable.
    /// @param nsMgr The XmlNamespaceManager to use for looking up namespace information, or @c nullptr.
    /// @param xmlLang The @c xml:lang scope.
    /// @param xmlSpace An XmlSpace value indicating the @c xml:space scope.
    /// @throws XmlException @p nt is not the same XmlNameTable used to construct @p nsMgr.
    ASPOSECPP_SHARED_API XmlParserContext(const SharedPtr<XmlNameTable>& nt, const SharedPtr<XmlNamespaceManager>& nsMgr, const String& xmlLang, System::Xml::XmlSpace xmlSpace);
    /// Initializes a new instance of the XmlParserContext class with the specified XmlNameTable, XmlNamespaceManager,
    /// @c xml:lang, @c xml:space, and encoding.
    /// @param nt The XmlNameTable to use to atomize strings.
    /// If this is @c nullptr, the name table used to construct the @p nsMgr is used instead.
    /// For more information on atomized strings, see XmlNameTable.
    /// @param nsMgr The XmlNamespaceManager to use for looking up namespace information, or @c nullptr.
    /// @param xmlLang The @c xml:lang scope.
    /// @param xmlSpace An XmlSpace value indicating the @c xml:space scope.
    /// @param enc An Encoding object indicating the encoding setting.
    /// @throws XmlException @p nt is not the same XmlNameTable used to construct @p nsMgr.
    ASPOSECPP_SHARED_API XmlParserContext(const SharedPtr<XmlNameTable>& nt, const SharedPtr<XmlNamespaceManager>& nsMgr, const String& xmlLang, System::Xml::XmlSpace xmlSpace, const SharedPtr<System::Text::Encoding>& enc);
    /// Initializes a new instance of the XmlParserContext class with the specified XmlNameTable, XmlNamespaceManager,
    /// base URI, @c xml:lang, @c xml:space, and document type values.
    /// @param nt The XmlNameTable to use to atomize strings.
    /// If this is @c nullptr, the name table used to construct the @p nsMgr is used instead.
    /// For more information about atomized strings, see XmlNameTable.
    /// @param nsMgr The XmlNamespaceManager to use for looking up namespace information, or @c nullptr.
    /// @param docTypeName The name of the document type declaration.
    /// @param pubId The public identifier.
    /// @param sysId The system identifier.
    /// @param internalSubset The internal DTD subset. The DTD subset is used for entity resolution, not for document validation.
    /// @param baseURI The base URI for the XML fragment (the location from which the fragment was loaded).
    /// @param xmlLang The @c xml:lang scope.
    /// @param xmlSpace An XmlSpace value indicating the @c xml:space scope.
    /// @throws XmlException @p nt is not the same XmlNameTable used to construct @p nsMgr.
    ASPOSECPP_SHARED_API XmlParserContext(const SharedPtr<XmlNameTable>& nt, const SharedPtr<XmlNamespaceManager>& nsMgr, const String& docTypeName, const String& pubId, const String& sysId, const String& internalSubset, const String& baseURI, const String& xmlLang, System::Xml::XmlSpace xmlSpace);
    /// Initializes a new instance of the XmlParserContext class with the specified XmlNameTable, XmlNamespaceManager,
    /// base URI, @c xml:lang, @c xml:space, encoding, and document type values.
    /// @param nt The XmlNameTable to use to atomize strings.
    /// If this is @c nullptr, the name table used to construct the @p nsMgr is used instead.
    /// For more information about atomized strings, see XmlNameTable.
    /// @param nsMgr The XmlNamespaceManager to use for looking up namespace information, or @c nullptr.
    /// @param docTypeName The name of the document type declaration.
    /// @param pubId The public identifier.
    /// @param sysId The system identifier.
    /// @param internalSubset The internal DTD subset. The DTD is used for entity resolution, not for document validation.
    /// @param baseURI The base URI for the XML fragment (the location from which the fragment was loaded).
    /// @param xmlLang The @c xml:lang scope.
    /// @param xmlSpace An XmlSpace value indicating the @c xml:space scope.
    /// @param enc An Encoding object indicating the encoding setting.
    /// @throws XmlException @p nt is not the same XmlNameTable used to construct @p nsMgr.
    ASPOSECPP_SHARED_API XmlParserContext(const SharedPtr<XmlNameTable>& nt, const SharedPtr<XmlNamespaceManager>& nsMgr, const String& docTypeName, const String& pubId, const String& sysId, const String& internalSubset, const String& baseURI, const String& xmlLang, System::Xml::XmlSpace xmlSpace, const SharedPtr<System::Text::Encoding>& enc);

protected:

    /// @cond
    bool get_HasDtdInfo();

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
    const char* DBG_class_name() const override { return "XmlParserContext"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlNameTable> _nt;
    SharedPtr<XmlNamespaceManager> _nsMgr;
    String _docTypeName;
    String _pubId;
    String _sysId;
    String _internalSubset;
    String _xmlLang;
    System::Xml::XmlSpace _xmlSpace;
    String _baseURI;
    SharedPtr<System::Text::Encoding> _encoding;

};

} // namespace Xml
} // namespace System


