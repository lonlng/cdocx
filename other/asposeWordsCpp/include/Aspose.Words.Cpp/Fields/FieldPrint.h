//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldPrint.h
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

/// Implements the PRINT field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS FieldPrint : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IFieldCodeTokenInfoProvider
{
    typedef FieldPrint ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IFieldCodeTokenInfoProvider BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the printer-specific control code characters or PostScript instructions.
    ASPOSE_WORDS_SHARED_API System::String get_PrinterInstructions();
    /// Sets the printer-specific control code characters or PostScript instructions.
    ASPOSE_WORDS_SHARED_API void set_PrinterInstructions(const System::String& value);
    /// Gets the drawing rectangle that the PostScript instructions operate on.
    ASPOSE_WORDS_SHARED_API System::String get_PostScriptGroup();
    /// Sets the drawing rectangle that the PostScript instructions operate on.
    ASPOSE_WORDS_SHARED_API void set_PostScriptGroup(const System::String& value);

private:

    Aspose::Words::Fields::FieldSwitchType GetSwitchType(System::String ) override;

private:

};

}
}
}
