/// @file xml/xml_url_resolver.h

#pragma once

#include <xml/xml_resolver.h>
#include <system/shared_ptr.h>


/// @cond
namespace System
{
namespace Net
{
namespace Cache
{
class RequestCachePolicy;
} // namespace Cache
class ICredentials;
class IWebProxy;
} // namespace Net
class String;
class TypeInfo;
class Uri;
namespace Xml
{
class XmlDownloadManager;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Resolves external XML resources named by a Uniform Resource Identifier (URI).
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlUrlResolver : public XmlResolver
{
    typedef XmlUrlResolver ThisType;
    typedef XmlResolver BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlUrlResolver>;

public:

    /// Sets credentials used to authenticate web requests.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Credentials(SharedPtr<Net::ICredentials> value) override;
    /// Sets the network proxy for the underlying WebRequest object.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Proxy(const SharedPtr<Net::IWebProxy>& value);
    /// Sets the cache policy for the underlying WebRequest object.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_CachePolicy(const SharedPtr<Net::Cache::RequestCachePolicy>& value);

    /// Initializes a new instance of the XmlUrlResolver class.
    ASPOSECPP_SHARED_API XmlUrlResolver();

    /// Maps a URI to an object that contains the actual resource.
    /// @param absoluteUri The URI returned from XmlResolver::ResolveUri(SharedPtr<Uri>, String) call.
    /// @param role Currently not used.
    /// @param ofObjectToReturn The type of object to return. The current implementation only returns Stream objects.
    /// @returns A stream object or @c nullptr if a type other than stream is specified.
    /// @throws XmlException @p ofObjectToReturn is neither @c nullptr nor a @c Stream type.
    /// @throws UriFormatException The specified URI is not an absolute URI.
    /// @throws ArgumentNullException @p absoluteUri is @c nullptr.
    /// @throws Exception There is a runtime error (for example, an interrupted server connection).
    ASPOSECPP_SHARED_API SharedPtr<Object> GetEntity(SharedPtr<Uri> absoluteUri, String role, const TypeInfo& ofObjectToReturn) override;
    /// Resolves the absolute URI from the base and relative URIs.
    /// @param baseUri The base URI used to resolve the relative URI.
    /// @param relativeUri The URI to resolve. The URI can be absolute or relative.
    /// If absolute, this value effectively replaces the @p baseUri value.
    /// If relative, it combines with the @p baseUri to make an absolute URI.
    /// @returns The absolute URI, or @c nullptr if the relative URI cannot be resolved.
    /// @throws ArgumentNullException @p baseUri is @c nullptr or @p relativeUri is @c nullptr.
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
    const char* DBG_class_name() const override { return "XmlUrlResolver"; }
    #endif
    /// @endcond

private:

    static SharedPtr<XmlDownloadManager> s_DownloadManager;
    SharedPtr<Net::ICredentials> _credentials;
    SharedPtr<Net::IWebProxy> _proxy;
    SharedPtr<Net::Cache::RequestCachePolicy> _cachePolicy;

    static SharedPtr<XmlDownloadManager> get_DownloadManager();

};

} // namespace Xml
} // namespace System


