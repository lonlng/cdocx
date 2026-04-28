/// @file system/collections/virtualized_iterator.h
#pragma once

#include <iterator>
#include <utility>
#include <memory>
#include <system/diagnostics/debug.h>
#include <type_traits>
#include <cstring>
#include <limits>

#include <system/exceptions.h>
#include <system/smart_ptr.h>
#include <defines.h>

namespace System { namespace Collections { namespace Generic {

template <typename T> class IEnumerable;

}}} // namespace System::Collections::Generic

namespace System { namespace Details {

/// Base type for the inner objects kept by VirtualizedIterator and VirtualizedConstIterator.
/// Child types should define the actual logic the iterator has.
/// @tparam Element Type of the elements being iterated through.
template <typename Element>
class VirtualizedIteratorBase
{
public:
    /// Destructor.
    virtual ~VirtualizedIteratorBase() = default;
    /// Gets the element which haves the specified offset to the current iterator.
    /// @param offset Offset to the current iterator.
    /// @return Element at the specified offset.
    virtual Element OffsetDereferenceIterator(std::ptrdiff_t offset) const
    {
        ASPOSE_UNUSED(offset);
        throw System::NotImplementedException(u"Iterator offset dereference");
    }
    /// Copy-sets the element which haves the specified offset to the current iterator.
    /// @param offset Offset to the current iterator.
    /// @param value Value to set.
    virtual void OffsetDereferenceAssignIterator(std::ptrdiff_t offset, const Element &value) const
    {
        ASPOSE_UNUSED(offset);
        ASPOSE_UNUSED(value);
        throw System::NotImplementedException(u"Iterator offset assignment");
    }
    /// Move-sets the element which haves the specified offset to the current iterator.
    /// @param offset Offset to the current iterator.
    /// @param value Value to set.
    virtual void OffsetDereferenceAssignIterator(std::ptrdiff_t offset, Element &&value) const
    {
        ASPOSE_UNUSED(offset);
        ASPOSE_UNUSED(value);
        throw System::NotImplementedException(u"Iterator offset assignment");
    }
    /// Moves the iterator step forward.
    /// Must update m_is_end and m_pointer.
    virtual void IncrementIterator() = 0;
    /// Moves the iterator step back.
    /// Must update m_is_end and m_pointer.
    virtual void DecrementIterator()
    {
        throw System::NotImplementedException(u"Iterator decrement");
    }
    /// Moves the iterator by the specified number of steps.
    /// Must update m_is_end and m_pointer.
    /// @param offset Number of steps to move the iterator by.
    virtual void ShiftIteratorBy(std::ptrdiff_t offset)
    {
        ASPOSE_UNUSED(offset);
        throw System::NotImplementedException(u"Iterator offset shift");
    }
    /// Checks if two iterators point to the same item.
    /// @param other Iterator to check against.
    /// @return True if both this and @p other iterators point to the same item, false otherwise.
    virtual bool IteratorEquals(VirtualizedIteratorBase *other) const = 0;
    /// Checks if two iterators are less-ordered.
    /// @param other Iterator to check against.
    /// @return True if this iterator precedes @p other, false otherwise.
    virtual bool IteratorLess(VirtualizedIteratorBase *other) const
    {
        ASPOSE_UNUSED(other);
        throw System::NotImplementedException(u"Iterator less-comparison");
    }
    /// Gets the number of steps between two iterators.
    /// @param other Iterator to check against.
    /// @return Number of steps from this iterator to the @p other one. Positive if this goes after @p other, negative if @p other goes after this.
    virtual std::ptrdiff_t DiffIterators(VirtualizedIteratorBase *other) const
    {
        ASPOSE_UNUSED(other);
        throw System::NotImplementedException(u"Iterator subtraction");
    }
    /// Clones current iterator.
    /// @return Copy of the current iterator.
    virtual VirtualizedIteratorBase* CloneIterator() const = 0;

    /// Checks whether assigning the dereferenced value changes the actual value stored in the container being iterated through.
    /// @return True if iterator dereference assignment changes stored value, false if the temporary value is being changed instead.
    bool AssignsContainerValue() const
    {
        return m_points_to_container_element;
    }
    /// Checks whether the current iterator points to the container's end.
    /// @return true if this iterator points to the container's end, false if it points to the element of container.
    bool IsEndIterator() const
    {
        return m_is_end;
    }
    /// Gets the pointer to the element being currently pointed by the iterator or to its copy.
    /// @return Pointer either to the current element or to its copy.
    Element* GetElementPointer() const
    {
        return m_pointer;
    }

    VirtualizedIteratorBase(const VirtualizedIteratorBase&) = delete;
    VirtualizedIteratorBase(VirtualizedIteratorBase&&) = delete;
    VirtualizedIteratorBase& operator = (const VirtualizedIteratorBase&) = delete;
    VirtualizedIteratorBase& operator = (VirtualizedIteratorBase&&) = delete;

protected:
    /// Constructor.
    /// @param points_to_container_element True if the iterator always has pointer to the element being iterated through, false if it can hold the pointer to this element's local copy.
    /// @param is_end_iterator True if the iterator point to the container's end, false otherwise.
    VirtualizedIteratorBase(bool points_to_container_element, bool is_end_iterator)
        : m_points_to_container_element(points_to_container_element)
        , m_is_end(is_end_iterator)
    {}

