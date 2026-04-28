/// @file xml/xsl/xslt_argument_list.h

#pragma once

#include <system/string.h>
#include <system/multicast_delegate.h>
#include <system/eventargs.h>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Xsl {

/// Provides data for the XsltArgumentList::XsltMessageEncountered event.
class ASPOSECPP_SHARED_CLASS XsltMessageEncounteredEventArgs : public EventArgs
{
    typedef XsltMessageEncounteredEventArgs ThisType;
    typedef EventArgs BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltMessageEncounteredEventArgs>;

public:

    /// Returns the contents of the @c xsl:message element.
    /// @returns The contents of the @c xsl:message element.
    virtual ASPOSECPP_SHARED_API String get_Message() = 0;

};

/// Represents the method that will handle the XsltArgumentList::XsltMessageEncountered event.
/// @param sender The source of the event.
/// @param e The XsltMessageEncounteredEventArgs containing the event data.
using XsltMessageEncounteredEventHandler = System::MulticastDelegate<void(SharedPtr<Object> /*sender*/, SharedPtr<XsltMessageEncounteredEventArgs> /*e*/)>;

/// Contains a variable number of arguments which are either XSLT parameters or extension objects.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XsltArgumentList : public System::Object
{
    typedef XsltArgumentList ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XsltArgumentList>;

public:

    /// Occurs when a message is specified in the style sheet by the @c xsl:message element.
    XsltMessageEncounteredEventHandler XsltMessageEncountered;

    /// Implements a new instance of the XsltArgumentList.
    ASPOSECPP_SHARED_API XsltArgumentList();

    /// Returns the parameter associated with the namespace qualified name.
    /// @param name The name of the parameter.
    /// XsltArgumentList does not check to ensure the name passed is a valid local name;
    /// however, the name cannot be @c nullptr.
    /// @param namespaceUri The namespace URI associated with the parameter.
    /// @returns The parameter object or @c nullptr if one was not found.
    ASPOSECPP_SHARED_API SharedPtr<Object> GetParam(const String& name, const String& namespaceUri);
    /// Returns the object associated with the given namespace.
    /// @param namespaceUri The namespace URI of the object.
    /// @returns The namespace URI object or @c nullptr if one was not found.
    ASPOSECPP_SHARED_API SharedPtr<Object> GetExtensionObject(const String& namespaceUri);
    /// Adds a parameter to the XsltArgumentList and associates it with the namespace qualified name.
    /// @param name The name to associate with the parameter.
    /// @param namespaceUri The namespace URI to associate with the parameter.
    /// To use the default namespace, specify an empty string.
    /// @param parameter The parameter value or object to add to the list.
    /// @throws ArgumentException The @p namespaceUri is either @c nullptr or http://www.w3.org/1999/XSL/Transform.
    /// The @p name is not a valid name according to the W3C XML specification.
    /// The @p namespaceUri already has a parameter associated with it.
    ASPOSECPP_SHARED_API void AddParam(const String& name, const String& namespaceUri, const SharedPtr<Object>& parameter);
    /// Adds a new object to the XsltArgumentList and associates it with the namespace URI.
    /// @param namespaceUri The namespace URI to associate with the object. To use the default namespace, specify an empty string.
    /// @param extension The object to add to the list.
    /// @throws ArgumentException The @p namespaceUri is either @c nullptr or http://www.w3.org/1999/XSL/Transform
    /// The @p namespaceUri already has an extension object associated with it.
    /// @throws SecurityException The caller does not have sufficient permissions to call this method.
    ASPOSECPP_SHARED_API void AddExtensionObject(const String& namespaceUri, const SharedPtr<Object>& extension);
    /// Removes the parameter from the XsltArgumentList.
    /// @param name The name of the parameter to remove.
    /// XsltArgumentList does not check to ensure the name passed is a valid local name;
    /// however, the name cannot be @c nullptr.
    /// @param namespaceUri The namespace URI of the parameter to remove.
    /// @returns The parameter object or @c nullptr if one was not found.
    ASPOSECPP_SHARED_API SharedPtr<Object> RemoveParam(const String& name, const String& namespaceUri);
    /// Removes the object with the namespace URI from the XsltArgumentList.
    /// @param namespaceUri The namespace URI associated with the object to remove.
    /// @returns The object with the namespace URI or @c nullptr if one was not found.
    ASPOSECPP_SHARED_API SharedPtr<Object> RemoveExtensionObject(const String& namespaceUri);
    /// Removes all parameters and extension objects from the XsltArgumentList.
    ASPOSECPP_SHARED_API void Clear();

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
    const char* DBG_class_name() const override { return "XsltArgumentList"; }
#endif
    /// @endcond

private:

    SharedPtr<Collections::Generic::Dictionary<SharedPtr<XmlQualifiedName>, SharedPtr<Object>>> _parameters;
    SharedPtr<Collections::Generic::Dictionary<String, SharedPtr<Object>>> _extensions;

    static void CheckArgumentNull(const SharedPtr<Object>& param, const String& paramName);

};

} // namespace Xsl
} // namespace Xml
} // namespace System


