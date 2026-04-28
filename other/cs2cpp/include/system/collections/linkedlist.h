/// @file system/collections/linkedlist.h
#pragma once

#include <system/object.h>
#include <system/string.h>
#include <system/type_info.h>
#include <system/shared_ptr.h>
#include <system/exceptions.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <system/collections/icollection.h>
#include <system/collections/invalidatable.h>
#include <system/array.h>

#include <system/diagnostics/debug.h>
#include <list>
#include <unordered_map>

#include <type_traits>

namespace System { namespace Collections { namespace Generic {

/// LinkedList forward declaration.
template <typename T>
class LinkedList;

/// Node of linked list. Implements a wrapper over an iterator of std::list that is wrapped in linked list.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
/// @tparam T Stored value type.
template <typename T>
class ASPOSECPP_SHARED_CLASS LinkedListNode final : public Object
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(LinkedListNode<T>, System::BaseTypesInfo<System::Object>)
    /// Access for owning list.
    friend class LinkedList<T>;
    /// Using of iterator of std::list with custom allocator.
    typedef typename LinkedList<T>::iterator iterator;

    /// Constructor.
    /// @param list Containing list.
    /// @param it Iterator on the containing list to be wrapped.
    LinkedListNode(const SharedPtr<LinkedList<T>>& list, const iterator& it) : m_value(*it)
    {
        Bind(list, it);
    }
    MEMBER_FUNCTION_MAKE_OBJECT(LinkedListNode, CODEPORTING_ARGS(const SharedPtr<LinkedList<T>>& list, const iterator& it), CODEPORTING_ARGS(list, it));

    /// Binds LinkedList and LinkedListNode to each other.
    /// @param list Bindable list
    /// @param it Bindable list data iterator
    void Bind(const SharedPtr<LinkedList<T>>& list, const iterator& it)
    {
        list->m_ptr_node_map[&*it] = this;
        m_list = list;
        m_it = it;
    }

    /// Unbinds LinkedList and LinkedListNode from each other.
    void Unbind()
    {
        if (m_list != nullptr)
        {
            m_list->m_ptr_node_map.erase(&*m_it);
            m_list = nullptr;
            m_it = iterator();
        }
    }

    /// Unbinds LinkedList from LinkedListNode.
    void UnbindNode()
    {
        if (m_list != nullptr)
        {
            m_list = nullptr;
            m_it = iterator();
        }
    }

    /// Gets a copy of the binded list data iterator.
    iterator CopyIterator() const
    {
        return m_it;
    }

public:
    /// Constructor.
    /// @param value Contaied value.
    LinkedListNode(const T &value) : m_value(value)
    {}

    /// Gets containing list.
    /// @return Pointer to containing list (if any) or null.
    SharedPtr<LinkedList<T>> get_List() const
    {
        return m_list;
    }

    /// Gets next node.
    /// @return Pointer to next node (if any) or null.
    SharedPtr<LinkedListNode<T>> get_Next() const
    {
        if (m_list != nullptr)
        {
            auto next_it = ++CopyIterator();
            if (next_it == m_list->m_data.end())
                return nullptr;

            return m_list->MakeSharedLinkedListNode(next_it);
        }
        else
            return nullptr;
    }

    /// Gets previous node.
    /// @return Pointer to previous node (if any) or null.
    SharedPtr<LinkedListNode<T>> get_Previous() const
    {
        if (m_list != nullptr && m_it != m_list->m_data.begin())
            return m_list->MakeSharedLinkedListNode(--CopyIterator());
        else
            return nullptr;
    }

    /// Gets stored value.
    /// @return Stored value.
    T get_Value() const
    {
        return m_value;
    }

