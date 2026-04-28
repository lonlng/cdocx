/// @file xml/serialization/xml_serializer_namespaces.h

#pragma once

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
template <typename> class List;
} // namespace Generic
} // namespace Collections
namespace Xml
{
namespace Serialization
{
class XmlSerializationWriter;
} // namespace Serialization
class XmlQualifiedName;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace Serialization {

/// Contains the XML namespaces and prefixes that the Serialization::XmlSerializer uses to generate qualified names in an XML-document instance.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlSerializerNamespaces : public System::Object
{
    typedef XmlSerializerNamespaces ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlSerializerNamespaces>;

private:
    /// @cond
    friend class XmlSerializationWriter;
    /// @endcond

public:

    /// Returns the number of prefix and namespace pairs in the collection.
    /// @returns The number of prefix and namespace pairs in the collection.
    ASPOSECPP_SHARED_API int32_t get_Count();
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::List<SharedPtr<XmlQualifiedName>>> get_NamespaceList();
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::Dictionary<String, String>> get_Namespaces();
    ASPOSECPP_SHARED_API void set_Namespaces(const SharedPtr<Collections::Generic::Dictionary<String, String>>& value);

    /// Initializes a new instance of the Serialization::XmlSerializerNamespaces class.
    ASPOSECPP_SHARED_API XmlSerializerNamespaces();
    /// Initializes a new instance of the Serialization::XmlSerializerNamespaces class, using the specified instance of @c XmlSerializerNamespaces containing the collection of prefix and namespace pairs.
    /// @param namespaces An instance of the Serialization::XmlSerializerNamespaces containing the namespace and prefix pairs.
    ASPOSECPP_SHARED_API XmlSerializerNamespaces(const SharedPtr<XmlSerializerNamespaces>& namespaces);
    /// Initializes a new instance of the Serialization::XmlSerializerNamespaces class.
    /// @param namespaces An array of XmlQualifiedName objects.
    ASPOSECPP_SHARED_API XmlSerializerNamespaces(const ArrayPtr<SharedPtr<XmlQualifiedName>>& namespaces);

    /// Adds a prefix and namespace pair to an Serialization::XmlSerializerNamespaces object.
    /// @param prefix The prefix associated with an XML namespace.
    /// @param ns An XML namespace.
    ASPOSECPP_SHARED_API void Add(const String& prefix, const String& ns);
    /// Returns the array of prefix and namespace pairs in an Serialization::XmlSerializerNamespaces object.
    /// @returns An array of XmlQualifiedName objects that are used as qualified names in an XML document.
    ASPOSECPP_SHARED_API ArrayPtr<SharedPtr<XmlQualifiedName>> ToArray();

protected:

    /// @cond
    void AddInternal(const String& prefix, const String& ns);
    String LookupPrefix(const String& ns);
    /// @endcond
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
    const char* DBG_class_name() const override { return "XmlSerializerNamespaces"; }
#endif


private:

    SharedPtr<Collections::Generic::Dictionary<String, String>> _namespaces;

};

} // namespace Serialization
} // namespace Xml
} // namespace System


