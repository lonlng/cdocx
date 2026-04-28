//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/BookmarksOutlineLevelCollection.h
#pragma once

#include <system/string.h>
#include <system/collections/sorted_list.h>
#include <system/collections/keyvalue_pair.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

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

namespace Saving {

/// A collection of individual bookmarks outline level.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-bookmarks/">Working with Bookmarks</a> documentation article.
/// 
/// Key is a case-insensitive string bookmark name. Value is a int bookmark outline level.
/// 
/// Bookmark outline level may be a value from 0 to 9. Specify 0 and Word bookmark will not be displayed in the document outline.
/// Specify 1 and Word bookmark will be displayed in the document outline at level 1; 2 for level 2 and so on.
class ASPOSE_WORDS_SHARED_CLASS BookmarksOutlineLevelCollection : public System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, int32_t>>
{
    typedef BookmarksOutlineLevelCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::Collections::Generic::KeyValuePair<System::String, int32_t>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    using iterator_holder_type = System::Collections::Generic::SortedList<System::String, int32_t>;

    using iterator = typename iterator_holder_type::iterator;

    using const_iterator = typename iterator_holder_type::const_iterator;

    using virtualized_iterator_element = typename iterator_holder_type::virtualized_iterator_element;

    using virtualized_iterator = typename iterator_holder_type::virtualized_iterator;

public:

    /// Gets the number of elements contained in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Gets or a sets a bookmark outline level by the bookmark name.
    /// 
    /// @param name Case-insensitive name of the bookmark.
    /// 
    /// @return The outline level of the bookmark. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API int32_t idx_get(const System::String& name);
    /// Gets or a sets a bookmark outline level by the bookmark name.
    /// 
    /// @param name Case-insensitive name of the bookmark.
    /// 
    /// @return The outline level of the bookmark. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API void idx_set(const System::String& name, int32_t value);
    /// Gets or sets a bookmark outline level at the specified index.
    /// 
    /// @param index Zero-based index of the bookmark.
    /// 
    /// @return The outline level of the bookmark. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API int32_t idx_get(int32_t index);
    /// Gets or sets a bookmark outline level at the specified index.
    /// 
    /// @param index Zero-based index of the bookmark.
    /// 
    /// @return The outline level of the bookmark. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API void idx_set(int32_t index, int32_t value);

    /// Adds a bookmark to the collection.
    /// 
    /// @param name The case-insensitive name of the bookmark to add.
    /// @param outlineLevel The outline level of the bookmark. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API void Add(const System::String& name, int32_t outlineLevel);
    /// Determines whether the collection contains a bookmark with the given name.
    /// 
    /// @param name Case-insensitive name of the bookmark to locate.
    /// 
    /// @return <c>%true</c> if item is found in the collection; otherwise, <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool Contains(const System::String& name);
    /// Returns the zero-based index of the specified bookmark in the collection.
    /// 
    /// @param name The case-insensitive name of the bookmark.
    /// 
    /// @return The zero based index. Negative value if not found.
    ASPOSE_WORDS_SHARED_API int32_t IndexOfKey(const System::String& name);
    /// Removes a bookmark with the specified name from the collection.
    /// 
    /// @param name The case-insensitive name of the bookmark.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& name);
    /// Removes a bookmark at the specified index.
    /// 
    /// @param index The zero based index.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all elements from the collection.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns an enumerator object that can be used to iterate over all items in the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::Collections::Generic::KeyValuePair<System::String, int32_t>>> GetEnumerator() override;

    ASPOSE_WORDS_SHARED_API BookmarksOutlineLevelCollection();

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

    virtual ASPOSE_WORDS_SHARED_API ~BookmarksOutlineLevelCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