    /// Sets stored value.
    /// @param value Value to store.
    void set_Value(const T &value)
    {
        m_value = value;
        if (m_list != nullptr)
        {
            *m_it = value;
        }
    }

protected:
    /// Destructor.
    ~LinkedListNode() override
    {
        if (m_list != nullptr)
        {
            m_list->m_ptr_node_map.erase(&*m_it);
        }
    }

#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Implements loop references detection mechanics for LinkedListNode<T> type.
    /// @return Data structure holding information on shared pointers owned by LinkedListNode<T>.
    void GetSharedMembers(System::Object::shared_members_type& result) const override
    {
        System::Object::GetSharedMembers(result);

        result.Add("System::Collections::Generic::LinkedListNode::m_list", this->m_list);
    }
#endif

    
#ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to collection and its elements.
        /// @param visitor Visitor to apply.
        void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
        {
            Object::DBG_for_each_member(visitor);

            visitor.add_self(this);
            visitor.add_member(this, m_list, "m_list");
        }

        /// Gets class name.
        /// @return Current class name.
        const char* DBG_class_name() const override { return "LinkedListNode<T>"; }
#endif

private:
    /// Value.
    T m_value;
    /// Containing list.
    SharedPtr<LinkedList<T>> m_list;
    /// Iterator on the containing list that is wrapped.
    iterator m_it;
};

/// Linked list container. Implements a wrapper over std::list.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or
/// assertion faults. Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions
/// as argument.
/// @code
/// #include <system/collections/linkedlist.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create an instance of the LinkedList class.
///   auto list = MakeObject<LinkedList<int>>();
///
///   // Fill the linked list.
///   list->AddFirst(1);
///   list->AddLast(30);
///   list->AddAfter(list->get_First(), 15);
///   list->AddBefore(list->get_Last(), 25);
///
///   // Print the linked list items.
///   for (const auto item: list)
///   {
///     std::cout << item << ' ';
///   }
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1 15 25 30
/// */
/// @endcode
/// @tparam T Contained value type.
template <typename T>
class ASPOSECPP_SHARED_CLASS LinkedList : virtual public Object, public ICollection<T>, private Invalidatable
{
    /// Base types.
    typedef BaseTypesInfo<Object, ICollection<T>> ThisTypeBaseTypesInfo;
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(LinkedList<T>, ThisTypeBaseTypesInfo);
    /// Access for owned nodes.
    friend class LinkedListNode<T>;
    
    using Invalidatable::Invalidate;

    ASPOSE_COLLECTION_POINTER_MODE_CONTROL(T)

public:
    /// Underlying data type.
    typedef std::list<T, typename pointer_mode_t::allocator_type> list_t;
    
    /// Iterator type.
    typedef typename list_t::iterator iterator;
    /// Const iterator type.
    typedef typename list_t::const_iterator const_iterator;
    /// Reverse iterator type.
    typedef typename list_t::reverse_iterator reverse_iterator;
    /// Const reverse iterator type.
    typedef typename list_t::const_reverse_iterator const_reverse_iterator;

    /// Enumerator to iterate through linked list.
    class Enumerator : virtual public Object, public IEnumerator<T>
    {
        /// Base types.
        typedef BaseTypesInfo<Object, IEnumerator<T>> ThisTypeBaseTypesInfo;
        /// RTTI information.
        RTTI_INFO_TEMPLATE_CLASS(LinkedList<T>, ThisTypeBaseTypesInfo);
        /// Using of iterator of list with custom allocator.
        typedef typename LinkedList<T>::iterator iterator;

        /// Current iterator.
        iterator m_current;
        /// IEnumerable list.
        SharedPtr<LinkedList<T>> m_list;
        /// Optimization flag that distinguish the first call of the MoveNext function from the rest.
        bool m_was_first_move;
        /// Optimization flag, which determines that enumerator has not yet reached the end of the list.
        bool m_was_not_reached_end;
        /// Tracker of lists state.
        InvalidatableTracker m_tracker;

    public:
        /// Creates enumerator.
        /// @param list List to iterate through.
        Enumerator(const SharedPtr<LinkedList<T>>& list) : m_list(list)
            , m_was_first_move(false)
            , m_was_not_reached_end(true), m_tracker(list.get())
        {}

        /// Gets current element.
        /// @return Element enumerator points to.
        MakeConstRef_t<T> get_Current() const override
        {
            return *m_current;
        }

