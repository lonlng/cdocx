//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Drawing/Core/LineFillType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Drawing {

namespace Core {

/// LineFillType enumeration.
enum class LineFillType
{
    Solid = 0,
    Pattern = 1,
    Texture = 2,
    Picture = 3
};

}
}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Drawing::Core::LineFillType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Drawing::Core::LineFillType, const char_t*>, 4>& values();
};
