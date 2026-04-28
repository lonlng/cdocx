/// @file system/collections/stack.h
#ifndef _aspose_system_collections_stack_h_
#define _aspose_system_collections_stack_h_

#include "system/object.h"
#include "system/array.h"
#include "system/collections/base_enumerator.h"
#include "system/collections/icollection.h"
#include "system/cycles_detection.h"

#include <list>
#include <iterator>

namespace System {
namespace Collections {
namespace Generic {

/// Stack class forward declaration.
template<typename T> class Stack;

/// Stack pointer.
/// This type is a pointer to manage other object's deletion.
/// It should be allocated on stack and passed to functions either by value or by const reference.
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS StackPtr : public SharedPtr<Stack<T> >
{
public:
    /// Constructs null pointer.
    StackPtr() {}
    /// Constructs pointer referencing specific stack.
    /// @param obj Stack to refeence.
    StackPtr(const SharedPtr<Stack<T> >& obj) : SharedPtr<Stack<T> >(obj) { }
};

/// Stack class wrapping std::list.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include <system/collections/stack.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// void PrintItems(const SmartPtr<IEnumerable<int>> &stack)
/// {
///   for (const auto item: stack)
///   {
///     std::cout << item << ' ';
///   }
///   std::cout << std::endl;
/// }
///
/// int main()
/// {
///   // Create the Stack-class instance.
///   auto stack = MakeObject<Stack<int>>();
///
///   // Fill the stack.
///   stack->Push(1);
///   stack->Push(2);
///   stack->Push(3);
///
///   // Print the last item of the stack. The Peek method doesn't remove an item from the stack.
///   std::cout << stack->Peek() << std::endl;
///   PrintItems(stack);
///
///   // Print the last item of the stack. The Pop method removes an item from the stack.
///   std::cout << stack->Pop() << std::endl;
///   PrintItems(stack);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 3
/// 3 2 1
/// 3
/// 2 1
/// */
/// @endcode
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS Stack : public IEnumerable<T>
{
    ASPOSE_COLLECTION_POINTER_MODE_CONTROL(T)

public:
    /// Value type.
    typedef T ValueType;

private:
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::Stack<T>, System::BaseTypesInfo<System::Object>);

public:
    /// Underlying data type.
    typedef std::list<T, ASPOSE_COLLECTION_ALLOCATOR_TYPE> stack_t;

protected:
    /// Pointer type.
    typedef SharedPtr<Stack<T> > ThisPtr;
    /// Iterator type.
    typedef typename stack_t::reverse_iterator queueIt_t;
    /// Underlying data structure.
    stack_t m_data;

public:
    /// Collection containing elements of same type.
    typedef SharedPtr<IEnumerable<T> > IEnumerablePtr;
    /// Enumerator type.
    typedef SharedPtr<IEnumerator<T> > IEnumeratorPtr;

    /// Enumerator to iterate through stack.
    /// Objects of this class should only be allocated using System::MakeObject() function.
    /// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
    /// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
    class Enumerator : public ReverseEnumerator<stack_t>
    {
    public:
        /// Constructs enumerator iterating through given stack.
        /// @param data Stack to iterate through.
        Enumerator(const ThisPtr& data) : ReverseEnumerator<stack_t>(data, data->m_data) { }
        /// RTTI information.
        RTTI_INFO_TEMPLATE_CLASS(Stack<T>::Enumerator, System::BaseTypesInfo<System::Object>);
    };

    /// Constructs empty stack.
    Stack() : ASPOSE_COLLECTION_INIT_ALLOCATOR() {}
    /// Constructs empty stack.
    /// @param capacity Number of elements to reserve; ignored.
    /// @throw ArgumentOutOfRangeException if capacity is less than zero.
    Stack(int capacity) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        if (capacity < 0)
        {
            throw ArgumentOutOfRangeException(u"capacity");
        }
        /* do nothing, underlying data structure doesn't support reserve  */
    }
    /// Copy constructor.
    /// @param collection Collection to copy elements from.
    /// @throw ArgumentNullException if collection is nullptr.
    Stack(IEnumerablePtr collection) : ASPOSE_COLLECTION_INIT_ALLOCATOR()
    {
        AddRange(collection);
    }

