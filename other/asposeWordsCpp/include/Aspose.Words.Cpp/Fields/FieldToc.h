//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldToc.h
#pragma once

#include <system/array.h>

#include <Aspose.Words.Cpp/NodeReplacer.h>
#include <Aspose.Words.Cpp/Fields/IFieldFakeResultNodeModifier.h>
#include <Aspose.Words.Cpp/Fields/ITocEntryExtractorOptions.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
class Bookmark;

namespace Fields
{
class FieldEnd;

class FieldStart;
enum class FieldSwitchType;
class FieldUpdateAction;
enum class FieldUpdateStage;

class LevelRange;
}
class INodeModifier;

class Node;
class NodeRange;
class Paragraph;
class Style;

}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IList;
}
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the TOC field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldToc : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldToc ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the name of the bookmark that marks the portion of the document used to build the table.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName();
    /// Sets the name of the bookmark that marks the portion of the document used to build the table.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets the name of the sequence identifier used when building a table of figures.
    ASPOSE_WORDS_SHARED_API System::String get_TableOfFiguresLabel();
    /// Sets the name of the sequence identifier used when building a table of figures.
    ASPOSE_WORDS_SHARED_API void set_TableOfFiguresLabel(const System::String& value);
    /// Gets the name of the sequence identifier used when building a table of figures that does not include caption's
    /// label and number.
    ASPOSE_WORDS_SHARED_API System::String get_CaptionlessTableOfFiguresLabel();
    /// Sets the name of the sequence identifier used when building a table of figures that does not include caption's
    /// label and number.
    ASPOSE_WORDS_SHARED_API void set_CaptionlessTableOfFiguresLabel(const System::String& value);
    /// Gets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceSeparator();
    /// Sets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API void set_SequenceSeparator(const System::String& value);
    /// Gets a string that should match type identifiers of TC fields being included.
    ASPOSE_WORDS_SHARED_API System::String get_EntryIdentifier();
    /// Sets a string that should match type identifiers of TC fields being included.
    ASPOSE_WORDS_SHARED_API void set_EntryIdentifier(const System::String& value);
    /// Gets whether to make the table of contents entries hyperlinks.
    ASPOSE_WORDS_SHARED_API bool get_InsertHyperlinks();
    /// Sets whether to make the table of contents entries hyperlinks.
    ASPOSE_WORDS_SHARED_API void set_InsertHyperlinks(bool value);
    /// Gets a range of levels of the table of contents entries to be included.
    ASPOSE_WORDS_SHARED_API System::String get_EntryLevelRange();
    /// Sets a range of levels of the table of contents entries to be included.
    ASPOSE_WORDS_SHARED_API void set_EntryLevelRange(const System::String& value);
    /// Gets a range of levels of the table of contents entries from which to omits page numbers.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumberOmittingLevelRange();
    /// Sets a range of levels of the table of contents entries from which to omits page numbers.
    ASPOSE_WORDS_SHARED_API void set_PageNumberOmittingLevelRange(const System::String& value);
    /// Gets a range of heading levels to include.
    ASPOSE_WORDS_SHARED_API System::String get_HeadingLevelRange();
    /// Sets a range of heading levels to include.
    ASPOSE_WORDS_SHARED_API void set_HeadingLevelRange(const System::String& value);
    /// Gets a sequence of characters that separate an entry and its page number.
    ASPOSE_WORDS_SHARED_API System::String get_EntrySeparator();
    /// Sets a sequence of characters that separate an entry and its page number.
    ASPOSE_WORDS_SHARED_API void set_EntrySeparator(const System::String& value);
    /// Gets the identifier of a sequence for which a prefix should be added to the entry's page number.
    ASPOSE_WORDS_SHARED_API System::String get_PrefixedSequenceIdentifier();
    /// Sets the identifier of a sequence for which a prefix should be added to the entry's page number.
    ASPOSE_WORDS_SHARED_API void set_PrefixedSequenceIdentifier(const System::String& value);
    /// Gets a list of styles other than the built-in heading styles to include in the table of contents.
    ASPOSE_WORDS_SHARED_API System::String get_CustomStyles();
    /// Sets a list of styles other than the built-in heading styles to include in the table of contents.
    ASPOSE_WORDS_SHARED_API void set_CustomStyles(const System::String& value);
    /// Gets whether to use the applied paragraph outline level.
    ASPOSE_WORDS_SHARED_API bool get_UseParagraphOutlineLevel();
    /// Sets whether to use the applied paragraph outline level.
    ASPOSE_WORDS_SHARED_API void set_UseParagraphOutlineLevel(bool value);
    /// Gets whether to preserve tab entries within table entries.
    ASPOSE_WORDS_SHARED_API bool get_PreserveTabs();
    /// Sets whether to preserve tab entries within table entries.
    ASPOSE_WORDS_SHARED_API void set_PreserveTabs(bool value);
    /// Gets whether to preserve newline characters within table entries.
    ASPOSE_WORDS_SHARED_API bool get_PreserveLineBreaks();
    /// Sets whether to preserve newline characters within table entries.
    ASPOSE_WORDS_SHARED_API void set_PreserveLineBreaks(bool value);
    /// Gets whether to hide tab leader and page numbers in Web layout view.
    ASPOSE_WORDS_SHARED_API bool get_HideInWebLayout();
    /// Sets whether to hide tab leader and page numbers in Web layout view.
    ASPOSE_WORDS_SHARED_API void set_HideInWebLayout(bool value);

    /// Updates the page numbers for items in this table of contents.
    /// 
    /// @return <c>%true</c> if the operation is successful. If any of the related TOC bookmarks was removed, <c>%false</c> will be returned.
    ASPOSE_WORDS_SHARED_API bool UpdatePageNumbers();

    ASPOSE_WORDS_SHARED_API FieldToc();

protected:

    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateStage GetUpdateStage() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API void BeforeUnlink() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldToc();

private:

    __TypeStub<1,1,1,1>::type mField0;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
