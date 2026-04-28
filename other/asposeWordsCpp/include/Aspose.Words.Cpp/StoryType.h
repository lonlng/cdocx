//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/StoryType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/Notes/FootnoteSeparatorType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Text of a Word document is stored in stories. <see cref="Aspose::Words::StoryType">StoryType</see> identifies a story.
enum class ASPOSE_WORDS_SHARED_CLASS StoryType
{
    /// Default value. There is no such story in the document.
    None = 0,
    /// Contains the main text of the document, represented by <see cref="Aspose::Words::Body">Body</see>.
    MainText = 1,
    /// Contains footnote text, represented by <see cref="Aspose::Words::Notes::Footnote">Footnote</see>.
    Footnotes = 2,
    /// Contains endnotes text, represented by <see cref="Aspose::Words::Notes::Footnote">Footnote</see>.
    Endnotes = 3,
    /// Contains document comments (annotations), represented by <see cref="Aspose::Words::Comment">Comment</see>.
    Comments = 4,
    /// Contains shape or textbox text, represented by <see cref="Aspose::Words::Drawing::Shape">Shape</see>.
    Textbox = 5,
    /// Contains text of the even pages header, represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    EvenPagesHeader = 6,
    /// Contains text of the primary header. When header is different for odd and even pages,
    /// contains text of the odd pages header. Represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    PrimaryHeader = 7,
    /// Contains text of the even pages footer, represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    EvenPagesFooter = 8,
    /// Contains text of the primary footer. When footer is different for odd and even pages,
    /// contains text of the odd pages footer. Represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    PrimaryFooter = 9,
    /// Contains text of the first page header, represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    FirstPageHeader = 10,
    /// Contains text of the first page footer, represented by <see cref="Aspose::Words::HeaderFooter">HeaderFooter</see>.
    FirstPageFooter = 11,
    /// Contains the text of the footnote separator.
    FootnoteSeparator = 12,
    /// Contains the text of the footnote continuation separator.
    FootnoteContinuationSeparator = 13,
    /// Contains the text of the footnote continuation notice separator.
    FootnoteContinuationNotice = 14,
    /// Contains the text of the endnote separator.
    EndnoteSeparator = 15,
    /// Contains the text of the endnote continuation separator.
    EndnoteContinuationSeparator = 16,
    /// Contains the text of the endnote continuation notice separator.
    EndnoteContinuationNotice = 17
};

/// \cond
class StoryTypeHelper : public System::Object
{
    typedef StoryTypeHelper ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    static System::String ToUpperString(Aspose::Words::StoryType enumValue);
    static bool IsFootnoteEndnoteCommentStory(Aspose::Words::StoryType storyType);
    static bool IsHeaderFooterStory(Aspose::Words::StoryType storyType);
    static bool IsHeader(Aspose::Words::StoryType storyType);
    static bool IsFooter(Aspose::Words::StoryType storyType);
    static Aspose::Words::StoryType FootnoteSeparatorTypeToStoryType(Aspose::Words::Notes::FootnoteSeparatorType type);

};/// \endcond

/// \cond
class StoryTypeStack : public System::Object
{
    typedef StoryTypeStack ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    Aspose::Words::StoryType get_Current();
    bool get_IsInHeaderOrFooter();
    bool get_IsInHeader() const;
    bool get_IsInFooter() const;

    void Push(Aspose::Words::StoryType storyType);
    void Pop(Aspose::Words::StoryType storyType);

    StoryTypeStack();

private:

    __TypeStub<1,1,1,1>::type mField0;

    __TypeStub<1,1,1,1>::type mField1;

    System::SharedPtr<System::Object> mField2;

};/// \endcond

}
}

template<>
struct EnumMetaInfo<Aspose::Words::StoryType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::StoryType, const char_t*>, 18>& values();
};
