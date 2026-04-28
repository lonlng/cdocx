//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldAdvance.h
#pragma once

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

/// Implements the ADVANCE field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldAdvance : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldAdvance ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the number of points by which the text that follows the field should be moved down.
    ASPOSE_WORDS_SHARED_API System::String get_DownOffset();
    /// Sets the number of points by which the text that follows the field should be moved down.
    ASPOSE_WORDS_SHARED_API void set_DownOffset(const System::String& value);
    /// Gets the number of points by which the text that follows the field should be moved left.
    ASPOSE_WORDS_SHARED_API System::String get_LeftOffset();
    /// Sets the number of points by which the text that follows the field should be moved left.
    ASPOSE_WORDS_SHARED_API void set_LeftOffset(const System::String& value);
    /// Gets the number of points by which the text that follows the field should be moved right.
    ASPOSE_WORDS_SHARED_API System::String get_RightOffset();
    /// Sets the number of points by which the text that follows the field should be moved right.
    ASPOSE_WORDS_SHARED_API void set_RightOffset(const System::String& value);
    /// Gets the number of points by which the text that follows the field should be moved up.
    ASPOSE_WORDS_SHARED_API System::String get_UpOffset();
    /// Sets the number of points by which the text that follows the field should be moved up.
    ASPOSE_WORDS_SHARED_API void set_UpOffset(const System::String& value);
    /// Gets the number of points by which the text that follows the field should be moved horizontally
    /// from the left edge of the column, frame, or text box.
    ASPOSE_WORDS_SHARED_API System::String get_HorizontalPosition();
    /// Sets the number of points by which the text that follows the field should be moved horizontally
    /// from the left edge of the column, frame, or text box.
    ASPOSE_WORDS_SHARED_API void set_HorizontalPosition(const System::String& value);
    /// Gets the number of points by which the text that follows the field should be moved vertically
    /// from the top edge of the page.
    ASPOSE_WORDS_SHARED_API System::String get_VerticalPosition();
    /// Sets the number of points by which the text that follows the field should be moved vertically
    /// from the top edge of the page.
    ASPOSE_WORDS_SHARED_API void set_VerticalPosition(const System::String& value);

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

};

}
}
}
