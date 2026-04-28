//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Fonts/FontEmbeddingUsagePermissions.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Fonts {

/// Represents the font embedding usage permissions.
enum class ASPOSE_WORDS_SHARED_CLASS FontEmbeddingUsagePermissions
{
    /// The font may be embedded, and may be permanently installed for use on a remote systems, or for use by
    /// other users.
    Installable = 0,
    /// The font must not be modified, embedded or exchanged in any manner without first obtaining explicit
    /// permission of the legal owner.
    RestrictedLicense = 1,
    /// The font may be embedded, and may be temporarily loaded on other systems for purposes of viewing or
    /// printing the document.
    PrintAndPreview = 2,
    /// The font may be embedded, and may be temporarily loaded on other systems.
    Editable = 3
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Fonts::FontEmbeddingUsagePermissions>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Fonts::FontEmbeddingUsagePermissions, const char_t*>, 4>& values();
};
