/// @file system/collections/ienumerable.h
#pragma once

#include <iterator>
#include <memory>

#include <system/collections/ienumerator.h>
#include <system/collections/virtualized_iterator.h>
#include <system/func.h>
#include <system/linq/igrouping.h>

namespace System { namespace Linq {
template <typename T> class IOrderedEnumerable;
}}

namespace System { namespace Collections { namespace Generic {

template<typename T> class ASPOSECPP_SHARED_CLASS List;
template<typename T> class EnumerableExt;

/// Interface of object providing enumerator on contained elements.
/// @tparam T Element type.
template<typename T>
class ASPOSECPP_SHARED_CLASS IEnumerable: virtual public Object
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(System::Collections::Generic::IEnumerable<T>, System::BaseTypesInfo<System::Object>);

public:
    /// Enumerator type.
    typedef IEnumerator<T> IEnumeratorType;

    using ValueType = T;

    // There no need to define an empty virtual dtor, virtual dtor for inheritance already defined in the Object class
    /// Gets enumerator.
    /// @return Pointer to newly created enumerator object which can be used to iterate through interfaced object.
    virtual SharedPtr<IEnumerator<T> > GetEnumerator() = 0;

    // Implementation of some of LINQ extension methods as usual class methods
    // header <system/linq/enumerable.h> should be included in order to use

    /// Applies an accumulator function over a sequence.
    /// @param func An accumulator function to be invoked on each element.
    /// @return The final accumulator value.
    T LINQ_Aggregate(const Func<T, T, T>& func);

    /// Returns the element at a specified index in a sequence.
    /// @param index Index to get element at.
    /// @return Element at specified index.
    T LINQ_ElementAt(int index);

    /// Returns the element at a specified index in a sequence.
    /// @param index Index to get element at.
    /// @return Element at specified index or default-constructed value if not found.
    T LINQ_ElementAtOrDefault(int index);

    /// Returns the first element of a sequence.
    /// @return First element in the sequence.
    /// @throws InvalidOperationException Source sequence is empty.
    T LINQ_First();

    /// Returns the first element of a sequence that satisfy the specified condition.
    /// @param predicate A function to test each element for a condition.
    /// @return First element in the sequence that satisfy the specified condition.
    /// @throws InvalidOperationException No element satisfy the specified condition.
    T LINQ_First(const Func<T, bool>& predicate);

    /// Returns the first element of a sequence, or a default value if the sequence is empty.
    /// @return First element in the sequence or default-constructed value if the sequence is empty.
    T LINQ_FirstOrDefault();

    /// Returns the first element of the sequence that satisfies a condition or a default value if no such element is
    /// found.
    /// @param predicate A function to test each element for a condition.
    /// @return default(T) if source is empty or if no element passes the test specified by predicate; otherwise,
    /// the first element in source that passes the test specified by predicate.
    T LINQ_FirstOrDefault(std::function<bool(T)> predicate);

    /// Returns the last element of a sequence.
    /// @return Last element in the sequence.
    /// @throws InvalidOperationException Source sequence is empty.
    T LINQ_Last();

    /// Returns the last element of a sequence, or a default value if the sequence is empty.
    /// @return Last element in the sequence or default-constructed value if the sequence is empty.
    T LINQ_LastOrDefault();

    /// Creates a List<T> from a sequence.
    /// @return The list containing all elements of specified sequence.
    SharedPtr<List<T>> LINQ_ToList();

    /// Returns the number of elements in the sequence (calculated via direct counting).
    /// @return Number of elements in the sequence.
    int LINQ_Count();

    /// Returns the number of elements in the sequence that satisfy the specified condition.
    /// @param predicate A function to test each element for a condition.
    /// @return Number of elements in the sequence that satisfy the specified condition.
    int LINQ_Count(const Func<T, bool>& predicate);

    /// Creates an array from a sequence.
    /// @return Array that contains all elements of current sequence.
    System::ArrayPtr<T> LINQ_ToArray();

    /// Determines whether all elements of a sequence satisfy a condition.
    /// @param predicate A function to test each element for a condition.
    /// @return true if every element of the source sequence passes the test in the specified predicate, or if the
    /// sequence is empty; otherwise, false.
    bool LINQ_All(std::function<bool(T)> predicate);

    /// Determines whether a sequence contains any elements.
    /// @return true if the source sequence contains any elements; otherwise, false.
    bool LINQ_Any();

    /// Determines whether any element of a sequence exists or satisfies a condition.
    /// @param predicate A function to test each element for a condition.
    /// @return true if the source sequence contains any elements; otherwise, false.
    bool LINQ_Any(std::function<bool(T)> predicate);

    /// Filters a sequence based on the specified predicate.
    /// @param predicate A function that test each elements for some condition.
    /// @return An IEnumerable that contains filtered elements.
    SharedPtr<IEnumerable<T>> LINQ_Where(std::function<bool(T)> predicate);