    /// Gets enumerator to iterate through current stack.
    /// @return Newly created enumerator to iterate through current stack.
    IEnumeratorPtr GetEnumerator() override
    {
        return MakeObject<Enumerator>(MakeSharedPtr(this));
    }
    /// Gets number of elements in stack.
    /// @return Actual elements count.
    virtual int get_Count() const
    {
        return ASPOSECPP_CHECKED_CAST(int, m_data.size());
    }
    /// Deletes all elements from stack.
    virtual void Clear()
    {
        m_data.clear();
    }

    /// Checks if specific item is present in container; uses operator == for comparison.
    /// @param item Item to look for.
    /// @return True if item is found, false otherwise.
    virtual bool Contains(const T& item) const
    {
        return std::find(m_data.begin(), m_data.end(), item) != m_data.end();
    }
    /// Puts element of top of the stack.
    /// @param item Element to push into stack.
    void Push(const T& item)
    {
        m_data.push_back(item);
    }
    /// Gets element from top of the stack.
    /// @return Popped element.
    T Pop()
    {
        if (m_data.empty())
            throw InvalidOperationException(u"Stack is empty");

        T rv = m_data.back();
        m_data.pop_back();
        return rv;
    }
    /// Gets element from stack top, but keeps it in stack.
    /// @return Top element of the stack.
    T Peek()
    {
        if (m_data.empty())
            throw InvalidOperationException(u"Stack is empty");

        return m_data.back();
    }

    /// Internal data structure accessor.
    /// @return Reference to internal data structure.
    stack_t& data() { return m_data; }
    /// Internal data structure accessor.
    /// @return Const reference to internal data structure.
    const stack_t& data() const { return m_data; }

    /// Converts stack to array.
    /// @return Newly created element with copies of all elements in stack.
    virtual ArrayPtr<T> ToArray()
    {
        ArrayPtr<T> result = System::MakeObject<Array<T> >(this->get_Count());

        std::copy(m_data.rbegin(), m_data.rend(), result->data().begin());

        return result;
    }

    /// Puts elements into stack.
    /// @param collection Container of elements to push into stack.
    /// @throw ArgumentNullException if collection is nullptr.
    void AddRange(IEnumerablePtr collection)
    {
        if (!collection)
        {
            throw ArgumentNullException(u"collection");
        }

        IEnumeratorPtr it = collection->GetEnumerator();
        while (it->MoveNext())
        {
            m_data.push_back(it->Current());
        }
    }

    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, typename stack_t::reverse_iterator>(m_data.rbegin(), m_data.rend());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndIterator() override
    {
        return new System::Details::NativeIteratorWrapper<T, typename stack_t::reverse_iterator>(m_data.rend(), m_data.rend());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeBeginConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeBeginConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, typename stack_t::const_reverse_iterator>(m_data.crbegin(), m_data.crend());
    }
    /// @copydoc System::Collections::Generic::IEnumerable<T>::virtualizeEndConstIterator
    System::Details::VirtualizedIteratorBase<T>* virtualizeEndConstIterator() const override
    {
        return new System::Details::NativeConstIteratorWrapper<T, typename stack_t::const_reverse_iterator>(m_data.crend(), m_data.crend());
    }

protected:
    /// Destructor.
    ~Stack() override = default;

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
    const char* DBG_class_name() const override { return "Stack<T>"; }
#endif

protected:
#ifdef ASPOSE_GET_SHARED_MEMBERS
    /// Defines loop references lookup algorithm for stack.
    DEFINE_GET_SHARED_MEMBERS(m_data)
#endif
};

} // namespace Generic
} // namespace Collections
} // namespace System

#endif // _aspose_system_collections_stack_h_
