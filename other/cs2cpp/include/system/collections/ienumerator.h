/// @file system/collections/ienumerator.h
#pragma once

#include <system/object.h>
#include <defines.h>
#include <system/exceptions.h>
#include <system/idisposable.h>
#include <system/make_const_ref.h>
#include <system/collections/virtualized_iterator.h>
#include <numeric>
#include <utility>

namespace System {
namespace Collections {
namespace Generic {

/// Interface of enumerator which can be used to iterate through some elements.
/// Objects of this class should only be allocated using System::MakeObject() function.
/// Never create instance of this type on stack or using operator new, as it will result in runtime errors and/or assertion faults.
/// Always wrap this class into System::SmartPtr pointer and use this pointer to pass it to functions as argument.
/// @code
/// #include <system/collections/list.h>
/// #include <system/smart_ptr.h>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create the List-class instance.
///   auto collection = MakeObject<List<int>>();
///
///   // Fill the list.
///   collection->Add(1);
///   collection->Add(2);
///   collection->Add(3);
///
///   // Get the enumerator of the list.
///   auto enumerator = collection->GetEnumerator();
///
///   while (enumerator->MoveNext())
///   {
///     // Get the current element and print it.
///     std::cout << enumerator->get_Current() << ' ';
///   }
///
///   // Reset the enumerator.
///   enumerator->Reset();
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1 2 3
/// */
/// @endcode
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS IEnumerator
    : virtual public IDisposable
    , public System::Details::EnumeratorBasedIterator<T>
    , protected System::Details::IteratorPointerUpdater<T, false>
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::IEnumerator<T>, System::BaseTypesInfo<System::IDisposable>);

    using System::Details::IteratorPointerUpdater<T, false>::UpdateIteratorPointer;
    using System::Details::IteratorPointerUpdater<T, false>::InitializeIteratorPointer;

public:
    IEnumerator()
        : System::Details::EnumeratorBasedIterator<T>(std::numeric_limits<std::ptrdiff_t>::max())
        , m_owned_by_virtualized_iterator(false)
    {}

    virtual ~IEnumerator()
    {
        if (m_owned_by_virtualized_iterator)
            Object::SharedRefRemovedSafe();
    }

    /// Value type.
    typedef T ValueType;

    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual MakeConstRef_t<T> Current() const { return get_Current(); }
    /// Gets current element.
    /// @return Currently referenced element copy.
    virtual MakeConstRef_t<T> get_Current() const = 0;
    /// Moves enumerator to the next element. If no element was referenced before, sets reference to the first element available.
    /// If container end was hit, does nothing.
    /// @return True if some element is available after call, false otherwise.
    virtual bool MoveNext() = 0;
    /// Resets enumerator to position before first element.
    virtual void Reset() { throw System::NotImplementedException(); }

    /// Does the first MoveNext() call and prepares the enumerator object to be used by VirtualizedIterator.
    void InitializeIterator() override
    {
        InitializeIteratorPointer(System::Details::VirtualizedIteratorBase<T>::m_pointer);
        if (MoveNext())
        {
            m_offset = 0;
            UpdateIteratorPointer(System::Details::VirtualizedIteratorBase<T>::m_pointer, get_Current());
            System::Details::VirtualizedIteratorBase<T>::m_is_end = false;
        }
        else
            System::Details::VirtualizedIteratorBase<T>::m_is_end = true;
    }
    /// Moves the iterator step forward.
    void IncrementIterator() override
    {
        if (MoveNext())
        {
            ++m_offset;
            UpdateIteratorPointer(System::Details::VirtualizedIteratorBase<T>::m_pointer, get_Current());
        }
        else
        {
            m_offset = std::numeric_limits<std::ptrdiff_t>::max();
            System::Details::VirtualizedIteratorBase<T>::m_pointer = nullptr;
            System::Details::VirtualizedIteratorBase<T>::m_is_end = true;
        }
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<T>* CloneIterator() const override
    {
        throw System::NotImplementedException();
    }
    /// Prepares the iterator to be used by the VirtualizedIterator class.
    /// @return This pointer.
    IEnumerator* AsVirtualizedIterator()
    {
        InitializeIterator();
        SharedRefAdded();
        return this;
    }
    /// Marks the enumerator owned by virtualized iterator.
    void MarkOwnedByVirtualizedIterator()
    {
        m_owned_by_virtualized_iterator = true;
    }

protected:
    /// Copy constructor.
    /// @param other Enumerator to copy data from.
    IEnumerator(const IEnumerator &other)
        : System::Details::EnumeratorBasedIterator<T>(other.m_offset)
        , m_owned_by_virtualized_iterator(false)
    {}

    using System::Details::EnumeratorBasedIterator<T>::m_offset;
    /// Whether is owned by VirtualizedIterator
    bool m_owned_by_virtualized_iterator;
};

/// Iterator that wraps the pre-created enumerator and redirects all calls into it.
/// @tparam Element Element type.
template <typename Element>
class EnumeratorWrapperIterator : public System::Details::VirtualizedIteratorBase<Element>
{
public:
    EnumeratorWrapperIterator(const SharedPtr<IEnumerator<Element>> &enumerator)
        : System::Details::VirtualizedIteratorBase<Element>(false, enumerator->IsEndIterator())
        , m_enumerator(enumerator)
    {
        System::Details::VirtualizedIteratorBase<Element>::m_pointer = m_enumerator->GetElementPointer();
    }

