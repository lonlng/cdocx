//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/ITextBox.h
#pragma once

#include <system/object.h>

#include <Aspose.Words.Cpp/Drawing/TextBoxWrapMode.h>
#include <Aspose.Words.Cpp/Drawing/ShapeMarkupLanguage.h>
#include <Aspose.Words.Cpp/Drawing/LayoutFlow.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// \cond
class ITextBox : public virtual System::Object
{
    typedef ITextBox ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    RTTI_INFO_DECL();

public:

    virtual Aspose::Words::Drawing::TextBoxWrapMode get_TextBoxWrapMode_ITextBox() = 0;
    virtual Aspose::Words::Drawing::LayoutFlow get_TextboxLayoutFlow_ITextBox() = 0;
    virtual bool get_HasVerticalTextFlow_ITextBox() = 0;
    virtual Aspose::Words::Drawing::ShapeMarkupLanguage get_MarkupLanguage_ITextBox() = 0;

    virtual float GetHorizontalMargins_ITextBox() = 0;

};/// \endcond

}
}
}
}
