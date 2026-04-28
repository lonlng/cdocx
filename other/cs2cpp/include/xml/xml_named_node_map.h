/// @file xml/xml_named_node_map.h

#pragma once

#include <system/object.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>


/// @cond
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class List;
} // namespace Generic
} // namespace Collections
class String;
namespace Xml
{
class DocumentXmlWriter;
class DocumentXPathNavigator;
class XmlAttributeCollection;
class XmlDocument;
class XmlDocumentType;
class XmlNode;
} // namespace Xml
} // namespace System
/// @endcond

namespace System {

namespace Xml {

/// Represents a collection of nodes that can be accessed by name or index.
/// @attention Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instances of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
class ASPOSECPP_SHARED_CLASS XmlNamedNodeMap : public Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>>
{
    typedef XmlNamedNodeMap ThisType;
    typedef Collections::Generic::IEnumerable<SharedPtr<System::Xml::XmlNode>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSECPP_SHARED_RTTI_INFO_DECL();

public:

    /// An alias for shared pointer to an instance of this class.
    using Ptr = SharedPtr<XmlNamedNodeMap>;

private:
    /// @cond
    friend class DocumentXmlWriter;
    friend class DocumentXPathNavigator;
    friend class XmlAttributeCollection;
    friend class XmlDocument;
    friend class XmlDocumentType;
    /// @endcond

protected:

    /// @cond
    class SmallXmlNodeList : public System::Object
    {
        typedef SmallXmlNodeList ThisType;
        typedef System::Object BaseType;

        typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
        RTTI_INFO_DECL();

    private:

        class SingleObjectEnumerator : public Collections::Generic::IEnumerator<SharedPtr<System::Xml::XmlNode>>
        {
            typedef SingleObjectEnumerator ThisType;
            typedef Collections::Generic::IEnumerator<SharedPtr<System::Xml::XmlNode>> BaseType;

            typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
            RTTI_INFO_DECL();

        public:

            const SharedPtr<XmlNode>& get_Current() const override;

            SingleObjectEnumerator(const SharedPtr<XmlNode>& value);

            bool MoveNext() override;
            void Reset() override;
            void Dispose() override;

            /// Clones current iterator.
            /// @return Copy of the current iterator.
            ASPOSECPP_SHARED_API System::Details::VirtualizedIteratorBase<SharedPtr<System::Xml::XmlNode>>* CloneIterator() const override;

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
            const char* DBG_class_name() const override { return "SingleObjectEnumerator"; }
        #endif


        private:

            SharedPtr<XmlNode> _loneValue;
            int32_t _position;
            mutable SharedPtr<XmlNode> m_CurrentHolder;

        };


    public:

        int32_t get_Count();

        SharedPtr<XmlNode> idx_get(int32_t index);

        void Add(const SharedPtr<XmlNode>& value);
        void RemoveAt(int32_t index);
        void Insert(int32_t index, const SharedPtr<XmlNode>& value);
        SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlNode>>> GetEnumerator();

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
        const char* DBG_class_name() const override { return "SingleObjectEnumerator"; }
        #endif


    private:

        SharedPtr<XmlNode> _field;
        SharedPtr<Collections::Generic::List<SharedPtr<XmlNode>>> _list;

    public:

        class ASPOSECPP_SHARED_CLASS Iterator : public Details::BaseIterator<std::forward_iterator_tag, const decltype(_field)>
        {
        public:
            ASPOSECPP_SHARED_API Iterator(pointer ptr);

            ASPOSECPP_SHARED_API Iterator& operator++();
            ASPOSECPP_SHARED_API Iterator operator++(int);

            ASPOSECPP_SHARED_API bool operator==(const Iterator& other) const;
            ASPOSECPP_SHARED_API bool operator!=(const Iterator& other) const;

            ASPOSECPP_SHARED_API reference operator*() const;

        private:
            pointer m_ptr;
        };

        Iterator begin() const noexcept;
        Iterator end() const noexcept;

        Iterator cbegin() const noexcept;
        Iterator cend() const noexcept;
    };
    /// @endcond

public:

    /// Returns the number of nodes in the XmlNamedNodeMap.
    /// @returns The number of nodes.
    virtual ASPOSECPP_SHARED_API int32_t get_Count();

