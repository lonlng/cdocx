//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldXE.h
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

}

class Node;
class NodeRange;

}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the XE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldXE : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldXE ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text of the entry.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Sets the text of the entry.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Gets whether to apply bold formatting to the entry's page number.
    ASPOSE_WORDS_SHARED_API bool get_IsBold();
    /// Sets whether to apply bold formatting to the entry's page number.
    ASPOSE_WORDS_SHARED_API void set_IsBold(bool value);
    /// Gets an index entry type.
    ASPOSE_WORDS_SHARED_API System::String get_EntryType();
    /// Sets an index entry type.
    ASPOSE_WORDS_SHARED_API void set_EntryType(const System::String& value);
    /// Gets whether to apply italic formatting to the entry's page number.
    ASPOSE_WORDS_SHARED_API bool get_IsItalic();
    /// Sets whether to apply italic formatting to the entry's page number.
    ASPOSE_WORDS_SHARED_API void set_IsItalic(bool value);
    /// Gets the name of the bookmark that marks a range of pages that is inserted as the entry's page number.
    ASPOSE_WORDS_SHARED_API System::String get_PageRangeBookmarkName();
    /// Sets the name of the bookmark that marks a range of pages that is inserted as the entry's page number.
    ASPOSE_WORDS_SHARED_API void set_PageRangeBookmarkName(const System::String& value);
    /// Gets text used in place of a page number.
    ASPOSE_WORDS_SHARED_API System::String get_PageNumberReplacement();
    /// Sets text used in place of a page number.
    ASPOSE_WORDS_SHARED_API void set_PageNumberReplacement(const System::String& value);
    /// Gets the yomi (first phonetic character for sorting indexes) for the index entry
    ASPOSE_WORDS_SHARED_API System::String get_Yomi();
    /// Sets the yomi (first phonetic character for sorting indexes) for the index entry
    ASPOSE_WORDS_SHARED_API void set_Yomi(const System::String& value);

protected:

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
