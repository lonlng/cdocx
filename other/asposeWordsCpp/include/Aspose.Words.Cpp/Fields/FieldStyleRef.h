//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldStyleRef.h
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
enum class FieldUpdateStage;

}
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the STYLEREF field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldStyleRef : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldStyleRef ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the name of the style by which the text to search for is formatted.
    ASPOSE_WORDS_SHARED_API System::String get_StyleName();
    /// Sets the name of the style by which the text to search for is formatted.
    ASPOSE_WORDS_SHARED_API void set_StyleName(const System::String& value);
    /// Gets whether to search from the bottom of the current page, rather from the top.
    ASPOSE_WORDS_SHARED_API bool get_SearchFromBottom();
    /// Sets whether to search from the bottom of the current page, rather from the top.
    ASPOSE_WORDS_SHARED_API void set_SearchFromBottom(bool value);
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

    virtual ASPOSE_WORDS_SHARED_API ~FieldStyleRef();

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