        /// Points enumerator to the next element (if any).
        /// @return True if next element was selected successfully, otherwise false.
        bool MoveNext() override
        {
            if (!m_tracker.CheckValidity())
                throw InvalidOperationException(u"Collection was modified after the enumerator was instantiated.");
            else if (!m_was_first_move)
            {
                m_was_first_move = true;

                if ((m_current = m_list->begin()) != m_list->end())
                    return true;
                else
                {
                    m_was_not_reached_end = false;
                    return false;
                }
            }
            else if (m_was_not_reached_end)
            {
                if (++m_current != m_list->end())
                    return true;
                else
                {
                    m_was_not_reached_end = false;
                    return false;
                }
            }
            else
                return false;
        }

    protected:
        /// Destructor.
        ~Enumerator() override
        {}

#ifdef ASPOSE_GET_SHARED_MEMBERS
        /// Implements loop references detection mechanics for LinkedList<T>::Enumerator type.
        /// @return Data structure holding information on shared pointers owned by LinkedList<T>::Enumerator.
        void GetSharedMembers(System::Object::shared_members_type& result) const override
        {
            System::Object::GetSharedMembers(result);

            result.Add("System::Collections::Generic::LinkedList::Enumerator::m_list", this->m_list);
        }
#endif

#ifdef __DBG_FOR_EACH_MEMBER
    public:
        /// Applies visitor to collection and its elements.
        /// @param visitor Visitor to apply.
        void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
        {
            Object::DBG_for_each_member(visitor);

            visitor.add_self(this);
            visitor.add_member(this, m_list, "m_list");
        }

        /// Gets class name.
        /// @return Current class name.
        const char* DBG_class_name() const override { return "LinkedList::Enumerator<T>"; }
#endif
    };

    /// Creates empty LinkedList.
    LinkedList() : ASPOSE_COLLECTION_INIT_ALLOCATOR(){}

    /// Copy constructor.
    /// @param collection Collection to copy data from.
    LinkedList(const SharedPtr<IEnumerable<T>>& collection) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        if (collection == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: collection");

        for (auto enumerator = collection->GetEnumerator(); enumerator->MoveNext();)
        {
            m_data.emplace_back(enumerator->get_Current());
        }
    }

    /// Gets pointer to the first element in the list.
    /// @return First element in the list.
    SharedPtr<LinkedListNode<T>> get_First() const
    {
        if (m_data.empty())
            return nullptr;
        else
            return MakeSharedLinkedListNode(m_data.begin());
    }

    /// Gets pointer to the last element in the list.
    /// @return Last element in the list.
    SharedPtr<LinkedListNode<T>> get_Last() const
    {
        if (m_data.empty())
            return nullptr;
        else
            return MakeSharedLinkedListNode(--m_data.end());
    }

    /// Gets number of elements in list.
    /// @return Actual number of elements in list.
    int get_Count() const override
    {
        return ASPOSECPP_CHECKED_CAST(int, m_data.size());
    }

