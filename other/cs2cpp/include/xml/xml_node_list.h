/// @file xml/xml_node_list.h

#pragma once

#include <system/idisposable.h>
#include <system/collections/ienumerable.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
} // namespace Generic
} // namespace Collections
namespace Xml
{
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents an ordered collection of nodes.
class ASPOSECPP_SHARED_CLASS XmlNodeList : public Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>>, public IDisposable
{
    typedef XmlNodeList ThisType;
    typedef Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>> BaseType;
    typedef IDisposable BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNodeList>;

public:

    /// Returns the number of nodes in the XmlNodeList.
    /// @returns The number of nodes in the XmlNodeList.
    virtual ASPOSECPP_SHARED_API int32_t get_Count() = 0;

    /// Retrieves a node at the given index.
    /// @param index The zero-based index into the list of nodes.
    /// @returns The XmlNode with the specified index in the collection.
    /// If @p index is greater than or equal to the number of nodes in the list, this returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> Item(int32_t index) = 0;
    /// Provides support for iteration over the collection of nodes in the XmlNodeList.
    /// @returns An enumerator object.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlNode>>> GetEnumerator() override = 0;

    /// Returns a node at the given index.
    /// @param i The zero-based index into the list of nodes.
    /// @returns The XmlNode with the specified index in the collection.
    /// If index is greater than or equal to the number of nodes in the list, this returns @c nullptr.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> idx_get(int32_t i);

protected:

    /// Disposes resources in the node list privately.
    virtual ASPOSECPP_SHARED_API void PrivateDisposeNodeList();

    virtual ASPOSECPP_SHARED_API ~XmlNodeList();

private:

    ASPOSECPP_SHARED_API void Dispose() override;

};

} // namespace Xml
} // namespace System


