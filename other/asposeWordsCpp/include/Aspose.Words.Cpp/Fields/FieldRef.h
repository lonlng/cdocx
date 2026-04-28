//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldRef.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IMergeFieldSurrogate.h>
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
class FieldUpdateAction;
enum class FieldUpdateStage;
}
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

/// Implements the REF field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldRef : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider, public Aspose::Words::Fields::IMergeFieldSurrogate
{
    typedef FieldRef ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;
    typedef Aspose::Words::Fields::IMergeFieldSurrogate BaseType2;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1, BaseType2> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() override;
    /// Gets the node that represents the field separator. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator() override;
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() override;
    /// Gets the referenced bookmark's name.
    ASPOSE_WORDS_SHARED_API System::String get_BookmarkName();
    /// Sets the referenced bookmark's name.
    ASPOSE_WORDS_SHARED_API void set_BookmarkName(const System::String& value);
    /// Gets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API System::String get_NumberSeparator();
    /// Sets the character sequence that is used to separate sequence numbers and page numbers.
    ASPOSE_WORDS_SHARED_API void set_NumberSeparator(const System::String& value);
    /// Gets whether to increment footnote, endnote, and annotation numbers that are
    /// marked by the bookmark, and insert the corresponding footnote, endnote, and comment text.
    ASPOSE_WORDS_SHARED_API bool get_IncludeNoteOrComment();
    /// Sets whether to increment footnote, endnote, and annotation numbers that are
    /// marked by the bookmark, and insert the corresponding footnote, endnote, and comment text.
    ASPOSE_WORDS_SHARED_API void set_IncludeNoteOrComment(bool value);
    /// Gets whether to create a hyperlink to the bookmarked paragraph.
    ASPOSE_WORDS_SHARED_API bool get_InsertHyperlink();
    /// Sets whether to create a hyperlink to the bookmarked paragraph.
    ASPOSE_WORDS_SHARED_API void set_InsertHyperlink(bool value);
    /// Gets whether to insert the paragraph number of the referenced paragraph exactly as it appears in the document.
    ASPOSE_WORDS_SHARED_API bool get_InsertParagraphNumber();
    /// Sets whether to insert the paragraph number of the referenced paragraph exactly as it appears in the document.
    ASPOSE_WORDS_SHARED_API void set_InsertParagraphNumber(bool value);
    /// Gets whether to insert the relative position of the referenced paragraph.
    ASPOSE_WORDS_SHARED_API bool get_InsertRelativePosition();
    /// Sets whether to insert the relative position of the referenced paragraph.
    ASPOSE_WORDS_SHARED_API void set_InsertRelativePosition(bool value);
    /// Gets whether to insert the paragraph number of the referenced paragraph in relative context.
    ASPOSE_WORDS_SHARED_API bool get_InsertParagraphNumberInRelativeContext();
    /// Sets whether to insert the paragraph number of the referenced paragraph in relative context.
    ASPOSE_WORDS_SHARED_API void set_InsertParagraphNumberInRelativeContext(bool value);
    /// Gets whether to suppress non-delimiter characters.
    ASPOSE_WORDS_SHARED_API bool get_SuppressNonDelimiters();
    /// Sets whether to suppress non-delimiter characters.
    ASPOSE_WORDS_SHARED_API void set_SuppressNonDelimiters(bool value);
    /// Gets whether to insert the paragraph number of the referenced paragraph in full context.
    ASPOSE_WORDS_SHARED_API bool get_InsertParagraphNumberInFullContext();
    /// Sets whether to insert the paragraph number of the referenced paragraph in full context.
    ASPOSE_WORDS_SHARED_API void set_InsertParagraphNumberInFullContext(bool value);

protected:

    ASPOSE_WORDS_SHARED_API Aspose::Words::Fields::FieldUpdateStage GetUpdateStage() override;
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldUpdateAction> UpdateCore() override;

    virtual ASPOSE_WORDS_SHARED_API ~FieldRef();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;
    System::String GetMergeFieldName() override;
    bool CanWorkAsMergeField() override;
    bool IsMergeValueRequired() override;

};

}
}
}
