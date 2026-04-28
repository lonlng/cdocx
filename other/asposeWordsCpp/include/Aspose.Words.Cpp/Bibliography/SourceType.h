//////////////////////////////////////////////////////////////////////////
// Copyright 2001-2026 Aspose Pty Ltd. All Rights Reserved.
//
// This file is part of Aspose.Words. The source code in this file
// is only intended as a supplement to the documentation, and is provided
// "as is", without warranty of any kind, either expressed or implied.
//////////////////////////////////////////////////////////////////////////
/// \file Aspose.Words.Cpp/Bibliography/SourceType.h
#pragma once

#include <system/object_ext.h>
#include <system/enum.h>

#include <Aspose.Words.Cpp/aspose_words_api_defs.h>

namespace Aspose {

namespace Words {

namespace Bibliography {

/// Represents bibliography source types.
enum class ASPOSE_WORDS_SHARED_CLASS SourceType
{
    /// Specifies the article in a periodical source.
    ArticleInAPeriodical,
    /// Specifies the book source.
    Book,
    /// Specifies the book section source.
    BookSection,
    /// Specifies the journal article source.
    JournalArticle,
    /// Specifies the conference proceedings source.
    ConferenceProceedings,
    /// Specifies the reporter source.
    Report,
    /// Specifies the sound recording source.
    SoundRecording,
    /// Specifies the performance source.
    Performance,
    /// Specifies the art source.
    Art,
    /// Specifies the document from internet site source.
    DocumentFromInternetSite,
    /// Specifies the internet site source.
    InternetSite,
    /// Specifies the film source.
    Film,
    /// Specifies the interview source.
    Interview,
    /// Specifies the patent source.
    Patent,
    /// Specifies the electronic source.
    Electronic,
    /// Specifies the case source.
    Case,
    /// Specifies the miscellaneous source.
    Misc
};

}
}
}

template<>
struct EnumMetaInfo<Aspose::Words::Bibliography::SourceType>
{
    static const ASPOSE_WORDS_SHARED_API std::array<std::pair<Aspose::Words::Bibliography::SourceType, const char_t*>, 17>& values();
};
