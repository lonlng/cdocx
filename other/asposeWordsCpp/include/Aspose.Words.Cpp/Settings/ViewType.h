//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Settings/ViewType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Settings {

/// Possible values for the view mode in %Microsoft Word.
/// 
/// @sa Aspose::Words::Settings::ViewOptions
/// @sa Aspose::Words::Settings::ViewOptions::get_ViewType
enum class ASPOSE_WORDS_SHARED_CLASS ViewType
{
    /// The document shall be rendered in the default view of the application.
    None = 0,
    /// The document shall be rendered in the default view of the application.
    Reading = 0,
    /// The document shall be opened in a view that displays the document as it will print.
    PageLayout = 1,
    /// The document shall be rendered in a view optimized for outlining or creating long documents.
    Outline = 3,
    /// The document shall be rendered in a view optimized for outlining or creating long documents.
    Normal = 4,
    /// The document shall be rendered in a view mimicking the way this document would be displayed
    /// in a web page.
    Web = 5
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Settings::ViewType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Settings::ViewType, const char_t*>, 6>& values();
};
