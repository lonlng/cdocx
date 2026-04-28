//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/BookmarkCollection.h
#pragma once

#include <system/shared_ptr.h>
#include <system/collections/ienumerator.h>
#include <system/collections/ienumerable.h>
#include <cstdint>

#include <Aspose.Words.Cpp/NodeMatcher.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{
class Bookmark;

class Node;

}
}
namespace System
{

class String;
}

namespace Aspose {

namespace Words {

/// A collection of <see cref="Aspose::Words::Bookmark">Bookmark</see> objects that represent the bookmarks in the specified range.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-bookmarks/">Working with Bookmarks</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS BookmarkCollection : public System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bookmark>>
{
    typedef BookmarkCollection ThisType;
    typedef System::Collections::Generic::IEnumerable<System::SharedPtr<Aspose::Words::Bookmark>> BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Returns the number of bookmarks in the collection.
    ASPOSE_WORDS_SHARED_API int32_t get_Count();

    /// Returns a bookmark at the specified index.
    /// 
    /// The index is zero-based.
    /// 
    /// Negative indexes are allowed and indicate access from the back of the collection.
    /// For example -1 means the last item, -2 means the second before last and so on.
    /// 
    /// If index is greater than or equal to the number of items in the list, this returns a null reference.
    /// 
    /// If index is negative and its absolute value is greater than the number of items in the list, this returns a null reference.
    /// 
    /// @param index An index into the collection.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bookmark> idx_get(int32_t index);
    /// Returns a bookmark by name.
    /// 
    /// Returns <c>%null</c> if the bookmark with the specified name cannot be found.
    /// 
    /// @param bookmarkName Case-insensitive name of the bookmark.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Bookmark> idx_get(const System::String& bookmarkName);

    /// Removes the specified bookmark from the document.
    /// 
    /// @param bookmark The bookmark to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::SharedPtr<Aspose::Words::Bookmark>& bookmark);
    /// Removes a bookmark with the specified name.
    /// 
    /// @param bookmarkName The case-insensitive name of the bookmark to remove.
    ASPOSE_WORDS_SHARED_API void Remove(const System::String& bookmarkName);
    /// Removes a bookmark at the specified index.
    /// 
    /// @param index The zero-based index of the bookmark to remove.
    ASPOSE_WORDS_SHARED_API void RemoveAt(int32_t index);
    /// Removes all bookmarks from this collection and from the document.
    ASPOSE_WORDS_SHARED_API void Clear();
    /// Returns an enumerator object.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<System::Collections::Generic::IEnumerator<System::SharedPtr<Aspose::Words::Bookmark>>> GetEnumerator() override;

protected:

    virtual ASPOSE_WORDS_SHARED_API ~BookmarkCollection();

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
