/// @file xml/resolvers/xml_preloaded_resolver.h

#pragma once

#include <xml/xml_resolver.h>
#include <xml/resolvers/xml_known_dtds.h>
#include <system/enum_helpers.h>
#include <system/array.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename, typename> class Dictionary;
template <typename> class IEnumerable;
template <typename> class IEqualityComparer;
} // namespace Generic
} // namespace Collections
namespace IO
{
class Stream;
class TextReader;
} // namespace IO
namespace Net
{
class ICredentials;
} // namespace Net
class TypeInfo;
class Uri;
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Resolvers {

/// Represents a class that is used to prepopulate the cache with DTDs or XML streams.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlPreloadedResolver : public XmlResolver
{
    typedef XmlPreloadedResolver ThisType;
    typedef XmlResolver BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlPreloadedResolver>;

private:

    class PreloadedData : public System::Object
    {
        typedef PreloadedData ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        virtual SharedPtr<IO::Stream> AsStream() = 0;
        virtual SharedPtr<IO::TextReader> AsTextReader();
        virtual bool SupportsType(const TypeInfo& type);
        /// @endcond

    };

    class XmlKnownDtdData : public XmlPreloadedResolver::PreloadedData
    {
        typedef XmlKnownDtdData ThisType;
        typedef XmlPreloadedResolver::PreloadedData BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        String publicId;
        String systemId;

        XmlKnownDtdData(const String& publicId, const String& systemId, const String& resourceName);

        SharedPtr<IO::Stream> AsStream() override;
        /// @endcond

    private:

        String _resourceName;

    };

    class ByteArrayChunk : public XmlPreloadedResolver::PreloadedData
    {
        typedef ByteArrayChunk ThisType;
        typedef XmlPreloadedResolver::PreloadedData BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        ByteArrayChunk(const ArrayPtr<uint8_t>& array);
        ByteArrayChunk(const ArrayPtr<uint8_t>& array, int32_t offset, int32_t length);

        SharedPtr<IO::Stream> AsStream() override;
        /// @endcond

    protected:

        #ifdef ASPOSE_GET_SHARED_MEMBERS
        void GetSharedMembers(System::Object::shared_members_type& result) const override;
        #endif

        #ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to members.
        /// @param visitor Visitor to apply.
        ASPOSECPP_SHARED_API void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override;
        /// Gets class name.
        /// @return String literal pointer.
        const char* DBG_class_name() const override { return "ByteArrayChunk"; }
#endif


    private:

        ArrayPtr<uint8_t> _array;
        int32_t _offset;
        int32_t _length;

    };

    class StringData : public XmlPreloadedResolver::PreloadedData
    {
        typedef StringData ThisType;
        typedef XmlPreloadedResolver::PreloadedData BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        /// @cond
        StringData(const String& str);

        SharedPtr<IO::Stream> AsStream() override;
        SharedPtr<IO::TextReader> AsTextReader() override;
        bool SupportsType(const TypeInfo& type) override;
        /// @endcond

    private:

        String _str;

    };


public:

    /// Sets the credentials that are used to authenticate the underlying Net::WebRequest.
    /// @param value The value to set.
    ASPOSECPP_SHARED_API void set_Credentials(SharedPtr<Net::ICredentials> value) override;
    /// Returns a collection of preloaded URIs.
    /// @returns The collection of preloaded URIs.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerable<SharedPtr<Uri>>> get_PreloadedUris();

    /// Initializes a new instance of the XmlPreloadedResolver class.
    ASPOSECPP_SHARED_API XmlPreloadedResolver();
    /// Initializes a new instance of the XmlPreloadedResolver class with the specified preloaded well-known DTDs.
    /// @param preloadedDtds The well-known DTDs that should be prepopulated into the cache.
    ASPOSECPP_SHARED_API XmlPreloadedResolver(XmlKnownDtds preloadedDtds);
    /// Initializes a new instance of the XmlPreloadedResolver class with the specified fallback resolver.
    /// @param fallbackResolver The XmlResolver or your own resolver.
    ASPOSECPP_SHARED_API XmlPreloadedResolver(const SharedPtr<XmlResolver>& fallbackResolver);
    /// Initializes a new instance of the XmlPreloadedResolver class with the specified fallback resolver and preloaded well-known DTDs.
    /// @param fallbackResolver The XmlResolver or your own resolver.
    /// @param preloadedDtds The well-known DTDs that should be prepopulated into the cache.
    ASPOSECPP_SHARED_API XmlPreloadedResolver(const SharedPtr<XmlResolver>& fallbackResolver, XmlKnownDtds preloadedDtds);
    /// Initializes a new instance of the XmlPreloadedResolver class with the specified fallback resolver,
    /// preloaded well-known DTDs, and URI equality comparer.
    /// @param fallbackResolver The XmlResolver or your own resolver.
    /// @param preloadedDtds The well-known DTDs that should be prepopulated into cache.
    /// @param uriComparer The implementation of the IEqualityComparer interface to use when you compare URIs.
    ASPOSECPP_SHARED_API XmlPreloadedResolver(const SharedPtr<XmlResolver>& fallbackResolver, XmlKnownDtds preloadedDtds, const SharedPtr<Collections::Generic::IEqualityComparer<SharedPtr<Uri>>>& uriComparer);

    /// Resolves the absolute URI from the base and relative URIs.
    /// @param baseUri The base URI used to resolve the relative URI.
    /// @param relativeUri The URI to resolve. The URI can be absolute or relative.
    /// If absolute, this value effectively replaces the @p baseUri value.
    /// If relative, it combines with the @p baseUri to make an absolute URI.
    /// @returns The Uri representing the absolute URI or @c nullptr if the relative URI cannot be resolved.
    /// @throws ArgumentNullException @p uri is @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<Uri> ResolveUri(SharedPtr<Uri> baseUri, String relativeUri) override;
    /// Maps a URI to an object that contains the actual resource.
    /// @param absoluteUri The URI returned from XmlResolver::ResolveUri(SharedPtr<Uri>,String) call.
    /// @param role Currently not used.
    /// @param ofObjectToReturn The type of object to return.
    /// The XmlPreloadedResolver supports Stream objects and TextReader objects for URIs that were added as String.
    /// If the requested type is not supported by the resolver, an exception will be thrown.
    /// Use the XmlPreloadedResolver::SupportsType(SharedPtr<Uri>,TypeInfo) method to determine whether a certain @c Type is supported by this resolver.
    /// @returns A Stream or TextReader object that corresponds to the actual source.
    /// @throws ArgumentNullException @p absoluteUri is @c nullptr.
    /// @throws XmlException Cannot resolve URI passed in @p absoluteUri.
    /// or
    /// @p ofObjectToReturn is not of a supported type.
    ASPOSECPP_SHARED_API SharedPtr<Object> GetEntity(SharedPtr<Uri> absoluteUri, String role, const TypeInfo& ofObjectToReturn) override;
    /// Determines whether the resolver supports other Types than just Stream.
    /// @param absoluteUri The absolute URI to check.
    /// @param type The Type to return.
    /// @returns @c true if the Type is supported; otherwise, @c false.
    /// @throws ArgumentNullException @p uri is @c nullptr.
    ASPOSECPP_SHARED_API bool SupportsType(SharedPtr<Uri> absoluteUri, const TypeInfo& type) override;
    /// Adds a byte array to the XmlPreloadedResolver store and maps it to a URI.
    /// If the store already contains a mapping for the same URI, the existing mapping is overridden.
    /// @param uri The URI of the data that is being added to the XmlPreloadedResolver store.
    /// @param value A byte array with the data that corresponds to the provided URI.
    /// @throws ArgumentNullException @p uri or @p value is @c nullptr.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<Uri>& uri, const ArrayPtr<uint8_t>& value);
    /// Adds a byte array to the XmlPreloadedResolver store and maps it to a URI.
    /// If the store already contains a mapping for the same URI, the existing mapping is overridden.
    /// @param uri The URI of the data that is being added to the XmlPreloadedResolver store.
    /// @param value A byte array with the data that corresponds to the provided URI.
    /// @param offset The offset in the provided byte array where the data starts.
    /// @param count The number of bytes to read from the byte array, starting at the provided offset.
    /// @throws ArgumentNullException @p uri or @p value is @c nullptr.
    /// @throws ArgumentOutOfRangeException @p offset or @p count is less than 0.
    /// or
    /// The length of the @p value minus @p offset is less than @p count.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<Uri>& uri, const ArrayPtr<uint8_t>& value, int32_t offset, int32_t count);
    /// Adds a Stream to the XmlPreloadedResolver store and maps it to a URI.
    /// If the store already contains a mapping for the same URI, the existing mapping is overridden.
    /// @param uri The URI of the data that is being added to the XmlPreloadedResolver store.
    /// @param value A Stream with the data that corresponds to the provided URI.
    /// @throws ArgumentNullException @p uri or @p value is @c nullptr.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<Uri>& uri, const SharedPtr<IO::Stream>& value);
    /// Adds a string with preloaded data to the XmlPreloadedResolver store and maps it to a URI.
    /// If the store already contains a mapping for the same URI, the existing mapping is overridden.
    /// @param uri The URI of the data that is being added to the XmlPreloadedResolver store.
    /// @param value A String with the data that corresponds to the provided URI.
    /// @throws ArgumentNullException @p uri or @p value is @c nullptr.
    ASPOSECPP_SHARED_API void Add(const SharedPtr<Uri>& uri, const String& value);
    /// Removes the data that corresponds to the URI from the XmlPreloadedResolver.
    /// @param uri The URI of the data that should be removed from the XmlPreloadedResolver store.
    /// @throws ArgumentNullException @p uri is @c nullptr.
    ASPOSECPP_SHARED_API void Remove(const SharedPtr<Uri>& uri);

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
    const char* DBG_class_name() const override { return "XmlPreloadedResolver"; }
    #endif
    /// @endcond

private:

    SharedPtr<XmlResolver> _fallbackResolver;
    SharedPtr<Collections::Generic::Dictionary<SharedPtr<Uri>, SharedPtr<XmlPreloadedResolver::PreloadedData>>> _mappings;
    XmlKnownDtds _preloadedDtds;
    static ArrayPtr<SharedPtr<XmlPreloadedResolver::XmlKnownDtdData>> s_xhtml10_Dtd;
    static ArrayPtr<SharedPtr<XmlPreloadedResolver::XmlKnownDtdData>> s_rss091_Dtd;

    void Add(const SharedPtr<Uri>& uri, const SharedPtr<XmlPreloadedResolver::PreloadedData>& data);
    void AddKnownDtd(const ArrayPtr<SharedPtr<XmlPreloadedResolver::XmlKnownDtdData>>& dtdSet);

    static struct __StaticConstructor__ { __StaticConstructor__(); } s_constructor__;

};

} // namespace Resolvers
} // namespace Xml
} // namespace System


