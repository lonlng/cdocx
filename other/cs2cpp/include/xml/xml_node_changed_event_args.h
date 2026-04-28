/// @file xml/xml_node_changed_event_args.h

#pragma once

#include <xml/xml_node_changed_action.h>
#include <system/string.h>
#include <system/eventargs.h>


/// @cond
namespace System
{
namespace Xml
{
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Provides data for the XmlDocument::NodeChanged, XmlDocument::NodeChanging, XmlDocument::NodeInserted,
/// XmlDocument::NodeInserting, XmlDocument::NodeRemoved and XmlDocument::NodeRemoving events.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlNodeChangedEventArgs : public EventArgs
{
    typedef XmlNodeChangedEventArgs ThisType;
    typedef EventArgs BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNodeChangedEventArgs>;

public:

    /// Returns a value indicating what type of node change event is occurring.
    /// @returns One of the enumeration values that describes the node change event.
    /// The @c Action value does not differentiate between when the event occurred (before or after).
    /// You can create separate event handlers to handle both instances.
    ASPOSECPP_SHARED_API XmlNodeChangedAction get_Action();
    /// Returns the XmlNode that is being added, removed or changed.
    /// @returns The XmlNode that is being added, removed or changed; this method never returns @c nullptr.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_Node();
    /// Returns the value of the XmlNode::get_ParentNode before the operation began.
    /// @returns The value of the @c ParentNode before the operation began.
    /// This method returns @c nullptr if the node did not have a parent.
    /// For attribute nodes, this method returns the XmlAttribute::get_OwnerElement value.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_OldParent();
    /// Returns the value of the XmlNode::get_ParentNode after the operation completes.
    /// @returns The value of the @c ParentNode after the operation completes.
    /// This method returns @c nullptr if the node is being removed.
    /// For attribute nodes, this method returns the XmlAttribute::get_OwnerElement value.
    ASPOSECPP_SHARED_API SharedPtr<XmlNode> get_NewParent();
    /// Returns the original value of the node.
    /// @returns The original value of the node.
    /// This method returns @c nullptr if the node is neither an attribute nor a text node, or if the node is being inserted.
    /// If called in a XmlDocument::NodeChanging event, @c get_OldValue returns the current value of the node that
    /// will be replaced if the change is successful.
    /// If called in a XmlDocument::NodeChanged event, @c get_OldValue returns the value of node prior to the change.
    ASPOSECPP_SHARED_API String get_OldValue();
    /// Returns the new value of the node.
    /// @returns The new value of the node.
    /// This method returns @c nullptr if the node is neither an attribute nor a text node, or if the node is being removed.
    /// If called in a XmlDocument::NodeChanging event, @c get_NewValue returns the value of the node if the change is successful.
    /// If called in a XmlDocument::NodeChanged event, @c get_NewValue returns the current value of the node.
    ASPOSECPP_SHARED_API String get_NewValue();

    /// Initializes a new instance of the XmlNodeChangedEventArgs class.
    /// @param node The XmlNode that generated the event.
    /// @param oldParent The old parent XmlNode of the XmlNode that generated the event.
    /// @param newParent The new parent XmlNode of the XmlNode that generated the event.
    /// @param oldValue The old value of the XmlNode that generated the event.
    /// @param newValue The new value of the XmlNode that generated the event.
    /// @param action The XmlNodeChangedAction.
    ASPOSECPP_SHARED_API XmlNodeChangedEventArgs(const SharedPtr<XmlNode>& node, const SharedPtr<XmlNode>& oldParent, const SharedPtr<XmlNode>& newParent, const String& oldValue, const String& newValue, XmlNodeChangedAction action);

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
    const char* DBG_class_name() const override { return "XmlNodeChangedEventArgs"; }
    #endif
    /// @endcond

private:

    XmlNodeChangedAction _action;
    SharedPtr<XmlNode> _node;
    SharedPtr<XmlNode> _oldParent;
    SharedPtr<XmlNode> _newParent;
    String _oldValue;
    String _newValue;

};

} // namespace Xml
} // namespace System


