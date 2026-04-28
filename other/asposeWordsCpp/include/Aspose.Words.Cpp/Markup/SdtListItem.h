//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtListItem.h
#pragma once

#include <system/string.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// This element specifies a single list item within a parent <see cref="Aspose::Words::Markup::SdtType::ComboBox">ComboBox</see> or <see cref="Aspose::Words::Markup::SdtType::DropDownList">DropDownList</see> structured document tag.
/// To learn more, visit the <a href="https://docs.aspose.com/words/net/working-with-content-control-sdt/">Structured Document Tags or Content Control</a> documentation article.
class ASPOSE_WORDS_SHARED_CLASS SdtListItem : public System::Object
{
    typedef SdtListItem ThisType;
    typedef System::Object BaseType;

    typedef ::System::BaseTypesInfo<BaseType> ThisTypeBaseTypesInfo;
    ASPOSE_WORDS_SHARED_RTTI_INFO_DECL();

public:

    /// Gets the text to display in the run content in place of the <see cref="Aspose::Words::Markup::SdtListItem::get_Value">Value</see> attribute contents for this list item.
    /// 
    /// Cannot be <c>%null</c> and cannot be an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_DisplayText() const;
    /// Gets the value of this list item.
    /// 
    /// Cannot be <c>%null</c> and cannot be an empty string.
    ASPOSE_WORDS_SHARED_API System::String get_Value() const;

    /// Initializes a new instance of this class.
    ASPOSE_WORDS_SHARED_API SdtListItem(const System::String& displayText, const System::String& value);
    /// Initializes a new instance of this class.
    ASPOSE_WORDS_SHARED_API SdtListItem(const System::String& value);

protected:

    SdtListItem();

private:

    System::String mField0;
    System::String mField1;

};

}
}
}
