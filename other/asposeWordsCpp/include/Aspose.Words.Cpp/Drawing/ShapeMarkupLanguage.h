//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/ShapeMarkupLanguage.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

/// Specifies Markup language used for the shape.
enum class ASPOSE_WORDS_SHARED_CLASS ShapeMarkupLanguage : uint8_t
{
    /// Drawing Markup Language is used to define the shape.
    Dml,
    /// Vector Markup Language is used to define the shape.
    Vml
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::ShapeMarkupLanguage>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::ShapeMarkupLanguage, const char_t*>, 2>& values();
};