    /// Whether the iterator is guaranteed to have a pointer to an in-container value.
    const bool m_points_to_container_element;
    /// Whether current iterator points to the end of the container.
    bool m_is_end;
    /// Pointer to the currently referenced element or its copy.
    Element *m_pointer;
};


/// Service type to extract the inner iterator type from wrapper type e. g. reverse_iterator.
/// Specialization for non-wrapped iterator.
/// @tparam Iterator Type to extract inner iterator type from.
template <typename Iterator>
struct UnderlyingIteratorExtractor
{
    /// Iterator type.
    using type = Iterator;
};
/// Service type to extract the inner iterator type from wrapper type e. g. reverse_iterator.
/// Specialization for reverse_iterator wrappers.
/// @tparam Iterator Type that is wrapped.
template <typename Iterator>
struct UnderlyingIteratorExtractor<std::reverse_iterator<Iterator>>
{
    /// Unwrapped iterator type.
    using type = Iterator;
};
/// Type of the unwrapped the iterator type from wrapper type e. g. reverse_iterator.
/// @tparam Iterator Type to extract inner iterator type from.
template <typename Iterator>
using UnderlyingIteratorType = typename UnderlyingIteratorExtractor<typename std::remove_cv<typename std::remove_reference<Iterator>::type>::type>::type;


/// Service type for iterator offset dereference.
/// Specialization for the iterators that don't support offset dereferencement.
/// @tparam Iterator Iterator type.
/// @tparam Value Value type.
template <typename Iterator, typename Value, typename = void>
struct IteratorOffsetDereferencer
{
    /// Gets the element at the specified offset to the iterator.
    /// @throws Always throws NotSupportedException.
    static Value get(const Iterator&, std::ptrdiff_t)
    {
        throw System::NotSupportedException(u"Iterator offset dereference");
    }
};
/// Service type for iterator offset dereference.
/// Specialization for the iterators that support offset dereferencement.
/// @tparam Iterator Iterator type.
/// @tparam Value Value type.
template <typename Iterator, typename Value>
struct IteratorOffsetDereferencer<Iterator, Value, decltype(std::declval<const UnderlyingIteratorType<Iterator>>()[std::declval<std::ptrdiff_t>()], (void)0)>
{
    /// Gets the element at the specified offset to the iterator.
    /// @param iterator Iterator to offset dereference.
    /// @param offset Offset to the given iterator to get element at.
    /// @return Value at the specified offset to the iterator.
    static Value get(const Iterator &iterator, std::ptrdiff_t offset)
    {
        return iterator[offset];
    }
};

/// Service type for iterator offset assignment.
/// Specialization for the iterators that don't support offset assignment.
/// @tparam Iterator Iterator type.
/// @tparam Value Value type.
template <typename Iterator, typename Value, typename = void>
struct IteratorOffsetAssigner
{
    /// Sets the element at the specified offset to the iterator.
    /// @throws Always throws NotSupportedException.
    static void assign(const Iterator&, std::ptrdiff_t, const Value&)
    {
        throw System::NotSupportedException(u"Iterator offset assignment");
    }
};
/// Service type for iterator offset assignment.
/// Specialization for the iterators that support offset assignment.
/// @tparam Iterator Iterator type.
/// @tparam Value Value type.
template <typename Iterator, typename Value>
struct IteratorOffsetAssigner<Iterator, Value, decltype((void)(std::declval<const UnderlyingIteratorType<Iterator>>()[std::declval<std::ptrdiff_t>()] = std::declval<Value>()))>
{
    /// Copy-sets the element at the specified offset to the iterator.
    /// @param iterator Iterator to use as a reference point.
    /// @param offset Offset to the given iterator to set element at.
    /// @param value Value to set.
    static void assign(const Iterator &iterator, std::ptrdiff_t offset, const Value &value)
    {
        iterator[offset] = value;
    }
    /// Move-sets the element at the specified offset to the iterator.
    /// @param iterator Iterator to use as a reference point.
    /// @param offset Offset to the given iterator to set element at.
    /// @param value Value to set.
    static void assign(const Iterator &iterator, std::ptrdiff_t offset, Value &&value)
    {
        iterator[offset] = std::move(value);
    }
};

/// Service type for iterator decrement.
/// Specialization for the iterators that don't support decrement.
/// @tparam Iterator Iterator type.
template <typename Iterator, typename = void>
struct IteratorDecrementer
{
    /// Decrements iterator.
    /// @throws Always throws NotSupportedException.
    static void decrement(Iterator&)
    {
        throw System::NotSupportedException(u"Iterator decrement");
    }
};
/// Service type for iterator decrement.
/// Specialization for the iterators that support decrement.
/// @tparam Iterator Iterator type.
template <typename Iterator>
struct IteratorDecrementer<Iterator, decltype(--std::declval<UnderlyingIteratorType<Iterator>>(), (void)0)>
{
    /// Decrements iterator.
    /// @param iterator Iterator to decrement.
    static void decrement(Iterator &iterator)
    {
        --iterator;
    }
};

/// Service type for iterator shifting.
/// Specialization for the iterators that don't support shifting.
/// @tparam Iterator Iterator type.
template <typename Iterator, typename = void>
struct IteratorShifter
{
    /// Shifts iterator.
    /// @throws Always throws NotSupportedException.
    static void shift(Iterator&, std::ptrdiff_t)
    {
        throw System::NotSupportedException(u"Iterator decrement");
    }
};
/// Service type for iterator shifting.
/// Specialization for the iterators that support shifting.
/// @tparam Iterator Iterator type.
template <typename Iterator>
struct IteratorShifter<Iterator, decltype(std::declval<UnderlyingIteratorType<Iterator>>() += std::declval<std::ptrdiff_t>(), (void)0)>
{
    /// Shifts iterator.
    /// @param iterator Iterator to shift.
    /// @param offset Number of steps to shift iterator by.
    static void shift(Iterator &iterator, std::ptrdiff_t offset)
    {
        iterator += offset;
    }
};

/// Service type for iterator subtraction.
/// Specialization for the iterators that don't support subtraction.
/// @tparam Iterator Iterator type.
template <typename Iterator, typename = void>
struct IteratorDiffer
{
    /// Subtracts iterators.
    /// @throws Always throws NotSupportedException.
    static std::ptrdiff_t diff(const Iterator&, const Iterator&)
    {
        throw System::NotSupportedException(u"Iterator difference");
    }
};
/// Service type for iterator subtraction.
/// Specialization for the iterators that support subtraction.
/// @tparam Iterator Iterator type.
template <typename Iterator>
struct IteratorDiffer<Iterator, decltype(std::declval<UnderlyingIteratorType<Iterator>>() - std::declval<UnderlyingIteratorType<Iterator>>(), (void)0)>
{
    /// Subtracts iterators.
    /// @param lhs Left-hand iterator.
    /// @param rhs Right-hand iterator.
    /// @return Iterator subtraction result.
    static std::ptrdiff_t diff(const Iterator &lhs, const Iterator &rhs)
    {
        return lhs - rhs;
    }
};

/// Service type for iterator less-comparison.
/// Specialization for the iterators that don't support less-comparison.
/// @tparam Iterator Iterator type.
template <typename Iterator, typename = void>
struct IteratorLessComparer
{
    /// Less-compares the iterators.
    /// @throws Always throws NotSupportedException.
    static bool less(const Iterator&, const Iterator&)
    {
        throw System::NotSupportedException(u"Iterator less-comparison");
    }
};
/// Service type for iterator less-comparison.
/// Specialization for the iterators that support less-comparison.
/// @tparam Iterator Iterator type.
template <typename Iterator>
struct IteratorLessComparer<Iterator, decltype(std::declval<UnderlyingIteratorType<Iterator>>() < std::declval<UnderlyingIteratorType<Iterator>>(), (void)0)>
{
    /// Less-compares the iterators.
    /// @param lhs Left-hand iterator.
    /// @param rhs Right-hand iterator.
    /// @return True if @p lhs precedes @p rhs, false otherwise.
    static bool less(const Iterator &lhs, const Iterator &rhs)
    {
        return lhs < rhs;
    }
};


/// Service base class that implements the strategy to get pointers to iterator-provided values (either caching or not).
/// Specialization for the case of iterators providing real references to in-container elements.
/// @tparam Element Type of the container element.
/// @tparam iterator_provides_direct_reference Whether the iterators provide direct references to container's elements.
template <typename Element, bool iterator_provides_direct_reference,
    bool = std::is_arithmetic<Element>::value || std::is_enum<Element>::value || IsSmartPtr<Element>::value || System::detail::is_a<Element, System::ExceptionWrapper>::value>
struct IteratorPointerUpdater
{
    /// Initializes the pointer to the element. Required for caching implementations.
    void InitializeIteratorPointer(Element*&)
    {}
    /// Assigns the pointer directly to the container's element.
    /// Used from native iterator wrappers.
    /// @param pointer Pointer the external code will have.
    /// @param value Element to point to.
    void UpdateIteratorPointer(Element *&pointer, Element &value)
    {
        pointer = &value;
    }
    /// Assigns the pointer directly to the container's element.
    /// Used from native iterator wrappers.
    /// @param pointer Pointer the external code will have.
    /// @param value Element to point to.
    void UpdateIteratorPointer(Element *&pointer, const Element &value)
    {
        // This is to make const iterators compatible with VirtualizedIteratorBase interface and to avoid having separate VirtualizedConstIteratorBase one.
        // Actually, this pointer will never be used as a non-const for const iterators.
        pointer = const_cast<Element*>(&value);
    }
};

/// Service base class that implements the strategy to get pointers to iterator-provided values (either caching or not).
/// Specialization for the case of iterators not providing real references to in-container elements and trivial element's default constructors:
/// provides caching and constructs cached value by default.
/// @tparam Element Type of the container element.
template <typename Element>
struct IteratorPointerUpdater<Element, false, true>
{
    /// Initializes the pointer to the element.
    /// @param pointer Pointer to target to internal cache.
    void InitializeIteratorPointer(Element *&pointer)
    {
        pointer = &m_cache;
    }
    /// Updates the cached value.
    /// Used from native iterator wrappers.
    /// @param value Value to copy to the cache.
    void UpdateIteratorPointer(Element*&, const Element &value)
    {
        m_cache = value;
    }
    /// Updates the cached value.
    /// Used from native iterator wrappers.
    /// @param value Value to move to the cache.
    void UpdateIteratorPointer(Element*&, Element &&value)
    {
        m_cache = std::move(value);
    }

