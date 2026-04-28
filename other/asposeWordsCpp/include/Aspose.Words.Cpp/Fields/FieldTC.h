//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldTC.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/ITocEntry.h>
#include <Aspose.Words.Cpp/Fields/IFieldCodeTokenInfoProvider.h>
#include <Aspose.Words.Cpp/Fields/Field.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{

namespace Words
{
namespace Fields
{

class FieldEnd;
class FieldSeparator;
class FieldStart;
enum class FieldSwitchType;

}
class Node;
class NodeRange;
class Paragraph;
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the TC field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldTC final : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::ITocEntry
{
    typedef FieldTC ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::ITocEntry BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text of the entry.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Sets the text of the entry.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);
    /// Gets a type identifier for this field (which is typically a letter).
    ASPOSE_WORDS_SHARED_API System::String get_TypeIdentifier();
    /// Sets a type identifier for this field (which is typically a letter).
    ASPOSE_WORDS_SHARED_API void set_TypeIdentifier(const System::String& value);
    /// Gets the level of the entry.
    ASPOSE_WORDS_SHARED_API System::String get_EntryLevel();
    /// Sets the level of the entry.
    ASPOSE_WORDS_SHARED_API void set_EntryLevel(const System::String& value);
    /// Gets whether page number in TOC should be omitted for this field.
    ASPOSE_WORDS_SHARED_API bool get_OmitPageNumber() override;
    /// Sets whether page number in TOC should be omitted for this field.
    ASPOSE_WORDS_SHARED_API void set_OmitPageNumber(bool value);

    ASPOSE_WORDS_SHARED_API FieldTC();

protected:

    ASPOSE_WORDS_SHARED_API void Initialize(System::SharedPtr<Aspose::Words::Fields::FieldStart> , System::SharedPtr<Aspose::Words::Fields::FieldSeparator> , System::SharedPtr<Aspose::Words::Fields::FieldEnd> ) override;

private:

    System::SharedPtr<System::Object> mField0;

    System::SharedPtr<Aspose::Words::Paragraph> get_Paragraph() override;
    int32_t get_Level() override;
    bool get_IsInFieldCode() override;
    bool get_HasBookmark() override;
    bool get_IsLinkedStyleTocEntry() override;

    __TypeStub<4,4,4,4>::type mField1;
    __TypeStub<1,1,1,1>::type mField2;

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;
    System::SharedPtr<Aspose::Words::NodeRange> InsertBookmark(System::String ) override;
    System::String GetDocumentOutlineTitle() override;
    System::SharedPtr<Aspose::Words::NodeRange> GetLabelRange() override;
    int32_t GetSequenceValue(System::String ) override;
    int32_t GetPageNumber() override;

};

}
}
}
