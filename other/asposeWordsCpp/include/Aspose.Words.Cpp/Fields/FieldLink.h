//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldLink.h
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
}
}
namespace System
{
class String;
}

namespace Aspose {

namespace Words {

namespace Fields {

/// Implements the LINK field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldLink : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldLink ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the application type of the link information.
    ASPOSE_WORDS_SHARED_API System::String get_ProgId();
    /// Sets the application type of the link information.
    ASPOSE_WORDS_SHARED_API void set_ProgId(const System::String& value);
    /// Gets the name and location of the source file.
    ASPOSE_WORDS_SHARED_API System::String get_SourceFullName();
    /// Sets the name and location of the source file.
    ASPOSE_WORDS_SHARED_API void set_SourceFullName(const System::String& value);
    /// Gets the portion of the source file that's being linked.
    ASPOSE_WORDS_SHARED_API System::String get_SourceItem();
    /// Sets the portion of the source file that's being linked.
    ASPOSE_WORDS_SHARED_API void set_SourceItem(const System::String& value);
    /// Gets whether to update this field automatically.
    ASPOSE_WORDS_SHARED_API bool get_AutoUpdate();
    /// Sets whether to update this field automatically.
    ASPOSE_WORDS_SHARED_API void set_AutoUpdate(bool value);
    /// Gets whether to insert the linked object as a bitmap.
    ASPOSE_WORDS_SHARED_API bool get_InsertAsBitmap();
    /// Sets whether to insert the linked object as a bitmap.
    ASPOSE_WORDS_SHARED_API void set_InsertAsBitmap(bool value);
    /// Gets whether to reduce the file size by not storing graphics data with the document.
    ASPOSE_WORDS_SHARED_API bool get_IsLinked();
    /// Sets whether to reduce the file size by not storing graphics data with the document.
    ASPOSE_WORDS_SHARED_API void set_IsLinked(bool value);
    /// Gets a way the linked object updates its formatting.
    ASPOSE_WORDS_SHARED_API System::String get_FormatUpdateType();
    /// Sets a way the linked object updates its formatting.
    ASPOSE_WORDS_SHARED_API void set_FormatUpdateType(const System::String& value);
    /// Gets whether to insert the linked object as HTML format text.
    ASPOSE_WORDS_SHARED_API bool get_InsertAsHtml();
    /// Sets whether to insert the linked object as HTML format text.
    ASPOSE_WORDS_SHARED_API void set_InsertAsHtml(bool value);
    /// Gets whether to insert the linked object as a picture.
    ASPOSE_WORDS_SHARED_API bool get_InsertAsPicture();
    /// Sets whether to insert the linked object as a picture.
    ASPOSE_WORDS_SHARED_API void set_InsertAsPicture(bool value);
    /// Gets whether to insert the linked object in rich-text format (RTF).
    ASPOSE_WORDS_SHARED_API bool get_InsertAsRtf();
    /// Sets whether to insert the linked object in rich-text format (RTF).
    ASPOSE_WORDS_SHARED_API void set_InsertAsRtf(bool value);
    /// Gets whether to insert the linked object in text-only format.
    ASPOSE_WORDS_SHARED_API bool get_InsertAsText();
    /// Sets whether to insert the linked object in text-only format.
    ASPOSE_WORDS_SHARED_API void set_InsertAsText(bool value);
    /// Gets whether to insert the linked object as Unicode text.
    ASPOSE_WORDS_SHARED_API bool get_InsertAsUnicode();
    /// Sets whether to insert the linked object as Unicode text.
    ASPOSE_WORDS_SHARED_API void set_InsertAsUnicode(bool value);

protected:

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

protected:

};

}
}
}