    /// Moves value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldTemporaryObject(Element &&value)
    {
        m_cache = std::move(value);
        return &m_cache;
    }
    /// Copies value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldTemporaryObject(const Element &value)
    {
        m_cache = value;
        return &m_cache;
    }
    /// Moves value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldIfTemporary(Element &&value)
    {
        m_cache = std::move(value);
        return &m_cache;
    }
    /// Copies value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldIfTemporary(const Element &value)
    {
        m_cache = value;
        return &m_cache;
    }
    /// Returns direct pointer to the given non-temporary value.
    /// @param value Value to get pointer to.
    /// @return Pointer to the given value.
    Element* HoldIfTemporary(Element &value)
    {
        return &value;
    }

    /// Moves value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldAndGetReference(Element &&value) const
    {
        m_cache = std::move(value);
        return m_cache;
    }
    /// Copies value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldAndGetReference(const Element &value) const
    {
        m_cache = value;
        return m_cache;
    }
    /// Moves value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldIfTemporaryAndGetReference(Element &&value) const
    {
        m_cache = std::move(value);
        return m_cache;
    }
    /// Returns the given reference to the non-temporary object.
    /// Used from enumerators.
    /// @param value Value to return.
    /// @return Same reference as @p value.
    const Element& HoldIfTemporaryAndGetReference(const Element &value) const
    {
        return value;
    }

private:
    /// Cached value.
    mutable Element m_cache;
};

/// Service base class that implements the strategy to get pointers to iterator-provided values (either caching or not).
/// Specialization for the case of iterators not providing real references to in-container elements and trivial element's default constructors:
/// provides caching, but does not construct cached element until it is required.
/// @tparam Element Type of the container element.
template <typename Element>
struct IteratorPointerUpdater<Element, false, false>
{
    /// Constructor.
    IteratorPointerUpdater() = default;
    /// Moving constructor. Doesn't actually move cached value.
    IteratorPointerUpdater(const IteratorPointerUpdater &)
        : m_allocated(false)
    {}
    /// Destructor.
    ~IteratorPointerUpdater()
    {
        if (m_allocated)
            reinterpret_cast<Element&>(m_cache).~Element();
    }
    /// Initializes the pointer to the element.
    /// @param pointer Pointer to target to internal cache.
    void InitializeIteratorPointer(Element *&pointer)
    {
        pointer = reinterpret_cast<Element*>(&m_cache);
    }
    /// Updates the cached value.
    /// Used from native iterator wrappers.
    /// @param value Value to copy to the cache.
    void UpdateIteratorPointer(Element*&, const Element &value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(value);
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = value;
        }
    }
    /// Updates the cached value.
    /// Used from native iterator wrappers.
    /// @param value Value to move to the cache.
    void UpdateIteratorPointer(Element*&, Element &&value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(std::move(value));
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = std::move(value);
        }
    }

    /// Moves value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldTemporaryObject(Element &&value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(std::move(value));
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = std::move(value);
        }
        return reinterpret_cast<Element*>(&m_cache);
    }
    /// Copies value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldTemporaryObject(const Element &value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(value);
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = value;
        }
        return reinterpret_cast<Element*>(&m_cache);
    }
    /// Moves value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldIfTemporary(Element &&value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(std::move(value));
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = std::move(value);
        }
        return reinterpret_cast<Element*>(&m_cache);
    }
    /// Copies value into cache and returns pointer to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    Element* HoldIfTemporary(const Element &value)
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(value);
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = value;
        }
        return reinterpret_cast<Element*>(&m_cache);
    }
    /// Returns direct pointer to the given non-temporary value.
    /// @param value Value to get pointer to.
    /// @return Pointer to the given value.
    Element* HoldIfTemporary(Element &value)
    {
        return &value;
    }

    /// Moves value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldAndGetReference(Element &&value) const
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(std::move(value));
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = std::move(value);
        }
        return *reinterpret_cast<Element*>(&m_cache);
    }
    /// Copies value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldAndGetReference(const Element &value) const
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(value);
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = value;
        }
        return *reinterpret_cast<Element*>(&m_cache);
    }
    /// Moves value into cache and returns reference to it.
    /// Used from enumerators.
    /// @param value Value to store.
    /// @return Pointer to the stored value.
    const Element& HoldIfTemporaryAndGetReference(Element &&value) const
    {
        if (!m_allocated)
        {
            new (reinterpret_cast<Element*>(&m_cache)) Element(std::move(value));
            m_allocated = true;
        }
        else
        {
            reinterpret_cast<Element&>(m_cache) = std::move(value);
        }
        return *reinterpret_cast<Element*>(&m_cache);
    }
    /// Returns the given reference to the non-temporary object.
    /// Used from enumerators.
    /// @param value Value to return.
    /// @return Same reference as @p value.
    const Element& HoldIfTemporaryAndGetReference(const Element &value) const
    {
        return value;
    }

