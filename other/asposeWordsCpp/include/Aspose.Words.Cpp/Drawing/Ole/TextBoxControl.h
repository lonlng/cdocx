//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/TextBoxControl.h
#pragma once

#include <system/shared_ptr.h>

#include <Aspose.Words.Cpp/Drawing/Ole/MorphDataControl.h>
#include <Aspose.Words.Cpp/Drawing/Ole/Forms2OleControlType.h>
#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose
{
namespace Words
{

namespace Drawing
{
namespace Ole
{
class Forms2OleControl;
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
class String;
}

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

/// The TextBox control displays text from an organized set of data or user input.
class ASPOSE_WORDS_SHARED_CLASS TextBoxControl : public Aspose::Words::Drawing::Ole::MorphDataControl
{
    typedef TextBoxControl ThisType;
    typedef Aspose::Words::Drawing::Ole::MorphDataControl BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets type of Forms 2.0 control.
    ASPOSE_WORDS_SHARED_API Aspose::Words::Drawing::Ole::Forms2OleControlType get_Type() override;
    /// Gets a text of the control.
    ASPOSE_WORDS_SHARED_API System::String get_Text();
    /// Sets a text of the control.
    ASPOSE_WORDS_SHARED_API void set_Text(const System::String& value);

protected:

    ASPOSE_WORDS_SHARED_API Aspose::Words::Forms2::ClsidCacheIndex get_ClsidCacheIndex() override;

    ASPOSE_WORDS_SHARED_API System::String get_ClsidVirtual() override;

private:

    System::SharedPtr<System::Object> mField0;

};

}
}
}
}