    /// Retrieves an XmlNode specified by name.
    /// @param name The qualified name of the node to retrieve.
    /// It is matched against the XmlNode::get_Name value of the matching node.
    /// @returns An XmlNode with the specified name or @c nullptr if a matching node is not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> GetNamedItem(String name);
    /// Adds an XmlNode using its XmlNode::get_Name value.
    /// @param node An XmlNode to store in the XmlNamedNodeMap.
    /// If a node with that name is already present in the map, it is replaced by the new one.
    /// @returns If the @p node replaces an existing node with the same name, the old node is returned;
    /// otherwise, @c nullptr is returned.
    /// @throws ArgumentException The @p node was created from a different XmlDocument than the one that created the XmlNamedNodeMap;
    /// or the XmlNamedNodeMap is read-only.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> SetNamedItem(SharedPtr<XmlNode> node);
    /// Removes the node from the XmlNamedNodeMap.
    /// @param name The qualified name of the node to remove.
    /// The name is matched against the XmlNode::get_Name value of the matching node.
    /// @returns The XmlNode removed from this XmlNamedNodeMap or @c nullptr if a matching node was not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveNamedItem(String name);
    /// Retrieves the node at the specified index in the XmlNamedNodeMap.
    /// @param index The index position of the node to retrieve from the XmlNamedNodeMap.
    /// The index is zero-based; therefore, the index of the first node is 0 and
    /// the index of the last node is XmlNamedNodeMap::get_Count - 1.
    /// @returns The XmlNode at the specified index.
    /// If @p index is less than 0 or greater than or equal to the XmlNamedNodeMap::get_Count value, @c nullptr is returned.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> Item(int32_t index);
    /// Retrieves a node with the matching XmlNode::get_LocalName and XmlNode::get_NamespaceURI values.
    /// @param localName The local name of the node to retrieve.
    /// @param namespaceURI The namespace Uniform Resource Identifier (URI) of the node to retrieve.
    /// @returns An XmlNode with the matching local name and namespace URI or @c nullptr if a matching node was not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> GetNamedItem(String localName, String namespaceURI);
    /// Removes a node with the matching XmlNode::get_LocalName and XmlNode::get_NamespaceURI values.
    /// @param localName The local name of the node to remove.
    /// @param namespaceURI The namespace URI of the node to remove.
    /// @returns The XmlNode removed or @c nullptr if a matching node was not found.
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveNamedItem(String localName, String namespaceURI);
    /// Provides support for iteration over the collection of nodes in the XmlNamedNodeMap.
    /// @returns An enumerator object.
    ASPOSECPP_SHARED_API SharedPtr<Collections::Generic::IEnumerator<SharedPtr<XmlNode>>> GetEnumerator() override;

protected:

    /// @cond
    WeakPtr<XmlNode> parent;
    SharedPtr<XmlNamedNodeMap::SmallXmlNodeList> nodes;

    XmlNamedNodeMap(const SharedPtr<XmlNode>& parent);
    MEMBER_FUNCTION_MAKE_OBJECT_DECLARATION(XmlNamedNodeMap, CODEPORTING_ARGS(SharedPtr<XmlNode> parent));

    int32_t FindNodeOffset(const String& name);
    int32_t FindNodeOffset(const String& localName, const String& namespaceURI);
    virtual ASPOSECPP_SHARED_API const SharedPtr<XmlNode>& AddNode(const SharedPtr<XmlNode>& node);
    virtual ASPOSECPP_SHARED_API const SharedPtr<XmlNode>& AddNodeForLoad(const SharedPtr<XmlNode>& node, const SharedPtr<XmlDocument>& doc);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> RemoveNodeAt(int32_t i);
    SharedPtr<XmlNode> ReplaceNodeAt(int32_t i, const SharedPtr<XmlNode>& node);
    virtual ASPOSECPP_SHARED_API SharedPtr<XmlNode> InsertNodeAt(int32_t i, SharedPtr<XmlNode> node);
    /// @endcond

    virtual ASPOSECPP_SHARED_API ~XmlNamedNodeMap();

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
    const char* DBG_class_name() const override { return "XmlNamedNodeMap"; }
    #endif
    /// @endcond

public:
    /// Iterator type.
    using iterator = SmallXmlNodeList::Iterator;

    /// Gets iterator to the first element of collection.
    /// @return An iterator pointing to the first element in the collection.
    ASPOSECPP_SHARED_API iterator begin() const noexcept;
    /// Gets iterator for a non-existent element behind the last element of the collection.
    /// @return An iterator pointing to the element behind the last element of the collection.
    ASPOSECPP_SHARED_API iterator end() const noexcept;

    /// Gets iterator to the first element of collection.
    /// @return An iterator pointing to the first element in the collection.
    ASPOSECPP_SHARED_API iterator cbegin() const noexcept;
    /// Gets iterator for a non-existent element behind the last element of the collection.
    /// @return An iterator pointing to the element behind the last element of the collection.
    ASPOSECPP_SHARED_API iterator cend() const noexcept;

};

} // namespace Xml
} // namespace System


