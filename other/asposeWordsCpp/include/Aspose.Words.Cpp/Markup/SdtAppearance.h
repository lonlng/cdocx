//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Markup/SdtAppearance.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>
#include <cstdint>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Markup {

/// Specifies the appearance of a structured document tag.
enum class ASPOSE_WORDS_SHARED_CLASS SdtAppearance
{
    /// Represents a structured document tag shown as a shaded rectangle or bounding box.
    BoundingBox,
    /// Represents a structured document tag shown as start and end markers.
    Tags,
    /// Represents a structured document tag that is not shown.
    Hidden,
    /// Defaults to <see cref="Aspose::Words::Markup::SdtAppearance::BoundingBox">BoundingBox</see>.
    Default = static_cast<int32_t>(BoundingBox)
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Markup::SdtAppearance>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Markup::SdtAppearance, const char_t*>, 4>& values();
};
