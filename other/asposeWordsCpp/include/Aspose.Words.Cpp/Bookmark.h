//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bookmark.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

class BookmarkEnd;
class BookmarkStart;

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

/// Represents a single bookmark.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-bookmarks/">Working with Bookmarks</a> documentation article.
/// 
/// <see cref="Aspose::Words::Bookmark">Bookmark</see> is a "facade" object that encapsulates two nodes <see cref="Aspose::Words::Bookmark::get_BookmarkStart">BookmarkStart</see>
/// and <see cref="Aspose::Words::Bookmark::get_BookmarkEnd">BookmarkEnd</see> in a document tree and allows to work with a bookmark as a single object.
class ASPOSE_WORDS_SHARED_CLASS Bookmark : public System::Object
{
    typedef Bookmark ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the bookmark.
    ASPOSE_WORDS_SHARED_API System::String get_Name();
    /// Sets the name of the bookmark.
    ASPOSE_WORDS_SHARED_API void set_Name(const System::String& value);
    /// Gets the text enclosed in the bookmark.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Sets the text enclosed in the bookmark.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Gets the node that represents the start of the bookmark.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BookmarkStart> get_BookmarkStart() const;
    /// Gets the node that represents the end of the bookmark.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::BookmarkEnd> get_BookmarkEnd();
    /// Returns <c>%true</c> if this bookmark is a table column bookmark.
    ASPOSE_WORDS_SHARED_API bool get_IsColumn();
    /// Gets the zero-based index of the first column of the table column range associated with the bookmark.
    ASPOSE_WORDS_SHARED_API int32_t get_FirstColumn();
    /// Gets the zero-based index of the last column of the table column range associated with the bookmark.
    ASPOSE_WORDS_SHARED_API int32_t get_LastColumn();

    /// Removes the bookmark from the document. Does not remove text inside the bookmark.
    ASPOSE_WORDS_SHARED_API void Remove();

protected:

private:

    System::SharedPtr<System::Object> mField0;
    System::SharedPtr<System::Object> mField1;

protected:

};

}
}
