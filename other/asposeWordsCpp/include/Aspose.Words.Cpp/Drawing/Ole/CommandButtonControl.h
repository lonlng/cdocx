//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/CommandButtonControl.h
#pragma once

#include <system/shared_ptr.h>
#include <system/enum_helpers.h>
#include <cstdint>

#include <Aspose.Words.Cpp/Drawing/Ole/Forms2OleControlType.h>
#include <Aspose.Words.Cpp/Drawing/Ole/Forms2OleControl.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{
namespace Ole
{
class OleControl;
}
}
namespace Forms2
{
enum class ClsidCacheIndex;

}
}
}
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

/// The CommandButton control runs a macro that performs an action when a user clicks it.
class ASPOSE_WORDS_SHARED_CLASS CommandButtonControl : public Aspose::Words::Drawing::Ole::Forms2OleControl
{
    typedef CommandButtonControl ThisType;
    typedef Aspose::Words::Drawing::Ole::Forms2OleControl BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

protected:

protected:

private:

    /// CommandButtonPropMask enumeration.
    enum class CommandButtonPropMask
    {
        ForeColor = 0x00000001,
        BackColor = 0x00000002,
        VariousPropertyBits = 0x00000004,
        Caption = 0x00000008,
        PicturePosition = 0x00000010,
        Size = 0x00000020,
        MousePointer = 0x00000040,
        Picture = 0x00000080,
        Accelerator = 0x00000100,
        TakeFocusOnClick = 0x00000200,
        MouseIcon = 0x00000400
    };
    DECLARE_FRIEND_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::CommandButtonControl::CommandButtonPropMask);

public:

    /// Gets type of Forms 2.0 control.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Ole::Forms2OleControlType get_Type() override;

    /// Initializes a new instance of <see cref="Aspose::Words::Drawing::Ole::CommandButtonControl">CommandButtonControl</see> class.
    ASPOSE_WORDS_SHARED_API CommandButtonControl();

protected:

    ASPOSE_WORDS_SHARED_API System::String get_ClsidVirtual() override;
    ASPOSE_WORDS_SHARED_API Aspose::Words::Forms2::ClsidCacheIndex get_ClsidCacheIndex() override;

    ASPOSE_WORDS_SHARED_API void Read(System::SharedPtr<System::IO::BinaryReader> ) override;
    ASPOSE_WORDS_SHARED_API uint32_t Write(System::SharedPtr<System::IO::BinaryWriter> ) override;

private:

    System::SharedPtr<System::Object> mField0;

};

DECLARE_ENUM_OPERATORS(Aspose::Words::Drawing::Ole::CommandButtonControl::CommandButtonPropMask);
DECLARE_USING_GLOBAL_OPERATORS
}
}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Drawing::Ole);
