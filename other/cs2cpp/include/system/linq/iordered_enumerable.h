/// @file system/linq/iordered_enumerable.h
#pragma once

#include <iterator>
#include <memory>

#include <system/collections/ienumerable.h>

namespace System { namespace Linq {

/// Represents a sorted sequence
/// @tparam T The type of the elements of the sequence.
template<typename T>
class ASPOSECPP_SHARED_CLASS IOrderedEnumerable : public System::Collections::Generic::IEnumerable<T>
{
    /// RTTI information.
    RTTI_INFO_TEMPLATE_CLASS(IOrderedEnumerable, System::BaseTypesInfo<System::Collections::Generic::IEnumerable<T>>);

public:
    using Comparator = std::function<bool(const T&, const T&)>;

    IOrderedEnumerable(const System::SharedPtr<System::Collections::Generic::IEnumerable<T>>& root, const Comparator& comp)
        : m_root(root), m_comparator(comp)
    {
    }

    virtual SharedPtr<System::Collections::Generic::IEnumerator<T>> GetEnumerator() override
    {
        return m_root->GetEnumerator();
    }

    /// Performs a subsequent ordering of the elements in a sequence in ascending order according to a key
    /// @param keySelector A function to extract a key from each element.
    /// @tparam Key The type of the key returned by keySelector.
    /// @return System::Linq::IOrderedEnumerable whose elements are sorted according to a key.
    template <typename Key>
    SharedPtr<IOrderedEnumerable<T>> LINQ_ThenBy(const Func<T, Key>& keySelector);

protected:
    System::SharedPtr<System::Collections::Generic::IEnumerable<T>> m_root;
    Comparator m_comparator;
};

}} // namespace System::Linq