    /// Determines if a sequence contains a specified value.
    /// @param value The value to locate in the sequence.
    /// @return true if the sequence contains the specified value, otherwise false.
    bool LINQ_Contains(T value);

    /// Casts the elements to the specified type.
    /// @tparam ResultType The type to cast the elements of the sequence.
    /// @return An IEnumerable that contains elements of the sequence cast the ResultType.
    /// @throws InvalidCastException Element of the sequence cannot be cast to the ResultType.
    template <typename ResultType>
    SharedPtr<IEnumerable<ResultType>> LINQ_Cast();

    /// Sorts the elements of a sequence in ascending order according to the key values selected by keySelector
    /// @tparam keySelector A function to extract a key from an element.
    /// @return An IOrderedEnumerable whose elements are sorted according to a key
    template <typename Key>
    SharedPtr<Linq::IOrderedEnumerable<T>> LINQ_OrderBy(const Func<T, Key>& keySelector);

    /// Sorts the elements of a sequence in descending order according to the key values selected by keySelector
    /// @tparam keySelector A function to extract a key from an element.
    /// @return An IOrderedEnumerable whose elements are sorted to the descending order of the key
    template <typename Key>
    SharedPtr<Linq::IOrderedEnumerable<T>> LINQ_OrderByDescending(const Func<T, Key>& keySelector);

    /// Filters the elements of the sequence based on the specified type.
    /// @tparam ResultType The type to filter the elements of the sequence.
    /// @return An IEnumerable that contains elements from the sequence of the ResultType.
    template <typename ResultType>
    SharedPtr<IEnumerable<ResultType>> LINQ_OfType();

    /// Transforms elements of a sequence.
    /// @tparam ResultType The type of the value returned by the @p selector.
    /// @param selector A transform function.
    /// @return An IEnumerable that contains elements returned by the @p selector function.
    template <typename ResultType>
    SharedPtr<IEnumerable<ResultType>> LINQ_Select(const Func<T, ResultType>& selector);

    /// Transforms each element of a sequence into a new form by incorporating the element's index.
    /// @tparam ResultType The type of the value returned by the @p selector.
    /// @param selector A transform function.
    /// @return An IEnumerable that contains elements returned by the @p selector function.
    template <typename ResultType>
    SharedPtr<IEnumerable<ResultType>> LINQ_Select(const Func<T, int32_t, ResultType>& selector);

    /// Concatenates two sequences.
    /// @param sequence The sequence will be concatenated with the current one.
    /// @return An IEnumerable that contains the concatenated elements of the two input sequences.
    SharedPtr<IEnumerable<T>> LINQ_Concat(SharedPtr<IEnumerable<T>> sequence);

    /// Inverts the order of the elements in a sequence.
    /// @return A sequence whose elements correspond to those of the input sequence in reverse order.
    SharedPtr<IEnumerable<T>> LINQ_Reverse();

    /// Groups the elements of a sequence.
    /// @tparam Key The type of the key returned by keyPredicate
    /// @param keyPredicate A function to extract the key for each element.
    /// @return An IEnumerable that contains a sequence of objects and a key
    template <typename Key>
    System::SharedPtr<IEnumerable<System::SharedPtr<System::Linq::IGrouping<Key, T>>>>
        LINQ_GroupBy(System::Func<T, Key> keyPredicate);

    /// Groups the elements of a sequence.
    /// @tparam Key The type of the key returned by keyPredicate
    /// @tparam Element The type of the element returned by elementSelector
    /// @param keyPredicate A function to extract the key for each element.
    /// @param elementSelector A function to extract value key for each element.
    /// @return An IEnumerable that contains a sequence of objects and a key
    template <typename Key, typename Element>
    System::SharedPtr<IEnumerable<System::SharedPtr<System::Linq::IGrouping<Key, Element>>>>
        LINQ_GroupBy(System::Func<T, Key> keyPredicate, System::Func<T, Element> elementSelector);

    /// Projects each element of a sequence and combines the resulting sequences into one sequence.
    /// @tparam ResultType The type of the value returned by the @p selector.
    /// @param selector A transform function.
    /// @return An IEnumerable that contains the result of invoking a one-to-many projection function on each element of the input sequence.
    template <typename ResultType>
    SharedPtr<IEnumerable<ResultType>> LINQ_SelectMany(const Func<T, SharedPtr<IEnumerable<ResultType>>>& selector);

    /// Returns a specified number of contiguous elements from the start of a sequence.
    /// @param count The number of elements to return.
    /// @return An System.Collections.Generic.IEnumerable that contains the specified number of elements from the start of the input sequence.
    SharedPtr<IEnumerable<T>> LINQ_Take(int32_t count);