    /// Adds @p element after @p node of the list.
    /// @param node Node after which to insert
    /// @param element Element to add
    /// @return New node.
    SharedPtr<LinkedListNode<T>> AddAfter(const SharedPtr<LinkedListNode<T>>& node, const T& element)
    {
        if (node == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: node");

        if (node->get_List().get() != this)
            throw InvalidOperationException(u"The LinkedList node does not belong to current LinkedList.");

        Invalidate();

        auto it = m_data.emplace(++node->CopyIterator(), element);
        return LinkedListNode<T>::MakeObject(MakeSharedPtr(this), it);
    }

    /// Adds @p newNode after @p node of the list.
    /// @param node Node after which to insert
    /// @param newNode New node to add
    void AddAfter(const SharedPtr<LinkedListNode<T>>& node, const SharedPtr<LinkedListNode<T>>& newNode)
    {
        if (node == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: node");

        if (newNode == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: newNode");
        
        if (node->m_list.get() != this)
            throw InvalidOperationException(u"The LinkedList node does not belong to current LinkedList.");

        if (newNode->m_list != nullptr)
            throw InvalidOperationException(u"The LinkedList node already belongs to a LinkedList.");

        Invalidate();

        auto it = m_data.emplace(++node->CopyIterator(), newNode->m_value);
        newNode->Bind(MakeSharedPtr(this), it);
    }

    /// Adds @p element before @p node of the list.
    /// @param node Node before which to insert
    /// @param element Element to add
    /// @return New node.
    SharedPtr<LinkedListNode<T>> AddBefore(const SharedPtr<LinkedListNode<T>>& node, const T& element)
    {
        if (node == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: node");

        if (node->get_List().get() != this)
            throw InvalidOperationException(u"The LinkedList node does not belong to current LinkedList.");

        Invalidate();

        auto it = m_data.emplace(node->m_it, element);
        return LinkedListNode<T>::MakeObject(MakeSharedPtr(this), it);
    }

    /// Adds @p newNode before @p node of the list.
    /// @param node Node before which to insert
    /// @param newNode New node to add
    void AddBefore(const SharedPtr<LinkedListNode<T>>& node, const SharedPtr<LinkedListNode<T>>& newNode)
    {
        if (node == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: node");

        if (newNode == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: newNode");

        if (node->m_list.get() != this)
            throw InvalidOperationException(u"The LinkedList node does not belong to current LinkedList.");

        if (newNode->m_list != nullptr)
            throw InvalidOperationException(u"The LinkedList node already belongs to a LinkedList.");

        Invalidate();

        auto it = m_data.emplace(node->m_it, newNode->m_value);
        newNode->Bind(MakeSharedPtr(this), it);
    }

    /// Adds @p element to the beginning of the list.
    /// @param element Element to add.
    /// @return New node.
    SharedPtr<LinkedListNode<T>> AddFirst(const T& element)
    {
        Invalidate();

        auto it = m_data.emplace(m_data.begin(), element);
        return LinkedListNode<T>::MakeObject(MakeSharedPtr(this), it);
    }

    /// Adds @p newNode to the beginning of the list.
    /// @param newNode New node to add.
    void AddFirst(const SharedPtr<LinkedListNode<T>>& newNode)
    {
        if (newNode == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: newNode");

        if (newNode->m_list != nullptr)
            throw InvalidOperationException(u"The LinkedList node already belongs to a LinkedList.");

        Invalidate();

        auto it = m_data.emplace(m_data.begin(), newNode->m_value);
        newNode->Bind(MakeSharedPtr(this), it);
    }

    /// Adds @p element to the end of the list.
    /// @param element Element to add.
    /// @return New node.
    SharedPtr<LinkedListNode<T>> AddLast(const T& element)
    {
        Invalidate();

        auto it = m_data.emplace(m_data.end(), element);
        return LinkedListNode<T>::MakeObject(MakeSharedPtr(this), it);
    }

    /// Adds @p newNode to the end of the list.
    /// @param newNode New node to add.
    void AddLast(const SharedPtr<LinkedListNode<T>>& newNode)
    {
        if (newNode == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: newNode");

        if (newNode->m_list != nullptr)
            throw InvalidOperationException(u"The LinkedList node already belongs to a LinkedList.");

        Invalidate();

        auto it = m_data.emplace(m_data.end(), newNode->m_value);
        newNode->Bind(MakeSharedPtr(this), it);
    }

    /// Adds @p element to the end of the list.
    /// @param element Element to add into list.
    void Add(const T& element) override
    {
        AddLast(element);
    }

    /// Deletes all elements in list.
    void Clear() override
    {
        Invalidate();

        std::for_each(m_ptr_node_map.begin(), m_ptr_node_map.end(),
                      [](const std::pair<const T*, LinkedListNode<T>*>& it_node_pair) {
                          it_node_pair.second->UnbindNode();
                      });
        m_ptr_node_map.clear();
        m_data.clear();
    }

    /// Checks if @p element is present in list.
    /// @param element Element to look for.
    /// @return True if @p element is found, false otherwise.
    bool Contains(const T& element) const override
    {
        return std::find(m_data.begin(), m_data.end(), element) != m_data.end();
    }

    /// Copies container data into existing array elements.
    /// @param array the destination
    /// @param index zero-based index in array at which copying begins.
    void CopyTo(ArrayPtr<T> array, int index) override
    {
        if (array == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: array");

        if (index < 0)
            throw ArgumentOutOfRangeException(u"Index is out of range. Parameter name: index");

        if (array->get_Count() - index < get_Count())
            throw ArgumentException(u"Insufficient space in the target location to copy the information.");

        std::copy(m_data.begin(), m_data.end(), array.begin() + index);
    }

    /// Performs forward direction find of an @p element in the list.
    /// @param element Element to find.
    /// @return Founded node if @p element is found, nullptr otherwise.
    SharedPtr<LinkedListNode<T>> Find(const T& element) const
    {
        auto it = std::find(m_data.begin(), m_data.end(), element);
        if (it == m_data.end())
            return nullptr;
        else
            return MakeSharedLinkedListNode(it);
    }

    /// Performs reverse direction find of an @p element in the list.
    /// @param element Element to find.
    /// @return Founded node if @p element is found, nullptr otherwise.
    SharedPtr<LinkedListNode<T>> FindLast(const T& element) const
    {
        auto rit = std::find(m_data.rbegin(), m_data.rend(), element);
        if (rit == m_data.rend())
            return nullptr;
        else
            return MakeSharedLinkedListNode(--rit.base());
    }

    /// Gets enumerator to iterate through current LinkedList.
    /// @return Newly created enumerator object.
    SharedPtr<IEnumerator<T>> GetEnumerator() override
    {
        return MakeObject<Enumerator>(MakeSharedPtr(this));
    }

    /// Removes first occurance of the specified @p element from list.
    /// @param element Element to remove.
    /// @return True if @p element was found and removed, false otherwise.
    bool Remove(const T& element) override
    {
        auto it = std::find(m_data.begin(), m_data.end(), element);
        if (it == m_data.end())
            return false;
        else
        {
            Invalidate();

            auto ptr_node_it = m_ptr_node_map.find(&*it);
            if (ptr_node_it != m_ptr_node_map.end())
            {
                ptr_node_it->second->Unbind();
            }

            m_data.erase(it);
            return true;
        }
    }

    /// Removes node from list
    /// @param node Node to remove.
    void Remove(const SharedPtr<LinkedListNode<T>>& node)
    {
        if (node == nullptr)
            throw ArgumentNullException(u"Value cannot be null. Parameter name: node");

        if (node->m_list.get() != this)
            throw InvalidOperationException(u"The LinkedList node does not belong to current LinkedList.");

        Invalidate();

        auto it = node->m_it;
        node->Unbind();
        m_data.erase(it);
    }

    /// Removes first node from list
    /// @throw InvalidOperationException if the LinkedList<T> is empty.
    void RemoveFirst()
    {
        if (m_data.empty())
            throw InvalidOperationException(u"The LinkedList is empty.");

        Invalidate();

        auto ptr_node_it = m_ptr_node_map.find(&*m_data.begin());
        if (ptr_node_it != m_ptr_node_map.end())
        {
            ptr_node_it->second->Unbind();
        }

        m_data.pop_front();
    }

    /// Removes last node from list
    /// @throw InvalidOperationException if the LinkedList<T> is empty.
    void RemoveLast()
    {
        if (m_data.empty())
            throw InvalidOperationException(u"The LinkedList is empty.");
        
        Invalidate();

        auto ptr_node_it = m_ptr_node_map.find(&*--m_data.end());
        if (ptr_node_it != m_ptr_node_map.end())
        {
            ptr_node_it->second->Unbind();
        }

        m_data.pop_back();
    }

    /// Gets iterator to the first element of collection.
    /// @return An iterator pointing to the first element in the linked list.
    iterator begin() noexcept
    {
        return m_data.begin();
    }
    /// Gets iterator for a non-existent element behind the end of the collection.
    /// @return An iterator pointing to the theoretical element placed after the end element in the linked list.
    iterator end() noexcept
    {
        return m_data.end();
    }

    /// Gets iterator to the first element of the const-qualified collection.
    /// @return An iterator pointing to the first element in the const-qualified instance of the linked list.
    const_iterator begin() const noexcept
    {
        return m_data.begin();
    }
    /// Gets iterator for a non-existent element behind the end of the const-qualified collection.
    /// @return An iterator pointing to the theoretical element placed after the end element in the const-qualified
    /// instance of the linked list.
    const_iterator end() const noexcept
    {
        return m_data.end();
    }

    /// Gets iterator to the first const-qualified element of collection.
    /// @return An iterator pointing to the first const-qualified element in the linked list.
    const_iterator cbegin() const noexcept
    {
        return m_data.cbegin();
    }
    /// Gets iterator for a non-existent const-qualified element behind the end of the collection.
    /// @return An iterator pointing to the theoretical const-qualified element placed after the end element in the
    /// linked list.
    const_iterator cend() const noexcept
    {
        return m_data.cend();
    }

    /// Gets a reverse iterator to the last element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the linked list (first in reverse).
    reverse_iterator rbegin() noexcept
    {
        return m_data.rbegin();
    }
    /// Gets a reverse iterator for a non-existent element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical element preceeding the first element in the linked list
    /// (last in reverse).
    reverse_iterator rend() noexcept
    {
        return m_data.rend();
    }

    /// Gets a reverse iterator to the last element of the const-qualified collection (first in reverse).
    /// @return A reverse iterator pointing to the last element in the const-qualified linked list (first in reverse).
    const_reverse_iterator rbegin() const noexcept
    {
        return m_data.rbegin();
    }
    /// Gets a reverse iterator for a non-existent element before the start of the const-qualified collection.
    /// @return A reverse iterator pointing to the theoretical element preceeding the first element in the
    /// const-qualified linked list (last in reverse).
    const_reverse_iterator rend() const noexcept
    {
        return m_data.rend();
    }

    /// Gets a reverse iterator to the last const-qualified element of collection (first in reverse).
    /// @return A reverse iterator pointing to the last const-qualified element in the linked list (first in reverse).
    const_reverse_iterator crbegin() const noexcept
    {
        return m_data.crbegin();
    }
    /// Gets a reverse iterator for a non-existent const-qualified element before the start of the collection.
    /// @return A reverse iterator pointing to the theoretical const-qualified element preceeding the first element in
    /// the linked list (last in reverse).
    const_reverse_iterator crend() const noexcept
    {
        return m_data.crend();
    }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, iterator>(begin(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, iterator>(end(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, const_iterator>(begin(), end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, const_iterator>(end(), end());
    }

#ifdef __DBG_FOR_EACH_MEMBER
    /// Applies visitor to container and elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor& visitor) const override
    {
        Object::DBG_for_each_member(visitor);

        visitor.add_self(this);
        visitor.add_member(this, m_data, "m_data");
    }

    /// Gets class name.
    /// @return Pointer to string literal.
    const char* DBG_class_name() const override { return "LinkedList<T>"; }
#endif

protected:
    /// Destructor.
    ~LinkedList() override
    {}

#ifdef ASPOSE_GET_SHARED_MEMBERS
    DEFINE_GET_SHARED_MEMBERS(m_data)
#endif

private:
    /// Finds or add new LinkedListNode in m_ptr_node_map hash table and makes shared pointer to it.
    /// @return A shared pointer of a LinkedListNode.
    SharedPtr<LinkedListNode<T>> MakeSharedLinkedListNode(iterator it) const
    {
        auto ptr_node_it = m_ptr_node_map.find(&*it);
        if (ptr_node_it != m_ptr_node_map.end())
            return MakeSharedPtr(ptr_node_it->second);
        else
            return LinkedListNode<T>::MakeObject(MakeSharedPtr(this), it);
    }

    /// Underlying list.
    mutable list_t m_data;
    /// Hash table, that maps pointers of list datas and pointers of all LinkedListNode that wraps iterators of that
    /// datas.
    std::unordered_map<const T*, LinkedListNode<T>*> m_ptr_node_map;
};

}}} // namespace System::Collections::Generic
