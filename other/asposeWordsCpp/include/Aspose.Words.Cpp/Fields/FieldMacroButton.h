//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fields/FieldMacroButton.h
#pragma once

#include <cstdint>

#include <Aspose.Words.Cpp/Fields/IMergeFieldSurrogate.h>
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

/// Implements the MACROBUTTON field.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-fields/">Working with Fields</a> documentation article.
/// 
/// Allows a macro or command to be run.
/// 
/// In %Aspose.Words this field can also act as a merge field.
class ASPOSE_WORDS_SHARED_CLASS FieldMacroButton : public Aspose::Words::Fields::Field, public Aspose::Words::Fields::IMergeFieldSurrogate
{
    typedef FieldMacroButton ThisType;
    typedef Aspose::Words::Fields::Field BaseType;
    typedef Aspose::Words::Fields::IMergeFieldSurrogate BaseType1;

    typedef ::System::BaseTypesInfo<BaseType, BaseType1> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the node that represents the start of the field.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldStart> get_Start() override;
    /// Gets the node that represents the field separator. Can be <c>%null</c>.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldSeparator> get_Separator() override;
    /// Gets the node that represents the field end.
    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::Fields::FieldEnd> get_End() override;
    /// Gets the name of the macro or command to run.
    ASPOSE_WORDS_SHARED_API System::String get_MacroName();
    /// Sets the name of the macro or command to run.
    ASPOSE_WORDS_SHARED_API void set_MacroName(const System::String& value);
    /// Gets the text to appear as the "button" that is selected to run the macro or command.
    ASPOSE_WORDS_SHARED_API System::String get_DisplayText();
    /// Sets the text to appear as the "button" that is selected to run the macro or command.
    ASPOSE_WORDS_SHARED_API void set_DisplayText(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API System::SharedPtr<Aspose::Words::NodeRange> GetFakeResult() override;

private:

    System::String GetMergeFieldName() override;
    bool CanWorkAsMergeField() override;
    bool IsMergeValueRequired() override;

private:

};

}
}
}
