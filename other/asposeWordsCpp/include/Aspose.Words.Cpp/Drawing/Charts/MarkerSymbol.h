//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Charts/MarkerSymbol.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Charts {

/// Specifies marker symbol style.
enum class ASPOSE_WORDS_SHARED_CLASS MarkerSymbol
{
    /// Specifies a default marker symbol shall be drawn at each data point.
    Default,
    /// Specifies a circle shall be drawn at each data point.
    Circle,
    /// Specifies a dash shall be drawn at each data point.
    Dash,
    /// Specifies a diamond shall be drawn at each data point.
    Diamond,
    /// Specifies a dot shall be drawn at each data point.
    Dot,
    /// Specifies nothing shall be drawn at each data point.
    None,
    /// Specifies a picture shall be drawn at each data point.
    Picture,
    /// Specifies a plus shall be drawn at each data point.
    Plus,
    /// Specifies a square shall be drawn at each data point.
    Square,
    /// Specifies a star shall be drawn at each data point.
    Star,
    /// Specifies a triangle shall be drawn at each data point.
    Triangle,
    /// Specifies an X shall be drawn at each data point.
    X
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Charts::MarkerSymbol>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Charts::MarkerSymbol, const char_t*>, 12>& values();
};
