//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/WatermarkType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

/// Specifies the watermark type.
enum class ASPOSE_WORDS_SHARED_CLASS WatermarkType
{
    /// Indicates that the text will be used as a watermark.
    /// Such a watermark corresponds to a WordArt object.
    Text,
    /// Indicates that the image will be used as a watermark.
    /// Such a watermark corresponds to a shape with image.
    Image,
    /// Indicates watermark is no set.
    None
};

}
}

template<>
struct EnumMetaInfo<Aspose::Words::WatermarkType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::WatermarkType, const char_t*>, 3>& values();
};