private:
    /// Whether the cache was initialized and should be destructred.
    mutable bool m_allocated = false;
    /// Cached value.
    mutable typename std::aligned_storage<sizeof(Element), alignof(Element)>::type m_cache;
};


/// Base type for the virtualized iterator cores that are implemented around native C++-styled iterators.
/// This class implements iterator position changes, but the value access should be implemented in subclasses.
/// @tparam Element Iterated element type.
/// @tparam Iterator Internal iterator type.
template <typename Element, typename Iterator>
class NativeIteratorWrapperBase : public VirtualizedIteratorBase<Element>
{
    /// Whether the iterator provides direct pointers to the stored values.
    static constexpr bool is_pointer_assignable = std::is_same<decltype(*std::declval<Iterator>()), Element&>::value;

public:
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeIteratorWrapperBase(const Iterator &iterator, const Iterator &end)
        : VirtualizedIteratorBase<Element>(is_pointer_assignable, iterator == end)
        , m_iterator(iterator)
        , m_end(end)
    {}
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeIteratorWrapperBase(Iterator &&iterator, Iterator &&end) noexcept
        : VirtualizedIteratorBase<Element>(is_pointer_assignable, iterator == end)
        , m_iterator(std::forward<Iterator>(iterator))
        , m_end(std::forward<Iterator>(end))
    {}
    /// Destructor.
    virtual ~NativeIteratorWrapperBase() = default;
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IteratorEquals
    bool IteratorEquals(VirtualizedIteratorBase<Element> *other) const override
    {
        CODEPORTING_DEBUG_ASSERT(dynamic_cast<NativeIteratorWrapperBase*>(other) != nullptr);
        return m_iterator == static_cast<NativeIteratorWrapperBase*>(other)->m_iterator;
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IteratorLess
    bool IteratorLess(VirtualizedIteratorBase<Element> *other) const override
    {
        CODEPORTING_DEBUG_ASSERT(dynamic_cast<NativeIteratorWrapperBase*>(other) != nullptr);
        return IteratorLessComparer<Iterator>::less(m_iterator, static_cast<NativeIteratorWrapperBase*>(other)->m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::DiffIterators
    std::ptrdiff_t DiffIterators(VirtualizedIteratorBase<Element> *other) const override
    {
        CODEPORTING_DEBUG_ASSERT(dynamic_cast<NativeIteratorWrapperBase*>(other) != nullptr);
        return IteratorDiffer<Iterator>::diff(m_iterator, static_cast<NativeIteratorWrapperBase*>(other)->m_iterator);
    }

    NativeIteratorWrapperBase(const NativeIteratorWrapperBase&) = delete;
    NativeIteratorWrapperBase(NativeIteratorWrapperBase&&) = delete;

protected:
    /// Stored iterator value.
    Iterator m_iterator;
    /// Iterator to the container's end.
    const Iterator m_end;

    /// Implementation of the iterator increment.
    /// @return True if the iterator still points to the element in the container and the cache should be updated (if any), false if it points to the container end.
    bool IteratorIncrementImplementation()
    {
        ++m_iterator;
        VirtualizedIteratorBase<Element>::m_is_end = m_iterator == m_end;
        if (VirtualizedIteratorBase<Element>::m_is_end)
            VirtualizedIteratorBase<Element>::m_pointer = nullptr;
        return !VirtualizedIteratorBase<Element>::m_is_end;
    }
    /// Implementation of the iterator shift.
    /// @param offset Number of steps to add to the iterator.
    /// @return True if the iterator still points to the element in the container and the cache should be updated (if any), false if it points to the container end.
    bool IteratorShiftImplementation(std::ptrdiff_t offset)
    {
        IteratorShifter<Iterator>::shift(m_iterator, offset);
        VirtualizedIteratorBase<Element>::m_is_end = m_iterator == m_end;
        if (VirtualizedIteratorBase<Element>::m_is_end)
            VirtualizedIteratorBase<Element>::m_pointer = nullptr;
        return !VirtualizedIteratorBase<Element>::m_is_end;
    }
};


/// Virtualized iterator kernel that wraps the native C++ iterator and proxies the values of them.
/// @param Element Iterated element type.
/// @param Iterator Stored iterator type.
template <typename Element, typename Iterator>
class NativeIteratorWrapper
    : public NativeIteratorWrapperBase<Element, Iterator>
    , private IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value>
{
    // Parent members to use.
    using NativeIteratorWrapperBase<Element, Iterator>::m_iterator;
    using NativeIteratorWrapperBase<Element, Iterator>::m_end;
    using VirtualizedIteratorBase<Element>::m_pointer;
    using IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value>::InitializeIteratorPointer;
    using IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value>::UpdateIteratorPointer;

public:
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeIteratorWrapper(const Iterator &iterator, const Iterator &end)
        : NativeIteratorWrapperBase<Element, Iterator>(iterator, end)
    {
        InitializeIteratorPointer(m_pointer);
        if (!VirtualizedIteratorBase<Element>::IsEndIterator())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeIteratorWrapper(Iterator &&iterator, Iterator &&end) noexcept
        : NativeIteratorWrapperBase<Element, Iterator>(std::forward<Iterator>(iterator), std::forward<Iterator>(end))
    {
        InitializeIteratorPointer(m_pointer);
        if (!VirtualizedIteratorBase<Element>::IsEndIterator())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// Destructor.
    virtual ~NativeIteratorWrapper() = default;
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IncrementIterator
    void IncrementIterator() override
    {
        if (NativeIteratorWrapperBase<Element, Iterator>::IteratorIncrementImplementation())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::DecrementIterator
    void DecrementIterator() override
    {
        IteratorDecrementer<Iterator>::decrement(m_iterator);
        VirtualizedIteratorBase<Element>::m_is_end = false;
        UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::ShiftIteratorBy
    void ShiftIteratorBy(std::ptrdiff_t offset) override
    {
        if (NativeIteratorWrapperBase<Element, Iterator>::IteratorShiftImplementation(offset))
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceIterator
    Element OffsetDereferenceIterator(std::ptrdiff_t offset) const override
    {
        return IteratorOffsetDereferencer<Iterator, Element>::get(m_iterator, offset);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceAssignIterator
    void OffsetDereferenceAssignIterator(std::ptrdiff_t offset, const Element &value) const override
    {
        IteratorOffsetAssigner<Iterator, Element>::assign(m_iterator, offset, value);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceAssignIterator
    void OffsetDereferenceAssignIterator(std::ptrdiff_t offset, Element &&value) const override
    {
        IteratorOffsetAssigner<Iterator, Element>::assign(m_iterator, offset, std::move(value));
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::CloneIterator
    VirtualizedIteratorBase<Element>* CloneIterator() const override
    {
        return new NativeIteratorWrapper(m_iterator, m_end);
    }

    NativeIteratorWrapper(NativeIteratorWrapper&&) = delete;

private:
    /// Copying constructor.
    /// @param other Instance to copy data from.
    NativeIteratorWrapper(const NativeIteratorWrapper &other)
        : NativeIteratorWrapper(other.m_iterator, other.VirtualizedIteratorBase<Element>::m_end)
    {}
};

/// Virtualized iterator kernel that wraps the native C++ const iterator and proxies the values of them.
/// @param Element Iterated element type.
/// @param Iterator Stored iterator type.
template <typename Element, typename Iterator>
class NativeConstIteratorWrapper
    : public NativeIteratorWrapperBase<Element, Iterator>
    , private IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value || std::is_same<const Element&, decltype(*std::declval<Iterator>())>::value>
{
    // Parent members to use.
    using NativeIteratorWrapperBase<Element, Iterator>::m_iterator;
    using NativeIteratorWrapperBase<Element, Iterator>::m_end;
    using VirtualizedIteratorBase<Element>::m_pointer;
    using IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value || std::is_same<const Element&, decltype(*std::declval<Iterator>())>::value>
        ::InitializeIteratorPointer;
    using IteratorPointerUpdater<Element, std::is_same<Element&, decltype(*std::declval<Iterator>())>::value || std::is_same<const Element&, decltype(*std::declval<Iterator>())>::value>
        ::UpdateIteratorPointer;

public:
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeConstIteratorWrapper(const Iterator &iterator, const Iterator &end)
        : NativeIteratorWrapperBase<Element, Iterator>(iterator, end)
    {
        InitializeIteratorPointer(m_pointer);
        if (!VirtualizedIteratorBase<Element>::IsEndIterator())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// Constructor.
    /// @param iterator Iterator to store.
    /// @param end Iterator to the container's end.
    NativeConstIteratorWrapper(Iterator &&iterator, Iterator &&end) noexcept
        : NativeIteratorWrapperBase<Element, Iterator>(std::forward<Iterator>(iterator), std::forward<Iterator>(end))
    {
        InitializeIteratorPointer(m_pointer);
        if (!VirtualizedIteratorBase<Element>::IsEndIterator())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// Destructor.
    virtual ~NativeConstIteratorWrapper() = default;
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IncrementIterator
    void IncrementIterator() override
    {
        if (NativeIteratorWrapperBase<Element, Iterator>::IteratorIncrementImplementation())
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::DecrementIterator
    void DecrementIterator() override
    {
        IteratorDecrementer<Iterator>::decrement(m_iterator);
        VirtualizedIteratorBase<Element>::m_is_end = false;
        UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::ShiftIteratorBy
    void ShiftIteratorBy(std::ptrdiff_t offset) override
    {
        if (NativeIteratorWrapperBase<Element, Iterator>::IteratorShiftImplementation(offset))
            UpdateIteratorPointer(m_pointer, *m_iterator);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceIterator
    Element OffsetDereferenceIterator(std::ptrdiff_t offset) const override
    {
        return IteratorOffsetDereferencer<Iterator, Element>::get(m_iterator, offset);
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceAssignIterator
    void OffsetDereferenceAssignIterator(std::ptrdiff_t, const Element&) const override
    {
        throw System::NotSupportedException(u"Assigning element through const iterator");
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::OffsetDereferenceAssignIterator
    void OffsetDereferenceAssignIterator(std::ptrdiff_t, Element&&) const override
    {
        throw System::NotSupportedException(u"Assigning element through const iterator");
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::CloneIterator
    VirtualizedIteratorBase<Element>* CloneIterator() const override
    {
        return new NativeConstIteratorWrapper(m_iterator, m_end);
    }

    NativeConstIteratorWrapper(NativeConstIteratorWrapper&&) = delete;

private:
    /// Copying constructor.
    /// @param other Instance to copy data from.
    NativeConstIteratorWrapper(const NativeConstIteratorWrapper& other)
        : NativeConstIteratorWrapper(other.m_iterator, other.VirtualizedIteratorBase<Element>::m_end)
    {}
};


/// Base class for virtualized iterators based on enumerators.
/// @tparam Element Element type.
template <typename Element>
class EnumeratorBasedIterator : public VirtualizedIteratorBase<Element>
{
public:
    /// Destructor.
    virtual ~EnumeratorBasedIterator() = default;

    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IteratorEquals
    bool IteratorEquals(VirtualizedIteratorBase<Element> *other) const override
    {
        CODEPORTING_DEBUG_ASSERT(dynamic_cast<EnumeratorBasedIterator*>(other) != nullptr);
        return static_cast<EnumeratorBasedIterator*>(other)->m_offset == m_offset;
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IteratorLess
    bool IteratorLess(VirtualizedIteratorBase<Element> *other) const override
    {
        CODEPORTING_DEBUG_ASSERT(dynamic_cast<EnumeratorBasedIterator*>(other) != nullptr);
        return static_cast<EnumeratorBasedIterator*>(other)->m_offset > m_offset;
    }
    /// Prepares Enumerator's contents to be used as an iterator.
    virtual void InitializeIterator()
    {}

protected:
    /// Constructor.
    EnumeratorBasedIterator()
        : VirtualizedIteratorBase<Element>(false, true)
        , m_offset(std::numeric_limits<std::ptrdiff_t>::max())
    {}
    /// Constructor.
    /// @param offset Number of steps from the begin position, or std::numeric_limits<std::ptrdiff_t>::max() for end position.
    EnumeratorBasedIterator(std::ptrdiff_t offset)
        : VirtualizedIteratorBase<Element>(false, offset == std::numeric_limits<std::ptrdiff_t>::max())
        , m_offset(offset)
    {}
    /// Copy constructor.
    EnumeratorBasedIterator(const EnumeratorBasedIterator &other)
        : VirtualizedIteratorBase<Element>(false, other.m_offset == std::numeric_limits<std::ptrdiff_t>::max())
        , m_offset(other.m_offset)
    {}

    /// Number of MoveNext() calls since last Reset() call for in-container positions, or max possible value for end position.
    std::ptrdiff_t m_offset;
};

/// Special iterator instance which means 'after the end of container iterated through via enumerators'.
/// @param Element Container element type.
template <typename Element>
class EnumeratorBasedEndIterator : public EnumeratorBasedIterator<Element>
{
public:
    /// Constructor.
    EnumeratorBasedEndIterator()
        : EnumeratorBasedIterator<Element>(std::numeric_limits<std::ptrdiff_t>::max())
    {}
    /// Destructor.
    virtual ~EnumeratorBasedEndIterator() = default;

    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::IteratorEquals
    void IncrementIterator() override
    {
        throw InvalidOperationException(u"Moving past the container's end");
    }
    /// @copydoc System::Details::VirtualizedIteratorBase<Element>::CloneIterator
    System::Details::VirtualizedIteratorBase<Element>* CloneIterator() const override
    {
        return new EnumeratorBasedEndIterator();
    }
};


/// Special class needed to support the 'iter[idx]->member' syntax.
/// Holds a local copy of the element being pointed to.
/// @param Element Value type.
template <typename Element>
class VirtualizedIteratorOffsetPointer
{
public:
    /// Constructor.
    /// @param iterator Iterator to offset dereference.
    /// @param offset Offset to the given iterator to get the value from.
    VirtualizedIteratorOffsetPointer(VirtualizedIteratorBase<Element> *iterator, std::ptrdiff_t offset)
        : m_value(iterator->OffsetDereferenceIterator(offset))
    {}
    /// Move constructor.
    /// @param other Instance to move data from.
    VirtualizedIteratorOffsetPointer(VirtualizedIteratorOffsetPointer &&other) noexcept
        : m_value(std::move(other.m_value))
    {}

    /// Structure dereference operator.
    /// @return The pointer returned by the stored element's structure derefefence operator.
    decltype(std::declval<Element>().operator ->()) operator -> () const
    {
        return m_value.operator ->();
    }

    VirtualizedIteratorOffsetPointer(const VirtualizedIteratorOffsetPointer&) = delete;
    VirtualizedIteratorOffsetPointer& operator = (const VirtualizedIteratorOffsetPointer&) = delete;
    VirtualizedIteratorOffsetPointer& operator = (VirtualizedIteratorOffsetPointer&&) = delete;

private:
    /// Element to call structure dereference operator of.
    Element m_value;
};

/// Special class needed to support the 'iter[idx]' syntax.
/// @param Element Value type.
template <typename Element>
class VirtualizedIteratorOffsetReference
{
public:
    /// Constructor.
    /// @param iterator Iterator to offset dereference.
    /// @param offset Offset to the given iterator to access the value from.
    VirtualizedIteratorOffsetReference(VirtualizedIteratorBase<Element> *iterator, std::ptrdiff_t offset)
        : m_iterator(iterator), m_offset(offset)
    {}
    /// Copy constructor.
    VirtualizedIteratorOffsetReference(const VirtualizedIteratorOffsetReference&) = default;
    /// Move constructor.
    VirtualizedIteratorOffsetReference(VirtualizedIteratorOffsetReference&&) noexcept = default;

    /// Element access operator.
    /// @return The element at the given offset to the given iterator.
    operator Element () const
    {
        if (m_offset == 0)
            return *m_iterator->GetElementPointer();
        else
            return m_iterator->OffsetDereferenceIterator(m_offset);
    }
    /// Assignment operator.
    /// @param value Value to copy-assign to the referenced element.
    /// @return This reference.
    VirtualizedIteratorOffsetReference& operator = (const Element &value)
    {
        m_iterator->OffsetDereferenceAssignIterator(m_offset, value);
        return *this;
    }
    /// Assignment operator.
    /// @param value Value to move-assign to the referenced element.
    /// @return This reference.
    VirtualizedIteratorOffsetReference& operator = (Element &&value)
    {
        m_iterator->OffsetDereferenceAssignIterator(m_offset, std::move(value));
        return *this;
    }
    /// Structure dereference operator.
    /// @return Temporary variable used to store and structure dereference the currently referenced value.
    VirtualizedIteratorOffsetPointer<Element> operator -> () const
    {
        return VirtualizedIteratorOffsetPointer<Element>(m_iterator, m_offset);
    }

    VirtualizedIteratorOffsetReference& operator = (const VirtualizedIteratorOffsetReference&) = delete;
    VirtualizedIteratorOffsetReference& operator = (VirtualizedIteratorOffsetReference&&) = delete;

private:
    /// Iterator to offset-dereference.
    VirtualizedIteratorBase<Element> *const m_iterator;
    /// Offset, as calculated to the given iterator.
    const std::ptrdiff_t m_offset;
};


template <typename Element> class VirtualizedConstIterator;

/// Iterator type used by System::Collections::Generic::IEnumerable<T> and duck-typed collections.
/// Holds a pointer to the internal object which implements the actual iterator logic in its virtual methods.
/// Depending on container type, some methods may be unsupported and throw exceptions.
/// @code
/// #include <system/collections/list.h>
/// #include <system/smart_ptr.h>
/// #include <algorithm>
/// #include <iterator>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create the List-class instance.
///   SharedPtr<ICollection<int>> collection = MakeObject<List<int>>();
///
///   // Fill the list.
///   collection->Add(1);
///   collection->Add(2);
///   collection->Add(3);
///
///   // Iterate over the collection using VirtualizedIterator and print items.
///   std::ostream_iterator<int> osi(std::cout, " ");
///   std::copy(collection->begin(), collection->end(), osi);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1 2 3
/// */
/// @endcode
/// @tparam Element Element type.
template <typename Element>
class VirtualizedIterator : public BaseIterator<std::random_access_iterator_tag, Element, std::ptrdiff_t, Element*, Element&>
{
public:
    /// Default constructor.
    /// Dereferencing the iterator created by it is UB.
    VirtualizedIterator() = default;
    /// Copy constructor.
    /// @param other Iterator to copy data from.
    VirtualizedIterator(const VirtualizedIterator &other)
        : m_iterator(other.m_iterator->CloneIterator())
    {}
    /// Move constructor.
    /// @param other Iterator to move data from.
    VirtualizedIterator(VirtualizedIterator &&other) noexcept
        : m_iterator(other.m_iterator.release())
    {}
    /// Constructor.
    /// @param virtualizedIterator Iterator kernel to wrap.
    explicit VirtualizedIterator(VirtualizedIteratorBase<Element> *virtualizedIterator)
        : m_iterator(virtualizedIterator)
    {}

    /// Assignment iterator.
    /// @param other Iterator to copy data from.
    VirtualizedIterator& operator = (const VirtualizedIterator &other)
    {
        m_iterator.reset(other.m_iterator->CloneIterator());
        return *this;
    }
    /// Assignment iterator.
    /// @param other Iterator to move data from.
    VirtualizedIterator& operator = (VirtualizedIterator &&other) noexcept
    {
        m_iterator = std::move(other.m_iterator);
        return *this;
    }

    /// Moves iterator to the next position.
    /// @return This reference.
    VirtualizedIterator& operator ++ ()
    {
        m_iterator->IncrementIterator();
        return *this;
    }
    /// Moves iterator to the previous position.
    /// @return This reference.
    VirtualizedIterator& operator -- ()
    {
        m_iterator->DecrementIterator();
        return *this;
    }
    /// Moves iterator to the next position.
    /// @return The value iterator had before the increment.
    VirtualizedIterator operator ++ (int)
    {
        VirtualizedIterator copy(*this);
        operator++();
        return copy;
    }
    /// Moves iterator to the previous position.
    /// @return The value iterator had before the decrement.
    VirtualizedIterator operator -- (int)
    {
        VirtualizedIterator copy(*this);
        operator --();
        return copy;
    }

    /// Changes iterator position by the given number of steps.
    /// @param offset Number of forward steps to make.
    /// @return This reference.
    VirtualizedIterator& operator += (std::ptrdiff_t offset)
    {
        m_iterator->ShiftIteratorBy(offset);
        return *this;
    }
    /// Changes iterator position by the given number of steps.
    /// @param offset Number of backward steps to make.
    /// @return This reference.
    VirtualizedIterator& operator -= (std::ptrdiff_t offset)
    {
        m_iterator->ShiftIteratorBy(-offset);
        return *this;
    }
    /// Gets the iterator that stays the given number of steps after the current one.
    /// @param offset Number of steps to add to the current iterator.
    /// @return The new iterator which stays off the current one for the given number of steps.
    VirtualizedIterator operator + (std::ptrdiff_t offset) const
    {
        VirtualizedIterator copy(*this);
        copy += offset;
        return copy;
    }
    /// Gets the iterator that stays the given number of steps before the current one.
    /// @param offset Number of steps to subtract from the current iterator.
    /// @return The new iterator which stays off the current one for the given number of steps.
    VirtualizedIterator operator - (std::ptrdiff_t offset) const
    {
        VirtualizedIterator copy(*this);
        copy -= offset;
        return copy;
    }
    /// Gets the number of steps between the current and the given iterators.
    /// @param other Iterator to subtract from the current one.
    /// @return Returns the number of steps to add to @p other iterator to make it equal to the current one.
    std::ptrdiff_t operator - (const VirtualizedIterator &other) const
    {
        return m_iterator->DiffIterators(other.m_iterator.get());
    }

    /// Accesses element being referenced by the current iterator.
    /// @return Reference to the container element or its copy.
    Element& operator * () const
    {
        return *m_iterator->GetElementPointer();
    }
    /// Accesses members of the element being referenced by the current iterator.
    /// @return Pointer to the container element or its copy.
    Element* operator -> () const
    {
        return m_iterator->GetElementPointer();
    }
    /// Accesses element via the given offset calculated to the currently referenced one.
    /// @param offset Number of the steps to make from the currently referenced element.
    /// @return Accessor referencing the specified element.
    VirtualizedIteratorOffsetReference<Element> operator [] (std::ptrdiff_t offset) const
    {
        return VirtualizedIteratorOffsetReference<Element>(m_iterator.get(), offset);
    }

    /// Equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if two iterators point to the same element, false otherwise.
    bool operator == (const VirtualizedIterator &other) const
    {
        if (m_iterator->IsEndIterator() != other.m_iterator->IsEndIterator())
            return false;
        else if (m_iterator->IsEndIterator())
            return true;
        else
            return m_iterator->IteratorEquals(other.m_iterator.get());
    }
    /// Unequal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if two iterators point to the same element, true otherwise.
    bool operator != (const VirtualizedIterator &other) const
    {
        if (m_iterator->IsEndIterator() != other.m_iterator->IsEndIterator())
            return true;
        else if (m_iterator->IsEndIterator())
            return false;
        else
            return !m_iterator->IteratorEquals(other.m_iterator.get());
    }
    /// Less-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if the current iterator precedes the @p other one, false otherwise.
    bool operator < (const VirtualizedIterator &other) const
    {
        if (other.m_iterator->IsEndIterator())
            return !m_iterator->IsEndIterator();
        else
            return m_iterator->IteratorLess(other.m_iterator.get());
    }
    /// Greater-or-equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if the current iterator precedes the @p other one, true otherwise.
    bool operator >= (const VirtualizedIterator &other) const
    {
        return !(*this < other);
    }
    /// Greater-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if the @p other iterator precedes the current one, false otherwise.
    bool operator > (const VirtualizedIterator &other) const
    {
        return other < *this;
    }
    /// Greater-or-equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if the @p other iterator precedes the current one, true otherwise.
    bool operator <= (const VirtualizedIterator &other) const
    {
        return !(other < *this);
    }

    /// Swaps the actual values held by the current and the given iterators.
    /// @param other Iterator to swap with the current one.
    void swap(VirtualizedIterator &other)
    {
        std::swap(m_iterator, other.m_iterator);
    }

private:
    /// Actual iterator implementation.
    std::unique_ptr<VirtualizedIteratorBase<std::remove_const_t<Element>>> m_iterator;

    friend class VirtualizedConstIterator<Element>;
};

/// Const iterator type used by System::Collections::Generic::IEnumerable<T> and duck-typed collections.
/// Holds a pointer to the internal object which implements the actual iterator logic in its virtual methods.
/// Depending on container type, some methods may be unsupported and throw exceptions.
/// @code
/// #include <system/collections/list.h>
/// #include <system/smart_ptr.h>
/// #include <algorithm>
/// #include <iterator>
///
/// using namespace System;
/// using namespace System::Collections::Generic;
///
/// int main()
/// {
///   // Create the List-class instance.
///   auto collection = MakeObject<List<int>>();
///   const IEnumerable<int> *enumerable = collection.get();
///
///   // Fill the list.
///   collection->Add(1);
///   collection->Add(2);
///   collection->Add(3);
///
///   // Iterate over the collection using VirtualizedConstIterator and print items.
///   std::ostream_iterator<int> osi(std::cout, " ");
///   std::copy(enumerable->begin(), enumerable->end(), osi);
///
///   return 0;
/// }
/// /*
/// This code example produces the following output:
/// 1 2 3
/// */
/// @endcode
/// @tparam Element Element type.
template <typename Element>
class VirtualizedConstIterator : public BaseIterator<std::random_access_iterator_tag, Element, std::ptrdiff_t, const Element*, const Element&>
{
public:
    /// Default constructor.
    /// Dereferencing the iterator created by it is UB.
    VirtualizedConstIterator()
        : m_iterator(nullptr)
    {}
    /// Copy constructor.
    /// @param other Iterator to copy data from.
    VirtualizedConstIterator(const VirtualizedConstIterator &other)
        : m_iterator(other.m_iterator->CloneIterator())
    {}
    /// Move constructor.
    /// @param other Iterator to move data from.
    VirtualizedConstIterator(VirtualizedConstIterator &&other) noexcept
        : m_iterator(other.m_iterator.release())
    {}
    /// Copy constructor.
    /// @param other Iterator to copy data from.
    VirtualizedConstIterator(const VirtualizedIterator<Element> &other)
        : m_iterator(other.m_iterator->CloneIterator())
    {}
    /// Move constructor.
    /// @param other Iterator to move data from.
    VirtualizedConstIterator(VirtualizedIterator<Element> &&other) noexcept
        : m_iterator(other.m_iterator.release())
    {}
    /// Constructor.
    /// @param virtualizedIterator Iterator kernel to wrap.
    explicit VirtualizedConstIterator(VirtualizedIteratorBase<Element> *virtualizedIterator)
        : m_iterator(virtualizedIterator)
    {}

    /// Assignment iterator.
    /// @param other Iterator to copy data from.
    VirtualizedConstIterator& operator = (const VirtualizedConstIterator &other)
    {
        m_iterator.reset(other.m_iterator->CloneIterator());
        return *this;
    }
    /// Assignment iterator.
    /// @param other Iterator to move data from.
    VirtualizedConstIterator& operator = (VirtualizedConstIterator &&other) noexcept
    {
        m_iterator = std::move(other.m_iterator);
        return *this;
    }

    /// Moves iterator to the next position.
    /// @return This reference.
    VirtualizedConstIterator& operator ++ ()
    {
        m_iterator->IncrementIterator();
        return *this;
    }
    /// Moves iterator to the previous position.
    /// @return This reference.
    VirtualizedConstIterator& operator -- ()
    {
        m_iterator->DecrementIterator();
        return *this;
    }
    /// Moves iterator to the next position.
    /// @return The value iterator had before the increment.
    VirtualizedConstIterator operator ++ (int)
    {
        VirtualizedConstIterator copy(*this);
        operator++();
        return copy;
    }
    /// Moves iterator to the previous position.
    /// @return The value iterator had before the decrement.
    VirtualizedConstIterator operator -- (int)
    {
        VirtualizedConstIterator copy(*this);
        operator --();
        return copy;
    }

    /// Changes iterator position by the given number of steps.
    /// @param offset Number of forward steps to make.
    /// @return This reference.
    VirtualizedConstIterator& operator += (std::ptrdiff_t offset)
    {
        m_iterator->ShiftIteratorBy(offset);
        return *this;
    }
    /// Changes iterator position by the given number of steps.
    /// @param offset Number of backward steps to make.
    /// @return This reference.
    VirtualizedConstIterator& operator -= (std::ptrdiff_t offset)
    {
        m_iterator->ShiftIteratorBy(-offset);
        return *this;
    }
    /// Gets the iterator that stays the given number of steps after the current one.
    /// @param offset Number of steps to add to the current iterator.
    /// @return The new iterator which stays off the current one for the given number of steps.
    VirtualizedConstIterator operator + (std::ptrdiff_t offset) const
    {
        VirtualizedConstIterator copy(*this);
        copy += offset;
        return copy;
    }
    /// Gets the iterator that stays the given number of steps before the current one.
    /// @param offset Number of steps to subtract from the current iterator.
    /// @return The new iterator which stays off the current one for the given number of steps.
    VirtualizedConstIterator operator - (std::ptrdiff_t offset) const
    {
        VirtualizedConstIterator copy(*this);
        copy -= offset;
        return copy;
    }
    /// Gets the number of steps between the current and the given iterators.
    /// @param other Iterator to subtract from the current one.
    /// @return Returns the number of steps to add to @p other iterator to make it equal to the current one.
    std::ptrdiff_t operator - (const VirtualizedConstIterator &other) const
    {
        return m_iterator->DiffIterators(other.m_iterator.get());
    }

    /// Accesses element being referenced by the current iterator.
    /// @return Reference to the container element or its copy.
    const Element& operator * () const
    {
        return *m_iterator->GetElementPointer();
    }
    /// Accesses members of the element being referenced by the current iterator.
    /// @return Pointer to the container element or its copy.
    const Element* operator -> () const
    {
        return m_iterator->GetElementPointer();
    }
    /// Accesses element via the given offset calculated to the currently referenced one.
    /// @param offset Number of the steps to make from the currently referenced element.
    /// @return The specified element.
    Element operator [] (std::ptrdiff_t offset) const
    {
        if (offset == 0)
            return *m_iterator->GetElementPointer();
        else
            return m_iterator->OffsetDereferenceIterator(offset);
    }

    /// Equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if two iterators point to the same element, false otherwise.
    bool operator == (const VirtualizedConstIterator &other) const
    {
        if (m_iterator->IsEndIterator() != other.m_iterator->IsEndIterator())
            return false;
        else if (m_iterator->IsEndIterator())
            return true;
        else
            return m_iterator->IteratorEquals(other.m_iterator.get());
    }
    /// Unequal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if two iterators point to the same element, true otherwise.
    bool operator != (const VirtualizedConstIterator &other) const
    {
        if (m_iterator->IsEndIterator() != other.m_iterator->IsEndIterator())
            return true;
        else if (m_iterator->IsEndIterator())
            return false;
        else
            return !m_iterator->IteratorEquals(other.m_iterator.get());
    }
    /// Less-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if the current iterator precedes the @p other one, false otherwise.
    bool operator < (const VirtualizedConstIterator &other) const
    {
        if (other.m_iterator->IsEndIterator())
            return !m_iterator->IsEndIterator();
        else
            return m_iterator->IteratorLess(other.m_iterator.get());
    }
    /// Greater-or-equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if the current iterator precedes the @p other one, true otherwise.
    bool operator >= (const VirtualizedConstIterator &other) const
    {
        return !(*this < other);
    }
    /// Greater-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return True if the @p other iterator precedes the current one, false otherwise.
    bool operator > (const VirtualizedConstIterator &other) const
    {
        return other < *this;
    }
    /// Greater-or-equal-compares current and given iterators.
    /// @param other Iterator to compare to the current one.
    /// @return False if the @p other iterator precedes the current one, true otherwise.
    bool operator <= (const VirtualizedConstIterator &other) const
    {
        return !(other < *this);
    }

    /// Swaps the actual values held by the current and the given iterators.
    /// @param other Iterator to swap with the current one.
    void swap(VirtualizedConstIterator &other)
    {
        std::swap(m_iterator, other.m_iterator);
    }

private:
    /// Actual iterator implementation.
    std::unique_ptr<VirtualizedIteratorBase<std::remove_const_t<Element>>> m_iterator;
};

/// Shifts the given iterator by the given number of steps.
/// @tparam Element Iterator element type.
/// @param offset Number of steps to shift iterator by.
/// @param iterator Iterator to shift.
/// @return The iterator that stays @p offset steps after @p iterator.
template <typename Element>
VirtualizedIterator<Element> operator + (std::ptrdiff_t offset, const VirtualizedIterator<Element> &iterator)
{
    return iterator + offset;
}
/// Shifts the given iterator by the given number of steps.
/// @tparam Element Iterator element type.
/// @param offset Number of steps to shift iterator by.
/// @param iterator Iterator to shift.
/// @return The iterator that stays @p offset steps after @p iterator.
template <typename Element>
VirtualizedConstIterator<Element> operator + (std::ptrdiff_t offset, const VirtualizedConstIterator<Element> &iterator)
{
    return iterator + offset;
}

}} // namespace System::Details

using System::Details::operator +;

namespace std
{

/// Swaps two iterators.
/// @tparam Element Iterator element type.
/// @param lhs First iterator to swap.
/// @param rhs Second iterator to swap.
template <typename Element>
void swap(System::Details::VirtualizedIterator<Element> &lhs, System::Details::VirtualizedIterator<Element> &rhs)
{
    lhs.swap(rhs);
}
/// Swaps two iterators.
/// @tparam Element Iterator element type.
/// @param lhs First iterator to swap.
/// @param rhs Second iterator to swap.
template <typename Element>
void swap(System::Details::VirtualizedConstIterator<Element> &lhs, System::Details::VirtualizedConstIterator<Element> &rhs)
{
    lhs.swap(rhs);
}

}
