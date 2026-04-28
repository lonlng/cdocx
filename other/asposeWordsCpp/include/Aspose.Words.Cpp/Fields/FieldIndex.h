//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldIndex.h
#pragma once

#include <system/object.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Bidi
{
class IBidiParagraphLevelOverride;
}

namespace Words
{

namespace Fields
{

enum class FieldSwitchType;
class FieldUpdateAction;

}
class INodeModifier;

class Node;
class NodeRange;

}
}
namespace System
{
class String;
namespace Text
{
class StringBuilder;
}
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the INDEX field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldIndex : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldIndex ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

private:

public:

    /// Gets the name of the bookmark that marks the portion of the document used to build the index.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName();
    /// Sets the name of the bookmark that marks the portion of the document used to build the index.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets the number of columns per page used when building the index.
    ASPOSE_WORDS_SHARED_API System::String get_NumberOfColumns();
    /// Sets the number of columns per page used when building the index.
    ASPOSE_WORDS_SHARED_API void set_NumberOfColumns(const System::String& value);
    /// Gets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceSeparator();
    /// Sets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API void set_SequenceSeparator(const System::String& value);
    /// Gets the character sequence that is used to separate an index entry and its page number.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumberSeparator();
    /// Sets the character sequence that is used to separate an index entry and its page number.
    ASPOSE_WORDS_SHARED_API void set_PageNumberSeparator(const System::String& value);
    /// Gets a value indicating whether a page number separator is overridden through the field's code.
    ASPOSE_WORDS_SHARED_API bool get_HasPageNumberSeparator();
    /// Gets an index entry type used to build the index.
    ASPOSE_WORDS_SHARED_API System::String get_EntryType();
    /// Sets an index entry type used to build the index.
    ASPOSE_WORDS_SHARED_API void set_EntryType(const System::String& value);
    /// Gets the character sequence that is used to separate the start and end of a page range.
    ASPOSE_WORDS_SHARED_API System::String get_PageRangeSeparator();
    /// Sets the character sequence that is used to separate the start and end of a page range.
    ASPOSE_WORDS_SHARED_API void set_PageRangeSeparator(const System::String& value);
    /// Gets a heading that appears at the start of each set of entries for any given letter.
    ASPOSE_WORDS_SHARED_API System::String get_Heading();
    /// Sets a heading that appears at the start of each set of entries for any given letter.
    ASPOSE_WORDS_SHARED_API void set_Heading(const System::String& value);
    /// Gets the character sequence that is used to separate cross references and other entries.
    ASPOSE_WORDS_SHARED_API System::String get_CrossReferenceSeparator();
    /// Sets the character sequence that is used to separate cross references and other entries.
    ASPOSE_WORDS_SHARED_API void set_CrossReferenceSeparator(const System::String& value);
    /// Gets the character sequence that is used to separate two page numbers in a page number list.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumberListSeparator();
    /// Sets the character sequence that is used to separate two page numbers in a page number list.
    ASPOSE_WORDS_SHARED_API void set_PageNumberListSeparator(const System::String& value);
    /// Gets a range of letters to which limit the index.
    ASPOSE_WORDS_SHARED_API System::String get_LetterRange();
    /// Sets a range of letters to which limit the index.
    ASPOSE_WORDS_SHARED_API void set_LetterRange(const System::String& value);
    /// Gets whether run subentries into the same line as the main entry.
    ASPOSE_WORDS_SHARED_API bool get_RunSubentriesOnSameLine();
    /// Sets whether run subentries into the same line as the main entry.
    ASPOSE_WORDS_SHARED_API void set_RunSubentriesOnSameLine(bool value);
    /// Gets the name of a sequence whose number is included with the page number.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceName();
    /// Sets the name of a sequence whose number is included with the page number.
    ASPOSE_WORDS_SHARED_API void set_SequenceName(const System::String& value);
    /// Gets a value indicating whether a sequence should be used while the field's result building.
    ASPOSE_WORDS_SHARED_API bool get_HasSequenceName();
    /// Gets whether to enable the use of yomi text for index entries.
    ASPOSE_WORDS_SHARED_API bool get_UseYomi();
    /// Sets whether to enable the use of yomi text for index entries.
    ASPOSE_WORDS_SHARED_API void set_UseYomi(bool value);
    /// Gets the language ID used to generate the index.
    ASPOSE_WORDS_SHARED_API System::String get_LanguageId();
    /// Sets the language ID used to generate the index.
    ASPOSE_WORDS_SHARED_API void set_LanguageId(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Bidi::IBidiParagraphLevelOverride> GetBidiParagraphLevelOverride() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldIndex();

private:

    System::SharedPtr<System::Object> mField0;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
