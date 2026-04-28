//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/MorphDataControl.h
#pragma once

#include <Aspose.Words.Cpp/Drawing/Ole/Forms2OleControl.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace System
{
namespace IO
{
class BinaryReader;
class BinaryWriter;
}
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

/// The MorphDataControl structure is an aggregate of six controls: CheckBox, ComboBox, ListBox, OptionButton, TextBox, and ToggleButton.
class ASPOSE_WORDS_SHARED_CLASS MorphDataControl : public Aspose::Words::Drawing::Ole::Forms2OleControl
{
    typedef MorphDataControl ThisType;
    typedef Aspose::Words::Drawing::Ole::Forms2OleControl BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

protected:

private:

    /// MorphDataPropMask1 enumeration.
    enum class MorphDataPropMask1 : uint32_t
    {
        VariousPropertyBits = 0x00000001,
        BackColor = 0x00000002,
        ForeColor = 0x00000004,
        MaxLength = 0x00000008,
        BorderStyle = 0x00000010,
        ScrollBars = 0x00000020,
        DisplayStyle = 0x00000040,
        MousePointer = 0x00000080,
        Size = 0x00000100,
        PasswordChar = 0x00000200,
        ListWidth = 0x00000400,
        BoundColumn = 0x00000800,
        TextColumn = 0x00001000,
        ColumnCount = 0x00002000,
        ListRows = 0x00004000,
        ColumnInfo = 0x00008000,
        MatchEntry = 0x00010000,
        ListStyle = 0x00020000,
        ShowDropButtonWhen = 0x00040000,
        UnusedBits1 = 0x00080000,
        DropButtonStyle = 0x00100000,
        MultiSelect = 0x00200000,
        Value = 0x00400000,
        Caption = 0x00800000,
        PicturePosition = 0x01000000,
        BorderColor = 0x02000000,
        SpecialEffect = 0x04000000,
        MouseIcon = 0x08000000,
        Picture = 0x10000000,
        Accelerator = 0x20000000,
        UnusedBits2 = 0x40000000,
        Reserved = 0x80000000
    };
    DECLARE_FRIEND_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::MorphDataControl::MorphDataPropMask1);

    /// MorphDataPropMask2 enumeration.
    enum class MorphDataPropMask2 : uint32_t
    {
        GroupName = 0x00000001
    };
    DECLARE_FRIEND_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::MorphDataControl::MorphDataPropMask2);

protected:

    ASPOSE_WORDS_SHARED_API void Read(System::SharedPtr<System::IO::BinaryReader> ) override;
    ASPOSE_WORDS_SHARED_API uint32_t Write(System::SharedPtr<System::IO::BinaryWriter> ) override;

};

DECLARE_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::MorphDataControl::MorphDataPropMask1);
DECLARE_USING_GLOBAL_OPERATORS

DECLARE_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::MorphDataControl::MorphDataPropMask2);
DECLARE_USING_GLOBAL_OPERATORS
}
}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Drawing::Ole);
