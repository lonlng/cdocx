/// @file xml/xpath/xpath_node_iterator.h

#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Internal
{
namespace Xml
{
namespace XPath
{
class CacheAxisQuery;
class CacheOutputQuery;
class ContextQuery;
class ResetableIterator;
} // namespace XPath
} // namespace Xml
} // namespace Internal
namespace Xml
{
namespace XPath
{
class XPathNavigator;
} // namespace XPath
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

namespace XPath {

/// Provides an iterator over a selected set of nodes.
class ASPOSECPP_SHARED_CLASS XPathNodeIterator : public Collections::Generic::IEnumerable<SharedPtr<System::Xml::XPath::XPathNavigator>>
{
    typedef XPathNodeIterator ThisType;
    typedef Collections::Generic::IEnumerable<SharedPtr<System::Xml::XPath::XPathNavigator>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XPathNodeIterator>;

private:
    /// @cond
    friend class Internal::Xml::XPath::ContextQuery;
    friend class Internal::Xml::XPath::CacheAxisQuery;
    friend class Internal::Xml::XPath::CacheOutputQuery;
    friend class Internal::Xml::XPath::ResetableIterator;
    /// @endcond

private:

    class Enumerator : public Collections::Generic::IEnumerator<SharedPtr<System::Xml::XPath::XPathNavigator>>
    {
        typedef Enumerator ThisType;
        typedef Collections::Generic::IEnumerator<SharedPtr<System::Xml::XPath::XPathNavigator>> BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    public:

        const SharedPtr<XPathNavigator>& get_Current() const override;

        Enumerator(const SharedPtr<XPathNodeIterator>& original);

        void Dispose() override;
        bool MoveNext() override;
        void Reset() override;

        /// Clones current iterator.
        /// @return Copy of the current iterator.
        ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<System::Xml::XPath::XPathNavigator>>* CloneIterator() const override;

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
        const char* DBG_class_name() const override { return "Pen"; }
    #endif


    private:

        SharedPtr<XPathNodeIterator> _original;
        SharedPtr<XPathNodeIterator> _current;
        bool _iterationStarted;
        mutable SharedPtr<XPathNavigator> m_CurrentHolder;

    };


public:

    /// When overridden in a derived class, gets the XPathNavigator object for this XPathNodeIterator,
    /// positioned on the current context node.
    /// @returns An XPathNavigator object positioned on the context node from which the node set was selected.
    /// The XPathNodeIterator::MoveNext method must be called to move the XPathNodeIterator to the first node in the selected set.
    virtual ASPOSECPP_SHARED_API const SharedPtr<XPathNavigator>& get_Current() = 0;
    /// When overridden in a derived class, gets the index of the current position in the selected set of nodes.
    /// @returns The index of the current position.
    virtual ASPOSECPP_SHARED_API int32_t get_CurrentPosition() = 0;
    /// Returns the index of the last node in the selected set of nodes.
    /// @returns The index of the last node in the selected set of nodes, or 0 if there are no selected nodes.
    virtual ASPOSECPP_SHARED_API int32_t get_Count();

    /// When overridden in a derived class, returns a clone of this XPathNodeIterator object.
    /// @returns A new XPathNodeIterator object clone of this XPathNodeIterator object.
    virtual ASPOSECPP_SHARED_API SharedPtr<XPathNodeIterator> Clone() = 0;
    /// When overridden in a derived class, moves the XPathNavigator object returned by
    /// the XPathNodeIterator::get_Current method to the next node in the selected node set.
    /// @returns @c true if the XPathNavigator object moved to the next node; @c false if there are no more selected nodes.
    virtual ASPOSECPP_SHARED_API bool MoveNext() = 0;
    /// Returns an IEnumerator object to iterate through the selected node set.
    /// @returns An IEnumerator object to iterate through the selected node set.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XPathNavigator>>> GetEnumerator() override;

    /// Initializes a new instance of the XPathNodeIterator class.
    ASPOSECPP_SHARED_API XPathNodeIterator();

protected:

    /// @cond
    int32_t count;
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XPathNodeIterator();

};

} // namespace XPath
} // namespace Xml
} // namespace System


