//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldToa.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Fields
{
enum class FieldSwitchType;
class FieldUpdateAction;

}
class INodeModifier;
}
}
namespace System
{
namespace Collections
{
namespace Generic
{
template <typename> class IEnumerable;
}
}
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the TOA field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldToa : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldToa ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the bookmark that marks the portion of the document used to build the table.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName();
    /// Sets the name of the bookmark that marks the portion of the document used to build the table.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets the integral category for entries included in the table.
    ASPOSE_WORDS_SHARED_API System::String get_EntryCategory();
    /// Sets the integral category for entries included in the table.
    ASPOSE_WORDS_SHARED_API void set_EntryCategory(const System::String& value);
    /// Gets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceSeparator();
    /// Sets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API void set_SequenceSeparator(const System::String& value);
    /// Gets the character sequence that is used to separate a table of authorities entry and its page number.
    ASPOSE_WORDS_SHARED_API System::String get_EntrySeparator();
    /// Sets the character sequence that is used to separate a table of authorities entry and its page number.
    ASPOSE_WORDS_SHARED_API void set_EntrySeparator(const System::String& value);
    /// Gets whether to remove the formatting of the entry text in the document from the
    /// entry in the table of authorities.
    ASPOSE_WORDS_SHARED_API bool get_RemoveEntryFormatting();
    /// Sets whether to remove the formatting of the entry text in the document from the
    /// entry in the table of authorities.
    ASPOSE_WORDS_SHARED_API void set_RemoveEntryFormatting(bool value);
    /// Gets the character sequence that is used to separate the start and end of a page range.
    ASPOSE_WORDS_SHARED_API System::String get_PageRangeSeparator();
    /// Sets the character sequence that is used to separate the start and end of a page range.
    ASPOSE_WORDS_SHARED_API void set_PageRangeSeparator(const System::String& value);
    /// Gets whether to include the category heading for the entries in a table of authorities.
    ASPOSE_WORDS_SHARED_API bool get_UseHeading();
    /// Sets whether to include the category heading for the entries in a table of authorities.
    ASPOSE_WORDS_SHARED_API void set_UseHeading(bool value);
    /// Gets the character sequence that is used to separate two page numbers in a page number list.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumberListSeparator();
    /// Sets the character sequence that is used to separate two page numbers in a page number list.
    ASPOSE_WORDS_SHARED_API void set_PageNumberListSeparator(const System::String& value);
    /// Gets whether to replace five or more different page references to the same
    /// authority with "passim", which is used to indicate that a word or passage occurs frequently
    /// in the work cited.
    ASPOSE_WORDS_SHARED_API bool get_UsePassim();
    /// Sets whether to replace five or more different page references to the same
    /// authority with "passim", which is used to indicate that a word or passage occurs frequently
    /// in the work cited.
    ASPOSE_WORDS_SHARED_API void set_UsePassim(bool value);
    /// Gets the name of a sequence whose number is included with the page number.
    ASPOSE_WORDS_SHARED_API System::String get_SequenceName();
    /// Sets the name of a sequence whose number is included with the page number.
    ASPOSE_WORDS_SHARED_API void set_SequenceName(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldToa();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