    /// Destructor.
    virtual ~EnumeratorWrapperIterator() = default;

    /// Moves the iterator step forward.
    /// Must update m_is_end and m_pointer.
    void IncrementIterator() override
    {
        m_enumerator->IncrementIterator();
        System::Details::VirtualizedIteratorBase<Element>::m_pointer = m_enumerator->GetElementPointer();
        System::Details::VirtualizedIteratorBase<Element>::m_is_end = m_enumerator->IsEndIterator();
    }
    /// Checks if two iterators point to the same item.
    /// @param other Iterator to check against.
    /// @return True if both this and @p other iterators point to the same item, false otherwise.
    bool IteratorEquals(System::Details::VirtualizedIteratorBase<Element> *other) const override
    {
        return m_enumerator->IteratorEquals(other);
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    System::Details::VirtualizedIteratorBase<Element>* CloneIterator() const override
    {
        return m_enumerator->CloneIterator();
    }

protected:
    /// Wrapped enumerator.
    const SharedPtr<IEnumerator<Element>> m_enumerator;
};


/// Placeholder macro for the API keyword when there is no one.
#define CODEPORTING_NO_API_KEYWORD

/// Declaration of the public methods of the abstract enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
/// @tparam api_keyword API keyword to define the methods with.
#define CODEPORTING_ABSTRACT_ENUMERATOR_ITERATOR_METHODS_DECLARATION(element_type, api_keyword) \
public: \
    api_keyword ::System::Details::VirtualizedIteratorBase<element_type>* CloneIterator() const override; \
    api_keyword void InitializeIterator() override; \
    api_keyword void IncrementIterator() override;

/// In-class definition of the public methods of the abstract enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
#define CODEPORTING_ABSTRACT_ENUMERATOR_ITERATOR_MEMBERS_INLINE(element_type) \
public: \
    ::System::Details::VirtualizedIteratorBase<element_type>* CloneIterator() const \
    { \
        throw System::NotImplementedException(); \
    } \
    void InitializeIterator() override \
    { \
        ::System::Collections::Generic::IEnumerator<element_type>::InitializeIterator(); \
    } \
    void IncrementIterator() override \
    { \
        ::System::Collections::Generic::IEnumerator<element_type>::IncrementIterator(); \
    }

/// Definition of the public methods of the abstract enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
/// @tparam type_name Name of the enumerator type.
#define CODEPORTING_ABSTRACT_ENUMERATOR_ITERATOR_MEMBERS_IMPLEMENTATION(element_type, type_name) \
    ::System::Details::VirtualizedIteratorBase<element_type>* type_name::CloneIterator() const \
    { \
        throw System::NotImplementedException(); \
    } \
    void type_name::InitializeIterator() \
    { \
        ::System::Collections::Generic::IEnumerator<element_type>::InitializeIterator(); \
    } \
    void type_name::IncrementIterator() \
    { \
        ::System::Collections::Generic::IEnumerator<element_type>::IncrementIterator(); \
    }

/// Declaration of the public methods of the concrete enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
/// @tparam api_keyword API keyword to define the methods with.
#define CODEPORTING_ENUMERATOR_ITERATOR_METHODS_DECLARATION(element_type, api_keyword) \
public: \
    api_keyword ::System::Details::VirtualizedIteratorBase<element_type>* CloneIterator() const override; \
    api_keyword void InitializeIterator() override; \
    api_keyword void IncrementIterator() override; \

/// In-class definition of the public methods of the concrete enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
/// @tparam this_type Current enumerator class.
/// @tparam ptr_type Type the SmartPtr should keep to the current enumerator type.
#define CODEPORTING_ENUMERATOR_ITERATOR_MEMBERS_INLINE(element_type, this_type, ptr_type) \
public: \
    ::System::Details::VirtualizedIteratorBase<element_type>* CloneIterator() const override \
    { \
        if (::System::Details::VirtualizedIteratorBase<element_type>::IsEndIterator()) \
            return new ::System::Details::EnumeratorBasedEndIterator<element_type>(); \
        if (::System::Details::EnumeratorBasedIterator<element_type>::m_offset != 0) \
            throw ::System::NotSupportedException(u"Cloning intermediate state enumerator-based iterator"); \
        this_type *const copy = new this_type(*this); \
        std::unique_ptr<ptr_type> holder(copy); \
        copy->::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end; \
        copy->::System::Details::IteratorPointerUpdater<element_type, false>::InitializeIteratorPointer(copy->::System::Details::VirtualizedIteratorBase<element_type>::m_pointer); \
        copy->::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = copy->GetCurrentElementPointer(); \
        holder.release(); \
        return copy; \
    } \
    void InitializeIterator() override \
    { \
        ::System::Details::IteratorPointerUpdater<element_type, false>::InitializeIteratorPointer(::System::Details::EnumeratorBasedIterator<element_type>::m_pointer); \
        if (MoveNextImplementation()) \
        { \
            ::System::Details::EnumeratorBasedIterator<element_type>::m_offset = 0; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = GetCurrentElementPointer(); \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = false; \
        } \
        else \
        { \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = true; \
        } \
    } \
    void IncrementIterator() override \
    { \
        if (MoveNextImplementation()) \
        { \
            ++::System::Details::EnumeratorBasedIterator<element_type>::m_offset; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = GetCurrentElementPointer(); \
        } \
        else \
        { \
            ::System::Details::EnumeratorBasedIterator<element_type>::m_offset = std::numeric_limits<std::ptrdiff_t>::max(); \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = nullptr; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = true; \
        } \
    }

/// Definition of the public methods of the concrete enumerator that can be used as iterator.
/// @tparam element_type Type of the elements iterating through.
/// @tparam this_type Current enumerator class.
/// @tparam ptr_type Type the SmartPtr should keep to the current enumerator type.
#define CODEPORTING_ENUMERATOR_ITERATOR_MEMBERS_IMPLEMENTATION(element_type, type_name, ptr_type) \
    ::System::Details::VirtualizedIteratorBase<element_type>* type_name::CloneIterator() const \
    { \
        if (::System::Details::VirtualizedIteratorBase<element_type>::IsEndIterator()) \
            return new ::System::Details::EnumeratorBasedEndIterator<element_type>(); \
        if (::System::Details::EnumeratorBasedIterator<element_type>::m_offset != 0) \
            throw ::System::NotSupportedException(u"Cloning intermediate state enumerator-based iterator"); \
        type_name *const copy = new type_name(*this); \
        std::unique_ptr<ptr_type> holder(copy); \
        copy->::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end; \
        copy->::System::Details::IteratorPointerUpdater<element_type, false>::InitializeIteratorPointer(copy->::System::Details::VirtualizedIteratorBase<element_type>::m_pointer); \
        copy->::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = copy->GetCurrentElementPointer(); \
        holder.release(); \
        return copy; \
    } \
    void type_name::InitializeIterator() \
    { \
        ::System::Details::IteratorPointerUpdater<element_type, false>::InitializeIteratorPointer(::System::Details::EnumeratorBasedIterator<element_type>::m_pointer); \
        if (MoveNextImplementation()) \
        { \
            ::System::Details::EnumeratorBasedIterator<element_type>::m_offset = 0; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = GetCurrentElementPointer(); \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = false; \
        } \
        else \
        { \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = true; \
        } \
    } \
    void type_name::IncrementIterator() \
    { \
        if (MoveNextImplementation()) \
        { \
            ++::System::Details::EnumeratorBasedIterator<element_type>::m_offset; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = GetCurrentElementPointer(); \
        } \
        else \
        { \
            ::System::Details::EnumeratorBasedIterator<element_type>::m_offset = std::numeric_limits<std::ptrdiff_t>::max(); \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_pointer = nullptr; \
            ::System::Details::VirtualizedIteratorBase<element_type>::m_is_end = true; \
        } \
    }


} // namespace Generic
} // namespace Collections
} // namespace System
