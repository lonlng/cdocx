/// @file xml/xml_implementation.h

#pragma once

#include <system/object.h>


/// @cond
namespace System
{
class String;
namespace Xml
{
class XmlDocument;
class XmlNameTable;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Defines the context for a set of XmlDocument objects.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlImplementation : public System::Object
{
    typedef XmlImplementation ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlImplementation>;

private:
    /// @cond
    friend class XmlDocument;
    /// @endcond

public:

    /// Initializes a new instance of the XmlImplementation class.
    ASPOSECPP_SHARED_API XmlImplementation();
    /// Initializes a new instance of the XmlImplementation class with the XmlNameTable specified.
    /// @param nt An XmlNameTable object.
    ASPOSECPP_SHARED_API XmlImplementation(const SharedPtr<XmlNameTable>& nt);

    /// Tests if the Document Object Model (DOM) implementation implements a specific feature.
    /// @param strFeature The package name of the feature to test. This name is not case-sensitive.
    /// @param strVersion This is the version number of the package name to test.
    /// If the version is not specified (@c nullptr), supporting any version of the feature causes the method to return @c true.
    /// @returns @c true if the feature is implemented in the specified version; otherwise, @c false.
    ///
    /// The following table shows the combinations that cause @c HasFeature to return @c true.
    /// <list type="table"><listheader><term> strFeature
    /// </term><description> strVersion
    /// </description></listheader><item><term> XML
    /// </term><description> 1.0
    /// </description></item><item><term> XML
    /// </term><description> 2.0
    /// </description></item></list>
    ASPOSECPP_SHARED_API bool HasFeature(const String& strFeature, const String& strVersion);
    /// Creates a new XmlDocument.
    /// @returns The new XmlDocument object.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlDocument> CreateDocument();

protected:

    /// @cond
    SharedPtr<XmlNameTable> get_NameTable();
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlImplementation();

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
    const char* DBG_class_name() const override { return "XmlImplementation"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlNameTable> _nameTable;

};

} // namespace Xml
} // namespace System


