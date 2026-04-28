//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Saving/OutlineOptions.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Saving
{
class BookmarksOutlineLevelCollection;

}
}
}

namespace Aspose {

namespace Words {

namespace Saving {

/// Allows to specify outline options.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/save-a-document/">Save a Document</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS OutlineOptions : public System::Object
{
    typedef OutlineOptions ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets a value determining whether or not to create missing outline levels when the document is
    /// exported.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_CreateMissingOutlineLevels() const;
    /// Sets a value determining whether or not to create missing outline levels when the document is
    /// exported.
    /// Default value for this property is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_CreateMissingOutlineLevels(bool value);
    /// Specifies how many levels of headings (paragraphs formatted with the Heading styles) to include in the
    /// document outline.
    /// 
    /// Specify 0 for no headings in the outline; specify 1 for one level of headings in the outline and so on.
    /// 
    /// Default is 0. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API int32_t get_HeadingsOutlineLevels() const;
    /// Setter for Aspose::Words::Saving::OutlineOptions::get_HeadingsOutlineLevels
    ASPOSE_WORDS_SHARED_API void set_HeadingsOutlineLevels(int32_t value);
    /// Specifies how many levels in the document outline to show expanded when the file is viewed.
    /// 
    /// Note that this options will not work when saving to XPS.
    /// 
    /// Specify 0 and the document outline will be collapsed; specify 1 and the first level items
    /// in the outline will be expanded and so on.
    /// 
    /// Default is 0. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API int32_t get_ExpandedOutlineLevels() const;
    /// Setter for Aspose::Words::Saving::OutlineOptions::get_ExpandedOutlineLevels
    ASPOSE_WORDS_SHARED_API void set_ExpandedOutlineLevels(int32_t value);
    /// Specifies the default level in the document outline at which to display Word bookmarks.
    /// 
    /// Individual bookmarks level could be specified using <see cref="Aspose::Words::Saving::OutlineOptions::get_BookmarksOutlineLevels">BookmarksOutlineLevels</see> property.
    /// 
    /// Specify 0 and Word bookmarks will not be displayed in the document outline.
    /// Specify 1 and Word bookmarks will be displayed in the document outline at level 1; 2 for level 2 and so on.
    /// 
    /// Default is 0. Valid range is 0 to 9.
    ASPOSE_WORDS_SHARED_API int32_t get_DefaultBookmarksOutlineLevel() const;
    /// Setter for Aspose::Words::Saving::OutlineOptions::get_DefaultBookmarksOutlineLevel
    ASPOSE_WORDS_SHARED_API void set_DefaultBookmarksOutlineLevel(int32_t value);
    /// Allows to specify individual bookmarks outline level.
    /// 
    /// If bookmark level is not specified in this collection then <see cref="Aspose::Words::Saving::OutlineOptions::get_DefaultBookmarksOutlineLevel">DefaultBookmarksOutlineLevel</see> value is used.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Saving::BookmarksOutlineLevelCollection> get_BookmarksOutlineLevels() const;
    /// Specifies whether or not to create outlines for headings (paragraphs formatted with the Heading styles) inside tables.
    /// 
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API bool get_CreateOutlinesForHeadingsInTables() const;
    /// Specifies whether or not to create outlines for headings (paragraphs formatted with the Heading styles) inside tables.
    /// 
    /// Default value is <c>%false</c>.
    ASPOSE_WORDS_SHARED_API void set_CreateOutlinesForHeadingsInTables(bool value);

    ASPOSE_WORDS_SHARED_API OutlineOptions();

protected:

private:

    __TypeStub<4,4,4,4>::type mField0;
    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<4,4,4,4>::type mField2;
    System::SharedPtr<System::Object> mField3;
    __TypeStub<1,1,1,1>::type mField4;
    __TypeStub<1,1,1,1>::type mField5;

};

}
}
}
