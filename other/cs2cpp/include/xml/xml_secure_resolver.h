/// @file xml/xml_secure_resolver.h

#pragma once

#include <xml/xml_resolver.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Net
{
class ICredentials;
} // namespace Net
class String;
class TypeInfo;
class Uri;
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Helps to secure another implementation of XmlResolver by wrapping the XmlResolver object and
/// restricting the resources that the underlying XmlResolver has access to.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSecureResolver : public XmlResolver
{
    typedef XmlSecureResolver ThisType;
    typedef XmlResolver BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSecureResolver>;

public:

    /// Sets credentials used to authenticate web requests.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Credentials(SharedPtr<Net::ICredentials> value) override;

    /// Initializes a new instance of the XmlSecureResolver class with the XmlResolver and URL provided.
    /// @param resolver The XML resolver that is wrapped by the XmlSecureResolver.
    /// @param securityUrl Currently not used.
    ASPOSECPP_SHARED_API XmlSecureResolver(const SharedPtr<XmlResolver>& resolver, const String& securityUrl);

    /// Maps a URI to an object that contains the actual resource.
    /// @param absoluteUri The URI that is returned from XmlSecureResolver::ResolveUri(SharedPtr<Uri>, String) call.
    /// @param role Currently not used.
    /// @param ofObjectToReturn The type of object to return. The current version only returns Stream objects.
    /// @returns The stream returned by calling @c GetEntity on the underlying XmlResolver.
    /// If a type other than Stream is specified, the method returns @c nullptr.
    /// @throws XmlException @p ofObjectToReturn is neither @c nullptr nor a Stream type.
    /// @throws UriFormatException The specified URI is not an absolute URI.
    /// @throws NullReferenceException @p absoluteUri is @c nullptr.
    /// @throws Exception There is a runtime error (for example, an interrupted server connection).
    ASPOSECPP_SHARED_API SharedPtr<Object> GetEntity(SharedPtr<Uri> absoluteUri, String role, const TypeInfo& ofObjectToReturn) override;
    /// Resolves the absolute URI from the base and relative URIs by calling @c ResolveUri on the underlying XmlResolver.
    /// @param baseUri The base URI used to resolve the relative URI.
    /// @param relativeUri The URI to resolve. The URI can be absolute or relative.
    /// If absolute, this value effectively replaces the @p baseUri value.
    /// If relative, it combines with the @p baseUri to make an absolute URI.
    /// @returns The absolute URI or @c nullptr if the relative URI cannot be resolved
    /// (returned by calling @c ResolveUri on the underlying XmlResolver).
    /// @throws ArgumentException @p relativeUri is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Uri> ResolveUri(SharedPtr<Uri> baseUri, String relativeUri) override;

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
    const char* DBG_class_name() const override { return "XmlSecureResolver"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlResolver> _resolver;

};

} // namespace Xml
} // namespace System


