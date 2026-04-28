/// @file system/collections/queue.h
#ifndef _aspose_system_collections_queue_h_
#define _aspose_system_collections_queue_h_

#include "system/object.h"
#include "system/collections/base_enumerator.h"
#include "system/collections/ienumerable.h"
#include "system/collections/icollection.h"
#include "system/cycles_detection.h"

#include <list>

namespace System {
namespace Collections {
namespace Generic {

/// Queue class forward declaration.
template<typename T> class Queue;

/// Queue pointer.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
/// @param T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS QueuePtr : public SharedPtr<Queue<T> >
{
public:
    /// Constructs null pointer.
    QueuePtr() {}
    /// Constructs pointer to specific queue.
    /// @param obj Queue to point to.
    QueuePtr(const SharedPtr<Queue<T> >& obj) : SharedPtr<Queue<T> >(obj) { }
};

/// Queue container wrapping STL list.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include <system/collections/queue.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// void PrintItems(const SmartPtr<IEnumerable<int>> &queue)
/// {
///   for (const int item: queue)
///   {
///     std::cout << item << ' ';
///   }
///   std::cout << std::endl;
/// }
///
/// int main()
/// {
///   // Create the Queue-class instance.
///   auto queue = MakeObject<Queue<int>>();
///
///   // Fill the queue.
///   queue->Enqueue(1);
///   queue->Enqueue(2);
///   queue->Enqueue(3);
///
///   // Print the first queue item. The Peek method doesn't remove an item from the queue.
///   std::cout << queue->Peek() << std::endl;
///   // Print the queue items.
///   PrintItems(queue);
///
///   // Print the first queue item. The Dequeue method removes an item from the queue.
///   std::cout << queue->Dequeue() << std::endl;
///   // Print the queue items.
///   PrintItems(queue);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1
/// 1 2 3
/// 1
/// 2 3
/// */
/// @endcode
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS Queue : public IEnumerable<T>
{
    ASPOSE_COLLECTION_POINTER_MODE_CONTROL(T)

public:
    /// This type
    typedef T ValueType;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::Queue<T>, System::BaseTypesInfo<System::Object>);

public:
    /// Underlying data type.
    typedef std::list<T, ASPOSE_COLLECTION_ALLOCATOR_TYPE> queue_t;

protected:
    /// Pointer type.
    typedef SharedPtr<Queue<T> > ThisPtr;
    /// Iterator type.
    typedef typename queue_t::iterator queueIt_t;
    /// Wrapped data structure.
    queue_t m_data;

public:
    /// Container of same type elements.
    typedef SharedPtr<IEnumerable<T> > IEnumerablePtr;
    /// Enumerator type.
    typedef SharedPtr<IEnumerator<T> > IEnumeratorPtr;

    /// Enumerator to iterate through queue.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class Enumerator : public SimpleEnumerator<queue_t>
    {
    public:
        /// Constructs enumerator pointing to specific queue.
        /// @param data Queue to point to.
        Enumerator(const ThisPtr& data) : SimpleEnumerator<queue_t>(data, data->m_data) { }
        /// RTTI information.
        RTTI_INFO_TEMPLATE_CLASS(Queue<T>::Enumerator, System::BaseTypesInfo<System::Object>);
    };

    /// Constructs empty queue.
    Queue() : ASPOSE_COLLECTION_INIT_ALLOCATOR() {}
    /// Constructs empty queue.
    /// @param capacity Number of elements to reserve.
    /// @throw ArgumentOutOfRangeException if capacity is less than zero.
    Queue(int capacity) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        if (capacity < 0) {
            throw ArgumentOutOfRangeException(u"capacity");
        }
    }
    /// Copy constructor.
    /// @param items Container to copy data from.
    /// @throw ArgumentNullException if items is nullptr.
    Queue(const SharedPtr<IEnumerable<T>>& items) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        if (!items)
        {
            throw ArgumentNullException(u"items");
        }

        auto e = items->GetEnumerator();
        while (e->MoveNext())
            m_data.push_back(e->get_Current());
    }

    /// Gets enumerator to iterate through the queue.
    /// @return Pointer to newly created enumerator.
    IEnumeratorPtr GetEnumerator() override
    {
        return MakeObject<Enumerator>(MakeSharedPtr(this));
    }

    /// Gets number of elements in queue.
    /// @return Actual number of elements.
    virtual int get_Count() const
    {
        return ASPOSECPP_CHECKED_CAST(int, m_data.size());
    }
    /// Deletes all elements in queue.
    virtual void Clear()
    {
        m_data.clear();
    }

    /// Checks if queue contains specific element using operator == to compare elements.
    /// @param item Item to look for.
    /// @return True if item is present, false otherwise.
    virtual bool Contains(const T& item) const
    {
        return std::find(m_data.begin(), m_data.end(), item) != m_data.end();
    }
    /// Puts item to the end of the queue.
    /// @param item Item to push.
    void Enqueue(const T& item)
    {
        m_data.push_back(item);
    }
    /// Gets item from the beginning of the queue.
    /// @return Popped item.
    /// @throw ArgumentNullException if the queue is empty.
    T Dequeue()
    {
        if (m_data.empty())
        {
            throw InvalidOperationException(u"Queue is empty");
        }
        T rv = m_data.front();
        m_data.pop_front();
        return rv;
    }
    /// Gets item from the beginning of the queue, but does not remove it from queue.
    /// @return First item in queue.
    /// @throw ArgumentNullException if the queue is empty.
    T Peek()
    {
        if (m_data.empty())
        {
            throw InvalidOperationException(u"Queue is empty");
        }
        return m_data.front();
    }

    /// Underlying data structure accessor.
    /// @return Reference to underlying data structure.
    queue_t& data() { return m_data; }
    /// Underlying data structure accessor.
    /// @return Const reference to underlying data structure.
    const queue_t& data() const { return m_data; }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, typename queue_t::iterator>(m_data.begin(), m_data.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, typename queue_t::iterator>(m_data.end(), m_data.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, typename queue_t::const_iterator>(m_data.begin(), m_data.end());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, typename queue_t::const_iterator>(m_data.end(), m_data.end());
    }

protected:
    /// Destructor.
    ~Queue() override {}

#ifdef __DBG_FOR_EACH_MEMBER
public:
    /// Applies visitor to container and elements.
    /// @param visitor Visitor to apply.
    void DBG_for_each_member(DBG::for_each_member_visitor &visitor) const override
    {
        visitor.add_self(this);
        DBG::for_each_of_Object(this, m_data, visitor);
    }

    /// Gets class name.
    /// @return String literal pointer.
    const char* DBG_class_name() const override { return "Queue<T>"; }
#endif

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Defines loop references lookup algorithm for queue.
    DEFINE_GET_SHARED_MEMBERS(m_data)
#endif
};

} // namespace Generic
} // namespace Collections
} // namespace System

#endif // _aspose_system_collections_queue_h_
