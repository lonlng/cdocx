/// @file xml/xml_resolver.h

#pragma once

#include <system/object.h>


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

/// Resolves external XML resources named by a Uniform Resource Identifier (URI).
class ASPOSECPP_SHARED_CLASS XmlResolver : public System::Object
{
    typedef XmlResolver ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlResolver>;

public:

    /// When overridden in a derived class, sets the credentials used to authenticate web requests.
    /// @param value The value to set.
    virtual ASPOSECPP_SHARED_API void set_Credentials(SharedPtr<Net::ICredentials> value);

    /// When overridden in a derived class, maps a URI to an object that contains the actual resource.
    /// @param absoluteUri The URI returned from XmlResolver::ResolveUri(SharedPtr<Uri>, String) call.
    /// @param role Currently not used.
    /// @param ofObjectToReturn The type of object to return. The current version only returns Stream objects.
    /// @returns A stream object or @c nullptr if a type other than stream is specified.
    /// @throws XmlException @p ofObjectToReturn is not a @c Stream type.
    /// @throws UriFormatException The specified URI is not an absolute URI.
    /// @throws ArgumentNullException @p absoluteUri is @c nullptr.
    /// @throws Exception There is a runtime error (for example, an interrupted server connection).
    virtual ASPOSECPP_SHARED_API SharedPtr<Object> GetEntity(SharedPtr<Uri> absoluteUri, String role, const TypeInfo& ofObjectToReturn) = 0;
    /// When overridden in a derived class, resolves the absolute URI from the base and relative URIs.
    /// @param baseUri The base URI used to resolve the relative URI.
    /// @param relativeUri The URI to resolve. The URI can be absolute or relative.
    /// If absolute, this value effectively replaces the @p baseUri value.
    /// If relative, it combines with the @p baseUri to make an absolute URI.
    /// @returns The absolute URI or @c nullptr if the relative URI cannot be resolved.
    /// @throws ArgumentException @p relativeUri is @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<Uri> ResolveUri(SharedPtr<Uri> baseUri, String relativeUri);
    /// Enables the resolver to return types other than Stream.
    /// @param absoluteUri The URI.
    /// @param type The type to return.
    /// @returns @c true if the @p type is supported; otherwise, @c false.
    virtual ASPOSECPP_SHARED_API bool SupportsType(SharedPtr<Uri> absoluteUri, const TypeInfo& type);

};

} // namespace Xml
} // namespace System