    /// Invokes a transform function on each element of a generic sequence and returns the minimum resulting value.
    /// @param selector A transform function to apply to each element.
    /// @tparam ResultType The type of the value returned by selector.
    /// @return The minimum value in the sequence.
    template <typename ResultType>
    ResultType LINQ_Min(const Func<T, ResultType>& selector);

    /// Invokes a transform function on each element of a generic sequence and returns the maximum resulting value.
    /// @param selector A transform function to apply to each element.
    /// @tparam ResultType The type of the value returned by selector.
    /// @return The maximum value in the sequence.
    template <typename ResultType>
    ResultType LINQ_Max(const Func<T, ResultType>& selector);

    /// Iterator type.
    using iterator = System::Details::VirtualizedIterator<T>;
    /// Const iterator type.
    using const_iterator = System::Details::VirtualizedConstIterator<T>;

    /// Gets iterator pointing to the first element (if any) of the collection.
    /// This iterator can't be used to change a referenced object because
    /// GetEnumerator() returns a copy-object of T.
    /// @return An iterator pointing to the first element (if any) of the collection
    iterator begin()
    {
        return iterator(virtualizeBeginIterator());
    }
    /// Gets iterator pointing right after the last element (if any) of the collection.
    /// This iterator can't be used to change a referenced object because
    /// GetEnumerator() returns a copy-object of T.
    /// @return An iterator pointing right after the last element (if any) of the collection
    iterator end()
    {
        return iterator(virtualizeEndIterator());
    }

    /// Gets iterator pointing to the first element (if any) of the const-qualified instance of the collection.
    /// @return An iterator pointing to the first element (if any) of the const-qualified instance of the collection
    const_iterator begin() const
    {
        return const_iterator(virtualizeBeginConstIterator());
    }
    /// Gets iterator pointing right after the last element (if any) of the const-qualified instance of the collection.
    /// @return An iterator pointing right after the last element (if any) of the const-qualified instance of the
    /// collection
    const_iterator end() const
    {
        return const_iterator(virtualizeEndConstIterator());
    }

    /// Gets iterator pointing to the first const-qualified element (if any) of the collection.
    /// @return An iterator pointing to the first const-qualified element (if any) of the collection
    const_iterator cbegin() const
    {
        return const_iterator(virtualizeBeginConstIterator());
    }
    /// Gets iterator pointing right after the last const-qualified element (if any) of the collection.
    /// @return An iterator pointing right after the last const-qualified element (if any) of the collection
    const_iterator cend() const
    {
        return const_iterator(virtualizeEndConstIterator());
    }

    /// Inner iterator base type.
    using virtualized_iterator = System::Details::VirtualizedIteratorBase<T>;
    /// Inner iterator element type.
    using virtualized_iterator_element = T;

    /// Gets the implementation of begin iterator for the current container.
    /// @return Pointer to the newly created iterator kernel object.
    virtual virtualized_iterator* virtualizeBeginIterator()
    {
        return GetEnumeratorAsVirtualizedIterator();
    }
    /// Gets the implementation of end iterator for the current container.
    /// @return Pointer to the newly created iterator kernel object.
    virtual virtualized_iterator* virtualizeEndIterator()
    {
        return new System::Details::EnumeratorBasedEndIterator<T>();
    }
    /// Gets the implementation of begin const iterator for the current container.
    /// @return Pointer to the newly created iterator kernel object.
    virtual virtualized_iterator* virtualizeBeginConstIterator() const
    {
        return GetEnumeratorAsVirtualizedIterator();
    }
    /// Gets the implementation of end const iterator for the current container.
    /// @return Pointer to the newly created iterator kernel object.
    virtual virtualized_iterator* virtualizeEndConstIterator() const
    {
        return new System::Details::EnumeratorBasedEndIterator<T>();
    }

protected:
    /// Destructor.
    ~IEnumerable() override {}

    /// Gets enumerator instance and prepares it to be used as iterator kernel.
    /// @return Pointer to the newly created iterator kernel object.
    virtualized_iterator* GetEnumeratorAsVirtualizedIterator()
    {
        IEnumerator<T> *iterator;
        {
            auto enumerator = GetEnumerator();
            if (enumerator->SharedCount() != 1)
            {
                enumerator->InitializeIterator();
                return new EnumeratorWrapperIterator<T>(enumerator);
            }
            iterator = enumerator->AsVirtualizedIterator();
        }
        iterator->MarkOwnedByVirtualizedIterator();
        return iterator;
    }
    /// Gets enumerator instance and prepares it to be used as iterator kernel.
    /// @return Pointer to the newly created iterator kernel object.
    virtualized_iterator* GetEnumeratorAsVirtualizedIterator() const
    {
        return const_cast<IEnumerable<T>*>(this)->GetEnumeratorAsVirtualizedIterator();
    }
};

}}} // namespace System::Collections::Generic
