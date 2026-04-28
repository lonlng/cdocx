//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtListItemCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/list.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Markup
{

class SdtListItem;

}

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerator;
}
}
}

namespace Aspose {

namespace Words {

namespace Markup {

/// Provides access to <see cref="Aspose::Words::Markup::SdtListItem">SdtListItem</see> elements of a structured document tag.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SdtListItemCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::SdtListItem>>
{
    typedef SdtListItemCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Markup::SdtListItem>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::List<System::SharedPtr<Aspose::Words::Markup::SdtListItem>>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Specifies currently selected value in this list.
    /// Null value allowed, meaning that no currently selected entry is associated with this list item collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::SdtListItem> get_SelectedValue();
    /// Specifies currently selected value in this list.
    /// Null value allowed, meaning that no currently selected entry is associated with this list item collection.
    ASPOSE_WORDS_SHARED_API void set_SelectedValue(const System::SharedPtr<Aspose::Words::Markup::SdtListItem>& value);
    /// Gets number of items in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Markup::SdtListItem>>> GetEnumerator() override;
    /// Adds an item to this collection.
    ASPOSE_WORDS_SHARED_API void Add(const System::SharedPtr<Aspose::Words::Markup::SdtListItem>& item);
    /// Removes a list item at the specified index.
    /// 
    /// @param index The zero-based index of the item to remove.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Clears all items from this collection.
    ASPOSE_WORDS_SHARED_API void Clear();

    /// Returns a <see cref="Aspose::Words::Markup::SdtListItem">SdtListItem</see> object given its zero-based index in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Markup::SdtListItem> idx_get(int32_t index);

    ASPOSE_WORDS_SHARED_API iterator begin() noexcept;

    ASPOSE_WORDS_SHARED_API iterator end() noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator begin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator end() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cbegin() const noexcept;

    ASPOSE_WORDS_SHARED_API const_iterator cend() const noexcept;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndIterator() override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeBeginConstIterator() const override;

    ASPOSE_WORDS_SHARED_API virtualized_iterator* virtualizeEndConstIterator() const override;

protected:

    SdtListItemCollection();

    virtual ASPOSE_WORDS_SHARED_API ~SdtListItemCollection();

private:

    __TypeStub<4,4,4,4>::type mField0;
    System::SharedPtr<System::Object> mField1;
    System::String mField2;
    System::SharedPtr<System::Object> mField3;

};

}
}
}
