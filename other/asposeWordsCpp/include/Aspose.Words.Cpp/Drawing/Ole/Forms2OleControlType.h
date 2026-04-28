//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Ole/Forms2OleControlType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Ole {

/// Enumerates types of Forms 2.0 controls.
enum class ASPOSE_WORDS_SHARED_CLASS Forms2OleControlType
{
    /// A radio button control.
    OptionButton,
    /// A control that displays text.
    Label,
    /// A control that allows the user to enter text.
    Textbox,
    /// A control that allows the user to select or deselect an option.
    CheckBox,
    /// A control that allows the user to toggle between two states.
    ToggleButton,
    /// A control that allows the user to increase or decrease a value.
    SpinButton,
    /// A control that allows the user to select an item from a list.
    ComboBox,
    /// A control that groups other controls.
    Frame,
    /// A control that displays multiple pages of content.
    MultiPage,
    /// A control that allows the user to switch between multiple pages of content.
    TabStrip,
    /// A button that triggers an action when clicked.
    CommandButton,
    /// A control that displays an image.
    Image,
    /// A control that allows the user to scroll through content.
    ScrollBar,
    /// A container for other controls.
    Form,
    /// A control that displays a list of items.
    ListBox
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Ole::Forms2OleControlType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Ole::Forms2OleControlType, const char_t*>, 15>& values();
};
