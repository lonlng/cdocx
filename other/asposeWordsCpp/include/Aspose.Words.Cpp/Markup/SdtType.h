//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies the type of a structured document tag (SDT) node.
enum class ASPOSE_WORDS_SHARED_CLASS SdtType
{
    /// No type is assigned to the SDT.
    None,
    /// The SDT represents a bibliography entry.
    Bibliography,
    /// The SDT represents a citation.
    Citation,
    /// The SDT represents an equation.
    Equation,
    /// The SDT represents a drop down list when displayed in the document.
    DropDownList,
    /// The SDT represents a combo box when displayed in the document.
    ComboBox,
    /// The SDT represents a date picker when displayed in the document.
    Date,
    /// The SDT represents a building block gallery type.
    BuildingBlockGallery,
    /// The SDT represents a document part type.
    DocPartObj,
    /// The SDT represents a restricted grouping when displayed in the document.
    Group,
    /// The SDT represents a picture when displayed in the document.
    Picture,
    /// The SDT represents a rich text box when displayed in the document.
    RichText,
    /// The SDT represents a plain text box when displayed in the document.
    PlainText,
    /// The SDT represents a checkbox when displayed in the document.
    Checkbox,
    /// The SDT represents repeating section type when displayed in the document.
    RepeatingSection,
    /// The SDT represents repeating section item.
    RepeatingSectionItem,
    /// The SDT represents an entity picker that allows the user to select an instance of an external content type.
    EntityPicker
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Markup::SdtType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Markup::SdtType, const char_t*>, 17>& values();
};
