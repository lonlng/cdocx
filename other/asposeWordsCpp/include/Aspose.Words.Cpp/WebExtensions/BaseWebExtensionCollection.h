//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WebExtensions/BaseWebExtensionCollection.h
#pragma once

#include <system/object_ext.h>
#include <system/exceptions.h>
#include <system/details/pointer_collection_helpers.h>
#include <system/constraints.h>
#include <system/collections/list.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace WebExtensions {

/// Base class for <see cref="Aspose::Words::WebExtensions::TaskPaneCollection">TaskPaneCollection</see>, <see cref="Aspose::Words::WebExtensions::WebExtensionBindingCollection">WebExtensionBindingCollection</see>,
/// <see cref="Aspose::Words::WebExtensions::WebExtensionPropertyCollection">WebExtensionPropertyCollection</see> and <see cref="Aspose::Words::WebExtensions::WebExtensionReferenceCollection">WebExtensionReferenceCollection</see> collections.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/work-with-office-add-ins/">Work with Office Add-ins</a> documentation article.
/// 
/// @tparam T Type of a collection item.
template<typename T>
class ASPOSE_WORDS_SHARED_CLASS BaseWebExtensionCollection : public System::Collections::Generic::IEnumerable<T>
{
    assert_is_cs_class(T);

    typedef BaseWebExtensionCollection<T> ThisType;
    typedef System::Collections::Generic::IEnumerable<T> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_TEMPLATE_CLASS(ThisType, ThisTypeBaseTypesInfo);

    template<typename FT0> friend class Aspose::Words::WebExtensions::BaseWebExtensionCollection;

public:

    using iterator_holder_type = System::Collections::Generic::List<T>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    int32_t get_Count()
    {
        return mItems->get_Count();
    }

    /// Gets or sets an item at the specified index.
    /// 
    /// @param index Zero-based index of the item.
    T idx_get(int32_t index)
    {
        return mItems->idx_get(index);
    }

    /// Gets or sets an item at the specified index.
    /// 
    /// @param index Zero-based index of the item.
    void idx_set(int32_t index, T value)
    {
        mItems->idx_set(index, value);
    }

    /// Adds specified item to the collection.
    /// 
    /// @param item Item for adding.
    void Add(T item)
    {
        if (item == nullptr)
        {
            throw System::ArgumentNullException(u"item");
        }

        mItems->Add(item);
    }

    /// Removes all elements from the collection.
    void Clear()
    {
        mItems->Clear();
    }

    /// Removes the item at the specified index from the collection.
    /// 
    /// @param index The zero-based index of the collection item.
    void Remove(int32_t index)
    {
        mItems->RemoveAt(index);
    }

    /// Returns an enumerator that can iterate through a collection.
    System::SharedPtr<System::Collections::Generic::IEnumerator<T>> GetEnumerator() override
    {
        return mItems->GetEnumerator();
    }

    BaseWebExtensionCollection() : mItems(System::MakeObject<System::Collections::Generic::List<T>>())
    {
    }

    iterator begin() noexcept
    {
        return mItems->begin();
    }

    iterator end() noexcept
    {
        return mItems->end();
    }

    const_iterator begin() const noexcept
    {
        return mItems->cbegin();
    }

    const_iterator end() const noexcept
    {
        return mItems->cend();
    }

    const_iterator cbegin() const noexcept
    {
        return mItems->cbegin();
    }

    const_iterator cend() const noexcept
    {
        return mItems->cend();
    }

    virtualized_iterator* virtualizeBeginIterator() override
    {
        return mItems->virtualizeBeginIterator();
    }

    virtualized_iterator* virtualizeEndIterator() override
    {
        return mItems->virtualizeEndIterator();
    }

    virtualized_iterator* virtualizeBeginConstIterator() const override
    {
        return mItems->virtualizeBeginConstIterator();
    }

    virtualized_iterator* virtualizeEndConstIterator() const override
    {
        return mItems->virtualizeEndConstIterator();
    }

    void SetTemplateWeakPtr(uint32_t argument) override
    {
        switch (argument)
        {
            case 0:
                System::Details::CollectionHelpers::SetWeakPointer(0, mItems);
                break;

        }
    }

protected:

    T get_First()
    {
        return (mItems->get_Count() > 0) ? mItems->idx_get(0) : nullptr;
    }

    T get_Last()
    {
        return (mItems->get_Count() > 0) ? mItems->idx_get(mItems->get_Count() - 1) : nullptr;
    }

    virtual ~BaseWebExtensionCollection()
    {
    }

private:

    System::SharedPtr<System::Collections::Generic::List<T>> mItems;

};

}
}
}
