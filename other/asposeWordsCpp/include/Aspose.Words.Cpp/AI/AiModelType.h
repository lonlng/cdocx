//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/AI/AiModelType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace AI {

/// Represents the types of <see cref="Aspose::Words::AI::AiModel">AiModel</see> that can be integrated into the document processing workflow.
enum class ASPOSE_WORDS_SHARED_CLASS AiModelType
{
    /// GPT-4o generative model type.
    Gpt4O = 0,
    /// GPT-4o mini generative model type.
    Gpt4OMini = 1,
    /// GPT-4 Turbo generative model type.
    Gpt4Turbo = 2,
    /// GPT-3.5 Turbo generative model type.
    Gpt35Turbo = 3,
    /// Gemini Flash latest release generative model type.
    GeminiFlashLatest = 4,
    /// Gemini Pro latest release generative model type.
    GeminiProLatest = 6,
    /// Claude 3.5 Sonnet generative model type.
    Claude35Sonnet = 7,
    /// Claude 3.5 Haiku generative model type.
    Claude35Haiku = 8,
    /// Claude 3 Opus generative model type.
    Claude3Opus = 9,
    /// Claude 3 Sonnet generative model type.
    Claude3Sonnet = 10,
    /// Claude 3 Haiku generative model type.
    Claude3Haiku = 11
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::AI::AiModelType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::AI::AiModelType, const char_t*>, 11>& values();
};
