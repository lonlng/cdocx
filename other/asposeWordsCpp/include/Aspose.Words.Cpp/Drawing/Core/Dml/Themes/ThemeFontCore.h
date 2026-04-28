//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/Dml/Themes/ThemeFontCore.h
#pragma once

#include <system/enum_helpers.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

namespace Dml {

namespace Themes {

/// ThemeFontCore enumeration.
enum class ThemeFontCore
{
    None = 0x00000000,
    MajorAscii = 0x00010001,
    MajorBidi = 0x00010002,
    MajorEastAsia = 0x00010003,
    MajorHAnsi = 0x00010004,
    MinorAscii = 0x00020001,
    MinorBidi = 0x00020002,
    MinorEastAsia = 0x00020003,
    MinorHAnsi = 0x00020004,
    GroupMask = 0x00ff0000,
    Major = 0x00010000,
    Minor = 0x00020000,
    RegionMask = 0x0000ffff,
    Ascii = 0x00000001,
    Bidi = 0x00000002,
    EastAsia = 0x00000003,
    HAnsi = 0x00000004
};

DECLARE_ENUM_OPERATORS(Aspose::Words::Drawing::Core::Dml::Themes::ThemeFontCore);
DECLARE_USING_GLOBAL_OPERATORS

}
}
}
}
}
}

DECLARE_USING_ENUM_OPERATORS(Aspose::Words::Drawing::Core::Dml::Themes);
